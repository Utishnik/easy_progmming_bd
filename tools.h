#ifndef TOOLSH
#define TOOLSH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


void *_Malloc(size_t size,int *err);

template <typename T>
size_t _array_size(T *arr);

std::string _char_to_str(char *str);

char *_str_to_char(std::string str);

#endif 