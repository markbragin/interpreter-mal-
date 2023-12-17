#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>

#include "core.h"
#include "environment.h"
#include "linenoise.hpp"
#include "repl.h"


const char* HISTORY_PATH = "history.txt";


int main() {
    linenoise::LoadHistory(HISTORY_PATH);

    Env coreEnv;
    for (auto& e : buildNamespace())
        coreEnv.set(e.first, e.second);

    Env replEnv(&coreEnv);

    std::string prompt = CYAN + ">>> " + RESET;
    std::string line;

    for(;;) {
        auto status = linenoise::Readline(prompt.c_str(), line);
        if (status)
            break;
        std::cout << rep(line, replEnv) << std::endl;
        linenoise::AddHistory(line.c_str());
    }

    linenoise::SaveHistory(HISTORY_PATH);

    return 0;
}
