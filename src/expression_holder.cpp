#include "expression_holder.hpp"

#include "input_query.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

ExpressionHolder::ExpressionHolder(InputQuery inpQuery)
    : _curInpQuery(inpQuery),
      _act_first_number(cut_number(_curInpQuery.get_first_number(),
                                   _curInpQuery.get_cnt_for_integer() +
                                       _curInpQuery.get_cnt_for_fractional())),
      _act_second_number(
          cut_number(_curInpQuery.get_second_number(),
                     _curInpQuery.get_cnt_for_integer() +
                         _curInpQuery.get_cnt_for_fractional())) {
}
void ExpressionHolder::solve() {
    std::int32_t ans = _curInpQuery.get_first_number();
        if (_curInpQuery.is_operation_exist()) {
            ans = use_oper();
        }

    std::string ans_str = std::to_string(round_to_dec(ans));
        if (ans_str.size() <= 3) {
            ans_str.insert(0, 4 - ans_str.size(), '0');
        }
    ans_str.insert(ans_str.size() - 3, 1, '.');
    std::cout << ans_str;
}

std::int32_t ExpressionHolder::use_oper() {
    std::int32_t ans;
        switch (_curInpQuery.get_cur_operation()) {

            case PossibleOperations::MINUS: {
                ans = _act_first_number - _act_second_number;
                break;
            }
            case PossibleOperations::PLUS: {
                ans = _act_first_number + _act_second_number;
                break;
            }
            case PossibleOperations::MUL: {
                std::int64_t tmp_ans =
                    static_cast<std::int64_t>(_act_first_number) *
                    static_cast<std::int64_t>(_act_second_number);
                ans = round_to_bin_and_shift(
                    tmp_ans, _curInpQuery.get_cnt_for_fractional());
                break;
            }
            case PossibleOperations::DIV: {
                ans = divide(static_cast<std::int64_t>(_act_first_number),
                             static_cast<std::int64_t>(_act_second_number));
                break;
            }
            case PossibleOperations::NO_OPER: {
                throw(std::runtime_error(
                    "invalid operation during program work"));
            }
        }
    return cut_number(ans, _curInpQuery.get_cnt_for_integer() +
                               _curInpQuery.get_cnt_for_fractional());
}

std::int32_t ExpressionHolder::divide(std::int64_t big_first_numb,
                                      std::int64_t big_second_numb) {

        if (big_second_numb == 0) {
            throw(std::runtime_error("div by zero"));
        }
        if ((big_first_numb < 0 && big_second_numb < 0) ||
            (big_first_numb > 0 && big_second_numb < 0)) {
            big_first_numb = -big_first_numb;
            big_second_numb = -big_second_numb;
        }

    std::int64_t div_tmp_ans = big_first_numb / big_second_numb;
        if (div_tmp_ans * big_first_numb == big_first_numb) {
            return static_cast<std::int32_t>(div_tmp_ans);
        }
    std::int64_t ans;
        switch (_curInpQuery.get_cur_rounding()) {

            case (PossibleRounding::TOWARD_ZERO): {
                ans = div_tmp_ans;
                break;
            }
            case (PossibleRounding::TOWARD_NEG_INFINITY): {
                    if (div_tmp_ans > 0) {
                        ans = div_tmp_ans;
                    }
                    else {
                        ans = div_tmp_ans - 1;
                    }
                break;
            }
            case (PossibleRounding::TOWARD_POS_INFINITY): {
                    if (div_tmp_ans < 0) {
                        ans = div_tmp_ans;
                    }
                    else {
                        ans = div_tmp_ans + 1;
                    }
                break;
            }
            case (PossibleRounding::TOWARD_NEAREST_EVEN): {
                ans = div_tmp_ans;
                std::int64_t mod =
                    big_first_numb - (big_second_numb * div_tmp_ans);
                    if (div_tmp_ans > 0) {

                            if (mod * 2 > big_second_numb) {
                                ans += 1;
                            }
                            if (mod * 2 == big_second_numb) {
                                    if ((ans & 1) == 1) {
                                        ans += 1;
                                    }
                            }
                    }
                    else {
                        std::int64_t abs_mod = -mod;
                            if (abs_mod * 2 > big_second_numb) {
                                ans -= 1;
                            }
                            if (abs_mod * 2 == big_second_numb) {
                                    if ((ans & 1) == 1) {
                                        ans -= 1;
                                    }
                            }
                    }
                break;
            }
        }
    return static_cast<std::int32_t>(ans);
}

std::int32_t ExpressionHolder::round_to_dec(std::int32_t inp_value) {
    std::int64_t tmp_ans = static_cast<std::int64_t>(inp_value) * 1000;
    return round_to_bin_and_shift(tmp_ans,
                                  _curInpQuery.get_cnt_for_fractional());
}

std::int32_t get_all_ones_at_inp_bit_cnt(std::int32_t inpCnt) {
        if (inpCnt >= 32) {
            return ~(static_cast<std::int32_t>(0));
        }
    return (static_cast<std::int32_t>(1) << inpCnt) -
           static_cast<std::int32_t>(1);
}

std::int32_t cut_number(std::int32_t inpNumber, std::int32_t cnt_bits) {

    inpNumber = inpNumber & get_all_ones_at_inp_bit_cnt(cnt_bits);
        if (inpNumber >> (cnt_bits - 1) != 0) {
            inpNumber |= get_all_ones_at_inp_bit_cnt(32) -
                         get_all_ones_at_inp_bit_cnt(cnt_bits);
        }
    return inpNumber;
}

std::int32_t ExpressionHolder::round_to_bin_and_shift(std::int64_t inpValue,
                                                      std::int32_t cntOfBits) {

    return divide(inpValue, 1LL << cntOfBits);
}