#include "../../s21_decimal.h"

/// @brief первое число меньше второго
/// @param d1
/// @param d2
/// @return 0 - false, 1 - true

int s21_is_less(s21_decimal d1, s21_decimal d2) {
  int flag = 0;
  if (s21_compare_sign(d1, d2) == 1) {
    flag = 1;
  }
  if (s21_compare_sign(d1, d2) == 0 || s21_compare_sign(d1, d2) == 3) {
    if (s21_comparison(d1, d2) == 2)
      flag = 1;
    else
      flag = 0;
    if (s21_compare_sign(d1, d2) == 3 && s21_comparison(d1, d2) != 0) {
      flag = !flag;
    }
  }
  return flag;
}

int s21_is_less_long(s21_decimal_long v1, s21_decimal_long v2) {
  int exit = 0;
  int res = 1;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  s21_decimal_copy_long(v1, &val_1);
  s21_decimal_copy_long(v2, &val_2);
  s21_normalize_long(&val_1, &val_2);
  if (s21_get_bit_long(val_1, 223) == 1 && s21_get_bit_long(val_2, 223) == 0) {
    res = 1;
    exit = 1;
  }
  if (s21_get_bit_long(val_1, 223) == s21_get_bit_long(val_2, 223)) {
    for (int i = 191; i >= 0 && !exit; i--) {
      if (s21_get_bit_long(val_1, i) == 1 && s21_get_bit_long(val_2, i) == 0) {
        res = 0;
        exit = 1;
      }
      if (s21_get_bit_long(val_1, i) == 0 && s21_get_bit_long(val_2, i) == 1) {
        res = 1;
        exit = 1;
      }
    }
    if (s21_get_sign_long(val_1)) {
      res = !res;
    }
  }
  return res;
}