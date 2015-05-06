/*
 * jason.h
 *
 *  Created on: May 5, 2015
 *      Author: aldgoff
 *
 *  Project: Intro to Design Patterns Pilot class.
 */

#ifndef DP4_SRC_STUDENTS_JASON_H_
#define DP4_SRC_STUDENTS_JASON_H_
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

namespace final_jason_file {

const bool on = false;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }

namespace legacy_classes {	// Can't change these.

class CleanABS {
public: ~CleanABS() { DTOR("~CleanABS "); }
	void clean() {
		cout << "    Clean ABS mold: soak in alcohol, rinse with water, dry.\n";
	}
};

class CleanPolys {
public: ~CleanPolys() { DTOR("~CleanPolys "); }
	void prepForReuse() {
		cout << "    Clean Poly mold: rinse with acetone, dry.\n";
	}
};

class PETCleanup {
public: ~PETCleanup() { DTOR("~PETCleanup "); }
	void carbonize() { // Use only on stainless steel.
		cout << "    Clean PET steel mold: heat to 895 C.\n";
	}
	void purify() {	// Use only on aluminum.
		cout << "    Clean PET aluminum mold: rinse with soap and water, dry.\n";
	}
};

class SynthCleanup {
public: ~SynthCleanup() { DTOR("~SynthCleanup "); }
	void ozone() {
		cout << "    Clean synthetic mold: ozone wash.\n";
	}
};

}

namespace factory_method
{	// DP 5.
	class injection_line
	{
	protected:
		injection_line * next;
		int threshhold;
		string metal;
		string metal_lc;
		string conveyer;
		string output;
		string machine;
		int cavities;
		int num_orders;
		string pack;
		bool steel;
		bool satin;
		string stuffer;

	public:
		injection_line(){next = 0;threshhold = 0;}
		injection_line(int num)
		{
			next = 0;threshhold = 0;
		}

		injection_line* setup(int num, string packager, string s)
		{
			if(num > threshhold && next)
				return next->setup(num, packager, s);
			else
			{
				num_orders = num;
				pack = packager;
				stuffer = s;
				cout << "  Setup injection line for " << get_num() << " run with " << packager << " packager and " << get_stuff_lc() << " stuffing:\n";
				cout << "    " << machine << " - " << metal << "(" << cavities << ")" << " - " << conveyer << " conveyer belt - " << output << "\n";
				return this;
			}
		}
		void setNext(injection_line *n)
		{
			next = n;
		}
		int get_cavities()
		{
			return cavities;
		}
		int get_num()
		{
			return num_orders/cavities;
		}
		string get_packager()
		{
			return pack;
		}
		string get_output()
		{
			return output;
		}
		bool is_steel()
		{
			return steel;
		}
		bool is_satin()
		{
			return satin;
		}
		string get_metal()
		{
			return metal;
		}
		string get_metal_lc()
		{
			string tmp = metal;
			for (std::string::size_type i=0; i<metal.length(); ++i)
				tmp[i] = tolower(metal[i]);
			return tmp;
		}
		string get_stuff_lc()
		{
			string tmp = stuffer;
			for (std::string::size_type i=0; i<stuffer.length(); ++i)
				tmp[i] = tolower(stuffer[i]);
			if(!tmp.compare("popcorn"))
				return "styrene popcorn";
			if(!tmp.compare("bubblewrap"))
				return "bubble wrap";
			if(!tmp.compare("foam"))
				return "expanding foam";
			return tmp;
		}
	};
	class ijm_110 : public injection_line
	{
	public:
		ijm_110(int thresh)
		{
			threshhold = thresh;
			cavities = 1;
			metal = "Aluminum";
			machine = "IJM_110";
			conveyer = "Linear";
			output = "CardboardBox";
			steel = 0;
			satin = 0;
		}
	};
	class ijm_120 : public injection_line
	{
	public:
		ijm_120(int thresh)
		{
			threshhold = thresh;
			cavities = 2;
			metal = "Aluminum";
			machine = "IJM_120";
			conveyer = "Y-Split";
			output = "CardboardBox";
			steel = 0;
			satin = 0;
		}
	};
	class ijm_140 : public injection_line
	{
	public:
		ijm_140(int thresh)
		{
			threshhold = thresh;
			cavities = 4;
			metal = "Aluminum";
			machine = "IJM_140";
			conveyer = "V-Level";
			output = "PallotBox";
			steel = 0;
			satin = 0;
		}
	};
	class ijm_210 : public injection_line
	{
	public:
		ijm_210(int thresh)
		{
			threshhold = thresh;
			cavities = 1;
			metal = "Steel";
			machine = "IJM_210";
			conveyer = "Linear";
			output = "PallotBox";
			steel = 1;
			satin = 0;
		}
	};
	class ijm_220 : public injection_line
	{
	public:
		ijm_220(int thresh)
		{
			threshhold = thresh;
			cavities = 2;
			metal = "Steel";
			machine = "IJM_220";
			conveyer = "Y-Split";
			output = "Crate";
			steel = 1;
			satin = 0;
		}
	};
	class ijm_240 : public injection_line
	{
	public:
		ijm_240(int thresh)
		{
			threshhold = thresh;
			cavities = 4;
			metal = "Steel";
			machine = "IJM_240";
			conveyer = "V-Level";
			output = "Crate";
			steel = 0;
			satin = 1;
		}
	};

