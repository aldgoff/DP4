/*
 * jeff.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 */
#define DP4_SRC_STUDENTS_JEFF_H_	// Used unique_ptr.
#ifndef DP4_SRC_STUDENTS_JEFF_H_
#define DP4_SRC_STUDENTS_JEFF_H_

namespace final_jeff_file {

  const bool on = true;	// Useful macro to turn dtor instrumentation on/off.
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

  namespace adapter {			// DP 2.

    // Seam point - add another interface.

  }

  namespace strategy {		// DP 1.

    // Seam point - add another algorithm.

  }

  namespace observer {		// DP 7.

    // Seam point - add another listener.

  }

  namespace abstract_factory {// DP 10.

    // Seam point - add another type1 member.
    // Seam point - add another type2 member.
    // Seam point - add another type3 member.
    // ...

    // Seam point - add another family.

  }
  // ----- Alternatively (may make it hard to match the dtor instrumentation) -----
  namespace abstract_factory_solti {	// DP 10 - more like GoF.

    class AbstractA {};
    class AbstractB {};
    class AbstractC {};
    // ...

    class AbstractFactory {};
    class InjectionLine {};

    // 10,000
    class ConcreteA_1 : public AbstractA {};
    class ConcreteB_1 : public AbstractB {};
    class ConcreteC_1 : public AbstractC {};
    class AF_1 : public AbstractFactory {};
    class IL_1 : public InjectionLine {};

    // 20,000
    class ConcreteA_2 : public AbstractA {};
    class ConcreteB_2 : public AbstractB {};
    class ConcreteC_2 : public AbstractC {};
    class AF_2 : public AbstractFactory {};
    class IL_2 : public InjectionLine {};

    // 50,000
    class ConcreteA_3 : public AbstractA {};
    class ConcreteB_3 : public AbstractB {};
    class ConcreteC_3 : public AbstractC {};
    class AF_3 : public AbstractFactory {};
    class IL_3 : public InjectionLine {};

    // Seam line - add another family.

  }

  namespace bridge {			// DP 9.

    // Seam Point - add another implementation.

    // Seam Point - add another abstraction.

  }

  namespace chain_of_resp {	// DP 8.

    // Seam points - add another responder.

  }

  namespace decorator {		// DP 6.

    // Seam point - add another option.

  }

  namespace factory_method {	// DP 5.

    // Seam point - add another class.

  }

  namespace template_method {	// DP 4.

    // Seam point - add another step.

  }


  class Object {
  public:
    Object(const string & name) : name_(name) {}
    virtual ~Object() {}

    virtual string getName() const { return name_; }

  private:
    const string name_;
  };


  class Shape : public Object {
  public:
    static unique_ptr<Shape> get(const string & name) {
      if (name == "duck") {
        return make_unique<Shape>(name, 35);
      } else if (name == "car") {
        return make_unique<Shape>(name, 40);
      } else if (name == "hero") {
        return make_unique<Shape>(name, 50);
      } else if (name == "dino") {
        return make_unique<Shape>(name, 30);
      }
      return nullptr;
    }

    Shape(const string & name, const int cavitySize)
      : Object(name), cavitySize_(cavitySize) {
    }

    int getCavitySize() const { return cavitySize_; }

  private:
    const int cavitySize_;
  };


  class Finish : public Object {
  public:
    static unique_ptr<Finish> get(const string & name) {
      if (name == "smooth") {
        return make_unique<Finish>(name);
      } else if (name == "rippled") {
        return make_unique<Finish>(name);
      } else if (name == "dimpled") {
        return make_unique<Finish>(name);
      } else if (name == "sanded") {
        return make_unique<Finish>(name);
      } else if (name == "satin") {
        return make_unique<Finish>(name);
      }
      return make_unique<Finish>("smooth");
    }

    Finish(const string & name)
      : Object(name) {
    }
  };


  class Volume : public Object {
  public:
    Volume(const string & name, int volume)
      : Object(name), volume_(volume) {
    }

