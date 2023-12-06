#include "types.h"
#include "user.h"


int main(int argc, char *argv[]) {
	setvideomode(0x13);
	setpixel(0, 50, 100);
	setpixel(0, 100, 50);  
	setpixel(0, 50, 50); 
	setpixel(0, 100, 100); 
	getch();
	setvideomode(0x03);
	exit();
}
