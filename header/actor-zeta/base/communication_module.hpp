#pragma once

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include <actor-zeta/base/metadata.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;

    class communication_module : public ref_counted {
    public:
        using key_type = std::string;
        using storage = std::unordered_map<key_type, std::unique_ptr<handler>>;
        using storage_contact_t = std::list<actor_address>;
        using contacts_t = std::unordered_map<key_type, storage_contact_t>;
        using contacts_iterator_t = storage_contact_t::iterator;
        using range_t = std::pair<contacts_iterator_t, contacts_iterator_t>;
        using address_range_t = std::pair<storage_contact_t::const_iterator, storage_contact_t::const_iterator>;

        communication_module() = delete;

        communication_module(const communication_module&) = delete;

        communication_module& operator=(const communication_module&) = delete;

        ~communication_module() override;

        auto address() const noexcept -> actor_address;

        auto sub_type() const -> sub_type_t;

        auto type() const -> const std::string&;

        auto message_types() const -> std::set<std::string>;

        auto enqueue(message_ptr) -> void;

        void enqueue(message_ptr, executor::execution_device*);

        auto broadcast(message_ptr) -> bool;

        virtual auto current_message() -> message* = 0;

    protected:
        communication_module(const std::string&, sub_type_t);

        virtual void enqueue_base(message_ptr, executor::execution_device*) = 0;

        auto addresses(const std::string&) -> address_range_t;

        auto self() const -> actor_address;

        template<class F>
        auto add_handler(const std::string& name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(const std::string& name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        void execute();

        bool on(const std::string&, handler*);

        /**
           * debug method
           */
        auto all_view_address() const -> void;

    private:
        void add_link(actor_address);

        void remove_link(const actor_address&);

        void initialize();

        contacts_t contacts_;
        storage handlers_;
        metadata type_;
    };
}} // namespace actor_zeta::base
