# Run 'make' from active directory to compile
# Run 'make clean' to remove the object files

# Written by Mark Bromley (March 2014)

analyze: analyze.o data.o
	g++ analyze.o data.o -o analyze

analyze.o: analyze.cpp data.hpp
	g++ -c analyze.cpp -o analyze.o

data.o: data.cpp data.hpp
	g++ -c data.cpp -o data.o

clean:
	rm -f *.o

veryclean: clean
	rm -f analyze
