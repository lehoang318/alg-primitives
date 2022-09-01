PROJ_NAME = graph

.PHONY: all
all: $(PROJ_NAME).cpp
	g++ -Wall -o $(PROJ_NAME) $(PROJ_NAME).cpp

.PHONY: kruskal
kruskal:
	g++ -Wall -o kruskal kruskal.cpp

.PHONY: djset
set: djset.cpp
	g++ -Wall -o djset djset.cpp

.PHONY: clean
clean:
	rm -rf $(PROJ_NAME) *.o
