/*
 * rohit.h
 *
 *  Created on:
 *      Author:
 *
 *  Project: Intro to Design Patterns Pilot class.
 */
#define DP4_SRC_STUDENTS_ROHIT_H_	// Used shared_ptr.
#ifndef DP4_SRC_STUDENTS_ROHIT_H_
#define DP4_SRC_STUDENTS_ROHIT_H_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

namespace final_rohit_file {

const bool on = false;	// Useful macro to turn dtor instrumentation on/off.
#define DTOR(x) if(on) { cout << x; }

// Additional instrumentations specialized for base as well as derived classes.
#define DTOR_BASE(x) if(on) { cout << x << endl; }
#define DTOR_DERIVED(x) if(on) { cout << x << " "; }

using namespace std;

// Utility function to return whether two strings match irrespective of case differences.
bool matches( const string& str, const string& match )
{
    return ( _strcmpi( str.c_str(), match.c_str() ) == 0 );
}

// Utility function to return whether a key exists in an order or not.
bool keyExists( const string& key, map<string, string>& order )
{
    return ( order.find( key ) != order.end() );
}

// Utility function to convert a string to lowercase.
string toLower( const string& str )
{
    string lower( str );
    transform( lower.begin(), lower.end(), lower.begin(), ::tolower );
    return lower;
}

// Split a string into components separated by the given delimeter.
// Source: https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s07.html
void splitString( const string& s, char c, vector<string>& v )
{
    string::size_type i = 0;
    string::size_type j = s.find( c );

    while( j != string::npos )
    {
        v.push_back( s.substr( i, j - i ) );
        i = ++j;
        j = s.find( c, j );

        if( j == string::npos )
            v.push_back( s.substr( i, s.length( ) ) );
    }

    // Add the string itself if nothing was added to the vector.
    if( v.empty() )
        v.push_back( s );
}

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

// NOTE: Adding OzoneWash here to keep it along side the other cleaning classes.
class OzoneWash
{
public: ~OzoneWash() { DTOR( "~OzoneWash " ); }
        void clean()
        {
            cout << "    Clean synthetic mold: ozone wash.\n";
        }
};

}

namespace abstract_factory
{// DP 10.

    // Abstract plastic class.
    class Plastic
    {
    public:

        // Ejection mechanism enumeration.
        enum Ejection
        {
            PROGRESSIVE,
            SMOOTH,
            SHOCK
        };

        // No default ctor and default implementation for all other predefined functions.
        Plastic( ) = delete;
        Plastic( const Plastic& ) = default;
        Plastic& operator=( const Plastic& ) = default;

        // Param ctor which sets the heating and cooling temperatures as well as the injection PSI.
        Plastic(
            const unsigned heat,
            const unsigned cool,
            const unsigned injectPSI,
            const Ejection ejection,
            const string name,
            const string familyName = "" ) :
            heatTemp( heat ),
            coolTemp( cool ),
            injectionPsi( injectPSI ),
            eject( ejection ),
            plasticName( name ),
            plasticFamilyName(
                familyName.empty() ?
                name :
                familyName )
        {
        }

        // Mandatory virtual dtor.
        virtual ~Plastic( )
        {
            DTOR_BASE( "~Plastic" );
        }

        // Cleaning method. Must be implemented by all plastic implementations.
        virtual void clean( ) = 0;

        // Injection cycle.
        void injectionCycle( )
        {
            cout    << "      Close - heat to "
                    << heatTemp
                    << " - inject at "
                    << injectionPsi
                    << " PSI - cool to "
                    << coolTemp
                    << " - separate - ";
            switch( eject )
            {
            case PROGRESSIVE:
                progressiveEject( );
                break;

            case SMOOTH:
                smoothEject( );
                break;

            case SHOCK:
                shockEject();
                break;
            }
            cout << endl;
        }

        // Accessor method for the plastic's name.
        string getName() const { return plasticName; }

        // Accessor method for the plastic's family name.
        string getFamilyName() const { return plasticFamilyName; }

    protected:

        // Progressive ejection mechanism.
        void progressiveEject( )
        {
            cout << "progressive eject.";
        }

        // Smooth ejection mechanism.
        void smoothEject( )
        {
            cout << "smooth eject.";
        }

        // Shock ejection mechanism.
        void shockEject()
        {
            cout << "shock eject.";
        }

        // Heating and cooling temperatures.
        unsigned heatTemp, coolTemp;

        // Injection PSI.
        unsigned injectionPsi;

        // Plastic name.
        string plasticName;

        // Family name of the plastic.
        string plasticFamilyName;

        // Ejection mechanism.
        Ejection eject;
    };
    typedef std::shared_ptr<Plastic> PlasticPtr;

    // ABS plastic.
    class ABS : public Plastic
    {
    public:

        // Default ctor.
        // Sets heating and cooling temperatures as well as injection PSI to predefined values.
        ABS( ) : Plastic( 440, 360, 125, PROGRESSIVE, "ABS" )
        {
        }

        // Default implementation for all other predefined functions.
        ABS( const ABS& ) = default;
        ABS& operator=( const ABS& ) = default;

        // Dtor.
        ~ABS( )
        {
            DTOR_DERIVED( "~ABS" );
        }

        // Cleaning method.
        void clean( ) override
        {
            legacy_classes::CleanABS cleaner;
            cleaner.clean( );
        }
    };

    // PET plastic.
    class PET : public Plastic
    {
    public:

        // No default ctor and default implementation for all other predefined functions.
        PET( ) = delete;
        PET( const PET& ) = default;
        PET& operator=( const PET& ) = default;

        // Param ctor accepts the metal type.
        // Sets heating and cooling temperatures as well as injection PSI to predefined values.
        PET( const string& metalType ) :
            Plastic( 404, 340, 110, SMOOTH, "PET" ),
            metal( metalType )
        {
        }

        // Dtor.
        ~PET( )
        {
            DTOR_DERIVED( "~PET" );
        }

        // Cleaning method depends on the metal type.
        void clean( ) override
        {
            legacy_classes::PETCleanup cleaner;
            if( matches( metal, "Aluminum" ) )
                cleaner.purify( );
            else if( matches( metal, "Steel" ) )
                cleaner.carbonize( );
        }

    protected:

        // Metal type.
        string metal;
    };

    // Abstract synthetics plastic.
    class Synthetics : public Plastic
    {
    public:

        // Default implementation for all other predefined functions.
        Synthetics() = delete;
        Synthetics( const Synthetics& ) = default;
        Synthetics& operator=( const Synthetics& ) = default;

        // Param ctor accepts the polymer name.
        // Sets heating and cooling temperatures as well as injection PSI to predefined values.
        Synthetics( const string name ) : Plastic( 480, 390, 150, SHOCK, name, "Synthetics" )
        {
        }

        // Dtor.
        virtual ~Synthetics()
        {
            DTOR_DERIVED( "~Synthetics" );
        }

        // Cleaning method.
        virtual void clean() = 0;
    };

    // Cleaning method for Poly plastics.Polymer plastics may use this default cleaning method if needed.
    // Note that this function has been defined inspite of being pure virtual so that it forces derived
    // classes to implement this method (so that they don't forget abou it) but provides a default
    // implementation that can be used.
    void Synthetics::clean()
    {
        legacy_classes::OzoneWash cleaner;
        cleaner.clean();
    }

    // Styrene.
    class Styrene : public Synthetics
    {
    public:

        // Default implementation for all other predefined functions.
        Styrene( const Styrene& ) = default;
        Styrene& operator=( const Styrene& ) = default;

        // Param ctor accepts the metal type.
        // Sets heating and cooling temperatures as well as injection PSI to predefined values.
        Styrene() : Synthetics( "Styrene" )
        {
        }

        // Dtor.
        ~Styrene()
        {
            DTOR_DERIVED( "~Styrene" );
        }

        // Cleaning method depends on the metal type.
        void clean() override
        {
            Synthetics::clean();
        }
    };

    // Nylon66.
    class Nylon66 : public Synthetics
    {
    public:

        // Default implementation for all other predefined functions.
        Nylon66( const Nylon66& ) = default;
        Nylon66& operator=( const Nylon66& ) = default;

        // Default ctor sets the name.
        Nylon66() : Synthetics( "Nylon66" )
        {
        }

        // Dtor.
        ~Nylon66()
        {
            DTOR_DERIVED( "~Nylon66" );
        }

        // Cleaning method depends on the metal type.
        void clean() override
        {
            Synthetics::clean();
        }
    };

    // Abstract polymer plastic.
    class Poly : public Plastic
    {
    public:

        // Default implementation for all other predefined functions.
        Poly( ) = delete;
        Poly( const Poly& ) = default;
        Poly& operator=( const Poly& ) = default;

        // Param ctor accepts the polymer name.
        // Sets heating and cooling temperatures as well as injection PSI to predefined values.
        Poly( const string name ) : Plastic( 350, 290, 90, SMOOTH, name, "Poly" )
        {
        }

        // Dtor.
        virtual ~Poly( )
        {
            DTOR_DERIVED( "~Poly" );
        }

        // Cleaning method.
        virtual void clean( ) = 0;
    };

    // Cleaning method for Poly plastics. Polymer plastics may use this default cleaning method if needed.
    // Note that this function has been defined inspite of being pure virtual so that it forces derived
    // classes to implement this method (so that they don't forget abou it) but provides a default
    // implementation that can be used.
    void Poly::clean( )
    {
        legacy_classes::CleanPolys cleaner;
        cleaner.prepForReuse( );
    }

    // Polypropylene polymer plastic.
    class Polypropylene : public Poly
    {
    public:

        // Default ctor. Uses default heating and cooling temperatures as well as injection PSI.
        Polypropylene( ) : Poly( "Polypropylene" )
        {
        }

        // Default implementation for all other predefined functions.
        Polypropylene( const Polypropylene& ) = default;
        Polypropylene& operator=( const Polypropylene& ) = default;

        // Dtor.
        ~Polypropylene( )
        {
            DTOR_DERIVED( "~Polypropylene" );
        }

        // Cleaning method. Use default base poly implementation.
        void clean( ) override
        {
            Poly::clean( );
        }
    };

    // Polyethelene polymer plastic.
    class Polyethelene : public Poly
    {
    public:

        // Default ctor. Uses default heating and cooling temperatures as well as injection PSI.
        Polyethelene( ) : Poly( "Polyethelene" )
        {
        }

        // Default implementation for all other predefined functions.
        Polyethelene( const Polyethelene& ) = default;
        Polyethelene& operator=( const Polyethelene& ) = default;

        // Dtor.
        ~Polyethelene( )
        {
            DTOR_DERIVED( "~Polyethelene" );
        }

