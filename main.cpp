#include "expression_holder.hpp"
#include "input_query.hpp"
#include "my_exception.hpp"
#include "parser.hpp"
#include <iostream>

int main(int argc, char** argv) {
    try {
        std::vector<std::string> tmp_vec;
        tmp_vec.reserve(static_cast<std::uint64_t>(argc - 1));
        for (std::uint64_t i = 0; i < static_cast<std::uint64_t>(argc - 1);
             ++i) {
            tmp_vec.emplace_back(argv[i + 1]);
        }
        InputQuery inp_query = Parser::parse_input_query(std::move(tmp_vec));
        ExpressionHolder cur_expr_holder = ExpressionHolder{inp_query};
        cur_expr_holder.solve();
        return 0;
    }
    catch (const MyException& e) {
        std::cerr << e.get_error();
        return e.get_code();
    }
    catch (...) {
        std::cerr << "unknown error";
    }
}
