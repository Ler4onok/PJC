#include "expr.hpp"
#include "expr_impl.hpp"
#include <stdexcept>


expr expr::number(double num) {
    return std::make_shared<exprs::number>(exprs::number(num));
}

const expr expr::ZERO = expr::number(0.0);
const expr expr::ONE = expr::number(1.0);

// TODO: overloaded operators +, -, *, /, functions pow, log, sin, cos,
//       expr::number, expr::variable, operator==, operator<<,
//       create_expression_tree

expr create_expression_tree(const std::string& expression) {
    // TODO
    throw std::logic_error("not implemented");
}

bool operator==(const expr &a, const expr &b) {
    return a->equals(*b->shared_from_this());
//    throw std::logic_error("not implemented");
}

std::ostream& operator<<(std::ostream &os, const expr &e) {
    e->write(os, expr_base::WriteFormat::Prefix);
    return os;
}

std::ostream& operator<<(std::ostream &os, fmt_expr const &f){

    f.e->write(os,f.fmt);

    return os;
}

expr operator+(expr a, expr b) {
    return std::make_shared<exprs::expr_add>(a, b);
}

expr operator-(expr a, expr b) {
    return std::make_shared<exprs::expr_minus>(exprs::expr_minus(a, b));

}

expr operator*(expr a, expr b) {
    return std::make_shared<exprs::expr_multiply>(exprs::expr_multiply(a, b));

}

expr operator/(expr a, expr b) {
    return std::make_shared<exprs::expr_divide>(exprs::expr_divide(a, b));

}

expr pow(expr m, expr e) {
    return std::make_shared<exprs::expr_pow>(exprs::expr_pow(m, e));

}

expr sin(expr e) {
    return std::make_shared<exprs::expr_sin>(exprs::expr_sin(e));

}

expr cos(expr e) {
    return std::make_shared<exprs::expr_cos>(exprs::expr_cos(e));

}

expr log(expr e) {
    return std::make_shared<exprs::expr_log>(exprs::expr_log(e));
}
