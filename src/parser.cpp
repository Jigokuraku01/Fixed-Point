#include "parser.hpp"

#include "input_query.hpp"
#include <stdexcept>
#include <string>
#include <vector>

InputQuery Parser::parse_input_query(const std::vector<std::string>&& argv) {
        if (argv.size() != 3 && argv.size() != 5) {
            throw std::invalid_argument("Invalid input format");
        }
    InputQuery ans = {1, 1, 1};
    return ans;
}