        // Cleaning method. Use default base poly implementation.
        void clean( ) override
        {
            Poly::clean( );
        }
    };

    // Plastic factory method.
    // TODO: Need a good way to validate that nullptr is not passed in when trying to create a Styrene.
    PlasticPtr makePlastic( const string& plasticType, const string& metalType = "" )
    {
        if( matches( plasticType, "ABS" ) )
        {
            return PlasticPtr( new ABS );
        }
        else if( matches( plasticType, "Polypropylene" ) )
        {
            return PlasticPtr( new Polypropylene );
        }
        else if( matches( plasticType, "Polyethelene" ) )
        {
            return PlasticPtr( new Polyethelene );
        }
        else if( matches( plasticType, "PET" ) )
        {
            if( metalType.empty( ) )
                throw exception( string( "metal type must be provided to create a PET plastic\n" ).c_str() );
            else
                return PlasticPtr( new PET( metalType ) );
        }
        else if( matches( plasticType, "Styrene" ) )
        {
            return PlasticPtr( new Styrene );
        }
        else if( matches( plasticType, "Nylon66" ) )
        {
            return PlasticPtr( new Nylon66 );
        }
        else
        {
            throw exception( string( "Unsupported plastic type: " + plasticType ).c_str() );
        }
    }

    // Seam point - add another type1 member.
    // Seam point - add another type2 member.
    // Seam point - add another type3 member.
    // ...

    // Seam point - add another family.

    // Metal base class.
    class Metal
    {
    public:

        // No default ctor and default implementation for other automatically generated funcs.
        Metal( ) = delete;
        Metal( const Metal& ) = default;
        Metal& operator=( const Metal& ) = default;

        // Param ctor accepts the metal name.
        Metal( const string& name ) :
            metalName( name ),
            lowercaseMetalName( toLower( metalName ) )
        {
        }

        // Mandatory virtual dtor.
        virtual ~Metal( )
        {
            DTOR_BASE( "~Metal" );
        }

        // Gets the metal's name.
        string getMetalName( ) const { return metalName; }

        // Get the metal name in lowercase.
        string getLowercaseMetalName() const { return lowercaseMetalName; }

    protected:

        // Metal name and its lowercase variant.
        string metalName, lowercaseMetalName;
    };
    typedef std::shared_ptr<Metal> MetalPtr;

    // Aluminum.
    class Aluminum : public Metal
    {
    public:

        // Default ctor sets the metal name.
        Aluminum( ) : Metal( "Aluminum" )
        {
        }

        // Default implementations for autogenerated funcs.
        Aluminum( const Aluminum& ) = default;
        Aluminum& operator=( const Aluminum& ) = default;

        // Dtor.
        ~Aluminum( )
        {
            DTOR_DERIVED( "~Aluminum" );
        }

    };

    // Steel.
    class Steel : public Metal
    {
    public:

        // Default ctor sets the metal name.
        Steel( ) : Metal( "Steel" )
        {
        }

        // Default implementations for autogenerated funcs.
        Steel( const Steel& ) = default;
        Steel& operator=( const Steel& ) = default;

        // Dtor.
        ~Steel( )
        {
            DTOR_DERIVED( "~Steel" );
        }

    };

    // Metal factory.
    MetalPtr makeMetal( const string& metalType )
    {
        if( matches( metalType, "Aluminum" ) )
        {
            return MetalPtr( new Aluminum );
        }
        else if( matches( metalType, "Steel" ) )
        {
            return MetalPtr( new Steel );
        }
        else
        {
            throw exception( string( "Unsupported metal type: " + metalType ).c_str( ) );
        }
    }

    // MoldShape classes.

    // Abstract mold base class.
    class MoldShape
    {
    public:

        // No default ctor and default implementation for other automatically generated funcs.
        MoldShape( ) = delete;
        MoldShape( const MoldShape& ) = default;
        MoldShape& operator=( const MoldShape& ) = default;

        // Param ctor accepts the mold name and volume in cc.
        MoldShape( const string& name, const unsigned ccVol1 ) :
            moldName( name ),
            lowercaseMoldName( toLower( moldName ) ),
            ccVol( ccVol1 )
        {
        }

        // Mandatory virtual dtor.
        virtual ~MoldShape( )
        {
            DTOR_BASE( "~MoldShape" );
        }

        // Accessor method for the mold shape name.
        string getMoldShapeName( ) const { return moldName; }

        // Accessor method for the mold shape name in lowercase.
        string getLowercaseMoldShapeName() const { return lowercaseMoldName; }

        // Accessor method for the vol in cc.
        unsigned getccVol( ) const { return ccVol; }

    protected:

        // MoldShape name and it's lowercase variant.
        string moldName, lowercaseMoldName;

        // Vol in cc.
        unsigned ccVol;
    };
    typedef std::shared_ptr<MoldShape> MoldShapePtr;

    // Duck mold.
    class DuckMold : public MoldShape
    {
    public:

        // Default implementation for other automatically generated funcs.
        DuckMold( const DuckMold& ) = default;
        DuckMold& operator=( const DuckMold& ) = default;

        // Param ctor accepts the mold name and volume in cc.
        DuckMold( ) : MoldShape( "Duck", 35 )
        {
        }

        // Dtor.
        ~DuckMold( )
        {
            DTOR_DERIVED( "~DuckMold" );
        }
    };

    // Car mold.
    class CarMold : public MoldShape
    {
    public:

        // Default implementation for other automatically generated funcs.
        CarMold( const CarMold& ) = default;
        CarMold& operator=( const CarMold& ) = default;

        // Param ctor accepts the mold name and volume in cc.
        CarMold( ) : MoldShape( "Car", 40 )
        {
        }

        // Dtor.
        ~CarMold( )
        {
            DTOR_DERIVED( "~CarMold" );
        }
    };

    // Hero mold.
    class HeroMold : public MoldShape
    {
    public:

        // Default implementation for other automatically generated funcs.
        HeroMold( const HeroMold& ) = default;
        HeroMold& operator=( const HeroMold& ) = default;

        // Param ctor accepts the mold name and volume in cc.
        HeroMold( ) : MoldShape( "Hero", 50 )
        {
        }

        // Dtor.
        ~HeroMold( )
        {
            DTOR_DERIVED( "~HeroMold" );
        }
    };

    // Dino mold.
    class DinoMold : public MoldShape
    {
    public:

        // Default implementation for other automatically generated funcs.
        DinoMold( const DinoMold& ) = default;
        DinoMold& operator=( const DinoMold& ) = default;

        // Param ctor accepts the mold name and volume in cc.
        DinoMold() : MoldShape( "Dino", 30 )
        {
        }

        // Dtor.
        ~DinoMold()
        {
            DTOR_DERIVED( "~DinoMold" );
        }
    };

    // MoldShape factory method.
    MoldShapePtr makeMoldShape( const string& moldType )
    {
        if( matches( moldType, "Duck" ) )
        {
            return MoldShapePtr( new DuckMold );
        }
        else if( matches( moldType, "Car" ) )
        {
            return MoldShapePtr( new CarMold );
        }
        else if( matches( moldType, "Hero" ) )
        {
            return MoldShapePtr( new HeroMold );
        }
        else if( matches( moldType, "Dino" ) )
        {
            return MoldShapePtr( new DinoMold );
        }
        else
        {
            throw exception( string( "Unsupported mold shape: " + moldType ).c_str( ) );
        }
    }

    // Abstract milling tool base class.
    class MillingTool
    {
    public:

        // No default ctor and default implementation for other automatically generated funcs.
        MillingTool( ) = delete;
        MillingTool( const MillingTool& ) = default;
        MillingTool& operator=( const MillingTool& ) = default;

        // Param ctor accepts the tool name and milling techniques.
        MillingTool(
            const string& name,
            const string& tech,
            const MetalPtr& pMetal,
            const MoldShapePtr& pShape,
            const unsigned numShapes,
            const string& finish ) :
            toolName( name ),
            toolTech( tech ),
            pMillMetal( pMetal ),
            pMoldShape( pShape ),
            nShapes( numShapes ),
            millFinish( finish )
        {
        }

        // Mandatory virtual dtor.
        virtual ~MillingTool()
        {
            DTOR_BASE( "~MillingTool" );
        }

        // Display method that all derived classes must implement.
        virtual void displayProcess() = 0;

        // Accessor method for the tool's name.
        string getToolName() const { return toolName; }

        // Accessor method for the tool's techniques.
        string getToolTechniques() const { return toolTech; }

    protected:

        // Milling tool name.
        string toolName;

        // Milling tool techniques.
        string toolTech;

        // Milling metal.
        MetalPtr pMillMetal;

        // Mold shape.
        MoldShapePtr pMoldShape;

        // No. of shapes.
        unsigned nShapes;

        // Milling finish.
        string millFinish;
    };
    typedef std::shared_ptr<MillingTool> MillingToolPtr;

    // Default implementation of displayProcess that derived classes can use if necessary.
    void MillingTool::displayProcess()
    {
        cout    << "      using "
                << getToolName()
                << " tools "
                << "(" << getToolTechniques() << ") to mill "
                << pMillMetal->getLowercaseMetalName()
                << " block into "
                << nShapes
                << " "
                << pMoldShape->getLowercaseMoldShapeName()
                << " shapes with "
                << millFinish
                << " finish.\n";
    }

    // HighCarbon milling tool.
    class HighCarbonTool : public MillingTool
    {
    public:

        // No default ctor and default implementation for other automatically generated funcs.
        HighCarbonTool() = delete;
        HighCarbonTool( const HighCarbonTool& ) = default;
        HighCarbonTool& operator=( const HighCarbonTool& ) = default;

        // Param ctor sets the tool name, milling techniques, no. of shapes and finish.
        // The metal is set to Aluminum as that is what HighCarbon is suited for.
        HighCarbonTool(
            const MoldShapePtr& pShape,
            const unsigned numShapes,
            const string& finish ) :
            MillingTool(
                "HighCarbon",
                "drill, cut, and high speed grind",
                makeMetal( "Aluminum" ),
                pShape,
                numShapes,
                finish )
        {
        }

        // Dtor.
        ~HighCarbonTool()
        {
            DTOR_DERIVED( "~HighCarbonTool" );
        }

        // Display method.
        void displayProcess() override
        {
            MillingTool::displayProcess();
        }
    };

    // Carbide milling tool.
    class CarbideTool : public MillingTool
    {
    public:

        // No default ctor and default implementation for other automatically generated funcs.
        CarbideTool( ) = delete;
        CarbideTool( const CarbideTool& ) = default;
        CarbideTool& operator=( const CarbideTool& ) = default;