    int getVolume() { return volume_; }
    void setVolume(int volume) { volume_ = volume; }

    Volume * setNext(unique_ptr<Volume> && next) {
      next_ = move(next);
      return next_.get();
    }

    int process() {
      cout << getName() << "(" << volume_ << ") ";
      return volume_ + (next_ ? next_->process() : 0);
    }

  private:
    int volume_;
    unique_ptr<Volume> next_;
  };


  class Plastic : public Volume {
  public:
    static unique_ptr<Plastic> get(const string & name) {
      if (name == "ABS") {
        return make_unique<Plastic>(name);
      } else if (name == "Polypropylene") {
        return make_unique<Plastic>(name);
      } else if (name == "Polyethelene") {
        return make_unique<Plastic>(name);
      } else if (name == "PET") {
        return make_unique<Plastic>(name);
      } else if (name == "Styrene") {
        return make_unique<Plastic>(name);
      } else if (name == "Nylon66") {
        return make_unique<Plastic>(name);
      }
      cout << "  <>Unknown plastic |" << name << "| defaulting to ABS." << endl;
      return make_unique<Plastic>("ABS");
    }

    Plastic(const string & name)
      : Volume(name, 0) {
    }
  };


  class Color : public Volume {
  public:
    static unique_ptr<Color> get(const string & name) {
      if (name == "black") {
        return make_unique<Color>(name);
      } else if (name == "brown") {
        return make_unique<Color>(name);
      } else if (name == "red") {
        return make_unique<Color>(name);
      } else if (name == "orange") {
        return make_unique<Color>(name);
      } else if (name == "yellow") {
        return make_unique<Color>(name);
      } else if (name == "green") {
        return make_unique<Color>(name);
      } else if (name == "blue") {
        return make_unique<Color>(name);
      } else if (name == "violet") {
        return make_unique<Color>(name);
      } else if (name == "gray") {
        return make_unique<Color>(name);
      } else if (name == "white") {
        return make_unique<Color>(name);
      }
      cout << "      <>No color specified, defaulting to black." << endl;
      return make_unique<Color>("black");
    }

    Color(const string & name)
      : Volume(name, 0) {
    }
  };


  class Additive : public Volume {
  public:
    static unique_ptr<Additive> get(const string & name, int volume) {
      if (name == "UVInhibiter" || name == "AntiBacterial" || name == "MicroFibers")
        return make_unique<Additive>(name, volume);
      return nullptr;
    }

    static initializer_list<string> & getNames() {
      return names_;
    }

    Additive(const string & name, int volume)
      : Volume(name, volume) {
    }

  private:
    static initializer_list<string> names_;
  };
  initializer_list<string> Additive::names_{"UVInhibiter", "AntiBacterial", "MicroFibers",};


  class Packager : public Object {
  public:
    static unique_ptr<Packager> get(const string & name);

    Packager(const string & name)
      : Object(name) {
    }
  };

  class BulkPackager : public Packager {
  public:
    BulkPackager()
      : Packager("Bulk") {
    }
  };

  class ShrinkWrap : public Packager {
  public:
    ShrinkWrap()
      : Packager("ShrinkWrap") {
    }
  };

  class HardPack : public Packager {
  public:
    HardPack()
      : Packager("HardPack") {
    }
  };

  class ZipLock : public Packager {
  public:
    ZipLock()
      : Packager("ZipLock") {
    }
  };


  class Stuffer : public Object {
  public:
    static unique_ptr<Stuffer> get(const string & name);

    Stuffer(const string & name)
      : Object(name) {
    }

    virtual string desc() = 0;
  };

  class AirStuffer : public Stuffer {
  public:
    AirStuffer()
      : Stuffer("Air") {
    }

    virtual string desc() override { return "air"; }
  };

  class PopcornStuffer : public Stuffer {
  public:
    PopcornStuffer()
      : Stuffer("Popcorn") {
    }

