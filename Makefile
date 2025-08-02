CXX = g++
CXXFLAGS = -IC:/Users/Toshiba/Documents/SFML-2.6.2/include
LDFLAGS = -LC:/Users/Toshiba/Documents/SFML-2.6.2/lib \
          -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = $(wildcard main.cpp game/classes/*.cpp)
OBJ = $(SRC:.cpp=.o)
OUT = main.exe

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	@echo Cleaning up...
	@rm -f $(OBJ) $(OUT)
