#ifndef _REPL_H_
#define _REPL_H_

#include <string>

#include "environment.h"
#include "exceptions.h"
#include "printer.h"
#include "reader.h"
#include "types.h"

const std::string RESET   = "\033[0m";
const std::string BLACK   = "\033[30m";
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN    = "\033[36m";
const std::string WHITE   = "\033[37m";


ObPtr READ(std::string input);
ObPtr EVAL(ObPtr ast, Env& env);
std::string PRINT(ObPtr input);
ObPtr evalAst(ObPtr ast, Env& env);
std::string rep(std::string input, Env& env);


#endif