    virtual string desc() override { return "styrene popcorn"; }
  };

  class BubbleWrapStuffer : public Stuffer {
  public:
    BubbleWrapStuffer()
      : Stuffer("BubbleWrap") {
    }

    virtual string desc() override { return "bubble wrap"; }
  };

  class FoamStuffer : public Stuffer {
  public:
    FoamStuffer()
      : Stuffer("Foam") {
    }

    virtual string desc() override { return "expanding foam"; }
  };

  unique_ptr<Stuffer> Stuffer::get(const string & name) {
    if (name == "Air")
      return make_unique<AirStuffer>();
    else if (name == "Popcorn")
      return make_unique<PopcornStuffer>();
    else if (name == "BubbleWrap")
      return make_unique<BubbleWrapStuffer>();
    else if (name == "Foam")
      return make_unique<FoamStuffer>();

    cout << "  <>Unknown stuffer |" << name << "| defaulting to Air stuffer." << endl;
    return make_unique<AirStuffer>();
  }


  unique_ptr<Packager> Packager::get(const string & name) {
    if (name == "Bulk") {
      return make_unique<BulkPackager>();
    } else if (name == "ShrinkWrap") {
      return make_unique<ShrinkWrap>();
    } else if (name == "HardPack") {
      return make_unique<HardPack>();
    } else if (name == "ZipLock") {
      return make_unique<ZipLock>();
    }
    cout << "  <>Unknown packager |" << name << "| defaulting to Bulk packager." << endl;
    return make_unique<BulkPackager>();
  }


  class Ijm : public Object {
  public:
    static unique_ptr<Ijm> get();

    Ijm(const string & name, unique_ptr<Ijm> && next)
      : Object(name), next_(move(next)) {
    }

    virtual Ijm * setup(int orderSize) = 0;

  protected:
    unique_ptr<Ijm> next_;
  };

  class Ijm_110 : public Ijm {
  public:
    Ijm_110(unique_ptr<Ijm> && next)
      : Ijm("IJM_110", move(next)) {
    }

    virtual Ijm * setup(int orderSize) override {
      if (orderSize <= 10000)
        return this;
      return next_->setup(orderSize);
    }
  };

  class Ijm_120 : public Ijm {
  public:
    Ijm_120(unique_ptr<Ijm> && next)
      : Ijm("IJM_120", move(next)) {
    }

    virtual Ijm * setup(int orderSize) override {
      if (orderSize <= 20000)
        return this;
      return next_->setup(orderSize);
    }
  };

  class Ijm_140 : public Ijm {
  public:
    Ijm_140(unique_ptr<Ijm> && next)
      : Ijm("IJM_140", move(next)) {
    }

    virtual Ijm * setup(int orderSize) override {
      if (orderSize <= 40000)
        return this;
      return next_->setup(orderSize);
    }
  };

  class Ijm_210 : public Ijm {
  public:
    Ijm_210(unique_ptr<Ijm> && next)
      : Ijm("IJM_210", move(next)) {
    }

    virtual Ijm * setup(int orderSize) override {
      if (orderSize <= 50000)
        return this;
      return next_->setup(orderSize);
    }
  };

  class Ijm_220 : public Ijm {
  public:
    Ijm_220(unique_ptr<Ijm> && next)
      : Ijm("IJM_220", move(next)) {
    }

    virtual Ijm * setup(int orderSize) override {
      if (orderSize <= 100000)
        return this;
      return next_->setup(orderSize);
    }
  };

  class Ijm_240 : public Ijm {
  public:
    Ijm_240(unique_ptr<Ijm> && next)
      : Ijm("IJM_240", move(next)) {
    }

    virtual Ijm * setup(int orderSize) override {
      if (orderSize <= 200000)
        return this;
      return next_->setup(orderSize);
    }
  };

