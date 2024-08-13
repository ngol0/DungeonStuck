# Flag
CXX := g++
LANGUAGE_FLAG := -std=c++20 
COMPILER_FLAG := -Wall -Wextra -Wno-deprecated-volatile -Wno-unused-parameter
LINKER_FLAG := `sdl2-config --libs --cflags` -lSDL2_image -llua
INCLUDE_FLAG := -I./libs

# Define your source files here
SRCS=src/**/*.cpp src/*.cpp libs/imgui/*.cpp

# Define object files (replace .cc with .o)
OBJS=$(SRCS:.cc=.o)

TARGET := gameengine

# Rule to build the target
$(TARGET): $(OBJS)
		$(CXX) $(COMPILER_FLAG) $(LANGUAGE_FLAG) $(OBJS) $(INCLUDE_FLAG) $(LINKER_FLAG) -o $(TARGET)

run:
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)