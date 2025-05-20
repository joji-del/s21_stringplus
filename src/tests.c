#include <check.h>

#include "s21_sprintf.h"
#include "s21_string.h"

START_TEST(s21_memchr_test) {
  char str1[] = "Hello, World!";
  ck_assert_ptr_eq(s21_memchr(str1, 'W', strlen(str1)),
                   memchr(str1, 'W', strlen(str1)));

  char str2[] = "123456789\0";
  char test_case_1 = '4';
  ck_assert_ptr_eq(s21_memchr(str2, (int)test_case_1, 10),
                   memchr(str2, (int)test_case_1, 10));
  ck_assert_ptr_eq(s21_memchr(str2, (int)test_case_1, 1),
                   memchr(str2, (int)test_case_1, 1));
  ck_assert_ptr_eq(s21_memchr(str2, ' ', 9), memchr(str2, ' ', 9));
  ck_assert_ptr_eq(s21_memchr(str2, '\0', 10), memchr(str2, '\0', 10));
  char str4[] = "";
  ck_assert_ptr_eq(s21_memchr(str4, 'H', 0), memchr(str4, 'H', 0));

  char str5[] = "Hello, World!/\0";
  ck_assert_ptr_eq(s21_memchr(str5, '\0', strlen(str5)),
                   memchr(str5, '\0', strlen(str5)));
  ck_assert_ptr_eq(s21_memchr(str5, '/', strlen(str5)),
                   memchr(str5, '/', strlen(str5)));
  ck_assert_ptr_eq(s21_memchr(str5, ' ', strlen(str5)),
                   memchr(str5, ' ', strlen(str5)));
  ck_assert_ptr_eq(s21_memchr(str5, '\n', strlen(str5)),
                   memchr(str5, '\n', strlen(str5)));
  char *str6 = malloc(10000);
  memset(str6, 'a', 10000);
  str6[9999] = 'b';
  ck_assert_ptr_eq(s21_memchr(str6, 'b', 10000), memchr(str6, 'b', 10000));
  free(str6);
}
END_TEST

START_TEST(s21_memcmp_test) {
  char str1[] = "Hello World!";
  char str2[] = "Hello World!";
  ck_assert_int_eq(s21_memcmp(str1, str2, 11) == 0,
                   memcmp(str1, str2, 11) == 0);
  ck_assert_int_eq(s21_memcmp(str1, str2, 0) == 0, memcmp(str1, str2, 0) == 0);

  char str3[] = "hello world";
  ck_assert_int_eq(s21_memcmp(str1, str3, 11) < 0, memcmp(str1, str3, 11) < 0);

  char str4[11] = "\0";
  ck_assert_int_eq(s21_memcmp(str1, str4, 11) > 0, memcmp(str1, str4, 11) > 0);
  ck_assert_int_eq(s21_memcmp(str3, str4, 11) > 0, memcmp(str3, str4, 11) > 0);

  char str5[] = "biba\0boba";
  char str6[] = "biba\0boba";
  ck_assert_int_eq(s21_memcmp(str5, str6, 10) == 0,
                   memcmp(str5, str6, 10) == 0);
  ck_assert_int_eq(s21_memcmp(str5, str6, 0) == 0, memcmp(str5, str6, 0) == 0);

  char str7[] = {0x41, 0x42, 0x43, 0x44};
  char str8[] = {0x41, 0x46, 0x43, 0x44};
  ck_assert_int_eq(s21_memcmp(str7, str8, 4) < 0, memcmp(str7, str8, 4) < 0);
  ck_assert_int_eq(s21_memcmp(str7, str8, 1) == 0, memcmp(str7, str8, 1) == 0);
  ck_assert_int_eq(s21_memcmp(str7, str8, 2) < 0, memcmp(str7, str8, 2) < 0);
}
END_TEST

