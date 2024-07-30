#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = 0;
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(src, i)) *dst += pow(2, i);
  }
  *dst /= pow(10, s21_get_scale(src));
  if (s21_get_sign(src)) *dst *= -1;
  return 0;
}