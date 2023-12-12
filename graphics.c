#include "types.h"
#include "defs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"

struct deviceContext deviceContexts[10];
int inUse = 0;

void clear320x200x256() {
	unsigned int *ptr = (unsigned int*)P2V(0xA0000);
	memset(ptr, 0x00, 64000);
};

int sys_setpixel(void){
	int hdc, x, y;

    if ((argint(0, &hdc) < 0) || (argint(1, &x) < 0) || (argint(2, &y) < 0)){
        return -1;
    }

	int address = 0xA0000 + 320 * y + x; 
	unsigned int *ptr = (unsigned int*)P2V(address);
	*ptr = deviceContexts[hdc].sPC;
	return 0;	
};

int sys_moveto(void){
	int hdc, x, y;

    if ((argint(0, &hdc) < 0) || (argint(1, &x) < 0) || (argint(2, &y) < 0)){
        return -1;
    }

	if(x>320){x=320;} // Clips values
	if(x<0){x=0;}
	if(y>200){y=200;}
	if(y<0){y=0;}

	deviceContexts[hdc].cX = x;
	deviceContexts[hdc].cY = y;

	return 0;
};

int abs(int a) {
    return a >= 0 ? a : -a;
}

int sys_lineto(void){
	int hdc, x, y;

    if ((argint(0, &hdc) < 0) || (argint(1, &x) < 0) || (argint(2, &y) < 0)){
        return -1;
    }

    int dx = abs(x - deviceContexts[hdc].cX);
    int dy = abs(y - deviceContexts[hdc].cY);
    int sx = deviceContexts[hdc].cX < x ? 1 : -1;
    int sy = deviceContexts[hdc].cY < y ? 1 : -1; // Calculates difference and direction of line
    int err = dx - dy;

    while (deviceContexts[hdc].cX != x ||deviceContexts[hdc].cY != y) {

		int address = 0xA0000 + 320 * deviceContexts[hdc].cY + deviceContexts[hdc].cX;
		unsigned int *ptr = (unsigned int*)P2V(address);
		*ptr = deviceContexts[hdc].sPC; // Sets the relevant pixel

        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            deviceContexts[hdc].cX += sx; // Calculates next location on slope
        }
        if (err2 < dx) {
            err += dx;
            deviceContexts[hdc].cY += sy;
        }
    }
	return 0;
};

int sys_setpencolour(void){
	int index, r, g, b;

    if ((argint(0, &index) < 0) || (argint(1, &r) < 0) || (argint(2, &g) < 0) || (argint(3, &b) < 0)){
        return -1;
    }

	if(index>255){index=255;} // Clips values
	if(index<16){index=16;}
	if(r>63){r=63;}
	if(r<0){r=0;}
	if(g>63){g=63;}
	if(g<0){g=0;}
	if(b>63){b=63;}
	if(b<0){b=0;}

	asm volatile("outb %b0, %w1" : : "a"(index), "Nd"(0x3C8));
	asm volatile("outb %b0, %w1" : : "a"(r), "Nd"(0x3C9));
	asm volatile("outb %b0, %w1" : : "a"(g), "Nd"(0x3C9));
	asm volatile("outb %b0, %w1" : : "a"(b), "Nd"(0x3C9));

	return 0;
}

int sys_selectpen(void){

	int hdc, index;

    if ((argint(0, &hdc) < 0) || (argint(1, &index) < 0)){
        return -1;
    }

	deviceContexts[hdc].sPC = index;
	
	return 0;
}

int sys_fillrect(void){
	int hdc;
	struct rect *r;
	
	if (argint(0, &hdc) < 0 || argptr(1, (void *)&r, sizeof(*r)) < 0){
		return -1;
	}

	for(int y=r->top; y<r->bottom; y++){
		for(int x =r->left; x<r->right; x++){
			int address = 0xA0000 + 320 * y + x; 
			unsigned int *ptr = (unsigned int*)P2V(address);
			*ptr = deviceContexts[hdc].sPC;
		}
	}

	return 0;
}

int sys_createcontext(void){
	int x, y, colour, context;

    if ((argint(0, &x) < 0) || (argint(1, &y) < 0) || (argint(2, &colour) < 0) || (argint(3, &context) < 0)){
        return -1;
    }

	deviceContexts[context].cX = x;
	deviceContexts[context].cY = y;
	deviceContexts[context].sPC = colour;
	return 0;

}

int sys_beginpaint(void){
	int hwnd;

    if (argint(0, &hwnd) < 0){
        return -1;
    }

	inUse+=1;

	return (inUse-1);
}

int sys_endpaint(void){
	int hdc;

    if (argint(0, &hdc) < 0){
        return -1;
    }

	inUse-=1;

	return 0;
}