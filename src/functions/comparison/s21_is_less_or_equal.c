#include "../../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_is_equal(d1, d2) == 1 || s21_is_less(d1, d2) == 1) ? 1 : 0;
}

int s21_is_less_or_equal_long(s21_decimal_long v1, s21_decimal_long v2) {
  int result = s21_is_less_long(v1, v2);
  if (!result) {
    result = 1;
    s21_decimal_long val_1 = {0};
    s21_decimal_long val_2 = {0};
    s21_decimal_copy_long(v1, &val_1);
    s21_decimal_copy_long(v2, &val_2);
    s21_normalize_long(&val_1, &val_2);
    for (int i = 0; i < 7; i++) {
      if (val_1.bits[i] != val_2.bits[i]) {
        result = 0;
      }
    }
  }
  return result;
}
