#include "../s21_decimal.h"

int s21_get_bit(s21_decimal d, int index) {
  return (d.bits[index / 32]) >> (index % 32) & 1;
}

int s21_get_scale(s21_decimal d) {
  unsigned int mask = 31 << 16;
  return (d.bits[3] & mask) >> 16;
}

int s21_get_sign(s21_decimal d) { return (d.bits[3] & (1 << 31)) == 0 ? 0 : 1; }

void s21_set_sign_long(s21_decimal_long *dec, unsigned int znak) {
  (*dec).bits[6] = ((*dec).bits[6]) & (~(1 << 31));
  if (znak == 1) {
    (*dec).bits[6] = ((*dec).bits[6]) | (1 << 31);
  }
}

void s21_zeroing_decimal(s21_decimal *d) {
  for (int i = 0; i < 4; i++) {
    d->bits[i] = 0;
  }
}

void s21_zeroing_decimal_long(s21_decimal_long *dst) {
  for (int i = 0; i < 7; i++) {
    dst->bits[i] = 0;
  }
}

void s21_set_scale(s21_decimal *d, int scale) {
  if (scale >= 0) {
    (*d).bits[3] = ((*d).bits[3]) & (0xFF00FFFF);
    (*d).bits[3] = (*d).bits[3] | ((scale) << 16);
  }
}

int s21_add_int(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  (*res).bits[0] = 5;
  int signal = 0;
  s21_zeroing_decimal(res);
  s21_decimal_long lres = {0};
  unsigned int carry = 0;
  for (int i = 0; i < 96; i++) {
    carry += s21_get_bit(num1, i) + s21_get_bit(num2, i);
    if ((carry % 2)) {
      s21_set_bit_1_long(&lres, i);
    }
    carry /= 2;
  }
  if (carry) {
    s21_set_bit_1_long(&lres, 96);
    signal = 1;
  }
  if (!signal) {
    for (int i = 0; i < 3; i++) {
      (*res).bits[i] = lres.bits[i];
    }
    (*res).bits[3] = num1.bits[3];
  }
  return signal;
}

int s21_add_int_long(s21_decimal_long num1, s21_decimal_long num2,
                     s21_decimal_long *res) {
  int signal = 0;
  for (int i = 0; i < 7; i++) {
    (*res).bits[i] = 0;
  }
  unsigned int carry = 0;
  s21_decimal_long num_1 = {0};
  s21_decimal_long num_2 = {0};
  for (int k = 0; k < 7; k++) {
    num_1.bits[k] = num1.bits[k];
    num_2.bits[k] = num2.bits[k];
  }
  for (int i = 0; i < 192; i++) {
    carry += s21_get_bit_long(num_1, i) + s21_get_bit_long(num_2, i);
    if ((carry % 2)) {
      s21_set_bit_1_long(res, i);
    }
    carry /= 2;
  }
  if (carry) {
    signal = 1;
  }
  (*res).bits[6] = num_1.bits[6];
  return signal;
}

int s21_bit_shift(s21_decimal *a, int shift) {
  int error = 0;
  if (shift == -1) {
    for (int i = 0; i < 95; i++) {
      if (s21_get_bit(*a, i + 1)) {
        s21_set_bit_1(a, i);
      } else {
        s21_set_bit_0(a, i);
      }
    }
    s21_set_bit_0(a, 95);
  } else if (!s21_get_bit(*a, 95)) {
    for (int i = 95; i > 0; i--) {
      if (s21_get_bit(*a, i - 1)) {
        s21_set_bit_1(a, i);
      } else {
        s21_set_bit_0(a, i);
      }
    }
    s21_set_bit_0(a, 0);
  } else {
    error = 1;
  }
  return error;
}

int s21_bit_shift_long(s21_decimal_long *a, int shift) {
  int error = 0;
  if (shift == -1) {
    for (int i = 0; i < 191; i++) {
      if (s21_get_bit_long(*a, i + 1)) {
        s21_set_bit_1_long(a, i);
      } else {
        s21_set_bit_0_long(a, i);
      }
    }
    s21_set_bit_0_long(a, 191);
  } else if (!s21_get_bit_long(*a, 191)) {
    for (int i = 191; i > 0; i--) {
      if (s21_get_bit_long(*a, i - 1)) {
        s21_set_bit_1_long(a, i);
      } else {
        s21_set_bit_0_long(a, i);
      }
    }
    s21_set_bit_0_long(a, 0);
  } else {
    error = 1;
  }
  return error;
}

