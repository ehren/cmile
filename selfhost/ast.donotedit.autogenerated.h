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
#include <typeinfo>
;
#include "visitor.donotedit.autogenerated.h"
;
#include "utility.donotedit.autogenerated.h"
;
#include "range_utility.donotedit.autogenerated.h"
;
struct Source : public ceto::shared_object, public std::enable_shared_from_this<Source> {

    decltype(std::string {""}) source = std::string {""};

};

struct SourceLoc : public ceto::object {

    std::shared_ptr<const Source> source;

    int loc;

    decltype(std::string {""}) header_file_cth = std::string {""};

    decltype(std::string {""}) header_file_h = std::string {""};

    explicit SourceLoc(const std::shared_ptr<const Source>& source = nullptr, const int loc = 0) : source(source), loc(loc) {
    }

};

struct Scope;

struct Node : public ceto::shared_object, public std::enable_shared_from_this<Node> {

    std::shared_ptr<const Node> func;

    std::vector<std::shared_ptr<const Node>> args;

    SourceLoc source;

    std::shared_ptr<const Node> declared_type = nullptr; static_assert(ceto::is_non_aggregate_init_and_if_convertible_then_non_narrowing_v<decltype(nullptr), std::remove_cvref_t<decltype(declared_type)>>);

    std::shared_ptr<const Scope> scope = nullptr; static_assert(ceto::is_non_aggregate_init_and_if_convertible_then_non_narrowing_v<decltype(nullptr), std::remove_cvref_t<decltype(scope)>>);

    std::weak_ptr<const Node> _parent = {};

         virtual inline auto classname() const -> std::string {
            return typeid_name((*this));
        }

         virtual inline auto repr() const -> std::string {
            const auto classname = this -> classname();
            const auto csv = join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ");
            return (((((classname + "(") + (*ceto::mad(this -> func)).repr()) + ")([") + csv) + "])");
        }

         virtual inline auto name() const -> std::optional<std::string> {
            return std::nullopt;
        }

         virtual inline auto accept( Visitor &  visitor) const -> void {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto cloned_args() const -> std::vector<std::shared_ptr<const Node>> {
            auto new_args { std::vector<std::shared_ptr<const Node>>((*ceto::mad(this -> args)).size()) } ;
            for(const auto& i : range((*ceto::mad(this -> args)).size())) {
                ceto::maybe_bounds_check_access(new_args,i) = (*ceto::mad(ceto::maybe_bounds_check_access(this -> args,i))).clone();
            }
            return new_args;
        }

         virtual inline auto clone() const -> std::shared_ptr<Node> {
            std::shared_ptr<Node> none = nullptr; static_assert(ceto::is_non_aggregate_init_and_if_convertible_then_non_narrowing_v<decltype(nullptr), std::remove_cvref_t<decltype(none)>>);
            auto c { std::make_shared<decltype(Node{[&]() {if (this -> func) {
                return (*ceto::mad(this -> func)).clone();
            } else {
                return none;
            }}()
, this -> cloned_args(), this -> source})>([&]() {if (this -> func) {
                return (*ceto::mad(this -> func)).clone();
            } else {
                return none;
            }}()
, this -> cloned_args(), this -> source) } ;
            return c;
        }

        inline auto parent() const -> auto {
            return (*ceto::mad(this -> _parent)).lock();
        }

        inline auto set_parent(const std::shared_ptr<const Node>&  p) -> void {
            (this -> _parent) = p;
        }

         virtual ~Node() {
            ; // pass
        }

    explicit Node(const std::shared_ptr<const Node>&  func, const std::vector<std::shared_ptr<const Node>>&  args, const decltype(SourceLoc())& source = SourceLoc()) : func(func), args(args), source(source) {
    }

    Node() = delete;

};

struct UnOp : public Node {

    std::string op;

        inline auto repr() const -> std::string override {
            return ((((std::string {"("} + (this -> op)) + " ") + (*ceto::mad(ceto::maybe_bounds_check_access(this -> args,0))).repr()) + ")");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(UnOp{this -> op, this -> cloned_args(), source})>(this -> op, this -> cloned_args(), source) } ;
            return c;
        }

