#include "core.h"


HashMap buildNamespace() {
    HashMap ns;
    ns.set(newSymbol("+"), newFn(add));
    ns.set(newSymbol("-"), newFn(subtract));
    ns.set(newSymbol("*"), newFn(multiply));
    ns.set(newSymbol("/"), newFn(divide));
    ns.set(newSymbol("**"), newFn(dotProduct));

    ns.set(newSymbol("="), newFn(equal));
    ns.set(newSymbol("!="), newFn(notEqual));
    ns.set(newSymbol("<"), newFn(lessThan));
    ns.set(newSymbol("<="), newFn(lessEqual));
    ns.set(newSymbol(">"), newFn(greaterThan));
    ns.set(newSymbol(">="), newFn(greaterEqual));
    ns.set(newSymbol("not"), newFn(negation));

    ns.set(newSymbol("true"), newTrue());
    ns.set(newSymbol("false"), newFalse());
    ns.set(newSymbol("nil"), newNil());

    ns.set(newSymbol(";"), newSymbol(";"));

    ns.set(newSymbol("list"), newFn(list));
    ns.set(newSymbol("list?"), newFn(isList));
    ns.set(newSymbol("empty?"), newFn(isSequenceEmpty));
    ns.set(newSymbol("count"), newFn(seqSize));
    ns.set(newSymbol("prn"), newFn(print));
    ns.set(newSymbol("type?"), newFn(type));
    ns.set(newSymbol("nvector"), newFn(nvector));
    ns.set(newSymbol("matrix"), newFn(matrix));
    ns.set(newSymbol("eye"), newFn(eye));
    ns.set(newSymbol("zeros"), newFn(zeros));
    ns.set(newSymbol("randmat"), newFn(randomMatrix));
    ns.set(newSymbol("randmatf"), newFn(randomMatrixFloat));
    ns.set(newSymbol("transpose"), newFn(transposeMatrix));

    return ns;
}

ObPtr add(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'+' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] + *args[1];
}


ObPtr subtract(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'-' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] - *args[1];
}


ObPtr multiply(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'*' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] * *args[1];
}


ObPtr divide(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'/' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] / *args[1];
}

ObPtr equal(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'=' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] == *args[1];
}

ObPtr lessThan(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'<' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] < *args[1];
}

ObPtr lessEqual(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'<=' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] <= *args[1];
}

ObPtr greaterThan(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'>' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] > *args[1];
}

ObPtr greaterEqual(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'>=' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    return *args[0] >= *args[1];
}

ObPtr list(std::vector<ObPtr> args, const Env& env) {
    ObPtr result = newList();
    for (auto& e : args)
        result->as<List>()->push(e);
    return result;
}

ObPtr isList(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'list?' takes 1 args, but" +
                std::to_string(args.size()) + " were given");
    return newBool(args[0]->is<List>());
}

ObPtr isSequenceEmpty(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'empty?' takes 1 args, but" +
                std::to_string(args.size()) + " were given");
    return newBool(args[0]->as<Sequence>()->empty());
}

ObPtr seqSize(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'count' takes 1 args, but " +
                std::to_string(args.size()) + " were given");
    if (args[0]->is<Nil>())
        return newInteger(0);
    return newInteger(args[0]->as<Sequence>()->size());
}

ObPtr print(std::vector<ObPtr> args, const Env& env) {
    if (args.size() > 0) {
        std::string out;
        for (auto& e : args)
            out += prStr(e) + " ";
        out[out.size() - 1] = '\n';
        std::cout << out;
    }
    return newNil();
}

ObPtr type(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError(
            "'type?' takes 1 args, but " + std::to_string(args.size()) + " were given"
        );
    return newSymbol(args[0]->typeRepr());
}

ObPtr negation(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'not' takes 1 args, but " +
                std::to_string(args.size()) + " were given");
    return !*args[0];
}

ObPtr notEqual(std::vector<ObPtr> args, const Env& env) {
    return !*equal(args, env);
}

ObPtr nvector(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'nvector' takes 1 args, but " +
                std::to_string(args.size()) + " were given");
    if (!args[0]->as<Vector>())
        throw TypeError("'nvector' takes vector as argument");
    ObPtr res = newNvector();
    Nvector* resPtr = res->as<Nvector>();
    for (const auto& e : *args[0]->as<Vector>()) {
        if (!e->as<Numeric>())
            throw TypeError("Value type must be <Numeric>: " + e->repr());
        resPtr->push(e->as<Numeric>()->asFlt());
    }
    return res;
}

ObPtr matrix(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'matrix' takes 1 args, but " +
                std::to_string(args.size()) + " were given");
    if (!args[0]->as<Vector>())
        throw TypeError("'matrix' takes vector as argument");
    ObPtr res = newMatrix();
    Matrix* resPtr = res->as<Matrix>();

    int i = 0;
    Nvector row;
    for (const auto& e : *args[0]->as<Vector>()) {
        if (e->repr() == ";") {
            if ((i == 0) || (*resPtr)[i - 1].size() == row.size()) {
                resPtr->push(row);
                row.clear();
                i++;
            } else
                throw ValueError("All rows in matrix must be the same size");
        }
        else if (!e->as<Numeric>())
            throw TypeError("Value type must be <Numeric>: " + e->repr());
        else 
            row.push(e->as<Numeric>()->asFlt());
    }
    if ((i == 0) || (*resPtr)[i - 1].size() == row.size())
        resPtr->push(row);
    else
        throw ValueError("All rows in matrix must be the same size");

    return res;
}

