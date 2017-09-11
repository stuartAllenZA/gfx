TARGET = bomber

CC = g++ -std=c++11

FLAGS = -lGL -lGLU -lGLEW -L/usr/include/GL -lglfw -L/usr/include/GLFW -lX11 -lXxf86vm -lXrandr -lpthread -lXi

I = -I include -I Core/includes

E = ./Core/entities/*.cpp

M = ./Core/models/*.cpp

R = ./Core/render/*.cpp

S = ./Core/sprite/*.cpp

U = ./Core/utils/*.cpp

SRC = ./src/*.cpp

all : $(TARGET)

$(TARGET) :
	$(CC) $(I) $(E) $(M) $(R) $(S) $(U) $(SRC) main.cpp -o $(TARGET) $(FLAGS)

clean:
	rm -rf $(TARGET)

re: clean all
