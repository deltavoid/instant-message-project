

CXX = g++

CXX_FLAGS = -g #-Wall #-std=c++11

server : *.cpp *.h
	$(CXX) $(CXX_FLAGS)  -o server *.cpp -lpthread

.PHONY : clean
clean :
	rm server
	