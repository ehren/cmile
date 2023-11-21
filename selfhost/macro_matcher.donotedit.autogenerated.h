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

#include "ast.donotedit.autogenerated.h"
;
#include <typeinfo>
;
#include <ranges>
;
    inline auto macro_matches(const std::shared_ptr<const Node>&  node, const std::shared_ptr<const Node>&  pattern, const std::map<std::string,std::shared_ptr<const Node>>  params) -> std::optional<std::map<std::shared_ptr<const Node>,std::shared_ptr<const Node>>> {
        (((std::cout << "node: ") << ceto::mado(node)->repr()) << " pattern: ") << ceto::mado(pattern)->repr();
if ((std::dynamic_pointer_cast<const Identifier>(pattern) != nullptr)) {
            (std::cout << 1) << "\n";
            const auto search = ceto::mado(params)->find(ceto::mad(ceto::mado(pattern)->name())->value());
if (search != ceto::mado(params)->end()) {
                (std::cout << 2) << "\n";
                (std::cout << 3) << "\n";
                const auto matched_param = (search -> second);
if ((std::dynamic_pointer_cast<const Identifier>(matched_param) != nullptr)) {
                    (std::cout << 4) << "\n";
                    return std::map<std::shared_ptr<const Node>,std::shared_ptr<const Node>>{{pattern, node}};
                } else if (const auto typeop = std::dynamic_pointer_cast<const TypeOp>(matched_param)) {
                    const auto ast_name = ceto::mado(typeop)->rhs();
                    (std::cout << 5) << "\n";
if ((std::dynamic_pointer_cast<const Identifier>(ast_name) != nullptr)) {
                        (std::cout << 6) << "\n";
if ((ceto::mado(ast_name)->name() == "BinOp") && (std::dynamic_pointer_cast<const BinOp>(node) != nullptr)) {
                            (std::cout << 6) << "a\n";
                            return std::map<std::shared_ptr<const Node>,std::shared_ptr<const Node>>{{pattern, node}};
                        } else if (((ceto::mado(ast_name)->name() == "UnOp") && (std::dynamic_pointer_cast<const UnOp>(node) != nullptr))) {
                            (std::cout << 6) << "b\n";
                            return std::map<std::shared_ptr<const Node>,std::shared_ptr<const Node>>{{pattern, node}};
                        }
                        const auto node_class_name = class_name((&node) -> get());
if (node_class_name == ceto::mad(ceto::mado(ceto::mado(typeop)->rhs())->name())->value()) {
                            (std::cout << 7) << "\n";
                            return std::map<std::shared_ptr<const Node>,std::shared_ptr<const Node>>{{pattern, node}};
                        }
                    }
                }
            }
            (std::cout << 8) << "\n";
        }
        (std::cout << 9) << "\n";
if (typeid((*node)) != typeid((*pattern))) {
            (std::cout << 10) << "\n";
            return {};
        }
if (ceto::mado(ceto::mado(node)->args)->size() != ceto::mado(ceto::mado(pattern)->args)->size()) {
            (std::cout << 11) << "\n";
            return {};
        }
if ((ceto::mado(node)->func == nullptr) != (ceto::mado(pattern)->func == nullptr)) {
            (std::cout << 12) << "\n";
            return {};
        }
        (std::cout << 13) << "\n";
if (((ceto::mado(ceto::mado(node)->args)->size() == 0) && (ceto::mado(node)->func == nullptr)) && (ceto::mado(pattern)->func == nullptr)) {
            (std::cout << 14) << "\n";
if (ceto::mado(node)->repr() == ceto::mado(pattern)->repr()) {
                (std::cout << 15) << "\n";
                return std::map<std::shared_ptr<const Node>,std::shared_ptr<const Node>>{};
            }
            return {};
        }
        (std::cout << 16) << "\n";
        auto submatches { std::map<std::shared_ptr<const Node>,std::shared_ptr<const Node>>{} } ;
        (std::cout << 17) << "\n";
        for(const auto& i : std::ranges::iota_view(0u, ceto::mado(ceto::mado(node)->args)->size())) {
            const auto m = macro_matches(ceto::maybe_bounds_check_access(ceto::mado(node)->args,i), ceto::maybe_bounds_check_access(ceto::mado(pattern)->args,i), params);
            (std::cout << 18) << "\n";
if (!m) {
                (std::cout << 19) << "\n";
                return {};
            }
            ceto::mado(submatches)->insert(ceto::mado(m)->begin(), ceto::mado(m)->end());
        }
        (std::cout << 20) << "\n";
if (ceto::mado(node)->func) {
            (std::cout << 21) << "\n";
            const auto m = macro_matches(ceto::mado(node)->func, ceto::mado(pattern)->func, params);
if (!m) {
                (std::cout << 22) << "\n";
                return {};
            }
            ceto::mado(submatches)->insert(ceto::mado(m)->begin(), ceto::mado(m)->end());
        }
        (std::cout << 23) << "\n";
        return submatches;
    }

