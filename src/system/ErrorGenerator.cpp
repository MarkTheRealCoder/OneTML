//
// Created by marco on 24/11/2024.
//

#include "ErrorGenerator.h"

#include <cstdarg>
#include <iostream>

#define VARIADIC_BUFFER_SIZE 1024

#define VARIADIC_ARGS(buffer, sv)       \
va_list args;                           \
va_start(args, sv);                     \
vsprintf(buffer, message, args);        \
va_end(args);


static std::string reasonToString(onetml::error::Reason reason) {
    std::string result;
    switch (reason) {
        case onetml::error::Reason::INFO:
            result = "[INFO]";
            break;
        case onetml::error::Reason::WARNING:
            result = "[WARNING]";
            break;
        case onetml::error::Reason::ERROR:
            result = "[ERROR]";
            break;
        case onetml::error::Reason::CONFIGURATIONS:
            result = "[CONFIGURATIONS]";
            break;
        case onetml::error::Reason::PATH:
            result = "[PATH]";
            break;
        case onetml::error::Reason::COMPONENT:
            result = "[COMPONENT]";
            break;
        case onetml::error::Reason::PARSER:
            result = "[PARSER]";
            break;
    }
    return result;
}

onetml::error::Error::Error(std::string message) : message(std::move(message)) {}

const char *onetml::error::Error::what() const noexcept {
    return message.c_str();
}

extern void raise(onetml::error::Reason reason, const char message[]) {
    throw onetml::error::Error(reasonToString(reason) + ": " + message);
}

extern void raiseFmt(onetml::error::Reason reason, const char message[], ...) {
    char buffer[VARIADIC_BUFFER_SIZE];
    VARIADIC_ARGS(buffer, message)
    throw onetml::error::Error(reasonToString(reason) + ": " + buffer);
}

extern void warn(onetml::error::Reason reason, const char message[]) {
    std::cerr << reasonToString(reason) << ": " << message << std::endl;
}

extern void warnFmt(onetml::error::Reason reason, const char message[], ...) {
    char buffer[VARIADIC_BUFFER_SIZE];
    VARIADIC_ARGS(buffer, message)
    std::cerr << reasonToString(reason) << ": " << buffer << std::endl;
}

extern void log(onetml::error::Reason reason, const char message[]) {
    std::cout << reasonToString(reason) << ": " << message << std::endl;
}

extern void logFmt(onetml::error::Reason reason, const char message[], ...) {
    char buffer[VARIADIC_BUFFER_SIZE];
    VARIADIC_ARGS(buffer, message)
    std::cout << reasonToString(reason) << ": " << buffer << std::endl;
}

extern void criticalFailure(onetml::error::Reason reason, const char message[]) {
    std::cerr << reasonToString(reason) << ": " << message << std::endl;
    exit(1);
}

extern void criticalFailureFmt(onetml::error::Reason reason, const char message[], ...) {
    char buffer[VARIADIC_BUFFER_SIZE];
    VARIADIC_ARGS(buffer, message)
    std::cerr << reasonToString(reason) << ": " << buffer << std::endl;
    exit(1);
}