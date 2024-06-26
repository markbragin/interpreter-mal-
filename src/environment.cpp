#include "environment.h"
#include "exceptions.h"


Env::Env(const Env* outer, ObPtr binds, ObPtr exprs) : outer_(outer) {
    if (!(binds->is<List>() && exprs->is<List>()))
        throw TypeError(binds->repr() + " and " + exprs->repr() +
                " must be lists");
    List* bPtr = binds->as<List>();
    List* ePtr = exprs->as<List>();
    if (bPtr->size() != ePtr->size())
        throw TypeError(binds->repr() + " and " + exprs->repr() +
                " must be the same size");
    for (int i = 0; i < bPtr->size(); i++) {
        ObPtr key = (*bPtr).at(i);
        ObPtr value = (*ePtr).at(i);
        set(key, value);
    }
}

const Env* Env::find(const ObPtr& key) const {
    if (data_.has(key))
        return this;
    else if (outer_)
        return outer_->find(key);
    else
        return nullptr;
}

ObPtr Env::get(const ObPtr& key) const {
    const Env* env = find(key);
    if (env)
        return env->data_.get(key);
    else throw NotFound(key->repr());
}
