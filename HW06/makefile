all: calistir

calistir: maintest.o CPU.o CPUProgram.o Memory.o Computer.o CPUProgramDyn.o
	g++ _mainTester.o CPU.o CPUProgram.o Memory.o Computer.o CPUProgramDyn.o -o HW6test
													
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
	
CPUProgramDyn.o: CPUProgramDyn.cpp	
	g++ -c -std=c++11 CPUProgramDyn.cpp

run1:
	./HW6test sort.txt 0

run2:
	./HW6test sort.txt 1
	
run3:
	./HW6test sort.txt 2
	
clean:
	rm *.o HW6test
