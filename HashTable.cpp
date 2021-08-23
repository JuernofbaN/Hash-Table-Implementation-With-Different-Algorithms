#include "HashTable.h"
#include <iostream>
#include <iostream>
//#include <cmath>
#include <cmath>
using namespace std;
/*
* Author: Turan Mert Duran
* ID: 21601418
* Section: 2
* Assignment: 4
*/

HashTable::HashTable(const int tableSize, const CollisionStrategy option)
{
	table = new int[tableSize];
	type = option;
	availabilityCheck = new int[tableSize];
	this->tableSize = tableSize;
	size = 0; // Empty
	for (int i = 0; i < tableSize; i++)
		availabilityCheck[i] = 1; // Initially all indexes are empty to insert. 
}

HashTable::~HashTable()
{
	delete[] table;
	delete[] availabilityCheck;
}

int HashTable::findEmptyLinear(int index)
{
	int newIndex = index;
	while (availabilityCheck[newIndex] == 3) {
		newIndex = newIndex + 1;
		newIndex = newIndex % tableSize;
	}
	return newIndex;
}

int HashTable::findEmptyDouble(int index, int key)
{
	int reversed = gettingReverse(key);
	int increment = reversed % tableSize;
	if (increment < 1) { // FOR  NEGATIVE INTEGERS AND INCREMENT 0's
		increment = increment + tableSize;
	}
	int newIndex = index % tableSize;
	int ctr = 1;
	while (availabilityCheck[newIndex] == 3) {
		newIndex = index + (ctr * increment);
		newIndex = newIndex % tableSize;
		if (ctr > tableSize) {
			return -1;
		}
		ctr++;
		
	}
	return newIndex;
}

int HashTable::findEmptyQuadratic(int index)
{
	int newIndex = index;
	int ctr = 1;
	while (availabilityCheck[newIndex] == 3) {
		newIndex = (int)pow(ctr, 2) + index;
		newIndex = newIndex % tableSize;
		//cout << " New InDEx "<<newIndex << endl;
		if (ctr > tableSize) {
			return -1;
		}
		ctr++;
	}
	return newIndex;
}

int HashTable::gettingReverse(int value)
{
	int reversedNumber = 0;
	int rem = 0;
	bool minus = false;
	if (value < 0) {
		value = -value;
		minus = true;
	}
	int n = value;
	while (n != 0)
	{
		rem = n % 10;
		reversedNumber = reversedNumber * 10 + rem;
		n /= 10;
	}
	if (minus == true)
		return -reversedNumber;
	return reversedNumber;
}

int HashTable::findIndexLinear(int value)
{
	int index = value % tableSize;
	if (index < 0) { // FOR  NEGATIVE INTEGERS
		index = index + tableSize;
	}
	if (table[index] == value && availabilityCheck[index] == 3) {
		return index;
	}
	else {
		int newIndex = index;
		for (int i = 0; i < tableSize+1; i++) {
			newIndex = newIndex + 1;
			newIndex = newIndex % tableSize;
			//cout << " Returning from find Index lýneear " << tableSize << "hello i :"<< i <<" new index " << newIndex<<  endl;
			if (table[newIndex] == value && availabilityCheck[newIndex] == 3) {
		//		cout << " Returning from find Index lýneear " << newIndex << endl;
				return newIndex;
			}
		}
		return -1;
	}
}

int HashTable::findIndexQuadratic(int value)
{
	int fIndex = value % tableSize;
	if (fIndex < 0) { // FOR  NEGATIVE INTEGERS
		fIndex = fIndex + tableSize;
	}
	if (table[fIndex] == value && availabilityCheck[fIndex] == 3)
		return fIndex;
	int index = fIndex;
	for (int i = 0; i < tableSize; i++) {
		index = (int)pow(i, 2) + fIndex;
		index = index % tableSize;
		if (table[index] == value && availabilityCheck[index] == 3) {
			return index;
		}
	}
	return -1;
}

int HashTable::findIndexDouble(int value)
{
	int fIndex = value % tableSize;
	if (fIndex < 0) { // FOR  NEGATIVE INTEGERS
		fIndex = fIndex + tableSize;
	}
	if (table[fIndex] == value && availabilityCheck[fIndex] == 3)
		return fIndex;
	int reversed = gettingReverse(value);
	int increment = reversed % tableSize;
	if (increment < 1) {
		increment = increment + tableSize;
	}
	int newIndex = fIndex;
	for (int i = 0; i < tableSize; i++) {
		newIndex = fIndex + (i * increment);
		newIndex = newIndex % tableSize;
		if (availabilityCheck[newIndex] == 3 && table[newIndex] == value)
			return newIndex;
	}
	return -1;
}

