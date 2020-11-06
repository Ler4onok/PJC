#pragma once

#include "expr.hpp"
#include <iosfwd>
#include <utility>

namespace exprs {

    //class variable
    class var : public expr_base {

        friend class expr;

    public:

        explicit var(std::string string) : variable(std::move(string)) {};

        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &deriveBy) const override;
        expr simplify() const override;

    private:

        std::string variable;

        void write(std::ostream &out, WriteFormat fmt) const override;
        bool equals(const expr_base &b) const override;

    };

    //class number

    class num: public expr_base{
        friend class expr;

    private:

        double number;

        void write(std::ostream &out, WriteFormat fmt) const override;
        bool equals(const expr_base &variable) const  override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &temp) const override;
        expr simplify() const override;

    public:
        explicit num(double num) : number(num) {};

    };

    //class expr_add

    class expr_add : public expr_base {

        friend class expr;

    public:

        expr_add( expr& one, expr& two): first(one), second(two){};

    private:

        expr first;
        expr second;

        void write(std::ostream &out, WriteFormat fmt) const override;
        bool equals(const expr_base &b) const override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &variable) const override;
        expr simplify() const override;

    };

    //class expr_minus

    class expr_minus : public expr_base {

        friend class expr;

    public:

        expr_minus(expr &one, expr &two) : first(one), second(two) {};

    private:

        expr first;
        expr second;

        void write(std::ostream &out, WriteFormat fmt) const override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &variable) const override;
        expr simplify() const override;
        bool equals(const expr_base &b) const override;

    };

    //class expr_minus

    class expr_multiply : public expr_base {

        friend class expr;

    public:

        expr_multiply(expr &one, expr &two) : first(one), second(two) {};

    private:

        expr first;
        expr second;

        void write(std::ostream &out, WriteFormat fmt) const override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &variable) const override;
        expr simplify() const override;
        bool equals(const expr_base &b) const override;

    };

    //class expr_divide

    class expr_divide : public expr_base {

        friend class expr;

    public:

        expr_divide(expr &one, expr &two) : first(one), second(two) {};

    private:

        expr first;
        expr second;

        void write(std::ostream &out, WriteFormat fmt) const override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &variable) const override;
        expr simplify() const override;
        bool equals(const expr_base &b) const override;

    };

    //class expr_pow

    class expr_pow : public expr_base {

        friend class expr;

    public:

        expr_pow(expr &one, expr &two) : first(one), second(two) {};

    private:

        expr first;
        expr second;

        void write(std::ostream &out, WriteFormat fmt) const override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &variable) const override;
        expr simplify() const override;
        bool equals(const expr_base &b) const override;

    };

    //class expr_log

    class expr_log : public expr_base {

        friend class expr;

    public:

        explicit expr_log(expr &rhs) : child(rhs) {};

    private:

        expr child;

        void write(std::ostream &out, WriteFormat fmt) const override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &variable) const override;
        expr simplify() const override;
        bool equals(const expr_base &b) const override;

    };

    //class expr_sin

    class expr_sin : public expr_base {

        friend class expr;

    public:

        explicit expr_sin(expr &rhs) : child(rhs) {};

    private:

        expr child;

        void write(std::ostream &out, WriteFormat fmt) const override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &variable) const override;
        expr simplify() const override;
        bool equals(const expr_base &b) const override;

    };

    //class expr_cos

    class expr_cos : public expr_base {

        friend class expr;

    public:

        explicit expr_cos(expr &rhs) : child(rhs) {};

    private:

        expr child;

        void write(std::ostream &out, WriteFormat fmt) const override;
        double evaluate(const variable_map_t &variables) const override;
        expr derive(std::string const &variable) const override;
        expr simplify() const override;
        bool equals(const expr_base &b) const override;

    };



}