        // Param ctor sets the tool name, milling techniques, no. of shapes and finish.
        // The metal is set to Steel as that is what Carbide is suited for.
        CarbideTool(
            const MoldShapePtr& pShape,
            const unsigned numShapes,
            const string& finish ) :
            MillingTool(
            "Carbide",
            "high speed drill, cross cut, and layer grind",
            makeMetal( "Steel" ),
            pShape,
            numShapes,
            finish )
        {
        }

        // Dtor.
        ~CarbideTool()
        {
            DTOR_DERIVED( "~CarbideTool" );
        }

        // Display method.
        void displayProcess( ) override
        {
            MillingTool::displayProcess( );
        }
    };

    // DiamondTipped milling tool.
    class DiamondTippedTool : public MillingTool
    {
    public:

        // No default ctor and default implementation for other automatically generated funcs.
        DiamondTippedTool() = delete;
        DiamondTippedTool( const DiamondTippedTool& ) = default;
        DiamondTippedTool& operator=( const DiamondTippedTool& ) = default;

        // Param ctor sets the tool name, milling techniques, no. of shapes and finish.
        // The metal is set to Steel as that is what Carbide is suited for.
        DiamondTippedTool(
            const MoldShapePtr& pShape,
            const unsigned numShapes,
            const string& finish ) :
            MillingTool(
            "DiamondTipped",
            "precision drill, oil cooled cut, and cartoid grind",
            makeMetal( "Steel" ),
            pShape,
            numShapes,
            finish )
        {
        }

        // Dtor.
        ~DiamondTippedTool()
        {
            DTOR_DERIVED( "~DiamondTippedTool" );
        }

        // Display method.
        void displayProcess() override
        {
            MillingTool::displayProcess();
        }
    };

    // Milling tool factory.
    MillingToolPtr makeMillingTool(
        const MetalPtr& pMetal,
        const MoldShapePtr& pShape,
        const unsigned numShapes,
        const string& finish )
    {
        if( matches( finish, "satin" ) )
        {
            return MillingToolPtr( new DiamondTippedTool( pShape, numShapes, finish ) );
        }
        else if( matches( pMetal->getMetalName(), "Aluminum" ) )
        {
            return MillingToolPtr( new HighCarbonTool( pShape, numShapes, finish ) );
        }
        else if( matches( pMetal->getMetalName(), "Steel" ) )
        {
            return MillingToolPtr( new CarbideTool( pShape, numShapes, finish ) );
        }
        else
        {
            throw exception( string( "Unsupported metal type: " + pMetal->getMetalName() ).c_str( ) );
        }
    }

    // Abstract tag base class.
    class Tag
    {
    public:

        // No default ctor and default implementation for other automatically generated funcs.
        Tag( ) = delete;
        Tag( const Tag& ) = default;
        Tag& operator=( const Tag& ) = default;

        // Param ctor accepts the tag name and width.
        Tag( const string& name, const unsigned width ) :
            tagName( name ),
            tagWidth( width )
        {
        }

        // Mandatory virtual dtor.
        virtual ~Tag( )
        {
            DTOR_BASE( "~Tag" );
        }

        // Accessor method for the tag's name.
        string getTagName( ) const { return tagName; }

        // Accessor method for the tag's width.
        unsigned getTagWidth( ) const { return tagWidth; }

    protected:

        // Tag name.
        string tagName;

        // Tag width.
        unsigned tagWidth;
    };
    typedef std::shared_ptr<Tag> TagPtr;

    // Model number tag.
    class ModelNumberTag : public Tag
    {
    public:

        // Default implementation for other automatically generated funcs.
        ModelNumberTag( const ModelNumberTag& ) = default;
        ModelNumberTag& operator=( const ModelNumberTag& ) = default;

        // Default ctor sets the tag name and width.
        ModelNumberTag( ) : Tag( "ModelNumber", 2 )
        {
        }

        // Dtor.
        ~ModelNumberTag( )
        {
            DTOR_DERIVED( "~ModelNumberTag" );
        }
    };

    // Country tag.
    class CountryTag : public Tag
    {
    public:

        // Default implementation for other automatically generated funcs.
        CountryTag( const CountryTag& ) = default;
        CountryTag& operator=( const CountryTag& ) = default;

        // Default ctor sets the tag name and width.
        CountryTag( ) : Tag( "Country", 2 )
        {
        }

        // Dtor.
        ~CountryTag( )
        {
            DTOR_DERIVED( "~CountryTag" );
        }
    };

    // Date tag.
    class DateTag : public Tag
    {
    public:

        // Default implementation for other automatically generated funcs.
        DateTag( const DateTag& ) = default;
        DateTag& operator=( const DateTag& ) = default;

        // Default ctor sets the tag name and width.
        DateTag( ) : Tag( "Date", 2 )
        {
        }

        // Dtor.
        ~DateTag( )
        {
            DTOR_DERIVED( "~DateTag" );
        }
    };

    // IncCounter tag.
    class IncCounterTag : public Tag
    {
    public:

        // Default implementation for other automatically generated funcs.
        IncCounterTag( const IncCounterTag& ) = default;
        IncCounterTag& operator=( const IncCounterTag& ) = default;

        // Default ctor sets the tag name and width.
        IncCounterTag() : Tag( "IncCounter", 4 )
        {
        }

        // Dtor.
        ~IncCounterTag()
        {
            DTOR_DERIVED( "~IncCounterTag" );
        }
    };

    // PartNumber tag.
    class PartNumberTag : public Tag
    {
    public:

        // Default implementation for other automatically generated funcs.
        PartNumberTag( const PartNumberTag& ) = default;
        PartNumberTag& operator=( const PartNumberTag& ) = default;

        // Default ctor sets the tag name and width.
        PartNumberTag() : Tag( "PartNumber", 2 )
        {
        }

        // Dtor.
        ~PartNumberTag()
        {
            DTOR_DERIVED( "~PartNumberTag" );
        }
    };

    // RecycleCode tag.
    class RecycleCodeTag : public Tag
    {
    public:

        // Default implementation for other automatically generated funcs.
        RecycleCodeTag( const RecycleCodeTag& ) = default;
        RecycleCodeTag& operator=( const RecycleCodeTag& ) = default;

        // Default ctor sets the tag name and width.
        RecycleCodeTag() : Tag( "RecycleCode", 6 )
        {
        }

        // Dtor.
        ~RecycleCodeTag()
        {
            DTOR_DERIVED( "~RecycleCodeTag" );
        }
    };

    // Tag factory method.
    TagPtr makeTag( const string& tagType )
    {
        if( matches( tagType, "ModelNumber" ) )
        {
            return TagPtr( new ModelNumberTag );
        }
        else if( matches( tagType, "Country" ) )
        {
            return TagPtr( new CountryTag );
        }
        else if( matches( tagType, "Date" ) )
        {
            return TagPtr( new DateTag );
        }
        else if( matches( tagType, "IncCounter" ) )
        {
            return TagPtr( new IncCounterTag );
        }
        else if( matches( tagType, "PartNumber" ) )
        {
            return TagPtr( new PartNumberTag );
        }
        else if( matches( tagType, "RecycleCode" ) )
        {
            return TagPtr( new RecycleCodeTag );
        }
        else
        {
            throw exception( string( "Unsupported tag type: " + tagType ).c_str( ) );
        }
    }
}

namespace adapter {			// DP 2.

// Seam point - add another interface.

}

namespace strategy {		// DP 1.

    using namespace abstract_factory;

    // MoldShape procurement strategy abstract base class.
    class MoldProcurement
    {
    public:

        // No default ctor and default implementation for all other predefined functions.
        MoldProcurement( ) = delete;
        MoldProcurement( const MoldProcurement& ) = default;
        MoldProcurement& operator=( const MoldProcurement& ) = default;

        // Param ctor accepts the mold shape which has to be procured
        // as well as its location.
        MoldProcurement( const MoldShapePtr& pMold, const string& moldLoc ) :
            pMoldShape( pMold ), moldLocation( moldLoc )
        {
        }

        // Mandatory virtual dtor.
        virtual ~MoldProcurement()
        {
            DTOR_BASE( "~MoldProcurement" );
        }

        // Accessor method for the mold shape.
        MoldShapePtr getMoldShape() const { return pMoldShape; }

        // Accessor method for the mold location.
        string getMoldLocation() const { return moldLocation; }

        // Display strategy method that all derived classes must implement.
        virtual void displayStrategy() = 0;

    protected:

        // Mold shape.
        MoldShapePtr pMoldShape;

        // Mold location.
        string moldLocation;
    };
    typedef std::shared_ptr<MoldProcurement> MoldProcurementPtr;

    // Default mold procurement strategy.
    class DefaultMoldProcurement : public MoldProcurement
    {
    public:

        // Default implementation for all other predefined functions.
        DefaultMoldProcurement( const DefaultMoldProcurement& ) = default;
        DefaultMoldProcurement& operator=( const DefaultMoldProcurement& ) = default;

        // Default ctor sets the mold shape to Duck and the mold location to the inventory.
        DefaultMoldProcurement() : MoldProcurement( makeMoldShape( "Duck" ), "inventory" )
        {
        }

        // Dtor.
        ~DefaultMoldProcurement( )
        {
            DTOR_DERIVED( "~DefaultMoldProcurement" );
        }

        // Display strategy method.
        void displayStrategy()
        {
            cout    << "    <>Can't find place || to get || mold from, defaulting to "
                    << pMoldShape->getLowercaseMoldShapeName()
                    << " from "
                    << moldLocation
                    << ".\n";
        }
    };

    // Inventory mold procurement strategy.
    class InventoryMoldProcurement : public MoldProcurement
    {
    public:

        // No default ctor and default implementation for all other predefined functions.
        InventoryMoldProcurement( const InventoryMoldProcurement& ) = default;
        InventoryMoldProcurement& operator=( const InventoryMoldProcurement& ) = default;

        // Param ctor sets the mold shape and the mold location.
        InventoryMoldProcurement( const MoldShapePtr& pMoldShape, const string& moldLoc ) :
            MoldProcurement( pMoldShape, moldLoc )
        {
        }

        // Dtor.
        ~InventoryMoldProcurement( )
        {
            DTOR_DERIVED( "~InventoryMoldProcurement" );
        }

        // Display strategy method.
        void displayStrategy( )
        {
            cout    << "    Pull "
                    << pMoldShape->getLowercaseMoldShapeName()
                    << " mold from "
                    << moldLocation
                    << ".\n";
        }
    };

    // Sister company mold procurement strategy.
    class SisterCompanyMoldProcurement : public MoldProcurement
    {
    public:

