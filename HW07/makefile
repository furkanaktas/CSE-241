all: calistir

calistir: maintest.o BigramMap.o BigramDyn.o exceptions.o 
	g++ _mainTester.o BigramMap.o BigramDyn.o exceptions.o -o exe
													
maintest.o: _mainTester.cpp
	g++ -c -std=c++11 _mainTester.cpp

BigramMap.o: BigramMap.cpp
	g++ -c -std=c++11 BigramMap.cpp

BigramDyn.o: BigramDyn.cpp
	 g++ -c -std=c++11 BigramDyn.cpp
	 
exceptions.o: exceptions.cpp
	g++ -c -std=c++11 exceptions.cpp		 


run1:
	./exe t1.txt 1 1

run2:
	./exe t1.txt 1 2
	
run3:
	./exe t2.txt 3 1

run4:
	./exe t2.txt 3 2

run5:
	./exe t3.txt 2 1
	
run6:
	./exe t3.txt 2 1

run7:
	./exe t4.txt 1 1
					
run8:
	./exe t4.txt 1 2
	
run9:
	./exe t5.txt 3 1

clean:
	rm *.o exe
