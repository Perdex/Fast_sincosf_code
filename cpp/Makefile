
FLAGS = -std=c++14 -Wall -march=native -O2
all:

tester: fast_sincosf.o speedtest.o accuracytest.o
	g++ tester.cpp fast_sincosf.o speedtest.o accuracytest.o -o tester $(FLAGS)
	rm *.o
speedtest.o:
	g++ speedtest.cpp -c $(FLAGS)
accuracytest.o:
	g++ accuracytest.cpp -c $(FLAGS)
fast_sincosf.o:
	g++ fast_sincosf.cpp -c $(FLAGS)

asm:
	g++ fast_sincosf.cpp speedtest.cpp -S $(FLAGS) -fverbose-asm
asm2:
	g++ asmtest.cpp asmtest2.cpp -S $(FLAGS)

clean:
	rm -f *.o *.s tester single speedtest perf.data.old


