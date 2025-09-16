#pragma once
#include "input_query.hpp"
#include <cstdint>
#include <string>
class ExpressionHolder {
  public:
    explicit ExpressionHolder(InputQuery inpQuery);
    std::string solve_and_return_ans();

  private:
    std::int64_t use_oper();
    std::int64_t round_to_dec(std::int64_t inp_value);
    std::int64_t round_to_bin_and_shift(std::int64_t inpValue,
                                        std::int64_t cntOfBits);

    std::int64_t divide(std::int64_t big_first_numb,
                        std::int64_t big_second_numb,
                        bool should_shift_numer = true);
    InputQuery _curInpQuery;

    std::int64_t _act_first_number;
    std::int64_t _act_second_number;
};

std::uint64_t get_all_ones_at_inp_bit_cnt(std::int64_t inpCnt);
std::int64_t cut_number(std::int64_t inpNumber, std::int64_t cnt_bits);