#include "../../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  s21_decimal_long res = {0};
  int znak_1 = s21_get_sign(value_1);
  int znak_2 = s21_get_sign(value_2);
  s21_set_bit_0(&value_1, 127);
  s21_set_bit_0(&value_2, 127);
  s21_copy_decimal_in_long(value_1, &val_1);
  s21_copy_decimal_in_long(value_2, &val_2);
  int smeshenie = 0;
  if (znak_1 != znak_2) {
    s21_normalize_long(&val_1, &val_2);
    s21_add_int_long(val_1, val_2, &res);
    if (s21_get_bit_long(val_1, 223)) {
      s21_set_bit_1_long(&res, 223);
    } else {
      s21_set_bit_0_long(&res, 223);
    }
    s21_set_scale_long(&res, s21_get_scale_long(val_1));
    smeshenie = s21_get_scale_long(res);

  } else {
    if (!s21_is_less_or_equal(value_2, value_1)) {
      s21_copy_decimal_in_long(value_2, &val_1);
      s21_copy_decimal_in_long(value_1, &val_2);
      znak_1 = !znak_2;
    }
    s21_normalize_long(&val_1, &val_2);
    s21_subtraction_int_long(val_1, val_2, &res);
    s21_set_sign_long(&res, znak_1);
    smeshenie = s21_get_scale_long(res);
  }
  while (res.bits[3] || res.bits[4] || res.bits[5]) {
    smeshenie--;
    s21_decimal_long tmp_10 = {0};
    s21_decimal_long ost = {0};
    s21_decimal_long musor = {0};
    tmp_10.bits[0] = 10;
    s21_decimal_copy_long(s21_int_divide_long_int(res, tmp_10, &res), &ost);
    if (ost.bits[0] > 4) {
      s21_decimal_copy_long(s21_int_divide_long_int(res, tmp_10, &musor),
                            &tmp_10);
      if (!s21_multiplicity(tmp_10)) {
        s21_decimal_long tmp_1 = {{1, 0, 0, 0, 0, 0, 0}};
        s21_normalize_long(&tmp_1, &res);
        s21_add_int_long(res, tmp_1, &res);
      }
    }
  }
  if (!res.bits[3] && !res.bits[4] && !res.bits[5] && smeshenie >= 0 &&
      smeshenie < 29) {
    s21_import_to_small_decimal(res, result);
    s21_set_scale(result, smeshenie);
    int accur = s21_get_scale(*result);
    s21_set_scale(result, accur);
    s21_set_sign(result, znak_1);
  } else if (znak_1) {
    error = 2;
  } else {
    error = 1;
  }
  return error;
}