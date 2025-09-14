#include "parser.hpp"

#include "input_query.hpp"
#include "my_exception.hpp"
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

InputQuery Parser::parse_input_query(const std::vector<std::string>&& argv) {
    if (argv.size() != 3 && argv.size() != 5) {
        throw MyException(EXIT_FAILURE, "Invalid input format");
    }
    std::int32_t cnt_for_integer;
    std::int32_t cnt_for_fractional;
    std::int32_t first_number;
    PossibleRounding cur_rounding;
    std::int32_t second_number = 0;
    PossibleOperations cur_operation = PossibleOperations::NO_OPER;

    const std::string& integer_and_fractional_cnt = argv[0];
    std::uint64_t pos = integer_and_fractional_cnt.find('.');

    if (pos == std::string::npos) {
        throw MyException(EXIT_FAILURE, "invalid input format: " +
                                            integer_and_fractional_cnt);
    }

    std::string left = integer_and_fractional_cnt.substr(0, pos);
    std::string right = integer_and_fractional_cnt.substr(pos + 1);
    cnt_for_integer = parse_to_int(left, 10);
    cnt_for_fractional = parse_to_int(right, 10);

    std::int32_t cur_rounding_int = parse_to_int(argv[1], 10);
    switch (cur_rounding_int) {
        case (0): {
            cur_rounding = PossibleRounding::TOWARD_ZERO;
            break;
        }
        case (1): {
            cur_rounding = PossibleRounding::TOWARD_NEAREST_EVEN;
            break;
        }
        case (2): {
            cur_rounding = PossibleRounding::TOWARD_POS_INFINITY;
            break;
        }
        case (3): {
            cur_rounding = PossibleRounding::TOWARD_NEG_INFINITY;
            break;
        }
        default: {
            throw MyException(EXIT_FAILURE,
                              "unknown rounding code: " +
                                  std::to_string(cur_rounding_int));
        }
    }

    if (argv.size() == 3) {
        first_number = parse_to_int(argv[2], 16);
    }
    else {
        if (argv[2].size() != 1) {
            throw MyException(EXIT_FAILURE, "unknown operation: " + argv[2]);
        }
        switch (argv[2][0]) {
            case ('+'): {
                cur_operation = PossibleOperations::PLUS;
                break;
            }
            case ('-'): {
                cur_operation = PossibleOperations::MINUS;
                break;
            }
            case ('*'): {
                cur_operation = PossibleOperations::MUL;
                break;
            }
            case ('/'): {
                cur_operation = PossibleOperations::DIV;
                break;
            }
            default: {
                throw MyException(EXIT_FAILURE,
                                  "unknown operation: " + argv[2]);
            }
        }
        first_number = parse_to_int(argv[3], 16);
        second_number = parse_to_int(argv[4], 16);
    }
    InputQuery ans = {cnt_for_integer, cnt_for_fractional, first_number,
                      cur_rounding,    second_number,      cur_operation};
    return ans;
}

std::int32_t Parser::parse_to_int(const std::string& inpStr,
                                  std::int32_t base) {
    try {
        std::uint64_t pos = 0;
        std::uint64_t result = std::stoul(inpStr, &pos, base);

        if (pos != inpStr.size()) {
            throw std::invalid_argument("Invalid input number format: " +
                                        inpStr.substr(pos));
        }

        return static_cast<std::int32_t>(result);
    }
    catch (const std::invalid_argument& e) {
        throw MyException(EXIT_FAILURE,
                          "Invalid input number format: " + inpStr);
    }
}