/*
 * dttc.h
 *
 *  Created on: Mar 21, 2015
 *      Author: aldgoff
 *
 * Description:
 *   Place to try out code for my DTTC talk on design patterns as lambda calculus
 *   implementations.
 *
 * Titles:
 *   Design Patterns Explained in 30 Minutes
 */

#ifndef DP4_SRC_DTTC_H_
#define DP4_SRC_DTTC_H_

namespace dttc {

char str[80+1];

namespace legacy {

unsigned shiftLeft(const unsigned& reg, unsigned bits) {
	unsigned shiftedReg = reg;

	if(bits == 0) shiftedReg = reg << 0;
	else if(bits == 1) shiftedReg = reg << 1;
	else if(bits == 2) shiftedReg = reg << 2;
	else if(bits == 3) shiftedReg = reg << 3;
	else if(bits == 4) shiftedReg = reg << 4;
	else if(bits == 5) shiftedReg = reg << 5;
	else if(bits == 6) shiftedReg = reg << 6;
	else if(bits == 7) shiftedReg = reg << 7;
	else if(bits == 8) shiftedReg = reg << 8;
	else if(bits == 9) shiftedReg = reg << 9;
	else if(bits == 10) shiftedReg = reg << 10;
	else if(bits == 11) shiftedReg = reg << 11;
	else if(bits == 12) shiftedReg = reg << 12;
	else if(bits == 13) shiftedReg = reg << 13;
	else if(bits == 14) shiftedReg = reg << 14;
	else if(bits == 15) shiftedReg = reg << 15;
	else {
		cout << "  OOPS!\n";
	}

	return shiftedReg;
}

void bubbleSort(int* array, size_t size) { cout << "  bubble sort\n"; }
void quickSort(int* array, size_t size) { cout << "  quick sort\n";}
void heapSort(int* array, size_t size) { cout << "  heap sort\n";}
void mergeSort(int* array, size_t size) { cout << "  merge sort\n";}
void radixSort(int* array, size_t size) { cout << "  radix sort\n";}

bool mustBeStable = false;
bool keysWellBehaved = false;

void mySort(int* array, size_t size) {
	if(mustBeStable)		 heapSort(array, size);
	else if(keysWellBehaved) radixSort(array, size);
	else if(size <10)		 bubbleSort(array, size);
	else if(size < 100000)	 quickSort(array, size);
	else if(size >= 100000)  mergeSort(array, size);
	else {
		cout << "  OOPS!";
	}
	if(size < 10)			 bubbleSort(array, size);
	else if(size < 100000)	 quickSort(array, size);
	else if(mustBeStable)	 heapSort(array, size);
	else if(size >= 100000)  mergeSort(array, size);
	else if(keysWellBehaved) radixSort(array, size);
	else {
		cout << "  OOPS!";
	}
}

void demo() {
	unsigned reg = 0x00FF;

	sprintf(str, "  %04X - %04X\n", reg, shiftLeft(reg, 4));
	cout << str;


	int array[7] = { 5, 2, 3, 7, 1, 6, 4 };
	size_t sizes[] = { 7, 100, 200000 };
	for(size_t i=0; i<sizeof(sizes)/sizeof(*sizes); i++) {
		mySort(array, sizes[i]);
	}
}

}

namespace design_pattern {

unsigned shiftLeft(const unsigned& reg, unsigned bits) {
	return(reg << bits);
}

class Sort {
public: virtual ~Sort() {}
public:
	virtual void algorithm(unsigned* array, size_t size)=0;
};
class BubbleSort : public Sort {
public:
	void algorithm(unsigned* array, size_t size) { cout << "  bubble sort\n"; }
};
class QuickSort : public Sort {
public:
	void algorithm(unsigned* array, size_t size) { cout << "  quick sort\n"; }
};
class HeapSort : public Sort {
public:
	void algorithm(unsigned* array, size_t size) { cout << "  heap sort\n"; }
};
class MergeSort : public Sort {
public:
	void algorithm(unsigned* array, size_t size) { cout << "  merge sort\n"; }
};
class RadixSort : public Sort {
public:
	void algorithm(unsigned* array, size_t size) { cout << "  radix sort\n"; }
};

void clientCode(unsigned* array, size_t size, Sort* sort) {
	sort->algorithm(array, size);
}

void demo() {
	unsigned reg = 0x00FF;

	sprintf(str, "  %04X - %04X\n", reg, shiftLeft(reg, 4));
	cout << str;

	unsigned array[7] = { 5, 2, 3, 7, 1, 6, 4 };


	Sort* sorts[] = { new BubbleSort, new QuickSort, new HeapSort };
	size_t sizes[] = { 7, 100, 200000 };
	for(size_t i=0; i<sizeof(sorts)/sizeof(*sorts); i++) {
		clientCode(array, sizes[i], sorts[i]);
	}
}

}

}



#endif /* DP4_SRC_DTTC_H_ */
