#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP
#include <utility>

namespace ptrs::unique {
template <typename T>
struct default_deleter {
    void operator()(T *ptr) const {
        delete ptr;
    }
};

template <typename T, typename Deleter = default_deleter<T>>
struct unique_ptr {
private:
    T *ptr;
    Deleter deleter;

public:
    unique_ptr(const unique_ptr &) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;

    unique_ptr() : ptr(nullptr) {
    }

    explicit unique_ptr(std::nullptr_t) : ptr(nullptr) {
    }

    explicit unique_ptr(T *p) : ptr(p) {
    }

    explicit unique_ptr(T *p, const Deleter &d) : ptr(p), deleter(d) {
    }

    explicit unique_ptr(T *p, Deleter &&d) : ptr(p), deleter(std::move(d)) {
    }

    unique_ptr(unique_ptr &&other)
        : ptr(other.release()), deleter(std::move(other.deleter)) {
    }

    ~unique_ptr() {
        reset();
    }

    friend void swap(unique_ptr &lhs, unique_ptr &rhs) {
        std::swap(lhs.ptr, rhs.ptr);
        std::swap(lhs.deleter, rhs.deleter);
    }

    unique_ptr &operator=(unique_ptr &&other) {
        if (this != &other) {
            if (other.ptr) {
                reset(other.release());
            } else {
                reset();
            }
            deleter = std::move(other.deleter);
        }
        return *this;
    }

    [[nodiscard]] T *release() {
        return std::exchange(ptr, nullptr);
    }

    [[nodiscard]] T *get() const {
        return ptr;
    }

    void reset(T *p = nullptr) {
        if (ptr) {
            deleter(ptr);
        }
        ptr = p;
    }

    [[nodiscard]] bool operator==(const unique_ptr &rhs) const {
        return ptr == rhs.ptr;
    }

    [[nodiscard]] bool operator!=(const unique_ptr &rhs) const {
        return ptr != rhs.ptr;
    }

    [[nodiscard]] T &operator*() const {
        return *ptr;
    }

    [[nodiscard]] T *operator->() const {
        return ptr;
    }

    [[nodiscard]] explicit operator bool() const {
        return ptr != nullptr;
    }
};
}  // namespace ptrs::unique
#endif  // UNIQUE_PTR_HPP