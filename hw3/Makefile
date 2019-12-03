all:stringparser
stringparser: stringparser.cpp stackstring.o ulliststr.o
	g++ -g -Wall stringparser.cpp stackstring.o ulliststr.o -o stringparser -std=c++11
stackstring.o: stackstring.cpp stackstring.h
	g++ -g -Wall -c stackstring.cpp -o stackstring.o -std=c++11
ulliststr.o: ulliststr.cpp ulliststr.h
	g++ -g -Wall -c ulliststr.cpp -o ulliststr.o -std=c++11
clean: 
	rm -rf *o