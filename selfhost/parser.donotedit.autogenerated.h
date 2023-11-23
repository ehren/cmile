#pragma once

#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <cassert>
#include <compare> // for <=>
#include <thread>
#include <optional>

//#include <concepts>
//#include <ranges>
//#include <numeric>


#include "ceto.h"


#include <peglib.h>
;
#include <iostream>
;
#include "ast.donotedit.autogenerated.h"
;
    inline auto parse_test(const std::string&  grammar_path, const std::string&  str) -> void {
        const auto grammar_file = std::ifstream(grammar_path);
        auto grammar_buffer { std::stringstream() } ;
        grammar_buffer << ceto::mado(grammar_file)->rdbuf();
        const auto grammar_string = ceto::mado(grammar_buffer)->str();
        auto parser { peg::parser() } ;
        const auto ok = ceto::mado(parser)->load_grammar(ceto::mado(grammar_string)->c_str());
if (!ok) {
            throw std::runtime_error("failed to load grammar");
        }
        ceto::mado(parser)->parse(str);
    }