    explicit UnOp(const std::string&  op, const std::vector<std::shared_ptr<const Node>>&  args, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, args, source), op(op) {
    }

    UnOp() = delete;

};

struct LeftAssociativeUnOp : public Node {

    std::string op;

        inline auto repr() const -> std::string override {
            return (((("(" + (*ceto::mad(ceto::maybe_bounds_check_access(this -> args,0))).repr()) + " ") + (this -> op)) + ")");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(LeftAssociativeUnOp{this -> op, this -> cloned_args(), source})>(this -> op, this -> cloned_args(), source) } ;
            return c;
        }

    explicit LeftAssociativeUnOp(const std::string&  op, const std::vector<std::shared_ptr<const Node>>&  args, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, args, source), op(op) {
    }

    LeftAssociativeUnOp() = delete;

};

struct BinOp : public Node {

    std::string op;

        inline auto lhs() const -> auto {
            return ceto::maybe_bounds_check_access(this -> args,0);
        }

        inline auto rhs() const -> auto {
            return ceto::maybe_bounds_check_access(this -> args,1);
        }

        inline auto repr() const -> std::string override {
            return (((((("(" + (*ceto::mad(this -> lhs())).repr()) + " ") + (this -> op)) + " ") + (*ceto::mad(this -> rhs())).repr()) + ")");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(BinOp{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

    explicit BinOp(const std::string&  op, const std::vector<std::shared_ptr<const Node>>&  args, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, args, source), op(op) {
    }

    BinOp() = delete;

};

struct TypeOp : public BinOp {

using BinOp::BinOp;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(TypeOp{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct SyntaxTypeOp : public TypeOp {

using TypeOp::TypeOp;

    std::shared_ptr<const Node> synthetic_lambda_return_lambda = nullptr; static_assert(ceto::is_non_aggregate_init_and_if_convertible_then_non_narrowing_v<decltype(nullptr), std::remove_cvref_t<decltype(synthetic_lambda_return_lambda)>>);

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(SyntaxTypeOp{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct AttributeAccess : public BinOp {

using BinOp::BinOp;

        inline auto repr() const -> std::string override {
            return (((*ceto::mad(this -> lhs())).repr() + ".") + (*ceto::mad(this -> rhs())).repr());
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(AttributeAccess{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct ArrowOp : public BinOp {

using BinOp::BinOp;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(ArrowOp{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct ScopeResolution : public BinOp {

using BinOp::BinOp;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(ScopeResolution{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct Assign : public BinOp {

using BinOp::BinOp;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(Assign{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct NamedParameter : public Assign {

using Assign::Assign;

        inline auto repr() const -> std::string override {
            return ((std::string {"NamedParameter("} + join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ")) + ")");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(NamedParameter{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct BitwiseOrOp : public BinOp {

using BinOp::BinOp;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(BitwiseOrOp{this -> op, this -> cloned_args(), this -> source})>(this -> op, this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct Identifier : public Node {

    std::string _name;

        inline auto repr() const -> std::string override {
            return (this -> _name);
        }

        inline auto name() const -> std::optional<std::string> override {
            return (this -> _name);
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<Identifier>((*this)) } ;
            return c;
        }

    explicit Identifier(const std::string&  name, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, std::vector<std::shared_ptr<const Node>>{}, source), _name(name) {
    }

    Identifier() = delete;

};

struct Call : public Node {

using Node::Node;

    decltype(false) is_one_liner_if = false;

        inline auto repr() const -> std::string override {
            const auto csv = join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ");
            return ((((*ceto::mad(this -> func)).repr() + "(") + csv) + ")");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(Call{(*ceto::mad(this -> func)).clone(), this -> cloned_args(), this -> source})>((*ceto::mad(this -> func)).clone(), this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct ArrayAccess : public Node {

using Node::Node;

        inline auto repr() const -> std::string override {
            const auto csv = join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ");
            return ((((*ceto::mad(this -> func)).repr() + "[") + csv) + "]");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(ArrayAccess{(*ceto::mad(this -> func)).clone(), this -> cloned_args(), this -> source})>((*ceto::mad(this -> func)).clone(), this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct BracedCall : public Node {

using Node::Node;

        inline auto repr() const -> std::string override {
            const auto csv = join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ");
            return ((((*ceto::mad(this -> func)).repr() + "{") + csv) + "}");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(BracedCall{(*ceto::mad(this -> func)).clone(), this -> cloned_args(), this -> source})>((*ceto::mad(this -> func)).clone(), this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct Template : public Node {

using Node::Node;

        inline auto repr() const -> std::string override {
            const auto csv = join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ");
            return ((((*ceto::mad(this -> func)).repr() + "<") + csv) + ">");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(Template{(*ceto::mad(this -> func)).clone(), this -> cloned_args(), this -> source})>((*ceto::mad(this -> func)).clone(), this -> cloned_args(), this -> source) } ;
            return c;
        }

};

    inline auto get_string_replace_function() -> auto {
        static std::function<std::string(std::string)> func = {};
        return func;
    }

    inline auto set_string_replace_function(const decltype(get_string_replace_function())  f) -> void {
        get_string_replace_function() = f;
    }

struct StringLiteral : public Node {

    std::string str;

    std::shared_ptr<const Identifier> prefix;

    std::shared_ptr<const Identifier> suffix;

        inline auto escaped() const -> auto {
            auto s { string_replace(this -> str, "\\", "\\\\") } ;
            s = string_replace(s, "\n", "\\n");
            s = string_replace(s, "\"", "\\\"");
            s = ((std::string {"\""} + s) + "\"");
            return s;
        }

        inline auto repr() const -> std::string override {
            return (([&]() {if (this -> prefix) {
                return (*ceto::mad_smartptr((*ceto::mad(this -> prefix)).name())).value();
            } else {
                return std::string {""};
            }}()
 + this -> escaped()) + [&]() {if (this -> suffix) {
                return (*ceto::mad_smartptr((*ceto::mad(this -> suffix)).name())).value();
            } else {
                return std::string {""};
            }}()
);
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(StringLiteral{this -> str, [&]() {if (this -> prefix) {
                return std::dynamic_pointer_cast<const Identifier>((*ceto::mad(this -> prefix)).clone());
            } else {
                return (this -> prefix);
            }}()
, [&]() {if (this -> suffix) {
                return std::dynamic_pointer_cast<const Identifier>((*ceto::mad(this -> suffix)).clone());
            } else {
                return (this -> suffix);
            }}()
, this -> source})>(this -> str, [&]() {if (this -> prefix) {
                return std::dynamic_pointer_cast<const Identifier>((*ceto::mad(this -> prefix)).clone());
            } else {
                return (this -> prefix);
            }}()
, [&]() {if (this -> suffix) {
                return std::dynamic_pointer_cast<const Identifier>((*ceto::mad(this -> suffix)).clone());
            } else {
                return (this -> suffix);
            }}()
, this -> source) } ;
            return c;
        }

    explicit StringLiteral(const std::string&  str, const std::shared_ptr<const Identifier>& prefix = nullptr, const std::shared_ptr<const Identifier>& suffix = nullptr, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, std::vector<std::shared_ptr<const Node>>{}, source), str(str), prefix(prefix), suffix(suffix) {
    }

    StringLiteral() = delete;

};

struct IntegerLiteral : public Node {

    std::string integer_string;

    std::shared_ptr<const Identifier> suffix;

        inline auto repr() const -> std::string override {
            return ((this -> integer_string) + [&]() {if (this -> suffix) {
                return (*ceto::mad_smartptr((*ceto::mad(this -> suffix)).name())).value();
            } else {
                return std::string {""};
            }}()
);
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(IntegerLiteral{this -> integer_string, [&]() {if (this -> suffix) {
                return std::dynamic_pointer_cast<const Identifier>((*ceto::mad(this -> suffix)).clone());
            } else {
                return (this -> suffix);
            }}()
, this -> source})>(this -> integer_string, [&]() {if (this -> suffix) {
                return std::dynamic_pointer_cast<const Identifier>((*ceto::mad(this -> suffix)).clone());
            } else {
                return (this -> suffix);
            }}()
, this -> source) } ;
            return c;
        }

    explicit IntegerLiteral(const std::string&  integer_string, const std::shared_ptr<const Identifier>& suffix = nullptr, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, {}, source), integer_string(integer_string), suffix(suffix) {
    }

    IntegerLiteral() = delete;

};

struct FloatLiteral : public Node {

    std::string float_string;

    std::shared_ptr<const Identifier> suffix;

        inline auto repr() const -> std::string override {
            return ((this -> float_string) + [&]() {if (this -> suffix) {
                return (*ceto::mad_smartptr((*ceto::mad(this -> suffix)).name())).value();
            } else {
                return std::string {""};
            }}()
);
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(FloatLiteral{this -> float_string, [&]() {if (this -> suffix) {
                return std::dynamic_pointer_cast<const Identifier>((*ceto::mad(this -> suffix)).clone());
            } else {
                return (this -> suffix);
            }}()
, this -> source})>(this -> float_string, [&]() {if (this -> suffix) {
                return std::dynamic_pointer_cast<const Identifier>((*ceto::mad(this -> suffix)).clone());
            } else {
                return (this -> suffix);
            }}()
, this -> source) } ;
            return c;
        }

    explicit FloatLiteral(const std::string&  float_string, const std::shared_ptr<const Identifier>&  suffix, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, {}, source), float_string(float_string), suffix(suffix) {
    }

    FloatLiteral() = delete;

};

struct ListLike_ : public Node {

        inline auto repr() const -> std::string override {
            const auto classname = this -> classname();
            return (((classname + "(") + join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ")) + ")");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(ListLike_{this -> cloned_args(), this -> source})>(this -> cloned_args(), this -> source) } ;
            return c;
        }

    explicit ListLike_(const std::vector<std::shared_ptr<const Node>>&  args, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, args, source) {
    }

    ListLike_() = delete;

};

struct ListLiteral : public ListLike_ {

using ListLike_::ListLike_;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(ListLiteral{this -> cloned_args(), this -> source})>(this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct TupleLiteral : public ListLike_ {

using ListLike_::ListLike_;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(TupleLiteral{this -> cloned_args(), this -> source})>(this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct BracedLiteral : public ListLike_ {

using ListLike_::ListLike_;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(BracedLiteral{this -> cloned_args(), this -> source})>(this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct Block : public ListLike_ {

using ListLike_::ListLike_;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(Block{this -> cloned_args(), this -> source})>(this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct Module : public Block {

using Block::Block;

    decltype(false) has_main_function = false;

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(Module{this -> cloned_args(), this -> source})>(this -> cloned_args(), this -> source) } ;
            return c;
        }

};

struct RedundantParens : public Node {

        inline auto repr() const -> std::string override {
            const auto classname = this -> classname();
            return (((classname + "(") + join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ")) + ")");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(RedundantParens{this -> cloned_args(), this -> source})>(this -> cloned_args(), this -> source) } ;
            return c;
        }

    explicit RedundantParens(const std::vector<std::shared_ptr<const Node>>&  args, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, args, source) {
    }

    RedundantParens() = delete;

};

struct InfixWrapper_ : public Node {

        inline auto repr() const -> std::string override {
            const auto classname = this -> classname();
            return (((classname + "(") + join(this -> args, [](const auto &a) {
                    if constexpr (!std::is_void_v<decltype((*ceto::mad(a)).repr())>) { return (*ceto::mad(a)).repr(); } else { static_cast<void>((*ceto::mad(a)).repr()); };
                    }, ", ")) + ")");
        }

        inline auto accept( Visitor &  visitor) const -> void override {
            (*ceto::mad(visitor)).visit((*this));
        }

        inline auto clone() const -> std::shared_ptr<Node> override {
            auto c { std::make_shared<decltype(InfixWrapper_{this -> cloned_args(), this -> source})>(this -> cloned_args(), this -> source) } ;
            return c;
        }

    explicit InfixWrapper_(const std::vector<std::shared_ptr<const Node>>&  args, const decltype(SourceLoc())& source = SourceLoc()) : Node (nullptr, args, source) {
    }

    InfixWrapper_() = delete;

};

