#ifndef _TYPES_H_
#define _TYPES_H_

#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "exceptions.h"


class Object;
class Symbol;
class Numeric;
class Integer;
class Float;
class Rational;
class Sequence;
class List;
class Vector;
class HashMap;
class Fn;
class Bool;
class True;
class False;
class Nil;
class Nvector;
class Matrix;

class Env;

typedef std::shared_ptr<Object> ObPtr;
typedef std::vector<ObPtr>::iterator SequenceIter;
typedef std::vector<ObPtr>::const_iterator SequenceConstIter;
typedef std::function<ObPtr(std::vector<ObPtr>, const Env&)> Function;

ObPtr newSymbol(std::string val);
ObPtr newInteger(long long val);
ObPtr newFloat(double val);
ObPtr newRational(int num, int den);
ObPtr newList();
ObPtr newList(SequenceConstIter begin, SequenceConstIter end);
ObPtr newVector();
ObPtr newVector(SequenceConstIter begin, SequenceConstIter end);
ObPtr newFn(Function ptr);
ObPtr newBool(bool expr);
ObPtr newTrue();
ObPtr newFalse();
ObPtr newNil();
ObPtr newHashMap();
ObPtr newNvector();
ObPtr newMatrix();

std::string getInvalidOperandsTypeMsg(const Object& lhs, const Object& rhs);

const static double EPSILON = std::numeric_limits<double>::epsilon();


class Object {
public:
    template<typename T>
    T* as();

    template<typename T>
    const T* as() const;

    template<typename T>
    bool is() const;

    virtual std::string typeRepr() const = 0;
    virtual std::string repr() const = 0;
    static std::string typeRpr() { return "<Object>"; };

    virtual operator bool() const = 0;
    virtual ObPtr operator!() const { return newBool(!bool(*this)); };

    virtual ObPtr operator==(const Object& rhs) const;
    virtual ObPtr operator!=(const Object& rhs) const;
    virtual ObPtr operator<(const Object& rhs) const;
    virtual ObPtr operator<=(const Object& rhs) const;
    virtual ObPtr operator>(const Object& rhs) const;
    virtual ObPtr operator>=(const Object& rhs) const;

    virtual ObPtr operator+(const Object& rhs) const;
    virtual ObPtr operator-(const Object& rhs) const;
    virtual ObPtr operator*(const Object& rhs) const;
    virtual ObPtr operator/(const Object& rhs) const;
};

template<typename T>
T* Object::as() {
    T* ptr = dynamic_cast<T*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " is not a " + T::typeRpr() );
    return ptr;
}

template<typename T>
const T* Object::as() const {
    const T* ptr = dynamic_cast<const T*>(this);
    if (!ptr)
        throw TypeError(this->repr() + " is not a " + T::typeRpr() );
    return ptr;
}

template<typename T>
bool Object::is() const {
    auto* ptr = dynamic_cast<const T*>(this);
    return ptr;
}


class Atom : public Object {
public:
    virtual ~Atom() = 0;
    static std::string typeRpr() { return "<Atom>"; };
};

class Symbol : public Atom {
    std::string name_;
public:
    Symbol(const std::string& str) : name_(str) { };

    std::string typeRepr() const { return "<Symbol>"; }
    std::string repr() const;
    static std::string typeRpr() { return "<Symbol>"; };

    operator bool() const { return !name_.empty(); }

    ObPtr operator==(const Object& rhs) const;
    bool matches(const std::string& val) { return name_ == val; }
};


class Numeric : public Atom {
public:
    virtual ~Numeric() = 0;
    static std::string typeRpr() { return "<Numeric>"; };
    virtual double asFlt() const = 0;
};


class Integer : public Numeric {
    long long int_;
public:
    Integer(long long val) : int_(val) { };

    std::string typeRepr() const { return "<Integer>"; }
    std::string repr() const;
    static std::string typeRpr() { return "<Integer>"; };

    long long value() const { return int_; }
    virtual double asFlt() const { return int_; };

    operator bool() const { return int_ != 0; }

