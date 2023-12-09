#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
	setvideomode(0x13);
	setpencolour(16, 0, 43, 32);
	selectpen(0, 16);
	setpixel(0, 50, 100);
	setpixel(0, 100, 50);  
	setpixel(0, 50, 50); 
	setpixel(0, 100, 100); 
	setpencolour(17, 43, 32, 0);
	selectpen(0, 17);
	lineto(0, 320, 200);
	moveto(0, 320, 0);
	setpencolour(18, 43, 0, 32);
	selectpen(0, 18);
	lineto(0, 0, 200);

	struct rect rect;
	rect.top = 70;
	rect.left = 30;
	rect.bottom = 140;
	rect.right = 60;
	fillrect(0, &rect);

	setpencolour(19, 34, 53, 107);
	selectpen(0, 19);

	rect.top = 100;
	rect.left = 100;
	rect.bottom = 150;
	rect.right = 200;
	fillrect(0, &rect);

	getch();
	setvideomode(0x03);
	exit();
}
