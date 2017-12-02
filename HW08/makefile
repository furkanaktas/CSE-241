all: Bigram.class BigramMap.class BigramDyn.class _mainTester.class

Bigram.class: Bigram.java
	javac Bigram.java

BigramMap.class: BigramMap.java
	javac BigramMap.java

BigramDyn.class: BigramDyn.java
	javac BigramDyn.java

_mainTester.class: _mainTester.java
	javac _mainTester.java

run1:
	java _mainTester t1.txt 1 1
		
run2:
	java _mainTester t1.txt 1 2

run3:
	java _mainTester t2.txt 2 1

run4:
	java _mainTester t2.txt 2 2

run5:
	java _mainTester t3.txt 3 1

run6:
	java _mainTester t3.txt 3 2

run7:
	java _mainTester t4.txt 1 1

run8:
	java _mainTester t4.txt 1 2

run9:
	java _mainTester t5.txt 1 1

clean:
	rm -f *.class
