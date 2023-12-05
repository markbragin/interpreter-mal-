#include <algorithm>
#include <iomanip>
#include <limits>
#include <math.h>
#include <sstream>
#include <vector>

#include "exceptions.h"
#include "types.h"
#include "utils.h"


ObPtr newSymbol(std::string val) {
    return ObPtr(new Symbol(val));
}

ObPtr newInteger(long long val) {
    return ObPtr(new Integer(val));
}

ObPtr newFloat(double val) {
    return ObPtr(new Float(val));
}

ObPtr newList() {
    return ObPtr(new List);
}

ObPtr newList(SequenceConstIter begin, SequenceConstIter end) {
    return ObPtr(new List(begin, end));
}

ObPtr newVector() {
    return ObPtr(new Vector);
}

ObPtr newVector(SequenceConstIter begin, SequenceConstIter end) {
    return ObPtr(new Vector(begin, end));
}

ObPtr newFn(Function ptr) {
    return ObPtr(new Fn(ptr));
}

ObPtr newBool(bool expr) {
    return expr ? newTrue() : newFalse();
}

ObPtr newTrue() {
    return ObPtr(new True);
}

ObPtr newFalse() {
    return ObPtr(new False);
}

ObPtr newNil() {
    return ObPtr(new Nil);
}

ObPtr newHashMap() {
    return ObPtr(new HashMap);
}

ObPtr newNvector() {
    return ObPtr(new Nvector);
}

ObPtr newMatrix() {
    return ObPtr(new Matrix);
}

Sequence* Object::asSequence() {
    Sequence* ptr = dynamic_cast<Sequence*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Sequence>");
    return ptr;
}

List* Object::asList() {
    List* ptr = dynamic_cast<List*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <List>");
    return ptr;
}

Vector* Object::asVector() {
    Vector* ptr = dynamic_cast<Vector*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Vector>");
    return ptr;
};

Symbol* Object::asSymbol() {
    Symbol* ptr = dynamic_cast<Symbol*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Symbol>");
    return ptr;
}

Numeric* Object::asNumeric() {
    Numeric* ptr = dynamic_cast<Numeric*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Numeric>");
    return ptr;
}

Integer* Object::asInteger() {
    Integer* ptr = dynamic_cast<Integer*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Integer>");
    return ptr;
}

Float* Object::asFloat() {
    Float* ptr = dynamic_cast<Float*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Float>");
    return ptr;
}

HashMap* Object::asHashMap() {
    HashMap* ptr = dynamic_cast<HashMap*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <HashMap>");
    return ptr;
}

Fn* Object::asFn() {
    Fn* ptr = dynamic_cast<Fn*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Function>");
    return ptr;
}

Bool* Object::asBool() {
    Bool* ptr = dynamic_cast<Bool*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Bool>");
    return ptr;
}

Nil* Object::asNil() {
    Nil* ptr = dynamic_cast<Nil*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Nil>");
    return ptr;
}

Nvector* Object::asNvector() {
    Nvector* ptr = dynamic_cast<Nvector*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Nvector>");
    return ptr;
}

Matrix* Object::asMatrix() {
    Matrix* ptr = dynamic_cast<Matrix*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Matrix>");
    return ptr;
}


const Sequence* Object::asSequence() const {
    const Sequence* ptr = dynamic_cast<const Sequence*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Sequence>");
    return ptr;
}

const List* Object::asList() const {
    const List* ptr = dynamic_cast<const List*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <List>");
    return ptr;
}

const Vector* Object::asVector() const {
    const Vector* ptr = dynamic_cast<const Vector*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Vector>");
    return ptr;
};

const Symbol* Object::asSymbol() const {
    const Symbol* ptr = dynamic_cast<const Symbol*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Symbol>");
    return ptr;
}

const Numeric* Object::asNumeric() const {
    const Numeric* ptr = dynamic_cast<const Numeric*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Numeric>");
    return ptr;
}

const Integer* Object::asInteger() const {
    const Integer* ptr = dynamic_cast<const Integer*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Integer>");
    return ptr;
}

const Float* Object::asFloat() const {
    const Float* ptr = dynamic_cast<const Float*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Float>");
    return ptr;
}

const HashMap* Object::asHashMap() const {
    const HashMap* ptr = dynamic_cast<const HashMap*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <HashMap>");
    return ptr;
}

