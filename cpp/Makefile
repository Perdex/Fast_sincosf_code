
FLAGS = -std=c++11 -Wall

all:

tester: fast_sincosf.o
	g++ tester.cpp fast_sincosf.o -o tester $(FLAGS) -O3
	rm *.o
speedtest: fast_sincosf.o
	g++ speedtest.cpp fast_sincosf.o -o speedtest $(FLAGS) -O2
	rm *.o
single:
	g++ fast_sincosf.cpp -c -DDEBUG $(FLAGS) -O2
	g++ tester_single.cpp fast_sincosf.o -o single $(FLAGS) -O2
	rm *.o
fast_sincosf.o:
	g++ fast_sincosf.cpp -c $(FLAGS) -O2
clean:
	rm -f *.o tester single speedtest