#include "pic.h"
#include "ports.h"

// Code from: https://github.com/szhou42/osdev

void pic_init() {
    outb(PIC1_COMMAND, ICW1);
    outb(PIC2_COMMAND, ICW1);

    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    outb(PIC1_DATA, 0x4);
    outb(PIC2_DATA, 0x2);

    outb(PIC1_DATA, 1);
    outb(PIC2_DATA, 1);

    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 0);
}

/*
 * Tell PIC interrupt is handled
 * */
void irq_ack(char irq) {
    if(irq >= 0x28)
        outb(PIC2, PIC_EOI);
    outb(PIC1, PIC_EOI);
}
