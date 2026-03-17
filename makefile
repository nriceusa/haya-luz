SOURCES = $(shell find ./Source -name "*.cpp")

all:
	g++ -std=c++11 $(SOURCES) -o haya-luz
