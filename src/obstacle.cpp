#include "headers/obstacle.hpp"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int32_t> dist_pos_x(5, 350);