	class locate
	{
	protected:
		locate * next;
		string location;
		int cavities;
		string shape;
		string finish;

	public:
		locate(){next = 0;}

		virtual locate * setup(string location, string shape, injection_line * line, string f) = 0;

		void setNext(locate *n)
		{
			next = n;
		}
		string get_shape()
		{
			return shape;
		}
	};
	class mill : public locate
	{
		string l;
	public:
		mill(){l = "mill";}

		locate * setup(string location, string s, injection_line * line, string f)
		{
			if(location.compare(l))
				return next->setup(location, s, line, f);
			else
			{
				shape = s;
				finish = f;
				cout << "    Create " << s << " mold from mill with " << line->get_cavities() << " cavities:\n";
				if(!line->is_steel() && !line->is_satin())
					cout << "      using HighCarbon tools (drill, cut, and high speed grind) to mill " << line->get_metal_lc() << " block into " << line->get_cavities() << " " << shape << " shapes with " << finish << " finish.\n";
				else if(line->is_steel())
					cout << "      using Carbide tools (high speed drill, cross cut, and layer grind) to mill " << line->get_metal_lc() << " block into " << line->get_cavities() << " " << shape << " shapes with " << finish << " finish.\n";
				else
					cout << "      using DiamondTipped tools (precision drill, oil cooled cut, and cartoid grind) to mill " << line->get_metal_lc() << " block into " << line->get_cavities() << " " << shape << " shapes with " << finish << " finish.\n";

				return this;
			}
		}
	};
	class sister : public locate
	{
		string l;
	public:
		sister(){l = "sisterCompany";}

		locate * setup(string location, string s, injection_line * line, string f)
		{
			if(location.compare(l))
				return next->setup(location, s, line, f);
			else
			{
				shape = s;
				finish = f;
				cout << "    Borrow " << s << " mold from sister company.\n";

				return this;
			}
		}
	};
	class purchase : public locate
	{
		string l;
	public:
		purchase(){l = "purchase";}

		locate * setup(string location, string s, injection_line * line, string f)
		{
			if(location.compare(l))
				return next->setup(location, s, line, f);
			else
			{
				shape = s;
				finish = f;
				cout << "    Acquire " << s << " mold via purchase.\n";

				return this;
			}
		}
	};
	class inventory : public locate
	{
		string l;
	public:
		inventory(){l = "inventory";}

		locate * setup(string location, string s, injection_line * line, string f)
		{
			if(location.compare(l))
			{
				cout << "    <>Can't find place |" << location << "| to get |" << s << "| mold from, defaulting to duck from inventory.\n";
				shape = "duck";
				location = "Inventory";
			}else
			{
				cout << "    Pull " << s << " mold from inventory.\n";
				shape = s;
				finish = f;
			}
			return this;
		}
	};

	class plastic_class
	{
	protected:
		int heat_temp;
		int inject_psi;
		int cool_temp;
		string plastic;
		string technique;
		plastic_class * next;

