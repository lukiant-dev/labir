LIBS=-lGL -lglut -lGLEW
CC=g++

SOURCES=main_file.cpp tga.cpp latarnia.cpp elementy.cpp glm.cpp
HEADERS=tga.h cube.h latarnia.h elementy.h glm.h
OBJECTS=$(SOURCES:.cpp=.o)

all: main_file

main_file: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@
	
clean:
	-rm -rf *.o main_file
