#include "tokenizer.hpp"
#include "expr.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <stack>
//------------------------------------------------------------------------------
//---  Token
//------------------------------------------------------------------------------

bool Token::is_binary_op() const {
    return id != TokenId::End && std::strchr(BINOPS, static_cast<char>(id)) != nullptr;
}
//------------------------------------------------------------------------------

int Token::op_precedence() const {
    if(is_function()){
        return 5;
    }
    switch (id) {
        case TokenId::Power:
            return 3;
        case TokenId::Multiply:
        case TokenId::Divide:
            return 2;
        case TokenId::LParen:
            return 0;
        default:
            return 1;
    }
}
//------------------------------------------------------------------------------

Associativity Token::associativity() const {
    if (id == TokenId::Power)
        return Associativity::Right;
    return Associativity::Left;
}

bool Token::is_function() const {
    return this->function;

    ///return  this->identifier== "log" || this->identifier== "cos" ||this->identifier== "sin";
}

bool Token::is_cos() const {
    return  this->identifier== "cos";
}

bool Token::is_sin() const {
    return  this->identifier== "sin";
}

bool Token::is_log() const {
    return this->identifier== "log";
}
//------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &os, const Token &tok) {
    os << "Token('" << (char) tok.id << "'";
    if (tok.id == TokenId::Number)
        os << ", " << tok.number;
    else if (tok.id == TokenId::Identifier)
        os << ", " << tok.identifier;
    os << ")";
    return os;
}
//------------------------------------------------------------------------------
//---  Tokenizer
//------------------------------------------------------------------------------

Tokenizer::Tokenizer(std::istream &is)
        : m_is(is) {
}
//------------------------------------------------------------------------------

Token Tokenizer::next() {
    m_is >> std::skipws;
    std::istream::sentry sentry(m_is);
    if (!sentry)
        return Token(TokenId::End);

    auto c = m_is.peek();
    Token res;
    bool consume = true;

    if (c == std::istream::traits_type::eof())
        return Token(TokenId::End);
    else if (std::isdigit(c)) {
        double number;
        m_is >> number;
        res = Token(TokenId::Number, number);
        consume = false;
    } else if (std::isalpha(c)) {
        std::string ident;
        m_is.ignore();
        do {
            ident.push_back(c);
            c = m_is.get();
        } while (std::isalpha(c));
        if (c != std::istream::traits_type::eof())
            m_is.putback(c);

        // clearly retarded API (pun intended): clear does not clear the bits,
        // but sets them
        m_is.clear(m_is.rdstate() & ~std::ios::failbit);

        res = Token(TokenId::Identifier, std::move(ident));
        consume = false;
    } else {
        if (std::strchr(SYMBOL_TOKENS, c) == nullptr) {
            std::stringstream ss;
            ss << "unknown token " << static_cast<char>(c);
            throw tokenize_error(ss.str());
        }
        res = Token(static_cast<TokenId>(c));
    }
    if (m_is.fail())
        throw tokenize_error("failed conversion");
    if (consume)
        m_is.get();
    return res;
}


std::vector<Token> Tokenizer::create_prefix(std::vector<Token>  token_array) {
    Token tmp = next();
    std::stack<Token> operators = std::stack<Token>();
    std::stack<std::vector<Token>> operands = std::stack<std::vector<Token>>();


    for (auto tmp : token_array) {
        if (tmp.id == TokenId::End) {
            break;
        } else if (tmp.id == TokenId::LParen) {
            operators.push(tmp);
        } else if (tmp.id == TokenId::RParen) {
            while (!operators.empty() && operators.top().id != TokenId::LParen) {
                auto op = operators.top();
                operators.pop();

                auto operand1 = operands.top();
                operands.pop();

                auto operand2 = operands.top();
                operands.pop();
                std::vector<Token> tmp_vec = std::vector<Token>();
                tmp_vec.push_back(op);

                /// join three vectors
                tmp_vec.insert(tmp_vec.end(), operand2.begin(), operand2.end());
                tmp_vec.insert(tmp_vec.end(), operand1.begin(), operand1.end());
                operands.push(tmp_vec);

            }
            /// pop Lparen
            operators.pop();

            /// is operand or var
        } else if (tmp.id == TokenId::Identifier || tmp.id == TokenId::Number) {
            std::vector<Token> tmp_vec = std::vector<Token>();
            tmp_vec.push_back(tmp);
            operands.push(tmp_vec);
        } else {
            while (!operators.empty() && tmp.op_precedence() <= operators.top().op_precedence()) {
                auto op = operators.top();
                operators.pop();

                auto operand1 = operands.top();
                operands.pop();

                auto operand2 = operands.top();
                operands.pop();
                std::vector<Token> tmp_vec = std::vector<Token>();
                tmp_vec.push_back(op);

                /// join three vectors
                tmp_vec.insert(tmp_vec.end(), operand2.begin(), operand2.end());
                tmp_vec.insert(tmp_vec.end(), operand1.begin(), operand1.end());
                operands.push(tmp_vec);
            }
            operators.push(tmp);
        }
        tmp = next();
    }
    while (!operators.empty()) {
        auto op = operators.top();
        operators.pop();

        auto operand1 = operands.top();
        operands.pop();

        auto operand2 = operands.top();
        operands.pop();
        std::vector<Token> tmp_vec = std::vector<Token>();
        tmp_vec.push_back(op);

        /// join three vectors
        tmp_vec.insert(tmp_vec.end(), operand2.begin(), operand2.end());
        tmp_vec.insert(tmp_vec.end(), operand1.begin(), operand1.end());
        operands.push(tmp_vec);
    }

    if(operands.empty() || operands.top().size()==0){
        return std::vector<Token>();
    }



    return operands.top();
}