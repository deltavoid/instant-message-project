
CXX = g++

CXX_FLAGS = -g

CXX_INCLUDES = 

CXX_LIBS = 


TARGET = main

OBJECTS = main.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXX_FLAGS) -o $@ $(OBJECTS) $(CXX_LIBS)

main.o : main.cpp imc.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $@ -c $<


.PHONY : clean
clean : 
	rm *.o
	rm main