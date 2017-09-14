TARGET = game

CFLAGS = g++ -std=c++11

LFLAGS = -lGL -lGLU -lGLEW -L/usr/include/GL -lglfw -L/usr/include/GLFW -lX11 -lXxf86vm -lXrandr -lpthread -lXi

I = -I include

SP = ./src/

SRC = $(SP)main.cpp\
	  $(SP)MainGame.cpp

all : $(TARGET)

$(TARGET) :
	@$(CFLAGS) $(I) $(SRC) -o $(TARGET) $(LFLAGS)

clean:
	@rm -rf $(TARGET) *.swp *.swo src/*.swp src/*.swo

re: clean all
