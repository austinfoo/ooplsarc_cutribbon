INCDIRS:=/Users/dmielke/Documents/oopl/trees/googletest/googletest/include
LIBDIRS:=/Users/dmielke/Documents/oopl/trees/googletest/googletest/make

FILES :=                                        \
    .travis.yml                                 \
    dijkstra-tests/EID-RunCutRibbon.in   \
    dijkstra-tests/EID-RunCutRibbon.out  \
    dijkstra-tests/EID-TestCutRibbon.c++ \
    dijkstra-tests/EID-TestCutRibbon.out \
    CutRibbon.c++                        \
    CutRibbon.h                          \
    CutRibbon.log                        \
    html                                        \
    RunCutRibbon.c++                     \
    RunCutRibbon.in                      \
    RunCutRibbon.out                     \
    TestCutRibbon.c++                    \
    TestCutRibbon.out                    \
    CutRibbonBundle.c++

# Call gcc and gcov differently on Darwin
ifeq ($(shell uname), Darwin)
  CXX      := g++
  GCOV     := gcov
  VALGRIND := echo Valgrind not available on Darwin
else
  CXX      := g++-4.8
  GCOV     := gcov-4.8
  VALGRIND := valgrind
endif

CXXFLAGS   := -pedantic -std=c++11 -Wall -I$(INCDIRS)
LDFLAGS    := -lgtest -lgtest_main -pthread -L$(LIBDIRS)
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunCutRibbon
	rm -f RunCutRibbon.tmp
	rm -f TestCutRibbon
	rm -f TestCutRibbon.tmp
	rm -f CutRibbonBundle

config:
	git config -l

bundle:
	cat CutRibbon.h CutRibbon.c++ RunCutRibbon.c++ | sed -e "s/#include \"CutRibbon.h\"//g" > CutRibbonBundle.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) CutRibbonBundle.c++ -o CutRibbonBundle

scrub:
	make  clean
	rm -f  CutRibbon.log
	rm -rf dijkstra-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunCutRibbon.tmp TestCutRibbon.tmp

RunCutRibbon: CutRibbon.h CutRibbon.c++ RunCutRibbon.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) CutRibbon.c++ RunCutRibbon.c++ -o RunCutRibbon

RunCutRibbon.tmp: RunCutRibbon
	./RunCutRibbon < RunCutRibbon.in > RunCutRibbon.tmp
	diff RunCutRibbon.tmp RunCutRibbon.out

TestCutRibbon: CutRibbon.h CutRibbon.c++ TestCutRibbon.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) CutRibbon.c++ TestCutRibbon.c++ -o TestCutRibbon $(LDFLAGS)

TestCutRibbon.tmp: TestCutRibbon
	./TestCutRibbon                                                     >  TestCutRibbon.tmp 2>&1
	$(VALGRIND) ./TestCutRibbon                                         >> TestCutRibbon.tmp
	$(GCOV) -b CutRibbon.c++     | grep -A 5 "File 'CutRibbon.c++'"     >> TestCutRibbon.tmp
	$(GCOV) -b TestCutRibbon.c++ | grep -A 5 "File 'TestCutRibbon.c++'" >> TestCutRibbon.tmp
	cat TestCutRibbon.tmp