  unique_ptr<Ijm> Ijm::get() {
    auto ijm240 = make_unique<Ijm_240>(nullptr);        // 200k
    auto ijm220 = make_unique<Ijm_220>(move(ijm240));   // 100k
    auto ijm210 = make_unique<Ijm_210>(move(ijm220));   // 50k
    auto ijm140 = make_unique<Ijm_140>(move(ijm210));   // 40k
    auto ijm120 = make_unique<Ijm_120>(move(ijm140));   // 20k
    auto ijm110 = make_unique<Ijm_110>(move(ijm120));   // 10k
    return move(ijm110);
  }

  class Mold : public Object {
  public:
    static unique_ptr<Mold> get();

    Mold(const string & name, int cavities, unique_ptr<Mold> && next)
      : Object(name), cavities_(cavities), next_(move(next)) {
    }
    virtual ~Mold() {}

    virtual int cavities() { return cavities_; }
    virtual int maxRuns() = 0;

    Mold * setup(int orderSize) {
      if (orderSize <= maxRuns())
        return this;
      return next_->setup(orderSize);
    }

  private:
    int cavities_;
    unique_ptr<Mold> next_;
  };

  class Aluminum : public Mold {
  public:
    Aluminum(int cavities, unique_ptr<Mold> && next)
      : Mold("Aluminum", cavities, move(next)) {
    }

    virtual int maxRuns() override { return 10000 * cavities(); };
  };

  class Steel : public Mold {
  public:
    Steel(int cavities ,unique_ptr<Mold> && next)
      : Mold("Steel", cavities, move(next)) {
    }

    virtual int maxRuns() override { return 50000 * cavities(); };
  };

  unique_ptr<Mold> Mold::get() {
    auto steel4 = make_unique<Steel>(4, nullptr);               // 50kx4
    auto steel2 = make_unique<Steel>(2, move(steel4));          // 50kx2
    auto steel = make_unique<Steel>(1, move(steel2));           // 50k
    auto aluminum4 = make_unique<Aluminum>(4, move(steel));     // 10kx4
    auto aluminum2 = make_unique<Aluminum>(2, move(aluminum4)); // 10kx2
    auto aluminum = make_unique<Aluminum>(1, move(aluminum2));  // 10k
    return move(aluminum);
  }


  class MillTool : public Object {
  public:
    static unique_ptr<MillTool> get(Mold * mold, Finish * finish);

    MillTool(const string & name)
      : Object(name) {
    }

    virtual void mill(Mold * mold, Finish * finish, Shape * shape) = 0;
  };

  class HighCarbonMillTool : public MillTool {
  public:
    HighCarbonMillTool()
      : MillTool("HighCarbon") {
    }

    virtual void mill(Mold * mold, Finish * finish, Shape * shape) override {
      cout << "      using HighCarbon tools (drill, cut, and high speed grind) to mill aluminum block into "
           << mold->cavities() << " " << shape->getName() << " shapes with " << finish->getName() << " finish.\n";
    }
  };

  class CarbideMillTool : public MillTool {
  public:
    CarbideMillTool()
      : MillTool("Carbide") {
    }

    virtual void mill(Mold * mold, Finish * finish, Shape * shape) override {
      cout << "      using Carbide tools (high speed drill, cross cut, and layer grind) to mill steel block into "
           << mold->cavities() << " " << shape->getName() << " shapes with " << finish->getName() << " finish.\n";
    }
  };

  class DiamondMillTool : public MillTool {
  public:
    DiamondMillTool()
      : MillTool("DiamondTipped") {
    }

    virtual void mill(Mold * mold, Finish * finish, Shape * shape) override {
      cout << "      using DiamondTipped tools (precision drill, oil cooled cut, and cartoid grind) to mill steel block into "
           << mold->cavities() << " " << shape->getName() << " shapes with " << finish->getName() << " finish.\n";
    }
  };

  unique_ptr<MillTool> MillTool::get(Mold * mold, Finish * finish) {
    if (finish->getName() == "satin") {
      return make_unique<DiamondMillTool>();
    } else if (dynamic_cast<Aluminum *>(mold) != nullptr) {
      return make_unique<HighCarbonMillTool>();
    } else if (dynamic_cast<Steel *>(mold) != nullptr) {
      return make_unique<CarbideMillTool>();
    }
    return nullptr;
  }


