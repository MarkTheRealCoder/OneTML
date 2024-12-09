//
// Created by marco on 24/11/2024.
//

#ifndef ONETML_ERRORGENERATOR_H
#define ONETML_ERRORGENERATOR_H

#include <string>
#include "utils.h"

ONETML_NAMESPACE
namespace error {

    enum class Reason {
        INFO,
        WARNING,
        ERROR,
        CONFIGURATIONS,
        PATH,
        COMPONENT,
        PARSER
    };

    class Error: public std::exception {
    private:
        std::string message;
    public:
        Error(std::string  message);
        [[nodiscard]] const char *what() const noexcept override;

    };

    extern void raise(Reason reason, const char message[]);
    extern void raiseFmt(Reason reason, const char message[], ...);

    extern void warn(Reason reason, const char message[]);
    extern void warnFmt(Reason reason, const char message[], ...);

    extern void log(Reason reason, const char message[]);
    extern void logFmt(Reason reason, const char message[], ...);

    extern void criticalFailure(Reason reason, const char message[]);
    extern void criticalFailureFmt(Reason reason, const char message[], ...);
} // egen

ONETML_END_NAMESPACE

#endif //ONETML_ERRORGENERATOR_H
