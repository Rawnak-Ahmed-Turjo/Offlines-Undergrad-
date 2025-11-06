#include <iostream>
#include <cmath>
#include <cstring>
#define pi 3.1416
using namespace std;
class Rectangle
{
    double length;
    double width;
    char *color;

public:
    Rectangle(double length, double width, const char *color)
    {
        this->length = length;
        this->width = width;
        this->color = (char *)malloc(strlen(color) + 1);
        strcpy(this->color, color);
    }
    Rectangle()
    {
        this->length = 0;
        this->width = 0;
        this->color = NULL;
    }
    ~Rectangle()
    {
        free(this->color);
    }
    double getPerimeter()
    {
        return 2 * (length + width);
    }
    double getArea()
    {
        return length * width;
    }
    char *getColor()
    {
        return color;
    }
    void setColor(const char *color)
    {
        free(this->color);
        this->color = (char *)malloc(strlen(color) + 1);
        strcpy(this->color, color);
    }
    int getlength() { return length; }
    int getwidth() { return width; }
    void setlength(double length) { this->length = length; }
    void setwidth(double width) { this->width = width; }
};
class Triangle
{
    double a;
    double b;
    double c;
    char *color;

public:
    Triangle(double a, double b, double c, const char *color)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->color = (char *)malloc(strlen(color) + 1);
        strcpy(this->color, color);
    }
    Triangle()
    {
        this->a = 0;
        this->b = 0;
        this->c = 0;
        this->color = NULL;

    }
    ~Triangle()
    {
        free(this->color);
    }
    double getPerimeter()
    {
        return a + b + c;
    }
    double getArea()
    {
        int s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    char *getColor()
    {
        return color;
    }
    void setColor(const char *color)
    {
        free(this->color);
        this->color = (char *)malloc(strlen(color) + 1);
        strcpy(this->color, color);
    }
    int geta() { return a; }
    int getb() { return b; }
    int getc() { return c; }
    void seta(double a) { this->a = a; }
    void setb(double b) { this->b = b; }
    void setc(double c) { this->c = c; }
};
class Circle
{
    double radius;
    char *color;

public:
    Circle(double radius, const char *color)
    {
        this->radius = radius;
        this->color = (char *)malloc(strlen(color) + 1);
        strcpy(this->color, color);
    }
    Circle()
    {
        this->radius = 0;
        this->color = NULL;

    }
    double getPerimeter()
    {
        return 2 * pi * radius;
    }
    double getArea()
    {
        return pi * radius * radius;
    }
    char *getColor()
    {
        return color;
    }
    void setColor(const char *color)
    {
        free(this->color);
        this->color = (char *)malloc(strlen(color) + 1);
        strcpy(this->color, color);
    }
    ~Circle()
    {
        free(this->color);
    }
    int getradius() { return radius; }
    void setradius(double radius) { this->radius = radius; };
};

class ShapeCollection
{
    Rectangle Rectangle_array[100];
    Triangle Triangle_array[100];
    Circle Circle_array[100];

    int rect_index = 0, tri_index = 0, cir_index = 0;

public:
    void addRectangle(Rectangle &rect)
    {
        Rectangle_array[rect_index].setlength(rect.getlength());
        Rectangle_array[rect_index].setwidth(rect.getwidth());
        rect_index++;
    }
    void addTriangle(Triangle &tri)
    {
        Triangle_array[tri_index].seta(tri.geta());
        Triangle_array[tri_index].setb(tri.getb());
        Triangle_array[tri_index].setc(tri.getc());
        tri_index++;
    }
    void addCircle(Circle &cir)
    {
        Circle_array[cir_index].setradius(cir.getradius());
        cir_index++;
    }
    int getRectCount() { return rect_index; }
    int getTriCount() { return tri_index; }
    int getCircCount() { return cir_index; }
    void printRectangles()
    {
        for (int i = 0; i < rect_index; i++)
            cout << "Rectangle " << i << ": length: " << Rectangle_array[i].getlength() << " width: " << Rectangle_array[i].getwidth() << endl;
    }
    void printTriangles()
    {
        for (int i = 0; i < tri_index; i++)
            cout << "Triangle " << i << ": a: " << Triangle_array[i].geta() << " b: " << Triangle_array[i].getb() << " c: " << Triangle_array[i].getc() << endl;
    }
    void printCircles()
    {
        for (int i = 0; i < cir_index; i++)
            cout << "Circle " << i << ": radius: " << Circle_array[i].getradius() << endl;
    }

};


int main()
{
    // Create rectangle with length, width, color
    Rectangle r1(10, 20, "Red");
    // The Color is stored using malloc, which will be freed during destruction
    cout << "Rectangle Perimeter: " << r1.getPerimeter() << endl;
    cout << "Rectangle Area: " << r1.getArea() << endl;
    cout << "Rectangle Color: " << r1.getColor() << endl;
    // When changing the color, you need to free the memory of the old color
    // and allocate new memory for the new color
    r1.setColor("Yellow");
    cout << "Rectangle Color: " << r1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    // Create triangle with a, b, c, color. (a, b, c are lengths of the sides)
    Triangle t1(3, 4, 5, "Blue");
    cout << "Triangle Perimeter: " << t1.getPerimeter() << endl;
    cout << "Triangle Color: " << t1.getColor() << endl;
    cout << "Triangle Area: " << t1.getArea() << endl;
    t1.setColor("Orange");
    cout << "Triangle Color: " << t1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    // Create circle with radius, color
    Circle c1(7, "Green");
    cout << "Circle Perimeter: " << c1.getPerimeter() << endl;
    cout << "Circle Area: " << c1.getArea() << endl;
    cout << "Circle Color: " << c1.getColor() << endl;
    c1.setColor("Purple");
    cout << "Circle Color: " << c1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    /*
    When constructing the ShapeCollection class, you will create static arrays for 100
    rectangles, triangles and circles. You don’t have to dynamically allocate memory for this.
    */
    ShapeCollection shapes;
    /* IMPORTANT: You need to pass the objects by reference to the add functions
    If you pass by value, the copy constructor will be called and the dynamically
    allocated memory will be copied, leading to double free errors when things go
    out of scope. Once passed by reference, do not directly store the reference in
    the array. Instead, copy the data from the reference to the array element.
    We will see better ways to handle this in the upcoming sessions.
    */
    shapes.addRectangle(r1);
    shapes.addTriangle(t1);
    shapes.addCircle(c1);

    Rectangle r2(15, 25, "Black");
    shapes.addRectangle(r2);
    Triangle t2(5, 12, 13, "White");
    shapes.addTriangle(t2);

    cout << "Number of Rectangles: " << shapes.getRectCount() << endl;
    cout << "Number of Triangles: " << shapes.getTriCount() << endl;
    cout << "Number of Circles: " << shapes.getCircCount() << endl;
    cout << "--------------------------------------" << endl;

    shapes.printRectangles();
    shapes.printTriangles();
    shapes.printCircles();

    return 0;
}