	public:
		plastic_class(){next = 0;}

		virtual plastic_class * setup(string p) = 0;
		virtual void clean(bool steel) = 0;
		virtual string get_name() = 0;

		void print_injection_cycle()
		{
			cout << "      Close - heat to "<< heat_temp <<" - inject at " << inject_psi << " PSI - cool to " << cool_temp << " - separate - " << technique << " eject.\n";
		}
		void setNext(plastic_class *n)
		{
			next = n;
		}
	};
	class ABS : public plastic_class
	{
		string l;
		legacy_classes::CleanABS *cl;
	public:
		ABS(){l = "ABS";next = 0;heat_temp = 440;inject_psi = 125;cool_temp = 360;technique = "progressive";cl = new legacy_classes::CleanABS();}
		~ABS(){delete cl;}

		plastic_class * setup(string p)
		{
			if(l.compare(p))
				return next->setup(p);
			else
			{
				plastic = p;
				return this;
			}
		}
		void clean(bool steel)
		{
			cl->clean();
		}
		string get_name()
		{
			return l;
		}
	};
	class Polypropylene : public plastic_class
	{
		string l;
		legacy_classes::CleanPolys *cl;
	public:
		Polypropylene(){l = "Polypropylene";next = 0;heat_temp = 350;inject_psi = 90;cool_temp = 290;technique = "smooth";cl = new legacy_classes::CleanPolys();}
		~Polypropylene(){delete cl;}

		plastic_class * setup(string p)
		{
			if(l.compare(p))
				return next->setup(p);
			else
			{
				plastic = p;
				return this;
			}
		}
		void clean(bool steel)
		{
			cl->prepForReuse();
		}
		string get_name()
		{
			return "Poly";
		}
	};
	class Styrene : public plastic_class
	{
		string l;
		legacy_classes::SynthCleanup *cl;
	public:
		Styrene(){l = "Styrene";next = 0;heat_temp = 480;inject_psi = 150;cool_temp = 390;technique = "shock";cl = new legacy_classes::SynthCleanup();}
		~Styrene(){delete cl;}

		plastic_class * setup(string p)
		{
			if(l.compare(p))
				return next->setup(p);
			else
			{
				plastic = p;
				return this;
			}
		}
		void clean(bool steel)
		{
			cl->ozone();
		}
		string get_name()
		{
			return "Synthetics";
		}
	};
	class Nilon66 : public plastic_class
	{
		string l;
		legacy_classes::SynthCleanup *cl;
	public:
		Nilon66(){l = "Nylon66";next = 0;heat_temp = 480;inject_psi = 150;cool_temp = 390;technique = "shock";cl = new legacy_classes::SynthCleanup();}
		~Nilon66(){delete cl;}

		plastic_class * setup(string p)
		{
			if(l.compare(p))
				return next->setup(p);
			else
			{
				plastic = p;
				return this;
			}
		}
		void clean(bool steel)
		{
			cl->ozone();
		}
		string get_name()
		{
			return "Synthetics";
		}
	};
	class Polyethelene : public plastic_class
	{
		string l;
		legacy_classes::CleanPolys *cl;
	public:
		Polyethelene(){l = "Polyethelene";next = 0;heat_temp = 350;inject_psi = 90;cool_temp = 290;technique = "smooth";cl = new legacy_classes::CleanPolys();}
		~Polyethelene(){delete cl;}

		plastic_class * setup(string p)
		{
			if(l.compare(p))
				return next->setup(p);
			else
			{
				plastic = p;
				return this;
			}
		}
		void clean(bool steel)
		{
			cl->prepForReuse();
		}
		string get_name()
		{
			return "Poly";
		}
	};
	class PET : public plastic_class
	{
		string l;
		legacy_classes::PETCleanup *cl;
	public:
		PET(){l = "PET";next = 0;heat_temp = 404;inject_psi = 110;cool_temp = 340;technique = "smooth";cl = new legacy_classes::PETCleanup();}
		~PET(){delete cl;}

