#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP
#include <utility>

namespace ptrs::shared {
template <typename T>
struct shared_ptr {
private:
    T *data_ptr = nullptr;
    std::size_t *counter = nullptr;

public:
    shared_ptr() = default;

    explicit shared_ptr(T *ptr)
        : data_ptr(ptr),
          counter(  // NOLINT
                    // [modernize-use-default-member-init,-warnings-as-errors]
              nullptr
          ) {
        if (data_ptr != nullptr) {
            counter = new std::size_t(1);
        }
    }

    shared_ptr(const shared_ptr &other)
        // cppcheck-suppress copyCtorPointerCopying
        : data_ptr(other.data_ptr), counter(other.counter) {
        if (data_ptr != nullptr) {
            (*counter)++;
        }
    }

    shared_ptr(shared_ptr &&other)
        : data_ptr(std::exchange(other.data_ptr, nullptr)),
          counter(std::exchange(other.counter, nullptr)) {
    }

    ~shared_ptr() {
        reset();
    }

    shared_ptr &operator=(const shared_ptr &other) {
        if (this != &other) {
            reset();
            data_ptr = other.data_ptr;
            if (data_ptr != nullptr) {
                counter = other.counter;
                (*counter)++;
            } else {
                counter = nullptr;
            }
        }
        return *this;
    }

    shared_ptr &operator=(shared_ptr &&other) {
        if (this != &other) {
            reset();
            data_ptr = other.data_ptr;
            counter = other.counter;
            other.data_ptr = nullptr;
            other.counter = nullptr;
        }
        return *this;
    }

    void reset(T *ptr = nullptr) {
        if (counter != nullptr) {
            if (--(*counter) == 0) {
                delete data_ptr;
                delete counter;
            }
        }
        data_ptr = ptr;
        if (ptr != nullptr) {
            counter = new std::size_t(1);
        } else {
            counter = nullptr;
        }
    }

    [[nodiscard]] T *get() const {
        return data_ptr;
    }

    [[nodiscard]] T &operator*() const {
        return *data_ptr;
    }

    [[nodiscard]] T *operator->() const {
        return data_ptr;
    }

    [[nodiscard]] explicit operator bool() const {
        return (data_ptr != nullptr);
    }

    [[nodiscard]] bool operator==(const shared_ptr &rhs) const {
        return data_ptr == rhs.data_ptr;
    }

    [[nodiscard]] bool operator!=(const shared_ptr &rhs) const {
        return data_ptr != rhs.data_ptr;
    }

    friend void swap(shared_ptr &lhs, shared_ptr &rhs) {
        std::swap(lhs.data_ptr, rhs.data_ptr);
        std::swap(lhs.counter, rhs.counter);
    }
};
}  // namespace ptrs::shared
#endif  // SHARED_PTR_HPP