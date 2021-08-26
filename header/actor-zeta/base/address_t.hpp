#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief A compact location expressor
    ///
    class address_t final {
    public:
        address_t() = default;

        address_t(address_t&&) = default;

        address_t(const address_t&) = default;

        explicit address_t(communication_module*);

        ~address_t();

        address_t& operator=(address_t&&) = default;

        address_t& operator=(const address_t&) = default;

        inline auto operator->() const noexcept -> communication_module* {
            return ptr_.get();
        }

        inline operator bool() const noexcept {
            return static_cast<bool>(ptr_);
        }

        inline auto operator!() const noexcept -> bool {
            return !ptr_;
        }

    private:
        intrusive_ptr<communication_module> ptr_;
    };

}} // namespace actor_zeta::base
