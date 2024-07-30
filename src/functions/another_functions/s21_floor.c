#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (value.bits[0] || value.bits[1] || value.bits[2]) {
    int sign = s21_get_sign(value);
    s21_truncate(value, result);
    if (s21_get_sign(value) && s21_get_scale(value) > 0) {
      s21_decimal tmp_1 = {{1, 0, 0, 0}};
      s21_add_int(*result, tmp_1, result);
    }
    s21_set_sign(result, sign);
    error = 0;
  }
  return error;
}
