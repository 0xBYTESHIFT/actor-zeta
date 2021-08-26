#include <actor-zeta/base/abstract_actor.hpp>
#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/base/address_t.hpp>
#include <actor-zeta/base/message.hpp>

namespace actor_zeta { namespace base {
    actor::~actor() = default;

    auto actor::address() const noexcept -> address_t {
        return ptr_->address();
    }

    auto actor::type() const -> const std::string& {
        return ptr_->type();
    }

    void actor::swap(actor& other) noexcept {
        using std::swap;
        ptr_.swap(other.ptr_);
    }

    actor::actor(std::nullptr_t)
        : ptr_(nullptr) {}

    actor& actor::operator=(std::nullptr_t) {
        ptr_.reset();
        return *this;
    }
}} // namespace actor_zeta::base
