#include "../../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  s21_decimal_copy(value, result);
  if (value.bits[0] || value.bits[1] || value.bits[2]) {
    error = s21_get_scale(value) - 1;
    if (error + 1 > 0) {
      s21_decimal tmp_10 = {{10, 0, 0, 0}};
      s21_decimal ost = {0};
      int znak = s21_get_sign(value);
      value.bits[3] = 0;
      while (error--) {
        s21_divide_int(value, tmp_10, &value);
      }
      s21_decimal_copy(s21_divide_int(value, tmp_10, result), &ost);
      if (ost.bits[0] > 4) {
        s21_inishial(&tmp_10, 1, 0, 0, 0);
        s21_add_int(*result, tmp_10, result);
      }
      s21_set_scale(result, 0);
      s21_set_sign(result, znak);
    }
    error = 0;
  }
  return error;
}
