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
};

#endif
