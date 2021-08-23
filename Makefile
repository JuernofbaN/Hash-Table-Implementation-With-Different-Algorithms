
output: HashTable.o main.o
	g++ HashTable.o main.o -o output
	
HashTable.o: HashTable.cpp
	g++ -c HashTable.cpp

main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm *.o output