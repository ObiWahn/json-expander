#include <cstring>
#include <iostream>
#include <string>

#include <tao/json.hpp>
#include <tao/json/external/pegtl.hpp>
#include <tao/json/external/pegtl/contrib/json.hpp>
#include <tao/json/external/pegtl/memory_input.hpp>

using namespace tao::json;
using namespace std::literals::string_literals;

namespace expander {

struct value : pegtl::try_catch<pegtl::sor<pegtl::json::object, pegtl::json::array>> {};
struct any : pegtl::any {};
struct grammar : pegtl::star<pegtl::sor<value, any>> {};

struct state {
    bool json_only = false;
    std::string value;
};

// default action
template<typename rule>
struct action : pegtl::nothing<rule> {};

// actions for tokens
template<>
struct action<value> {
    template<typename input>
    static void apply(input const& in, state& s) {
        auto value = tao::json::from_string(in.string_view());
        if (!s.json_only) {
            s.value += "\n"s;
        }
        s.value += to_string(value, 2);
        s.value += "\n"s;
    }
};

template<>
struct action<any> {
    template<typename input>
    static void apply(input const& in, state& s) {
        if (!s.json_only) {
            s.value += in.string();
        }
    }
};

struct options {
    bool json_only = false;
};

options parse_args(int count, char const* values[]) {
    options opts;
    for (std::size_t i = 1; i < count; i++) {
        if (std::strcmp(values[i], "--json-only") == 0) {
            opts.json_only = true;
        }
    }
    return opts;
};

} // namespace expander

int main(int count, char const* values[]) {
    int error = 0;
    std::size_t pos;
    expander::state state;
    auto options = expander::parse_args(count, values);
    state.json_only = options.json_only;

    for (std::string line; std::getline(std::cin, line);) {
        state.value.clear();
        try {
            pegtl::memory_input in(line, "");
            pegtl::parse<expander::grammar, expander::action>(in, state);
        } catch (std::exception const& ex) {
            std::cerr << ex.what();
            state.value = std::move(line);
            error = 1;
        }

        std::cout << state.value;
    } // end loop - for line in input

    return error;
}