START_TEST(s21_memcpy_test) {
  char data_str[100];
  char data_str_copy[100];
  char str1[] = "Hello, World!";

  for (int i = 0; i < 100; i++) {
    data_str[i] = '\0';
    data_str_copy[i] = '\0';
  }
  s21_memcpy(data_str, str1, 5);
  memcpy(data_str_copy, str1, 5);
  ck_assert_str_eq(data_str, data_str_copy);

  s21_memcpy(data_str, str1, 0);
  memcpy(data_str_copy, str1, 0);
  ck_assert_str_eq(data_str, data_str_copy);

  s21_memcpy(data_str, str1, strlen(str1));
  memcpy(data_str_copy, str1, strlen(str1));
  ck_assert_str_eq(data_str, data_str_copy);

  s21_memcpy(data_str, str1, strlen(str1) + 1);
  memcpy(data_str_copy, str1, strlen(str1) + 1);
  ck_assert_str_eq(data_str, data_str_copy);

  char str1_data[] = "Hello, World!";
  char str1_copy[] = "Hello, World!";
  char str2[] = "Hello, World!";

  s21_memcpy(str1_data, str2, strlen(str1_data));
  memcpy(str1_copy, str2, strlen(str1_data));
  ck_assert_str_eq(str1_data, str1_copy);

  s21_memcpy(str1_data, str2, strlen(str1_data) + 1);
  memcpy(str1_copy, str2, strlen(str1_data) + 1);
  ck_assert_str_eq(str1_data, str1_copy);

  s21_memcpy(str1_data, str2, 0);
  memcpy(str1_copy, str2, 0);
  ck_assert_str_eq(str1_data, str1_copy);

  s21_memcpy(str1_data, str2, 5);
  memcpy(str1_copy, str2, 5);
  ck_assert_str_eq(str1_data, str1_copy);

  int data[] = {1, 2, 3, 4, 5, 6};
  int data_res_s21[5];
  int data_res_orig[5];

  s21_memcpy(data_res_s21, data, 5 * sizeof(int));
  memcpy(data_res_orig, data, 5 * sizeof(int));
  ck_assert_mem_eq(data_res_s21, data_res_orig, 5 * sizeof(int));

  s21_memcpy(data_res_s21, data, 1);
  memcpy(data_res_orig, data, 1);
  ck_assert_mem_eq(data_res_s21, data_res_orig, 1);

  float data_f[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  float data_f_res_s21[9];
  float data_f_res_orig[9];

  s21_memcpy(data_f_res_s21, data_f, 9 * sizeof(float));
  memcpy(data_f_res_orig, data_f, 9 * sizeof(float));
  ck_assert_mem_eq(data_f_res_s21, data_f_res_orig, 9 * sizeof(float));

  s21_memcpy(data_f_res_s21, data_f, 1);
  memcpy(data_f_res_orig, data_f, 1);
  ck_assert_mem_eq(data_f_res_s21, data_f_res_orig, 1);
}
END_TEST

START_TEST(s21_memset_test) {
  char str_s21[50];
  char str_orig[50];

  s21_memset(str_s21, 's', 10);
  memset(str_orig, 's', 10);
  ck_assert_mem_eq(str_s21, str_orig, 10 * sizeof(char));

  s21_memset(str_s21, '1', 10);
  memset(str_orig, '1', 10);
  ck_assert_mem_eq(str_s21, str_orig, 10 * sizeof(char));

  s21_memset(str_s21, '0', 1);
  memset(str_orig, '0', 1);
  ck_assert_mem_eq(str_s21, str_orig, 1 * sizeof(char));

  s21_memset(str_s21, '\0', 10);
  memset(str_orig, '\0', 10);
  ck_assert_mem_eq(str_s21, str_orig, 10 * sizeof(char));

  s21_memset(str_s21, 0x41, 10);
  memset(str_orig, 0x41, 10);
  ck_assert_mem_eq(str_s21, str_orig, 10 * sizeof(char));

  s21_memset(str_s21, ' ', 5);
  memset(str_orig, ' ', 5);
  ck_assert_mem_eq(str_s21, str_orig, 5 * sizeof(char));

  s21_memset(str_s21, '/', 5);
  memset(str_orig, '/', 5);
  ck_assert_mem_eq(str_s21, str_orig, 5 * sizeof(char));

  int str_i_s21[50];
  int str_i_orig[50];

  s21_memset(str_i_s21, 1, 10 * sizeof(int));
  memset(str_i_orig, 1, 10 * sizeof(int));
  ck_assert_mem_eq(str_i_s21, str_i_orig, 10 * sizeof(int));

  s21_memset(str_i_s21, 10, 10 * sizeof(int));
  memset(str_i_orig, 10, 10 * sizeof(int));
  ck_assert_mem_eq(str_i_s21, str_i_orig, 10 * sizeof(int));

  s21_memset(str_i_s21, 0x31, 10 * sizeof(int));
  memset(str_i_orig, 0x31, 10 * sizeof(int));
  ck_assert_mem_eq(str_i_s21, str_i_orig, 10 * sizeof(int));
}
END_TEST

START_TEST(s21_strlen_test) {
  char str1[] = "Hello, World!";
  char str2[] = "\0";
  char str3[] = "biba\0boba";
  char str4[] = "   \0   ";
  char str5[] = "\nHello\0World\0\0";
  char str6[] = "/";
  char str7[] = " ";
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));
  ck_assert_int_eq(s21_strlen(str3), strlen(str3));
  ck_assert_int_eq(s21_strlen(str4), strlen(str4));
  ck_assert_int_eq(s21_strlen(str5), strlen(str5));
  ck_assert_int_eq(s21_strlen(str6), strlen(str6));
  ck_assert_int_eq(s21_strlen(str7), strlen(str7));
}
END_TEST

START_TEST(s21_strncat_test) {
  char data_cat_s21[50] = "Hello,";
  char data_cat_orig[50] = "Hello,";
  char str1[] = "World";
  char str2[] = "";
  char data_cat_s212[50] = "";
  char data_cat_orig2[50] = "";

  ck_assert_str_eq(s21_strncat(data_cat_s21, str1, 20),
                   strncat(data_cat_orig, str1, 20));
  ck_assert_str_eq(s21_strncat(data_cat_s21, str2, 6),
                   strncat(data_cat_orig, str2, 6));
  ck_assert_str_eq(s21_strncat(data_cat_s21, str2, 2),
                   strncat(data_cat_orig, str2, 2));
  ck_assert_str_eq(s21_strncat(str1, str2, 5), strncat(str1, str2, 5));

  char data_cat_s213[50] = "";
  char data_cat_orig3[50] = "";
  char data_cat_s21_[50] = "Hello,";
  char data_cat_orig_[50] = "Hello,";
  ck_assert_str_eq(s21_strncat(data_cat_s213, data_cat_s21_, 7),
                   strncat(data_cat_orig3, data_cat_orig_, 7));  // ERROR

  ck_assert_str_eq(s21_strncat(data_cat_s212, str2, 5),
                   strncat(data_cat_orig2, str2, 5));
  ck_assert_str_eq(s21_strncat(str2, str1, 0), strncat(str2, str1, 0));
  ck_assert_str_eq(s21_strncat(data_cat_s212, str2, 1),
                   strncat(data_cat_orig2, str2, 1));
}
END_TEST

