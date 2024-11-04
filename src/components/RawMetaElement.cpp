//
// Created by marco on 04/11/2024.
//

#include "RawMetaElement.h"

using namespace std;

const regex& RawMetaElement::LABELS() {
    static const regex labels( R"(\<\s*\bRawMetaElement\b\s+([A-Za-z0-9_\-]+)\s*\>\s*(.*)\s*\<\/RawMetaElement\>)", regex::multiline);
    return labels;
}

const regex& RawMetaElement::VALUES() {
    static const regex values( R"({{\s+([A-Za-z0-9_\-]+):([a-z]+)\s+}})", regex::multiline);
    return values;
}

const regex& RawMetaElement::CONDITION() {
    static const regex values( R"({{\s+([A-Za-z0-9_\-]+):([a-z]+)\s+}})", regex::multiline);
    return values;
}

void RawMetaElement::inject(const std::string &label, const time_t content) {

}

void RawMetaElement::inject(const std::string &label, const double content) {

}

void RawMetaElement::inject(const std::string &label, const bool content) {

}

void RawMetaElement::inject(const std::string &label, const std::string content) {

}

void RawMetaElement::inject(const std::string &label, const int content) {

}

std::string RawMetaElement::toString() {
    return this->element;
}

std::string operator<<(std::string &out, RawMetaElement t) {
    out += t.toString();
    return out;
}

RawMetaElement::SupportedTypes RawMetaElement::requestedType(const string &parsed_type)  {

    static map<string, SupportedTypes> types = {
            {"int", SupportedTypes::INTEGER}, {"integer", SupportedTypes::INTEGER},
            {"str", SupportedTypes::STRING}, {"string", SupportedTypes::STRING},
            {"bool", SupportedTypes::BOOLEAN}, {"boolean", SupportedTypes::BOOLEAN},
            {"float", SupportedTypes::DOUBLE}, {"double", SupportedTypes::DOUBLE},
            {"date", SupportedTypes::DATE},
            {"datetime", SupportedTypes::DATETIME}
    };

    if (auto pair = types.find(parsed_type); pair == types.end()) return pair->second;

    return SupportedTypes::UNKNOWN;
}
