#ifndef _READER_H_
#define _READER_H_

#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>

#include "types.h"


// static const boost::regex WHITESPACES = boost::regex("[\\s,]*");

// static const boost::regex VAlID_TOKENS_REGEXP[] = {
//     boost::regex("~@"),
//     boost::regex("[\\[\\]{}()'`~^@]"),
//     boost::regex("\"(?:\\\\.|[^\\\\\"])*\""),
//     boost::regex(";.*"),
//     boost::regex("[^\\s\\[\\]{}('\"`,;)]*")
// };

static const boost::regex intRegex("^[-+]?\\d+$");
static const boost::regex floatRegex("[+-]?([0-9]+[.]([0-9]*)?|[.][0-9]+)");

static const boost::regex TOKENS_REGEXP(
    "[\\s,]"
    "*(~@|[\\[\\]{}()'`~^@]|"
    "\"(?:\\\\.|[^\\\\\"])*\"?|"
    // ";.*|"
    ";|"
    "[^\\s\\[\\]{}('\"`,;)]*)"
);


class Reader
{
    std::vector<std::string> tokens_;
    unsigned pos_;
public:
    Reader(std::vector<std::string>& tokens) : tokens_(tokens), pos_(0) { };
    std::string& next() { return tokens_[pos_++]; }
    const std::string& peek() const { return tokens_[pos_]; }
    bool eof() const { return pos_ == tokens_.size(); }
};


ObPtr readStr(const std::string& line);

std::vector<std::string> tokenize(const std::string& line);

ObPtr readForm(Reader& reader);

ObPtr readList(Reader& reader);

ObPtr readVector(Reader& reader);

ObPtr readAtom(Reader& reader);

ObPtr readHashMap(Reader& reader);

ObPtr readQuotedValue(Reader& reader);


#endif
