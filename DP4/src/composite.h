/*
 * composite.h
 *
 * Desc: Allow client code to treat objects and collections of objects the same.
 *
 * Category: Structural
 *
 *  Created on: Sep 1, 2014
 *      Author: aldgoff
 *
 * URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Composite
 * URL: http://www.dofactory.com/net/composite-design-pattern
 * URL: http://sourcemaking.com/design_patterns/composite
 */

#ifndef COMPOSITE_H_
#define COMPOSITE_H_

/* Consider modeling a fruit tree. Branches can contain other branches or leaves.
 * Of course they can also contain buds, and eventually fruit.
 * Rewrite the problematic example below to follow the open-closed principle.
 * See if you can get the number of seam points in the library code down to just one.
 *
 * Extra Credit:
 *   What happens when the spec change occurs to allow removing branches and leaves?
 *   Who is in control of the display order?
 *   Add the fruit class to both the problem and the design pattern code. Can you
 *   see the difference in maintainability?
 */

namespace leaf_versus_list {

class Leaf;
class Bud;
// Seam point 1: Add class declaration for fruit.

class Branch {	// Has to be changed for new types of 'leaves' - violates open-closed principle.
public:
	string name;
	list<Branch*> branches;
	list<Leaf*>   leafs;
	list<Bud*>    buds;
	// Seam point 2: Add container for fruit.
public:
	Branch(string name) : name(name) {}
public:
	void addBranch(Branch* branch) {
		branches.push_back(branch);
	}
	void addLeaf(Leaf* leaf) {
		leafs.push_back(leaf);
	}
	void addBud(Bud* bud) {
		buds.push_back(bud);
	}
	// Seam point 3: Add add-method for fruit.
};

class Leaf {
public:
	string name;
public:
	Leaf(string name) : name(name) {}
};

class Bud {
public:
	string name;
public:
	Bud(string name) : name(name) {}
};

// Seam point 4: Add class for fruit.

void display(Branch* branch, int depth) {	// Has to be changed for new types of 'leaves' - violates open-closed principle.
	for(int i=0; i<depth; i++) cout << "-";			// Display this branch.
	cout << " " << branch->name << endl;

	list<Branch*>::iterator it = branch->branches.begin();	// Display all the child branches.
	for(; it!=branch->branches.end(); it++) {
		display(*it, depth + 2);
	}

	list<Leaf*>::iterator itl = branch->leafs.begin();		// Display all the child leafs.
	for(; itl!=branch->leafs.end(); itl++) {
		for(int i=0; i<depth+2; i++) cout << "-";
		cout << " " << (*itl)->name << endl;
	}

	list<Bud*>::iterator itb = branch->buds.begin();		// Display all the child buds.
	for(; itb!=branch->buds.end(); itb++) {
		for(int i=0; i<depth+2; i++) cout << "-";
		cout << " " << (*itb)->name << endl;
	}

	// Seam point 5: Add display code for fruit.
}

void demo() {
	cout << "<< Composite problem >>\n";

	Branch* trunk = new Branch("trunk");
	trunk->addLeaf(new Leaf("leaf1"));
	trunk->addBud(new Bud("bud2"));
	trunk->addLeaf(new Leaf("leaf3"));

	Branch* branch = new Branch("branch4");
	trunk->addBud(new Bud("bud5"));
	branch->addLeaf(new Leaf("leaf6"));
	trunk->addBranch(branch);

	branch->addLeaf(new Leaf("leaf7"));
	branch->addLeaf(new Leaf("leaf8"));

	Branch* branch2 = new Branch("branch9");
	branch2->addLeaf(new Leaf("budA"));
	Branch* subComp = new Branch("branchB");
	subComp->addLeaf(new Leaf("leafC"));
	branch2->addBranch(subComp);
	trunk->addBranch(branch2);
	branch2->addBud(new Bud("budD"));
	trunk->addLeaf(new Leaf("leafE"));

	display(trunk, 1);	// Display order driven by library code, not client code.
	cout << endl;
}

}

namespace composite {

class Composite {					// No seam points, closed to modification.
protected:
	string name;
public:
	Composite(string name) : name(name) {}
	virtual ~Composite() {}
public:
	virtual void add(Composite* branch) { cout << "OOPS!, can't add to non branches.\n"; };
	virtual void display(int depth)=0;
};
class Branch : public Composite {	// No seam points, closed to modification.
	list<Composite*> children;
public:
	Branch(string name) : Composite(name) {}
	virtual ~Branch() {}
public:
	void add(Composite* branch) {
		children.push_back(branch);
	}
	void display(int depth) {						// Display this branch and all its children.
		for(int i=0; i<depth; i++) cout << "-";
		cout << " " << name << endl;

		list<Composite*>::iterator it=children.begin();
		for(; it!=children.end(); it++) {
			(*it)->display(depth + 2);
		}
	}
public:
};
class Leaf : public Composite {
public:
	Leaf(string name) : Composite(name) {}
	virtual ~Leaf() {};
public:
	void display(int depth) {						// Display this leaf.
		for(int i=0; i<depth; i++) cout << "-";
		cout << " " << name << endl;
	}
};
class Bud : public Composite {
public:
	Bud(string name) : Composite(name) {}
	virtual ~Bud() {};
public:
	void display(int depth) {						// Display this bud.
		for(int i=0; i<depth; i++) cout << "-";
		cout << " " << name << endl;
	}
};
// Seam point: Add class for fruit.

void demo() {
	cout << "<< Composite solution >>\n";

	Composite* trunk = new Branch("trunk");
	trunk->add(new Leaf("leaf1"));
	trunk->add(new Bud("bud2"));
	trunk->add(new Leaf("leaf3"));

	Composite* branch = new Branch("branch4");
	branch->add(new Bud("bud5"));
	branch->add(new Leaf("leaf6"));
	trunk->add(branch);

	trunk->add(new Leaf("leaf7"));
	trunk->add(new Leaf("leaf8"));

	Composite* limb = new Branch("branch9");
	limb->add(new Bud("budA"));
	Composite* twig = new Branch("branchB");
	twig->add(new Leaf("leafC"));
	limb->add(twig);
	trunk->add(limb);
	limb->add(new Bud("budD"));
	trunk->add(new Leaf("leafE"));

	trunk->display(1);	// Client code in control of display order.
	cout << endl;

	Leaf* badLeaf = new Leaf("badLeaf");
	badLeaf->add(new Bud("budLeaf"));

	cout << endl;
}

}

#endif /* COMPOSITE_H_ */
