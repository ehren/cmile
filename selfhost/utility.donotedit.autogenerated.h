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


#include <numeric>
;
#include <algorithm>
;
#include <string_view>
;
#if _MSC_VER
    
    #define CETO_EXPORT __declspec(dllexport)
    ;
#else
    #include <cxxabi.h>
;
    
    #define CETO_EXPORT __attribute__((visibility("default")))
    ;
#endif

    template <typename T1, typename T2>
auto join(const T1& v, const T2& to_string, const decltype(std::string {""})&  sep = std::string {""}) -> auto {
        if ((*ceto::mad(v)).empty()) {
            return std::string {""};
        }
        return std::accumulate((*ceto::mad(v)).cbegin() + 1, (*ceto::mad(v)).cend(), to_string(ceto::maybe_bounds_check_access(v,0)), [&to_string, &sep](const auto &a, const auto &el) {
                if constexpr (!std::is_void_v<decltype(((a + sep) + to_string(el)))>) { return ((a + sep) + to_string(el)); } else { static_cast<void>(((a + sep) + to_string(el))); };
                });
    }

    inline auto string_replace(const std::string&  source, const std::string&  from, const std::string&  to) -> auto {
        auto new_string { std::string() } ;
        (*ceto::mad(new_string)).reserve((*ceto::mad(source)).length());
        std::string::size_type last_pos { 0 } ; static_assert(std::is_convertible_v<decltype(0), decltype(last_pos)>);
        std::string::size_type find_pos { 0 } ; static_assert(std::is_convertible_v<decltype(0), decltype(find_pos)>);
        while (std::string::npos != (find_pos = (*ceto::mad(source)).find(from, last_pos))) {            (*ceto::mad(new_string)).append(source, last_pos, find_pos - last_pos);
            new_string += to;
            last_pos = (find_pos + (*ceto::mad(from)).length());
        }
        (*ceto::mad(new_string)).append(source, last_pos, (*ceto::mad(source)).length() - last_pos);
        return new_string;
    }

    template <typename T1>
auto contains(const T1& container,  const typename std::remove_reference_t<decltype(container)> :: value_type &  element) -> auto {
        return (std::find((*ceto::mad(container)).begin(), (*ceto::mad(container)).end(), element) != (*ceto::mad(container)).end());
    }

    template <typename T1>
auto typeid_name(const T1& object) -> auto {
        #if _MSC_VER
            const auto name = (*ceto::mad(typeid(object))).name();
            using namespace std::literals;
            const auto prefix = "struct "sv;
            const auto name_view = std::string_view(name);
            if ((*ceto::mad(name_view)).starts_with(prefix)) {
                return (*ceto::mad((*ceto::mad(name_view)).substr((*ceto::mad(prefix)).size()))).data();
            }
            return name;
        #else
            return abi::__cxa_demangle((*ceto::mad(typeid(object))).name(), 0, 0, 0);
        #endif

    }

