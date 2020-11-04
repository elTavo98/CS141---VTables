#include <malloc.h>

#define PI 3.14159

typedef double (*VirtualMethodPointer)(void*);
typedef VirtualMethodPointer* VTableType;
typedef struct Shape Shape;
typedef struct Circle Circle;
typedef struct Triangle Triangle;
typedef struct Square Square;
typedef struct Rectangle Rectangle;

// Shape Class
struct Shape
{
	VTableType VPointer;
	char* name;
};

double Shape_area(Shape* _this)
{
	return 0.0;
}

void Shape_draw(Shape* _this)
{
	printf("\n");
}

VirtualMethodPointer Shape_VTable [] =
{
	(VirtualMethodPointer)Shape_area,
	(VirtualMethodPointer)Shape_draw
};

Shape* Shape_Shape(Shape* _this, char* name)
{
	_this->VPointer = Shape_VTable;
	_this->name = name;
	return _this;
}

//Circle Class
struct Circle
	// extends Shape
{
	VTableType VPointer;
	char* name;
	int radius;
};

double Circle_area(Circle* _this)
{
	return PI * _this->radius * _this->radius;
}

void Circle_draw(Circle* _this)
{
	printf("    *  *    \n");
    printf(" *        * \n");
    printf("*          *\n");
    printf("*          *\n");
    printf(" *        * \n");
    printf("    *  *    \n");
}

void Circle_dimensions(Circle* _this)
{
	printf("%s: radius = %i \n", _this->name, _this->radius);
}

VirtualMethodPointer Circle_VTable[] =
{
	(VirtualMethodPointer)Circle_area,
	(VirtualMethodPointer)Circle_draw,
	(VirtualMethodPointer)Circle_dimensions
};

Circle* Circle_Circle(Circle* _this, char* name, int newRadius)
{
	Shape_Shape((Shape*)_this, name);
	_this->VPointer = Circle_VTable;
	_this->radius = newRadius;
	return _this;
}

//Triangle Class
struct Triangle
	// extends Shape
{
	VTableType VPointer;
	char* name;
	int base;
	int height;
};

double Triangle_area(Triangle* _this)
{
	return 0.5 * _this->base * _this->height;
}

void Triangle_draw(Triangle* _this)
{
    printf("     *\n");
    printf("   *   *\n");
    printf("  *     *\n");
    printf(" *       *\n");
    printf("* * * * * *\n");
}

void Triangle_dimensions(Triangle* _this)
{
	printf("%s: height=%i, base=%i\n", _this->name, _this->height, _this->base);
}

VirtualMethodPointer Triangle_VTable[] = 
{
	(VirtualMethodPointer)Triangle_area,
	(VirtualMethodPointer)Triangle_draw,
	(VirtualMethodPointer)Triangle_dimensions
};

Triangle* Triangle_Triangle(Triangle* _this, char* name, int h, int b)
{
	Shape_Shape((Shape*)_this, name);
	_this->VPointer = Triangle_VTable;
	_this->base = b;
	_this->height = h;
	return _this;
}

// Square Class
struct Square
{
	VTableType VPointer;
	char* name;
	int side;
};

double Square_area(Square* _this)
{
	return _this->side * _this->side;
}

void Square_draw(Square* _this)
{
    printf(" _______\n");
    printf("|       |\n");
    printf("|       |\n");
    printf("|       |\n");
    printf(" -------\n");
}

void Square_dimensions(Square* _this)
{
	printf("%s: side = %i \n", _this->name, _this->side);
}

VirtualMethodPointer Square_VTable[] =
{
	(VirtualMethodPointer)Square_area,
	(VirtualMethodPointer)Square_draw,
	(VirtualMethodPointer)Square_dimensions
};

Square* Square_Square(Square* _this, char* name, int s)
{
	Shape_Shape((Shape*)_this, name);
	_this->VPointer = Square_VTable;
	_this->side = s;
	return _this;
}

// Rectangle Class
struct Rectangle
{
	VTableType VPointer;
	char* name;
	int side;
	int length;
};

double Rectangle_area(Rectangle* _this)
{
	return _this->side * _this->length;
}

void Rectangle_draw(Rectangle* _this)
{
    printf(" ___________\n");
    printf("|           |\n");
    printf("|           |\n");
    printf("|           |\n");
    printf(" -----------\n");
}

void Rectangle_dimensions(Rectangle* _this)
{
	printf("%s: height = %i, width = %i \n", _this->name, _this->length, _this->side);
}

VirtualMethodPointer Rectangle_VTable[] =
{
	(VirtualMethodPointer)Rectangle_area,
	(VirtualMethodPointer)Rectangle_draw,
	(VirtualMethodPointer)Rectangle_dimensions
};

Rectangle* Rectangle_Rectangle(Rectangle* _this, char* name, int newLength, int width)
{
	Square_Square((Square*)_this, name, width);
	_this->VPointer = Rectangle_VTable;
	_this->length = newLength;
	return _this;
}


int main()
{
	// Allocs
	Shape* picture[] = {/*
		Shape_Shape((Shape*)malloc(sizeof(Shape)), "FirstShape"),
		Shape_Shape((Shape*)malloc(sizeof(Shape)), "SecondShape"),*/
		(Shape*)Triangle_Triangle((Triangle*)malloc(sizeof(Triangle)), "FirstTriangle", 5, 5),
		(Shape*)Triangle_Triangle((Triangle*)malloc(sizeof(Triangle)), "SecondTriangle", 4, 3),
		(Shape*)Circle_Circle((Circle*)malloc(sizeof(Circle)), "FirstCircle", 5),
		(Shape*)Circle_Circle((Circle*)malloc(sizeof(Circle)), "SecondCircle", 10),
		(Shape*)Square_Square((Square*)malloc(sizeof(Square)), "FirstSquare", 5),
		(Shape*)Square_Square((Square*)malloc(sizeof(Square)), "SecondSquare", 10),
		(Shape*)Rectangle_Rectangle((Rectangle*)malloc(sizeof(Rectangle)), "FirstRectangle", 4, 8),
		(Shape*)Rectangle_Rectangle((Rectangle*)malloc(sizeof(Rectangle)), "SecondRectangle", 8, 4)
	};


	//Fun stuff a.k.a Dynamic Binding
	for(int i = 0; i < sizeof(picture)/sizeof(*picture); i++)
	{
		(picture[i]->VPointer[2])(picture[i]);
	}

	double sum = 0.0;
	for(int i = 0; i < sizeof(picture)/sizeof(*picture); i++)
	{
		sum += (picture[i]->VPointer[0])(picture[i]);
		//printf("Area for %s is %f \n", picture[i]->name, picture[i]->VPointer[0](picture[i]));
	}
	printf("The total area of the shapes on this picture is %f \n", sum);


	for(int i = 0; i < sizeof(picture)/sizeof(*picture); i++)
	{
		picture[i]->VPointer[1](picture[i]);
	}


	// Deallocs
	for(int i = 0; i < sizeof(picture)/sizeof(*picture); i++)
	{
		free(picture[i]);
	}
	return 0;
}
