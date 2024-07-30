#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 7.9228162514264337593543950335e28

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  int bits[7];
} s21_decimal_long;

// arithmetic operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result);

// comparison opeartors
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_is_less_long(s21_decimal_long v1, s21_decimal_long v2);
int s21_is_less_or_equal_long(s21_decimal_long v1, s21_decimal_long v2);

// convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// another functions
int s21_floor(
    s21_decimal value,
    s21_decimal *result);  // Rounds a specified Decimal number to the
                           // closest integer toward negative infinity.
int s21_round(
    s21_decimal value,
    s21_decimal *result);  // Rounds a decimal value to the nearest integer.
int s21_truncate(
    s21_decimal value,
    s21_decimal *
        result);  // Returns the integral digits of the specified Decimal; any
                  // fractional digits are discarded, including trailing zeroes.
int s21_negate(
    s21_decimal value,
    s21_decimal *result);  // Returns the result of multiplying the
                           // specified Decimal value by negative one.

// additional functions
int s21_get_bit(s21_decimal d, int index);
int s21_get_bit_long(s21_decimal_long number, int index);
int s21_get_sign(s21_decimal d);
int s21_get_sign_long(s21_decimal_long dst);
int s21_get_scale(s21_decimal d);
int s21_get_scale_long(s21_decimal_long dec);

void s21_set_bit_1(s21_decimal *dec, int bit);  //устанавливает бит в 1.
void s21_set_bit_0(s21_decimal *dec, int bit);  //устанавливает бит в 0.
void s21_set_bit_1_long(s21_decimal_long *dec, int bit);
void s21_set_bit_0_long(s21_decimal_long *dec, int bit);
void s21_set_scale(s21_decimal *d, int scale);
void s21_set_scale_long(s21_decimal_long *dec, unsigned int scale);
void s21_set_sign(s21_decimal *dec, unsigned int sign);
void s21_set_sign_long(s21_decimal_long *dec, unsigned int znak);

void s21_zeroing_decimal(s21_decimal *d);
void s21_zeroing_decimal_long(s21_decimal_long *dst);
void s21_decimal_copy(s21_decimal original, s21_decimal *copy);
void s21_decimal_copy_long(s21_decimal_long original, s21_decimal_long *copy);
void s21_normalize_long(s21_decimal_long *a, s21_decimal_long *b);
void s21_copy_decimal_in_long(s21_decimal a, s21_decimal_long *b);
void s21_copy_long_in_decimal(s21_decimal_long a, s21_decimal *b);
int s21_add_int(s21_decimal num1, s21_decimal num2, s21_decimal *res);
int s21_add_int_long(s21_decimal_long num1, s21_decimal_long num2,
                     s21_decimal_long *res);
void s21_subtraction_int(s21_decimal num1, s21_decimal num2, s21_decimal *res);
void s21_subtraction_int_long(s21_decimal_long num1, s21_decimal_long num2,
                              s21_decimal_long *res);
void s21_inishial(s21_decimal *number, int bit0, int bit1, int bit2, int bit3);
void s21_inishial_long(s21_decimal_long *number, int bit0, int bit1, int bit2,
                       int bit3, int bit4, int bit5, int bit6);
void s21_divide_tens(s21_decimal *value);
int s21_multiplicity(s21_decimal_long a);
void s21_remove_zeros(s21_decimal *value);
int s21_reminder_ten(s21_decimal value);
void s21_import_to_small_decimal(s21_decimal_long a, s21_decimal *b);
int s21_bit_shift(s21_decimal *a, int shift);
int s21_bit_shift_long(s21_decimal_long *a, int shift);

int s21_comparison(s21_decimal d1, s21_decimal d2);
int s21_compare_sign(s21_decimal d1, s21_decimal d2);

s21_decimal s21_divide_int(s21_decimal num1, s21_decimal num2,
                           s21_decimal *res);
s21_decimal_long s21_int_divide_long_int(s21_decimal_long num1,
                                         s21_decimal_long num2,
                                         s21_decimal_long *res);

#endif  // SRC_S21_DECIMAL_H_
