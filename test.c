#include "types.h"
#include "user.h"	

int main(int argc, char *argv[]) {

	setvideomode(0x13);

	int givenDeviceContext = beginpaint(0);

	createcontext(0, 0, 0, 0x0F);

	int pid = fork();
    if (pid == 0) {
        // Child process
        char *args[] = {"test2", 0}; // Arguments for exec
        exec("test2", args); // Execute the second program
    }

	setpencolour(16, 0, 43, 32);
	selectpen(givenDeviceContext, 16);
	setpixel(givenDeviceContext, 50, 100);
	setpixel(givenDeviceContext, 100, 50);  
	setpixel(givenDeviceContext, 50, 50); 
	setpixel(givenDeviceContext, 100, 100); 
	setpencolour(17, 43, 32, 0);
	selectpen(givenDeviceContext, 17);
	lineto(givenDeviceContext, 320, 200);
	moveto(givenDeviceContext, 320, 0);
	setpencolour(18, 43, 0, 32);
	selectpen(givenDeviceContext, 18);
	lineto(givenDeviceContext, 0, 200);

	struct rect rect;
	rect.top = 70;
	rect.left = 30;
	rect.bottom = 140;
	rect.right = 60;
	fillrect(givenDeviceContext, &rect);

	setpencolour(19, 34, 53, 107);
	selectpen(givenDeviceContext, 19);

	rect.top = 100;
	rect.left = 100;
	rect.bottom = 150;
	rect.right = 200;
	fillrect(givenDeviceContext, &rect);

	endpaint(givenDeviceContext);

	wait();
	getch();
	setvideomode(0x03);
	exit();
}
