#ifndef _CORE_H_
#define _CORE_H_

#include <climits>
#include <random>
#include <string>
#include <vector>
#include <unordered_map>

#include "exceptions.h"
#include "printer.h"
#include "types.h"


HashMap buildNamespace();

ObPtr add(std::vector<ObPtr> args, const Env& env);
ObPtr subtract(std::vector<ObPtr> args, const Env& env);
ObPtr multiply(std::vector<ObPtr> args, const Env& env);
ObPtr divide(std::vector<ObPtr> args, const Env& env);

ObPtr equal(std::vector<ObPtr> args, const Env& env);
ObPtr notEqual(std::vector<ObPtr> args, const Env& env);
ObPtr lessThan(std::vector<ObPtr> args, const Env& env);
ObPtr lessEqual(std::vector<ObPtr> args, const Env& env);
ObPtr greaterThan(std::vector<ObPtr> args, const Env& env);
ObPtr greaterEqual(std::vector<ObPtr> args, const Env& env);
ObPtr negation(std::vector<ObPtr> args, const Env& env);

ObPtr list(std::vector<ObPtr> args, const Env& env);
ObPtr isList(std::vector<ObPtr> args, const Env& env);
ObPtr isSequenceEmpty(std::vector<ObPtr> args, const Env& env);
ObPtr seqSize(std::vector<ObPtr> args, const Env& env);
ObPtr print(std::vector<ObPtr> args, const Env& env);
ObPtr type(std::vector<ObPtr> args, const Env& env);
ObPtr nvector(std::vector<ObPtr> args, const Env& env);
ObPtr matrix(std::vector<ObPtr> args, const Env& env);
ObPtr dotProduct(std::vector<ObPtr> args, const Env& env);
ObPtr eye(std::vector<ObPtr> args, const Env& env);
ObPtr randomMatrix(std::vector<ObPtr> args, const Env& env);

#endif
