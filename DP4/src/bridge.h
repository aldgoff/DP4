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

namespace lecture {

/* The client code needs different thread schedulers, such as
 *   preemptive, roundRobin, timeSliced, prioritized, etc.
 * but the implementations for each of these is platform dependent, that is
 *   Unix, Windows, OS10, iOS, JVM, etc.
 */

namespace bridge_legacy {

/* Initial requirements:
 *   Two kinds of thread schedulers:
 *     preemptive and round robin.
 *   Two kinds of platforms:
 *     Unix and Windows.
 */

enum Scheduler {
	PRE_EMPTIVE,
	ROUND_ROBIN,
	// Seam point - insert another enumerated type, violates open/closed.
};
enum Platform {
	UNIX,
	WINDOWS,
	// Seam point - insert another enumerated type, violates open/closed.
};

class Preemptive {
private:
	void runOnUnix() {
		cout << "  Preemptive thread scheduler running on Unix platform.\n";
	}
	void runOnWindows() {
		cout << "  Preemptive thread scheduler running on Windows platform.\n";
	}
	// Seam point - insert another method, violates open/closed.
public:
	void run(Platform plat) {
		switch(plat) {
		case UNIX: runOnUnix();	break;
		case WINDOWS: runOnWindows(); break;
		// Seam point - insert another case, violates open/closed.
		default: cout << "  OOPS!\n"; break;
		}
	}
};

class RoundRobin {
private:
	void runOnUnix() {
		cout << "  Round robin thread scheduler running on Unix platform.\n";
	}
	void runOnWindows() {
		cout << "  Round robin thread scheduler running on Windows platform.\n";
	}
	// Seam point - insert another method, violates open/closed.
public:
	void run(Platform plat) {
		switch(plat) {
		case UNIX: runOnUnix();	break;
		case WINDOWS: runOnWindows(); break;
		// Seam point - insert another case, violates open/closed.
		default: cout << "  OOPS!\n"; break;
		}
	}
};

void clientCode(Scheduler type, Platform plat) {
	switch(type) {
	case PRE_EMPTIVE:
		{
			Preemptive scheduler;
			scheduler.run(plat);
		}
		break;
	case ROUND_ROBIN:
		{
			RoundRobin scheduler;
			scheduler.run(plat);
		}
		break;
	// Seam point - insert another case, violates open/closed.
	default:
		cout << "  OOPS!\n";
		break;
	}
}

void demo() {
	cout << "  << legacy >>\n";
	Scheduler types[] = { PRE_EMPTIVE, ROUND_ROBIN };
	Platform plats[] = { UNIX, WINDOWS };
	for(size_t i=0; i<sizeof(types)/sizeof(*types); i++) {
		for(size_t j=0; j<sizeof(plats)/sizeof(*plats); j++) {
			clientCode(types[i], plats[j]);
		}
		cout << endl;
	}
}

}

namespace bridge_problem {

/* New requirements:
 *   Add two kinds of thread schedulers:
 *     time sliced and prioritized.
 *   Add three kinds of platforms:
 *     OS10, iOS and JVM.
 */

enum Scheduler {
	PRE_EMPTIVE,
	ROUND_ROBIN,
	// Seam point - insert another enumerated type, violates open/closed.
	TIME_SLICED,
	PRIORITIZED,
};
enum Platform {
	UNIX,
	WINDOWS,
	// Seam point - insert another enumerated type, violates open/closed.
	OS10,
	IOS,
	JVM,
};

class Preemptive {
private:
	void runOnUnix() {
		cout << "  Preemptive thread scheduler running on Unix platform.\n";
	}
	void runOnWindows() {
		cout << "  Preemptive thread scheduler running on Windows platform.\n";
	}
	// Seam point - insert another method, violates open/closed.
	void runOnOS10() {
		cout << "  Preemptive thread scheduler running on OS10 platform.\n";
	}
	void runOnIOS() {
		cout << "  Preemptive thread scheduler running on iOS platform.\n";
	}
	void runOnJVM() {
		cout << "  Preemptive thread scheduler running on JVM platform.\n";
	}
public:
	void run(Platform plat) {
		switch(plat) {
		case UNIX: runOnUnix();	break;
		case WINDOWS: runOnWindows(); break;
		// Seam point - insert another case, violates open/closed.
		case OS10: runOnOS10();	break;
		case IOS: runOnIOS();	break;
		case JVM: runOnJVM();	break;
		default: cout << "  OOPS!\n"; break;
		}
	}
};

class RoundRobin {
private:
	void runOnUnix() {
		cout << "  Round robin thread scheduler running on Unix platform.\n";
	}
	void runOnWindows() {
		cout << "  Round robin thread scheduler running on Windows platform.\n";
	}
	// Seam point - insert another method, violates open/closed.
	void runOnOS10() {
		cout << "  Round robin thread scheduler running on OS10 platform.\n";
	}
	void runOnIOS() {
		cout << "  Round robin thread scheduler running on iOS platform.\n";
	}
	void runOnJVM() {
		cout << "  Round robin thread scheduler running on JVM platform.\n";
	}
public:
	void run(Platform plat) {
		switch(plat) {
		case UNIX: runOnUnix();	break;
		case WINDOWS: runOnWindows(); break;
		// Seam point - insert another case, violates open/closed.
		case OS10: runOnOS10();	break;
		case IOS: runOnIOS();	break;
		case JVM: runOnJVM();	break;
		default: cout << "  OOPS!\n"; break;
		}
	}
};

class TimeSliced {
private:
	void runOnUnix() {
		cout << "  Time sliced thread scheduler running on Unix platform.\n";
	}
	void runOnWindows() {
		cout << "  Time sliced thread scheduler running on Windows platform.\n";
	}
	// Seam point - insert another method, violates open/closed.
	void runOnOS10() {
		cout << "  Time sliced thread scheduler running on OS10 platform.\n";
	}
	void runOnIOS() {
		cout << "  Time sliced thread scheduler running on iOS platform.\n";
	}
	void runOnJVM() {
		cout << "  Time sliced thread scheduler running on JVM platform.\n";
	}
public:
	void run(Platform plat) {
		switch(plat) {
		case UNIX: runOnUnix();	break;
		case WINDOWS: runOnWindows(); break;
		// Seam point - insert another case, violates open/closed.
		case OS10: runOnOS10();	break;
		case IOS: runOnIOS();	break;
		case JVM: runOnJVM();	break;
		default: cout << "  OOPS!\n"; break;
		}
	}
};

class Prioritized {
private:
	void runOnUnix() {
		cout << "  Prioritized thread scheduler running on Unix platform.\n";
	}
	void runOnWindows() {
		cout << "  Prioritized thread scheduler running on Windows platform.\n";
	}
	// Seam point - insert another method, violates open/closed.
	void runOnOS10() {
		cout << "  Prioritized thread scheduler running on OS10 platform.\n";
	}
	void runOnIOS() {
		cout << "  Prioritized thread scheduler running on iOS platform.\n";
	}
	void runOnJVM() {
		cout << "  Prioritized thread scheduler running on JVM platform.\n";
	}
public:
	void run(Platform plat) {
		switch(plat) {
		case UNIX: runOnUnix();	break;
		case WINDOWS: runOnWindows(); break;
		// Seam point - insert another case, violates open/closed.
		case OS10: runOnOS10();	break;
		case IOS: runOnIOS();	break;
		case JVM: runOnJVM();	break;
		default: cout << "  OOPS!\n"; break;
		}
	}
};

void clientCode(Scheduler type, Platform plat) {
	switch(type) {
	case PRE_EMPTIVE:
		{
			Preemptive scheduler;
			scheduler.run(plat);
		}
		break;
	case ROUND_ROBIN:
		{
			RoundRobin scheduler;
			scheduler.run(plat);
		}
		break;
	// Seam point - insert another case, violates open/closed.
	case TIME_SLICED:
		{
			TimeSliced scheduler;
			scheduler.run(plat);
		}
		break;
	case PRIORITIZED:
		{
			Prioritized scheduler;
			scheduler.run(plat);
		}
		break;
	default:
		cout << "  OOPS!\n";
		break;
	}
}

void demo() {
	cout << "  << problem >>\n";
	Scheduler types[] = { PRE_EMPTIVE, ROUND_ROBIN, TIME_SLICED, PRIORITIZED };
	Platform plats[] = { UNIX, WINDOWS, OS10, IOS, JVM };
	for(size_t i=0; i<sizeof(types)/sizeof(*types); i++) {
		for(size_t j=0; j<sizeof(plats)/sizeof(*plats); j++) {
			clientCode(types[i], plats[j]);
		}
		cout << endl;
	}
}

}

namespace bridge_combinatorial_explosion {	// OOP is no help.

class ThreadScheduler {	// Subclasses scale quadratically.
public: virtual ~ThreadScheduler() { cout << " ~ThreadScheduler\n"; }
public:
	virtual void run() { cout << "  run().\n"; }
};

class TSPreEmptiveUnix : public ThreadScheduler {
public: ~TSPreEmptiveUnix() { cout << "  ~TSPreEmptiveUnix"; }
	void run() {
		cout << "  Preemptive thread scheduler running on Unix platform.\n";
	}
};
class TSPreEmptiveWindows : public ThreadScheduler {
public: ~TSPreEmptiveWindows() { cout << "  ~TSPreEmptiveWindows"; }
	void run() {
		cout << "  Preemptive thread scheduler running on Windows platform.\n";
	}
};
// ... OS10, iOS
class TSPreEmptiveJVM : public ThreadScheduler {
public: ~TSPreEmptiveJVM() { cout << "  ~TSPreEmptiveJVM"; }
	void run() {
		cout << "  Preemptive thread scheduler running on JVM platform.\n";
	}
};

class TSRoundRobinUnix : public ThreadScheduler {
public: ~TSRoundRobinUnix() { cout << "  ~TSRoundRobinUnix"; }
	void run() {
		cout << "  RoundRobin thread scheduler running on Unix platform.\n";
	}
};
class TSRoundRobinWindows : public ThreadScheduler {
public: ~TSRoundRobinWindows() { cout << "  ~TSRoundRobinWindows"; }
	void run() {
		cout << "  RoundRobin thread scheduler running on Windows platform.\n";
	}
};
// ... OS10, iOS
class TSRoundRobinJVM : public ThreadScheduler {
public: ~TSRoundRobinJVM() { cout << "  ~TSRoundRobinJVM"; }
	void run() {
		cout << "  RoundRobin thread scheduler running on JVM platform.\n";
	}
};

class TSTimeSlicedUnix : public ThreadScheduler {
public: ~TSTimeSlicedUnix() { cout << "  ~TSTimeSlicedUnix"; }
	void run() {
		cout << "  TimeSliced thread scheduler running on Unix platform.\n";
	}
};
class TSTimeSlicedWindows : public ThreadScheduler {
public: ~TSTimeSlicedWindows() { cout << "  ~TSTimeSlicedWindows"; }
	void run() {
		cout << "  TimeSliced thread scheduler running on Windows platform.\n";
	}
};
// ... OS10, iOS
class TSTimeSlicedJVM : public ThreadScheduler {
public: ~TSTimeSlicedJVM() { cout << "  ~TSTimeSlicedJVM"; }
	void run() {
		cout << "  TimeSliced thread scheduler running on JVM platform.\n";
	}
};

// ... Prioritized
// ... Unix, Windows, OS10, iOS, JVM.

void demo() {
	cout << "  << combinatorial explosion >>\n";
	ThreadScheduler* threads[] = {
		new TSPreEmptiveUnix, new TSPreEmptiveWindows, new TSPreEmptiveJVM,
		new TSRoundRobinUnix, new TSRoundRobinWindows, new TSRoundRobinJVM,
		new TSTimeSlicedUnix, new TSTimeSlicedWindows, new TSTimeSlicedJVM,
	};
	for(size_t i=0; i<sizeof(threads)/sizeof(*threads); i++) {
		threads[i]->run();
	}
	cout << endl;

	for(size_t i=0; i<sizeof(threads)/sizeof(*threads); i++) {	// Dtors.
		delete threads[i];
	}
	cout << endl;
}

}

namespace bridge_solution {

class Platform {	// Implementation.
public: virtual ~Platform() { cout << " ~Platform"; }
public:
	virtual void run() { cout << "  Derived class needs to override this.\n"; }
};
class Unix : public Platform {
public: ~Unix() { cout << " ~Unix"; }
public:
	void run() { cout << " Unix platform.\n"; }
};
class Windows : public Platform {
public: ~Windows() { cout << " ~Windows"; }
	void run() { cout << " Windows platform.\n"; }
};
class OS10 : public Platform {
public: ~OS10() { cout << " ~OS10"; }
	void run() { cout << " OS10 platform.\n"; }
};
class iOS : public Platform {
public: ~iOS() { cout << " ~iOS"; }
	void run() { cout << " iOS platform.\n"; }
};
class JVM : public Platform {
public: ~JVM() { cout << " ~JVM"; }
	void run() { cout << " JVM platform.\n"; }
};

class ThreadScheduler {	// Abstraction.
public:
	Platform* platform;
public:
	ThreadScheduler() : platform(0) {}
	virtual ~ThreadScheduler() {
		if(platform) delete platform;
		cout << " ~ThreadScheduler\n";
	}
public:
	virtual void run() { platform->run(); }
};
class Preemptive : public ThreadScheduler {
public: ~Preemptive() { cout << "  ~Preemptive"; }
public:
	void run() {
		cout << "  Preemptive thread scheduler running on";
		platform->run(); }
};
class RoundRobin : public ThreadScheduler {
public: ~RoundRobin() { cout << "  ~RoundRobin"; }
public:
	virtual void run() {
		cout << "  RoundRobin thread scheduler running on";
		platform->run(); }
};
class TimeSliced : public ThreadScheduler {
public: ~TimeSliced() { cout << "  ~TimeSliced"; }
public:
	virtual void run() {
		cout << "  TimeSliced thread scheduler running on";
		platform->run(); }
};
class Prioritized : public ThreadScheduler {
public: ~Prioritized() { cout << "  ~Prioritized"; }
public:
	virtual void run() {
		cout << "  Prioritized thread scheduler running on";
		platform->run(); }
};

void clientCode(ThreadScheduler* scheduler) {
	scheduler->run();
}

void demo() {
	cout << "  << solution >>\n";
	ThreadScheduler* threads[4][5] = {{0},{0},{0},{0}};

	for(size_t i=0; i<4; i++) {
		Platform* platforms[] = {
			new Unix, new Windows, new OS10, new iOS, new JVM
		};
		for(size_t j=0; j<sizeof(platforms)/sizeof(*platforms); j++) {
			switch(i) {
			case 0: threads[i][j] = new Preemptive;	 break;
			case 1: threads[i][j] = new RoundRobin;	 break;
			case 2: threads[i][j] = new TimeSliced;	 break;
			case 3: threads[i][j] = new Prioritized; break;
			}
			threads[i][j]->platform = platforms[j];
			clientCode(threads[i][j]);
		}
		cout << endl;
	}

	for(size_t i=0; i<4; i++) {		// Call dtors.
		for(size_t j=0; j<5; j++) {
			delete threads[i][j];
		}
	}
	cout << endl;
}

}

}

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

