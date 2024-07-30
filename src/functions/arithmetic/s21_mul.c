#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal_long long_res = {0};
  s21_decimal_long long_buffer = {0};
  unsigned int mul = 0;
  if ((!value_1.bits[0] && !value_1.bits[1] && !value_1.bits[2]) ||
      (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2])) {
    s21_zeroing_decimal(result);
    s21_set_sign(result, s21_get_sign(value_1) ^ s21_get_sign(value_2));
  } else {
    if (value_1.bits[0] == 1 && !value_1.bits[1] && !value_1.bits[2] &&
        !s21_get_sign(value_1)) {
      s21_copy_decimal_in_long(value_2, &long_res);
    } else if (value_2.bits[0] == 1 && !value_2.bits[1] && !value_2.bits[2] &&
               !s21_get_sign(value_2)) {
      s21_copy_decimal_in_long(value_1, &long_res);
    } else if (value_1.bits[0] == 1 && !value_1.bits[1] && !value_1.bits[2] &&
               s21_get_sign(value_1)) {
      s21_copy_decimal_in_long(value_2, &long_res);
    } else if (value_2.bits[0] == 1 && !value_2.bits[1] && !value_2.bits[2] &&
               s21_get_sign(value_2)) {
      s21_copy_decimal_in_long(value_1, &long_res);
    } else {
      for (int g = 0; g < 96; g++) {
        s21_zeroing_decimal_long(&long_buffer);
        for (int i = 0; i < 96; i++) {
          mul = s21_get_bit(value_1, i) & s21_get_bit(value_2, g);
          if (mul) {
            s21_set_bit_1_long(&long_buffer, g + i);
          }
        }
        if (long_res.bits[5] < 1073741823) {
          s21_add_int_long(long_res, long_buffer, &long_res);
        }
      }
    }
    int znak = s21_get_bit(value_1, 127) ^ s21_get_bit(value_2, 127);
    mul = (s21_get_scale(value_1) + s21_get_scale(value_2));
    while ((long_res.bits[3] || long_res.bits[4] || long_res.bits[5] ||
            mul > 28) &&
           mul > 0) {
      mul--;
      s21_decimal_long tmp_10 = {0};
      s21_decimal_long ost = {0};
      s21_decimal_long musor = {0};
      tmp_10.bits[0] = 10;
      s21_decimal_copy_long(
          s21_int_divide_long_int(long_res, tmp_10, &long_res), &ost);
      if (ost.bits[0] == 5) {
        s21_decimal_copy_long(s21_int_divide_long_int(long_res, tmp_10, &musor),
                              &tmp_10);
        if (!s21_multiplicity(tmp_10)) {
          s21_decimal_long tmp_1 = {{1, 0, 0, 0, 0, 0, 0}};
          s21_normalize_long(&tmp_1, &long_res);
          s21_add_int_long(long_res, tmp_1, &long_res);
        }
      } else if (ost.bits[0] > 4) {
        s21_decimal_long tmp_1 = {{1, 0, 0, 0, 0, 0, 0}};
        s21_normalize_long(&tmp_1, &long_res);
        s21_add_int_long(long_res, tmp_1, &long_res);
      }
    }
    if (long_res.bits[3] != 0 || long_res.bits[4] != 0 ||
        long_res.bits[5] != 0 || mul > 29) {
      if (!znak) {
        error = 1;
      } else {
        error = 2;
      }
    } else {
      if (mul <= 28) {
        s21_import_to_small_decimal(long_res, result);
        s21_set_scale(result, mul);
        s21_set_sign(result, znak);
      } else {
        error = 1;
      }
    }
  }
  return error;
}
