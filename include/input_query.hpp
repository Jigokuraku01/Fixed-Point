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
    InputQuery(std::int32_t cnt_for_integer, std::int32_t cnt_for_fractional,
               std::int32_t first_number,
               PossibleRounding cur_rounding = PossibleRounding::TOWARD_ZERO,
               bool is_oper_exist = false, std::int32_t second_number = 0,
               PossibleOperations cur_operation = PossibleOperations::NO_OPER);

    [[nodiscard]]
    std::int32_t get_first_number() const noexcept;
    [[nodiscard]]
    std::int32_t get_second_number() const noexcept;
    [[nodiscard]]
    std::int32_t get_cnt_for_integer() const noexcept;
    [[nodiscard]]
    std::int32_t get_cnt_for_fractional() const noexcept;
    [[nodiscard]]
    PossibleOperations get_cur_operation() const noexcept;
    [[nodiscard]]
    PossibleRounding get_cur_rounding() const noexcept;
    [[nodiscard]]
    bool is_operation_exist() const noexcept;

  private:
    bool _is_operation_exist;
    std::int32_t _cnt_for_integer;
    std::int32_t _cnt_for_fractional;
    std::int32_t _first_number;
    std::int32_t _second_number;
    PossibleRounding _cur_rounding;
    PossibleOperations _cur_operation;
};