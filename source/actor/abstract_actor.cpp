#include <iostream>

#include <actor-zeta/base/abstract_actor.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/impl/handler.ipp>

namespace actor_zeta { namespace base {

    abstract_actor::~abstract_actor() = default;

    abstract_actor::abstract_actor(const std::string& type)
        : communication_module(type, sub_type_t::actor) {
    }

}} // namespace actor_zeta::base
