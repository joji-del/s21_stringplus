#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

typedef struct {
  bool flag_plus;
  bool flag_minus;
  bool flag_space;
  int width;
  int precision;
  int length;
} Format;

int s21_format_parser(const char **strFlag, Format *format);
void append_char(char *buff, int *index, char c);
void append_string(char *buff, int *index, const char *str, int width,
                   bool left_align);
void s21_sprintf_specifier(char *buff, char specifier, int *index, va_list args,
                           Format *format);
int s21_sprintf(char *buffer, const char *format, ...);
void int_to_string(long long num, char *str, bool is_unsigned);
void float_to_string(double num, char *str, int precision);
void unsigned_to_string(unsigned long long value, char *str);

#endif