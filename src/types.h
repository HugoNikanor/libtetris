#ifndef TYPES_H
#define TYPES_H

typedef struct {
	int x;
	int y;
} point;

typedef enum
	{ EMPTY, GREEN, RED, ORANGE, YELLOW, BLUE, MAGENTA, CYAN }
color;

typedef struct {
	color color;
	unsigned rotation : 2;
	// the size of the bounding box of the piece - 1
	int bounds;
	point* shape; // list
} piece;

typedef enum { LEFT, RIGHT } direction;

#endif // TYPES_H
