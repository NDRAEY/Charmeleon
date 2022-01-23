#include "isr.h"
#include "regs.h"

void register_irq(int num, isr_t handler);
void firq_handler(register_t * reg);
