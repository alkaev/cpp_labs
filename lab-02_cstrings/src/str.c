#include "str.h"
#include <stddef.h>


char* my_strcpy(char * restrict s1, const char * restrict s2){
    char *p1 = s1;
    while ( *s2 != '\0')
    {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
     return p1;    
}

char *my_strcat(char * restrict s1, const char * restrict s2){
    char *p1 = s1;
    while (*s1 != '\0')
    {
        s1++;
    }
    while(*s2 != '\0')
    {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
    return p1;
}

int my_strcmp(const char *s1, const char *s2){
    while(*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;   
}

size_t my_strlen(const char *s){
    const char *p = s;
    while (*p != '\0') p++;
    return p - s;
}






