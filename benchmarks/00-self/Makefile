CPPFLAGS = -std=c++11 -O3 -Wall -pedantic
01-omp: 01-omp.cpp
	$(MAKE) clean;\
	g++ $(CPPFLAGS) -fopenmp -DBARRY_USE_OMP 01-omp.cpp -o 01-omp-pll.o && \
		./01-omp-pll.o && \
		g++ $(CPPFLAGS) 01-omp.cpp -o 01-omp.o && \
		./01-omp.o
clean:
	rm *.o
