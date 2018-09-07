
FLAGS = -std=c++14 -Wall -march=native

all:

tester: fast_sincosf.o speedtest.o accuracytest.o
	g++ tester.cpp fast_sincosf.o speedtest.o accuracytest.o -o tester $(FLAGS) -O2
	rm *.o
speedtest.o:
	g++ speedtest.cpp -c $(FLAGS) -O2
accuracytest.o:
	g++ accuracytest.cpp -c $(FLAGS) -O2
fast_sincosf.o:
	g++ fast_sincosf.cpp -c $(FLAGS) -O2

asm:
	g++ fast_sincosf.cpp speedtest.cpp -S $(FLAGS) -O2 -fverbose-asm

clean:
	rm -f *.o tester single speedtest


