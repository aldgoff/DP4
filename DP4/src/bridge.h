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
 *  URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Bridge
 */

#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <math.h>

namespace wikibooks_cpp_pcdp {

class DrawingAPI {
public:
	virtual void drawCircle(double x, double y, double radius)=0;
	virtual ~DrawingAPI() {}
};
class DrawingAPI1 : public DrawingAPI {
	void drawCircle(double x, double y, double radius) {
		cout << "API1.circle of " << radius << " at " << x << ":" << y << endl;
	}
};
class DrawingAPI2 : public DrawingAPI {
	void drawCircle(double x, double y, double radius) {
		cout << "API2.circle of " << radius << " at " << x << ":" << y << endl;
	}
};
// Seam point, yet another implementation.

class Shape {
public:
	virtual ~Shape() {}
	virtual void draw()=0;
	virtual void resizeByPercentage(double percent)=0;
};

class Circle : public Shape {
private:
	double 		x, y, r;
	DrawingAPI*	drawingAPI;
public:
	Circle(double x, double y, double r, DrawingAPI* drawingAPI)
		: x(x), y(y), r(r), drawingAPI(drawingAPI) {}
	void draw() {
		drawingAPI->drawCircle(x,y,r);
	};
	void resizeByPercentage(double percent) {
		r *= (1 + percent/100);
	}
};
// Seam point, add another shape.

void demo_bridge() {
	Circle circle1(1,2,3, new DrawingAPI1());
	Circle circle2(4,5,6, new DrawingAPI2());
	circle1.draw();
	circle2.draw();
	circle1.resizeByPercentage(10);
	circle2.resizeByPercentage(10);
	circle1.draw();
	circle2.draw();

	 cout << endl;
}

}

namespace problem_scenario1 {

// Have a graphics package that draws basic shapes.
// Currently runs on 3 platforms: high res, plotter, and a low power portable, but will eventually need to run on wearables.
// Currently draws lines, circles and rectangles, but will need to draw other shapes, like triangles.

class LineHiRes {
	void draw() { cout << "Line Hi Res" << endl; }
};
class CircleHiRes {
	void draw() { cout << "Circle Hi Res" << endl; }
};
class RectHiRes {
	void draw() { cout << "Rect Hi Res" << endl; }
};
// Seam point; other shapes.

class LinePlotter {
	void draw() { cout << "Line Plotter" << endl; }
};
class CirclePlotter {
	void draw() { cout << "Circle Plotter" << endl; }
};
class RectPlotter {
	void draw() { cout << "Rect Plotter" << endl; }
};
// Seam point; other shapes.

class LinePortable {
	void draw() { cout << "Line Portable" << endl; }
};
class CirclePortable {
	void draw() { cout << "Circle Portable" << endl; }
};
class RectPortable {
	void draw() { cout << "Rect Portable" << endl; }
};
// Seam point; other shapes.

// Seam point; other platforms

}

namespace problem_scenario {

/* Each of 3 graphics platforms supplies two 2D drawing primitives, lines and arcs, implemented as functions.
   They can be used to create a variety of shapes, such as rectangles, circles, rounded rectangles, etc.

   Use the bridge pattern to write code that avoids the combinatorial explosion of classes
   and methods which a procedural approach to the problem would entail.
   Show how adding another shape or another platform requires only a linear amount of additional code.

   For extra credit, abstract the coordinate system to cover both Cartesian and polar coordinates <math.h>.

   Below are the 3 pairs of function primitives available for the platforms and
   the equations showing how to use them to draw rectangles and circles.
   It is straight forward to use the primitives to draw
   other shapes such as triangles and rounded rectangles.
   Note, they just print text to the screen, this is an academic exercise.
*/

void drawLine(double x1, double y1, double x2, double y2) {
	cout << "Draw vector line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << endl;
}
void drawArc(double x1, double y1, double x2, double y2) {
	cout << "Draw vector arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << endl;
}

void draw_line(double x1, double y1, double x2, double y2) {
	cout << "Draw raster line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << endl;
}
void draw_arc(double x1, double y1, double x2, double y2) {
	cout << "Draw raster arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << endl;
}

void draw_a_line(double x1, double y1, double x2, double y2) {
	cout << "Draw plotter line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << endl;
}
void draw_an_arc(double x1, double y1, double x2, double y2) {
	cout << "Draw plotter arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << endl;
}

// Rectangle, draw 4 lines (upper left corner is x1,y1, lower right corner is x2,y2).
//	 draw(x1,y1, x2,y1); draw(x2,y1, x2,y2); draw(x2,y2, x1,y2); draw(x1,y2, x1,y1);
// Circle, draw 4 arcs (90 degrees, clockwise, center is x,y).
//	 draw(x,y+r, x+r,y); draw(x+r,y, x,y-r); draw(x,y-r, x-r,y); draw(x-r,y, x,y+r);

}

