all: parser

parser:stackint.h circular_list_int.h parser.cpp
	g++ -g -Wall -std=c++11 parser.cpp stackint.cpp circular_list_int.cpp -o parser

clean:
	rm -rf parser