#include <actor-zeta/base/address_t.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/supervisor.hpp>

namespace actor_zeta { namespace base {

    supervisor_t::supervisor_t(std::string name)
        : communication_module(name, sub_type_t::supervisor) {}

    supervisor_t::~supervisor_t() {}

    auto supervisor_t::current_message() -> message* {
        return current_message_;
    }

    auto supervisor_t::set_current_message(message_ptr msg) -> void {
        current_message_ = msg.release();
    }

}} // namespace actor_zeta::base
