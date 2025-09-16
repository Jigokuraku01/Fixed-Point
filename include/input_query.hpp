#pragma once

#include <cstdint>
enum class PossibleOperations : std::uint8_t {
    PLUS,
    MINUS,
    MUL,
    DIV,
    NO_OPER,
};

enum class PossibleRounding : std::uint8_t {
    TOWARD_ZERO,
    TOWARD_NEAREST_EVEN,
    TOWARD_POS_INFINITY,
    TOWARD_NEG_INFINITY,
};
class InputQuery {
  public:
    InputQuery(std::int64_t cnt_for_integer, std::int64_t cnt_for_fractional,
               std::int64_t first_number,
               PossibleRounding cur_rounding = PossibleRounding::TOWARD_ZERO,
               std::int64_t second_number = 0,
               PossibleOperations cur_operation = PossibleOperations::NO_OPER);

    [[nodiscard]]
    std::int64_t get_first_number() const noexcept;
    [[nodiscard]]
    std::int64_t get_second_number() const noexcept;
    [[nodiscard]]
    std::int64_t get_cnt_for_integer() const noexcept;
    [[nodiscard]]
    std::int64_t get_cnt_for_fractional() const noexcept;
    [[nodiscard]]
    PossibleOperations get_cur_operation() const noexcept;
    [[nodiscard]]
    PossibleRounding get_cur_rounding() const noexcept;

  private:
    std::int64_t _cnt_for_integer;
    std::int64_t _cnt_for_fractional;
    std::int64_t _first_number;
    std::int64_t _second_number;
    PossibleRounding _cur_rounding;
    PossibleOperations _cur_operation;
};