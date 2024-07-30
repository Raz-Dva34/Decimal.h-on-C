# s21_decimal

Implementation of your own library s21_decimal.h.

## Introduction

In this project, you have implemented the library s21_decimal.h in the C programming language. This library should add the ability to work with the "decimal" type, which is not included in the language standard. However, this type is critically important, for example, for financial calculations, where calculation errors inherent in floating-point types are unacceptable. Within the framework of this project, you will become familiar with the tasks of processing financial information, delve into the issues of internal representation of various data types and consolidate the structured approach.

## Chapter II

## Information

The Decimal type represents decimal numbers in the range of positive 79,228,162,514,264,337,593,543,950,335 to negative 79,228,162,514,264,337,593,543,950,335. The default Decimal value is 0. Decimal is suitable for financial calculations that require a large number of significant integer and fractional digits and no rounding errors. This type does not eliminate the need for rounding. Rather, it minimizes the errors caused by rounding.

When the result of division and multiplication is passed to a rounding method, the result does not suffer from loss of precision.

A Decimal number is a floating-point value consisting of a sign, a numeric value where each digit is in the range 0 to 9, and a scaling factor that specifies the position of the decimal point separating the integer and fractional parts of the numeric value.

The binary representation of Decimal consists of a 1-bit sign, a 96-bit integer, and a scaling factor used to divide the 96-bit integer and specify which part of it is a decimal fraction. The scaling factor is implicitly equal to 10 raised to a power of 0 to 28. Therefore, the binary representation of Decimal is ((-2^96 to 2^96) / 10^(0 to 28)), where -(2^96-1) is the minimum value and 2^96-1 is the maximum value.

The scaling factor can also preserve any trailing zeros in Decimal. These trailing zeros do not affect the value in arithmetic or comparison operations.

### Binary Representation

The binary representation of Decimal consists of a 1-bit sign, a 96-bit integer, and a scaling factor used to divide the integer and indicate which part of it is a decimal fraction. The scaling factor is implicitly equal to 10 raised to a power of 0 through 28.

A Decimal number can be implemented as a four-element array of 32-bit signed integers (`int bits[4];`).

`bits[0]`, `bits[1]`, and `bits[2]` contain the low-order, middle, and high-order 32 bits of the 96-bit integer, respectively.

`bits[3]` contains the scaling factor and sign, and consists of the following parts:
- Bits 0 through 15, the low-order word, are unused and must be zero;
- Bits 16 through 23 must contain an exponent from 0 through 28 that specifies the power of 10 to divide the integer into;
- Bits 24 through 30 are unused and must be zero;
- Bit 31 contains the sign; 0 means positive, and 1 means negative.

Note that the bit representation distinguishes between negative and positive zeros. These values ​​can be considered equivalent for all operations.

### Example:

```c
typedef struct
{
int bits[4];
} s21_decimal;
```

### Arithmetic Operators

| Operator Name | Operator | Function |
| ------ | ------ |--------------------------------------------------------------------|
| Addition | + | int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Subtraction | - | int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Multiplication | * | int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Division | / | int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |

Functions return an error code:
- 0 - OK
- 1 - the number is too large or equal to infinity
- 2 - the number is too small or equal to negative infinity
- 3 - division by 0

*Clarification about numbers that do not fit into the mantissa:*
- *When receiving numbers that do not fit into the mantissa during arithmetic operations, use banker's rounding (for example, 79,228,162,514,264,337,593,543,950,335 - 0.6 = 79,228,162,514,264,337,593,543,950,334)*

### Comparison operators

| Operator name | Operator | Function |
| ------ | ------ | ------ |
| Less than | < | int s21_is_less(s21_decimal, s21_decimal) |
| Less than or equal to | <= | int s21_is_less_or_equal(s21_decimal, s21_decimal) |
| Greater than | \> | int s21_is_greater(s21_decimal, s21_decimal) |
| Greater than or equal to | \>= | int s21_is_greater_or_equal(s21_decimal, s21_decimal) |
| Equal to | == | int s21_is_equal(s21_decimal, s21_decimal) |
| Not equal to | != | int s21_is_not_equal(s21_decimal, s21_decimal) |

Return value: - 0 - FALSE - 1 - TRUE ### Converters | Converter | Function |
| ------ | ------ |
| From int | int s21_from_int_to_decimal(int src, s21_decimal *dst) |
| From float | int s21_from_float_to_decimal(float src, s21_decimal *dst) |
| In int | int s21_from_decimal_to_int(s21_decimal src, int *dst) |
| to float | int s21_from_decimal_to_float(s21_decimal src, float *dst) |

Return value - error code:
- 0 - OK
- 1 - conversion error

*Clarification about converting a float number:*
- *If the numbers are too small (0 < |x| < 1e-28), return an error and a value of 0*
- *If the numbers are too large (|x| > 79,228,162,514,264,337,593,543,950,335) or equal to infinity, return an error*
- *When processing a float number, convert all significant decimal digits it contains. If there are more than 7 such digits, the value of the number is rounded to the nearest one that has no more than 7 significant digits.*

*Clarification about converting from a decimal number to an int number:*
- *If a decimal number has a fractional part, it should be discarded (for example, 0.9 is converted to 0)*

### Other functions

| Description | Function |
| ------ |----------------------------------------------------------|
| Rounds the specified Decimal to the nearest integer, toward negative infinity. | int s21_floor(s21_decimal value, s21_decimal *result) |
| Rounds the Decimal to the nearest integer. | int s21_round(s21_decimal value, s21_decimal *result) |
| Returns the whole digits of the specified Decimal; any fractional digits are discarded, including trailing zeros. | int s21_truncate(s21_decimal value, s21_decimal *result) |
| Returns the result of multiplying the specified Decimal by -1. | int s21_negate(s21_decimal value, s21_decimal *result) |

Return value - error code:
- 0 - OK
- 1 - calculation error

## Chapter III

## Part 1. Implementation of the decimal.h library function

- The library is developed in the C language of the C11 standard using the gcc compiler;
- A Makefile is provided for building the library and tests (with the all, clean, test, s21_decimal.a, gcov_report targets);
- The gcov_report target must generate a gcov report as an html page. For this, unit tests must be run with the gcov flags;
- The defined type supports numbers from -79,228,162,514,264,337,593,543,950,335 to +79,228,162,514,264,337,593,543,950,335.
