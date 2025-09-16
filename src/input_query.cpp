#include "input_query.hpp"

[[nodiscard]]
std::int64_t InputQuery::get_first_number() const noexcept {
    return _first_number;
}
[[nodiscard]]
std::int64_t InputQuery::get_second_number() const noexcept {
    return _second_number;
}
[[nodiscard]]
PossibleOperations InputQuery::get_cur_operation() const noexcept {
    return _cur_operation;
}
[[nodiscard]]
PossibleRounding InputQuery::get_cur_rounding() const noexcept {
    return _cur_rounding;
}

[[nodiscard]]
std::int64_t InputQuery::get_cnt_for_integer() const noexcept {
    return _cnt_for_integer;
}
[[nodiscard]]
std::int64_t InputQuery::get_cnt_for_fractional() const noexcept {
    return _cnt_for_fractional;
}

InputQuery::InputQuery(std::int64_t cnt_for_integer,
                       std::int64_t cnt_for_fractional,
                       std::int64_t first_number, PossibleRounding cur_rounding,
                       std::int64_t second_number,
                       PossibleOperations cur_operation)
    : _cnt_for_integer(cnt_for_integer),
      _cnt_for_fractional(cnt_for_fractional), _first_number(first_number),
      _second_number(second_number), _cur_rounding(cur_rounding),
      _cur_operation(cur_operation) {
}
