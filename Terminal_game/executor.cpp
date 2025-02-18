#include <cmath>
#include <deque>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif
void process_forward(
    char orientation,
    int &coord_x,
    int &coord_y,
    std::set<std::pair<int, int>> &visited_cells
) {
    switch (orientation) {
        case '^':
            coord_y++;
            visited_cells.insert(std::make_pair(coord_x, coord_y));
            break;
        case 'v':
            coord_y--;
            visited_cells.insert(std::make_pair(coord_x, coord_y));
            break;
        case '<':
            coord_x--;
            visited_cells.insert(std::make_pair(coord_x, coord_y));
            break;
        case '>':
            coord_x++;
            visited_cells.insert(std::make_pair(coord_x, coord_y));
            break;
    }
}

void process_back(
    char orientation,
    int &coord_x,
    int &coord_y,
    std::set<std::pair<int, int>> &visited_cells
) {
    switch (orientation) {
        case '^':
            coord_y--;
            visited_cells.insert(std::make_pair(coord_x, coord_y));
            break;
        case 'v':
            coord_y++;
            visited_cells.insert(std::make_pair(coord_x, coord_y));
            break;
        case '<':
            coord_x++;
            visited_cells.insert(std::make_pair(coord_x, coord_y));
            break;
        case '>':
            coord_x--;
            visited_cells.insert(std::make_pair(coord_x, coord_y));
            break;
    }
}

void turn_left(char &orientation) {
    switch (orientation) {
        case '^':
            orientation = '<';
            break;
        case '>':
            orientation = '^';
            break;
        case 'v':
            orientation = '>';
            break;
        case '<':
            orientation = 'v';
            break;
    }
}

void turn_right(char &orientation) {
    switch (orientation) {
        case '^':
            orientation = '>';
            break;
        case '>':
            orientation = 'v';
            break;
        case 'v':
            orientation = '<';
            break;
        case '<':
            orientation = '^';
            break;
    }
}

void print_map(
    char orientation,
    int coord_x,
    int coord_y,
    const std::set<std::pair<int, int>> &visited_cells
) {
    if (visited_cells.empty()) {
        return;
    }
    int min_x = coord_x;
    int max_x = coord_x;
    int min_y = coord_y;
    int max_y = coord_y;
    for (const auto &cell : visited_cells) {
        min_x = std::min(min_x, cell.first);
        max_x = std::max(max_x, cell.first);
        min_y = std::min(min_y, cell.second);
        max_y = std::max(max_y, cell.second);
    }
    int width = max_x + abs(min_x) + 1;   // NOLINT all
    int height = max_y + abs(min_y) + 1;  // NOLINT all
    std::deque<std::deque<char>> map(height, std::deque<char>(width, '.'));
    for (const auto &cell : visited_cells) {
        map[cell.second - min_y][cell.first - min_x] = 'o';
    }
    map[coord_y - min_y][coord_x - min_x] = orientation;
    if (orientation == map[abs(min_y)][abs(min_x)]) {
        map[abs(min_y)][abs(min_x)] = orientation;
    } else {
        map[abs(min_y)][abs(min_x)] = '0';
    }
    for (int line_start = 0; line_start < width; line_start++) {
        std::cout << "  ";
    }
    std::cout << " " << std::endl;
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            std::cout << ' ' << map[i][j];
        }
        std::cout << ' ';
        std::cout << std::endl;
        if (i > 0) {
            for (int line_mid = 0; line_mid < width; line_mid++) {
                std::cout << "  ";
            }
            std::cout << " " << std::endl;
        }
    }
    for (int line_end = 0; line_end < width; line_end++) {
        std::cout << "  ";
    }
    std::cout << " " << std::endl;
}

