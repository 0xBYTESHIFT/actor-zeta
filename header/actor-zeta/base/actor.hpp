#pragma once

#include <actor-zeta/detail/intrusive_ptr.hpp>
#include <actor-zeta/detail/type_list.hpp>
#include <actor-zeta/forwards.hpp>
#include <string>

//smart actor
namespace actor_zeta { namespace base {
    ///
    /// @brief An Actor's entity container
    ///
    class actor final {
    public:
        actor() = default;

        actor(const actor& a) = delete;

        actor(actor&& a) = default;

        actor& operator=(const actor& a) = delete;

        actor& operator=(actor&& a) = default;

        actor(std::nullptr_t);

        actor& operator=(std::nullptr_t);

        template<
            class T,
            class = std::enable_if_t<std::is_base_of<abstract_actor, T>::value>>
        actor(intrusive_ptr<T> ptr)
            : ptr_(std::move(ptr)) {}

        template<
            class T,
            class = std::enable_if_t<std::is_base_of<abstract_actor, T>::value>>
        actor(T* ptr)
            : ptr_(ptr) {}

        template<
            class T,
            class = std::enable_if_t<std::is_base_of<abstract_actor, T>::value>>
        actor& operator=(intrusive_ptr<T> ptr) {
            actor tmp{std::move(ptr)};
            swap(tmp);
            return *this;
        }

        template<
            class T,
            class = std::enable_if_t<std::is_base_of<abstract_actor, T>::value>>
        actor& operator=(T* ptr) {
            actor tmp{ptr};
            swap(tmp);
            return *this;
        }

        auto address() const noexcept -> address_t;

        ~actor();

        inline auto operator->() const noexcept -> abstract_actor* {
            return ptr_.get();
        }

        inline explicit operator bool() const noexcept {
            return static_cast<bool>(ptr_);
        }

        [[nodiscard]] auto type() const -> const std::string&;

        inline auto operator!() const noexcept -> bool {
            return !ptr_;
        }

    private:
        void swap(actor&) noexcept;

        intrusive_ptr<abstract_actor> ptr_;
    };
}} // namespace actor_zeta::base