  class ConveyorBelt : public Object {
  public:
    static unique_ptr<ConveyorBelt> get();

    ConveyorBelt(const string & name, int maxOrderSize, unique_ptr<ConveyorBelt> && next)
      : Object(name), maxOrderSize_(maxOrderSize), next_(move(next)) {
    }

    ConveyorBelt * setup(int orderSize) {
      if (orderSize <= maxOrderSize_)
        return this;
      return next_->setup(orderSize);
    }

  private:
    int maxOrderSize_;
    unique_ptr<ConveyorBelt> next_;
  };

  unique_ptr<ConveyorBelt> ConveyorBelt::get() {
    auto vlevelLarge = make_unique<ConveyorBelt>("V-Level", 200000, nullptr);
    auto ysplitLarge = make_unique<ConveyorBelt>("Y-Split", 100000, move(vlevelLarge));
    auto linearLarge = make_unique<ConveyorBelt>("Linear", 50000, move(ysplitLarge));
    auto vlevel = make_unique<ConveyorBelt>("V-Level", 40000, move(linearLarge));
    auto ysplit = make_unique<ConveyorBelt>("Y-Split", 20000, move(vlevel));
    auto linear = make_unique<ConveyorBelt>("Linear", 10000, move(ysplit));
    return move(linear);
  }


  class Package : public Object {
  public:
    static unique_ptr<Package> get();

    Package(const string & name, int maxOrderSize, unique_ptr<Package> && next)
      : Object(name), maxOrderSize_(maxOrderSize), next_(move(next)) {
    }

    Package * setup(int orderSize) {
      if (orderSize <= maxOrderSize_)
        return this;
      return next_->setup(orderSize);
    }

  private:
    int maxOrderSize_;
    unique_ptr<Package> next_;
  };

  unique_ptr<Package> Package::get() {
    auto crateLarge = make_unique<Package>("Crate", 200000, nullptr);
    auto crate = make_unique<Package>("Crate", 100000, move(crateLarge));
    auto pallot = make_unique<Package>("PallotBox", 50000, move(crate));
    auto cardboardLarge = make_unique<Package>("CardboardBox", 20000, move(pallot));
    auto cardboard = make_unique<Package>("CardboardBox", 10000, move(cardboardLarge));
    return move(cardboard);
  }


  class MoldLoc : public Object {
  public:
    static tuple<unique_ptr<MoldLoc>, unique_ptr<Shape>>
    get(const string & name, Mold * mold, Finish * finish, unique_ptr<Shape> && shape);

    MoldLoc(const string & name)
      : Object(name) {
    }
  };

  class InventoryMoldLoc : public MoldLoc {
  public:
    InventoryMoldLoc(Shape * shape)
      : MoldLoc("inventory") {
      if (shape != nullptr)
        cout << "    Pull " << shape->getName() << " mold from inventory." << endl;
    }
  };

  class SisterCompanyMoldLoc : public MoldLoc {
  public:
    SisterCompanyMoldLoc(Mold * mold, Shape * shape)
      : MoldLoc("sisterCompany") {
      if (shape != nullptr)
        cout << "    Borrow " << shape->getName() << " mold from sister company." << endl;
    }
  };

  class PurchaseMoldLoc : public MoldLoc {
  public:
    PurchaseMoldLoc(Mold * mold, Shape * shape)
      : MoldLoc("purchase") {
      if (shape != nullptr)
        cout << "    Acquire " << shape->getName() << " mold via purchase." << endl;
    }
  };

  class MillMoldLoc : public MoldLoc {
  public:
    MillMoldLoc(Mold * mold, Finish * finish, Shape * shape)
      : MoldLoc("mill") {
      if (shape != nullptr)
        cout << "    Create " << shape->getName() << " mold from mill with "
             << mold->cavities() << " cavities:" << endl;
      auto milltool = MillTool::get(mold, finish);
      milltool->mill(mold, finish, shape);
    }
  };