const Fn* Object::asFn() const {
    const Fn* ptr = dynamic_cast<const Fn*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Function>");
    return ptr;
}

const Bool* Object::asBool() const {
    const Bool* ptr = dynamic_cast<const Bool*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Bool>");
    return ptr;
}

const Nil* Object::asNil() const {
    const Nil* ptr = dynamic_cast<const Nil*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Nil>");
    return ptr;
}

const Nvector* Object::asNvector() const {
    const Nvector* ptr = dynamic_cast<const Nvector*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Nvector>");
    return ptr;
}

const Matrix* Object::asMatrix() const {
    const Matrix* ptr = dynamic_cast<const Matrix*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " not a <Matrix>");
    return ptr;
}


bool Object::isSequence() const {
    return asSequence();
}

bool Object::isList() const {
    return asList();
}

bool Object::isVector() const {
    return asVector();
};

bool Object::isSymbol() const {
    return asSymbol();
}

bool Object::isNumeric() const {
    return asNumeric();
}

bool Object::isInteger() const {
    return asInteger();
}

bool Object::isFloat() const {
    return asFloat();
}

bool Object::isHashMap() const {
    return asHashMap();
}

bool Object::isFn() const {
    return asFn();
}

bool Object::isBool() const {
    return asBool();
}

bool Object::isNil() const {
    return asNil();
}

bool Object::isNvector() const {
    return asNvector();
}


