#include <iostream>

#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/impl/handler.ipp>

namespace actor_zeta { namespace base {

    void error_sync_contacts(const std::string& name, const std::string& error) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Actor name : " << name << '\n';
        std::cerr << "Not initialization address type:" << error << '\n';
        std::cerr << "WARNING" << std::endl;
    }

    void error_duplicate_handler(const std::string& error) {
        std::cerr << "Duplicate" << '\n';
        std::cerr << "Handler: " << error << '\n';
        std::cerr << "Duplicate" << std::endl;
    }

    void error_add_handler(const std::string& error) {
        std::cerr << "error add handler" << '\n';
        std::cerr << "Handler: " << error << '\n';
        std::cerr << "error add handler" << std::endl;
    }

    void error_skip(const std::string& sender, const std::string& reciever, const std::string& handler) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Skip, can't find handler: " << reciever << "::" << handler;
        std::cerr << " sender: " << sender << "\n";
        std::cerr << "WARNING" << std::endl;
    }

    void communication_module::execute() {
        const auto& cmd = current_message()->command();
        auto it = handlers_.find(cmd);
        if (it != handlers_.end()) {
            return it->second->invoke(*this);
        }
        //auto sender = current_message()->sender().type();
        auto sender = "sender";
        auto reciever = this->type();
        error_skip(sender, reciever, current_message()->command());
    }

    bool communication_module::on(const std::string& name, handler* aa) {
        auto it = handlers_.find(name);
        bool status = false;
        if (it == handlers_.end()) {
            auto it1 = handlers_.emplace(name, std::unique_ptr<handler>(aa));
            status = it1.second;
            if (status == false) {
                error_add_handler(name);
            }
        } else {
            error_duplicate_handler(name);
        }

        return status;
    }

    void communication_module::enqueue(message_ptr msg) {
        enqueue(std::move(msg), nullptr);
    }

    auto communication_module::message_types() const -> std::set<std::string> {
        std::set<std::string> types;

        for (const auto& i : handlers_) {
            types.emplace(std::string(i.first.begin(), i.first.end()));
        }

        return types;
    }

    auto communication_module::all_view_address() const -> void {
        for (const auto& [name, list] : contacts_)
            std::cerr << name << std::endl;
    }

    auto communication_module::addresses(const std::string& name) -> address_range_t {
        auto& list = contacts_.at(name);
        return std::make_pair(list.cbegin(), list.cend());
    }

    auto communication_module::self() const -> actor_address {
        return address();
    }

    auto communication_module::sub_type() const -> sub_type_t {
        return type_.sub_type_;
    }

    auto communication_module::type() const -> const std::string& {
        return type_.type_;
    }

    communication_module::~communication_module() = default;

    communication_module::communication_module(const std::string& name, sub_type_t type)
        : type_{0, type, name} {
        initialize();
    }

    actor_address communication_module::address() const noexcept {
        return actor_address{const_cast<communication_module*>(this)};
    }

    void communication_module::initialize() {
        add_handler(
            "add_link",
            &communication_module::add_link);

        add_handler(
            "remove_link",
            &communication_module::remove_link);
    }

    void communication_module::add_link(actor_address address) {
        if (address) {
            auto name = address->type();
            contacts_[name].emplace_back(std::move(address));
        } else {
            auto mes = "communication_module::add_link !address";
            error_sync_contacts(address->type(), mes);
        }
    }

    void communication_module::remove_link(const actor_address& address) {
        auto it = contacts_.find(address->type());
        if (it != contacts_.end()) {
            contacts_.erase(it);
        }
    }

    auto communication_module::broadcast(message_ptr msg) -> bool {
        auto tmp = std::move(msg);

        for (auto& [name, list] : contacts_) {
            for (auto& i : list) {
                i->enqueue(message_ptr(tmp->clone()));
            }
        }

        return true;
    }

    void communication_module::enqueue(message_ptr msg, executor::execution_device* e) {
        enqueue_base(std::move(msg), e);
    }

}} // namespace actor_zeta::base