namespace bridge {

class CoordSystem {	// Implementation dimension 2.
public:
	virtual ~CoordSystem() {}
	virtual double x()=0;
	virtual double y()=0;
};
class Cartesian : public CoordSystem {
	double	X;
	double	Y;
public:
	Cartesian(double x=0.0, double y=0.0) :X(x), Y(y) {}
	double x() { return X; }
	double y() { return Y; }
};
class Polar : public CoordSystem {
	double	r;
	double	theta;
public:
	Polar(double r=0.0, double theta=0.0) : r(r), theta(theta) {}
	double x() { return r*cos(theta); }
	double y() { return r*sin(theta); }
};
// Seam point, add another coordinate system.

class Platform {	// Implementation dimension 1.
public:
	virtual ~Platform() {}
	virtual void line(double x1, double y1, double x2, double y2)=0;
	virtual void arc(double x1, double y1, double x2, double y2)=0;
};
class Vector : public Platform {
public:
	void line(double x1, double y1, double x2, double y2) {
		problem_scenario::drawLine(x1,y1, x2,y2);
	}
	void arc(double x1, double y1, double x2, double y2) {
		problem_scenario::drawArc(x1,y1, x2,y2);
	}
};
class Rastor : public Platform {
public:
	void line(double x1, double y1, double x2, double y2) {
		problem_scenario::draw_line(x1,y1, x2,y2);
	}
	void arc(double x1, double y1, double x2, double y2) {
		problem_scenario::draw_arc(x1,y1, x2,y2);
	}
};
class Plotter : public Platform {
public:
	void line(double x1, double y1, double x2, double y2) {
		problem_scenario::draw_a_line(x1,y1, x2,y2);
	}
	void arc(double x1, double y1, double x2, double y2) {
		problem_scenario::draw_an_arc(x1,y1, x2,y2);
	}
};
// Seam point, add another platform.

class Shape {		// Abstraction.
protected:
	CoordSystem* loc;
	Platform*	 platform;
public:
	Shape(CoordSystem* pos, Platform* platform) : loc(pos), platform(platform) {}
	virtual ~Shape() {}
	virtual void draw()=0;
};
class Line : public Shape {
	CoordSystem* end;
public:
	Line(CoordSystem* beg, CoordSystem* end, Platform* platform) : Shape(beg, platform), end(end) {}
	void draw() {
		platform->line(loc->x(),loc->y(), end->x(),end->y());
	}
};
class Rect : public Shape {
	CoordSystem* end;
public:
	Rect(CoordSystem* beg, CoordSystem* end, Platform* platform) : Shape(beg, platform), end(end) {}
	void draw() {
		// Rectangle algorithm: draw(x1,y1, x2,y1); draw(x2,y1, x2,y2); draw(x2,y2, x1,y2); draw(x1,y2, x1,y1);
		double x1 = loc->x();
		double y1 = loc->y();
		double x2 = end->x();
		double y2 = end->y();
		platform->line(x1,y1, x2,y1);
		platform->line(x2,y1, x2,y2);
		platform->line(x2,y2, x1,y2);
		platform->line(x1,y2, x1,y1);
	}
};
class Circle : public Shape {
	double r;
public:
	Circle(CoordSystem* loc, double r, Platform* platform) : Shape(loc, platform), r(r) {}
	void draw() {
		// Circle algorithm: draw(x,y+r, x+r,y); draw(x+r,y, x,y-r); draw(x,y-r, x-r,y); draw(x-r,y, x,y+r);
		double x = loc->x();
		double y = loc->y();
		platform->arc(x,y+r, x+r,y);
		platform->arc(x+r,y, x,y-r);
		platform->arc(x,y-r, x-r,y);
		platform->arc(x-r,y, x,y+r);
	}
};
// Seam point, add another shape.

void demo() {
	Line	line(new Cartesian(1,2), new Cartesian(3,4), new Vector());		line.draw();	cout << endl;
	Rect	rect(new Cartesian(1,2), new Polar(3,4),     new Rastor());		rect.draw();	cout << endl;
	Circle	circle(new Polar(1,2), 20.0,				 new Plotter());	circle.draw();	cout << endl;

	cout << "-------------------------------------------------\n" << endl;

	Shape* shapes[] = {
		new Line(new Cartesian(1,2), new Cartesian(3,4), new Vector()),
		new Rect(new Cartesian(1,2), new Polar(3,4), new Rastor()),
		new Circle(new Polar(1,2), 20.0, new Plotter())
	};

	for(size_t i=0; i<sizeof(shapes)/sizeof(Shape*); i++) {
		shapes[i]->draw();
		cout << endl;
	}
}

}

#endif /* BRIDGE_H_ */
