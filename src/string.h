#ifndef STRING_H
#define STRING_H

unsigned int digit_count(int num);
void itoa(int num, char *number);
void itoh(unsigned long n, char sign, char *outbuf);
int strcpy(char *dst, const char *src);
void *memset(void *dst,char val, int n);
void strcat(void *dest, const void *src);
int strlen(const char *s);
void *memcpy(void *dst, void const *src, int n);

#endif