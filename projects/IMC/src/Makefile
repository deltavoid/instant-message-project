
CXX = g++

CXX_FLAGS = -g -Wall

CXX_INCLUDES = 

CXX_LIBS = -pthread


TARGET = main


all : $(TARGET)


$(TARGET) : *.cpp *.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $(TARGET) *.cpp *.h $(CXX_LIBS)


.PHONY : clean
clean : 
	rm *.o
	rm main