  tuple<unique_ptr<MoldLoc>, unique_ptr<Shape>>
  MoldLoc::get(const string & name, Mold * mold, Finish * finish, unique_ptr<Shape> && shape) {
    unique_ptr<MoldLoc> moldloc;
    if (name == "inventory" && shape) {
      moldloc = make_unique<InventoryMoldLoc>(shape.get());
    } else if (name == "sisterCompany" && shape) {
      moldloc = make_unique<SisterCompanyMoldLoc>(mold, shape.get());
    } else if (name == "purchase" && shape) {
      moldloc = make_unique<PurchaseMoldLoc>(mold, shape.get());
    } else if (name == "mill" && shape) {
      moldloc = make_unique<MillMoldLoc>(mold, finish, shape.get());
    } else {
      cout << "    <>Can't find place |" << name << "| to get |"
           << (shape ? shape->getName() : "")
           << "| mold from, defaulting to duck from inventory." << endl;
      moldloc = make_unique<InventoryMoldLoc>(nullptr);
      shape = Shape::get("duck");
    }
    return make_tuple(move(moldloc), move(shape));
  }


  class Tag : public Object {
  public:
    static unique_ptr<Tag> get(const vector<string> & names) {
      unique_ptr<Tag> tag;
      for (auto it = rbegin(names); it != rend(names); ++it) {
        auto name = *it;
        unique_ptr<Tag> tag2;
        if (name == "ModelNumber") {
          tag = make_unique<Tag>(name, 2, move(tag));
        } else if (name == "Country") {
          tag = make_unique<Tag>(name, 2, move(tag));
        } else if (name == "Date") {
          tag = make_unique<Tag>(name, 2, move(tag));
        } else if (name == "IncCounter") {
          tag = make_unique<Tag>(name, 4, move(tag));
        } else if (name == "PartNumber") {
          tag = make_unique<Tag>(name, 2, move(tag));
        } else if (name == "RecycleCode") {
          tag = make_unique<Tag>(name, 6, move(tag));
        }
      }
      return tag;
    }

    Tag(const string & name, int width, unique_ptr<Tag> && tag)
      : Object(name), width_(width), next_(move(tag)) {
    }

    virtual string getName() const override {
      if (next_)
        return Object::getName() + " " + next_->getName();
      return Object::getName() + " ";
    }

    int width() {
      if (next_)
        return width_ + next_->width();
      return width_;
    }

  private:
    const int width_;
    unique_ptr<Tag> next_;
  };


  class Imf {
  public:
    Imf() {
      initialize();
    }

    void initialize() {
      ijm_ = Ijm::get();
      mold_ = Mold::get();
      conveyorBelt_ = ConveyorBelt::get();
      package_ = Package::get();
    }

