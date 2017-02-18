output: main.o net.o neuron.o parser.o
		g++ main.o net.o neuron.o parser.o -o output

main.o: main.cpp gnuplot_i.hpp
		g++ -c main.cpp

net.o: net.cpp net.h
		g++ -c net.cpp

neuron.o: neuron.cpp neuron.h
		g++ -c neuron.cpp

parser.o: parser.cpp parser.h
		g++ -c parser.cpp

clean:
		rm *.o output
