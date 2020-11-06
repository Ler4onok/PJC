#include "expr.hpp"
#include "expr_impl.hpp"
#include "tokenizer.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stack>

const expr expr::ZERO = expr::number(0.0);
const expr expr::ONE = expr::number(1.0);

expr expr::number(double n) {
    return std::make_shared<exprs::num>(exprs::num(n));
}

expr expr::variable(std::string name) {
    return std::make_shared<exprs::var>(exprs::var(name));
}

void add_node(std::stack<expr> &operands, Token op) {
    expr lhs;
    expr rhs;

    switch (op.id) {

        case TokenId::Plus:
            rhs = operands.top();
            operands.pop();
            lhs = operands.top();
            operands.pop();

            operands.push(lhs + rhs);
            break;

        case TokenId::Minus:
            rhs = operands.top();
            operands.pop();
            lhs = operands.top();
            operands.pop();

            operands.push(lhs - rhs);
            break;
        case TokenId::Multiply:
            rhs = operands.top();
            operands.pop();
            lhs = operands.top();
            operands.pop();

            operands.push(lhs * rhs);
            break;
        case TokenId::Divide:
            rhs = operands.top();
            operands.pop();
            lhs = operands.top();
            operands.pop();

            operands.push(lhs / rhs);
            break;
        case TokenId::Power:
            rhs = operands.top();
            operands.pop();
            lhs = operands.top();
            operands.pop();

            operands.push(pow(lhs, rhs));
            break;
        case TokenId::Identifier:

            if (op.is_function()) {
                lhs = operands.top();
                operands.pop();
                if (op.is_cos()) {
                    operands.push(cos(lhs));
                } else if (op.is_sin()) {
                    auto ffs = sin(lhs);
                    operands.push(ffs);
                } else if (op.is_log()) {
                    operands.push(log(lhs));
                }
            } else {
                throw parse_error("! unknown function ");
            }
            break;
    }


}

void check_left(int r_paren_left, bool awaiting_left_parent, bool awaiting_operator){
    if (r_paren_left != 0) {
        throw parse_error("! unclosed parenthesis");
    } else if (awaiting_left_parent) {
        throw parse_error("! awaited left parent after function");
    } else if (awaiting_operator) {
        throw parse_error("! last token is operator");
    }
}

bool is_formatted(std::vector<Token>& token_array) {
    int array_size = token_array.size();
    int left_side = 0;
    bool left_parent = false;
    bool awaiting_operator = false;

//    for(Token token: token_array){
    for (int i=0; i < array_size; i++) {
        if (token_array[i].id == TokenId::RParen) {
            left_side = left_side - 1;

        }
        else if (token_array[i].id == TokenId::LParen) {
            if (awaiting_operator) {
                throw parse_error("() instaed of operator");
            }

            //if left parent exists
            if (left_parent == true) {
                left_parent = false;
            }

            left_side = left_side +  1;
            awaiting_operator = false;

        }

        else if (token_array[i].id == TokenId::Number) {
            if (awaiting_operator) {
                throw parse_error("The number instead of operator");
            }
            awaiting_operator = true;
        }

        else if (token_array[i].id == TokenId::Identifier) {

            if (token_array[i + 1].id == TokenId::LParen) {
                left_parent = true;

                if (!(token_array[i].identifier == "log" || token_array[i].identifier == "cos" || token_array[i].identifier == "sin")) {
                    throw unknown_function_exception("The function is unknown");

                } else if (token_array[i].identifier == "log" || token_array[i].identifier == "cos" || token_array[i].identifier == "sin"){
                    token_array[i].function = true;
                }
            } else {
                awaiting_operator = true;
                //                if (awaiting_operator) {
//                    throw parse_error("number instead of operator");
//                }
            }
        } else {
            if (awaiting_operator == false) {
                throw parse_error("! unexpected operator");
            } else {
                awaiting_operator = false;
            }
        }

    }

    // additional check of left side
    check_left(left_side, left_parent, awaiting_operator);

    return true;

}

std::vector<Token> tokenize(const std::string& str){
    Token token;
    std::vector<Token> tokens;

    auto ss = std::stringstream(str);
    std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>(ss);

    // first iteration before loop starts
    token = t->next();
    tokens.push_back(token);

    while (token.id != TokenId::End) {
        token = t->next();
        tokens.push_back(token);
    }

    return tokens;
}

bool compare(auto expr1, auto expr2){
    if (expr1 == expr2){
        return true;
    }
    else{
        return false;
    }
}
//void add_value(std::stack<Token> operators, std::stack<expr> operands, Token token){
//    Token t2;
//
//    while (!operators.empty()) {
//        t2 = operators.top();
//        if ((token.associativity() == Associativity::Left && token.op_precedence() == t2.op_precedence()) ||
//            token.op_precedence() < t2.op_precedence()) {
//            operators.pop();
//            add_node(operands, t2);
//
//        } else {
//            break;
//        }
//    }
//    operators.push(token);
//}


expr create_expression_tree(const std::string& expression) {
    // get expression
    auto ss = std::stringstream(expression);
    // add parser??
    std::vector<Token> tokens = tokenize(expression);

    std::stack<Token> operators;
    std::stack<expr> operands;
    Token tok;

    if (is_formatted(tokens) == false) {
        throw parse_error("The array is wrong");
    }


    for (int i = 0; i < tokens.size(); i++) {

        if (compare(tokens[i].id, TokenId::LParen)){
            operators.push(tokens[i]);
        }

        else if(compare(tokens[i].id, TokenId::RParen)){
            while (!operators.empty()) {
                tok = operators.top();
                operators.pop();
                if (tok.id == TokenId::LParen) {
                        break;
                    } else {
                        add_node(operands, tok);
                    }
            }
        }
        else if (compare(tokens[i].id, TokenId::Number)){
            operands.push(expr::number(tokens[i].number));

        }

        else if (compare(tokens[i].id, TokenId::Identifier)) {
            if (!tokens[i].is_function()) {
                operands.push(expr::variable(tokens[i].identifier));

            } else {

                while (!operators.empty()) {
                    if (!((tokens[i].associativity() == Associativity::Left && tokens[i].op_precedence() == operators.top().op_precedence()) ||
                        tokens[i].op_precedence() < operators.top().op_precedence())) {
                        break;
                    } else if ((operators.top().op_precedence() < tokens[i].op_precedence()) || (tokens[i].associativity() == Associativity::Left && tokens[i].op_precedence() == operators.top().op_precedence())) {
                        operators.pop();
                        add_node(operands, operators.top());
                    }
                }
                operators.push(tokens[i]);
            }
        }

        else {
            while (!operators.empty()) {
                Token top =  operators.top();
                if (!((tokens[i].associativity() == Associativity::Left && tokens[i].op_precedence() == top.op_precedence()) ||
                    tokens[i].op_precedence() < top.op_precedence())) {
                  break;

                } else {
                    operators.pop();
                    add_node(operands, top);
                }
            }
            operators.push(tokens[i]);
        }

    }


    while (!operators.empty()) {
        add_node(operands, operators.top());
        operators.pop();
    }

    return operands.top();
}

bool operator==(const expr &a, const expr &b) {
    return a->equals(*b->shared_from_this());
}

std::ostream &operator<<(std::ostream &os, const expr &e) {
    e->write(os, expr::WriteFormat::Prefix);
    return os;
}

std::ostream &operator<<(std::ostream &os, const fmt_expr &fmt) {
    fmt.e->write(os, fmt.fmt);
    return os;
}
expr operator+(expr a, expr b) {
    return std::make_shared<exprs::expr_add>(exprs::expr_add(a, b));
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