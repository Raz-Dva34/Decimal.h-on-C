#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  if (src != src || fabs(src) > MAX) {
    error = 1;
  } else if (fabs(src) < 1e-28 && fabs(src) > 0) {
    error = 1;
    s21_zeroing_decimal(dst);
  } else {
    double result = src;
    int exp = 0;
    s21_zeroing_decimal(dst);
    if (result < 0) {
      s21_negate(*dst, dst);
      result *= -1.0;
    }
    while (result < 999999.9 && exp < 28) {
      exp++;
      result *= 10;
    }
    while (result >= 9999999.9) {
      result /= 10;
      exp--;
    }
    dst->bits[0] = (int)round(result);
    if (exp > 0) {
      s21_set_scale(dst, exp);
    }
    while (exp < 0) {
      long long int buf;
      unsigned int overflow = 0;
      for (int i = 0; i < 3; i++) {
        buf = (unsigned int)dst->bits[i];
        buf *= 10;
        buf += overflow;
        overflow = buf >> 32;
        dst->bits[i] = (unsigned int)buf;
      }
      exp++;
    }
    s21_remove_zeros(dst);
  }
  return error;
}