START_TEST(s21_strchr_test) {
  char str1_s21[] = "123456";
  char str1_orig[] = "123456";
  int symbol_1 = '4';

  char *res1 = s21_strchr(str1_s21, symbol_1);
  char *res2 = strchr(str1_orig, symbol_1);
  ck_assert_str_eq(res1, "456");
  ck_assert_str_eq(res1, res2);
  ck_assert_str_eq(str1_s21, str1_orig);

  char str2_s21[] = "bibaboba";
  char str2_orig[] = "bibaboba";
  int symbol_2 = 'a';

  char *res3 = s21_strchr(str2_s21, symbol_2);
  char *res4 = strchr(str2_orig, symbol_2);
  ck_assert_str_eq(res3, "aboba");
  ck_assert_str_eq(res3, res4);
  ck_assert_str_eq(str2_s21, str2_orig);

  char str3_s21[] = "aboba";
  char str3_orig[] = "aboba";
  int symbol_3 = '\0';

  char *res5 = s21_strchr(str3_s21, symbol_3);
  char *res6 = strchr(str3_orig, symbol_3);
  ck_assert_str_eq(res5, res6);
}
END_TEST

START_TEST(s21_strncmp_test) {
  char str1[] = "boba";
  char str1_copy[] = "boba";
  int strncmp_s21 = s21_strncmp(str1, str1_copy, 4);
  int strncmp_orig = strncmp(str1, str1_copy, 4);
  ck_assert_int_eq(strncmp_s21, strncmp_orig);

  char str2[] = "boba";
  char str2_copy[] = "biba";
  int strncmp_s21_2 = s21_strncmp(str2, str2_copy, 4);
  int strncmp_orig_2 = strncmp(str2, str2_copy, 4);
  ck_assert_int_eq(strncmp_s21_2, strncmp_orig_2);

  char str3[] = "";
  char str3_copy[] = "";
  int strncmp_s21_3 = s21_strncmp(str3, str3_copy, 0);
  int strncmp_orig_3 = strncmp(str3, str3_copy, 0);
  ck_assert_int_eq(strncmp_s21_3, strncmp_orig_3);

  char str4[] = "Hello World";
  char str4_copy[] = "World";
  int strncmp_s21_4 = s21_strncmp(str4, str4_copy, 5);
  int strncmp_orig_4 = strncmp(str4, str4_copy, 5);
  ck_assert_int_eq(strncmp_s21_4, strncmp_orig_4);

  char str5[] = "biba\0boba";
  char str5_copy[] = "biba boba";
  int strncmp_s21_5 = s21_strncmp(str5, str5_copy, 9);
  int strncmp_orig_5 = strncmp(str5, str5_copy, 9);
  ck_assert_int_eq(strncmp_s21_5, strncmp_orig_5);

  char str6[] = "biba    boba";
  char str6_copy[] = "biba    boba";
  int strncmp_s21_6 = s21_strncmp(str6, str6_copy, 12);
  int strncmp_orig_6 = strncmp(str6, str6_copy, 12);
  ck_assert_int_eq(strncmp_s21_6, strncmp_orig_6);

  char str7[] = "   ";
  char str7_copy[] = "   ";
  int strncmp_s21_7 = s21_strncmp(str7, str7_copy, 3);
  int strncmp_orig_7 = strncmp(str7, str7_copy, 3);
  ck_assert_int_eq(strncmp_s21_7, strncmp_orig_7);

  char str8[] = "";
  char str8_copy[] = "";
  int strncmp_s21_8 = s21_strncmp(str8, str8_copy, 1);
  int strncmp_orig_8 = strncmp(str8, str8_copy, 1);
  ck_assert_int_eq(strncmp_s21_8, strncmp_orig_8);

  char str9[] = "boba";
  char str9_copy[] = "";
  int strncmp_s21_9 = s21_strncmp(str9, str9_copy, 4);
  int strncmp_orig_9 = strncmp(str9, str9_copy, 4);
  ck_assert_int_eq(strncmp_s21_9, strncmp_orig_9);
}
END_TEST

START_TEST(s21_strcspn_test) {
  char str1[] = "abcdefg";
  char str2[] = "zxq";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));

  char str3[] = "";
  char str4[] = "hello";
  ck_assert_int_eq(s21_strcspn(str3, str4), strcspn(str3, str4));
  ck_assert_int_eq(s21_strcspn(str2, str4), strcspn(str2, str4));
  ck_assert_int_eq(s21_strcspn(str1, str3), strcspn(str1, str3));

  char str5[] = "1234";
  char str6[] = "5678";
  ck_assert_int_eq(s21_strcspn(str5, str6), strcspn(str5, str6));
  ck_assert_int_eq(s21_strcspn(str3, str6), strcspn(str3, str6));
  ck_assert_int_eq(s21_strcspn(str4, str6), strcspn(str4, str6));

  char str7[] = "123456789";
  char str8[] = "123456789";
  ck_assert_int_eq(s21_strcspn(str7, str8), strcspn(str7, str8));
  ck_assert_int_eq(s21_strcspn(str6, str8), strcspn(str6, str8));
  ck_assert_int_eq(s21_strcspn(str3, str8), strcspn(str3, str8));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char str1[] = "Hello";
  char str2[] = "World";
  char *strpbrk_s21 = s21_strpbrk(str1, str2);
  char *strpbrk_orig = strpbrk(str1, str2);
  ck_assert_ptr_eq(strpbrk_s21, strpbrk_orig);

  char str5[] = "Hello";
  char str6[] = "";
  char *strpbrk_s21_3 = s21_strpbrk(str5, str6);
  char *strpbrk_orig_3 = strpbrk(str5, str6);
  ck_assert_ptr_eq(strpbrk_s21_3, strpbrk_orig_3);

  char str7[] = "";
  char str8[] = "World";
  char *strpbrk_s21_4 = s21_strpbrk(str7, str8);
  char *strpbrk_orig_4 = strpbrk(str7, str8);
  ck_assert_ptr_eq(strpbrk_s21_4, strpbrk_orig_4);

  char str9[] = "";
  char str10[] = "";
  char *strpbrk_s21_5 = s21_strpbrk(str9, str10);
  char *strpbrk_orig_5 = strpbrk(str9, str10);
  ck_assert_ptr_eq(strpbrk_s21_5, strpbrk_orig_5);

  char str11[] = "biba\0boba";
  char str12[] = "\0";
  char *strpbrk_s21_6 = s21_strpbrk(str11, str12);
  char *strpbrk_orig_6 = strpbrk(str11, str12);
  ck_assert_ptr_eq(strpbrk_s21_6, strpbrk_orig_6);
}
END_TEST

