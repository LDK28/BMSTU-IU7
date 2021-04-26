#ifndef MYFUNCIONS_H
#define MYFUNCIONS_H

#include <stdio.h>
#include <stdlib.h>

const char*my_strpbrk(const char *string1, const char *string2);
size_t my_strspn(const char *string1, const char *string2);
size_t my_strcspn(const char *string1, const char *string2);
const char*my_strchr(const char *string, int symbol);
const char*my_strrchr(const char *string, int symbol);

#endif 