        // No default ctor and default implementation for all other predefined functions.
        SisterCompanyMoldProcurement( const SisterCompanyMoldProcurement& ) = default;
        SisterCompanyMoldProcurement& operator=( const SisterCompanyMoldProcurement& ) = default;

        // Param ctor sets the mold shape and the mold location.
        SisterCompanyMoldProcurement( const MoldShapePtr& pMoldShape, const string& moldLoc ) :
            MoldProcurement( pMoldShape, moldLoc )
        {
        }

        // Dtor.
        ~SisterCompanyMoldProcurement()
        {
            DTOR_DERIVED( "~SisterCompanyMoldProcurement" );
        }

        // Display strategy method.
        void displayStrategy()
        {
            cout << "    Borrow "
                << pMoldShape->getLowercaseMoldShapeName()
                << " mold from sister company.\n";
        }
    };

    // Purchase mold procurement strategy.
    class PurchaseMoldProcurement : public MoldProcurement
    {
    public:

        // No default ctor and default implementation for all other predefined functions.
        PurchaseMoldProcurement( const PurchaseMoldProcurement& ) = default;
        PurchaseMoldProcurement& operator=( const PurchaseMoldProcurement& ) = default;

        // Param ctor sets the mold shape and the mold location.
        PurchaseMoldProcurement( const MoldShapePtr& pMoldShape, const string& moldLoc ) :
            MoldProcurement( pMoldShape, moldLoc )
        {
        }

        // Dtor.
        ~PurchaseMoldProcurement()
        {
            DTOR_DERIVED( "~PurchaseMoldProcurement" );
        }

        // Display strategy method.
        void displayStrategy()
        {
            cout << "    Acquire "
                << pMoldShape->getLowercaseMoldShapeName()
                << " mold via "
                << moldLocation
                << ".\n";
        }
    };

    // Mill mold procurement strategy.
    class MillMoldProcurement : public MoldProcurement
    {
    public:

        // No default ctor and default implementation for all other predefined functions.
        MillMoldProcurement( const MillMoldProcurement& ) = default;
        MillMoldProcurement& operator=( const MillMoldProcurement& ) = default;

        // Param ctor sets the mold shape, mold location, no. of cavities, mold metal and finish.
        MillMoldProcurement(
            const MoldShapePtr& pMoldShape,
            const string& moldLoc,
            const unsigned numCavities,
            const MetalPtr& pMetal,
            const string& finishType ) :
            MoldProcurement( pMoldShape, moldLoc ),
            nCavities( numCavities ),
            pMoldMetal( pMetal ),
            finish( finishType ),
            pTool( makeMillingTool( pMoldMetal, pMoldShape, nCavities, finish ) )
        {
        }

        // Dtor.
        ~MillMoldProcurement( )
        {
            DTOR_DERIVED( "~MillMoldProcurement" );
        }

        // Display strategy method.
        void displayStrategy()
        {
            cout << "    Create "
                << pMoldShape->getLowercaseMoldShapeName()
                << " mold from "
                << moldLocation
                << " with "
                << nCavities
                << " cavities:\n";
            pTool->displayProcess();
        }

    private:

        // No. of cavities in the mold.
        unsigned nCavities;

        // Mold metal.
        MetalPtr pMoldMetal;

        // Finish type.
        string finish;

        // Milling tool.
        MillingToolPtr pTool;
    };

// Seam point - add another algorithm.

}

namespace observer {		// DP 7.

    using namespace std;

    // Output bin subject class forward declaration.
    class OutputBin;

    // TODO: Modify default ctor of observer base classes to not accept a subject and add a method
    //       to set the subject at a later time so that observers do not rely on a subject being
    //       defined at the time of instantiation.

    // Abstract Observer class.
    class OutputBinObserver
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        OutputBinObserver( ) = delete;
        OutputBinObserver( const OutputBinObserver& ) = default;
        OutputBinObserver& operator=( const OutputBinObserver& ) = default;

        // Param ctor which accepts the OutputBin object that this observer will subscribe to.
        // NOTE: This method will be defined after the OutputBin subject class is defined
        //       as it needs the definition of the subject's public methods.
        OutputBinObserver( OutputBin* pOutputBin, const string name );

        // Dtor unsubscribes this observer from the subject.
        // NOTE: This method will be defined after the OutputBin subject class is defined
        //       as it needs the definition of the subject's public methods.
        virtual ~OutputBinObserver();

        // Update method that all derived classes will have to implement.
        virtual void update() = 0;

        // Accessor method for the observer's name.
        string getObserverName( ) const { return observerName; }

    protected:

        // OutputBin subject.
        OutputBin* pSubject;

