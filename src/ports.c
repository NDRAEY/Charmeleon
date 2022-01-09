#include "ports.h"

unsigned char inb(unsigned short port)
{
  unsigned char ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(unsigned short port, unsigned char data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

unsigned long inl(unsigned short port)
{
  unsigned long ret;
  asm volatile("inl %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outl(unsigned short port, unsigned long data)
{
  asm volatile("outl %0, %1" : "=a"(data) : "d"(port));
}
