
all: main.cpp BST.cpp libs/TerminalGraphs/TerminalGraphs.cpp
	g++ -g -Wall main.cpp BST.cpp libs/TerminalGraphs/TerminalGraphs.cpp -o $(obj)main.o
