#pragma once

#include <stdexcept>
#include <string>
#include "../ast/ASTNode.hpp" // For SourceLocation

namespace dli {

class RuntimeError : public std::runtime_error {
public:
    SourceLocation loc;

    RuntimeError(const SourceLocation& location, const std::string& message)
        : std::runtime_error(message), loc(location) {}
};

} // namespace dli

