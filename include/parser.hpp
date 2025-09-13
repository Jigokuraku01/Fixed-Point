#pragma once
#include "input_query.hpp"
#include <string>
#include <vector>

class Parser {
  public:
    static InputQuery parse_input_query(const std::vector<std::string>&& argv);
};
