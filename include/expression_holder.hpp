#pragma once
#include "input_query.hpp"
#include <cstdint>
#include <string>
class ExpressionHolder {
  public:
    explicit ExpressionHolder(InputQuery inpQuery);
    std::string solve_and_return_ans();

  private:
    std::int32_t use_oper();
    std::int32_t round_to_dec(std::int32_t inp_value);
    std::int32_t round_to_bin_and_shift(std::int64_t inpValue,
                                        std::int32_t cntOfBits);

    std::int32_t divide(std::int64_t big_first_numb,
                        std::int64_t big_second_numb);
    InputQuery _curInpQuery;

    std::int32_t _act_first_number;
    std::int32_t _act_second_number;
};

std::uint32_t get_all_ones_at_inp_bit_cnt(std::int32_t inpCnt);
std::int32_t cut_number(std::int32_t inpNumber, std::int32_t cnt_bits);