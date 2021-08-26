#pragma once

#include <string_view>

namespace actor_zeta {

    using actor_id = std::size_t;

    enum class sub_type_t : uint8_t {
        non = 0x00,
        actor,
        supervisor
    };

    struct metadata final {
        actor_id id_;
        sub_type_t sub_type_;
        std::string_view type_;
    };

} // namespace actor_zeta
