#pragma once

#include <memory>

namespace dli {

struct SourceLocation {
    int firstLine {1};
    int firstColumn {1};
    int lastLine {1};
    int lastColumn {1};
};

struct ASTNode {
    virtual ~ASTNode() = default;
    SourceLocation loc {};
    virtual void accept(class ASTVisitor& v) = 0;
};

} // namespace dli


