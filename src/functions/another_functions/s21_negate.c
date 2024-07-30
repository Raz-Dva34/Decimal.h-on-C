#include "../../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = !s21_get_sign(value);
  s21_decimal_copy(value, result);
  s21_set_sign(result, error);
  error = 0;
  return error;
}