bool HashTable::search(const int item, int& numProbes)
{
	if (type == LINEAR) {
		int index = item % tableSize; 
		if (index < 0) // FOR  NEGATIVE INTEGERS
			index = index + tableSize;
		int probCtr = 0;
		for (int i = 0; i < tableSize; i++) {
            probCtr++;
			if (availabilityCheck[index] == 3 && table[index] == item) {
				numProbes = probCtr;
				return true;
			}
			if (availabilityCheck[index] == 1) {
				numProbes = probCtr;
				return false;
			}
			index = index + 1;
			index = index % tableSize;
		}
		numProbes = probCtr;
		return false;
	}
	else if (type == QUADRATIC) {
		int fIndex = item % tableSize;
		if (fIndex < 0) // FOR  NEGATIVE INTEGERS
			fIndex = fIndex + tableSize;
		int probCtr = 0;
		int index = fIndex;
		for (int i = 0; i < tableSize; i++) {
            index = (int)pow(i, 2) + fIndex;
            index = index % tableSize;
            probCtr++;
			if (availabilityCheck[index] == 3 && table[index] == item) {
				numProbes = probCtr;
				return true;
			}
			if (availabilityCheck[index] == 1) {
				numProbes = probCtr;
				return false;
			}
		}
		numProbes = probCtr;
		return false;
	}
	else if (type == DOUBLE) {
		int fIndex = item % tableSize;
		if (fIndex < 0) // FOR  NEGATIVE INTEGERS
			fIndex = fIndex + tableSize;
		int probCtr = 1;
		int reversed = gettingReverse(item);
		int increment = reversed % tableSize;
		if (increment < 1) {
			increment = increment + tableSize;
		}
		int index = fIndex;
		for (int i = 0; i < tableSize; i++) {
			if (availabilityCheck[index] == 3 && table[index] == item) {
				numProbes = probCtr;
				return true;
			}
			if (availabilityCheck[index] == 1) {
				numProbes = probCtr;
				return false;
			}
			index = fIndex + (i * increment);
			index = index % tableSize;
			if (i != 0) {
				probCtr++;
			}
			
		}
		numProbes = probCtr;
		return false;
	}
	return false;
}

void HashTable::display()
{
	for (int i = 0; i < tableSize; i++) {
		cout << i << ":  ";
		if (availabilityCheck[i] == 3) {
			cout << table[i];
		}
		cout << endl;
	}
}

bool HashTable::insert(const int item)
{    int counterAh= 0;
    for(int i = 0; i < tableSize; i++){
        if(availabilityCheck[i] == 3)
            counterAh++;
    }
    size = counterAh;
	// Check if table Full, if full return false
	if (size == tableSize) {
		return false;
	}
	// First check mod index same for all enums
	int fIndex = item % tableSize;
	if (fIndex < 0) { // FOR  NEGATIVE INTEGERS
		fIndex = fIndex + tableSize;
	}
	if (availabilityCheck[fIndex] != 3) {
		table[fIndex] = item;
		availabilityCheck[fIndex] = 3;
		size++;
		return true;
	}
	else { // If first index that we found is full then we check for another space
		if (type == LINEAR) {
			int index = findEmptyLinear(fIndex);
			size++;
			availabilityCheck[index] = 3;
			table[index] = item;
			return true;
		}
		else if (type == QUADRATIC) {
			int index = findEmptyQuadratic(fIndex);
			size++;
			if (index == -1) {
				return false;
			}
			availabilityCheck[index] = 3;
			table[index] = item;
			return true;
		}
		else if(type == DOUBLE){
			int index = findEmptyDouble(fIndex, item);
			size++;
			if (index == -1) {
				return false;
			}
			availabilityCheck[index] = 3;
			table[index] = item;
			return true;
		}
	}
	return false;
}

bool HashTable::remove(const int item)
{
	if (type == LINEAR) {
		int index = findIndexLinear(item);
		if (index == -1) {
			return false; // not found
		}
		else {
			availabilityCheck[index] = 2; // It was full and deleted it means. 
			size--;
			return true;
		}
	}
	else if (type == QUADRATIC) {
		int index = findIndexQuadratic(item);
		if (index == -1) {
			return false; // not found
		}
		else {
			availabilityCheck[index] = 2; // It was full and deleted it means. 
			size--;
			return true;
		}
	}
	else if (type == DOUBLE) {
		int index = findIndexDouble(item);
		if (index == -1) {
			return false; // not found
		}
		else {
			availabilityCheck[index] = 2; // It was full and deleted it means. 
			size--;
			return true;
		}
	}
	return false;
}

void HashTable::analyse(int& numSuccProbes, int& numUnsuccProbes) {
    int totalProbesSuc = 0;
    int probes = 0;
    int counterAh= 0;
    for(int i = 0; i < tableSize; i++){
        if(availabilityCheck[i] == 3)
            counterAh++;
    }
    size = counterAh;
    for (int i = 0; i < tableSize; i++) {
        if (availabilityCheck[i] == 3) {
            search(table[i], probes);
            totalProbesSuc = totalProbesSuc + probes;
       //     cout << "ctr" << table[i] <<" ---- "<< probes <<  "totalProbesUns" << size << "size "<<endl;
        }
    }
    if(size != 0)
        numSuccProbes = ((double)totalProbesSuc / (double)size);
    probes = 0;
    int totalProbesUns = 0;
    int totUns = 0;
    //int counter = 0;
    //int* total = new int[size];
    int ctr;
    if (type != DOUBLE) {
        for(int i = 0; i < tableSize; i++){
            ctr = i;
            while(search(ctr, totalProbesUns) == true){
               // cout << "size" << size << endl;
                ctr = ctr + tableSize;
            }
            //(ctr, totalProbesUns);
   //         cout << "ctr" << ctr <<" ---- "<< totalProbesUns <<  "totalProbesUns" <<endl;
            search(ctr, totalProbesUns);
            totUns = totalProbesUns + totUns;
        }
        numUnsuccProbes = (int) totUns/tableSize;
    }
    else {
        numUnsuccProbes = -1;
    }
    
}