    void processOrder(map<string, string> & order) {
      auto plastic = Plastic::get(getOrderItem(order, "plastic"));
      auto orderSize = processSize(order);
      auto packager = Packager::get(getOrderItem(order, "packager"));
      auto stuffer = Stuffer::get(getOrderItem(order, "stuffer"));

      auto ijm = ijm_->setup(orderSize);
      auto mold = mold_->setup(orderSize);
      auto belt = conveyorBelt_->setup(orderSize);
      auto package = package_->setup(orderSize);

      cout << "  Setup injection line for " << (orderSize / mold->cavities()) << " run with "
        << packager->getName() << " packager and " << stuffer->desc() << " stuffing:" << endl;

      cout << "    "
        << ijm->getName() << " - "
        << mold->getName() << "(" << mold->cavities() << ") - "
        << belt->getName() << " conveyer belt - "
        << package->getName() << endl;

      cout << "  Process order." << endl;

      // Shape and mold location
      auto shape = Shape::get(getOrderItem(order, "mold"));
      auto finish = Finish::get(getOrderItem(order, "finish"));
      auto moldLocShape = MoldLoc::get(getOrderItem(order, "moldLoc"),
                                       mold,
                                       finish.get(),
                                       move(shape));
      auto moldLoc = move(get<0>(moldLocShape));
      shape = move(get<1>(moldLocShape));

      plastic->setVolume(shape->getCavitySize());

      // Tags
      auto tags = Tag::get(tokenize(getOrderItem(order, "tags")));
      cout << "    Insert tags [" << (tags ? tags->getName() : "")
        << "] of width " << (tags ? tags->width() : 0) << "/20 mm." << endl;

      cout << "    Load plastic, color, and additive bins." << endl;

      // Color
      auto color = Color::get(getOrderItem(order, "color"));
      color->setVolume(shape->getCavitySize() / 10);
      auto nextVol = plastic->setNext(move(color));

      // Additives
      for (auto & n : Additive::getNames()) {
        auto volstr = getOrderItem(order, n);
        if (!volstr.empty()) {
          int volume;
          istringstream(volstr) >> volume;
          nextVol = nextVol->setNext(Additive::get(n, volume));
        }
      }

      // Recipe
      cout << "      Recipe: ";
      cout << "Total = " << (plastic->process() * mold->cavities()) << "." << endl;

      // Shipping
      cout << "    Ship to \"" << getOrderItem(order, "address") << "\"" << endl;
    }

  private:
    int processSize(map<string, string> & order) {
      int size{0};
      auto it = order.find("size");
      if (it != end(order)) {
        istringstream(it->second) >> size;
        if (size > 200000) {
          cout << "  <>Size too large |" << size << "| defaulting to HugeOrder of 200000." << endl;
          size = 200000;
        }
      }
      if (size == 0) {
        cout << "  <>No size specified, defaulting to 100." << endl;
        size = 100;
      }
      return size;
    }

    string getOrderItem(map<string, string> & order, const string & key) {
      auto it = order.find(key);
      return it != end(order) ? it->second : "";
    }

    vector<string> tokenize(string str) {
      vector<char> tok(begin(str), end(str));
      tok.push_back('\0');

      vector<string> tokens;
      for (auto t = strtok(tok.data(), " "); t != nullptr; t = strtok(nullptr, " "))
        tokens.push_back(t);

      return tokens;
    }

    unique_ptr<Ijm> ijm_;
    unique_ptr<Mold> mold_;
    unique_ptr<ConveyorBelt> conveyorBelt_;
    unique_ptr<Package> package_;
  };


  void process(map<string, string>& order) {
    Imf imf;
    imf.processOrder(order);
  }

  pair<string, string> parse(string line) {
    char key[83];
    char val[83] = {0};

    sscanf(line.c_str(), "%s", key);

    const char* equalSign = strchr(line.c_str(), '=');
    string value = "";
    if (equalSign) {	// tags = sam i am
      const char*	nextToken = equalSign += 2;
      while (nextToken) {
        sscanf(nextToken, "%s", val);
        value += val;
        nextToken = strchr(nextToken + 1, ' ');
        value += " ";
      }
      value.erase(value.length() - 1, 1);
    }

    return make_pair(key, value);
  }

  map<string, string> getCompleteOrder(FILE* orderFilePtr) {
    map<string, string> order;
    char line[80 + 3];
    pair<string, string>	keyValue;

    while (fgets(line, 80, orderFilePtr)) {
      cout << line;
      if (strstr(line, "endOfOrder")) {
        return(order);
      } else {
        keyValue = parse(line);
        string key = keyValue.first;
        if (strchr(key.c_str(), ':'))	// Skip left justified order number.
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

    for (;;) {	// Get and process each order.
      map<string, string> order = getCompleteOrder(orderFilePtr);
      if (order.size() == 0)
        break;
      process(order);
    }
  }

}

#endif /* DP4_SRC_STUDENTS_JEFF_H_ */