		plastic_class * setup(string p)
		{
			if(l.compare(p))
				return next->setup(p);
			else
			{
				plastic = p;
				return this;
			}
		}
		void clean(bool steel)
		{
			if(steel)
				cl->carbonize();
			else
				cl->purify();
		}
		string get_name()
		{
			return l;
		}
	};

	class order
	{
		injection_line * line;
		plastic_class * p;

		ijm_110 *a;
		ijm_120 *b;
		ijm_140 *b1;
		ijm_210 *c;
		ijm_220 *c1;
		ijm_240 *c2;
		Polypropylene * p1;
		Polyethelene * p2;
		PET * p3;
		ABS * a1;
		Styrene *p4;
		Nilon66 *p5;

	public:
		~order()
		{
			delete a;
			delete b;
			delete c;
			delete p1;
			delete p2;
			delete p3;
			delete a1;
		}
		order(int num_order, string packager, string plastic, string stuffer)
		{
			a = new ijm_110(10000);
			b = new ijm_120(20000);
			a->setNext(b);
			b1 = new ijm_140(40000);
			b->setNext(b1);
			c = new ijm_210(50000);
			b1->setNext(c);
			c1 = new ijm_220(100000);
			c->setNext(c1);
			c2 = new ijm_240(200000);
			c1->setNext(c2);

			line = a->setup(num_order, packager, stuffer);

			p1 = new Polypropylene();
			p2 = new Polyethelene();
			p1->setNext(p2);
			p3 = new PET();
			p2->setNext(p3);
			p4 = new Styrene();
			p3->setNext(p4);
			p5 = new Nilon66();
			p4->setNext(p5);
			a1 = new ABS();
			p5->setNext(a1);

			p = p1->setup(plastic);
		}

		void insert_tags(string tags)
		{
			string valid[] = {"ModelNumber", "Country", "Date", "IncCounter", "PartNumber", "RecycleCode"};
			int size[] = {2, 2, 2, 4, 2, 6};
			int total = 0;
			istringstream iss(tags);

			cout << "    Insert tags [";
			do
			{
				string sub;
				iss >> sub;
				bool found = false;
				for(int i = 0; !sub.empty() && i < 6; i++)
				{
					if(!sub.compare(valid[i]))
					{
						cout << valid[i] << " ";
						total += size[i];
						found = true;
					}
				}
				if(!sub.empty() && !found)
					cout << "Ignoring unknown tag " << sub << ".\n";
			} while (iss);
			cout << "] of width " << to_string(total) << "/20 mm.\n";
		}

		int get_volume(string shape)
		{
			string valid[] = {"duck", "car", "hero", "dino"};
			int size[] = {35, 40, 50, 30};

			for(int i = 0; i < 4; i++)
			{
				if(!shape.compare(valid[i]))
				{
					return size[i];
				}
			}
			return -1;
		}

		void process_order(string location, string shape, string tags, string color, string plastic, int uvinhibiter, int antibacterial, string finish, int microfibers)
		{
			cout << "  Process order.\n";

			mill a;
			sister a1;
			a.setNext(&a1);
			purchase a2;
			a1.setNext(&a2);
			inventory b;
			a2.setNext(&b);

			locate * l = a.setup(location, shape, line, finish);

			insert_tags(tags);

			cout << "    Load plastic, color, and additive bins.\n";
			if(color.empty())
			{
				cout << "      <>No color specified, defaulting to black.\n";
				color = "black";
			}

			int volume = get_volume(l->get_shape());
			cout << "      Recipe: " << plastic << "(" << volume << ") " << color << "(" << int(volume*.1) << ") ";
			if(uvinhibiter)
				cout << "UVInhibiter(" << uvinhibiter << ") ";
			if(antibacterial)
				cout << "AntiBacterial(" << antibacterial << ") ";
			if(microfibers)
				cout << "MicroFibers(" << microfibers << ") ";
			int total = (int(volume *1.1) + uvinhibiter + antibacterial + microfibers)*line->get_cavities();
			cout << "Total = " << total << ".\n";


			cout << "    Cycle IJM for " << p->get_name() << " " << line->get_num() << " times.\n";
			p->print_injection_cycle();
			cout << "      " << line->get_output() << " package bin full...\n";
			cout << "        IJM pausing while " << line->get_output() << " package bin is swapped.\n";
			cout << "        Conveyer belt pausing while " << line->get_output() << " package bin is swapped.\n";
			cout << "        Packager pausing while " << line->get_output() << " package bin is swapped.\n";
			cout << "        Stuffer filling " << line->get_output() << " package bin with " << line->get_stuff_lc() << " stuffing.\n";

			p->clean(line->is_steel());
		}
	};
// Seam point - add another class.

}