namespace bridge_legacy {	// Obsolete.

/* Initial requirements:
 *   Two kinds of shapes:
 *     rectangles and circles.
 *   Two kinds of platforms:
 *     Vector and raster.
 */

enum Shapes {
	RECTANGLE,
	CIRCLE,
	// Seam point - insert another enumerated type, violates open/closed.
};
enum Platform {
	VECTOR,
	RASTER,
	// Seam point - insert another enumerated type, violates open/closed.
};

void clientCode(Shapes type, Platform plat) {
	switch(type) {
	case RECTANGLE:
		switch(plat) {
		case VECTOR:
			break;
		case RASTER:
			break;
		default: cout << "  OOPS!\n"; break;
		}
		break;
	case CIRCLE:
		switch(plat) {
		case VECTOR:
			break;
		case RASTER:
			break;
		default: cout << "  OOPS!\n"; break;
		}
		break;
	// Seam point - insert another case, violates open/closed.
	default: cout << "  OOPS!\n"; break;
	}
}

void demo() {
	cout << endl;
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

namespace bridge_solution {

using namespace bridge_common::platform_vector;
using namespace bridge_common::platform_raster;
using namespace bridge_common::platform_plotter;

class Platform {
public: virtual ~Platform() { cout << " ~Platform\n"; }
	virtual void line(double x1, double y1, double x2, double y2)=0;
	virtual void arc(double x1, double y1, double x2, double y2)=0;
};
class Vector : public Platform {
public: ~Vector() { cout << "  ~Vector"; }
public:
	void line(double x1, double y1, double x2, double y2) {
		drawLine(x1,y1, x2,y1);
	}
	void arc(double x1, double y1, double x2, double y2) {
		drawArc(x1,y1, x2,y1);
	}
};
class Raster : public Platform {
public: ~Raster() { cout << "  ~Raster"; }
public:
	void line(double x1, double y1, double x2, double y2) {
		draw_line(x1,y1, x2,y1);
	}
	void arc(double x1, double y1, double x2, double y2) {
		draw_arc(x1,y1, x2,y1);
	}
};
class Plotter : public Platform {
public: ~Plotter() { cout << "  ~Plotter"; }
public:
	void line(double x1, double y1, double x2, double y2) {
		draw_a_line(x1,y1, x2,y1);
	}
	void arc(double x1, double y1, double x2, double y2) {
		draw_an_arc(x1,y1, x2,y1);
	}
};
// Seam point - add another platform, follows open/closed principle.

class Shape {
protected:
	Platform* platform;
public:
	virtual ~Shape() { cout << " ~Shape\n"; }
	void setPlatform(Platform* platform) { this->platform = platform; }
	virtual void draw()=0;
};
class Rectangle : public Shape {
	double x1;
	double y1;
	double x2;
	double y2;
public:
	Rectangle(double x1, double y1, double x2, double y2)
		: x1(x1), y1(y1), x2(x2), y2(y2)
	{}
	~Rectangle() { cout << "  ~Rectangle"; }
public:
	void draw() {
		cout << "  Rectangle.draw(x1,y1, x2,y2)<platform>\n";
		platform->line(x1,y1, x2,y1);
		platform->line(x2,y1, x2,y2);
		platform->line(x2,y2, x1,y2);
		platform->line(x1,y2, x1,y1);
	}
};
class Circle : public Shape {
	double x;
	double y;
	double r;
public:
	Circle(double x, double y, double radius)
		: x(x), y(y), r(radius)
	{}
	~Circle() { cout << "  ~Circle"; }
public:
	void draw() {
		cout << "  Circle.draw(x,y, radius)<platform>\n";
		platform->arc(x,y+r, x+r,y);
		platform->arc(x+r,y, x,y-r);
		platform->arc(x,y-r, x-r,y);
		platform->arc(x-r,y, x,y+r);
	}
};
// Seam point - add another shape, follows open/closed principle.

void clientCode(Shape* shape) {	// Only has to know Shape, not even Platform.
	shape->draw();
}

void demo() {
	Shape*		shapes[] = { new Rectangle(1,1, 2,3), new Circle(4,4, 1.0) };
	Platform*	platforms[] = { new Vector, new Raster, new Plotter };
	for(size_t i=0; i<sizeof(shapes)/sizeof(*shapes); i++) {
		for(size_t j=0; j<sizeof(platforms)/sizeof(*platforms); j++) {
			shapes[i]->setPlatform(platforms[j]);
			clientCode(shapes[i]);
		}
	}

	for(size_t i=0; i<sizeof(shapes)/sizeof(*shapes); i++) {	// Cleanup.
		delete shapes[i];
	}
	for(size_t j=0; j<sizeof(platforms)/sizeof(*platforms); j++) {	// Cleanup.
		delete platforms[j];
	}

	cout << endl;
}

}

}

namespace wikibooks_cpp_pcdp {	// Obsolete.

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

namespace problem_scenario1 {	// Obsolete.

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

namespace problem_scenario {	// Obsolete.

/* Each of 3 graphics platforms supplies two 2D drawing primitives,
   lines and arcs, implemented as functions.
   They can be used to create a variety of shapes, such as rectangles, circles,
   rounded rectangles, etc.

   Use the bridge pattern to write code that avoids the combinatorial explosion
   of classes and methods which a procedural approach entails.
   Show how adding another shape or platform requires only a linear amount of
   additional code.

   For extra credit, abstract the coordinate system to cover both Cartesian and
   polar coordinates <math.h>.

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

namespace bridge {	// Obsolete.

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
		// Line algorithm: draw(x1,y1, x2,y2);
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
