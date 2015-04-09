/*
 * Problems/final.h
 *
 *  Created on: Apr 6, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_PROBLEMS_FINAL_H_
#define DP4_SRC_PROBLEMS_FINAL_H_

#include <stdio.h>

namespace final_problem_file {

class Order {};

pair<string, string> parse(string line) {
	char key[83];
	char val[83];

	sscanf(line.c_str(), "%s", key);
	char* equalSign = strchr(line.c_str(), '=');
	if(equalSign) {
		sscanf(++equalSign, "%s", val);
	}

	return make_pair(key, val);
}

void process(map<string, string> order) {
//	map<string, string>::iterator it = order.begin();

	cout << "Order processing [TemplateMethod]";
	cout << "  Setup\n";
	cout << "     GetMold (depends on mold location)[CofR]\n";
	cout << "     Finish?\n";
	cout << "     Tags [Decorator]\n";
	cout << "     Additives [Decorator]\n";
	cout << "     Package path\n";
	cout << "  Injection runs\n";
	cout << "    Example injection steps (depends on plastic)[Strategy]\n";
	cout << "      close - mix - heat - flow - cool - open - eject - package\n";
	cout << "  Events\n";
	cout << "    Empty bins\n";
	cout << "    Full bins\n";
	cout << "  Clean mold (depends on plastic)[Adapter]\n";
	cout << "  Retire or return mold to inventory\n";

}

void reveal(map<string, string> order) {
	map<string, string>::iterator it = order.begin();
	for(; it!=order.end(); it++) {
		cout << "[" << it->first << "] = " << it->second << "\n";
	}
	cout << "order[orderNum] = " << order["orderNum"] << "\n";
	cout << "order[mold] = " << order["mold"] << "\n";
	cout << "order[moldLoc] = " << order["moldLoc"] << "\n";
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
	cout << "<<< final problem >>>\n";

	FILE* orderFilePtr = fopen(orderFile.c_str(), "r");

	for(;;) {	// Get and process each order.
		map<string, string> order = getCompleteOrder(orderFilePtr);
		if(order.size() == 0)
			break;
		process(order);
	}
}


}


#endif /* DP4_SRC_PROBLEMS_FINAL_H_ */
