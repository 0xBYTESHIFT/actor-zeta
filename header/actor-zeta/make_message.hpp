#pragma once

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta {

    using base::address_t;
    using base::message;
    using base::message_ptr;

    template<class T>
    auto make_message_ptr(address_t sender_, T name) -> message* {
        return new message(std::move(sender_), std::forward<T>(name));
    }

    template<class T, typename Arg>
    auto make_message_ptr(address_t sender_, T name, Arg&& arg) -> message* {
        auto any = std::any(std::forward<std::decay_t<Arg>>(arg));
        return new message(std::move(sender_), std::forward<T>(name), std::move(any));
    }

    template<class T, typename... Args>
    auto make_message_ptr(address_t sender_, T name, Args&&... args) -> message* {
        auto any = std::any(std::tuple<std::decay_t<Args>...>{std::forward<Args>(args)...});
        return new message(sender_, std::forward<T>(name), std::move(any));
    }

    template<class T>
    auto make_message(address_t sender_, T name) -> message_ptr {
        return message_ptr(new message(std::move(sender_), std::forward<T>(name)));
    }

    template<class T, typename Arg>
    auto make_message(address_t sender_, T name, Arg&& arg) -> message_ptr {
        auto any = std::any(std::forward<std::decay_t<Arg>>(arg));
        return message_ptr(new message(std::move(sender_), std::forward<T>(name), std::move(any)));
    }

    template<class T, typename... Args>
    auto make_message(address_t sender_, T name, Args&&... args) -> message_ptr {
        auto any = std::any(std::tuple<std::decay_t<Args>...>{std::forward<Args>(args)...});
        return message_ptr(new message(sender_, std::forward<T>(name), std::move(any)));
    }

} // namespace actor_zeta