namespace template_method {	// DP 4.

// Seam point - add another step.

}

void process(map<string, string>& order)
{
	string plastic;
	int num_orders = 0;
	string packager;
	string color;
	string cavities;
	string shape;
	string location;
	string finish;
	string tags;
	string stuffer;
	int uvinhibiter = 0;
	int antibacterial = 0;
	int microfibers = 0;
	string ship;

	plastic = order["plastic"];
	string tmp = order["size"];
	if(!tmp.empty())
		num_orders = stoi(tmp);
	if(num_orders >= 400000)
	{
		cout << "  <>Size too large |400000| defaulting to HugeOrder of 200000.\n";
		num_orders = 200000;
	}
	packager = order["packager"];
	color = order["color"];
	shape = order["mold"];
	location = order["moldLoc"];
	finish = order["finish"];
	tags = order["tags"];
	stuffer = order["stuffer"];
	ship = order["address"];
	tmp = order["UVInhibiter"];
	if(!tmp.empty())
		uvinhibiter = stoi(tmp);
	tmp = order["AntiBacterial"];
	if(!tmp.empty())
		antibacterial = stoi(tmp);
	tmp = order["MicroFibers"];
	if(!tmp.empty())
		microfibers = stoi(tmp);

	if(plastic.empty())
	{
		cout << "  <>Unknown plastic |" << plastic << "| defaulting to ABS.\n";
		plastic = "ABS";
	}
	if(!num_orders)
	{
		cout << "  <>No size specified, defaulting to 100.\n";
		num_orders = 100;
	}
	if(packager.empty())
	{
		cout << "  <>Unknown packager |" << packager << "| defaulting to Bulk packager.\n";
		packager = "Bulk";
	}
	if(stuffer.empty())
	{
		cout << "  <>Unknown stuffer |" << stuffer << "| defaulting to Air stuffer.\n";
		stuffer = "Air";
	}

	factory_method::order * o = new factory_method::order(num_orders, packager, plastic, stuffer);
	o->process_order(location, shape, tags, color, plastic, uvinhibiter, antibacterial, finish, microfibers);
	cout << "    Ship to \"" << ship << "\"\n";
	delete o;
}

pair<string, string> parse(string line) {
	char key[83];
	char val[83] = {0};

	sscanf(line.c_str(), "%s", key);

	char* equalSign = (char*)strchr(line.c_str(), '=');
	string value = "";
	if(equalSign) {	// tags = sam i am
		char*	nextToken = equalSign += 2;
		while(nextToken) {
			sscanf(nextToken, "%s", val);
			value += val;
			nextToken = strchr(nextToken+1, ' ');
			value += " ";
		}
		value.erase(value.length()-1, 1);
	}

	return make_pair(key, value);
}

map<string, string> getCompleteOrder(FILE* orderFilePtr) {
	map<string, string> order;
	char line[80+3];
	pair<string, string>	keyValue;

	while(fgets(line, 80, orderFilePtr)) {
		cout << line;
		if(strstr(line, "endOfOrder")) {
			return(order);
			}
		else {
			keyValue = parse(line);
			string key = keyValue.first;
			if(strchr(key.c_str(), ':'))	// Skip left justified order number.
				continue;
			string value = keyValue.second;
			order[key] = value;
		}
	}

	return order;
}

void demo(const string& orderFile) {
	cout << "<<< final design >>>\n";

	FILE* orderFilePtr = fopen(orderFile.c_str(), "r");

	for(;;) {	// Get and process each order.
		map<string, string> order = getCompleteOrder(orderFilePtr);
		if(order.size() == 0)
			break;
		process(order);
	}
}

}

#endif /* DP4_SRC_STUDENTS_JASON_H_ */
