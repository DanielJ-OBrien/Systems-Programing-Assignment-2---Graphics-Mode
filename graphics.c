#include "types.h"
#include "defs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"


void clear320x200x256() {
	unsigned int *ptr = (unsigned int*)P2V(0xA0000);
	memset(ptr, 0x00, 64000);
};

int sys_setpixel(void){
	int hdc, x, y;

    if ((argint(0, &hdc) < 0) || (argint(1, &x) < 0) || (argint(2, &y) < 0)){
        return -1;
    }

	cprintf("%d ", x);
	cprintf("%d ", y);
	cprintf("  ");

	int address = 0xA0000 + 320 * y + x; // This line calculate addresses wrong.
	unsigned int *ptr = (unsigned int*)P2V(address);
	*ptr = 0x0F;
	return 0;	
};

int sys_moveto(int hdc, int x, int y){
	return 0;
};

int sys_lineto(int hdc, int x, int y){
	return 0;
};