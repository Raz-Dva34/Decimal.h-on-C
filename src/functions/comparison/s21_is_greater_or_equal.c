#include "../../s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  return s21_is_equal(d1, d2) == 1 || s21_is_greater(d1, d2) == 1 ? 1 : 0;
}
