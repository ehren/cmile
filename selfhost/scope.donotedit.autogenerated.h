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

#include <map>
;
#include <cassert>
;
#include "ast.donotedit.autogenerated.h"
;
struct ClassDefinition : ceto::shared_object {

    std::shared_ptr<const Identifier> name_node;

    std::shared_ptr<const Call> class_def_node;

    bool is_unique;

    bool is_struct;

    bool is_forward_declaration;

    std::remove_cvref_t<decltype(false)> is_pure_virtual = false;

    std::remove_cvref_t<decltype(false)> is_concrete = false;

        inline auto repr() const -> auto {
            return ((((((((((this -> class_name() + std::string {"("}) + ceto::mado(this -> name_node)->repr()) + std::string {", "}) + ceto::mado(this -> class_def_node)->repr()) + std::to_string(this -> is_unique)) + std::string {", "}) + std::to_string(this -> is_struct)) + std::string {", "}) + std::to_string(this -> is_forward_declaration)) + std::string {")"});
        }

         virtual inline auto class_name() const -> std::string {
            return std::string {"ClassDefinition"};
        }

    explicit ClassDefinition(std::shared_ptr<const Identifier> name_node, std::shared_ptr<const Call> class_def_node, bool is_unique, bool is_struct, bool is_forward_declaration) : name_node(std::move(name_node)), class_def_node(std::move(class_def_node)), is_unique(is_unique), is_struct(is_struct), is_forward_declaration(is_forward_declaration) {}

    ClassDefinition() = delete;

};

struct InterfaceDefinition : public ClassDefinition {

         virtual inline auto class_name() const -> std::string {
            return std::string {"InterfaceDefinition"};
        }

    explicit InterfaceDefinition() : ClassDefinition (nullptr, nullptr, false, false, false) {
    }

};

struct VariableDefinition : ceto::shared_object {

    std::shared_ptr<const Identifier> defined_node;

    std::shared_ptr<const Node> defining_node;

        inline auto repr() const -> auto {
            return (((((this -> class_name() + std::string {"("}) + ceto::mado(this -> defined_node)->repr()) + std::string {", "}) + ceto::mado(this -> defining_node)->repr()) + std::string {")"});
        }

         virtual inline auto class_name() const -> std::string {
            return std::string {"VariableDefinition"};
        }

    explicit VariableDefinition(std::shared_ptr<const Identifier> defined_node, std::shared_ptr<const Node> defining_node) : defined_node(std::move(defined_node)), defining_node(std::move(defining_node)) {}

    VariableDefinition() = delete;

};

struct LocalVariableDefinition : public VariableDefinition {

using VariableDefinition::VariableDefinition;

         virtual inline auto class_name() const -> std::string {
            return std::string {"LocalVariableDefinition"};
        }

};

struct GlobalVariableDefinition : public VariableDefinition {

using VariableDefinition::VariableDefinition;

         virtual inline auto class_name() const -> std::string {
            return std::string {"GlobalVariableDefinition"};
        }

};

struct FieldDefinition : public VariableDefinition {

using VariableDefinition::VariableDefinition;

         virtual inline auto class_name() const -> std::string {
            return std::string {"FieldDefinition"};
        }

};

struct ParameterDefinition : public VariableDefinition {

using VariableDefinition::VariableDefinition;

         virtual inline auto class_name() const -> std::string {
            return std::string {"ParameterDefinition"};
        }

};

    template <typename T1>
auto contains(const T1& container,  const typename std::remove_reference_t<decltype(container)> :: value_type &  element) -> auto {
        return (std::find(ceto::mado(container)->begin(), ceto::mado(container)->end(), element) != ceto::mado(container)->end());
    }

    inline auto creates_new_variable_scope(const std::shared_ptr<const Node>&  e) -> auto {
        const auto call = dynamic_pointer_cast<const Call>(e);
if (call) {
            const auto name = ceto::mado(ceto::mado(call)->func)->name();
            return (name && contains(std::vector {{std::string {"def"}, std::string {"lambda"}, std::string {"class"}, std::string {"struct"}}}, ceto::mad(name)->value()));
        }
        return false;
    }

struct Scope : ceto::shared_object {

    std::remove_cvref_t<decltype(std::map<std::string,std::vector<std::shared_ptr<const Node>>>())> interfaces = std::map<std::string,std::vector<std::shared_ptr<const Node>>>();

    std::vector<std::shared_ptr<const ClassDefinition>> class_definitions = std::vector<std::shared_ptr<const ClassDefinition>>{}; static_assert(ceto::is_non_aggregate_init_and_if_convertible_then_non_narrowing_v<decltype(std::vector<std::shared_ptr<const ClassDefinition>>{}), std::remove_cvref_t<decltype(class_definitions)>>);

    std::vector<std::shared_ptr<const VariableDefinition>> variable_definitions = std::vector<std::shared_ptr<const VariableDefinition>>{}; static_assert(ceto::is_non_aggregate_init_and_if_convertible_then_non_narrowing_v<decltype(std::vector<std::shared_ptr<const VariableDefinition>>{}), std::remove_cvref_t<decltype(variable_definitions)>>);

    std::remove_cvref_t<decltype(0)> indent = 0;

    std::weak_ptr<const Scope> _parent = {};

    std::remove_cvref_t<decltype(false)> in_function_body = false;

    std::remove_cvref_t<decltype(false)> in_function_param_list = false;

    std::remove_cvref_t<decltype(false)> in_class_body = false;

    std::remove_cvref_t<decltype(false)> in_decltype = false;

        inline auto indent_str() const -> auto {
            return std::string(4 * (this -> indent), ' ');
        }

