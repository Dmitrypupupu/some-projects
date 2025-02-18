#ifndef BALL_ICON_HPP_
#define BALL_ICON_HPP_

#include "abstract_widgets.hpp"

namespace widgets {

struct ball_icon final : widget {
public:
    explicit ball_icon(int radius);

    [[nodiscard]] int radius() const;
    void radius(int new_radius);
    [[nodiscard]] int width() const override;
    [[nodiscard]] int height() const override;
    widget *child_at(int x, int y) override;

private:
    int m_radius;
};

[[nodiscard]] std::unique_ptr<ball_icon> make_ball_icon(int radius);

}  // namespace widgets

#endif  // BALL_ICON_HPP_