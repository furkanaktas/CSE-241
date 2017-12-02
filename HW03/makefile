all: calistir

calistir: main.o CPU.o CPUProgram.o
	g++ main.o CPU.o CPUProgram.o -o HW3

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp

CPUProgram.o: CPUProgram.cpp
	 g++ -c -std=c++11 CPUProgram.cpp

run1:
	./HW3 kare.txt 0	

run2:
	./HW3 kare.txt 1
			 
run3:
	./HW3 10to0.txt 0	

run4:
	./HW3 10to0.txt 1


clean:
	rm *.o HW3
