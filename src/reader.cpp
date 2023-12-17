#include <vector>
#include <string>
#include <boost/regex.hpp>

#include "exceptions.h"
#include "reader.h"
#include "types.h"


std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> result;
    boost::smatch match;

    auto itBegin = line.cbegin();
    auto itEnd = line.cend();

    while (itBegin != itEnd) {
        if (boost::regex_search(itBegin, itEnd, match, TOKENS_REGEXP)) {
            std::string token = match[1].str();
            result.push_back(token);
            itBegin += match[0].str().size();
        }
    }
    return result;
}

ObPtr readStr(const std::string& line) {
    std::vector<std::string> tokens = tokenize(line);
    Reader reader = Reader(tokens);
    return readForm(reader);
}

ObPtr readForm(Reader& reader) {
    if (reader.eof())
        return newNil();

    std::string token = reader.peek();
    switch (token[0]) {
        case '(':
            reader.next();
            return readList(reader);
        case '[':
            reader.next();
            return readVector(reader);
        case '{':
            reader.next();
            return readHashMap(reader);
        case '\'':
            return readQuotedValue(reader);
        case '`':
            return readQuotedValue(reader);
        case '~':
            return readQuotedValue(reader);
        case '@':
            return readQuotedValue(reader);
        default:
            return readAtom(reader);
    }
}

ObPtr readList(Reader& reader) {
    ObPtr list = newList();
    while (!reader.eof()) {
        if (reader.peek()[0] == ')') {
            reader.next();
            return list;
        }
        else
            list->as<List>()->push(readForm(reader));
    }
    if (reader.eof())
        throw SyntaxError("'(' never closed");
    return list;
}

ObPtr readVector(Reader& reader) {
    ObPtr vector = newVector();
    while (!reader.eof()) {
        if (reader.peek()[0] == ']') {
            reader.next();
            return vector;
        }
        else
            vector->as<Vector>()->push(readForm(reader));
    }
    if (reader.eof())
        throw SyntaxError("']' never closed");
    return vector;
}

ObPtr readAtom(Reader& reader) {
    std::string token = reader.next();
    boost::smatch match;
    if (boost::regex_search(token, match, rationalRegex)) {
        try {
            long long num = std::stoll(match[1].str());
            long long den = std::stoll(match[2].str());
            return newRational(num, den);
        } catch (const std::out_of_range& e) {
            throw OutOfRange(token + " too long");
        }
    }
    else if (boost::regex_match(token, floatRegex))
        return newFloat(std::stod(token));
    else if (boost::regex_match(token, intRegex)) {
        try {
            return newInteger(std::stoll(token));
        }
        catch (const std::out_of_range& e) {
            throw OutOfRange(token + " too long");
        }
    }
    return newSymbol(token);
}

ObPtr readHashMap(Reader& reader) {
    ObPtr map = newHashMap();
    while (!reader.eof()) {
        if (reader.peek()[0] == '}') {
            reader.next();
            return map;
        } else {
            ObPtr key = readForm(reader);
            ObPtr value = readForm(reader);
            map->as<HashMap>()->set(key, value);
        }
    }
    if (reader.eof())
        throw SyntaxError("'}' never closed");
    return map;
}

ObPtr readQuotedValue(Reader& reader) {
    std::string token = reader.next();
    switch (token[0]) {
        case '\'': {
            ObPtr list = newList();
            list->as<List>()->push(newSymbol("quote"));
            list->as<List>()->push(readForm(reader));
            return list;
        }
        case '`': {
            ObPtr list = newList();
            list->as<List>()->push(newSymbol("quasiquote"));
            list->as<List>()->push(readForm(reader));
            return list;
        }
        case '~': {
            if (token.length() > 1 && token[1] == '@') {
                ObPtr list = newList();
                list->as<List>()->push(newSymbol("splice-unquote"));
                list->as<List>()->push(readForm(reader));
                return list;
            }
            else {
                ObPtr list = newList();
                list->as<List>()->push(newSymbol("unquote"));
                list->as<List>()->push(readForm(reader));
                return list;
            }
        }
        case '@': {
            ObPtr list = newList();
            list->as<List>()->push(newSymbol("deref"));
            list->as<List>()->push(readForm(reader));
            return list;
        }
        default:
            throw SyntaxError("Bad quote");
    }
}
