#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>

#include "core.h"
#include "environment.h"
#include "exceptions.h"
#include "linenoise.hpp"
#include "printer.h"
#include "reader.h"
#include "types.h"


ObPtr READ(std::string input);
ObPtr EVAL(ObPtr ast, Env& env);
std::string PRINT(ObPtr input);
ObPtr evalAst(ObPtr ast, Env& env);
std::string rep(std::string input, Env& env);


const char* HISTORY_PATH = "history.txt";


int main() {
    linenoise::LoadHistory(HISTORY_PATH);

    Env replEnv;
    for (auto& e : buildNamespace())
        replEnv.set(e.first, e.second);

    std::string line;
    for(;;) {
        auto status = linenoise::Readline("user> ", line);
        if (status)
            break;
        std::cout << rep(line, replEnv) << std::endl;
        linenoise::AddHistory(line.c_str());
    }

    linenoise::SaveHistory(HISTORY_PATH);

    return 0;
}


ObPtr READ(std::string input) {
    return readStr(input);
}

ObPtr EVAL(ObPtr ast, Env& env) {
    if (ast->type() != Object::obType::LIST)
        return evalAst(ast, env);
    else if (ast->asList()->empty())
        return ast;
    else {
        List* list = ast->asList();
        ObPtr first = list->at(0);
        if (first->type() == Object::obType::SYMBOL) {
            Symbol* special = first->asSymbol();
            if (special->matches("def!")) {
                try {
                    ObPtr key = list->at(1);
                    ObPtr value = EVAL(list->at(2), env);
                    env.set(key, value);
                    return value; // CHECK IT!!
                }
                catch (const std::out_of_range& e) {
                    throw SyntaxError(list->repr());
                }
            }
            else if (special->matches("let*")) {
                if (list->size() != 3)
                    throw SyntaxError(list->repr());

                ObPtr bindings(list->at(1));
                if (bindings->asSequence()->size() % 2 != 0)
                    throw SyntaxError(bindings->repr());

                Sequence* binds = bindings->asSequence();
                Env newEnv(&env);
                for (int i = 0; i < binds->size(); i += 2) {
                    ObPtr key = binds->at(i);
                    ObPtr value = EVAL(binds->at(i + 1), newEnv);
                    newEnv.set(key, value);
                }
                return EVAL(list->at(2), newEnv);
            } else if (special->matches("do")) {
                ObPtr result = newNil();
                for (int i = 1; i < list->size(); i++)
                    result = EVAL(list->at(i), env);
                return result;

            } else if (special->matches("if")) {
                try {
                    ObPtr condition = list->at(1);
                    ObPtr trueExpr = list->at(2);
                    ObPtr falseExpr = list->size() == 4 ?
                        list->at(3) : newNil();
                    if (*EVAL(condition, env))
                        return EVAL(trueExpr, env);
                    else
                        return EVAL(falseExpr, env);
                } catch (const std::out_of_range& e) {
                    throw SyntaxError(
                        "if (condition) (true_expr) [(false_expr)]"
                    );
                }
            }
            else if (special->matches("fn*")) {
                try {
                    ObPtr binds(list->at(1));
                    ObPtr body(list->at(2));
                    auto closure = [binds, body](std::vector<ObPtr> args, const Env& env = nullptr) {
                        ObPtr exprs = newList(args.cbegin(), args.cend());
                        Env newEnv(&env, binds, exprs);
                        return EVAL(body, newEnv);
                    };
                    return newFn(closure);
                } catch (const std::out_of_range& e) {
                    throw SyntaxError("fn* (args) (body)");
                }
            }
        }
        ObPtr term(evalAst(ast, env));
        List* evalList = term->asList();
        ObPtr evalFirst = evalList->at(0);
        if (evalFirst->type() == Object::obType::FN) {
            std::vector<ObPtr> args(evalList->begin() + 1, evalList->end());
            return (*evalFirst->asFn())(args, env);
        } else
            throw NotFound("<function> " + evalFirst->repr() + "()");
    }
}

ObPtr evalAst(ObPtr ast, Env& env) {
    switch (ast->type()) {
        case Object::obType::SYMBOL: {
            ObPtr sym = env.get(ast);
            return sym;
        }
        case Object::obType::LIST: {
            ObPtr result = newList();
            for (auto& e : *(ast->asList())) {
                result->asList()->push(EVAL(e, env));
            }
            return result;
        }
        case Object::obType::VECTOR: {
            ObPtr result = newVector();
            for (auto& e : *(ast->asVector()))
                result->asVector()->push(EVAL(e, env));
            return result;
        }
        case Object::obType::HASHMAP: {
            ObPtr result = newHashMap();
            for (auto& e : *(ast->asHashMap()))
                result->asHashMap()->set(e.first, EVAL(e.second, env));
            return result;
        }
        default:
            return ast;
    }
}

std::string PRINT(ObPtr input) {
    return prStr(input);
}

std::string rep(std::string input, Env& env) {
    ObPtr result = nullptr;
    try {
        result = EVAL(READ(input), env);
    } catch (const NotFound& e) {
        std::cerr << "[Not Found]: " << e.what();
    } catch (const SyntaxError& e) {
        std::cerr << "[SyntaxError]: " << e.what();
    } catch (const TypeError& e) {
        std::cerr << "[TypeError]: " << e.what();
    } catch (const OutOfRange& e) {
        std::cerr << "[OutOfRange]: " << e.what();
    } catch (const ValueError& e) {
        std::cerr << "[ValueError]: " << e.what();
    } catch (const DivisionByZero& e) {
        std::cerr << "[DivisionByZero]: " << e.what();
    } catch (const std::bad_cast& e) {
        std::cerr << "[BADCAST :(]: " << e.what();
    }
    return PRINT(result);
}

