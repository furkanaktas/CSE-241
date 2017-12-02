all: calistir

calistir: main.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ main.o CPU.o CPUProgram.o Memory.o Computer.o -o HW4

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

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
				 
clean:
	rm *.o HW4
