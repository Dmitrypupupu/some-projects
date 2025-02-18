#ifndef BALL_ICON_CPP_
#define BALL_ICON_CPP_
#include "ball_icon.hpp"

namespace widgets {

ball_icon::ball_icon(int radius) : m_radius(radius) {
}

int ball_icon::radius() const {
    return m_radius;
}

void ball_icon::radius(int new_radius) {
    m_radius = new_radius;
}

[[nodiscard]] int ball_icon::width() const {
    return 2 * m_radius + 1;
}

[[nodiscard]] int ball_icon::height() const {
    return 2 * m_radius + 1;
}

widget *ball_icon::child_at(int x, int y) {
    const int size = (x - width() / 2) * (x - width() / 2) +
                     (y - height() / 2) * (y - height() / 2);
    if (size <= m_radius * m_radius) {
        return this;
    }
    return nullptr;
}

std::unique_ptr<ball_icon> make_ball_icon(int radius) {
    return std::make_unique<ball_icon>(radius);
}

}  // namespace widgets
#endif