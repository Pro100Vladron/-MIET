#ifndef TYPE_MAP_HPP
#define TYPE_MAP_HPP

#include <array>
#include <tuple>
#include <utility>

namespace detail
{
    template<class T, class Tuple>
    struct type_to_index;

    template<class T, class... Ts>
    struct type_to_index<T, std::tuple<T, Ts...>>
    {
        constexpr static size_t v = 0;
    };

    template<class T, class U, class... Ts>
    struct type_to_index<T, std::tuple<U, Ts...>>
    {
        constexpr static size_t v = 1 + type_to_index<T, std::tuple<Ts...>>::v;
    };
}

template<class ValueType, class... Types>
class type_map
{
private:
    using TypesTuple = std::tuple<Types...>;
    std::array<ValueType, sizeof...(Types)> values_;

public:
    template<typename... Args>
    explicit type_map(Args&&... args) : values_{std::forward<Args>(args)...} {}

    template<class T>
    decltype(auto) as()
    {
        constexpr size_t index = detail::type_to_index<T, TypesTuple>::v;
        return values_[index];
    }

    template<class T>
    decltype(auto) as() const
    {
        constexpr size_t index = detail::type_to_index<T, TypesTuple>::v;
        return values_[index];
    }
};

namespace std
{
    template<typename T, class ValueType, class... Types>
    decltype(auto) get(type_map<ValueType, Types...>& tm)
    {
        return tm.template as<T>();
    }

    template<typename T, class ValueType, class... Types>
    decltype(auto) get(const type_map<ValueType, Types...>& tm)
    {
        return tm.template as<T>();
    }
}

#endif // TYPE_MAP_HPP