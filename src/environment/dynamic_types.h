//
// Created by marco on 01/12/2024.
//

#ifndef ONETML_DYNAMIC_TYPES_H
#define ONETML_DYNAMIC_TYPES_H

#include <cstdint>
#include "../system/utils.h"

ONETML_NAMESPACE

enum class Type {
    EMPTY,
    OBJECT,
    ARRAY,
    INTEGER,
    UINTEGER,
    FLOATING,
    BOOLEAN,
    STRING,
    KEYSTRING
};

using intTml = int64_t;
using uintTml = uint64_t;
using floatTml = long double;
using boolTml = bool;
using stringTml = std::wstring;
using keyStringTml = std::string;

namespace type_utils {

    template<typename T>
    struct rem_cv {
        using type = std::remove_cv_t<T>;
    };

    template<typename T>
    struct rem_cv<T *> {
        using type = typename rem_cv<std::remove_cv_t<T>>::type *;
    };

    template<typename T, size_t N>
    struct rem_cv<T[N]> {
        using type = typename rem_cv<std::remove_cv_t<T>>::type[N];
    };


    template<typename T>
    struct rem_cv<T[]> {
        using type = typename rem_cv<std::remove_cv_t<T>>::type[];
    };

    template<typename T>
    using rem_cv_t = typename rem_cv<T>::type;


    // Compare types
    template<typename, typename>
    struct is_same : std::false_type {};

    template<typename T>
    struct is_same<T, T> : std::true_type {};

    template <typename F, typename S>
    inline constexpr bool is_same_v = is_same<F, S>::value;

    template <typename T>
    struct rem_defdecl {
        using type = T;
    };

    template <typename T>
    struct rem_defdecl<T&> {
        using type = T;
    };

    template <typename T>
    struct rem_defdecl<T&&> {
        using type = T;
    };

    template <typename T>
    struct rem_defdecl<T const> {
        using type = T;
    };

    template <typename T>
    using rem_defdecl_t = typename rem_defdecl<T>::type;
};

namespace type_checks {

    template <typename T>
    struct is_integer {
        static constexpr bool value =
                !std::is_unsigned_v<T> &&
                !type_utils::is_same_v<wchar_t, T> &&
                !std::is_floating_point_v<T> &&
                sizeof(T) >= 2;
    };

    template <typename T>
    inline static constexpr bool is_integer_v = is_integer<type_utils::rem_defdecl_t<T>>::value;

    template <typename T>
    struct is_uinteger {
        static constexpr bool value =
                !type_utils::is_same_v<wchar_t, T> &&
                !std::is_floating_point_v<T> &&
                std::is_unsigned_v<T> &&
                sizeof(T) >= 2;
    };

    template <typename T>
    inline static constexpr bool is_uinteger_v = is_uinteger<type_utils::rem_defdecl_t<T>>::value;

    template <typename T>
    struct is_floating {
        static constexpr bool value = std::is_floating_point_v<T>;
    };

    template <typename T>
    inline static constexpr bool is_floating_v = is_floating<type_utils::rem_defdecl_t<T>>::value;

    template <typename T>
    struct is_boolean {
        static constexpr bool value = type_utils::is_same_v<bool, T>;
    };

    template <typename T>
    inline static constexpr bool is_boolean_v = is_boolean<type_utils::rem_defdecl_t<T>>::value;

    template<bool isWide, typename T>
    struct is_any_string {
        using R = type_utils::rem_cv_t<typename std::decay<T>::type>;
        static constexpr bool value =
                type_utils::is_same_v<typename std::conditional<isWide, wchar_t *, char *>::type, R> ||
                type_utils::is_same_v<typename std::conditional<isWide, stringTml, keyStringTml>::type, R>;
    };

    template<bool isWide, typename T>
    inline static constexpr bool is_string_v = is_any_string<isWide, T>::value;

    template <typename T>
    inline constexpr bool is_key_string = is_string_v<std::false_type::value, T>;

    template <typename T>
    inline constexpr bool is_string = is_string_v<std::true_type::value, T>;

    template <typename T>
    inline constexpr bool is_array = std::false_type::value;
    template <typename T>
    inline constexpr bool is_array<T[]> = std::true_type::value;
    template <typename T, size_t N>
    inline constexpr bool is_array<T[N]> = std::true_type::value;
    template <typename T, size_t N>
    inline constexpr bool is_array<std::array<T, N>> = std::true_type::value;

    template <typename T>
    struct raw_type_match {
        const static Type value = (is_integer_v<T> ? Type::INTEGER :
                                   (is_uinteger_v<T> ? Type::UINTEGER :
                                   (is_floating_v<T> ? Type::FLOATING :
                                   (is_boolean_v<T> ? Type::BOOLEAN :
                                   (is_key_string<T> ? Type::KEYSTRING :
                                   (is_string<T> ? Type::STRING : Type::EMPTY))))));

    };

    template <typename T>
    inline constexpr Type type_match = raw_type_match<T>::value;

};

ONETML_END_NAMESPACE

#endif //ONETML_DYNAMIC_TYPES_H