    ObPtr operator==(const Object& rhs) const;
    ObPtr operator+(const Object& rhs) const;
    ObPtr operator-(const Object& rhs) const;
    ObPtr operator*(const Object& rhs) const;
    ObPtr operator/(const Object& rhs) const;

    ObPtr operator<(const Object& rhs) const;
    ObPtr operator<=(const Object& rhs) const;
    ObPtr operator>(const Object& rhs) const;
    ObPtr operator>=(const Object& rhs) const;
};

class Float : public Numeric {
    double float_;
public:
    Float(double val) : float_(val) { };

    std::string typeRepr() const { return "<Float>"; }
    std::string repr() const;
    static std::string typeRpr() { return "<Float>"; };

    double value() const { return float_; }
    virtual double asFlt() const { return float_; };

    operator bool() const { return float_ < EPSILON; }

    ObPtr operator==(const Object& rhs) const;
    ObPtr operator+(const Object& rhs) const;
    ObPtr operator-(const Object& rhs) const;
    ObPtr operator*(const Object& rhs) const;
    ObPtr operator/(const Object& rhs) const;

    ObPtr operator<(const Object& rhs) const;
    ObPtr operator<=(const Object& rhs) const;
    ObPtr operator>(const Object& rhs) const;
    ObPtr operator>=(const Object& rhs) const;
};

class Rational : public Numeric {
    long long numer_;
    long long denom_;
    void simplify_();
public:
    Rational(int num, int den);

    std::string typeRepr() const { return "<Rational>"; }
    std::string repr() const;
    static std::string typeRpr() { return "<Rational>"; };

    long long numer() const { return numer_; }
    long long denom() const { return denom_; }
    double value() const { return double(numer_) / denom_; }
    virtual double asFlt() const { return double(numer_) / denom_; };

    operator bool() const { return numer_ > 0; }

    ObPtr operator==(const Object& rhs) const;
    ObPtr operator+(const Object& rhs) const;
    ObPtr operator-(const Object& rhs) const;
    ObPtr operator*(const Object& rhs) const;
    ObPtr operator/(const Object& rhs) const;

    ObPtr operator<(const Object& rhs) const;
    ObPtr operator<=(const Object& rhs) const;
    ObPtr operator>(const Object& rhs) const;
    ObPtr operator>=(const Object& rhs) const;
};


class Sequence : public Object {
protected:
    std::vector<ObPtr> vector_;
public:
    Sequence() {};
    Sequence(SequenceConstIter begin, SequenceConstIter end)
        : vector_(begin, end) { }
    virtual ~Sequence() = 0;
    static std::string typeRpr() { return "<Sequence>"; };

    operator bool() const { return !vector_.empty(); }

    SequenceIter begin() { return vector_.begin(); };
    SequenceIter end() { return vector_.end(); };
    SequenceConstIter begin() const { return vector_.cbegin(); };
    SequenceConstIter end() const { return vector_.cend(); };

    ObPtr operator==(const Object& rhs) const;

    bool empty() const { return vector_.empty(); };
    int size() const { return vector_.size(); };
    ObPtr at(unsigned idx) const { return vector_.at(idx); };
};


class List : public Sequence {
public:
    List() { };
    List(SequenceConstIter begin, SequenceConstIter end)
        : Sequence(begin, end) { }

    std::string typeRepr() const { return "<List>"; }
    std::string repr() const;
    static std::string typeRpr() { return "<List>"; };

    void push(ObPtr valuePtr);
};


class Vector : public Sequence {
public:
    Vector() { };
    Vector(SequenceConstIter begin, SequenceConstIter end)
        : Sequence(begin, end) { }

    std::string typeRepr() const { return "<Vector>"; }
    std::string repr() const;
    static std::string typeRpr() { return "<Vector>"; };

    void push(ObPtr valuePtr);
};


class Fn : public Object {
    Function ptr_;
public:
    Fn(Function ptr) : ptr_(ptr) { };

    std::string typeRepr() const { return "<Function>"; }
    std::string repr() const { return std::string("#<Function>"); }
    static std::string typeRpr() { return "<Function>"; };

    operator bool() const { return bool(ptr_); }

