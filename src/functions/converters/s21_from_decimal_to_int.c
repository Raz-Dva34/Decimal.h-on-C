#include "../../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  if (src.bits[1] || src.bits[2] || s21_get_bit(src, 31) != 0)
    res = 1;
  else
    *dst = src.bits[0];
  *dst /= pow(10, s21_get_scale(src));
  if (s21_get_sign(src)) *dst *= -1;
  return res;
}