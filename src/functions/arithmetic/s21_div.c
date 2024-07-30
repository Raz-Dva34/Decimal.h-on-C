#include "../../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  s21_decimal_long res = {0};
  s21_copy_decimal_in_long(value_1, &val_1);
  s21_copy_decimal_in_long(value_2, &val_2);
  int accur_1 = s21_get_scale(value_1);
  int accur_2 = s21_get_scale(value_2);
  int znak = s21_get_sign(value_1) ^ s21_get_sign(value_2);
  s21_decimal_long val_1_10 = {0};
  s21_decimal_long tmp_10 = {{10, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long num_10 = {0};
  val_1.bits[6] = 0;
  s21_decimal_copy_long(val_1, &val_1_10);
  s21_mul_long(val_1_10, tmp_10, &val_1_10);
  for (; error < 6; error++) {
    if (val_2.bits[error]) {
      break;
    }
  }
  if (error < 6) {
    while (val_1_10.bits[5] < 134217727) {
      s21_decimal_copy_long(val_1_10, &val_1);
      s21_mul_long(val_1_10, tmp_10, &val_1_10);
      accur_1++;
    }
    s21_set_scale_long(&val_1, 0);
    s21_set_scale_long(&val_2, 0);
    int smeshenie = (-1) * accur_1 + accur_2;
    if (smeshenie < 0) {
      smeshenie *= -1;
    }
    error = 0;
    s21_decimal_copy_long(s21_int_divide_long_int(val_1, val_2, &res), &val_1);
    s21_inishial_long(&tmp_10, 10, 0, 0, 0, 0, 0, 0);
    while (!res.bits[3] && !res.bits[4] && !res.bits[5]) {
      s21_mul_long(val_1, tmp_10, &val_1);
      s21_mul_long(res, tmp_10, &res);
      s21_inishial_long(&tmp_10, 0, 0, 0, 0, 0, 0, 0);
      s21_decimal_copy_long(s21_int_divide_long_int(val_1, val_2, &tmp_10),
                            &val_1);
      s21_add_int_long(res, tmp_10, &res);
      s21_inishial_long(&tmp_10, 10, 0, 0, 0, 0, 0, 0);
      smeshenie += 1;
    }
    s21_inishial_long(&tmp_10, 10, 0, 0, 0, 0, 0, 0);
    s21_inishial_long(&val_1, 0, 0, 0, 0, 0, 0, 0);
    while (res.bits[3] || res.bits[4] || res.bits[5] || smeshenie > 28) {
      smeshenie--;
      s21_decimal_copy_long(s21_int_divide_long_int(res, tmp_10, &res), &val_1);
    }
    s21_inishial_long(&num_10, 1, 0, 0, 0, 0, 0, 0);
    if (val_1.bits[0] > 4) {
      s21_add_int_long(res, num_10, &res);
    }
    s21_inishial_long(&num_10, 0, 0, 0, 0, 0, 0, 0);
    s21_decimal_copy_long(res, &num_10);
    s21_decimal_copy_long(s21_int_divide_long_int(num_10, tmp_10, &num_10),
                          &val_1);
    while (!val_1.bits[0] && !val_1.bits[1] && !val_1.bits[2] &&
           !val_1.bits[3] && !val_1.bits[4] && !val_1.bits[5] &&
           smeshenie > 0) {
      s21_decimal_copy_long(num_10, &res);
      smeshenie--;
      s21_decimal_copy_long(s21_int_divide_long_int(num_10, tmp_10, &num_10),
                            &val_1);
    }
    if (!res.bits[3] && !res.bits[4] && !res.bits[5] && smeshenie >= 0 &&
        smeshenie < 29) {
      s21_import_to_small_decimal(res, result);
      s21_set_scale(result, smeshenie);
      s21_set_sign(result, znak);
    } else if (znak) {
      error = 2;
    } else {
      error = 1;
    }
  } else {
    error = 3;
  }
  return error;
}