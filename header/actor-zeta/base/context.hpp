#pragma once

#include <actor-zeta/forwards.hpp>
#include <string_view>

namespace actor_zeta { namespace base {

    ///
    /// @brief
    ///

    struct context {
        virtual ~context() = default;

        virtual auto addresses(std::string_view) -> actor_address& = 0;

        virtual auto self() -> actor_address = 0;

        virtual auto current_message() -> message* = 0;
    };

}} // namespace actor_zeta::base
