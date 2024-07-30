#include "../../s21_decimal.h"

/// @brief числа равны
/// @param d1
/// @param d2
/// @return 0 - false, 1 - true

int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  int flag = 0;
  if (s21_compare_sign(d1, d2) == 0 || s21_compare_sign(d1, d2) == 3) {
    if (s21_comparison(d1, d2) == 0)
      flag = 1;
    else
      flag = 0;
  } else {
    flag = 0;
  }
  return flag;
}
