#include "ports.h"

unsigned char inb(unsigned short port)
{
  unsigned char ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

void outb(unsigned short port, unsigned char data)
{
  asm volatile("outb %1, %0" : : "dN"(port), "a"(data));
}

unsigned short inw(unsigned short port)
{
  unsigned short ret;
  asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

void outw(unsigned short port, unsigned short data)
{
  asm volatile("outw %1, %0" : : "dN"(port), "a"(data));
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