void s21_decimal_copy(s21_decimal original, s21_decimal *copy) {
  for (int i = 0; i < 4; i++) {
    (*copy).bits[i] = original.bits[i];
  }
}

void s21_decimal_copy_long(s21_decimal_long original, s21_decimal_long *copy) {
  for (int i = 0; i < 7; i++) {
    (*copy).bits[i] = original.bits[i];
  }
}

void s21_copy_long_in_decimal(s21_decimal_long a, s21_decimal *b) {
  for (int i = 0; i < 3; i++) {
    (*b).bits[i] = a.bits[i];
  }
  (*b).bits[3] = a.bits[6];
}

void s21_divide_tens(s21_decimal *value) {
  long long int buf = (unsigned int)value->bits[2];
  long long int mod_res;
  for (int i = 2; i >= 0; i--) {
    mod_res = buf % 10;
    value->bits[i] = (unsigned int)(buf / 10);
    if (i) {
      buf = mod_res << 32;
      buf += (unsigned int)value->bits[i - 1];
    }
  }
}

void s21_set_sign(s21_decimal *dec, unsigned int sign) {
  (*dec).bits[3] = ((*dec).bits[3]) & (~(1 << 31));
  if (sign == 1) {
    (*dec).bits[3] = ((*dec).bits[3]) | (1 << 31);
  }
}

int s21_get_bit_long(s21_decimal_long dec, int bit) {
  int index = bit / 32;
  int shift = bit % 32;
  unsigned int shifted_value = dec.bits[index] >> shift;
  int bit_value = shifted_value & 1;
  return bit_value;
}

void s21_inishial(s21_decimal *number, int bit0, int bit1, int bit2, int bit3) {
  (*number).bits[0] = bit0;
  (*number).bits[1] = bit1;
  (*number).bits[2] = bit2;
  (*number).bits[3] = bit3;
}

s21_decimal s21_divide_int(s21_decimal num1, s21_decimal num2,
                           s21_decimal *res) {
  if (num2.bits[0] || num2.bits[1] || num2.bits[2]) {
    s21_decimal_long result = {0};
    s21_decimal num2_copy = {0};
    s21_decimal_long _2_in_step = {0};
    s21_decimal_copy(num2, &num2_copy);
    int znak = s21_get_sign(num1) ^ s21_get_sign(num2);
    s21_set_bit_0(&num1, 127);
    s21_set_bit_0(&num2, 127);
    while (s21_is_less_or_equal(num2, num1)) {
      s21_decimal_copy(num2, &num2_copy);
      s21_zeroing_decimal_long(&_2_in_step);
      _2_in_step.bits[0] = 1;
      while (1) {
        s21_bit_shift(&num2_copy, 1);
        s21_bit_shift_long(&_2_in_step, 1);
        if (!s21_is_less_or_equal(num2_copy, num1)) {
          s21_bit_shift(&num2_copy, -1);
          s21_bit_shift_long(&_2_in_step, -1);
          break;
        }
      }
      s21_add_int_long(result, _2_in_step, &result);
      s21_subtraction_int(num1, num2_copy, &num1);
    }
    if (!result.bits[3] && !result.bits[4] && !result.bits[5]) {
      s21_copy_long_in_decimal(result, res);
    }
    s21_set_sign(res, znak);
  }
  return num1;
}

void s21_subtraction_int(s21_decimal num1, s21_decimal num2, s21_decimal *res) {
  int sub_bit = 0;
  s21_decimal num11 = {0};
  s21_decimal num22 = {0};
  s21_decimal_copy(num1, &num11);
  s21_decimal_copy(num2, &num22);
  for (int i = 0; i < 96; i++) {
    sub_bit = s21_get_bit(num1, i) - s21_get_bit(num2, i);
    if (sub_bit > 0) {
      s21_set_bit_1(res, i);
    } else if (!sub_bit) {
      s21_set_bit_0(res, i);
    } else {
      int index_now_bit = i + 1;
      while (index_now_bit < 96 && !s21_get_bit(num1, index_now_bit)) {
        s21_set_bit_1(&num1, index_now_bit);
        index_now_bit++;
      }
      s21_set_bit_0(&num1, index_now_bit);
      s21_set_bit_1(res, i);
    }
  }
}

