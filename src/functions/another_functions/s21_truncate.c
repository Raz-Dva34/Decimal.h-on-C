#include "../../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int exp = s21_get_scale(value);
  while (exp) {
    s21_divide_tens(&value);
    exp--;
  }
  exp = exp << 16;
  if (s21_get_sign(value)) {
    exp |= 1 << 31;
  }
  value.bits[3] = exp;
  s21_decimal_copy(value, result);
  return error;
}