        inline auto add_variable_definition(const std::shared_ptr<const Identifier>&  defined_node, const std::shared_ptr<const Node>&  defining_node) -> void {
            auto parent { ceto::mado(defined_node)->parent() } ;
while (parent) {if (creates_new_variable_scope(parent)) {
                    const auto name = ceto::mado(ceto::mado(parent)->func)->name();
if ((name == std::string {"class"}) || (name == std::string {"struct"})) {
                        const auto defn = std::make_shared<const decltype(FieldDefinition{defined_node, defining_node})>(defined_node, defining_node);
                        ceto::mado(this -> variable_definitions)->push_back(defn);
                    } else if (((name == std::string {"def"}) || (name == std::string {"lambda"}))) {
                        const auto defn = std::make_shared<const decltype(ParameterDefinition{defined_node, defining_node})>(defined_node, defining_node);
                        ceto::mado(this -> variable_definitions)->push_back(defn);
                    } else {
                        const auto defn = std::make_shared<const decltype(LocalVariableDefinition{defined_node, defining_node})>(defined_node, defining_node);
                        ceto::mado(this -> variable_definitions)->push_back(defn);
                    }
                    return;
                }
                parent = ceto::mado(parent)->parent();
            }
            const auto defn = std::make_shared<const decltype(GlobalVariableDefinition{defined_node, defining_node})>(defined_node, defining_node);
            ceto::mado(this -> variable_definitions)->push_back(defn);
        }

        inline auto add_interface_method(const std::string&  interface_name, const std::shared_ptr<const Node>&  interface_method_def_node) -> void {
if (ceto::mado(this -> interfaces)->contains(interface_name)) {
                ceto::mado(ceto::maybe_bounds_check_access(this -> interfaces,interface_name))->push_back(interface_method_def_node);
            } else {
                ceto::maybe_bounds_check_access(this -> interfaces,interface_name) = std::vector {interface_method_def_node};
            }
        }

        inline auto add_class_definition(const std::shared_ptr<const ClassDefinition>&  class_definition) -> void {
            ceto::mado(this -> class_definitions)->push_back(class_definition);
        }

        inline auto lookup_class(const std::shared_ptr<const Node>&  class_node) const -> std::shared_ptr<const ClassDefinition> {
if (!dynamic_pointer_cast<const Identifier>(class_node)) {
                return nullptr;
            }
            for(const auto& c : (this -> class_definitions)) {
if (ceto::mado(ceto::mado(c)->name_node)->name() == ceto::mado(class_node)->name()) {
                    return c;
                }
            }
if (ceto::mado(this -> interfaces)->contains(ceto::mad(ceto::mado(class_node)->name())->value())) {
                return std::make_shared<const decltype(InterfaceDefinition())>();
            }
if (const auto s = ceto::mado(this -> _parent)->lock()) {
                return ceto::mado(s)->lookup_class(class_node);
            }
            return nullptr;
        }

        inline auto find_defs(const std::shared_ptr<const Node>&  var_node, const decltype(true) find_all = true) const -> std::vector<std::shared_ptr<const VariableDefinition>> {
if (!dynamic_pointer_cast<const Identifier>(var_node)) {
                return {};
            }
            auto results { std::vector<std::ranges::range_value_t<decltype(this->variable_definitions)>>() } ;
            for(const auto& d : (this -> variable_definitions)) {
if ((ceto::mado(ceto::mado(d)->defined_node)->name() == ceto::mado(var_node)->name()) && (ceto::mado(d)->defined_node != var_node)) {
                    const auto defined_loc = std::get<1>(ceto::mado(ceto::mado(d)->defined_node)->source);
                    const auto var_loc = std::get<1>(ceto::mado(var_node)->source);
if (defined_loc < var_loc) {
if (!find_all) {
                            return std::vector {d};
                        }
                        ceto::mad(results)->push_back(d);
                        const auto assign = dynamic_pointer_cast<const Assign>(ceto::mado(d)->defining_node);
if (assign) {
                            const auto ident = dynamic_pointer_cast<const Identifier>(ceto::mado(assign)->rhs());
if (ident) {
                                const auto more = this -> find_defs(ident, find_all);
                                ceto::mado(results)->insert(ceto::mado(results)->end(), ceto::mado(more)->begin(), ceto::mado(more)->end());
                            }
                        }
                    }
                }
            }
if (const auto s = ceto::mado(this -> _parent)->lock()) {
                const auto more = ceto::mado(s)->find_defs(var_node, find_all);
                ceto::mado(results)->insert(ceto::mado(results)->end(), ceto::mado(more)->begin(), ceto::mado(more)->end());
            }
            return results;
        }

        inline auto find_def(const std::shared_ptr<const Node>&  var_node) const -> auto {
            const auto find_all = false;
            const auto found = this -> find_defs(var_node, find_all);
            return [&]() {if (ceto::mado(found)->size() > 0) {
                return ceto::maybe_bounds_check_access(found,0);
            } else {
                const std::shared_ptr<const VariableDefinition> none_result = nullptr; static_assert(ceto::is_non_aggregate_init_and_if_convertible_then_non_narrowing_v<decltype(nullptr), std::remove_cvref_t<decltype(none_result)>>);
                return none_result;
            }}()
;
        }

        inline auto enter_scope() const -> std::shared_ptr<const Scope> {
            const auto self = ceto::shared_from(this);
            auto s { std::make_shared<decltype(Scope())>() } ;
            ceto::mado(s)->_parent = self;
            ceto::mado(s)->in_function_body = (this -> in_function_body);
            ceto::mado(s)->in_decltype = (this -> in_decltype);
            ceto::mado(s)->indent = ((this -> indent) + 1);
            return s;
        }

        inline auto parent() const -> auto {
            return ceto::mado(this -> _parent)->lock();
        }

};

