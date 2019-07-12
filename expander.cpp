#include <iostream>
#include <string>

#include <tao/json.hpp>
#include <tao/json/external/pegtl.hpp>
#include <tao/json/external/pegtl/contrib/json.hpp>
#include <tao/json/external/pegtl/memory_input.hpp>

using namespace tao::json;

namespace expander {

using value = pegtl::json::object;
using grammar = pegtl::must<value, pegtl::star<pegtl::any>>;
using state = std::size_t;

// default action
template<typename rule>
struct action : pegtl::nothing<rule> {};

// actions for tokens
template<>
struct action<value> {
    template<typename input>
    static void apply(input const& in, state& s) {
        if (in.position().byte_in_line == 0) {
            s = in.size();
        }
    }
};

} // namespace expander

int main() {
    std::size_t pos;
    expander::state state;

    for (std::string line; std::getline(std::cin, line);) {
        pos = 0;
        state = 0;

        for (std::size_t pos = 0; pos < line.size(); pos++) {
            if (line[pos] == '{') {
                std::string_view view(line.data() + pos, line.length() - pos);
                pegtl::memory_input in(view, std::string("symbol at: " + std::to_string(pos)));
                try {
                    bool is_json = pegtl::parse<expander::grammar, expander::action>(in, state);
                } catch (std::exception const& ex) {
                    state = 0;
                }

                std::string_view json_view(line.data() + pos, state);
                if (!json_view.empty()) {
                    try {
                        auto value = from_string(json_view);
                        std::cout << "\n";
                        to_stream(std::cout, value, 2);
                        std::cout << "\n";
                        pos += state;
                        continue;
                    } catch (pegtl::parse_error const& e) {
                        std::cout << "error for position: " << pos << " " << e.what() << std::endl;
                    }
                } // end - if view not empty
            }     // end if - candidate for document
            std::cout << line[pos];
        } // end loop - for pos in string
    }     // end loop - for line in input

    return 0;
}
