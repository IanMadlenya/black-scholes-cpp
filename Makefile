all: main.cpp
	g++ -Wall main.cpp derivative_pricer.cpp -o main

clean:
	rm main