int main() {  // NOLINT all
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
    const std::string quote_sherlock =
        "I had had so many reasons to believe in my friend's subtle powers of\n"
        "reasoning and extraordinary energy in action that I felt that he "
        "must\n"
        "have some solid grounds for the assured and easy demeanour with "
        "which\n"
        "he treated the singular mystery which he had been called upon to\n"
        "fathom. Once only had I known him to fail, in the case of the King "
        "of\n"
        "Bohemia and of the Irene Adler photograph; but when I looked back to\n"
        "the weird business of the Sign of Four, and the extraordinary\n"
        "circumstances connected with the Study in Scarlet, I felt that it "
        "would\n"
        "be a strange tangle indeed which he could not unravel.";
    const char *quote_catjeoffry = R"(For he is of the tribe of Tiger.
For the Cherub Cat is a term of the Angel Tiger.
For he has the subtlety and hissing of a serpent, which in goodness he suppresses.
For he will not do destruction, if he is well-fed, neither will he spit without provocation.
For he purrs in thankfulness, when God tells him he's a good Cat.
For he is an instrument for the children to learn benevolence upon.
For every house is incomplete without him and a blessing is lacking in the spirit.
For the Lord commanded Moses concerning the cats at the departure of the Children of Israel from Egypt.
For every family had one cat at least in the bag.
For the English Cats are the best in Europe.)";
    char orientation = '^';
    int coord_x = 0;
    int coord_y = 0;
    bool macro_recording = false;
    std::set<std::pair<int, int>> visited_cells;
    visited_cells.insert(std::make_pair(0, 0));
    std::vector<std::string> macro;
    std::string action;
    while (std::cin >> action) {  // Output
        if (action == "quit" ||
            action == "exit") {  // Completion of the program
            return 0;
        }
        if (action == "show-map") {  // map
            print_map(orientation, coord_x, coord_y, visited_cells);
        }
        if (action == "print-statistics" || action == "stats") {
            if (!macro_recording) {  // print stats
                std::cout << "Player " << orientation << " stands "
                          << abs(coord_x) << " away from OY, " << abs(coord_y)
                          << " away from OX. " << visited_cells.size()
                          << " cell(s) has been visited." << std::endl;
            }
        }
        if (action == "run-macro") {  // macro
            for (const std::string &cmd : macro) {
                switch (cmd[0]) {
                    case 'f':
                        process_forward(
                            orientation, coord_x, coord_y, visited_cells
                        );
                        break;
                    case 'b':
                        process_back(
                            orientation, coord_x, coord_y, visited_cells
                        );
                        break;
                    case 'l':
                        turn_left(orientation);
                        break;
                    case 'r':
                        turn_right(orientation);
                        break;
                }
                if (cmd == "turn-left" || cmd == "turn-right") {
                    switch (cmd[5]) {
                        case 'l':
                            turn_left(orientation);
                            break;
                        case 'r':
                            turn_right(orientation);
                            break;
                    }
                } else if (cmd == "print-statistics" || cmd == "stats") {
                    std::cout << "Player " << orientation << " stands "
                              << abs(coord_x) << " away from OY, "
                              << abs(coord_y) << " away from OX. "
                              << visited_cells.size()
                              << " cell(s) has been visited." << std::endl;
                }
            }
        }
        if (macro_recording) {  // Macro
            if (action == "end-macro") {
                macro_recording = false;
                std::cout << "New macro of " << macro.size() << " command(s)"
                          << std::endl;
            } else if (action == "forward" || action == "fwd" ||
                 action == "backward" || action == "bwd" ||
                 action == "turn-right" || action == "right" ||
                 action == "turn-left" || action == "left" ||
                 action == "print-statistics" || action == "stats") {
                macro.push_back(action);
                std::cout << "Recorded" << std::endl;
            } else {
                continue;
            }
        } else {
            if (action == "quit" ||
                action == "exit") {  // Completion of the program
                return 0;
            }
            if (action == "sherlock-holmes" ||
                action == "sherlock") {  // Quotes
                std::cout << quote_sherlock << std::endl;
            } else if (action == "cat" || action == "cat-jeoffry") {
                std::cout << quote_catjeoffry << std::endl;
            } else if (action == "forward" || action == "backward" ||
                 action == "fwd" || action == "bwd") { // Moving
                switch (action[0]) {
                    case 'f':
                        process_forward(
                            orientation, coord_x, coord_y, visited_cells
                        );
                        break;
                    case 'b':
                        process_back(
                            orientation, coord_x, coord_y, visited_cells
                        );
                        break;
                }
            } else if (action == "turn-left" || action == "left") {
                turn_left(orientation);
            } else if (action == "turn-right" || action == "right") {
                turn_right(orientation);
            } else if (action == "start-macro") {
                macro.clear();
                macro_recording = true;
            }
        }
    }
    return 0;
}