        // Name of the observer.
        string observerName;
    };

    // Molding machine observer abstract base class.
    class MoldingMachine : public OutputBinObserver
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        MoldingMachine( ) = delete;
        MoldingMachine( const MoldingMachine& ) = default;
        MoldingMachine& operator=( const MoldingMachine& ) = default;

        // Param ctor which accepts the OutputBin subject as well as the machine's name.
        // The observer name is set to the generic "IJM" so that it can be used in the update method.
        MoldingMachine( OutputBin* pSubject, const string name )
            : OutputBinObserver( pSubject, "IJM" ), machineName( name )
        {
        }

        // Dtor.
        virtual ~MoldingMachine()
        {
            DTOR_DERIVED( "~MoldingMachine" );
        }

        // Update method that all derived classes will have to implement.
        virtual void update() = 0;

        // Accessor method for the machine name.
        string getMachineName() const { return machineName; }

    protected:

        // Machine name.
        string machineName;
    };
    typedef std::shared_ptr<MoldingMachine> MoldingMachinePtr;

    // Base class implementation of the update method that all derived classes can use if necessary.
    void MoldingMachine::update() /*override*/
    {
        OutputBinObserver::update();
    }

    // IJM_110 molding machine.
    class IJM_110 : public MoldingMachine
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        IJM_110( ) = delete;
        IJM_110( const IJM_110& ) = default;
        IJM_110& operator=( const IJM_110& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        IJM_110( OutputBin *pSubject ) :
            MoldingMachine( pSubject, "IJM_110" )
        {
        }

        // Dtor.
        ~IJM_110()
        {
            DTOR_DERIVED( "~IJM_110" );
        }

        // Update method for which the base class implementation should suffice.
        void update() override
        {
            MoldingMachine::update();
        }
    };

    // IJM_120 molding machine.
    class IJM_120 : public MoldingMachine
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        IJM_120( ) = delete;
        IJM_120( const IJM_120& ) = default;
        IJM_120& operator=( const IJM_120& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        IJM_120( OutputBin *pSubject ) :
            MoldingMachine( pSubject, "IJM_120" )
        {
        }

        // Dtor.
        ~IJM_120( )
        {
            DTOR( "~IJM_120" );
        }

        // Update method for which the base class implementation should suffice.
        void update( ) override
        {
            MoldingMachine::update( );
        }
    };

    // IJM_210 molding machine.
    class IJM_210 : public MoldingMachine
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        IJM_210( ) = delete;
        IJM_210( const IJM_210& ) = default;
        IJM_210& operator=( const IJM_210& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        IJM_210( OutputBin *pSubject ) :
            MoldingMachine( pSubject, "IJM_210" )
        {
        }

        // Dtor.
        ~IJM_210( )
        {
            DTOR_DERIVED( "~IJM_210" );
        }

        // Update method for which the base class implementation should suffice.
        void update( ) override
        {
            MoldingMachine::update( );
        }
    };

    // IJM_140 molding machine.
    class IJM_140 : public MoldingMachine
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        IJM_140() = delete;
        IJM_140( const IJM_140& ) = default;
        IJM_140& operator=( const IJM_140& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        IJM_140( OutputBin *pSubject ) :
            MoldingMachine( pSubject, "IJM_140" )
        {
        }

        // Dtor.
        ~IJM_140()
        {
            DTOR_DERIVED( "~IJM_140" );
        }

        // Update method for which the base class implementation should suffice.
        void update() override
        {
            MoldingMachine::update();
        }
    };

    // IJM_220 molding machine.
    class IJM_220 : public MoldingMachine
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        IJM_220() = delete;
        IJM_220( const IJM_220& ) = default;
        IJM_220& operator=( const IJM_220& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        IJM_220( OutputBin *pSubject ) :
            MoldingMachine( pSubject, "IJM_220" )
        {
        }

        // Dtor.
        ~IJM_220()
        {
            DTOR_DERIVED( "~IJM_220" );
        }

        // Update method for which the base class implementation should suffice.
        void update() override
        {
            MoldingMachine::update();
        }
    };

    // IJM_240 molding machine.
    class IJM_240 : public MoldingMachine
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        IJM_240() = delete;
        IJM_240( const IJM_240& ) = default;
        IJM_240& operator=( const IJM_240& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        IJM_240( OutputBin *pSubject ) :
            MoldingMachine( pSubject, "IJM_240" )
        {
        }

        // Dtor.
        ~IJM_240()
        {
            DTOR_DERIVED( "~IJM_240" );
        }

        // Update method for which the base class implementation should suffice.
        void update() override
        {
            MoldingMachine::update();
        }
    };

    // Molding machine factory method.
    MoldingMachinePtr makeMoldingMachine( const string& moldingMachineType, OutputBin* pSubject )
    {
        if( matches( moldingMachineType, "IJM_110" ) )
        {
            return MoldingMachinePtr( new IJM_110( pSubject ) );
        }
        else if( matches( moldingMachineType, "IJM_120" ) )
        {
            return MoldingMachinePtr( new IJM_120( pSubject ) );
        }
        else if( matches( moldingMachineType, "IJM_210" ) )
        {
            return MoldingMachinePtr( new IJM_210( pSubject ) );
        }
        else if( matches( moldingMachineType, "IJM_140" ) )
        {
            return MoldingMachinePtr( new IJM_140( pSubject ) );
        }
        else if( matches( moldingMachineType, "IJM_220" ) )
        {
            return MoldingMachinePtr( new IJM_220( pSubject ) );
        }
        else if( matches( moldingMachineType, "IJM_240" ) )
        {
            return MoldingMachinePtr( new IJM_240( pSubject ) );
        }
        else
        {
            throw exception( string( "Unsupported molding machine type: " + moldingMachineType ).c_str( ) );
        }
    }

    // Conveyer belt observer abstract base class.
    class ConveyerBelt : public OutputBinObserver
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        ConveyerBelt( ) = delete;
        ConveyerBelt( const ConveyerBelt& ) = default;
        ConveyerBelt& operator=( const ConveyerBelt& ) = default;

        // Param ctor which accepts the OutputBin subject as well as the conveyer belt's name.
        // The observer name is set to the generic "Conveyer belt" so that it can be used in the update method.
        ConveyerBelt( OutputBin* pSubject, const string name ) :
            OutputBinObserver( pSubject, "Conveyer belt" ),
            conveyerBeltName(name)
        {
        }

        // Dtor.
        virtual ~ConveyerBelt( )
        {
            DTOR_DERIVED( "~ConveyerBelt" );
        }

        // Update method that all derived classes will have to implement.
        virtual void update( ) = 0;

        // Accessor method for the conveyer belt name.
        string getConveyerBeltName( ) const { return conveyerBeltName; }

    protected:

        // Conveyer belt name.
        string conveyerBeltName;
    };
    typedef std::shared_ptr<ConveyerBelt> ConveyerBeltPtr;

    // Base class implementation of the update method that all derived classes can use if necessary.
    void ConveyerBelt::update( ) /*override*/
    {
        OutputBinObserver::update( );
    }

    // Linear conveyer belt.
    class LinearBelt : public ConveyerBelt
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        LinearBelt( ) = delete;
        LinearBelt( const LinearBelt& ) = default;
        LinearBelt& operator=( const LinearBelt& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        LinearBelt( OutputBin *pSubject ) :
            ConveyerBelt( pSubject, "Linear" )
        {
        }

        // Dtor.
        ~LinearBelt( )
        {
            DTOR_DERIVED( "~LinearBelt" );
        }

        // Update method for which the base class implementation should suffice.
        void update( ) override
        {
            ConveyerBelt::update( );
        }
    };

    // Y-split conveyer belt.
    class Y_Split : public ConveyerBelt
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        Y_Split( ) = delete;
        Y_Split( const Y_Split& ) = default;
        Y_Split& operator=( const Y_Split& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        Y_Split( OutputBin *pSubject ) :
            ConveyerBelt( pSubject, "Y-Split" )
        {
        }

        // Dtor.
        ~Y_Split( )
        {
            DTOR_DERIVED( "~Y_Split" );
        }

        // Update method for which the base class implementation should suffice.
        void update( ) override
        {
            ConveyerBelt::update( );
        }
    };

    // V-level conveyer belt.
    class V_Level : public ConveyerBelt
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        V_Level() = delete;
        V_Level( const V_Level& ) = default;
        V_Level& operator=( const V_Level& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        V_Level( OutputBin *pSubject ) :
            ConveyerBelt( pSubject, "V-Level" )
        {
        }

        // Dtor.
        ~V_Level()
        {
            DTOR_DERIVED( "~V_Level" );
        }

        // Update method for which the base class implementation should suffice.
        void update() override
        {
            ConveyerBelt::update();
        }
    };

    // Conveyer belt factory.
    ConveyerBeltPtr makeConveyerBelt( const string& conveyerBeltType, OutputBin* pSubject )
    {
        if( matches( conveyerBeltType, "Linear" ) )
        {
            return ConveyerBeltPtr( new LinearBelt( pSubject ) );
        }
        else if( matches( conveyerBeltType, "Y-Split" ) )
        {
            return ConveyerBeltPtr( new Y_Split( pSubject ) );
        }
        else if( matches( conveyerBeltType, "V-Level" ) )
        {
            return ConveyerBeltPtr( new V_Level( pSubject ) );
        }
        else
        {
            throw exception( string( "Unsupported conveyer belt type: " + conveyerBeltType ).c_str( ) );
        }
    }

    // Packager observer abstract base class.
    class Packager : public OutputBinObserver
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        Packager( ) = delete;
        Packager( const Packager& ) = default;
        Packager& operator=( const Packager& ) = default;

        // Param ctor which accepts the OutputBin subject as well as the conveyer belt's name.
        // The observer name is set to the generic "Packager" so that it can be used in the update method.
        Packager( OutputBin* pSubject, const string name ) :
            OutputBinObserver( pSubject, "Packager" ),
            packagerName(name)
        {
        }

        // Dtor.
        virtual ~Packager( )
        {
            DTOR_DERIVED( "~Packager" );
        }

        // Update method that all derived classes will have to implement.
        virtual void update( ) = 0;

        // Accessor method for the packager name.
        string getPackagerName( ) const { return packagerName; }

    protected:

        // Packager name.
        string packagerName;

    };
    typedef std::shared_ptr<Packager> PackagerPtr;

    // Base class implementation of the update method that all derived classes can use if necessary.
    void Packager::update( ) /*override*/
    {
        OutputBinObserver::update( );
    }

    // Bulk packager.
    class Bulk : public Packager
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        Bulk( ) = delete;
        Bulk( const Bulk& ) = default;
        Bulk& operator=( const Bulk& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        Bulk( OutputBin *pSubject ) :
            Packager( pSubject, "Bulk" )
        {
        }

        // Dtor.
        ~Bulk( )
        {
            DTOR_DERIVED( "~Bulk" );
        }

        // Update method for which the base class implementation should suffice.
        void update( ) override
        {
            Packager::update( );
        }
    };

    // ShrinkWrap packager.
    class ShrinkWrap : public Packager
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        ShrinkWrap( ) = delete;
        ShrinkWrap( const ShrinkWrap& ) = default;
        ShrinkWrap& operator=( const ShrinkWrap& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        ShrinkWrap( OutputBin *pSubject ) :
            Packager( pSubject, "Bulk" )
        {
        }

        // Dtor.
        ~ShrinkWrap( )
        {
            DTOR_DERIVED( "~ShrinkWrap" );
        }

        // Update method for which the base class implementation should suffice.
        void update( ) override
        {
            Packager::update( );
        }
    };

    // HardPack packager.
    class HardPack : public Packager
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        HardPack( ) = delete;
        HardPack( const HardPack& ) = default;
        HardPack& operator=( const HardPack& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        HardPack( OutputBin *pSubject ) :
            Packager( pSubject, "Bulk" )
        {
        }

        // Dtor.
        ~HardPack( )
        {
            DTOR_DERIVED( "~HardPack" );
        }

        // Update method for which the base class implementation should suffice.
        void update( ) override
        {
            Packager::update( );
        }
    };

    // ZipLock packager.
    class ZipLock : public Packager
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        ZipLock() = delete;
        ZipLock( const ZipLock& ) = default;
        ZipLock& operator=( const ZipLock& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        ZipLock( OutputBin *pSubject ) :
            Packager( pSubject, "ZipLock" )
        {
        }

        // Dtor.
        ~ZipLock()
        {
            DTOR_DERIVED( "~ZipLock" );
        }

        // Update method for which the base class implementation should suffice.
        void update() override
        {
            Packager::update();
        }
    };

    // Packager factory.
    PackagerPtr makePackager( const string& packagerType, OutputBin* pSubject )
    {
        if( matches( packagerType, "ShrinkWrap" ) )
        {
            return PackagerPtr( new ShrinkWrap( pSubject ) );
        }
        else if( matches( packagerType, "HardPack" ) )
        {
            return PackagerPtr( new HardPack( pSubject ) );
        }
        else if( matches( packagerType, "ZipLock" ) )
        {
            return PackagerPtr( new ZipLock( pSubject ) );
        }
        else    // default to Bulk packager.
        {
            return PackagerPtr( new Bulk( pSubject ) );
        }
    }

    // Stuffer observer abstract base class.
    class Stuffer : public OutputBinObserver
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        Stuffer() = delete;
        Stuffer( const Stuffer& ) = default;
        Stuffer& operator=( const Stuffer& ) = default;

        // Param ctor which accepts the OutputBin subject as well as the conveyer belt's name.
        // The observer name is set to the generic "Packager" so that it can be used in the update method.
        Stuffer(
            OutputBin* pSubject,
            const string stufferName1,
            const string cushionName1 ) :
                OutputBinObserver( pSubject, "Stuffer" ),
                stufferName( stufferName1 ),
                cushionName( cushionName1 )
        {
        }

        // Dtor.
        virtual ~Stuffer()
        {
            DTOR_DERIVED( "~Stuffer" );
        }

        // Update method that all derived classes will have to implement.
        virtual void update() = 0;

        // Accessor method for the stuffer name.
        string getStufferName() const { return stufferName; }

        // Accessor method for the cushion name.
        string getCushionName() const { return cushionName; }

    protected:

        // Stuffer name.
        string stufferName;

        // Cushion.
        string cushionName;

    };
    typedef std::shared_ptr<Stuffer> StufferPtr;

    // Air stuffer.
    class AirStuffer : public Stuffer
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        AirStuffer() = delete;
        AirStuffer( const AirStuffer& ) = default;
        AirStuffer& operator=( const AirStuffer& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        AirStuffer( OutputBin *pSubject ) :
            Stuffer( pSubject, "Air", "air" )
        {
        }

        // Dtor.
        ~AirStuffer()
        {
            DTOR_DERIVED( "~AirStuffer" );
        }

        // Update method does nothing.
        void update() override
        {
            Stuffer::update();
        }
    };

    // Popcorn stuffer.
    class PopcornStuffer : public Stuffer
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        PopcornStuffer() = delete;
        PopcornStuffer( const PopcornStuffer& ) = default;
        PopcornStuffer& operator=( const PopcornStuffer& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        PopcornStuffer( OutputBin *pSubject ) :
            Stuffer( pSubject, "Popcorn", "styrene popcorn" )
        {
        }

        // Dtor.
        ~PopcornStuffer()
        {
            DTOR_DERIVED( "~PopcornStuffer" );
        }

        // Update method uses the base implementation.
        void update() override
        {
            Stuffer::update();
        }
    };

    // BubbleWrap stuffer.
    class BubbleWrapStuffer : public Stuffer
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        BubbleWrapStuffer() = delete;
        BubbleWrapStuffer( const BubbleWrapStuffer& ) = default;
        BubbleWrapStuffer& operator=( const BubbleWrapStuffer& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        BubbleWrapStuffer( OutputBin *pSubject ) :
            Stuffer( pSubject, "BubbleWrap", "bubble wrap" )
        {
        }

        // Dtor.
        ~BubbleWrapStuffer()
        {
            DTOR_DERIVED( "~BubbleWrapStuffer" );
        }

        // Update method uses the base implementation.
        void update() override
        {
            Stuffer::update();
        }
    };

    // Foam stuffer.
    class FoamStuffer : public Stuffer
    {
    public:

        // No default ctor and default implementation for auto generated functions.
        FoamStuffer() = delete;
        FoamStuffer( const FoamStuffer& ) = default;
        FoamStuffer& operator=( const FoamStuffer& ) = default;

        // Param ctor sets the OutputBin subject and the name.
        FoamStuffer( OutputBin *pSubject ) :
            Stuffer( pSubject, "Foam", "expanding foam" )
        {
        }

        // Dtor.
        ~FoamStuffer()
        {
            DTOR_DERIVED( "~FoamStuffer" );
        }

        // Update method uses the base implementation.
        void update() override
        {
            Stuffer::update();
        }
    };

    // Stuffer factory.
    StufferPtr makeStuffer( const string& stufferType, OutputBin* pSubject )
    {
        if( matches( stufferType, "Air" ) )
        {
            return StufferPtr( new AirStuffer( pSubject ) );
        }
        else if( matches( stufferType, "Popcorn" ) )
        {
            return StufferPtr( new PopcornStuffer( pSubject ) );
        }
        else if( matches( stufferType, "BubbleWrap" ) )
        {
            return StufferPtr( new BubbleWrapStuffer( pSubject ) );
        }
        else if( matches( stufferType, "Foam" ) )
        {
            return StufferPtr( new FoamStuffer( pSubject ) );
        }
        else
        {
            throw exception( string( "Unsupported stuffer type: " + stufferType ).c_str() );
        }
    }

    // Output bin abstract subject class.
    class OutputBin
    {
    public:

        // Default impl for default ctor, copy ctor and overloaded assignment operator.
        OutputBin( ) = default;
        OutputBin( const OutputBin& ) = default;
        OutputBin& operator=( const OutputBin& ) = default;

        // Param ctor which accepts the output bin's name.
        OutputBin( const string &name ) : binName( name )
        {
        }

        // Dtor.
        ~OutputBin( )
        {
            DTOR_BASE( "~OutputBin" );
        }

        // Attach an observer.
        void attachObserver( OutputBinObserver* pObserver )
        {
            m_pObservers.push_back( pObserver );
        }

        // Detach an observer.
        void detachObserver( OutputBinObserver* pObserver )
        {
            m_pObservers.erase(
                std::remove(
                m_pObservers.begin( ),
                m_pObservers.end( ),
                pObserver ),
                m_pObservers.end( ) );
        }

        // Accessor method for the bin's name.
        string getBinName() const { return binName; }

        // Output bin is full event.
        void binFull( )
        {
            // Indicate that the bin is full.
            cout << "      " << getBinName() << " package bin full...\n";

            notify( );   // Notify all the attached observers.
        }

    protected:

        // Notify all the observers that an event has occurred.
        void notify( )
        {
            for( auto &it : m_pObservers )
            {
                it->update( );
            }
        }

        // Name of the output bin.
        string binName;

        // List of attached observers.
        std::vector<OutputBinObserver*> m_pObservers;
    };
    typedef std::unique_ptr<OutputBin> OutputBinPtr;

    // Deferred OutputBinObserver class method defns.

    // Base class implementation of the update method that all derived classes can use if necessary.
    void OutputBinObserver::update( ) /*override*/
    {
        cout    << "        "
                << getObserverName( )
                << " pausing while "
                << pSubject->getBinName()
                << " package bin is swapped.\n";
    }

    // Param ctor which accepts the OutputBin object that this observer will subscribe to.
    // NOTE: This method will be defined after the OutputBin subject class is defined
    //       as it needs the definition of the subject's public methods.
    OutputBinObserver::OutputBinObserver( OutputBin* pOutputBin, const string name ) :
        pSubject( pOutputBin ), observerName( name )
    {
        // Add this observer to the subject's subscriber list.
        pSubject->attachObserver( this );
    }

    // Dtor unsubscribes this observer from the subject.
    // NOTE: This method will be defined after the OutputBin subject class is defined
    //       as it needs the definition of the subject's public methods.
    OutputBinObserver::~OutputBinObserver()
    {
        DTOR_BASE( "~OutputBinObserver" );

        // Remove this object from the object's subscriber list.
        pSubject->detachObserver( this );
    }

    // Base class implementation of the update method that all derived classes can use if necessary.
    void Stuffer::update() /*override*/
    {
        cout << "        Stuffer filling "
            << pSubject->getBinName()
            << " package bin with "
            << getCushionName()
            << " stuffing.\n";
    }

    // CardboardBox output bin.
    class CardboardBox : public OutputBin
    {
    public:

        // Default implementation for auto generated functions.
        CardboardBox( const CardboardBox& ) = default;
        CardboardBox& operator=( const CardboardBox& ) = default;

        // Default ctor sets the bin name.
        CardboardBox() : OutputBin( "CardboardBox" )
        {
        }

        // Dtor.
        ~CardboardBox( )
        {
            DTOR_DERIVED( "~CardboardBox" );
        }
    };

    // PallotBox output bin.
    class PallotBox : public OutputBin
    {
    public:

        // Default implementation for auto generated functions.
        PallotBox( const PallotBox& ) = default;
        PallotBox& operator=( const PallotBox& ) = default;

        // Default ctor sets the bin name.
        PallotBox( ) : OutputBin( "PallotBox" )
        {
        }

        // Dtor.
        ~PallotBox( )
        {
            DTOR_DERIVED( "~PallotBox" );
        }
    };

    // Crate output bin.
    class Crate : public OutputBin
    {
    public:

        // Default implementation for auto generated functions.
        Crate( const Crate& ) = default;
        Crate& operator=( const Crate& ) = default;

        // Default ctor sets the bin name.
        Crate() : OutputBin( "Crate" )
        {
        }

        // Dtor.
        ~Crate()
        {
            DTOR_DERIVED( "~Crate" );
        }
    };

    // Output bin factory method.
    OutputBinPtr makeOutputBin( const string& outputBinType )
    {
        if( matches( outputBinType, "CardboardBox" ) )
        {
            return OutputBinPtr( new CardboardBox );
        }
        else if( matches( outputBinType, "PallotBox" ) )
        {
            return OutputBinPtr( new PallotBox );
        }
        else if( matches( outputBinType, "Crate" ) )
        {
            return OutputBinPtr( new Crate );
        }
        else
        {
            throw exception( string( "Unsupported output bin type: " + outputBinType ).c_str( ) );
        }
    }

