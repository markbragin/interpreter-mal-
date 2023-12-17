#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include "types.h"


class Env{
public:
    HashMap data_;
    const Env *outer_;

public:
    Env() : outer_(nullptr) { };
    Env(const Env* outer) : outer_(outer) { };
    Env(const Env* outer, ObPtr binds, ObPtr exprs);
    const Env* find(const ObPtr& key) const;
    ObPtr get(const ObPtr& key) const;
    void set(const ObPtr& key, const ObPtr& value) { data_.set(key, value); }
    
    auto begin() { return data_.begin(); };
    auto end() { return data_.end(); };
    auto cbegin() const { return data_.cbegin(); };
    auto cend() const { return data_.cend(); };
};

#endif
