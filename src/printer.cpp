#include <string>

#include "printer.h"


std::string prStr(ObPtr value) {
    if (value)
        return value->repr();
    return "";
}
