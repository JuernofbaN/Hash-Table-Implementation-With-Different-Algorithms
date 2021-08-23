#include <iostream>
#include <fstream>
#include "HashTable.h"
using namespace std;
/*/Users/turanmertduran/Documents/xcode c44/Hello/Hello/input.txt
* Author: Turan Mert Duran
* ID: 21601418
* Section: 2
* Assignment: 4 
*/

int main()
{
CollisionStrategy type = QUADRATIC;
    int sizeTable = 11;
    ifstream inFile;
    
    inFile.open("input.txt");
   // inFile.open("/Users/turanmertduran/Documents/xcode c44/Hello/Hello/input.txt");
    if (!inFile) {
        cerr << "Unable to open file input.txt";
        return 0;
    }
    cout << "Table size " << sizeTable << endl;
    char x;
    int value;
    int numProbes = 0;
    HashTable myTable(sizeTable, type);
    while (inFile >> x) {
        if (x == 'I') {
            inFile >> value;
            if (myTable.insert(value)) {
                cout << value << " inserted" << endl;
            }
            else {
                cout << value << " not inserted" << endl;
            }
        }
        if (x == 'R') {
            inFile >> value;
            if (myTable.remove(value)) {
                cout << value << " removed" << endl;
            }
            else {
                cout << value << " not removed" << endl;
            }
        }
        if (x == 'S') {
            inFile >> value;
            if (myTable.search(value, numProbes)) {
                cout << value << " found after " << numProbes << " probes" << endl;
            }
            else {
                cout << value << " not found after " << numProbes << " probes" << endl;
            }
        }
    }
    myTable.display();
    int negatives, positives;
    myTable.analyse(positives, negatives);
    cout << "Analyse Completed with " << positives << " succesful search and " << negatives << " unsuccesful search." << endl;
    inFile.close();

    return 0;
}
