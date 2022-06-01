//Question 5 - Class Inheritance, const correctness and operator overloading

// Task 1 : Add a Circle class that has a center point and radius fields, create a base Shape class that both Circle and Rectangle inherit from, try to move as many common field/functions to the base class

// Task 2: Create an operator overload that will allow us to chain a point instance to a ostream (std::cout), for example:
////Point point1(5,7);
////std::cout << point1;
//The previous line should output "5/7" to the console

// Task 3: Review the const correctness of the Shape/Circle/Rectangle member functions and modify them where it's required

// Do not change the main function body - it should compile and run without any modifications after completion of all tasks  


#include <iostream>
#include <vector>
using namespace std;

const double PI = 3.141592653;

struct Point {

	Point() :
		x(0),
		y(0)
	{}

	Point(int x_, int y_) :
		x(x_),
		y(y_)
	{}

	friend ostream& operator<<(ostream& os, const Point& point)
	{
		os << '(' << point.x << ',' << point.y << ')';
		return os;
	}

	int x;
	int y;

};

struct Size { 

	Size() :
		width(0),
		height(0) {}

	Size(const int width_, const int height_) :
		width(width_),
		height(height_) {}

	int width;
	int height;
};

class Shape {//abstract class

protected:
	Point m_center;
public:
	Shape(const Point& center) :
		m_center(center)
	{}

	virtual ~Shape(){}
	virtual string  name() const = 0; //pure virtual function, implementation will provided in the derived class
	const Point& center() const {
		return m_center;
	}
	virtual double area() const = 0; //pure virtual function that shouldnt modify anything inside the object //changed the returning type from size_t for it to return a more accurate value

};

class Rectangle :public Shape {//inheritance


public:

	Rectangle(const Point& center, const Size& size) :
		Shape(center),
		m_size(size)
	{
	}

	Size& size() {
		return m_size;
	}

	double area() const {
		return m_size.width * (size_t)m_size.height;
	}

	string name() const {
		return "Rectangle";
	}

protected:
	Size  m_size;
};

class Circle :public Shape {//inheritance
	
	public:
		Circle(const Point& center, int radius):
			Shape(center),
			m_radius(radius)
		{
		}

		double area() const {
			return PI *m_radius * m_radius;
		}

		string name() const {
			return "Circle";
		}

	protected:
		int  m_radius;
};


int main(int argc, char** argv)
{
	//Do not change anything in this function body
	Circle circle1(Point(5, 5), 10);
	Rectangle rect1(Point(5, 5), Size(10, 10));
	Circle circle2(Point(8, 8), 4);

	std::vector<Shape*> shapes{ &circle1, &rect1, &circle2 };
	for (const Shape* shape : shapes) {
		std::cout << "Shape: " << shape->name() << " center: " << shape->center() << " area: " << shape->area() << std::endl;
	}

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}