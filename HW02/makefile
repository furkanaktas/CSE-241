all: calistir

calistir: main.o
	g++ main.o -o hw1

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

run1:
	./hw1 sort.txt 0
	
run2:
	./hw1 sort.txt 1	

run3:
	./hw1 sort.txt 2	

clean:
	rm -f *.o hw1
