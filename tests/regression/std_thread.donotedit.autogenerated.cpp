
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

template <typename _ceto_private_C1>struct Bar : ceto::shared_object {

    _ceto_private_C1 a;

    explicit Bar(_ceto_private_C1 a) : a(a) {}

    Bar() = delete;

};

struct Foo : ceto::shared_object {

    std::atomic<int> a { 0 } ; static_assert(std::is_convertible_v<decltype(0), decltype(a)>);

    std::atomic<bool> go { true } ; static_assert(std::is_convertible_v<decltype(true), decltype(go)>);

    std::atomic<bool> go2 = std::atomic<bool>{true}; static_assert(ceto::is_non_aggregate_init_and_if_convertible_then_non_narrowing_v<decltype(std::atomic<bool>{true}), std::remove_cvref_t<decltype(go2)>>);

};

    auto main() -> int {
        auto f { std::make_shared<decltype(Foo())>() } ;
        auto t { std::thread([f = ceto::default_capture(f)]() {
while (ceto::mado(f)->a < 100000) {                    (std::cout << ceto::mado(f)->a) << std::string {"\n"};
                }
                if constexpr (!std::is_void_v<decltype(ceto::mado(f)->go = false)>) { return ceto::mado(f)->go = false; } else { static_cast<void>(ceto::mado(f)->go = false); };
                }) } ;
        auto t2 { std::thread([f = ceto::default_capture(f)]() {
while (ceto::mado(f)->go) {                    ceto::mado(f)->a = (ceto::mado(f)->a + 1);
                    ceto::mad(ceto::mado(f)->a)->operator++();
                    ceto::mad(ceto::mado(f)->a)->operator++(1);
                    ceto::mado(f)->a += 1;
                }
                return;
                }) } ;
        ceto::mado(t)->join();
        ceto::mado(t2)->join();
    }
