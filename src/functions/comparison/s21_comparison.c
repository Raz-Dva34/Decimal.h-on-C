#include "../../s21_decimal.h"

/// @brief функция сравнения
/// @param d1
/// @param d2
/// @return 0 - биты равны, 1 - биты первого числа больше второго, 2 - биты
/// первого числа меньше второго
int s21_comparison(s21_decimal d1, s21_decimal d2) {
  int res = 0;
  s21_decimal_long val_1 = {0};
  s21_decimal_long val_2 = {0};
  s21_copy_decimal_in_long(d1, &val_1);
  s21_copy_decimal_in_long(d2, &val_2);
  s21_normalize_long(&val_1, &val_2);
  unsigned int bit_d1 = 0, bit_d2 = 0;
  for (int i = 191; i >= 0; --i) {
    if (!res) {
      bit_d1 = s21_get_bit_long(val_1, i);
      bit_d2 = s21_get_bit_long(val_2, i);
      if (bit_d1 == bit_d2) {
        res = 0;
      } else if (bit_d1 > bit_d2) {
        res = 1;
      } else if (bit_d1 < bit_d2) {
        res = 2;
      }
    }
  }
  return res;
}

int s21_compare_sign(s21_decimal d1, s21_decimal d2) {
  int res = 0;
  int sign_d1 = s21_get_sign(d1);
  int sign_d2 = s21_get_sign(d2);
  if (sign_d1 == 0 && sign_d2 == 0) {  // если знаки равны и положительны
    res = 0;
  } else if (sign_d1 == 1 &&
             sign_d2 == 1) {  // если знаки равны, и они отрицательные
    res = 3;
  } else if (sign_d1 > sign_d2) {  // если знак первого числа отрицательный, а
                                   // второго положительный
    res = 1;
  } else if (sign_d1 < sign_d2) {  // если знак первого положительный, а вторго
                                   // отрицательный
    res = 2;
  }
  return res;
}
