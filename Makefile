LIBS=-lGL -lGLU -lglut -lGLEW
CC=g++

SOURCES=main_file.cpp tga.cpp glm.cpp latarnia.cpp elementy.cpp
HEADERS=tga.h cube.h latarnia.h glm.h latarnia.h library.h elementy.h
OBJECTS=$(SOURCES:.cpp=.o)

all: main_file

main_file: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@
	
clean:
	-rm -rf *.o main_file