START_TEST(s21_strrchr_test) {
  char str1[] = "hello Hello HelLo HELLO";
  char test_str1 = 'H';
  char test_str2 = 'l';
  char test_str3 = ' ';
  char test_str4 = 'w';
  char test_str5 = '\0';

  char *s21_strrchr_1 = s21_strrchr(str1, test_str1);
  char *orig_strrch_1 = strrchr(str1, test_str1);
  ck_assert_ptr_eq(s21_strrchr_1, orig_strrch_1);

  char *s21_strrchr_2 = s21_strrchr(str1, test_str2);
  char *orig_strrch_2 = strrchr(str1, test_str2);
  ck_assert_ptr_eq(s21_strrchr_2, orig_strrch_2);

  char *s21_strrchr_3 = s21_strrchr(str1, test_str3);
  char *orig_strrch_3 = strrchr(str1, test_str3);
  ck_assert_ptr_eq(s21_strrchr_3, orig_strrch_3);

  char *s21_strrchr_4 = s21_strrchr(str1, test_str4);
  char *orig_strrch_4 = strrchr(str1, test_str4);
  ck_assert_ptr_eq(s21_strrchr_4, orig_strrch_4);

  char *s21_strrchr_5 = s21_strrchr(str1, test_str5);
  char *orig_strrch_5 = strrchr(str1, test_str5);
  ck_assert_ptr_eq(s21_strrchr_5, orig_strrch_5);

  char str2[] = "1234567890";
  int test_int1 = 1;
  int test_int2 = -1;
  int test_int3 = '1';
  int test_int4 = 0x31;
  int test_int5 = '\0';

  char *s21_strrchr_6 = s21_strrchr(str2, test_int1);
  char *orig_strrch_6 = strrchr(str2, test_int1);
  ck_assert_ptr_eq(s21_strrchr_6, orig_strrch_6);

  char *s21_strrchr_7 = s21_strrchr(str2, test_int2);
  char *orig_strrch_7 = strrchr(str2, test_int2);
  ck_assert_ptr_eq(s21_strrchr_7, orig_strrch_7);

  char *s21_strrchr_8 = s21_strrchr(str2, test_int3);
  char *orig_strrch_8 = strrchr(str2, test_int3);
  ck_assert_ptr_eq(s21_strrchr_8, orig_strrch_8);

  char *s21_strrchr_9 = s21_strrchr(str2, test_int4);
  char *orig_strrch_9 = strrchr(str2, test_int4);
  ck_assert_ptr_eq(s21_strrchr_9, orig_strrch_9);

  char *s21_strrchr_10 = s21_strrchr(str2, test_int5);
  char *orig_strrch_10 = strrchr(str2, test_int5);
  ck_assert_ptr_eq(s21_strrchr_10, orig_strrch_10);
}
END_TEST

START_TEST(s21_strstr_test) {
  char str1[] = "Hello\nHello\nHELLO\nhello\nhelo";
  char test_str1[] = "llo";
  char test_str2[] = "\n";
  char test_str3[] = " ";

  char *s21_strstr_1 = s21_strstr(str1, test_str1);
  char *orig_strstr_1 = strstr(str1, test_str1);
  ck_assert_ptr_eq(s21_strstr_1, orig_strstr_1);

  char *s21_strstr_2 = s21_strstr(str1, test_str2);
  char *orig_strstr_2 = strstr(str1, test_str2);
  ck_assert_ptr_eq(s21_strstr_2, orig_strstr_2);

  char *s21_strstr_3 = s21_strstr(str1, test_str3);
  char *orig_strstr_3 = strstr(str1, test_str3);
  ck_assert_ptr_eq(s21_strstr_3, orig_strstr_3);

  char str2[] = "Biba and Boba love school21 very much";
  char test_str4[] = "21";
  char test_str5[] = " ";
  char test_str6[] = "a ";

  char *s21_strstr_4 = s21_strstr(str2, test_str4);
  char *orig_strstr_4 = strstr(str2, test_str4);
  ck_assert_ptr_eq(s21_strstr_4, orig_strstr_4);

  char *s21_strstr_5 = s21_strstr(str2, test_str5);
  char *orig_strstr_5 = strstr(str2, test_str5);
  ck_assert_ptr_eq(s21_strstr_5, orig_strstr_5);

  char *s21_strstr_6 = s21_strstr(str2, test_str6);
  char *orig_strstr_6 = strstr(str2, test_str6);
  ck_assert_ptr_eq(s21_strstr_6, orig_strstr_6);

  char str3[] = "";
  char test_str7[] = "";

  char *s21_strstr_7 = s21_strstr(str3, test_str7);
  char *orig_strstr_7 = strstr(str3, test_str7);
  ck_assert_ptr_eq(s21_strstr_7, orig_strstr_7);
}
END_TEST

