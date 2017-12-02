all: calistir calistir2

calistir: main.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ main.o CPU.o CPUProgram.o Memory.o Computer.o -o HW5

calistir2: maintest.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ _mainTester.o CPU.o CPUProgram.o Memory.o Computer.o -o HW5test

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

maintest.o: _mainTester.cpp
	g++ -c -std=c++11 _mainTester.cpp

CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp

CPUProgram.o: CPUProgram.cpp
	 g++ -c -std=c++11 CPUProgram.cpp
	 
Memory.o: Memory.cpp
	g++ -c -std=c++11 Memory.cpp		 

Computer.o: Computer.cpp
	g++ -c -std=c++11 Computer.cpp

run1:
	./HW5 sort.txt 0

run2:
	./HW5 sort.txt 1

run3:
	./HW5 sort.txt 2

run4:
	./HW5test sort.txt 0

clean:
	rm *.o HW5 HW5test
