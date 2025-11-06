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
        this->color = new char[strlen(color) + 1];
        strcpy(this->color, color);
    }
    Rectangle()
    {
        this->length = 0;
        this->width = 0;
        this->color = NULL;
    }
    Rectangle(const Rectangle &rect)
    {
        length = rect.length;
        width = rect.width;
        color = new char[strlen(rect.color) + 1];
        strcpy(color, rect.color);
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
    Rectangle *clone()
    {
        Rectangle *new_rectangle = new Rectangle(this->length, this->width, this->color);
        return new_rectangle;
    }
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
        this->color = new char[(strlen(color) + 1)];
        strcpy(this->color, color);
    }
    Triangle()
    {
        this->a = 0;
        this->b = 0;
        this->c = 0;
        this->color = NULL;
    }
    Triangle(const Triangle &tri)
    {
        a = tri.a;
        b = tri.b;
        c = tri.c;
        color = new char[strlen(tri.color) + 1];
        strcpy(color, tri.color);
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
        double s = (a + b + c) / 2.0;
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
    Triangle *clone()
    {
        Triangle *new_triangle = new Triangle(this->a, this->b, this->c, this->color);
        return new_triangle;
    }
};
class Circle
{
    double radius;
    char *color;

public:
    Circle(double radius, const char *color)
    {
        this->radius = radius;
        this->color = new char[(strlen(color) + 1)];
        strcpy(this->color, color);
    }
    Circle()
    {
        this->radius = 0;
        this->color = NULL;
    }
    Circle(const Circle &cir)
    {
        radius = cir.radius;

        color = new char[strlen(cir.color) + 1];
        strcpy(color, cir.color);
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
    Circle *clone()
    {
        Circle *new_circle = new Circle(this->radius, this->color);

        return new_circle;
    }
};

class ShapeCollection
{
    Rectangle **Rectangle_array;
    Triangle **Triangle_array;
    Circle **Circle_array;

    int rect_index, tri_index, cir_index;
    int rect_capacity, tri_capacity, cir_capacity;

public:
    ShapeCollection()
    {
        rect_index = 0;
        tri_index = 0;
        cir_index = 0;
        rect_capacity = 1;
        tri_capacity = 1;
        cir_capacity = 1;
        Rectangle_array = new Rectangle *[1];
        Triangle_array = new Triangle *[1];
        Circle_array = new Circle *[1];
    }
    void add(Rectangle rect)
    {
        if (rect_index < rect_capacity)
        {
            Rectangle_array[rect_index] = new Rectangle(rect);
            rect_index++;
        }
        else
        {
            Rectangle **new_rectangle_array = new Rectangle *[rect_capacity * 2];
            for (int i = 0; i < rect_capacity; i++)
                new_rectangle_array[i] = Rectangle_array[i]->clone();

            cout << "increasing capacity of rectangles from " << rect_capacity << " to " << rect_capacity * 2 << endl;
            for (int i = 0; i < rect_capacity; i++)
                delete Rectangle_array[i];
            delete[] Rectangle_array;
            Rectangle_array = new_rectangle_array;
            rect_capacity *= 2;
            add(rect);
        }
    }
    void add(Triangle tri)
    {
        if (tri_index < tri_capacity)
        {
            Triangle_array[tri_index] = new Triangle(tri);
            tri_index++;
        }
        else
        {
            Triangle **new_triangle_array = new Triangle *[tri_capacity * 2];
            for (int i = 0; i < tri_capacity; i++)
                new_triangle_array[i] = Triangle_array[i]->clone();
            cout << "increasing capacity of triangles from " << tri_capacity << " to " << tri_capacity * 2 << endl;
            for (int i = 0; i < tri_capacity; i++)
                delete Triangle_array[i];
            delete[] Triangle_array;
            Triangle_array = new_triangle_array;
            tri_capacity *= 2;
            add(tri);
        }
    }
    void add(Circle cir)
    {
        if (cir_index < cir_capacity)
        {
            Circle_array[cir_index] = new Circle(cir);
            cir_index++;
        }
        else
        {
            Circle **new_circle_array = new Circle *[cir_capacity * 2];
            for (int i = 0; i < cir_capacity; i++)
                new_circle_array[i] = Circle_array[i]->clone(); /// here needs to be cloned

            cout << "increasing capacity of circles from " << cir_capacity << " to " << cir_capacity * 2 << endl;
            for (int i = 0; i < cir_capacity; i++)
                delete Circle_array[i];
            delete[] Circle_array;
            Circle_array = new_circle_array;
            cir_capacity *= 2;
            add(cir);
        }
    }

    int getRectCount() { return rect_index; }
    int getTriCount() { return tri_index; }
    int getCircCount() { return cir_index; }
    void printRectangles()
    {
        for (int i = 0; i < rect_index; i++)
            cout << "Rectangle " << i << ": length: " << (*Rectangle_array[i]).getlength() << " width: " << (*Rectangle_array[i]).getwidth() << endl;
    }
    void printTriangles()
    {
        for (int i = 0; i < tri_index; i++)
            cout << "Triangle " << i << ": a: " << (*Triangle_array[i]).geta() << " b: " << (*Triangle_array[i]).getb() << " c: " << (*Triangle_array[i]).getc() << endl;
    }
    void printCircles()
    {
        for (int i = 0; i < cir_index; i++)
            cout << "Circle " << i << ": radius: " << (*Circle_array[i]).getradius() << endl;
    }
    ~ShapeCollection()
    {
        for (int i = 0; i < rect_index; i++)
            delete Rectangle_array[i];
        delete[] Rectangle_array;
        for (int i = 0; i < tri_index; i++)
            delete Triangle_array[i];
        delete[] Triangle_array;
        for (int i = 0; i < cir_index; i++)
            delete Circle_array[i];
        delete[] Circle_array;
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
    When constructing the ShapeCollection class, you will create dynamic for
    rectangles, triangles and circles. You have to dynamically allocate memory for this.
    */
    ShapeCollection shapes;
    /* IMPORTANT: You need to pass the objects by value to the add functions
    If you pass by value, the copy constructor will be called and the dynamically
    allocated memory will be copied. So, you have to write copy contructor so that
    memory allocation is properly done and no double free error occurs.
    */

    shapes.add(r1);
    shapes.add(t1);
    shapes.add(c1);

    Rectangle r2(15, 25, "Black");
    Rectangle r3(150, 225, "Green");
    shapes.add(r2);
    shapes.add(r3);
    Triangle t2(5, 12, 13, "White");
    shapes.add(t2);

    cout << "Number of Rectangles: " << shapes.getRectCount() << endl;
    cout << "Number of Triangles: " << shapes.getTriCount() << endl;
    cout << "Number of Circles: " << shapes.getCircCount() << endl;
    cout << "--------------------------------------" << endl;

    shapes.printRectangles();
    shapes.printTriangles();
    shapes.printCircles();

    return 0;
}