START_TEST(s21_strtok_test) {
  char str1[] = "Hello, World!i love school21!";
  char str1_copy[] = "Hello, World!i love school21!";

  char test_str1[] = ", !o";

  char *s21_strtok_1 = s21_strtok(str1, test_str1);
  char *orig_strtok_1 = strtok(str1_copy, test_str1);
  ck_assert_pstr_eq(s21_strtok_1, orig_strtok_1);

  s21_strtok_1 = s21_strtok(S21_NULL, test_str1);
  orig_strtok_1 = strtok(NULL, test_str1);
  ck_assert_pstr_eq(s21_strtok_1, orig_strtok_1);

  char str2[] = "";
  char str2_copy[] = "";
  char *test_str2 = "";

  char *s21_strtok_2 = s21_strtok(str2, test_str2);
  char *orig_strtok_2 = strtok(str2_copy, test_str2);
  ck_assert_pstr_eq(s21_strtok_2, orig_strtok_2);

  char str3[] = "biba   and   boba";
  char str3_copy[] = "biba   and   boba";
  char *test_str3 = " ";
  char *s21_strtok_3 = s21_strtok(str3, test_str3);
  char *orig_strtok_3 = strtok(str3_copy, test_str3);
  ck_assert_pstr_eq(s21_strtok_3, orig_strtok_3);

  char str4[] = "l";
  char str4_copy[] = "l";
  char test_str4[] = "Hello, World!";
  char *s21_strtok_4 = s21_strtok(str4, test_str4);
  char *orig_strtok_4 = strtok(str4_copy, test_str4);
  ck_assert_pstr_eq(s21_strtok_4, orig_strtok_4);
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = -10; i < 110; i++) {
    char *s21_strerror_1 = s21_strerror(i);
    char *orig_strerror_1 = strerror(i);
    ck_assert_str_eq(s21_strerror_1, orig_strerror_1);
  }
}
END_TEST

START_TEST(s21_strncpy_test) {
  char data_str[100];
  char data_str_copy[100];
  for (int i = 0; i < 100; i++) {
    data_str[i] = '\0';
    data_str_copy[i] = '\0';
  }
  char str1[] = "Hello, World!";

  // Тест 1
  s21_strncpy(data_str, str1, 20);
  data_str[99] = '\0';  // Ручная нуль-терминация для обоих
  strncpy(data_str_copy, str1, 20);
  data_str_copy[99] = '\0';
  ck_assert_str_eq(data_str, data_str_copy);

  // Тест 2
  s21_strncpy(data_str, str1, 5);
  data_str[5] = '\0';
  strncpy(data_str_copy, str1, 5);
  data_str_copy[5] = '\0';
  ck_assert_str_eq(data_str, data_str_copy);

  // Тест 3
  s21_strncpy(data_str, str1, 1);
  data_str[1] = '\0';
  strncpy(data_str_copy, str1, 1);
  data_str_copy[1] = '\0';
  ck_assert_str_eq(data_str, data_str_copy);

  char str2[] = "";

  // Тест 4
  s21_strncpy(data_str, str2, 1);
  data_str[1] = '\0';
  strncpy(data_str_copy, str2, 1);
  data_str_copy[1] = '\0';
  ck_assert_str_eq(data_str, data_str_copy);

  // Тест 5
  s21_strncpy(data_str, str2, 10);
  data_str[10] = '\0';
  strncpy(data_str_copy, str2, 10);
  data_str_copy[10] = '\0';
  ck_assert_str_eq(data_str, data_str_copy);
}
END_TEST

START_TEST(s21_to_upper_test) {
  char str1[] = "hello, world";
  char *s21_to_upper_1 = s21_to_upper(str1);
  ck_assert_str_eq(s21_to_upper_1, "HELLO, WORLD");

  char str2[] = "";
  char *s21_to_upper_2 = s21_to_upper(str2);
  ck_assert_str_eq(s21_to_upper_2, "");

  char str3[] = "12\0\n&^@";
  char *s21_to_upper_3 = s21_to_upper(str3);
  ck_assert_str_eq(s21_to_upper_3, "12\0\n&^@");

  char str4[] = "He1lo, Wor1d!;";
  char *s21_to_upper_4 = s21_to_upper(str4);
  ck_assert_str_eq(s21_to_upper_4, "HE1LO, WOR1D!;");

  free(s21_to_upper_1);
  free(s21_to_upper_2);
  free(s21_to_upper_3);
  free(s21_to_upper_4);
}
END_TEST

START_TEST(s21_to_lower_test) {
  char str1[] = "Hello, World!";
  char *s21_to_lower_1 = s21_to_lower(str1);
  ck_assert_str_eq(s21_to_lower_1, "hello, world!");

  char str2[] = " ";
  char *s21_to_lower_2 = s21_to_lower(str2);
  ck_assert_str_eq(s21_to_lower_2, " ");

  char str3[] = "12\0\n&^!  $";
  char *s21_to_lower_3 = s21_to_lower(str3);
  ck_assert_str_eq(s21_to_lower_3, "12\0\n&^!  $");

  char str4[] = "Hel1o, Wor1d!";
  char *s21_to_lower_4 = s21_to_lower(str4);
  ck_assert_str_eq(s21_to_lower_4, "hel1o, wor1d!");

  free(s21_to_lower_1);
  free(s21_to_lower_2);
  free(s21_to_lower_3);
  free(s21_to_lower_4);
}
END_TEST

