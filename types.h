typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
struct rect {
 int top; // y co-ordinate of top of rectangle
 int left; // x co-ordinate of left of rectangle
 int bottom; // y co-ordinate of bottom of rectangle
 int right; // x co-ordinate of right of rectangle
};
struct deviceContext{
    int cX; // Current x position for drawing
    int cY; // Current y position for drawing
    int sPC; // Selected pen color
};