void s21_subtraction_int_long(s21_decimal_long num1, s21_decimal_long num2,
                              s21_decimal_long *res) {
  int sub_bit = 0;
  s21_decimal_long num11 = {0};
  s21_decimal_long num22 = {0};
  s21_decimal_copy_long(num1, &num11);
  s21_decimal_copy_long(num2, &num22);
  for (int i = 0; i < 192; i++) {
    sub_bit = s21_get_bit_long(num1, i) - s21_get_bit_long(num2, i);
    if (sub_bit > 0) {
      s21_set_bit_1_long(res, i);
    } else if (sub_bit == 0) {
      s21_set_bit_0_long(res, i);
    } else if (sub_bit < 0) {
      int index_now_bit = i + 1;
      while (index_now_bit < 192 && !s21_get_bit_long(num1, index_now_bit)) {
        s21_set_bit_1_long(&num1, index_now_bit);
        index_now_bit++;
      }
      s21_set_bit_0_long(&num1, index_now_bit);
      s21_set_bit_1_long(res, i);
    }
  }
  (*res).bits[6] = num1.bits[6];
}

int s21_reminder_ten(s21_decimal value) {
  long long int remainder = (unsigned int)value.bits[2];
  for (int i = 2; i >= 0; i--) {
    remainder = remainder % 10;
    if (i) {
      remainder = remainder << 32;
      remainder += (unsigned int)value.bits[i - 1];
    }
  }
  return (int)remainder;
}

void s21_remove_zeros(s21_decimal *value) {
  int exp = s21_get_scale(*value);
  while (exp && !s21_reminder_ten(*value)) {
    s21_divide_tens(value);
    s21_set_scale(value, --exp);
  }
}

s21_decimal_long s21_int_divide_long_int(s21_decimal_long num1,
                                         s21_decimal_long num2,
                                         s21_decimal_long *res) {
  s21_decimal_long result = {0};
  s21_decimal_long num2_copy = {0};
  s21_decimal_long _2_in_step = {0};
  s21_decimal_copy_long(num2, &num2_copy);
  int znak = !(s21_get_sign_long(num1) == s21_get_sign_long(num2));
  num1.bits[6] = 0;
  num2.bits[6] = 0;
  while (s21_is_less_or_equal_long(num2, num1)) {
    s21_decimal_copy_long(num2, &num2_copy);
    s21_zeroing_decimal_long(&_2_in_step);
    _2_in_step.bits[0] = 1;
    while (1) {
      s21_bit_shift_long(&num2_copy, 1);
      s21_bit_shift_long(&_2_in_step, 1);
      if (!s21_is_less_or_equal_long(num2_copy, num1)) {
        s21_bit_shift_long(&num2_copy, -1);
        s21_bit_shift_long(&_2_in_step, -1);
        break;
      }
    }
    s21_add_int_long(result, _2_in_step, &result);
    s21_subtraction_int_long(num1, num2_copy, &num1);
  }
  s21_decimal_copy_long(result, res);
  s21_set_sign_long(res, znak);
  return num1;
}

int s21_get_sign_long(s21_decimal_long dst) {  // знак
  return (dst.bits[6] & (1 << 31)) == 0 ? 0 : 1;
}

void s21_set_bit_0(s21_decimal *dec, int bit) {
  int element_index = bit / 32;
  int bit_index = bit % 32;
  (*dec).bits[element_index] =
      ((*dec).bits[element_index]) & (~(1 << bit_index));
}

void s21_set_bit_1(s21_decimal *dec, int bit) {
  int element_index = bit / 32;
  int bit_index = bit % 32;
  (*dec).bits[element_index] = ((*dec).bits[element_index]) | (1 << bit_index);
}

void s21_set_bit_0_long(s21_decimal_long *dec, int bit) {
  int index = bit / 32;
  int offset = bit % 32;
  int mask = ~(1 << offset);
  (*dec).bits[index] = ((*dec).bits[index]) & mask;
}

