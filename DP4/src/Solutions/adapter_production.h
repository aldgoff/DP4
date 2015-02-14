/*
 * adapter_production.h
 *
 *  Created on: Feb 13, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_SOLUTIONS_ADAPTER_PRODUCTION_H_
#define DP4_SRC_SOLUTIONS_ADAPTER_PRODUCTION_H_


namespace adapter_solution_production {

using namespace home_grown;

class Polygon : public ShapeInterfaceDraw {	// New code.
	commercial::Polygon poly;
public:
	void draw() { poly.display(); }
};
class Torus : public ShapeInterfaceDraw {
	commercial::Torus torus;
public:
	void draw() { torus.display(); }
};
class Bezel : public ShapeInterfaceDraw {
	commercial::Bezel bezel;
public:
	void draw() { bezel.display(); }
};

void demo() {
	vector<ShapeInterfaceDraw*> shapes;	// Old client code stays the same.
	shapes.push_back(new Point);
	shapes.push_back(new Line);
	shapes.push_back(new Rect);
	shapes.push_back(new Polygon);		// Just add new code.
	shapes.push_back(new Torus);
	shapes.push_back(new Bezel);

	for(size_t i=0; i<shapes.size(); i++) {	// Client code stays simple because
		shapes[i]->draw();					// API's have been converged.
	}

	for(size_t i=0; i<shapes.size(); i++) {	// Release allocated memory.
		delete shapes[i];
	}

	cout << endl;
}

}


#endif /* DP4_SRC_SOLUTIONS_ADAPTER_PRODUCTION_H_ */
