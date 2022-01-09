PREFIX = i686-linux-gnu-
CFLAGS = -Wall -Wextra -std=gnu99 -c -g -ffreestanding -O2 -m32
LDFLAGS = -T src/link.ld -nostdlib --nmagic
LDFLAGS_NOSCRIPT = -nostdlib --nmagic