START_TEST(s21_insert_test) {
  char str1[] = "Hello,";
  char str1_copy[] = " World!";
  char *s21_insert_1 = s21_insert(str1, str1_copy, 6);
  ck_assert_str_eq("Hello, World!", s21_insert_1);

  char str2[] = "";
  char str2_copy[] = "biba";
  char *s21_insert_2 = s21_insert(str2, str2_copy, 0);
  ck_assert_str_eq("biba", s21_insert_2);

  char str3[] = "Hello";
  char str3_copy[] = ", World!";
  char *s21_insert_3 = s21_insert(str3, str3_copy, 5);
  ck_assert_str_eq("Hello, World!", s21_insert_3);

  char str4[] = "";
  char str4_copy[] = "";
  char *s21_insert_4 = s21_insert(str4, str4_copy, 10);
  ck_assert_pstr_eq(s21_insert_4, S21_NULL);

  char str5[] = "b boba";
  char str5_copy[] = "iba";
  char *s21_insert_5 = s21_insert(str5, str5_copy, 1);
  ck_assert_str_eq("biba boba", s21_insert_5);

  char str6[] = "";
  char str6_copy[] = "";
  char *s21_insert_6 = s21_insert(str6, str6_copy, 1);
  ck_assert_pstr_eq(s21_insert_6, NULL);
}
END_TEST

START_TEST(s21_trim_test) {
  char str1[] = "   Hello, World!   ";
  char *test_1 = " ";
  char *s21_trim_1 = s21_trim(str1, test_1);
  ck_assert_str_eq(s21_trim_1, "Hello, World!");

  char str2[] = "Hello, World!";
  char *test_2 = "*";
  char *s21_trim_2 = s21_trim(str2, test_2);
  ck_assert_str_eq(s21_trim_2, "Hello, World!");

  char *str3 = "";
  char *test_3 = "";
  char *s21_trim_3 = s21_trim(str3, test_3);
  ck_assert_str_eq(s21_trim_3, "");

  char *str4 = "@#$biba and boba@#$";
  char *test_4 = "@#$";
  char *s21_trim_4 = s21_trim(str4, test_4);
  ck_assert_str_eq(s21_trim_4, "biba and boba");

  char *str5 = "@HELLO@";
  char *test_5 = "";
  char *s21_trim_5 = s21_trim(str5, test_5);
  ck_assert_str_eq(s21_trim_5, "@HELLO@");

  char *str6 = "";
  char *test_6 = "!@";
  char *s21_trim_6 = s21_trim(str6, test_6);
  ck_assert_str_eq(s21_trim_6, "");

  char *str7 = "!!!!";
  char *test_7 = "!";
  char *s21_trim_7 = s21_trim(str7, test_7);
  ck_assert_str_eq(s21_trim_7, "");

  free(s21_trim_1);
  free(s21_trim_2);
  free(s21_trim_3);
  free(s21_trim_4);
  free(s21_trim_5);
  free(s21_trim_6);
  free(s21_trim_7);
}
END_TEST

START_TEST(s21_sprintf_c_test) {
  char data[100];
  char data_copy[100];

  int s21_c_sprintf_1 = s21_sprintf(data, "%c", '!');
  int orig_c_sprintf_1 = sprintf(data_copy, "%c", '!');
  ck_assert_int_eq(s21_c_sprintf_1, orig_c_sprintf_1);

  int s21_c_sprintf_2 = s21_sprintf(data, "%10c", 0x21);
  int orig_c_sprintf_2 = sprintf(data_copy, "%10c", 0x21);
  ck_assert_int_eq(s21_c_sprintf_2, orig_c_sprintf_2);

  int s21_c_sprintf_3 = s21_sprintf(data, "%13c", 'a');
  int orig_c_sprintf_3 = sprintf(data_copy, "%13c", 'a');
  ck_assert_int_eq(s21_c_sprintf_3, orig_c_sprintf_3);

  int s21_c_sprintf_4 = s21_sprintf(data, "%-c", 'a');
  int orig_c_sprintf_4 = sprintf(data_copy, "%-c", 'a');
  ck_assert_int_eq(s21_c_sprintf_4, orig_c_sprintf_4);

  int s21_c_sprintf_5 = s21_sprintf(data, " %-c", '@');
  int orig_c_sprintf_5 = sprintf(data_copy, " %-c", '@');
  ck_assert_int_eq(s21_c_sprintf_5, orig_c_sprintf_5);

  int s21_c_sprintf_6 = s21_sprintf(data, "%c", 123);
  int orig_c_sprintf_6 = sprintf(data_copy, "%c", 123);
  ck_assert_int_eq(s21_c_sprintf_6, orig_c_sprintf_6);

  int s21_c_sprintf_7 = s21_sprintf(data, "%c", "Hello, World!");
  int orig_c_sprintf_7 = sprintf(data_copy, "%c", "Hello, World!"[0]);
  ck_assert_int_eq(s21_c_sprintf_7, orig_c_sprintf_7);

  int s21_c_sprintf_8 = s21_sprintf(data, "%c %c %c", 'c', 'c', 'c');
  int orig_c_sprintf_8 = sprintf(data_copy, "%c %c %c", 'c', 'c', 'c');
  ck_assert_int_eq(s21_c_sprintf_8, orig_c_sprintf_8);
}
END_TEST

