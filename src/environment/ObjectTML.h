//
// Created by marco on 27/11/2024.
//

#ifndef ONETML_OBJECTTML_H
#define ONETML_OBJECTTML_H

#include <cstdint>
#include <vector>
#include <map>
#include <memory>
#include "../system/utils.h"
#include "dynamic_types.h"

ONETML_NAMESPACE

struct DynamicType {
private:
    union {
        intTml *integer;
        uintTml *uinteger;
        floatTml *floating;
        boolTml *boolean;
        stringTml *string;
        void* complex = nullptr;
    } value;
    Type type = Type::EMPTY;
public:

    DynamicType() = default;

    template<typename T>
    requires type_checks::is_integer_v<T>
    DynamicType &operator=(const T& other) {
        this->remove_latest();
        this->type = Type::INTEGER;
        this->value.integer = new intTml(other);
        return *this;
    }

    template<typename T>
    requires type_checks::is_uinteger_v<T>
    DynamicType &operator=(const T& other) {
        this->remove_latest();
        this->type = Type::UINTEGER;
        this->value.uinteger = new uintTml(other);
        return *this;
    }

    template<typename T>
    requires type_checks::is_floating_v<T>
    DynamicType &operator=(const T& other) {
        this->remove_latest();
        this->type = Type::FLOATING;
        this->value.floating = new floatTml(other);
        return *this;
    }

    template<typename T>
    requires type_checks::is_boolean_v<T>
    DynamicType &operator=(const T& other) {
        this->remove_latest();
        this->type = Type::BOOLEAN;
        this->value.boolean = new boolTml(other);
        return *this;
    }

    template<typename T>
    requires type_checks::is_key_string<T> || type_checks::is_string<T>
    DynamicType &operator=(const T& other) {
        this->remove_latest();
        this->type = Type::STRING;
        std::wstring _buff;
        if (type_checks::is_key_string<T>) {
            std::array<wchar_t, other.size() + 1> buffer;
            std::mbstowcs(buffer.data(), other.c_str(), other.size());
            _buff = std::wstring(buffer.data());
        } else {
            _buff = std::wstring(other);
        }

        this->value.string = new std::wstring(_buff);
        return *this;
    }

    template<typename T>
    DynamicType &operator=(const T &other) {
        static_assert(false, "Type not supported");
        return *this;
    }

    template<typename T, Type TM = type_checks::type_match<T>>
    operator T() const {
        if constexpr (TM == Type::INTEGER) {
            return (T)*this->value.integer;
        } else if constexpr (TM == Type::UINTEGER) {
            return (T)*this->value.uinteger;
        } else if constexpr (TM == Type::FLOATING) {
            return (T)*this->value.floating;
        } else if constexpr (TM == Type::BOOLEAN) {
            return (T)*this->value.boolean;
        } else if constexpr (TM == Type::STRING) {
            return (T)*this->value.string;
        } else {
            static_assert(false, "Type not supported");
        }
    }

    void remove_latest();

    ~DynamicType() {
        this->remove_latest();
    };
};


ONETML_END_NAMESPACE


#endif //ONETML_OBJECTTML_H
