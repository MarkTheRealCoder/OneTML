//
// Created by marco on 27/11/2024.
//

#include "ObjectTML.h"

ONETML_NAMESPACE

void DynamicType::remove_latest() {
    switch (this->type) {
        case Type::INTEGER:
            delete this->value.integer;
            break;
        case Type::UINTEGER:
            delete this->value.uinteger;
            break;
        case Type::FLOATING:
            delete this->value.floating;
            break;
        case Type::BOOLEAN:
            delete this->value.boolean;
            break;
        case Type::STRING:
            delete this->value.string;
            break;
        default:
            break;
    }
    this->value.complex = nullptr;
}

ONETML_END_NAMESPACE