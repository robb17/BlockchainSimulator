#------------------------------------------------------------
# File: Makefile --------------------------------------------
# Credit due to Alice E. Fischer and Michael J. Fischer.
# Macro defs
CXXFLAGS = -O1 -g -Wall -std=c++17
OBJ = main.o tools.o block.o blockchain.o SPtr.o Serial.o agent.o simulator.o population.o inventory.o
TARGET = blockchain
#------------------------------------------------------------
# Rules
all: $(TARGET)
$(TARGET): $(OBJ)
		$(CXX) -o $@ $(OBJ)
clean:
		rm -f $(OBJ) $(TARGET)
#------------------------------------------------------------
# Dependencies
Serial.o: Serial.cpp Serial.hpp
main.o: main.cpp blockchain.hpp tools.hpp block.hpp SPtr.hpp Serial.hpp simulator.hpp agent.hpp population.hpp inventory.hpp
blockchain.o: blockchain.cpp block.hpp tools.hpp SPtr.hpp Serial.hpp
block.o: block.cpp SPtr.hpp Serial.hpp tools.hpp
SPtr.o: SPtr.cpp Serial.hpp block.hpp tools.hpp
tools.o: tools.cpp tools.hpp
agent.o: agent.cpp tools.hpp blockchain.hpp block.hpp SPtr.hpp Serial.hpp
simulator.o: simulator.hpp tools.hpp agent.hpp population.hpp blockchain.hpp block.hpp SPtr.hpp Serial.hpp inventory.hpp
population.o: population.cpp population.hpp agent.hpp tools.hpp blockchain.hpp block.hpp SPtr.hpp Serial.hpp inventory.hpp
inventory.o: inventory.cpp tools.hpp blockchain.hpp block.hpp tools.hpp SPtr.hpp Serial.hpp