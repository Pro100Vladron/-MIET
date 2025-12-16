
#ifndef IOMANIP_HPP
#define IOMANIP_HPP

#include <iostream>
#include <cmath>
#include <type_traits>
#include <string>

// 1. endm
inline std::ostream& endm(std::ostream& os) {
    return os << "[eol]\n";
}

// 2. squares
struct squares_wrapper {};
inline squares_wrapper squares;

struct squares_stream {
    std::ostream& os;
};

inline squares_stream operator<<(std::ostream& os, const squares_wrapper&) {
    return {os};
}

template <typename T>
std::ostream& operator<<(squares_stream s, const T& value) {
    s.os << "[" << value << "]";
    return s.os;
}

// 3. add - ПРОСТАЯ И РАБОЧАЯ ВЕРСИЯ
struct add_wrapper {};
inline add_wrapper add;

struct add_stream {
    std::ostream& os;
};

inline add_stream operator<<(std::ostream& os, const add_wrapper&) {
    return {os};
}

template<typename T>
class add_operator {
public:
    add_operator(std::ostream& os, const T& first) : os_(os), first_(first) {}
    
    template<typename U>
    std::ostream& operator<<(const U& second) const {
        // Для арифметических типов - сложение
        if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
            os_ << (first_ + second);
        } 
        // Для строк - конкатенация
        else {
            os_ << std::string(first_) + std::string(second);
        }
        return os_;
    }
    
private:
    std::ostream& os_;
    T first_;
};

// Вспомогательные функции для конвертации в string
template<typename T>
std::string to_string_impl(const T& value) {
    if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(value);
    } else {
        return std::string(value);
    }
}

// Специализация для std::string
template<>
std::string to_string_impl<std::string>(const std::string& value) {
    return value;
}

template<typename T>
add_operator<T> operator<<(add_stream s, const T& first) {
    return add_operator<T>(s.os, first);
}

// 4. cos
struct cos_wrapper {};
inline cos_wrapper cos_manip;

struct cos_stream {
    std::ostream& os;
};

inline cos_stream operator<<(std::ostream& os, const cos_wrapper&) {
    return {os};
}

template <typename T>
std::ostream& operator<<(cos_stream s, const T& value) {
    if constexpr (std::is_arithmetic_v<T>) {
        s.os << std::cos(static_cast<double>(value));
    } else {
        s.os << "cos(" << value << ")";
    }
    return s.os;
}

// 5. ftp
struct ftp_wrapper {};
inline ftp_wrapper ftp;

struct ftp_stream {
    std::ostream& os;
};

inline ftp_stream operator<<(std::ostream& os, const ftp_wrapper&) {
    return {os};
}

template <typename T>
std::ostream& operator<<(ftp_stream s, const T& site) {
    s.os << "ftp://" << site;
    return s.os;
}

#endif // IOMANIP_HPP
