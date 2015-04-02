/*
 * bridge.h
 *
 * Desc: Decouples an abstraction from its implementations so they can vary independently.
 *
 * Category: Structural
 *
 *  Created on: Apr 5, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Bridge
 *  	http://www.dofactory.com/net/bridge-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter10
 *  	http://sourcemaking.com/design_patterns/bridge
 */

#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <math.h>

namespace homework {

/* Consider a graphics program that must run on multiple platforms.
 * Each platform provides different drawing primitives for lines & arcs.
 * Basic shapes can be constructed from these primitives, such as
 *   rectangles, circles, etc.
 *
 * Use the bridge pattern to write code that avoids the combinatorial explosion
 * of classes and methods which a procedural approach entails.
 * Show how adding another shape or platform requires only a linear amount of
 * additional code.
 *
 * Rectangle, draw 4 lines (upper left corner: x1,y1, lower right corner: x2,y2).
 *	 draw(x1,y1, x2,y1) draw(x2,y1, x2,y2) draw(x2,y2, x1,y2) draw(x1,y2, x1,y1)
 * Circle, draw 4 arcs (90 degrees, clockwise, center is x,y).
 *	 draw(x,y+r, x+r,y) draw(x+r,y, x,y-r) draw(x,y-r, x-r,y) draw(x-r,y, x,y+r)
 *
 * In this problem, the Shape hierarchy has already been implemented.
 * Create a Platform hierarchy and add the plotter platform.
 */

namespace bridge_common {

namespace platform_vector {

void drawLine(double x1, double y1, double x2, double y2) {
	cout << "    Draw vector line: ["<<x1<<","<<y1<<"] ["<<x2<<","<<y2<<"]\n";
}
void drawArc(double x1, double y1, double x2, double y2) {
	cout << "    Draw vector arc: ("<<x1<<","<<y1<<") ("<<x2<<","<<y2<<")\n";
}

}

namespace platform_raster {

void draw_line(double x1, double y1, double x2, double y2) {
	cout << "    Draw raster line: ["<<x1<<","<<y1<<"] ["<<x2<<","<<y2<<"]\n";
}
void draw_arc(double x1, double y1, double x2, double y2) {
	cout << "    Draw raster arc: ("<<x1<<","<<y1<<") ("<<x2<<","<<y2<<")\n";;
}

}

// Seam point - add platform namespace & methods, follows open/closed principle.

namespace platform_plotter {

void draw_a_line(double x1, double y1, double x2, double y2) {
	cout << "    Draw plotter line: ["<<x1<<","<<y1<<"] ["<<x2<<","<<y2<<"]\n";
}
void draw_an_arc(double x1, double y1, double x2, double y2) {
	cout << "    Draw plotter arc: ("<<x1<<","<<y1<<") ("<<x2<<","<<y2<<")\n";;
}

}

}

namespace bridge_problem {

using namespace bridge_common::platform_vector;
using namespace bridge_common::platform_raster;

enum Platform {
	VECTOR,
	RASTER,
	// Seam point - insert another enumerated type, violates open/closed.
};

class Shape {
public: virtual ~Shape() { cout << " ~Shape\n"; }
	virtual void draw(Platform plat)=0;
};
class Rectangle : public Shape {
	double x1;
	double y1;
	double x2;
	double y2;
public:
	Rectangle(double x1, double y1, double x2, double y2)
		: x1(x1), y1(y1), x2(x2), y2(y2) {
	}
	~Rectangle() { cout << "  ~Rectangle"; }
public:
	void draw(Platform platform) {
		switch(platform) {
		case VECTOR:
			cout << "  Rectangle.draw(x1,y1, x2,y2)<vector>\n";
			drawLine(x1,y1, x2,y1);
			drawLine(x2,y1, x2,y2);
			drawLine(x2,y2, x1,y2);
			drawLine(x1,y2, x1,y1);
			break;
		case RASTER:
			cout << "  Rectangle.draw(x1,y1, x2,y2)<raster>\n";
			draw_line(x1,y1, x2,y1);
			draw_line(x2,y1, x2,y2);
			draw_line(x2,y2, x1,y2);
			draw_line(x1,y2, x1,y1);
			break;
		// Seam point - insert another platform, violates open/closed principle.
		default: cout << "  OOPS!\n"; break;
		}
	}
};
class Circle : public Shape {
	double x;
	double y;
	double r;
public:
	Circle(double x, double y, double radius)
		: x(x), y(y), r(radius) {
	}
	~Circle() { cout << "  ~Circle"; }
public:
	void draw(Platform platform) {
		switch(platform) {
		case VECTOR:
			cout << "  Circle.draw(x,y, radius)<vector>\n";
			drawArc(x,y+r, x+r,y);
			drawArc(x+r,y, x,y-r);
			drawArc(x,y-r, x-r,y);
			drawArc(x-r,y, x,y+r);
			break;
		case RASTER:
			cout << "  Circle.draw(x,y, radius)<raster>\n";
			draw_arc(x,y+r, x+r,y);
			draw_arc(x+r,y, x,y-r);
			draw_arc(x,y-r, x-r,y);
			draw_arc(x-r,y, x,y+r);
			break;
		// Seam point - insert another platform, violates open/closed principle.
		default: cout << "  OOPS!\n"; break;
		}
	}
};
// Seam point - add another shape, follows open/closed principle.

void clientCode(Shape* shape, Platform platform) { // Polymorphic use of shapes.
	shape->draw(platform);
}

void demo() {
	Shape*		shapes[] = { new Rectangle(1,1, 2,3), new Circle(4,4, 1.0) };
	Platform	platforms[] = { VECTOR, RASTER };
	for(size_t i=0; i<sizeof(shapes)/sizeof(*shapes); i++) {
		for(size_t j=0; j<sizeof(platforms)/sizeof(*platforms); j++) {
			clientCode(shapes[i], platforms[j]);
		}
	}

	for(size_t i=0; i<sizeof(shapes)/sizeof(*shapes); i++) {	// Cleanup.
		delete shapes[i];
	}

	cout << endl;
}

}

}

#endif /* BRIDGE_H_ */