// Seam point - add another listener.

}

// ----- Alternatively (may make it hard to match the dtor instrumentation) -----
namespace abstract_factory_solti {	// DP 10 - more like GoF.

class AbstractA{};
class AbstractB{};
class AbstractC{};
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

    using namespace abstract_factory;
    using namespace observer;

    // Abstract injection line setup class.
    class InjectionLineSetup
    {
    public:

        // No default ctor and default implementation for all auto-generated funcs.
        InjectionLineSetup() = delete;
        InjectionLineSetup( const InjectionLineSetup& ) = default;
        InjectionLineSetup& operator=( const InjectionLineSetup& ) = default;

        // Param ctor accepts the order size (threshold) and the successor if any.
        InjectionLineSetup(
            const unsigned orderSizeThreshold1,
            InjectionLineSetup* pSuccessor1 ) :
            orderSizeThreshold( orderSizeThreshold1 ),
            pSuccessor( pSuccessor1 )
        {
        }

        // Mandatory virtual dtor.
        virtual ~InjectionLineSetup()
        {
            DTOR_BASE( "~InjectionLineSetup" );
        }

        // Injection line setup method that all derived classes must implement.
        virtual void setupInjectionLine(
            const unsigned orderSize,
            OutputBinPtr& pBin,
            MoldingMachinePtr& pMolder,
            unsigned& nCavities,
            ConveyerBeltPtr& pConveyerBelt,
            MetalPtr& pMetal ) = 0;

    protected:

        // Order size threshold.
        unsigned orderSizeThreshold;

        // Successor.
        InjectionLineSetup* pSuccessor;
    };
    typedef std::unique_ptr<InjectionLineSetup> InjectionLineSetupPtr;

    // Small order injection line setup.
    class SmallOrderSetup : public InjectionLineSetup
    {
    public:

        // No default ctor and default implementation for all auto-generated funcs.
        SmallOrderSetup( ) = delete;
        SmallOrderSetup( const SmallOrderSetup& ) = default;
        SmallOrderSetup& operator=( const SmallOrderSetup& ) = default;

        // Param ctor accepts the order size (threshold) and the successor if any.
        SmallOrderSetup(
            const unsigned orderSizeThreshold1,
            InjectionLineSetup* pSuccessor1 = nullptr ) :
            InjectionLineSetup(
                orderSizeThreshold1,
                pSuccessor1 )
        {
        }

        // Dtor.
        ~SmallOrderSetup( )
        {
            DTOR_DERIVED( "~SmallOrderSetup" );
        }

        // Injection line setup method.
        void setupInjectionLine(
            const unsigned orderSize,
            OutputBinPtr& pBin,
            MoldingMachinePtr& pMolder,
            unsigned& nCavities,
            ConveyerBeltPtr& pConveyerBelt,
            MetalPtr& pMetal ) override
        {
            if( orderSize <= orderSizeThreshold )
            {
                // Output bin is CardboardBox.
                pBin = makeOutputBin( "CardboardBox" );

                // Machine is IJM_110.
                pMolder = makeMoldingMachine( "IJM_110", pBin.get( ) );

                // No. of cavities is 1.
                nCavities = 1;

                // Conveyer belt is linear.
                pConveyerBelt = makeConveyerBelt( "Linear", pBin.get( ) );

                // Metal is Aluminum.
                pMetal = makeMetal( "Aluminum" );
            }
            else if( pSuccessor )
            {
                pSuccessor->setupInjectionLine(
                    orderSize,
                    pBin,
                    pMolder,
                    nCavities,
                    pConveyerBelt,
                    pMetal );
            }
            else
            {
                throw exception( string( orderSize + " cannot be handled." ).c_str() );
            }
        }
    };

    // Medium order injection line setup.
    class MediumOrderSetup : public InjectionLineSetup
    {
    public:

        // No default ctor and default implementation for all auto-generated funcs.
        MediumOrderSetup( ) = delete;
        MediumOrderSetup( const MediumOrderSetup& ) = default;
        MediumOrderSetup& operator=( const MediumOrderSetup& ) = default;

        // Param ctor accepts the order size (threshold) and the successor if any.
        MediumOrderSetup(
            const unsigned orderSizeThreshold1,
            InjectionLineSetup* pSuccessor1 = nullptr ) :
            InjectionLineSetup(
            orderSizeThreshold1,
            pSuccessor1 )
        {
        }

        // Dtor.
        ~MediumOrderSetup( )
        {
            DTOR_DERIVED( "~MediumOrderSetup" );
        }

