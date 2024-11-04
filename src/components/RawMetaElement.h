//
// Created by marco on 04/11/2024.
//

#ifndef ONETML_RAWMETAELEMENT_H
#define ONETML_RAWMETAELEMENT_H

#include <regex>
#include <string>
#include <ctime>

class RawMetaElement {

protected:
    RawMetaElement(const std::string title, const std::string element): title(title), element(element) {};

    enum class SupportedTypes {
        INTEGER,
        STRING,
        BOOLEAN, // Supported for simplicity: converts boolean to string
        DOUBLE,
        DATE,
        DATETIME,
        UNKNOWN
    };

    static SupportedTypes requestedType(const std::string &parsed_type);

    const std::string title;
    const std::string element;
    static const std::regex& LABELS();
    static const std::regex& VALUES();
    static const std::regex& CONDITION();

public:
    /**
     * @param label The label that indicates the element that must be replaced.
     * @param content The content that must be inserted in that place.
     *
     * @result If content type is matched with required type,
     * then the template modifies its element replacing all labels with the same type with the provided content.
     *
     */
    void inject(const std::string& label, int content);             // Serving INTEGER
    /**
     * @param label The label that indicates the element that must be replaced.
     * @param content The content that must be inserted in that place.
     *
     * @result If content type is matched with required type,
     * then the template modifies its element replacing all labels with the same type with the provided content.
     *
     */
    void inject(const std::string& label, std::string content);     // Serving STRING
    /**
     * @param label The label that indicates the element that must be replaced.
     * @param content The content that must be inserted in that place.
     *
     * @result If content type is matched with required type,
     * then the template modifies its element replacing all labels with the same type with the provided content.
     *
     */
    void inject(const std::string& label, bool content);            // Serving BOOLEAN
    /**
     * @param label The label that indicates the element that must be replaced.
     * @param content The content that must be inserted in that place.
     *
     * @result If content type is matched with required type,
     * then the template modifies its element replacing all labels with the same type with the provided content.
     *
     */
    void inject(const std::string& label, double content);          // Serving DOUBLE and FLOAT
    /**
     * @param label The label that indicates the element that must be replaced.
     * @param content The content that must be inserted in that place.
     *
     * @result If content type is matched with required type,
     * then the template modifies its element replacing all labels with the same type with the provided content.
     *
     */
    void inject(const std::string& label, time_t content);          // Serving DATE and DATETIME

    /**
     * @result Returns the string representation of the element.
     */
    std::string toString();

    /**
     * @param out The string where to replace the element.
     * @param t The element to replace.
     * @return The string with the replaced element.
     *
     */
    friend std::string operator<<(std::string &out, RawMetaElement t);
};


#endif //ONETML_RAWMETAELEMENT_H
