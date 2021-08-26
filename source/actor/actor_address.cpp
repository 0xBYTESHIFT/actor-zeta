#include <actor-zeta/base/address_t.hpp>

namespace actor_zeta { namespace base {

    address_t::address_t(communication_module* aa)
        : ptr_(aa) {}

    address_t::~address_t() = default;

}} // namespace actor_zeta::base
