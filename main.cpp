#include "expression_holder.hpp"
#include "input_query.hpp"
#include <exception>
#include <iostream>

int main(/*int argc, char** argv*/) {
        try { /*
            std::vector<std::string> tmp_vec;
            tmp_vec.reserve(static_cast<std::uint64_t>(argc));
                for (std::uint64_t i = 0;
                     i < static_cast<std::uint64_t>(argc - 1); ++i) {
                    tmp_vec[i] = std::string(argv[i + 1]);
                }*/
            //InputQuery inp_query =
            //Parser::parse_input_query(std::move(tmp_vec));
            InputQuery inp_query = {4,
                                    4,
                                    18,
                                    PossibleRounding::TOWARD_NEAREST_EVEN,
                                    true,
                                    256,
                                    PossibleOperations::DIV};
            ExpressionHolder cur_expr_holder = ExpressionHolder{inp_query};
            cur_expr_holder.solve();
            return 0;
        }
        catch (std::exception e) {
            std::cerr << e.what();
        }
}
