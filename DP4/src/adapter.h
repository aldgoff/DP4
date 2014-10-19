/*
 * adapter.h
 *
 * Desc: Adapt interfaces so classes can work together polymorphically.
 *
 *  Created on: Mar 8, 2014
 *      Author: aldgoff
 *
 *  URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Adapter
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

/* Consider the case where an installed and heavily used class hierarchy
 * for simple shapes needs to be extended by incorporating a commercial
 * class hierarchy containing more complex shapes.
 * The problem is that the two class hierarchies use different API's.
 * The original one uses the function "draw()" the other the function "display()".
 * This breaks the polymorphism that kept the user code simple.
 * User code will become more complicated, likely will become littered with
 * if statements of the sort "what type are you?".
 * Solve this problem by writing new classes that 'adapt' the new interface
 * to the old.
 */

class ShapeInterfaceDraw {					// Interface class (home grown?).
public:
	virtual void draw()=0;
	virtual ~ShapeInterfaceDraw() {}
};
class Point : public ShapeInterfaceDraw {
public:
	void draw() { cout << "Draw point.\n";}
};
class Line : public ShapeInterfaceDraw {
public:
	void draw() { cout << "Draw line.\n"; }
};
class Rect : public ShapeInterfaceDraw {
public:
	void draw() { cout << "Draw rectangle.\n"; }
};

namespace convoluted {

class ShapeInterfaceDisplay {				// Another interface class (commercial?).
public:
	virtual void display()=0;
	virtual ~ShapeInterfaceDisplay() {}
};
class Polygon : public ShapeInterfaceDisplay {
public:
	void display() { cout << "Display polygon.\n";}
};
class Torus : public ShapeInterfaceDisplay {
public:
	void display() { cout << "Display torus.\n";}
};
class Bezel : public ShapeInterfaceDisplay {
public:
	void display() { cout << "Display bezel.\n";}
};

}

namespace adapter_problem {

void demo() {
	cout << "<< Adapter problem >>\n";

	vector<ShapeInterfaceDraw*> shapes;
	shapes.push_back(new Point);
	shapes.push_back(new Line);
	shapes.push_back(new Rect);

	vector<convoluted::ShapeInterfaceDisplay*> shapesC;
	shapesC.push_back(new convoluted::Polygon);
	shapesC.push_back(new convoluted::Torus);
	shapesC.push_back(new convoluted::Bezel);

	for(size_t i=0; i<shapes.size(); i++) {		// User code more complicated because API's differ.
		shapes[i]->draw();
	}

	for(size_t i=0; i<shapesC.size(); i++) {	// Likely result is a lot of if statements "what type are you?"
		shapesC[i]->display();
	}

	cout << endl;
}

}

namespace adapter_solution {

class Polygon : public ShapeInterfaceDraw {
	convoluted::Polygon poly;
public:
	void draw() { poly.display(); }
};
class Torus : public ShapeInterfaceDraw {
	convoluted::Torus torus;
public:
	void draw() { torus.display(); }
};
class Bezel : public ShapeInterfaceDraw {
	convoluted::Bezel bezel;
public:
	void draw() { bezel.display(); }
};

void demo() {
	cout << "<< Adapter solution >>\n";

	vector<ShapeInterfaceDraw*> shapes;
	shapes.push_back(new Point);
	shapes.push_back(new Line);
	shapes.push_back(new Rect);
	shapes.push_back(new Polygon);
	shapes.push_back(new Torus);
	shapes.push_back(new Bezel);

	for(size_t i=0; i<shapes.size(); i++) {	// User code stays simple because API's have been converged.
		shapes[i]->draw();
	}

	cout << endl;
}

}

#endif /* ADAPTER_H_ */
