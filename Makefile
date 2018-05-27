CXX = g++
CXXFLAGS = -g -Wall -O0
CXXSRCS = matmul.cpp matmul-driver.cpp 
BIN = mm
UNIX4 = tnewma03@unix4.csc.calpoly.edu

all:
	$(CXX) $(CXXFLAGS) -c $(CXXSRCS)
	$(CXX) $(CXXFLAGS) -o $(BIN) *.o

run :
	./mm > myOutput.gold
	./compare.py myOutput.gold output.gold

perf :
	perf stat -e cache-misses -e cache-references ./mm > myPerf.txt

ssh : 
	ssh $(UNIX4)

scpf :
	scp ./* $(UNIX4):~/cpe315/lab5

scpm :
	scp matmul.cpp $(UNIX4):~/cpe315/lab5

clean:
	rm -f *.o