    ObPtr operator()(std::vector<ObPtr> args, const Env& env) {
        return ptr_(args, env);
    }
};


class Bool : public Object {
public:
    virtual ~Bool() = 0;
    std::string typeRepr() const { return "<Bool>"; }
    static std::string typeRpr() { return "<Bool>"; };

    ObPtr operator==(const Object& rhs) const;
    virtual operator bool() const = 0;
};


class True : public Bool {
public:
    std::string repr() const { return "true"; }
    operator bool() const { return true; }
};


class False : public Bool {
public:
    std::string repr() const { return "false"; }
    operator bool() const { return false; }
};


class Nil : public Object {
public:
    std::string typeRepr() const { return "<Nil>"; }
    std::string repr() const { return "nil"; }
    static std::string typeRpr() { return "<Nil>"; };

    ObPtr operator==(const Object& rhs) const;
    operator bool() const { return false; }
};


struct ValueHash {
    std::size_t operator()(ObPtr val) const {
        return std::hash<std::string> {}(val->repr());
    }
};

struct HashMapPred {
    ObPtr operator()(ObPtr lhs, ObPtr rhs) const {
        return (*lhs) == (*rhs) ? ObPtr(new True) : ObPtr(new False);
    }
};

class HashMap : public Object {
    std::unordered_map<ObPtr, ObPtr, ValueHash, HashMapPred> map_;
public:
    std::string typeRepr() const { return "<HashMap>"; }
    std::string repr() const;
    static std::string typeRpr() { return "<HashMap>"; };

    void set(ObPtr key, ObPtr val);
    ObPtr get(ObPtr key);
    ObPtr get(ObPtr key) const;
    bool has(const ObPtr& val) const { return map_.find(val) != map_.end(); }

    operator bool() const { return !map_.empty(); }

    ObPtr operator==(const Object& rhs) const;

    auto begin() { return map_.begin(); };
    auto end() { return map_.end(); };
    auto cbegin() { return map_.cbegin(); };
    auto cend() { return map_.cend(); };
};

class Nvector : public Object {
    std::vector<double> data_;
public:
    std::string typeRepr() const { return "<Nvector>"; }
    std::string repr() const;
    static std::string typeRpr() { return "<Nvector>"; };

    operator bool() const { return !data_.empty(); }

    ObPtr operator==(const Object& rhs) const;

    ObPtr operator+(const Object& rhs) const;
    ObPtr operator-(const Object& rhs) const;
    ObPtr operator*(const Object& rhs) const;
    ObPtr operator/(const Object& rhs) const;

    double& operator[](unsigned idx) { return data_[idx]; };
    double operator[](unsigned idx) const { return data_.at(idx); };

    int size() const { return data_.size(); }
    double at(unsigned idx) const { return data_.at(idx); }
    void push(double val) { data_.push_back(val); }
    void clear() { data_.clear(); }
};


class Matrix : public Object
{
    std::vector<Nvector> data_;
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix(int m, int n);
public:
    Matrix() { };

    std::string typeRepr() const;
    std::string repr() const;
    static std::string typeRpr() { return "<Matrix>"; };

    operator bool() const { return !data_.empty(); }

    ObPtr operator==(const Object& rhs) const;
    // ObPtr operator<(const Object& rhs) const;
    // ObPtr operator<=(const Object& rhs) const;
    // ObPtr operator>(const Object& rhs) const;
    // ObPtr operator>=(const Object& rhs) const;

    ObPtr operator+(const Object& rhs) const;
    ObPtr operator-(const Object& rhs) const;
    ObPtr operator*(const Object& rhs) const;
    ObPtr operator/(const Object& rhs) const;

    inline int m() const { return data_.size(); };
    inline int n() const { return data_.empty() ? 0 : data_[0].size(); };

    Nvector& operator[](unsigned idx) { return data_[idx]; };
    const Nvector operator[](unsigned idx) const { return data_.at(idx); }

    void push(Nvector newRow) { data_.push_back(newRow); }
    void addEmptyRow() { data_.push_back({ }); }

    ObPtr dot(const Matrix& rhs) const;
    // double trace();
};

#endif
