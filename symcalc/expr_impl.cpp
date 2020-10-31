#include "expr_impl.hpp"

#include <iostream>
#include <cmath>
#include <limits>

namespace exprs {

// class VARIABLE

//    variable::variable(string string) : name(string) {}

    double var::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr var::derive(std::string const &temp) const {
        throw std::logic_error("not implemented yet");
    }

    expr var::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    bool var::equals(const expr_base &base) const {
//        if (const var *rhs = dynamic_cast<var const *>(base.shared_from_this().get())) {
//            bool result = rhs->variable == variable;
//            return result;
//        }
//        return false;

        throw std::logic_error("not implemented yet");

    }

    void var::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        out << variable;
    }


    //class NUMBER

//    number::number(double number){
//        num=number;
//    }

    void number::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        out << this->num;
    }

    double number::evaluate(const expr_base::variable_map_t &variable_map) const {
        return num;
    }

    expr number::derive(std::string const &temp) const {
        return expr::ZERO;
    }

    expr number::simplify() const {
        return shared_from_this();
    }


    bool number::equals(const expr_base &base) const {
        if(const number* v = dynamic_cast<number const*>(base.shared_from_this().get())) {
            bool result =  v->num == num;
            return result;
        }
        return false;
    }

    //class ADD

    double expr_add::evaluate(const expr_base::variable_map_t &variables) const {
        return first->evaluate(variables) + second->evaluate(variables);
    }

    expr expr_add::derive(std::string const &variable) const {
        return first->derive(variable) + second->derive(variable);    }

    expr expr_add::simplify() const {
        expr one = first->simplify();
        expr two = second->simplify();
        if(one == expr::ZERO){
            return two;
        }
        else if(two == expr::ZERO){
            return one;
        }
        return std::make_shared<exprs::expr_add>(expr_add(one,two));
    }

//    expr_plus::expr_plus(const expr &a, const expr &b) : one(a), two(b) {}

    void expr_add::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << " +)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "(" << fmt_expr{first, fmt} << " + " << fmt_expr{second, fmt} << ")";
        } else {
            out << "(+ " << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << ")";
        }
    }

    bool expr_add::equals(const expr_base &b) const {
        if(const expr_add* v = dynamic_cast<expr_add const*>(b.shared_from_this().get())) {
            return v->first == first && v->second == second;
        }
        return false;
    }

    // class MINUS

    double expr_minus::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_minus::derive(std::string const &temp) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_minus::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_minus::equals(const expr_base &variable) const {
        throw std::logic_error("not implemented yet");
    }

    void expr_minus::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << " -)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "(" << fmt_expr{first, fmt} << " - " << fmt_expr{second, fmt} << ")";
        } else {
            out << "(- " << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << ")";
        }
    }

// class MULTIPLY

    double expr_multiply::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_multiply::derive(std::string const &temp) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_multiply::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_multiply::equals(const expr_base &variable) const {
        throw std::logic_error("not implemented yet");
    }

    void expr_multiply::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << " *)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "(" << fmt_expr{first, fmt} << " * " << fmt_expr{second, fmt} << ")";
        } else {
            out << "(* " << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << ")";
        }
    }

    //class DIVIDE

    double expr_divide::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_divide::derive(std::string const &temp) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_divide::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_divide::equals(const expr_base &variable) const {
        throw std::logic_error("not implemented yet");
    }

    void expr_divide::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << " /)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "(" << fmt_expr{first, fmt} << " / " << fmt_expr{second, fmt} << ")";
        } else {
            out << "(/ " << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << ")";
        }
    }


    double expr_pow::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_pow::derive(std::string const &temp) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_pow::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_pow::equals(const expr_base &variable) const {
        throw std::logic_error("not implemented yet");
    }

    void expr_pow::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << " ^)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "(" << fmt_expr{first, fmt} << " ^ " << fmt_expr{second, fmt} << ") ";
        } else {
            out << "(^ " << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << ")";
        }
    }


    double expr_sin::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_sin::derive(std::string const &temp) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_sin::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    void expr_sin::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{child, fmt} << " sin)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "sin (" << fmt_expr{child, fmt} << ")";
        } else {
            out << "(sin " << fmt_expr{child, fmt} << ")";
        }

    }

    bool expr_sin::equals(const expr_base &variable) const {
        throw std::logic_error("not implemented yet");
    }

    double expr_cos::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_cos::derive(std::string const &temp) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_cos::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    void expr_cos::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{child, fmt} << " cos)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "cos (" << fmt_expr{child, fmt} << ")";
        } else {
            out << "(cos " << fmt_expr{child, fmt} << ")";
        }
    }

    bool expr_cos::equals(const expr_base &variable) const {
        throw std::logic_error("not implemented yet");
    }


    double expr_log::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_log::derive(std::string const &temp) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_log::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    void expr_log::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{child, fmt} << " log)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "log (" << fmt_expr{child, fmt} << ")";
        } else {
            out << "(log " << fmt_expr{child, fmt} << ")";
        }
    }

    bool expr_log::equals(const expr_base &variable) const {
        throw std::logic_error("not implemented yet");
    }

} // namespace exprs