START_TEST(s21_sprintf_s_test) {
  char data[100];
  char data_copy[100];
  char str1[] = "biba and boba";

  int s21_s_sprintf_1 = s21_sprintf(data, "%s", str1);
  int orig_s_sprintf_1 = sprintf(data_copy, "%s", str1);
  ck_assert_int_eq(s21_s_sprintf_1, orig_s_sprintf_1);

  int s21_s_sprintf_2 = s21_sprintf(data, "%10s", str1);
  int orig_s_sprintf_2 = sprintf(data_copy, "%10s", str1);
  ck_assert_int_eq(s21_s_sprintf_2, orig_s_sprintf_2);

  int s21_s_sprintf_3 = s21_sprintf(data, "%34s", " ");
  int orig_s_sprintf_3 = sprintf(data_copy, "%34s", " ");
  ck_assert_int_eq(s21_s_sprintf_3, orig_s_sprintf_3);

  int s21_s_sprintf_4 = s21_sprintf(data, "%-s", str1);
  int orig_s_sprintf_4 = sprintf(data_copy, "%-s", str1);
  ck_assert_uint_eq(s21_s_sprintf_4, orig_s_sprintf_4);

  int s21_s_sprintf_5 = s21_sprintf(data, "%s %s %s", "123", str1, "HELLO");
  int orig_s_sprintf_5 = sprintf(data_copy, "%s %s %s", "123", str1, "HELLO");
  ck_assert_uint_eq(s21_s_sprintf_5, orig_s_sprintf_5);
}
END_TEST

START_TEST(s21_sprintf_d_test) {
  char data[100];
  char data_copy[100];
  int str1 = 12345;
  int str2 = 2147483647;
  int str3 = -2147483648;

  int s21_d_sprintf_1 = s21_sprintf(data, "%d", str1);
  int orig_d_sprintf_1 = sprintf(data_copy, "%d", str1);
  ck_assert_int_eq(s21_d_sprintf_1, orig_d_sprintf_1);

  int s21_d_sprintf_2 = s21_sprintf(data, "%10.7d", str1);
  int orig_d_sprintf_2 = sprintf(data_copy, "%10.7d", str1);
  ck_assert_int_eq(s21_d_sprintf_2, orig_d_sprintf_2);

  int s21_d_sprintf_3 = s21_sprintf(data, "%7d", str1);
  int orig_d_sprintf_3 = sprintf(data_copy, "%7d", str1);
  ck_assert_int_eq(s21_d_sprintf_3, orig_d_sprintf_3);

  int s21_d_sprintf_4 = s21_sprintf(data, "%+d", str1);
  int orig_d_sprintf_4 = sprintf(data_copy, "%+d", str1);
  ck_assert_int_eq(s21_d_sprintf_4, orig_d_sprintf_4);

  int s21_d_sprintf_5 = s21_sprintf(data, "%-d", str1);
  int orig_d_sprintf_5 = sprintf(data_copy, "%-d", str1);
  ck_assert_int_eq(s21_d_sprintf_5, orig_d_sprintf_5);

  int s21_d_sprintf_6 = s21_sprintf(data, "% d", str1);
  int orig_d_sprintf_6 = sprintf(data_copy, "% d", str1);
  ck_assert_int_eq(s21_d_sprintf_6, orig_d_sprintf_6);

  int s21_d_sprintf_7 = s21_sprintf(data, "%ld", str2);
  int orig_d_sprintf_7 = sprintf(data_copy, "%ld", (long int)str2);
  ck_assert_int_eq(s21_d_sprintf_7, orig_d_sprintf_7);

  int s21_d_sprintf_8 = s21_sprintf(data, "%hd", str1);
  int orig_d_sprintf_8 = sprintf(data_copy, "%hd", str1);
  ck_assert_int_eq(s21_d_sprintf_8, orig_d_sprintf_8);

  int s21_d_sprintf_9 = s21_sprintf(data, "%ld", (long int)str3);
  int orig_d_sprintf_9 = sprintf(data_copy, "%ld", (long int)str3);
  ck_assert_int_eq(s21_d_sprintf_9, orig_d_sprintf_9);

  int s21_d_sprintf_10 = s21_sprintf(data, "%d", 123);
  int orig_d_sprintf_10 = sprintf(data_copy, "%d", 123);
  ck_assert_int_eq(s21_d_sprintf_10, orig_d_sprintf_10);

  int s21_d_sprintf_11 = s21_sprintf(data, "%d", 1234);
  int orig_d_sprintf_11 = sprintf(data_copy, "%d", 1234);
  ck_assert_int_eq(s21_d_sprintf_11, orig_d_sprintf_11);
}
END_TEST

