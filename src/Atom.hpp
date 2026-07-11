#pragma once
#include <string>
#include <utility>

namespace ext {

struct Atom {
    std::string symbol;
    double x;
    double y;
    double z;

    Atom(std::string sym, double x_val, double y_val, double z_val)
        : symbol(std::move(sym)), x(x_val), y(y_val), z(z_val) {}
};

} // namespace ext
