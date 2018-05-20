
CXX = g++

CXX_FLAGS = -g -Wall

CXX_INCLUDES = 

CXX_LIBS = -pthread


TARGET = main

OBJECTS = main.o imc.o  \
          request_entry.o request_centre.o request_handler.o request.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJECTS) $(CXX_LIBS)

main.o : main.cpp imc.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $@ -c $<

imc.o : imc.cpp request_entry.h request_centre.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $@ -c $<

request_entry.o : request_entry.cpp request_entry.h request_centre.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $@ -c $<

request_centre.o : request_centre.cpp request_centre.h request_handler.h request.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $@ -c $<

request_handler.o : request_handler.cpp request_handler.h request.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $@ -c $<

request.o : request.cpp request.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $@ -c $<



.PHONY : clean
clean : 
	rm *.o
	rm main