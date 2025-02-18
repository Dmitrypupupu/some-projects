#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace lab_bigint {

class bigint {
private:
    std::vector<int> digits;

    std::vector<int> static convert_to_digits(const std::string &number_string
    ) {
        std::vector<int> result;
        bool zeros = true;
        for (const char digit : number_string) {
            int number = digit - '0';  // NOLINT all
            if (zeros && number == 0) {
                continue;
            }
            zeros = false;
            result.push_back(number);
        }
        if (result.empty()) {
            result.push_back(0);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    [[nodiscard]] bigint convertdigits() const {
        bigint result;
        result.digits = digits;
        return result;
    }

public:
    // static const int BASE = 10;

    bigint() : digits{0} {  // Конструкторы
    }

    // cppcheck-suppress noExplicitConstructor
    bigint(const std::string &number_string) {
        if (number_string.empty()) {
            digits = {0};
        } else {
            digits = convert_to_digits(number_string);
        }
    }

    // cppcheck-suppress noExplicitConstructor
    bigint(unsigned int number) {
        const std::string number_string = std::to_string(number);
        digits = convert_to_digits(number_string);
    }

    [[nodiscard]] std::string to_string(
    ) const {  // Оператор преобразования числа в строку
        std::string result;
        for (std::vector<int>::size_type i = digits.size() - 1;
             i != static_cast<std::vector<int>::size_type>(-1); --i) {
            result += std::to_string(digits[i]);
        }
        return result;
    }

    explicit operator unsigned int(
    ) const {  // Оператор явного преобразования в uint
        unsigned int result = 0;
        for (std::vector<int>::size_type i = digits.size() - 1;
             i != static_cast<std::vector<int>::size_type>(-1); --i) {
            result = result * BASE + digits[i];
        }
        return result;
    }

    friend bool
    operator==(const bigint &lhs, const bigint &rhs) {  // Операторы сравнения
        return lhs.digits == rhs.digits;
    }

    friend bool operator!=(const bigint &lhs, const bigint &rhs) {
        return lhs.digits != rhs.digits;
    }

    friend bool operator>(const bigint &lhs, const bigint &rhs) {
        if (lhs.digits.size() != rhs.digits.size()) {
            return lhs.digits.size() > rhs.digits.size();
        }
        for (std::vector<int>::size_type i = lhs.digits.size() - 1;
             i != static_cast<std::vector<int>::size_type>(-1); --i) {
            if (lhs.digits[i] != rhs.digits[i]) {
                return lhs.digits[i] > rhs.digits[i];
            }
        }
        return false;
    }

    friend bool operator>=(const bigint &lhs, const bigint &rhs) {
        return lhs > rhs || lhs == rhs;
    }

    friend bool operator<(const bigint &lhs, const bigint &rhs) {
        return !(lhs >= rhs);
    }

    friend bool operator<=(const bigint &lhs, const bigint &rhs) {
        return !(lhs > rhs);
    }

    friend std::ostream &
    operator<<(std::ostream &os, const bigint &num) {  // Оператор вывода
        os << num.to_string();
        return os;
    }

    friend std::istream &
    operator>>(std::istream &is, bigint &num) {  // Оператор ввода из строки
        std::string input;
        is >> input;
        num = bigint(input);
        return is;
    }

    friend bigint operator+(const bigint &lhs, const bigint &rhs) {  // Оператор
                                                                     // плюс
        bigint a_copy = lhs.convertdigits();
        bigint b_copy = rhs.convertdigits();
        if (lhs.digits.size() > rhs.digits.size()) {
            while (a_copy.digits.size() != b_copy.digits.size()) {
                b_copy.digits.push_back(0);
            }
        } else if (a_copy.digits.size() < b_copy.digits.size()) {
            while (a_copy.digits.size() != b_copy.digits.size()) {
                a_copy.digits.push_back(0);
            }
        }
        bigint sum;
        std::vector<int> &resultdigits = sum.digits;
        resultdigits.pop_back();
        int buf = 0;
        for (std::vector<int>::size_type i = 0; i < a_copy.digits.size(); ++i) {
            int digit_sum = a_copy.digits[i] + b_copy.digits[i] + buf;
            buf = 0;
            if (digit_sum >= 10) {
                buf = 1;
                digit_sum -= 10;
            }
            resultdigits.push_back(digit_sum);
        }
        if (buf > 0) {
            resultdigits.push_back(buf);
        }
        return sum;
    }

    bigint &operator+=(const bigint &other) {
        *this = *this + other;
        return *this;
    }

    bigint &operator++() {
        *this = *this + 1;
        return *this;
    }

    bigint operator++(int) {
        bigint buff = *this;
        *this += 1;
        return buff;
    }

    friend bigint
    operator-(const bigint &lhs, const bigint &rhs) {  // Оператор минус
        bigint a_copy = lhs.convertdigits();
        bigint b_copy = rhs.convertdigits();
        while (a_copy.digits.size() < b_copy.digits.size()) {
            a_copy.digits.push_back(0);
        }
        bigint difference;
        std::vector<int> &resultdigits = difference.digits;
        resultdigits.pop_back();
        int buff = 0;
        for (std::vector<int>::size_type i = 0; i < a_copy.digits.size(); ++i) {
            int digit_difference = a_copy.digits[i] - buff;
            if (i < b_copy.digits.size()) {
                digit_difference -= b_copy.digits[i];
            }
            if (digit_difference < 0) {
                digit_difference += BASE;
                buff = 1;
            } else {
                buff = 0;
            }
            resultdigits.push_back(digit_difference);
        }
        while (resultdigits.size() > 1 && resultdigits.back() == 0) {
            resultdigits.pop_back();
        }
        return difference;
    }

    bigint &operator-=(const bigint &other) {
        *this = *this - other;
        return *this;
    }

    bigint &operator--() {
        *this = *this - 1;
        return *this;
    }

    bigint operator--(int) {
        bigint buff = *this;
        *this -= 1;
        return buff;
    }
};
}  // namespace lab_bigint