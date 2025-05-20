#include "s21_sprintf.h"

void unsigned_to_string(unsigned long long value, char *str) {
  char temp[100];
  int i = 0;

  do {
    temp[i++] = (value % 10) + '0';
    value /= 10;
  } while (value > 0);

  temp[i] = '\0';

  for (int j = 0; j < i; j++) {
    str[j] = temp[i - j - 1];
  }
  str[i] = '\0';
}

void int_to_string(long long num, char *str, bool is_unsigned) {
  char buffer[1024] = {0};
  int i = 0;
  bool is_negative = false;

  if (!is_unsigned && num < 0) {
    is_negative = true;
    num = -num;
  }

  do {
    buffer[i++] = '0' + (num % 10);
    num /= 10;
  } while (num > 0);

  if (is_negative) buffer[i++] = '-';

  int j = 0;
  while (i > 0) {
    str[j++] = buffer[--i];
  }
  str[j] = '\0';
}

void float_to_string(double num, char *str, int precision) {
  long long int_part = (long long)num;
  int index = 0;

  if (num < 0) {
    str[index++] = '-';
    int_part = -int_part;
    num = -num;
  }

  char buffer[1024];
  int buffer_index = 0;

  if (int_part == 0) {
    buffer[buffer_index++] = '0';
  } else {
    while (int_part > 0) {
      buffer[buffer_index++] = '0' + (int_part % 10);
      int_part /= 10;
    }
  }

  for (int i = buffer_index - 1; i >= 0; i--) {
    str[index++] = buffer[i];
  }

  if (precision > 0) {
    str[index++] = '.';
    double fractional = num - (long long)num;
    fractional += 0.5 / pow(10, precision);
    for (int i = 0; i < precision; i++) {
      fractional *= 10;
      int digit = (int)fractional;
      str[index++] = '0' + digit;
      fractional -= digit;
    }
  }

  str[index] = '\0';
}

int s21_sprintf_parcer(const char **strFormat, Format *format) {
  format->flag_plus = false;
  format->flag_minus = false;
  format->flag_space = false;
  format->width = 0;
  format->precision = -1;
  format->length = 0;

  while (**strFormat == '-' || **strFormat == '+' || **strFormat == ' ') {
    if (**strFormat == '-') format->flag_minus = true;
    if (**strFormat == '+') format->flag_plus = true;
    if (**strFormat == ' ') format->flag_space = true;
    (*strFormat)++;
  }

  while (**strFormat >= '0' && **strFormat <= '9') {
    format->width = format->width * 10 + (**strFormat - '0');
    (*strFormat)++;
  }

  if (**strFormat == '.') {
    (*strFormat)++;
    format->precision = 0;
    while (**strFormat >= '0' && **strFormat <= '9') {
      format->precision = format->precision * 10 + (**strFormat - '0');
      (*strFormat)++;
    }
  }

  if (**strFormat == 'h') {
    format->length = 1;
    (*strFormat)++;
  } else if (**strFormat == 'l') {
    format->length = 2;
    (*strFormat)++;
  }

  return **strFormat;
}

void append_char(char *buff, int *index, char c) {
  buff[*index] = c;
  (*index)++;
}

void append_string(char *buff, int *index, const char *str, int width,
                   bool flag_minus) {
  int len = s21_strlen(str);
  if (width > len && !flag_minus) {
    for (int i = 0; i < width - len; i++) {
      buff[*index] = ' ';
      (*index)++;
    }
  }
  while (*str) {
    buff[*index] = *str;
    (*index)++;
    str++;
  }
  if (width > len && flag_minus) {
    for (int i = 0; i < width - len; i++) {
      buff[*index] = ' ';
      (*index)++;
    }
  }
}

void s21_sprintf_specifier(char *buff, char specifier, int *index, va_list args,
                           Format *format) {
  char temp[1024] = {0};

  switch (specifier) {
    case 'c': {
      char c = (char)va_arg(args, int);
      if (format->width > 1 && !format->flag_minus) {
        for (int i = 0; i < format->width - 1; i++)
          append_char(buff, index, ' ');
      }
      append_char(buff, index, c);
      if (format->width > 1 && format->flag_minus) {
        for (int i = 0; i < format->width - 1; i++)
          append_char(buff, index, ' ');
      }
      break;
    }
    case 's': {
      char *s = va_arg(args, char *);
      if (!s) s = "(null)";
      append_string(buff, index, s, format->width, format->flag_minus);
      break;
    }
    case 'd': {
      long long d = 0;
      if (format->length == 1) {
        d = (short)va_arg(args, int);
      } else if (format->length == 2) {
        d = va_arg(args, long);
      } else {
        d = va_arg(args, int);
      }

      char temp[1024] = {0};

      if (format->flag_plus && d >= 0) {
        s21_strncat(temp, "+", sizeof(temp) - s21_strlen(temp) - 1);
      } else if (format->flag_space && d >= 0) {
        s21_strncat(temp, " ", sizeof(temp) - s21_strlen(temp) - 1);
      }

      char num_str[1024] = {0};
      int_to_string(d, num_str, false);

      s21_strncat(temp, num_str, sizeof(temp) - s21_strlen(temp) - 1);

      append_string(buff, index, temp, format->width, format->flag_minus);
      break;
    }
    case 'u': {
      unsigned long long u = 0;

      if (format->length == 1) {
        u = (unsigned short)va_arg(args, unsigned int);
      } else if (format->length == 2) {
        u = va_arg(args, unsigned long);
      } else {
        u = va_arg(args, unsigned int);
      }
      char num_str[1024] = {0};
      unsigned_to_string(u, num_str);
      append_string(buff, index, num_str, format->width, format->flag_minus);
      break;
    }
    case 'f': {
      double f = va_arg(args, double);
      float_to_string(f, temp, format->precision >= 0 ? format->precision : 6);
      append_string(buff, index, temp, format->width, format->flag_minus);
      break;
    }
    case '%': {
      append_char(buff, index, '%');
      break;
    }
    default:
      break;
  }
}

int s21_sprintf(char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int index = 0;
  const char *ptr = format;

  while (*ptr) {
    if (*ptr == '%') {
      ptr++;
      Format formatSpec;
      char specifier = s21_sprintf_parcer(&ptr, &formatSpec);
      s21_sprintf_specifier(buffer, specifier, &index, args, &formatSpec);
    } else {
      append_char(buffer, &index, *ptr);
    }
    ptr++;
  }
  buffer[index] = '\0';
  va_end(args);
  return index;
}

// int main() {
//     char buffer[300];
//     char egor_eblan[300];

//     sprintf(buffer, "%f", 1.);
//     printf("%s\n", buffer);
//     s21_sprintf(egor_eblan, "%f", 1.);
//     printf("%s\n", egor_eblan);
//     return 0;
// }