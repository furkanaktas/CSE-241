all: calistir calistir2

calistir: main.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ main.o CPU.o CPUProgram.o Memory.o Computer.o -o HW4

calistir2: maintest.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ _mainTester.o CPU.o CPUProgram.o Memory.o Computer.o -o HW4test

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
	./HW4 sort.txt 0

run2:
	./HW4 sort.txt 1

run3:
	./HW4 sort.txt 2

run4:
	./HW4 kare.txt 0	

run5:
	./HW4 kare.txt 1
	
run6:
	./HW4 kare.txt 2
	
run7:
	./HW4test sort.txt 0

run8:
	./HW4test sort.txt 1	

run9:
	./HW4test sort.txt 2

run10:
	./HW4test kare.txt 0

run11:
	./HW4test kare.txt 1

run12:
	./HW4test kare.txt 2
							 
clean:
	rm *.o HW4 HW4test