START_TEST(s21_sprintf_u_test) {
  char data[100];
  char data_copy[100];
  int str1 = 123;
  int str2 = 2147483647;
  int str3 = -2147483648;

  int s21_u_sprintf_1 = s21_sprintf(data, "%u", str1);
  int orig_u_sprintf_1 = sprintf(data_copy, "%u", str1);
  ck_assert_int_eq(s21_u_sprintf_1, orig_u_sprintf_1);

  int s21_u_sprintf_2 = s21_sprintf(data, "%-u", str1);
  int orig_u_sprintf_2 = sprintf(data_copy, "%-u", str1);
  ck_assert_int_eq(s21_u_sprintf_2, orig_u_sprintf_2);

  int s21_u_sprintf_3 = s21_sprintf(data, "%.1u", str1);
  int orig_u_sprintf_3 = sprintf(data_copy, "%.1u", str1);
  ck_assert_int_eq(s21_u_sprintf_3, orig_u_sprintf_3);

  int s21_u_sprintf_4 = s21_sprintf(data, "%lu", (long unsigned int)str3);
  int orig_u_sprintf_4 = sprintf(data_copy, "%lu", (long unsigned int)str3);
  ck_assert_int_eq(s21_u_sprintf_4, orig_u_sprintf_4);

  int s21_u_sprintf_5 = s21_sprintf(data, "%lu", (long unsigned int)str2);
  int orig_u_sprintf_5 = sprintf(data_copy, "%lu", (long unsigned int)str2);
  ck_assert_int_eq(s21_u_sprintf_5, orig_u_sprintf_5);

  int s21_u_sprintf_6 = s21_sprintf(data, "%05u", str1);
  int orig_u_sprintf_6 = sprintf(data_copy, "%05u", str1);
  ck_assert_int_eq(s21_u_sprintf_6, orig_u_sprintf_6);

  int s21_u_sprintf_7 = s21_sprintf(data, "%hu", str1);
  int orig_u_sprintf_7 = sprintf(data_copy, "%hu", str1);
  ck_assert_int_eq(s21_u_sprintf_7, orig_u_sprintf_7);

  int s21_u_sprintf_8 = s21_sprintf(data, "%u %u %u", str1, str2, str3);
  int orig_u_sprintf_8 = sprintf(data_copy, "%u %u %u", str1, str2, str3);
  ck_assert_int_eq(s21_u_sprintf_8, orig_u_sprintf_8);
}
END_TEST

START_TEST(s21_sprintf_f_test) {
  char data[100];
  char data_copy[100];

  double str1 = 1;
  double str2 = 0.0000132;
  double str3 = 1234523459.123456789;
  double str4 = -342.4324243241231;

  int s21_f_sprintf_1 = s21_sprintf(data, "%f", str1);
  int orig_f_sprintf_1 = sprintf(data_copy, "%f", str1);
  ck_assert_int_eq(s21_f_sprintf_1, orig_f_sprintf_1);

  int s21_f_sprintf_2 = s21_sprintf(data, "%2.2f", str2);
  int orig_f_sprintf_2 = sprintf(data_copy, "%2.2f", str2);
  ck_assert_int_eq(s21_f_sprintf_2, orig_f_sprintf_2);

  int s21_f_sprintf_3 = s21_sprintf(data, "%20.f", str4);
  int orig_f_sprintf_3 = sprintf(data_copy, "%20.f", str4);
  ck_assert_int_eq(s21_f_sprintf_3, orig_f_sprintf_3);

  int s21_f_sprintf_4 = s21_sprintf(data, "%+.4f", str4);
  int orig_f_sprintf_4 = sprintf(data_copy, "%+.4f", str4);
  ck_assert_int_eq(s21_f_sprintf_4, orig_f_sprintf_4);

  int s21_f_sprintf_6 = s21_sprintf(data, "%lf", str4);
  int orig_f_sprintf_6 = sprintf(data_copy, "%lf", str4);
  ck_assert_int_eq(s21_f_sprintf_6, orig_f_sprintf_6);

  int s21_f_sprintf_9 = s21_sprintf(data, "%f %f %f", str1, str2, str3);
  int orig_f_sprintf_9 = sprintf(data_copy, "%f %f %f", str1, str2, str3);
  ck_assert_int_eq(s21_f_sprintf_9, orig_f_sprintf_9);

  int s21_f_sprintf_10 = s21_sprintf(data, "%f", 123.0);
  int orig_f_sprintf_10 = sprintf(data_copy, "%f", 123.0);
  ck_assert_int_eq(s21_f_sprintf_10, orig_f_sprintf_10);

  int s21_f_sprintf_11 = s21_sprintf(data, "Helllo");
  int orig_f_sprintf_11 = sprintf(data_copy, "Helllo");
  ck_assert_int_eq(s21_f_sprintf_11, orig_f_sprintf_11);
}
END_TEST

int main(void) {
  Suite *s;
  SRunner *sr;
  TCase *tc = tcase_create("core");
  s = suite_create("s21_string");
  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_memchr_test);    // memchr
  tcase_add_test(tc, s21_memcmp_test);    // memcmp
  tcase_add_test(tc, s21_memcpy_test);    // memcpy
  tcase_add_test(tc, s21_memset_test);    // memset
  tcase_add_test(tc, s21_strlen_test);    // strlen
  tcase_add_test(tc, s21_strncat_test);   // strncat
  tcase_add_test(tc, s21_strchr_test);    // strchr
  tcase_add_test(tc, s21_strncmp_test);   // strncmp
  tcase_add_test(tc, s21_strcspn_test);   // strcspn
  tcase_add_test(tc, s21_strpbrk_test);   // strpbrk
  tcase_add_test(tc, s21_strrchr_test);   // strrchr
  tcase_add_test(tc, s21_strstr_test);    // strstr
  tcase_add_test(tc, s21_strtok_test);    // strtok
  tcase_add_test(tc, s21_strerror_test);  // strerror
  tcase_add_test(tc, s21_strncpy_test);   // strncpy
  tcase_add_test(tc, s21_to_upper_test);  // to_upper
  tcase_add_test(tc, s21_to_lower_test);  // to_lower
  tcase_add_test(tc, s21_insert_test);    // insert
  tcase_add_test(tc, s21_trim_test);      // trim

  tcase_add_test(tc, s21_sprintf_c_test);  // sprintf %c
  tcase_add_test(tc, s21_sprintf_s_test);  // sprintf %s
  tcase_add_test(tc, s21_sprintf_d_test);  // sprintf %d
  tcase_add_test(tc, s21_sprintf_u_test);  // sprintf %u
  tcase_add_test(tc, s21_sprintf_f_test);  // sprintf %f

  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int failed_tests = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed_tests == 0) ? 0 : 1;
}
