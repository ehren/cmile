
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


#include "ceto.h"
//#include "ceto_private_boundscheck.donotedit.autogenerated.h"

#include "ceto_private_listcomp.donotedit.autogenerated.h"
;
#include "ceto_private_boundscheck.donotedit.autogenerated.h"
;
#include "ceto_private_convenience.donotedit.autogenerated.h"
;
constexpr const auto g = 1;
struct Foo : public ceto::shared_object, public std::enable_shared_from_this<Foo> {

    decltype(1) x = 1;

        inline auto foo() const -> void {
            const auto x = 2;
            std::cout << x;
        }

};

    auto main() -> int {
        const auto f = std::make_shared<const Foo>();
        (*ceto::mad(f)).foo();
    }

