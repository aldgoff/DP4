/*
 * adapter_production.h
 *
 *  Created on: Feb 13, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_PROBLEMS_ADAPTER_PRODUCTION_H_
#define DP4_SRC_PROBLEMS_ADAPTER_PRODUCTION_H_


namespace adapter_problem_production {

using namespace home_grown;
using namespace commercial;

struct Shapes {
	ShapeInterfaceDraw*	draw;
	commercial::ShapeInterfaceDisplay*	display;
	Shapes(
		ShapeInterfaceDraw* draw=0)
		: draw(draw), display(0) {}
	Shapes(
		commercial::ShapeInterfaceDisplay* display=0)
		: draw(0), display(display) {}
	virtual ~Shapes() {
		cout << "  Shapes dtor -";
		delete draw;
		delete display;
	}
};

void demo() {
	vector<Shapes*>	shapes;					// Changes to existing code.
	shapes.push_back(new Shapes(new Point));
	shapes.push_back(new Shapes(new Line));
	shapes.push_back(new Shapes(new Rect));
	shapes.push_back(new Shapes(new Polygon));
	shapes.push_back(new Shapes(new Torus));
	shapes.push_back(new Shapes(new Bezel));

	for(size_t i=0; i<shapes.size(); i++) {	// Client code more complicated
		if(shapes[i]->draw)					// because API's differ
			shapes[i]->draw->draw();		// requiring if-else statements,
		else if(shapes[i]->display)			// changes to existing client code,
			shapes[i]->display->display();
		else {
			throw "unknown shape object.";	// and worse; error detection.
		}
	}

	for(size_t i=0; i<shapes.size(); i++) {	// Release allocated memory.
		delete shapes[i];
	}

	cout << endl;
}

}


#endif /* DP4_SRC_PROBLEMS_ADAPTER_PRODUCTION_H_ */