void s21_set_bit_1_long(s21_decimal_long *dec, int bit) {
  s21_set_bit_0_long(dec, bit);
  int index = bit / 32;
  int offset = bit % 32;
  int mask = 1 << offset;
  (*dec).bits[index] = ((*dec).bits[index]) | mask;
}

void s21_copy_decimal_in_long(s21_decimal a, s21_decimal_long *b) {
  for (int i = 0; i < 3; i++) {
    (*b).bits[i] = a.bits[i];
  }
  (*b).bits[6] = a.bits[3];
}

void s21_normalize_long(s21_decimal_long *a, s21_decimal_long *b) {
  int accur_1 = s21_get_scale_long(*a);
  int accur_2 = s21_get_scale_long(*b);
  int razn_accur = accur_1 - accur_2;
  s21_decimal_long int_10 = {0};
  int_10.bits[0] = 10;
  if (razn_accur > 0) {
    for (int i = 0; i < razn_accur; i++) {
      s21_mul_long(*b, int_10, b);
    }
    s21_set_scale_long(b, accur_1);
  }
  if (razn_accur < 0) {
    for (int i = 0; i < (-1) * razn_accur; i++) {
      s21_mul_long(*a, int_10, a);
    }
    s21_set_scale_long(a, accur_2);
  }
}

int s21_get_scale_long(s21_decimal_long dec) {
  int res = ((dec.bits[6] >> 16) & 31);
  if (res > 28) {
    res = 0;
  }
  return res;
}

int s21_mul_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result) {
  int error = 0;
  s21_decimal_long long_res = {0};
  s21_decimal_long long_buffer = {0};
  unsigned int mul = 0;
  for (int g = 0; g < 191; g++) {
    s21_zeroing_decimal_long(&long_buffer);
    for (int i = 0; i < 191; i++) {
      mul = s21_get_bit_long(value_1, i) & s21_get_bit_long(value_2, g);
      if (mul) {
        s21_set_bit_1_long(&long_buffer, g + i);
      }
    }
    s21_add_int_long(long_res, long_buffer, &long_res);
  }
  for (int k = 0; k < 6; k++) {
    (*result).bits[k] = long_res.bits[k];
  }
  mul = (s21_get_scale_long(value_1) + s21_get_scale_long(value_2));
  s21_set_scale_long(result, mul);
  if (s21_get_bit_long(value_1, 223) != s21_get_bit_long(value_2, 223)) {
    s21_set_bit_1_long(result, 223);
  }
  return error;
}

void s21_set_scale_long(s21_decimal_long *dec, unsigned int scale) {
  (*dec).bits[6] = ((*dec).bits[6]) & (0xFF00FFFF);
  (*dec).bits[6] = (*dec).bits[6] | ((scale) << 16);
}

int s21_multiplicity(s21_decimal_long a) {
  s21_decimal_long tmp_2 = {{2, 0, 0, 0, 0, 0}};
  s21_decimal_long ost = {0};
  s21_decimal_copy_long(a, &ost);
  s21_normalize_long(&tmp_2, &ost);
  s21_decimal_copy_long(s21_int_divide_long_int(ost, tmp_2, &ost), &ost);
  int i = 0;
  for (; i < 6; i++) {
    if (ost.bits[i] != 0) {
      break;
    }
  }
  if (i < 5) {
    i = 0;
  } else {
    i = 1;
  }
  return i;
}

void s21_import_to_small_decimal(s21_decimal_long a, s21_decimal *b) {
  for (int i = 0; i < 3; i++) {
    (*b).bits[i] = a.bits[i];
  }
  (*b).bits[3] = a.bits[6];
}

void s21_inishial_long(s21_decimal_long *number, int bit0, int bit1, int bit2,
                       int bit3, int bit4, int bit5, int bit6) {
  (*number).bits[0] = bit0;
  (*number).bits[1] = bit1;
  (*number).bits[2] = bit2;
  (*number).bits[3] = bit3;
  (*number).bits[4] = bit4;
  (*number).bits[5] = bit5;
  (*number).bits[6] = bit6;
}