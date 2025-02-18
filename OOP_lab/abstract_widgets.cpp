#include "abstract_widgets.hpp"
#include <utility>

namespace widgets {

int widget::width() const {
    return 0;
}

[[nodiscard]] int widget::height() const {
    return 0;
}

widget *widget::child_at(int x, int y) {
    if (x >= 0 && y >= 0 && this->width() > x && this->height() > y) {
        return this;
    }
    return nullptr;
}
}  // namespace widgets