        // Injection line setup method.
        void setupInjectionLine(
            const unsigned orderSize,
            OutputBinPtr& pBin,
            MoldingMachinePtr& pMolder,
            unsigned& nCavities,
            ConveyerBeltPtr& pConveyerBelt,
            MetalPtr& pMetal ) override
        {
            if( orderSize <= orderSizeThreshold )
            {
                // Output bin is CardboardBox.
                pBin = makeOutputBin( "CardboardBox" );

                // Machine is IJM_120.
                pMolder = makeMoldingMachine( "IJM_120", pBin.get( ) );

                // No. of cavities is 2.
                nCavities = 2;

                // Conveyer belt is Y-Split.
                pConveyerBelt = makeConveyerBelt( "Y-Split", pBin.get( ) );

                // Metal is Aluminum.
                pMetal = makeMetal( "Aluminum" );
            }
            else if( pSuccessor )
            {
                pSuccessor->setupInjectionLine(
                    orderSize,
                    pBin,
                    pMolder,
                    nCavities,
                    pConveyerBelt,
                    pMetal );
            }
            else
            {
                throw exception( string( orderSize + " cannot be handled." ).c_str( ) );
            }
        }
    };

    // Large order injection line setup.
    class LargeOrderSetup : public InjectionLineSetup
    {
    public:

        // No default ctor and default implementation for all auto-generated funcs.
        LargeOrderSetup( ) = delete;
        LargeOrderSetup( const LargeOrderSetup& ) = default;
        LargeOrderSetup& operator=( const LargeOrderSetup& ) = default;

        // Param ctor accepts the order size (threshold) and the successor if any.
        LargeOrderSetup(
            const unsigned orderSizeThreshold1,
            InjectionLineSetup* pSuccessor1 = nullptr ) :
            InjectionLineSetup(
            orderSizeThreshold1,
            pSuccessor1 )
        {
        }

        // Dtor.
        ~LargeOrderSetup( )
        {
            DTOR_DERIVED( "~LargeOrderSetup" );
        }

        // Injection line setup method.
        void setupInjectionLine(
            const unsigned orderSize,
            OutputBinPtr& pBin,
            MoldingMachinePtr& pMolder,
            unsigned& nCavities,
            ConveyerBeltPtr& pConveyerBelt,
            MetalPtr& pMetal ) override
        {
            if( orderSize <= orderSizeThreshold )
            {
                // Output bin is PallotBox.
                pBin = makeOutputBin( "PallotBox" );

                // Machine is IJM_210.
                pMolder = makeMoldingMachine( "IJM_210", pBin.get( ) );

                // No. of cavities is 1.
                nCavities = 1;

                // Conveyer belt is Linear.
                pConveyerBelt = makeConveyerBelt( "Linear", pBin.get( ) );

                // Metal is Steel.
                pMetal = makeMetal( "Steel" );
            }
            else if( pSuccessor )
            {
                pSuccessor->setupInjectionLine(
                    orderSize,
                    pBin,
                    pMolder,
                    nCavities,
                    pConveyerBelt,
                    pMetal );
            }
            else
            {
                throw exception( string( orderSize + " cannot be handled." ).c_str( ) );
            }
        }
    };

    // Fast order injection line setup.
    class FastOrderSetup : public InjectionLineSetup
    {
    public:

        // No default ctor and default implementation for all auto-generated funcs.
        FastOrderSetup() = delete;
        FastOrderSetup( const FastOrderSetup& ) = default;
        FastOrderSetup& operator=( const FastOrderSetup& ) = default;

        // Param ctor accepts the order size (threshold) and the successor if any.
        FastOrderSetup(
            const unsigned orderSizeThreshold1,
            InjectionLineSetup* pSuccessor1 = nullptr ) :
            InjectionLineSetup(
            orderSizeThreshold1,
            pSuccessor1 )
        {
        }

        // Dtor.
        ~FastOrderSetup()
        {
            DTOR_DERIVED( "~FastOrderSetup" );
        }

        // Injection line setup method.
        void setupInjectionLine(
            const unsigned orderSize,
            OutputBinPtr& pBin,
            MoldingMachinePtr& pMolder,
            unsigned& nCavities,
            ConveyerBeltPtr& pConveyerBelt,
            MetalPtr& pMetal ) override
        {
            if( orderSize <= orderSizeThreshold )
            {
                // Output bin is PallotBox.
                pBin = makeOutputBin( "PallotBox" );

                // Machine is IJM_140.
                pMolder = makeMoldingMachine( "IJM_140", pBin.get() );

                // No. of cavities is 4.
                nCavities = 4;

                // Conveyer belt is V-Level.
                pConveyerBelt = makeConveyerBelt( "V-Level", pBin.get() );

                // Metal is Steel.
                pMetal = makeMetal( "Aluminum" );
            }
            else if( pSuccessor )
            {
                pSuccessor->setupInjectionLine(
                    orderSize,
                    pBin,
                    pMolder,
                    nCavities,
                    pConveyerBelt,
                    pMetal );
            }
            else
            {
                throw exception( string( orderSize + " cannot be handled." ).c_str() );
            }
        }
    };

    // Larger order injection line setup.
    class LargerOrderSetup : public InjectionLineSetup
    {
    public:

        // No default ctor and default implementation for all auto-generated funcs.
        LargerOrderSetup() = delete;
        LargerOrderSetup( const LargerOrderSetup& ) = default;
        LargerOrderSetup& operator=( const LargerOrderSetup& ) = default;

        // Param ctor accepts the order size (threshold) and the successor if any.
        LargerOrderSetup(
            const unsigned orderSizeThreshold1,
            InjectionLineSetup* pSuccessor1 = nullptr ) :
            InjectionLineSetup(
            orderSizeThreshold1,
            pSuccessor1 )
        {
        }

        // Dtor.
        ~LargerOrderSetup()
        {
            DTOR_DERIVED( "~LargerOrderSetup" );
        }

        // Injection line setup method.
        void setupInjectionLine(
            const unsigned orderSize,
            OutputBinPtr& pBin,
            MoldingMachinePtr& pMolder,
            unsigned& nCavities,
            ConveyerBeltPtr& pConveyerBelt,
            MetalPtr& pMetal ) override
        {
            if( orderSize <= orderSizeThreshold )
            {
                // Output bin is Crate.
                pBin = makeOutputBin( "Crate" );

                // Machine is IJM_220.
                pMolder = makeMoldingMachine( "IJM_220", pBin.get() );

                // No. of cavities is 2.
                nCavities = 2;

                // Conveyer belt is Y-Split.
                pConveyerBelt = makeConveyerBelt( "Y-Split", pBin.get() );

                // Metal is Steel.
                pMetal = makeMetal( "Steel" );
            }
            else if( pSuccessor )
            {
                pSuccessor->setupInjectionLine(
                    orderSize,
                    pBin,
                    pMolder,
                    nCavities,
                    pConveyerBelt,
                    pMetal );
            }
            else
            {
                throw exception( string( to_string(orderSize) + " cannot be handled." ).c_str() );
            }
        }
    };

    // Huge order injection line setup.
    class HugeOrderSetup : public InjectionLineSetup
    {
    public:

        // No default ctor and default implementation for all auto-generated funcs.
        HugeOrderSetup() = delete;
        HugeOrderSetup( const HugeOrderSetup& ) = default;
        HugeOrderSetup& operator=( const HugeOrderSetup& ) = default;

        // Param ctor accepts the order size (threshold) and the successor if any.
        HugeOrderSetup(
            const unsigned orderSizeThreshold1,
            InjectionLineSetup* pSuccessor1 = nullptr ) :
            InjectionLineSetup(
            orderSizeThreshold1,
            pSuccessor1 )
        {
        }

        // Dtor.
        ~HugeOrderSetup()
        {
            DTOR_DERIVED( "~HugeOrderSetup" );
        }

        // Injection line setup method.
        void setupInjectionLine(
            const unsigned orderSize,
            OutputBinPtr& pBin,
            MoldingMachinePtr& pMolder,
            unsigned& nCavities,
            ConveyerBeltPtr& pConveyerBelt,
            MetalPtr& pMetal ) override
        {
            if( orderSize <= orderSizeThreshold )
            {
                // Output bin is Crate.
                pBin = makeOutputBin( "Crate" );

                // Machine is IJM_240.
                pMolder = makeMoldingMachine( "IJM_240", pBin.get() );

                // No. of cavities is 4.
                nCavities = 4;

                // Conveyer belt is V-Level.
                pConveyerBelt = makeConveyerBelt( "V-Level", pBin.get() );

                // Metal is Steel.
                pMetal = makeMetal( "Steel" );
            }
            else if( pSuccessor )
            {
                pSuccessor->setupInjectionLine(
                    orderSize,
                    pBin,
                    pMolder,
                    nCavities,
                    pConveyerBelt,
                    pMetal );
            }
            else
            {
                throw exception( string( orderSize + " cannot be handled." ).c_str() );
            }
        }
    };

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

namespace facade    // DP 7.
{
    using namespace observer;
    using namespace abstract_factory;
    using namespace strategy;
    using namespace chain_of_resp;

    // Order processor class.
    class OrderProcessor
    {
    public:

