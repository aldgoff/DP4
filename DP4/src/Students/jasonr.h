/*
 * jasonr.h
*
*  Created on: 5/1/2015
*      Author: Jason Holmes
*
*  Project: Intro to Design Patterns Pilot class.
 */
#define	DP4_SRC_STUDENTS_JASONR_H_	// Need shared_ptr, unique_ptr, etc.
#ifndef DP4_SRC_STUDENTS_JASONR_H_
#define DP4_SRC_STUDENTS_JASONR_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>
using namespace std;




namespace final_jasonr_file {

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

	}




	/************************************************************************/
	// Cleaners
	class Cleaner {
	public:
		static shared_ptr<Cleaner> Cleaner::get_cleaner(string & plastic);
		virtual void clean(string & metal) = 0;
		virtual ~Cleaner() {}
	};

	class CleanerABS : public Cleaner {
	public:
		legacy_classes::CleanABS cleaner;
		void clean(string & metal) {
			cleaner.clean();
		}
	};

	class CleanerPolys : public Cleaner {
	public:
		legacy_classes::CleanPolys cleaner;
		void clean(string & metal) {
			cleaner.prepForReuse();
		}
	};

	class CleanerPET : public Cleaner {
	public:
		legacy_classes::PETCleanup cleaner;
		void clean(string & metal) {
			if (metal == "Steel") {
				cleaner.carbonize();
			}
			else if (metal == "Aluminum") {
				cleaner.purify();
			}
		}
	};

	class CleanerOzone : public Cleaner {
	public:
		void clean(string & metal) {
			cout << "    Clean synthetic mold: ozone wash.\n";
		}
	};



	shared_ptr<Cleaner> Cleaner::get_cleaner(string & plastic) {
		if (plastic == "ABS") {
			return make_shared<CleanerABS>();
		}
		else if (plastic == "Polyethelene" || plastic == "Polypropylene") {
			return make_shared<CleanerPolys>();
		}
		else if (plastic == "PET") {
			return make_shared<CleanerPET>();
		}
		else if (plastic == "Styrene" || plastic == "Nylon66") {
			return make_shared<CleanerOzone>();
		}
		else {
			cout << "ERROR!!! Bad injection cycle" << plastic << endl;
			return make_shared<CleanerPET>();
		}
	}





	/************************************************************************/
	/* Generic pause observer base class */
	class OutputBin;
	class Machine {
	public:
		virtual void pause(OutputBin &) = 0;
		virtual ~Machine() {}
	};

	/************************************************************************/
	// Polymorphic output bin (From AF) (subject)
	class OutputBin {
	protected:
		string _name;
		vector<shared_ptr<Machine>> machines;

	public:
		OutputBin(const string type) : _name(type) {}

		/* When full, sends a pause to each observer machine */
		void full() {
			cout << "      " << _name << " package bin full..." << endl;
			for (auto machine : machines) {
				machine->pause(*this);
			}
		}

		/* Attach a machine observer */
		void attach(shared_ptr<Machine> machine) {
			machines.push_back(machine);
		}

		/* Detatch a machine observer */
		void detatch(shared_ptr<Machine> machine) {
			for (auto iter = machines.begin(); iter != machines.end(); ++iter) {
				if (*iter == machine) {
					machines.erase(iter);
					break;
				}
			}
		}

		string details() {
			return _name;
		}

		virtual ~OutputBin() {}

	};

	class CardboardBoxBin : public OutputBin {
	public:
		CardboardBoxBin() : OutputBin("CardboardBox") {}
	};

	class PallotBoxBin : public OutputBin {
	public:
		PallotBoxBin() : OutputBin("PallotBox") {}
	};

	class Crate : public OutputBin {
	public:
		Crate() : OutputBin("Crate") {}
	};




	/************************************************************************/
	// Stuffing machines
	class Stuffer : public Machine {
		string _type;
	public:
		static shared_ptr<Stuffer> get_stuffer(string & type);
		Stuffer(const string type) : _type(type) {}
		string details() {
			return _type;
		}
		void pause(OutputBin & bin) {
			cout << "        Stuffer filling " << bin.details() << " package bin with " << _type << " stuffing." << endl;
		}
		virtual ~Stuffer() {}
	};

	class AirStuffer : public Stuffer {
	public:
		AirStuffer() : Stuffer("air") {}
	};

	class PopcornStuffer : public Stuffer {
	public:
		PopcornStuffer() : Stuffer("styrene popcorn") {}
	};

	class BubbleWrapStuffer : public Stuffer {
	public:
		BubbleWrapStuffer() : Stuffer("bubble wrap") {}
	};

	class FoamStuffer : public Stuffer {
	public:
		FoamStuffer() : Stuffer("expanding foam") {}
	};

	shared_ptr<Stuffer> Stuffer::get_stuffer(string & type) {
		if (type == "Air") {
			return make_shared<AirStuffer>();
		}
		else if (type == "Popcorn") {
			return make_shared<PopcornStuffer>();
		}
		else if (type == "BubbleWrap") {
			return make_shared<BubbleWrapStuffer>();
		}
		else if (type == "Foam") {
			return make_shared<FoamStuffer>();
		}
		else {
			cout << "ERROR: Unknown stuffer " << type << endl;
			return make_shared<AirStuffer>();
		}
	}

	/************************************************************************/
	// Packagers
	// Polymorphic packager (Bulk, etc.) (observer)
	class Packager : public Machine {
	protected:
		string _name;

	public:

		/* Returns the appopriate packager class based on the order */
		static shared_ptr<Packager> get_packager(string&);

		Packager(string& type) {
			_name = type;
		}

		void pause(OutputBin & bin) {
			cout << "        Packager pausing while " << bin.details() << " package bin is swapped." << endl;
		}

		string name() { return _name; }
		virtual ~Packager() {}
	};

	class Bulk : public Packager {
	public:
		Bulk(string& type) : Packager(type) {}
	};

	class ShrinkWrap : public Packager {
	public:
		ShrinkWrap(string& type) : Packager(type) {}
	};

	class HardPack : public Packager {
	public:
		HardPack(string& type) : Packager(type) {}
	};

	class ZipLock : public Packager {
	public:
		ZipLock(string & type) : Packager(type) {}
	};

	shared_ptr<Packager> Packager::get_packager(string& type) {
		if (type == "ShrinkWrap") {
			return make_shared<ShrinkWrap>(type);
		}
		else if (type == "HardPack") {
			return make_shared<HardPack>(type);
		}
		else if (type == "ZipLock") {
			return make_shared<ZipLock>(type);
		}
		else {
			return make_shared<Bulk>(type);
		}
	}


	/************************************************************************/
	// Conveyor Belts
	// Polymorphic ConveyorBelt (From AF) (observer)
	class ConveyorBelt : public Machine {
		string _name;
	public:
		ConveyorBelt(const string type) : _name(type) {}
		void pause(OutputBin & bin) {
			cout << "        Conveyer belt pausing while " << bin.details() << " package bin is swapped." << endl;
		}
		string details() {
			return _name;
		}
		virtual ~ConveyorBelt() {}
	};

	class LinearBelt : public ConveyorBelt {
	public:
		LinearBelt() : ConveyorBelt("Linear") {}
	};

	class YSplitBelt : public ConveyorBelt {
	public:
		YSplitBelt() : ConveyorBelt("Y-Split") {}
	};

	class VLevelBelt : public ConveyorBelt {
	public:
		VLevelBelt() : ConveyorBelt("V-Level") {}
	};

	/************************************************************************/
	// Parent for plastic and decorators
	class MoldIngredient {
	public:
		virtual int recipe(int cc) = 0;
		virtual string name() = 0;
		virtual ~MoldIngredient() {}
	};

	/************************************************************************/
	// Plastics
	class Plastic : public MoldIngredient {
	protected:
		string _type;
	public:
		Plastic(string & type) : _type(type) {}
		string name(){ return _type; }
		int recipe(int cc) {
			cout << _type + "(" + to_string(cc) + ")";
			return cc;
		}

	};


	/************************************************************************/
	// Add ons, generic decorator type
	class AddOn : public MoldIngredient {
	protected:
		shared_ptr<MoldIngredient> trailing;
	public:
		AddOn(shared_ptr<MoldIngredient> ingredient) : trailing(ingredient) {}
		virtual ~AddOn() {}
	};


	/************************************************************************/
	// Additives
	class Additive : public AddOn {
	protected:
		int _cc;
	public:
		static shared_ptr<Additive> get_additive(string & additive, int cc, shared_ptr<MoldIngredient> ingredient);
		Additive(int cc, shared_ptr<MoldIngredient> ingredient) : _cc(cc), AddOn(ingredient) {}
		virtual ~Additive() {}
	};

	class UVInhibiter : public Additive {
	public:
		UVInhibiter(int cc, shared_ptr<MoldIngredient> ingredient) : Additive(cc, ingredient) {}
		string name() { return "UVInhibiter"; }
		int recipe(int cc) {
			int sum = trailing->recipe(cc) + _cc;
			cout << " " << name() << "(" + to_string(_cc) + ")";
			return sum;
		}
	};

	class AntiBacterial : public Additive {
	public:
		AntiBacterial(int cc, shared_ptr<MoldIngredient> ingredient) : Additive(cc, ingredient) {}
		string name() { return "AntiBacterial"; }
		int recipe(int cc) {
			int sum = trailing->recipe(cc) + _cc;
			cout << " " << name() << "(" + to_string(_cc) + ")";
			return sum;
		}
	};

	class MicroFiber : public Additive {
	public:
		MicroFiber(int cc, shared_ptr<MoldIngredient> ingredient) : Additive(cc, ingredient) {}
		string name() { return "MicroFibers"; }
		int recipe(int cc) {
			int sum = trailing->recipe(cc) + _cc;
			cout << " " << name() << "(" + to_string(_cc) + ")";
			return sum;
		}
	};

	// Return additive based on order, providing config file (and previous decorator)
	shared_ptr<Additive> Additive::get_additive(string & additive, int cc, shared_ptr<MoldIngredient> ingredient) {
		if (additive == "UVInhibiter") {
			return make_shared<UVInhibiter>(cc, ingredient);
		}
		else if (additive == "AntiBacterial") {
			return make_shared<AntiBacterial>(cc, ingredient);
		}
		else if (additive == "MicroFibers") {
			return make_shared<MicroFiber>(cc, ingredient);
		}
		else {
			cout << "ERROR - BAD ADDITIVE" << endl;
			return make_shared<UVInhibiter>(cc, ingredient);
		}
	}

	/************************************************************************/
	// Colors
	class Color : public AddOn {
	protected:
		string _color;
	public:
		Color(shared_ptr<MoldIngredient> ingredient) : AddOn(ingredient) {
			_no_color();
		}

		Color(string & color, shared_ptr<MoldIngredient> ingredient) : _color(color), AddOn(ingredient) {
			if (color == "") {
				_no_color();
			}
		}

		int recipe(int cc) {
			int my_cc = int(0.1*cc);
			int sum = trailing->recipe(cc) + my_cc;
			cout << " " + _color + "(" + to_string(my_cc) + ")";
			return sum;
		}

		string name() { return _color; }

		void _no_color() {
			cout << "      <>No color specified, defaulting to black." << endl;
			_color = "black";
		}

	};


	/************************************************************************/
	// Tags
	class Tag {
	protected:
		int _width;
		string _type;
	public:
		static vector<shared_ptr<Tag>> get_tags(string & tag_string);
		Tag(string & name, int width = 2) : _type(name), _width(width) {}
		int width() { return _width; }
		string name() { return _type; }
		virtual ~Tag() {}
	};

	class ModelNumber : public Tag {
	public:
		ModelNumber(string & name) : Tag(name) {}
	};

	class Country : public Tag {
	public:
		Country(string & name) : Tag(name) {}
	};

	class Date : public Tag {
	public:
		Date(string & name) : Tag(name) {}
	};

	class IncCounter : public Tag {
	public:
		IncCounter(string & name) : Tag(name, 4) {}
	};

	class PartNumber : public Tag {
	public:
		PartNumber(string & name) : Tag(name) {}
	};

	class RecycleCode : public Tag {
	public:
		RecycleCode(string & name) : Tag(name, 6) {}
	};

	/* Returns a new tag based on the name*/
	shared_ptr<Tag> new_tag(string & buffer) {
		if (buffer == "ModelNumber") {
			return make_shared<ModelNumber>(buffer);
		}
		else if (buffer == "Country") {
			return make_shared<Country>(buffer);
		}
		else if (buffer == "Date") {
			return make_shared<Date>(buffer);
		}
		else if (buffer == "PartNumber") {
			return make_shared<PartNumber>(buffer);
		}
		else if (buffer == "RecycleCode") {
			return make_shared<RecycleCode>(buffer);
		}
		else if (buffer == "IncCounter") {
			return make_shared<IncCounter>(buffer);
		}
		else {
			cout << "Ignoring unknown tag " << buffer << endl;
			return nullptr;
		}
	}

	/* Splits a tag string and returns a list of Tags */
	vector<shared_ptr<Tag>> Tag::get_tags(string & tag_string){
		vector<shared_ptr<Tag>> tags;
		string buffer;
		for (auto character : tag_string) {
			if (!isspace(character)) {
				buffer += character;
			}
			else {
				auto tag = new_tag(buffer);
				if (tag != nullptr) {
					tags.push_back(tag);
				}
				buffer.clear();
			}
		}
		if (!buffer.empty()) {
			auto tag = new_tag(buffer);
			if (tag != nullptr) {
				tags.push_back(tag);
			}
		}

		return tags;
	}




	/************************************************************************/
	// Mold Shapes
	class Shape {
		string _shape;
		string _finish;
		int _cc;
	public:
		static shared_ptr<Shape> get_shape(string & shape, string & finish);
		Shape(const string shape, string & finish, int cc) : _shape(shape), _cc(cc), _finish(finish) {}
		string name() { return _shape; }
		int volume() { return _cc; }
		string finish() { return _finish; }
		virtual ~Shape() {}
	};

	class Duck : public Shape {
	public:
		Duck(string & shape, string & finish) : Shape("duck", finish, 35) {}
	};

	class Car : public Shape {
	public:
		Car(string & shape, string & finish) : Shape("car", finish, 40) {}
	};

	class Hero : public Shape {
	public:
		Hero(string & shape, string & finish) : Shape("hero", finish, 50) {}
	};

	class Dino : public Shape {
	public:
		Dino(string & shape, string & finish) : Shape("dino", finish, 30) {}
	};

	/* Returns a shape class based on name */
	shared_ptr<Shape> Shape::get_shape(string & shape, string & finish){
		if (shape == "duck") {
			return make_shared<Duck>(shape, finish);
		}
		else if (shape == "car") {
			return make_shared<Car>(shape, finish);
		}
		else if (shape == "hero") {
			return make_shared<Hero>(shape, finish);
		}
		else if (shape == "dino") {
			return make_shared<Dino>(shape, finish);
		}
		else {
			cout << "ERROR!!!! - Invalid shape " << shape << endl;
			return make_shared<Duck>(shape, finish);
		}
	}




	/************************************************************************/
	// Molds
	class Mold {
	protected:
		int _cavities;
		string _metal;
		shared_ptr<Shape> _shape;
	public:
		Mold(int cavities, const string metal) : _cavities(cavities), _metal(metal){}

		int cavities() { return _cavities; }
		string metal() { return _metal; }
		shared_ptr<Shape> shape() { return _shape; }

		string details() { return _metal + "(" + to_string(_cavities) + ")"; }

		void set_shape(shared_ptr<Shape> shape) {
			_shape = shape;
		}

		virtual ~Mold() {}

	};

	class AluminumMold : public Mold {
	public:
		AluminumMold(int cavities) : Mold(cavities, "Aluminum") {}
	};

	class SteelMold : public Mold {
	public:
		SteelMold(int cavities) : Mold(cavities, "Steel") {}
	};



	/************************************************************************/
	// Milling Platform
	class MillingPlatform {
		int _cavities;
		string _platform;
		shared_ptr<Mold> _mold;
	public:
		MillingPlatform(const string platform, shared_ptr<Mold> mold) : _platform(platform), _mold(mold) {}
		static shared_ptr<MillingPlatform> get_platform(shared_ptr<Mold> mold);
		virtual string drill() {
			return "drill";
		}
		virtual string cut() {
			return "cut";
		}
		virtual string grind() {
			return "grind";
		}

		void run() {
			cout << "    Create " << _mold->shape()->name() << " mold from mill with " << _mold->cavities() << " cavities:" << endl;
			cout << "      using " << _platform << " tools (" << drill() << ", " << cut() << ", and " << grind() << ") to mill ";
			cout << _mold->metal() << " block into " << _mold->cavities() << " " << _mold->shape()->name() << " shapes with " << _mold->shape()->finish() << " finish." << endl;;
		}

		virtual ~MillingPlatform() {}
	};

	class HighCarbon : public MillingPlatform {
	public:
		HighCarbon(shared_ptr<Mold> mold) : MillingPlatform("HighCarbon", mold) {}

		string grind() {
			return "high speed grind";
		}

	};

	class Carbide : public MillingPlatform {
	public:
		Carbide(shared_ptr<Mold> mold) : MillingPlatform("Carbide", mold) {}
		string drill() {
			return "high speed drill";
		}

		string cut() {
			return "cross cut";
		}

		string grind() {
			return "layer grind";
		}

	};

	class DiamondTipped : public MillingPlatform {
	public:
		DiamondTipped(shared_ptr<Mold> mold) : MillingPlatform("DiamondTipped", mold) {}
		string drill() {
			return "precision drill";
		}

		string cut() {
			return "oil cooled cut";
		}

		string grind() {
			return "cartoid grind";
		}
	};

	/* Return platform based on metal and finish */
	shared_ptr<MillingPlatform> MillingPlatform::get_platform(shared_ptr<Mold> mold) {
		if (mold->shape()->finish() == "satin") {
			return make_shared<DiamondTipped>(mold);
		}
		if (mold->metal() == "Aluminum") {
			return make_shared<HighCarbon>(mold);
		}
		else {
			return make_shared<Carbide>(mold);
		}
	}


	/*************************************************************************/
	// Injection cycle
	class InjectionCycle {
	public:
		static shared_ptr<InjectionCycle> get_injection_cycle(string & plastic);
		virtual void run() = 0;
		virtual ~InjectionCycle() {}
	};

	class ABSInjectionCycle : public InjectionCycle {
	public:
		void run() {
			cout << "      Close - heat to 440 - inject at 125 PSI - cool to 360 - separate - progressive eject." << endl;
		}
	};

	class PolyInjectionCycle : public InjectionCycle {
	public:
		void run() {
			cout << "      Close - heat to 350 - inject at 90 PSI - cool to 290 - separate - smooth eject." << endl;
		}
	};

	class PETInjectionCycle : public InjectionCycle {
	public:
		void run() {
			cout << "      Close - heat to 404 - inject at 110 PSI - cool to 340 - separate - smooth eject." << endl;
		}
	};

	class StyreneInjectionCycle : public InjectionCycle {
		void run() {
			cout << "      Close - heat to 480 - inject at 150 PSI - cool to 390 - separate - shock eject." << endl;
		}
	};


	/* Returns injection cycle based on plastic */
	shared_ptr<InjectionCycle> InjectionCycle::get_injection_cycle(string & plastic) {
		if (plastic == "ABS") {
			return make_shared<ABSInjectionCycle>();
		}
		else if (plastic == "Polyethelene" || plastic == "Polypropylene") {
			return make_shared<PolyInjectionCycle>();
		}
		else if (plastic == "PET") {
			return make_shared<PETInjectionCycle>();
		}
		else if (plastic == "Styrene" || plastic == "Nylon66") {
			return make_shared<StyreneInjectionCycle>();
		}
		else {
			cout << "ERROR!!! Bad injection cycle" << plastic << endl;
			return make_shared<PETInjectionCycle>();
		}
	}


	/************************************************************************/
	// IJM
	class IJM : public Machine {
	protected:
		string _model;
		shared_ptr<Mold> _mold;
		int _order_size;
		unique_ptr<ConveyorBelt> _conveyor_belt;
		unique_ptr<OutputBin> _output_bin;

	public:
		IJM(const string model, int order_size) : _model(model), _order_size(order_size) {}

		void simulate(string & plastic) {
			cout << "    Cycle IJM for " << plastic << " " << cycles() << " times." << endl;
			InjectionCycle::get_injection_cycle(plastic)->run();
		}

		int cycles() {
			return _order_size / _mold->cavities();
		}

		shared_ptr<Mold> mold() {
			return _mold;
		}

		string details() {
			return "    " + _model + " - " + _mold->details();
		}

		void pause(OutputBin & bin) {
			cout << "        IJM pausing while " << bin.details() << " package bin is swapped." << endl;
		}

		virtual ~IJM() {}

	};

	class IJM_110 : public IJM {
	public:
		IJM_110(int order_size) : IJM("IJM_110", order_size) {
			_mold = make_shared<AluminumMold>(1);
		}
	};

	class IJM_120 : public IJM {
	public:
		IJM_120(int order_size) : IJM("IJM_120", order_size) {
			_mold = make_shared<AluminumMold>(2);
		}
	};

	class IJM_140 : public IJM {
	public:
		IJM_140(int order_size) : IJM("IJM_140", order_size) {
			_mold = make_shared<AluminumMold>(4);
		}
	};

	class IJM_210 : public IJM {
	public:
		IJM_210(int order_size) : IJM("IJM_210", order_size) {
			_mold = make_shared<SteelMold>(1);
		}
	};

	class IJM_220 : public IJM{
	public:
		IJM_220(int order_size) : IJM("IJM_220", order_size) {
			_mold = make_shared<SteelMold>(2);
		}
	};

	class IJM_240 : public IJM {
	public:
		IJM_240(int order_size) : IJM("IJM_240", order_size) {
			_mold = make_shared<SteelMold>(4);
		}
	};


	/************************************************************************/
	// Injection Line (AF)
	class InjectionLine {
	protected:
		shared_ptr<IJM> _ijm;
		shared_ptr<ConveyorBelt> _conveyor_belt;
		shared_ptr<Packager> _packager;
		shared_ptr<OutputBin> _output_bin;
		shared_ptr<Stuffer> _stuffer;
	public:
		static shared_ptr<InjectionLine> get_injection_line(int order_size, string & packager, string & stuffer);

		InjectionLine(string & packager, string & stuffer) {
			_packager = Packager::get_packager(packager);
			_stuffer = Stuffer::get_stuffer(stuffer);
		}

		void setup() {

			_output_bin->attach(_ijm);
			_output_bin->attach(_conveyor_belt);
			_output_bin->attach(_packager);
			_output_bin->attach(_stuffer);

			cout << "  Setup injection line for " << _ijm->cycles()
				 << " run with " << _packager->name() << " packager"
				 << " and " << _stuffer->details() << " stuffing:" << endl;
			cout << _ijm->details() + " - " + _conveyor_belt->details() + " conveyer belt - " + _output_bin->details() << endl;
		}

		void run(string & plastic) {
			_ijm->simulate(plastic);
		}

		void pause() {
			_output_bin->full();
		}

		shared_ptr<Mold> mold() {
			return _ijm->mold();
		}

		virtual ~InjectionLine() {
			_output_bin->detatch(_ijm);
			_output_bin->detatch(_conveyor_belt);
			_output_bin->detatch(_packager);
			_output_bin->detatch(_stuffer);
		}

	};

	class SmallInjectionLine : public InjectionLine {
	public:
		SmallInjectionLine(int order_size, string & packager, string & stuffer) : InjectionLine(packager, stuffer) {
			_ijm = make_shared<IJM_110>(order_size);
			_conveyor_belt = make_shared<LinearBelt>();
			_output_bin = make_shared<CardboardBoxBin>();
		}
	};

	class MediumInjectionLine : public InjectionLine {
	public:
		MediumInjectionLine(int order_size, string & packager, string & stuffer) : InjectionLine(packager, stuffer) {
			_ijm = make_shared<IJM_120>(order_size);
			_conveyor_belt = make_shared<YSplitBelt>();
			_output_bin = make_shared<CardboardBoxBin>();
		}
	};

	class LargeInjectionLine : public InjectionLine {
	public:
		LargeInjectionLine(int order_size, string & packager, string & stuffer) : InjectionLine(packager, stuffer) {
			_ijm = make_shared<IJM_210>(order_size);
			_conveyor_belt = make_shared<LinearBelt>();
			_output_bin = make_shared<PallotBoxBin>();
		}
	};

	class FastInjectionLine : public InjectionLine {
	public:
		FastInjectionLine(int order_size, string & packager, string & stuffer) : InjectionLine(packager, stuffer) {
			_ijm = make_shared<IJM_140>(order_size);
			_conveyor_belt = make_shared<VLevelBelt>();
			_output_bin = make_shared<PallotBoxBin>();
		}
	};

	class ExtraLargeInjectionLine : public InjectionLine {
	public:
		ExtraLargeInjectionLine(int order_size, string & packager, string & stuffer) : InjectionLine(packager, stuffer) {
			_ijm = make_shared<IJM_220>(order_size);
			_conveyor_belt = make_shared<YSplitBelt>();
			_output_bin = make_shared<Crate>();
		}
	};

	class HugeInjectionLine : public InjectionLine {
	public:
		HugeInjectionLine(int order_size, string & packager, string & stuffer) : InjectionLine(packager, stuffer) {
			_ijm = make_shared<IJM_240>(order_size);
			_conveyor_belt = make_shared<VLevelBelt>();
			_output_bin = make_shared<Crate>();
		}
	};

	/* Returns injection line based on order size */
	shared_ptr<InjectionLine> InjectionLine::get_injection_line(int order_size, string & packager, string & stuffer) {
		if (order_size <= 10000) {
			return make_shared<SmallInjectionLine>(order_size, packager, stuffer);
		}
		else if (order_size <= 20000) {
			return make_shared<MediumInjectionLine>(order_size, packager, stuffer);
		}
		else if (order_size <= 40000) {
			return make_shared<FastInjectionLine>(order_size, packager, stuffer);
		}
		else if (order_size <= 50000) {
			return make_shared<LargeInjectionLine>(order_size, packager, stuffer);
		}
		else if (order_size <= 100000) {
			return make_shared<ExtraLargeInjectionLine>(order_size, packager, stuffer);
		}
		else {
			return make_shared<HugeInjectionLine>(order_size, packager, stuffer);
		}
	}



	/************************************************************************/
	// Mold source
	class MoldSource {
	protected:
		shared_ptr<MoldSource> _fallback;
	public:
		MoldSource(shared_ptr<MoldSource> fallback) : _fallback(fallback) {}
		virtual void get_mold(shared_ptr<Mold> mold, string & location) = 0;
		void check_next(shared_ptr<Mold> mold, string & location) {
			if (_fallback != nullptr) {
				_fallback->get_mold(mold, location);
			}
			else {
				cout << "ERROR - could not find mold location" << endl;
			}
		}
		virtual ~MoldSource() {}
	};

	class Inventory : public MoldSource {
	public:
		Inventory(shared_ptr<MoldSource> fallback) : MoldSource(fallback) {}
		void get_mold(shared_ptr<Mold> mold, string & location) {
			if (location == "inventory"){
				cout << "    Pull " << mold->shape()->name() << " mold from inventory." << endl;
				return;
			}
			check_next(mold, location);
		}
	};

	class Mill : public MoldSource {
	public:
		Mill(shared_ptr<MoldSource> fallback) : MoldSource(fallback) {}
		void get_mold(shared_ptr<Mold> mold, string & location) {
			if (location == "mill") {
				shared_ptr<MillingPlatform> platform = MillingPlatform::get_platform(mold);
				platform->run();
				return;
			}
			check_next(mold, location);

		}
	};

	class Purchase : public MoldSource {
	public:
		Purchase(shared_ptr<MoldSource> fallback) : MoldSource(fallback) {}
		void get_mold(shared_ptr<Mold> mold, string & location) {
			if (location == "purchase") {
				cout << "    Acquire " << mold->shape()->name() << " mold via purchase." << endl;
				return;
			}
			check_next(mold, location);
		}
	};

	class SisterCompany : public MoldSource {
	public:
		SisterCompany(shared_ptr<MoldSource> fallback) : MoldSource(fallback) {}
		void get_mold(shared_ptr<Mold> mold, string & location) {
			if (location == "sisterCompany") {
				cout << "    Borrow " << mold->shape()->name() << " mold from sister company." << endl;
				return;
			}
			check_next(mold, location);
		}
	};



	/************************************************************************/
	/* Wrapper for the order which fills in default values */
	class Order {
	private:
		map<string, string> order_map;
	public:
		Order(map<string, string> & order) : order_map(order) {

			map<string, string> default_map;
			default_map["size"] = "100";
			default_map["packager"] = "Bulk";
			default_map["plastic"] = "ABS";
			default_map["stuffer"] = "Air";

			for (auto kv : default_map) {
				if (order_map.find(kv.first) == order_map.end()) {
					cout << "  <>Unknown " << kv.first << ", defaulting to ";
					cout << kv.second << "." << endl;
					order_map[kv.first] = kv.second;
				}
			}

			if (atoi(get("size").c_str()) > 200000) {
				cout << "  <>Size too large |" << get("size") << "| defaulting to HugeOrder of 200000" << endl;
				order_map["size"] = "200000";
			}

		}

		/* Returns entry in order, or empty string if not found */
		string get(const string key) {
			if (order_map.find(key) != order_map.end()) {
				return order_map[key];
			}
			return "";
		}


	};






	/************************************************************************/
	// Order Processor
	class OrderProcesser {
		shared_ptr<InjectionLine> injection_line;
		Order _order;
		shared_ptr<MoldIngredient> plastic;

	public:
		OrderProcesser(Order & order) : _order(order) {
			int size = atoi(_order.get("size").c_str());
			injection_line = InjectionLine::get_injection_line(size, order.get("packager"), order.get("stuffer"));
			injection_line->setup();

		}

		void get_mold() {
			string shape = _order.get("mold");
			string location = _order.get("moldLoc");

			bool used_defaults = false;
			if (shape == "") {
				shape = "duck";
				used_defaults = true;
			}
			if (location == "") {
				location = "inventory";
				used_defaults = true;
			}

			injection_line->mold()->set_shape(Shape::get_shape(shape, _order.get("finish")));

			if (used_defaults) {
				cout << "    <>Can't find place || to get || mold from, defaulting to " << shape << " from " << location << "." << endl;
			}
			shared_ptr<MoldSource> purchase = make_shared<Purchase>(nullptr);
			shared_ptr<MoldSource> sister_company = make_shared<SisterCompany>(purchase);
			shared_ptr<MoldSource> mill = make_shared<Mill>(sister_company);
			shared_ptr<MoldSource> inventory = make_shared<Inventory>(mill);

			inventory->get_mold(injection_line->mold(), location);

		}

		void insert_tags() {
			auto mold = injection_line->mold();

			cout << "    Insert tags [";
			auto tags = Tag::get_tags(_order.get("tags"));
			int width = 0;
			for (auto tag : tags) {
				width += tag->width();
				cout << tag->name() << " ";
			}
			cout << "] of width " << width << "/20 mm." << endl;

		}

		void load_plastic() {
			cout << "    Load plastic, color, and additive bins." << endl;

			plastic = make_shared<Plastic>(_order.get("plastic"));
			plastic = shared_ptr<MoldIngredient>(new Color(_order.get("color"), plastic));

			vector<string> additives = { "UVInhibiter", "AntiBacterial", "MicroFibers" };
			for (auto additive : additives) {
				if (_order.get(additive) != "") {
					plastic = shared_ptr<MoldIngredient>(Additive::get_additive(additive, atoi(_order.get(additive).c_str()), plastic));
				}
			}

			auto mold = injection_line->mold();
			cout << "      Recipe: ";
			int total = plastic->recipe(mold->shape()->volume()) * mold->cavities();
			cout << " Total = " << total << "." << endl;

		}

		void pause() {
			injection_line->pause();
		}

		void run() {
			injection_line->run(_order.get("plastic"));
		}

		void clean() {
			auto cleaner = Cleaner::get_cleaner(_order.get("plastic"));
			cleaner->clean(injection_line->mold()->metal());
		}

		void ship() {
			cout << "    Ship to \"" << _order.get("address") << "\"" << endl;
		}

		void process() {
			cout << "  Process order." << endl;
			get_mold();
			insert_tags();
			load_plastic();
			run();
			pause();
			clean();
			ship();
		}





	};



	/************************************************************************/
	// Process function
	void process(map<string, string> & order) {
		Order o(order);
		OrderProcesser op(o);
		op.process();
		cout << endl;
	}



	/************************************************************************/
	// Rewritten file IO

	/* Removes trailing and leading whitespace, returning a new string */
	string str_trim(string & str) {
		string str_trimmed;
		string whitespace_buffer;
		bool started = false;
		for (auto character : str) {
			if (!isspace(character)) {
				if (started) {
					str_trimmed += whitespace_buffer + character;
				}
				else {
					str_trimmed += character;
				}
				whitespace_buffer.clear();
				started = true;
			}
			else {
				whitespace_buffer += character;
			}
		}
		return str_trimmed;
	}

	/* Removes whitespace, returning a new string */
	string str_strip(string & str) {
		string str_stripped;
		for (auto character : str) {
			if (!isspace(character)) {
				str_stripped += character;
			}
		}
		return str_stripped;
	}


	map<string, string> get_order(const string & order_file) {
		static ifstream infile(order_file);
		string line;
		bool in_order = false;
		map<string, string> current_order;
		if (!infile.is_open()) {
			return current_order;
			// Do something here
		}

		while (getline(infile, line)) {
			cout << line << endl;
			string buffer, key, value;
			for (auto character : line) {
				if (!in_order) {
					if (character == ':') {
						in_order = true;
						break;
					}
				}
				else {
					if (character == '=') {
						key = str_strip(buffer);
						buffer.clear();
					}
					else {
						buffer += character;
					}
				}
			}
			/* End of order reached. Add the new order to the list */
			if (str_strip(buffer) == "endOfOrder") {
				if (!current_order.empty()) {
					return current_order;
				}
			}
			/* Add the key/value pair to the current order */
			if (!buffer.empty()) {
				value = str_trim(buffer);
				current_order.emplace(key, value);
			}
		}
		return current_order;

	}

	/* Reads the order file into a list of maps, one per order */
	unique_ptr<vector<map<string, string>>> read_order_file(const string & order_file) {
		auto orders = make_unique<vector<map<string, string>>>();
		ifstream infile(order_file);
		string line;
		if (!infile.is_open()) {
			// Do something here
		}
		bool in_order = false;
		map<string, string> current_order;

		while (getline(infile, line)) {
			string buffer, key, value;
			for (auto character : line) {
				if (!in_order) {
					if (character == ':') {
						in_order = true;
						break;
					}
				}
				else {
					if (character == '=') {
						key = str_strip(buffer);
						buffer.clear();
					}
					else {
						buffer += character;
					}
				}
			}
			/* End of order reached. Add the new order to the list */
			if (str_strip(buffer) == "endOfOrder") {
				if (!current_order.empty()) {
					orders->push_back(current_order);
					current_order.clear();
				}
				in_order = false;
			}
			/* Add the key/value pair to the current order */
			if (in_order && !buffer.empty()) {
				value = str_trim(buffer);
				current_order.emplace(key, value);
			}
		}
		return orders;
	}

	void demo(const string& orderFile) {
		cout << "<<< final design >>>\n";

		auto order = get_order(orderFile);
		while (!order.empty()) {
			process(order);
			order = get_order(orderFile);
		}
	}


}

#endif /* DP4_SRC_STUDENTS_JASONR_H_ */
