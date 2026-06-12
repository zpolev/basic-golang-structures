#include "zutils.h"
#include <stdio.h>

void printInt(void *e) { printf("%d\n", *(int *)e); }
void printDouble(void *e) { printf("%f\n", *(double *)e); }
void printFloat(void *e) { printf("%f\n", *(float *)e); }
void printChar(void *e) { printf("%c\n", *(char *)e); }
