#pragma once
enum  CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
class HashTable
{
	/*
* Author: Turan Mert Duran
* ID: 21601418
* Section: 2
* Assignment: 4
*/
public:
	
	HashTable(const int tableSize, const CollisionStrategy option);
	~HashTable();
	int findEmptyLinear(int index); // finds empty spaces for to insert +
	int findEmptyDouble(int index, int key);	// finds empty spaces for to insert +
 	int findEmptyQuadratic(int index);	// finds empty spaces for to insert +
	int gettingReverse(int value); // return reverse of given value
	int findIndexLinear(int value);
	int findIndexQuadratic(int value);
	int findIndexDouble(int value);
	bool search(const int item, int& numProbes);
	void display(); // displays items
	bool insert(const int item); // inserting items 
	bool remove(const int item); // removes items
    void analyse(int& numSuccProbes, int& numUnsuccProbes); // analyse

private: 
	int* table;
	int* availabilityCheck; // 1 For EMPTY, 2 FOR IT WAS FULL BUT IT DELETED, 3 FOR FULL
	CollisionStrategy type;
	int tableSize;
	int size;
};

