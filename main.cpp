#include "dim.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <random>

using namespace std;

double generate_random()
{
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0, 1);
    
    return dis(gen);
}

DIM populateGraph() {

    DIM graph;

    // read the file and populate the graph
    string line;
    ifstream graphFile ("miniGraph.txt");

    if(graphFile.is_open())
    {
        while (getline (graphFile, line))
        {
            // parse the line and insert that edge in the graph with a random probability
            int src = line.at(0);
            int dest = line.at(2);
            double prob = generate_random();
            dim.insert(src, dest, prob);
        }
        graphFile.close();
    }
    dim.set_beta(128); // Set beta=32

    else cout << "Unable to open file";

    return graph;
}

int main(int argc, char *argv[]) {
	
    DIM dim = populateGraph(dim);
	
	for (int v = 0; v < 4; v++)
		printf("Influence of %d is %1.6f\n", v, dim.infest(v));
	printf("Most influential vertex is %d\n", dim.infmax(1)[0]);

	dim.insert(3, 1, 0.8); // Insert edge (3,1) with probability 0.8
	dim.erase(2, 3); // Delete edge (2,3)

	for (int v = 0; v < 4; v++)
		printf("Influence of %d is %1.6f\n", v, dim.infest(v));
	printf("Most influential vertex is %d\n", dim.infmax(1)[0]);

	dim.erase(2); // Delete vertex 2
	dim.change(0, 1, 0.9); // Change probability of edge (0,1) to 0.9

	for (int v = 0; v < 4; v++)
		printf("Influence of %d is %1.6f\n", v, dim.infest(v));
	printf("Most influential vertex is %d\n", dim.infmax(1)[0]);

	return 0;
}

