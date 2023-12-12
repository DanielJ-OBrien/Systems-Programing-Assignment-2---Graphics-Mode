#include "types.h"
#include "user.h"	

int main(int argc, char *argv[]) {

	int givenDeviceContext = beginpaint(0);

	createcontext(0, 0, 0, 0x06);

	setpencolour(20, 130, 43, 32);
	selectpen(givenDeviceContext, 20);
	setpixel(givenDeviceContext, 75, 99);
	setpixel(givenDeviceContext, 125, 45);  
	setpixel(givenDeviceContext, 12, 12); 
	setpixel(givenDeviceContext, 69, 64); 

	lineto(givenDeviceContext, 350, 100);

	struct rect rect2;

	rect2.top = 150;
	rect2.left = 96;
	rect2.bottom = 250;
	rect2.right = 110;
	fillrect(givenDeviceContext, &rect2);

	endpaint(givenDeviceContext);

	exit();
}
