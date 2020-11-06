#include "expr_impl.hpp"
#include <iostream>
#include <cmath>

namespace exprs {

    //____________________
    //
    // CLASS NUMBER
    //____________________

    void num::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        out << number;
    }

    double num::evaluate(const expr_base::variable_map_t &variables) const {
        return number;
    }

    expr num::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr num::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    bool num::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }

    //____________________
    //
    // CLASS VARIABLE
    //____________________

    void var::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        out << variable;
    }

    double var::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr var::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr var::derive(std::string const &deriveBy) const {
        throw std::logic_error("not implemented yet");
    }

    bool var::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }

    //____________________
    //
    // CLASS PLUS
    //____________________

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

    double expr_add::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_add::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_add::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_add::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }

    //____________________
    //
    //CLASS MINUS
    //____________________

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

    double expr_minus::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_minus::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_minus::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }


    bool expr_minus::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }

    //____________________
    //
    // CLASS MULTIPLY
    //____________________

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

    double expr_multiply::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_multiply::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_multiply::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_multiply::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }

    //____________________
    //
    // CLASS DIVIDE
    //____________________

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

    bool expr_divide::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");

    }

    double expr_divide::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");

    }

    expr expr_divide::simplify() const {
        throw std::logic_error("not implemented yet");

    }

    expr expr_divide::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    //____________________
    //
    // CLASS POWER
    //____________________

    void expr_pow::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if (fmt == WriteFormat::Postfix) {
            out << "(" << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << " ^)";
        }
        if (fmt == WriteFormat::Infix) {
            out << "(" << fmt_expr{first, fmt} << " ^ " << fmt_expr{second, fmt} << ")";
        } else {
            out << "(^ " << fmt_expr{first, fmt} << " " << fmt_expr{second, fmt} << ")";
        }
    }

    bool expr_pow::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }

    double expr_pow::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_pow::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_pow::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    //____________________
    //
    // CLASS SIN
    //____________________

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

    double expr_sin::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_sin::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_sin::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_sin::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }

    //____________________
    //
    // CLASS COS
    //____________________

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

    double expr_cos::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_cos::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_cos::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_cos::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");

    }

    //____________________
    //
    // CLASS LOG
    //____________________

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

    double expr_log::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_log::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_log::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    bool expr_log::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }

}

