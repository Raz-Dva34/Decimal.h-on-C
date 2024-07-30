#include "../../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  s21_zeroing_decimal(dst);
  if (src < 0) {
    dst->bits[3] = 1u << 31;
    src *= -1;
  }
  if (src < INT_MAX)
    dst->bits[0] = src;
  else
    res = 1;

  return res;
}