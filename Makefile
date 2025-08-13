CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

# Object files
SRCS = main.cpp simulation.cpp memory_manager.cpp firstfit.cpp bestfit.cpp memory_request.cpp
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = sim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Generic compile rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