ObPtr Object::operator==(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Object::operator!=(const Object& rhs) const {
    return !*(*this == rhs);
}

ObPtr Object::operator<(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Object::operator<=(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Object::operator>(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Object::operator>=(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Object::operator+(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Object::operator-(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Object::operator*(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Object::operator/(const Object& rhs) const {
    throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

// Atom

// Atom::Atom() {};

Atom::~Atom() { };

// Symbol

std::string Symbol::repr() const {
    return name_;
}

ObPtr Symbol::operator==(const Object& rhs) const {
    const Symbol* right = rhs.asSymbol();
    if (right)
        return newBool(name_ == right->name_);
    else
        return newFalse();
}

// Numeric

Numeric::~Numeric() { };

// Integer

ObPtr Integer::operator==(const Object& rhs) const {
    double l = int_;
    double r;
    if (rhs.isInteger())
        l = rhs.asInteger()->value();
    else if (rhs.isFloat())
        r = rhs.asFloat()->value();
    else
        return newFalse();
    return newBool(fabs(l - r) <= EPSILON);
}

ObPtr Integer::operator<(const Object& rhs) const {
    if (rhs.isInteger())
        return newBool(int_ < rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newBool(int_ < rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator<=(const Object& rhs) const {
    if (rhs.isInteger())
        return newBool(int_ <= rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newBool(int_ <= rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator>(const Object& rhs) const {
    return !*(*this <= rhs);
}

ObPtr Integer::operator>=(const Object& rhs) const {
    return !*(*this < rhs);
}

std::string Integer::repr() const {
    return std::to_string(int_);
}

ObPtr Integer::operator+(const Object& rhs) const {
    if (rhs.isInteger())
        return newInteger(int_ + rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newFloat(int_ + rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator-(const Object& rhs) const {
    if (rhs.isInteger())
        return newInteger(int_ - rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newFloat(int_ - rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator*(const Object& rhs) const {
    if (rhs.isInteger())
        return newInteger(int_ * rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newFloat(int_ * rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator/(const Object& rhs) const {
    if (rhs.isInteger()) {
        int rval = rhs.asInteger()->value();
        if (rval == 0)
            throw DivisionByZero(repr() + " " + rhs.repr());
        return newFloat(int_ / rval);
    } else if (rhs.isFloat()) {
        double rval = rhs.asFloat()->value();
        if (rval < EPSILON)
            throw DivisionByZero(repr() + " " + rhs.repr());
        return newFloat(int_ / rval);
    } else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

// Float

ObPtr Float::operator==(const Object& rhs) const {
    double l = float_;
    double r;
    if (rhs.isInteger())
        r = rhs.asInteger()->value();
    else if (rhs.isFloat())
        r = rhs.asFloat()->value();
    else
        return newFalse();
    return newBool(fabs(l - r) <= EPSILON);
}

ObPtr Float::operator<(const Object& rhs) const {
    if (rhs.isInteger())
        return newBool(float_ < rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newBool(float_ < rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator<=(const Object& rhs) const {
    if (rhs.isInteger())
        return newBool(float_ <= rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newBool(float_ <= rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator>(const Object& rhs) const {
    return !*(*this <= rhs);
}

ObPtr Float::operator>=(const Object& rhs) const {
    return !*(*this < rhs);
}

std::string Float::repr() const {
    return std::to_string(float_);
}

ObPtr Float::operator+(const Object& rhs) const {
    if (rhs.isInteger())
        return newFloat(float_ + rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newFloat(float_ + rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator-(const Object& rhs) const {
    if (rhs.isInteger())
        return newFloat(float_ - rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newFloat(float_ - rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator*(const Object& rhs) const {
    if (rhs.isInteger())
        return newFloat(float_ * rhs.asInteger()->value());
    else if (rhs.isFloat())
        return newFloat(float_ * rhs.asFloat()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator/(const Object& rhs) const {
    if (rhs.isInteger()) {
        int rval = rhs.asInteger()->value();
        if (rval == 0)
            throw DivisionByZero(repr() + " " + rhs.repr());
        return newFloat(float_ / rval);
    } else if (rhs.isFloat()) {
        double rval = rhs.asInteger()->value();
        if (rval < EPSILON)
            throw DivisionByZero(repr() + " " + rhs.repr());
        return newFloat(float_ / rval);
    }
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

// Sequence

Sequence::~Sequence() { };

// List

void List::push(ObPtr valuePtr) {
    vector_.push_back(valuePtr);
}

std::string List::repr() const {
    if (vector_.empty())
        return "()";
    std::string out = "(";
    for (auto &val : vector_) {
        out.append(val->repr());
        out.append(" ");
    }
    out[out.size() - 1] = ')';
    return out;
}

// Vector

void Vector::push(ObPtr valuePtr) {
    vector_.push_back(valuePtr);
}

std::string Vector::repr() const {
    if (vector_.empty())
        return "[]";
    std::string out = "[";
    for (auto &val : vector_) {
        out.append(val->repr());
        out.append(" ");
    }
    out[out.size() - 1] = ']';
    return out;
}

ObPtr Sequence::operator==(const Object& rhs) const {
    const Sequence* right = dynamic_cast<const Sequence*>(&rhs);
    if (right) {
        int lsize = size();
        int rsize = right->size();
        if (lsize != rsize)
            return newFalse();
        else {
            for (int i = 0; i < std::min(lsize, rsize); i++)
                if (*(*at(i) != *right->at(i)))
                    return newFalse();
        }
        return newTrue();
    } else {
        return newFalse();
    }
}

// HashMap

std::string HashMap::repr() const {
    if (map_.empty())
        return "{}";
    std::string out = "{";
    for (auto &pair : map_) {
        out.append(pair.first->repr());
        out.append(" ");
        out.append(pair.second->repr());
        out.append(" ");
    }
    out[out.size() - 1] = '}';
    return out;
}

void HashMap::set(ObPtr key, ObPtr val) {
    map_[key] = val;
}

ObPtr HashMap::get(ObPtr key) {
    if (map_.find(key) != map_.end())
        return map_.at(key);
    return nullptr;
}

ObPtr HashMap::get(ObPtr key) const {
    if (map_.find(key) != map_.end())
        return map_.at(key);
    return nullptr;
}

ObPtr HashMap::operator==(const Object& rhs) const {
    if (rhs.isHashMap())
        return newBool(map_ == dynamic_cast<const HashMap&>(rhs).map_);
    return newFalse();
}

// Bool
Bool::~Bool() { };

ObPtr Bool::operator==(const Object& rhs) const {
    if (rhs.isBool())
        return newBool((bool(*this) == bool(rhs)));
    return newFalse();
}

// Nil

ObPtr Nil::operator==(const Object& rhs) const {
    if (rhs.isNil())
        return newTrue();
    return newFalse();
}

// Nvector


std::string Nvector::repr() const {
    if (data_.empty())
        return "[]";
    std::string out;
    out += '[';
    for (auto& e : data_)
        out += std::to_string(e) + " ";
    out[out.size() - 1] = ']';
    return out;
}

ObPtr Nvector::operator==(const Object& rhs) const {
    const Nvector* right = rhs.asNvector();
    if (!right)
        return newFalse();
    if (size() != right->size())
        return newFalse();
    for (int i = 0; i < size(); i++) 
        if (fabs(data_.at(i) - right->at(i)) < EPSILON)
            return newFalse();
    return newTrue();
}

ObPtr Nvector::operator+(const Object& rhs) const {
    const Nvector* right = rhs.asNvector();
    if (!right)
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));

    ObPtr res = newNvector();
    if (size() != right->size())
        throw ValueError("NVectors must me the same size");

    for (int i = 0; i < size(); i++)
        res->asNvector()->push(data_.at(i) + right->at(i));
    return res;
}

ObPtr Nvector::operator-(const Object& rhs) const {
    const Nvector* right = rhs.asNvector();
    if (!right)
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));

    ObPtr res = newNvector();
    if (size() != right->size())
        throw ValueError("NVectors must me the same size");

    for (int i = 0; i < size(); i++)
        res->asNvector()->push(data_.at(i) - right->at(i));
    return res;
}

ObPtr Nvector::operator*(const Object& rhs) const {
    const Nvector* right = rhs.asNvector();
    if (!right)
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));

    ObPtr res = newNvector();
    if (size() != right->size())
        throw ValueError("NVectors must me the same size");

    for (int i = 0; i < size(); i++)
        res->asNvector()->push(data_.at(i) * right->at(i));
    return res;
}

ObPtr Nvector::operator/(const Object& rhs) const {
    const Nvector* right = rhs.asNvector();
    if (!right)
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));

    ObPtr res = newNvector();
    if (size() != right->size())
        throw ValueError("NVectors must me the same size");

    for (int i = 0; i < size(); i++) {
        double numer = data_.at(i);
        double denom = right->at(i);
        if (denom < EPSILON)
            throw DivisionByZero(std::to_string(numer) + " "
                    + std::to_string(denom));
        res->asNvector()->push(numer / denom);
    }
    return res;
}

// Matrix

std::string Matrix::typeRepr() const {
    return "Matrix(" + std::to_string(m()) + "," + std::to_string(n()) + ")";
};

std::string Matrix::repr() const {
	unsigned maxWidthPerCol[n()];
    std::stringstream out;

    out << '[';
	for (int j = 0; j < n(); j++)
		maxWidthPerCol[j] = maxWidthInCol(*this, j);

    for (int i = 0; i < m(); i++) {
        for (int j = 0; j < n(); j++)
            out << std::setw(maxWidthPerCol[j]) << data_[i][j] << " ";
        out << "\n ";
    }
    std::string res = out.str();
    res.erase(res.size() - 3);
    res.append("]");
    return res;
};


ObPtr Matrix::operator==(const Object& rhs) const {
    const Matrix* right = rhs.asMatrix();
    if (right->m() != m() || right->n() != n())
        return newFalse();
    for (int i = 0; i < m(); i++) {
        for (int j = 0; j < n(); j++) {
            if (fabs(data_[i][j] - (*right)[i][j]) > EPSILON)
                return newFalse();
        }
    }
    return newTrue();
}

ObPtr Matrix::operator+(const Object& rhs) const {
    const Matrix* right = rhs.asMatrix();
    if (right->m() != m() || right->n() != n())
        return newFalse();
    ObPtr res = newMatrix();
    Matrix* resM = res->asMatrix();
    for (int i = 0; i < m(); i++) {
        resM->addEmptyRow();
        for (int j = 0; j < n(); j++)
            (*resM)[i].push(data_[i][j] + (*right)[i][j]);
    }
    return res;
}

ObPtr Matrix::dot(const Matrix& rhs) const {
    if (n() != rhs.m())
        throw ValueError("Matrix sizes don't match");
    ObPtr res = newMatrix();
    Matrix* resM = res->asMatrix();
    for (int i = 0; i < m(); i++) {
        resM->addEmptyRow();
        for (int j = 0; j < rhs.n(); j++) {
            double prod = 0;
            for (int k = 0; k < n(); k++)
                prod += data_[i][k] * rhs[k][j];
            (*resM)[i].push(prod);
        }
    }
    return res;
}

// Misc

std::string getInvalidOperandsTypeMsg(const Object& lhs, const Object& rhs) {
    std::string lhsType = lhs.typeRepr();
    std::string rhsType = rhs.typeRepr();
    std::string msg = "Invalid operands type: " + lhsType + " @ " + rhsType;
    return msg;
}

