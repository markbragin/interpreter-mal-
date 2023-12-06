#include <algorithm>
#include <iomanip>
#include <limits>
#include <math.h>
#include <sstream>
#include <vector>

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
    const Symbol* right = rhs.as<Symbol>();
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
    if (rhs.as<Integer>())
        l = rhs.as<Integer>()->value();
    else if (rhs.as<Float>())
        r = rhs.as<Integer>()->value();
    else
        return newFalse();
    return newBool(fabs(l - r) <= EPSILON);
}

ObPtr Integer::operator<(const Object& rhs) const {
    if (rhs.as<Integer>())
        return newBool(int_ < rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newBool(int_ < rhs.as<Float>()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator<=(const Object& rhs) const {
    if (rhs.as<Integer>())
        return newBool(int_ <= rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newBool(int_ <= rhs.as<Float>()->value());
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
    if (rhs.as<Integer>())
        return newInteger(int_ + rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newFloat(int_ + rhs.as<Float>()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator-(const Object& rhs) const {
    if (rhs.as<Integer>())
        return newInteger(int_ - rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newFloat(int_ - rhs.as<Float>()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator*(const Object& rhs) const {
    if (rhs.as<Integer>())
        return newInteger(int_ * rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newFloat(int_ * rhs.as<Float>()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Integer::operator/(const Object& rhs) const {
    if (rhs.as<Integer>()) {
        int rval = rhs.as<Integer>()->value();
        if (rval == 0)
            throw DivisionByZero(repr() + " " + rhs.repr());
        return newFloat(double(int_) / rval);
    } else if (rhs.as<Float>()) {
        double rval = rhs.as<Float>()->value();
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
    if (rhs.as<Integer>())
        r = rhs.as<Integer>()->value();
    else if (rhs.as<Float>())
        r = rhs.as<Float>()->value();
    else
        return newFalse();
    return newBool(fabs(l - r) <= EPSILON);
}

ObPtr Float::operator<(const Object& rhs) const {
    if (rhs.as<Integer>())
        return newBool(float_ < rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newBool(float_ < rhs.as<Float>()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator<=(const Object& rhs) const {
    if (rhs.as<Integer>())
        return newBool(float_ <= rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newBool(float_ <= rhs.as<Float>()->value());
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
    if (rhs.as<Integer>())
        return newFloat(float_ + rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newFloat(float_ + rhs.as<Float>()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator-(const Object& rhs) const {
    if (rhs.as<Integer>())
        return newFloat(float_ - rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newFloat(float_ - rhs.as<Float>()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator*(const Object& rhs) const {
    if (rhs.as<Integer>())
        return newFloat(float_ * rhs.as<Integer>()->value());
    else if (rhs.as<Float>())
        return newFloat(float_ * rhs.as<Float>()->value());
    else
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));
}

ObPtr Float::operator/(const Object& rhs) const {
    if (rhs.as<Integer>()) {
        int rval = rhs.as<Integer>()->value();
        if (rval == 0)
            throw DivisionByZero(repr() + " " + rhs.repr());
        return newFloat(float_ / rval);
    } else if (rhs.as<Float>()) {
        double rval = rhs.as<Integer>()->value();
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
    const Sequence* right = rhs.as<Sequence>();
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
    if (rhs.as<HashMap>())
        return newBool(map_ == rhs.as<HashMap>()->map_);
    return newFalse();
}

// Bool
Bool::~Bool() { };

ObPtr Bool::operator==(const Object& rhs) const {
    if (rhs.as<Bool>())
        return newBool((bool(*this) == bool(rhs)));
    return newFalse();
}

// Nil

ObPtr Nil::operator==(const Object& rhs) const {
    if (rhs.as<Nil>())
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
    const Nvector* right = rhs.as<Nvector>();
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
    const Nvector* right = rhs.as<Nvector>();
    if (!right)
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));

    ObPtr res = newNvector();
    if (size() != right->size())
        throw ValueError("NVectors must me the same size");

    for (int i = 0; i < size(); i++)
        res->as<Nvector>()->push(data_.at(i) + right->at(i));
    return res;
}

ObPtr Nvector::operator-(const Object& rhs) const {
    const Nvector* right = rhs.as<Nvector>();
    if (!right)
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));

    ObPtr res = newNvector();
    if (size() != right->size())
        throw ValueError("NVectors must me the same size");

    for (int i = 0; i < size(); i++)
        res->as<Nvector>()->push(data_.at(i) - right->at(i));
    return res;
}

ObPtr Nvector::operator*(const Object& rhs) const {
    const Nvector* right = rhs.as<Nvector>();
    if (!right)
        throw TypeError(getInvalidOperandsTypeMsg(*this, rhs));

    ObPtr res = newNvector();
    if (size() != right->size())
        throw ValueError("NVectors must me the same size");

    for (int i = 0; i < size(); i++)
        res->as<Nvector>()->push(data_.at(i) * right->at(i));
    return res;
}

ObPtr Nvector::operator/(const Object& rhs) const {
    const Nvector* right = rhs.as<Nvector>();
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
        res->as<Nvector>()->push(numer / denom);
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
    const Matrix* right = rhs.as<Matrix>();
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
    const Matrix* right = rhs.as<Matrix>();
    if (right->m() != m() || right->n() != n())
        return newFalse();
    ObPtr res = newMatrix();
    Matrix* resM = res->as<Matrix>();
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
    Matrix* resM = res->as<Matrix>();
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

