#include "test_str.h"
#include "str.h"


void test_my_strcpy() {
    char s1[6];
    char s2[6] = "c-lab\0";
    my_strcpy(s1, s2);
    assert(my_strcmp(s1, s2) == 0);
}

void test_my_strcat() {
    char s1[13] = "c-lab\0";
    char s2[8] = "_alkaev\0";
    my_strcat(s1, s2);
    char result[13] = "c-lab_alkaev\0";
    assert(my_strcmp(s1, result) == 0);
}

void test_my_strcmp() {
    char s1[4] = "ab\0";
    char s2[3] = "a\0";
    assert(my_strcmp(s1, s2) > 0);
    char s3[4] = "ab\0";
    assert(my_strcmp(s1, s3) == 0);
    char s4[3] = "b\0";
    assert(my_strcmp(s1, s4) < 0);
}

void test_my_strlen() {
    assert(my_strlen("") == 0);
    assert(my_strlen("c-lab") == 5);
}