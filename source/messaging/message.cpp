#include <utility>

#include <actor-zeta/base/address_t.hpp>
#include <actor-zeta/base/message.hpp>

namespace actor_zeta { namespace base {

    auto message::command() const noexcept -> const std::string& {
        return command_;
    }

    auto message::clone() const -> message* {
        return new message(sender_, command_, body_);
    }

    message::operator bool() {
        return !command_.empty() || bool(sender_) || body_.has_value();
    }

    message::message(base::address_t sender, std::string name)
        : sender_(std::move(sender))
        , command_(std::move(name))
        , body_() {}

    message::message(base::address_t sender, std::string name, std::any body)
        : sender_(std::move(sender))
        , command_(std::move(name))
        , body_(std::move(body)) {}

    auto message::sender() const -> base::address_t {
        return sender_;
    }

    void message::swap(message& other) noexcept {
        using std::swap;
        swap(sender_, other.sender_);
        swap(command_, other.command_);
        swap(body_, other.body_);
    }

    message::message()
        : next(nullptr)
        , prev(nullptr) {}

    bool message::is_high_priority() const {
        return false;
    }

    auto message::body() -> std::any& {
        assert(body_.has_value());
        return body_;
    }
}} // namespace actor_zeta::base
