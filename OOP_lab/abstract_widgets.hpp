#ifndef ABSTRACT_WIDGETS_HPP_
#define ABSTRACT_WIDGETS_HPP_

#include <memory>
#include <string>

namespace widgets {

struct widget {  // NOLINT all
    [[nodiscard]] virtual int width() const = 0;
    [[nodiscard]] virtual int height() const = 0;
    virtual widget *child_at(int x, int y);
    widget() = default;
    widget(const widget &) = delete;
    widget(widget &&) = delete;

    virtual ~widget() = default;
};

}  // namespace widgets

#endif  // ABSTRACT_WIDGETS_HPP_