        // Param ctor which accepts the orders.
        OrderProcessor( map<string, string>& order )
        {
            // Get the plastic if provided, else default to ABS.
            // NOTE: Plastic creation is deferred to when the injection line is setup
            //       as the metal to be used will be determined at that point in time.
            //       We may need to know which metal is to be used if PET plastic is requested.
            if( !keyExists( "plastic", order ) )
            {
                cout << "  <>Unknown plastic || defaulting to ABS.\n";
                plasticType = "ABS";
            }
            else
            {
                plasticType = order.at( "plastic" );
            }

            // Get the order size.

            // Default to 100 if not specified.
            if( !keyExists( "size", order ) )
            {
                cout << "  <>No size specified, defaulting to 100.\n";
                orderSize = 100;
            }
            else
            {
                orderSize = stoul( order.at( "size" ) );

                // Clamp to 200,000 if the order size exceeds it.
                if( orderSize > 200000 )
                {
                    cout << "  <>Size too large |400000| defaulting to HugeOrder of 200000.\n";
                    orderSize = 200000;
                }

            }

            // Get the packager's name.
            if( !keyExists( "packager", order ) )
            {
                cout << "  <>Unknown packager || defaulting to Bulk packager.\n";
                packagerName = "Bulk";  // Defaults to Bulk.
            }
            else
            {
                packagerName = order.at( "packager" );
            }

            // Get the stuffer's name.
            if( !keyExists( "stuffer", order ) )
            {
                cout << "  <>Unknown stuffer || defaulting to Air stuffer.\n";
                stufferName = "Air";    // Defaults to Air.
            }
            else
            {
                stufferName = order.at( "stuffer" );
            }

            // Get the mold location if it exists.
            moldLocation =
                keyExists( "moldLoc", order ) ?
                order.at( "moldLoc" ) :
                "";

            // Get the requested mold shape.
            moldShape =
                keyExists( "mold", order ) ?
                order.at( "mold" ) :
                "";

            // Get the milling finish.
            millFinish =
                keyExists( "finish", order ) ?
                order.at( "finish" ) :
                "";

            // Get the tags if provided.
            tags.clear( );
            if( keyExists( "tags", order ) )
            {
                allTags = order.at( "tags" );
                splitString( allTags, ' ', tags );

                // Populate pTags with all the valid tags.
                for( auto& it : tags )
                {
                    pTags.push_back( makeTag( it ) );
                }
            }
            else
            {
                allTags = "";
            }

            // Get the color if provided, else default to empty.
            color =
                keyExists( "color", order ) ?
                order.at( "color" ) :
                "";

            // Get the additives if any.
            if( keyExists( "UVInhibiter", order ) )
            {
                if( stoi( order.at( "UVInhibiter" ) ) < 0 )
                {
                    throw exception( "UVInhibiter volume must be greater than 0" );
                }

                additives.push_back(
                    make_pair<string, unsigned>(
                        string( "UVInhibiter" ),
                        stoul( order.at( "UVInhibiter" ) ) ) );
            }
            if( keyExists( "AntiBacterial", order ) )
            {
                if( stoi( order.at( "AntiBacterial" ) ) < 0 )
                {
                    throw exception( "AntiBacterial volume must be greater than 0" );
                }

                additives.push_back(
                    make_pair<string, unsigned>(
                    string( "AntiBacterial" ),
                    stoul( order.at( "AntiBacterial" ) ) ) );
            }
            if( keyExists( "MicroFibers", order ) )
            {
                if( stoi( order.at( "MicroFibers" ) ) < 0 )
                {
                    throw exception( "MicroFibers volume must be greater than 0" );
                }

                additives.push_back(
                    make_pair<string, unsigned>(
                    string( "MicroFibers" ),
                    stoul( order.at( "MicroFibers" ) ) ) );
            }

            // Init the small, medium and large injection line setup objects.
            pHugeOrderSetup.reset( new HugeOrderSetup( 200000 ) );
            pLargerOrderSetup.reset( new LargerOrderSetup( 100000, pHugeOrderSetup.get() ) );
            pLargeOrderSetup.reset( new LargeOrderSetup( 50000, pLargerOrderSetup.get() ) );
            pFastOrderSetup.reset( new FastOrderSetup( 40000, pLargeOrderSetup.get() ) );
            pMediumOrderSetup.reset( new MediumOrderSetup( 20000, pFastOrderSetup.get() ) );
            pSmallOrderSetup.reset( new SmallOrderSetup( 10000, pMediumOrderSetup.get() ) );

            // Set the point of contact for injection line setup.
            pSetupContact = pSmallOrderSetup.get();

            // Get the shipping address.
            shippingAddress = keyExists( "address", order ) ? order.at( "address" ) : "";
        }

        // Public function that clients interact which.
        void processOrder( )
        {
            // Setup the injection line.
            setupInjectionLine( );

            // Start processing the order.
            cout << "  Process order.\n";

            // Obtain the toy's mold.
            obtainMold( );

            // Insert tags.
            insertTags( );

            // Load plastic, color and additive bins.
            loadBins( );

            // Run the injection cycle.
            runInjectionCycle( );

            // Clean mold.
            cleanMold( );

            // Ship to address.
            shipToAddress();
        }

    private:

        // Setup the injection line based on the order size.
        void setupInjectionLine( )
        {
            // Set the modified order size.
            if( orderSize > 10000 && orderSize <= 20000 )
            {
                modOrderSize = orderSize / 2;
            }
            else if( orderSize > 20000 && orderSize <= 40000 )
            {
                modOrderSize = orderSize / 4;
            }
            else if( orderSize > 50000 && orderSize <= 100000 )
            {
                modOrderSize = orderSize / 2;
            }
            else if( orderSize > 100000 && orderSize <= 200000 )
            {
                modOrderSize = orderSize / 4;
            }
            else
            {
                modOrderSize = orderSize;
            }

            // Setup the injection line.
            pSetupContact->setupInjectionLine(
                orderSize,
                pBin,
                pMolder,
                nCavities,
                pConveyerBelt,
                pMetal );

            // Create the specified packager.
            pPackager = makePackager( packagerName, pBin.get() );

            // Create the specified stuffer.
            pStuffer = makeStuffer( stufferName, pBin.get() );

            cout << "  Setup injection line for "
                << modOrderSize
                << " run with "
                << packagerName
                << " packager and "
                << pStuffer->getCushionName()
                << " stuffing:\n";

            cout << "    "
                 << pMolder->getMachineName()
                 << " - "
                 << pMetal->getMetalName()
                 << "(" << nCavities << ") - "
                 << pConveyerBelt->getConveyerBeltName()
                 << " conveyer belt - "
                 << pBin->getBinName()
                 << "\n";

            // Create the plastic.
            pPlastic = makePlastic( plasticType, pMetal->getMetalName() );
        }

        // Obtain the toy's mold.
        void obtainMold( )
        {
            // Obtain the mold using the appropriate strategy.
            if( moldLocation.empty() && moldShape.empty() )
            {
                pMoldProcurer.reset( new DefaultMoldProcurement );
                pMoldShape = pMoldProcurer->getMoldShape();
            }
            else
            {
                // Create the mold shape.
                pMoldShape = makeMoldShape( moldShape );

                if( matches( moldLocation, "inventory" ) )
                {
                    pMoldProcurer.reset( new InventoryMoldProcurement( pMoldShape, moldLocation ) );
                }
                else if( matches( moldLocation, "sisterCompany" ) )
                {
                    pMoldProcurer.reset( new SisterCompanyMoldProcurement( pMoldShape, moldLocation ) );
                }
                else if( matches( moldLocation, "purchase" ) )
                {
                    pMoldProcurer.reset( new PurchaseMoldProcurement( pMoldShape, moldLocation ) );
                }
                else if( matches( moldLocation, "mill" ) )
                {
                    pMoldProcurer.reset( new MillMoldProcurement( pMoldShape, moldLocation, nCavities, pMetal, millFinish ) );
                }
                else
                {
                    throw exception( string( "Unsupported mold location: " + moldLocation ).c_str() );
                }
            }

            // Display the mold procurement strategy.
            pMoldProcurer->displayStrategy();
        }

        // Insert tags.
        void insertTags( )
        {
            // Create a string and compute the total width of all the valid tags.
            allTags = "";
            unsigned totalWidth( 0 );
            for( auto& it : pTags )
            {
                allTags += string( it->getTagName() + string( " " ) );
                totalWidth += it->getTagWidth();
            }

            // Display the valid tags and their total width
            cout    << "    Insert tags ["
                    << allTags
                    << "] of width "
                    << totalWidth
                    << "/20 mm.\n";
        }

        // Load plastic, color and additive bins.
        void loadBins( )
        {
            cout << "    Load plastic, color, and additive bins.\n";

            // Get the color if provided else default to black.
            if( color.empty() )
            {
                cout << "      <>No color specified, defaulting to black.\n";
                color = "black";
            }

            // Display the recipe.
            const unsigned shapeVol( pMoldShape->getccVol() );
            const unsigned colorVol( shapeVol / 10 );
            unsigned totalVol( shapeVol + colorVol );
            cout    << "      Recipe: "
                    << pPlastic->getName()
                    << "(" << shapeVol << ") "
                    << color
                    << "(" << colorVol << ") ";

            // Accumulate the vol of the additives.
            for( auto& it : additives )
            {
                totalVol += it.second;
                cout    << it.first
                        << "(" << it.second << ") ";
            }

            // Need to account for no. of cavities.
            totalVol *= nCavities;

            cout << "Total = " << totalVol << ".\n";
        }

        // Run the injection cycle.
        void runInjectionCycle( )
        {
            // Display the injection cycle procedure.
            cout    << "    Cycle IJM for "
                    << pPlastic->getFamilyName() << " "
                    << modOrderSize
                    << " times.\n";

            pPlastic->injectionCycle();
            pBin->binFull();
        }

        // Clean mold.
        void cleanMold( )
        {
            pPlastic->clean();
        }

        // Ship to address.
        void shipToAddress()
        {
            cout    << "    Ship to "
                    << "\"" << shippingAddress << "\""
                    << endl;
        }

        // Original order size and modified size for no. of cavities.
        unsigned orderSize, modOrderSize;

        // Injection line params.

        // Output bin.
        OutputBinPtr pBin;

        // Molding machine.
        MoldingMachinePtr pMolder;

        // No. of cavities.
        unsigned nCavities;

        // Conveyer belt.
        ConveyerBeltPtr pConveyerBelt;

        // Packager object and name.
        PackagerPtr pPackager;
        string packagerName;

        // Metal.
        MetalPtr pMetal;

        // Mold location.
        string moldLocation;

        // Mold shape
        string moldShape;
        MoldShapePtr pMoldShape;

        // Mold procurement strategy.
        MoldProcurementPtr pMoldProcurer;

        // Milling finish.
        string millFinish;

        // Tags.
        string allTags;
        vector<string> tags;
        vector<TagPtr> pTags;

        // Color.
        string color;

        // Plastic.
        string plasticType;
        PlasticPtr pPlastic;

        // Additives. Pair of additive name and volume.
        vector<pair<string,unsigned>> additives;

        // Create small, medium and large injection line setup objects.
        InjectionLineSetupPtr pHugeOrderSetup;
        InjectionLineSetupPtr pLargerOrderSetup;
        InjectionLineSetupPtr pLargeOrderSetup;
        InjectionLineSetupPtr pMediumOrderSetup;
        InjectionLineSetupPtr pFastOrderSetup;
        InjectionLineSetupPtr pSmallOrderSetup;

        // Point of contact for injection line setup and go.
        InjectionLineSetup* pSetupContact;

        // Shipping address.
        string shippingAddress;

        // Stuffer.
        string stufferName;
        StufferPtr pStuffer;
    };
}

void process(map<string, string>& order) {

    try
    {
        // Create the order processor.
        facade::OrderProcessor orderProcessor( order );
        orderProcessor.processOrder( );
    }
    catch( const exception& e )
    {
        cout    << "  "
                << e.what()
                << "\n  Aborting current order.\n";
    }
}

pair<string, string> parse(string line) {
	char key[83];
	char val[83] = {0};

	sscanf(line.c_str(), "%s", key);

	char* equalSign = strchr(const_cast<char*>(line.c_str()), '=');
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

    fclose( orderFilePtr );
}

}

#endif /* DP4_SRC_STUDENTS_ROHIT_H_ */