ObPtr dotProduct(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 2)
        throw TypeError("'**' takes 2 args, but " +
                std::to_string(args.size()) + " were given");
    auto left = args[0]->as<Matrix>();
    auto right = args[1]->as<Matrix>();
    if (!left || !right)
        throw TypeError("'**' required 2 matrices");
    return left->dot(*right);
}

ObPtr eye(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'**' takes 1 args, but " +
                std::to_string(args.size()) + " were given");
    auto arg = args[0]->as<Integer>();
    if (!arg)
        throw TypeError("'eye' argument must be an <Integer> type");
    auto res = newMatrix();
    auto resm = res->as<Matrix>();
    for (int i = 0, sz = arg->value(); i < sz; i++) {
        resm->addEmptyRow();
        for (int j = 0; j < sz; j++) {
            (*resm)[i].push(i == j ? 1 : 0);
        }
    }
    return res;
}

ObPtr zeros(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'**' takes 1 args, but " +
                std::to_string(args.size()) + " were given");
    auto arg = args[0]->as<Integer>();
    if (!arg)
        throw TypeError("'eye' argument must be an <Integer> type");
    auto res = newMatrix();
    auto resm = res->as<Matrix>();
    for (int i = 0, sz = arg->value(); i < sz; i++) {
        resm->addEmptyRow();
        for (int j = 0; j < sz; j++)
            (*resm)[i].push(0);
    }
    return res;
}

ObPtr randomMatrixFloat(std::vector<ObPtr> args, const Env& env) {
    if (args.size() < 1 || args.size() > 4)
        throw TypeError("'randmat' args (m [n = m] [min = 0] [max = INT_MAX]), but " +
                std::to_string(args.size()) + " were given");
    int m, n, min = 0, max = INT_MAX;
    auto arg1 = args[0]->as<Integer>();
    if (!arg1)
        throw TypeError("'randmat' arguments must be an <Integer> type");
    m = n = arg1->value();
    if (args.size() > 1) {
        auto arg2 = args[1]->as<Integer>();
        if (!arg2)
            throw TypeError("'randmat' arguments must be an <Integer> type");
        n = arg2->value();
        if (args.size() > 2) {
            auto arg3 = args[2]->as<Numeric>();
            if (!arg3)
                throw TypeError("'randmat' arguments must be an <Numeric> type");
            min = arg3->asFlt();
            if (args.size() > 3) {
                auto arg4 = args[3]->as<Numeric>();
                if (!arg1)
                    throw TypeError("'randmat' arguments must be an <Numeric> type");
                max = arg4->asFlt();
            }
        }
    }
    if (max < min)
        throw ValueError("Max value < min value");

    auto res = newMatrix();
    auto resm = res->as<Matrix>();
    srand(time(nullptr));
    for (int i = 0; i < m; i++) {
        resm->addEmptyRow();
        for (int j = 0; j < n; j++) {
            (*resm)[i].push(min + double(rand()) / (double(RAND_MAX)/(max - min)));
        }
    }
    return res;
}

ObPtr randomMatrix(std::vector<ObPtr> args, const Env& env) {
    if (args.size() < 1 || args.size() > 4)
        throw TypeError("'randmat' args (m [n = m] [min = 0] [max = INT_MAX]), but " +
                std::to_string(args.size()) + " were given");
    int m, n, min = 0, max = INT_MAX;
    auto arg1 = args[0]->as<Integer>();
    if (!arg1)
        throw TypeError("'randmat' arguments must be an <Integer> type");
    m = n = arg1->value();
    if (args.size() > 1) {
        auto arg2 = args[1]->as<Integer>();
        if (!arg2)
            throw TypeError("'randmat' arguments must be an <Integer> type");
        n = arg2->value();
        if (args.size() > 2) {
            auto arg3 = args[2]->as<Integer>();
            if (!arg3)
                throw TypeError("'randmat' arguments must be an <Integer> type");
            min = arg3->value();
            if (args.size() > 3) {
                auto arg4 = args[3]->as<Integer>();
                if (!arg1)
                    throw TypeError("'randmat' arguments must be an <Integer> type");
                max = arg4->value();
            }
        }
    }
    if (max < min)
        throw ValueError("Max value < min value");

    auto res = newMatrix();
    auto resm = res->as<Matrix>();
    srand(time(nullptr));
    for (int i = 0; i < m; i++) {
        resm->addEmptyRow();
        for (int j = 0; j < n; j++) {
            (*resm)[i].push(rand() % (max - min) + min);
        }
    }
    return res;
}

ObPtr transposeMatrix(std::vector<ObPtr> args, const Env& env) {
    if (args.size() != 1)
        throw TypeError("'**' takes 1 args, but " +
                std::to_string(args.size()) + " were given");
    auto arg = args[0]->as<Matrix>();
    if (!arg)
        throw TypeError("'eye' argument must be an <Integer> type");
    int m = arg->m();
    int n = arg->n();
    auto res = newMatrix();
    auto resm = res->as<Matrix>();
    for (int i = 0; i < n; i++) {
        resm->addEmptyRow();
        for (int j = 0; j < m; j++)
            (*resm)[i].push((*arg)[j][i]);
    }
    return res;
}
