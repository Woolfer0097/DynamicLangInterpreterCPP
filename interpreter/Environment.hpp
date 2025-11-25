#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "Value.hpp"
#include "RuntimeError.hpp"

namespace dli {

class Environment {
    std::unordered_map<std::string, std::shared_ptr<Value>> values;
    std::shared_ptr<Environment> enclosing;

public:
    Environment() : enclosing(nullptr) {}
    explicit Environment(std::shared_ptr<Environment> enclosing) : enclosing(std::move(enclosing)) {}

    void define(const std::string& name, std::shared_ptr<Value> value) {
        values[name] = std::move(value);
    }

    void assign(const std::string& name, std::shared_ptr<Value> value, const SourceLocation& loc) {
        if (values.count(name)) {
            values[name] = std::move(value);
            return;
        }

        if (enclosing) {
            enclosing->assign(name, std::move(value), loc);
            return;
        }

        throw RuntimeError(loc, "Undefined variable '" + name + "'.");
    }

    std::shared_ptr<Value> get(const std::string& name, const SourceLocation& loc) {
        if (values.count(name)) {
            return values[name];
        }

        if (enclosing) {
            return enclosing->get(name, loc);
        }

        throw RuntimeError(loc, "Undefined variable '" + name + "'.");
    }
};

} // namespace dli

