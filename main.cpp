#include "dim.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <random>
#include <typeinfo>

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
    graph.init();

    graph.set_beta(128); // Set beta=32

    // read the file and populate the graph
    string line;
    ifstream graphFile ("miniGraph.txt");

    //create a vector to store the nodes
    vector<int> nodes;
    vector<int> pairOfNodes;

    if(graphFile.is_open())
    {
        int posOfSpace;
        while (getline (graphFile, line))
        {
            posOfSpace = line.find(" ");
            int src = stoi(line.substr(0, posOfSpace));
            int dest = stoi(line.substr(posOfSpace));
                
            //cout << "Src: " << src << " Dest: " << dest << endl;
            double prob = generate_random();

            if(find(nodes.begin(), nodes.end(), src) != nodes.end()) {
                /* v contains x */
            } else {
                //cout << "Inserting node " << src << endl;
                nodes.push_back(src);
                graph.insert(src);
            }
            if(find(nodes.begin(), nodes.end(), dest) != nodes.end()) {
                /* v contains x */
            } else {
                //cout << "Inserting node " << dest << endl;
                nodes.push_back(dest);
                graph.insert(dest);
            }
            
            graph.insert(src, dest, prob);
        }
        graphFile.close();
    }

    else cout << "Unable to open file";

    return graph;
}

int main(int argc, char *argv[]) {
	
    DIM dim = populateGraph();

	// for (int v = 0; v < dim.numOfNodes(); v++)
	// 	printf("Influence of %d is %1.6f\n", v, dim.infest(v));
	printf("Most influential vertex is %d\n", dim.infmax(1)[0]);

	return 0;
}

// #include "dim.hpp"

// using namespace std;

// int main(int argc, char *argv[]) {
// 	DIM dim;
// 	dim.init(); // Call at the beginning

// 	dim.insert(0); // Insert vertex 0
// 	dim.insert(1); // Insert vertex 1
// 	dim.insert(0, 1, 0.4); // Insert edge (0,1) with probability 0.5
// 	dim.set_beta(128); // Set beta=32

// 	dim.insert(2); // Insert vertex 2
// 	dim.insert(3); // Insert vertex 3

// 	dim.insert(1, 2, 0.5); // Insert edge (1,2) with probability 0.6
// 	dim.insert(2, 0, 0.6); // Insert edge (2,0) with probability 0.7
// 	dim.insert(2, 3, 0.7); // Insert edge (2,3) with probability 0.8

//     dim.insert(4);
//     dim.insert(5);

//     dim.insert(2, 4, 0.9);
//     dim.insert(3, 5, 0.8);
//     dim.insert(4, 5, 0.3);
//     dim.insert(1, 3, 0.7);


// 	for (int v = 0; v < 6; v++)
// 		printf("Influence of %d is %1.6f\n", v, dim.infest(v));
// 	printf("Most influential vertex is %d\n", dim.infmax(1)[0]);

// 	dim.insert(3, 1, 0.8); // Insert edge (3,1) with probability 0.8
// 	dim.erase(2, 3); // Delete edge (2,3)

// 	for (int v = 0; v < 6; v++)
// 		printf("Influence of %d is %1.6f\n", v, dim.infest(v));
// 	printf("Most influential vertex is %d\n", dim.infmax(1)[0]);

// 	dim.erase(2); // Delete vertex 2
// 	dim.change(0, 1, 0.9); // Change probability of edge (0,1) to 0.9

// 	for (int v = 0; v < 6; v++)
// 		printf("Influence of %d is %1.6f\n", v, dim.infest(v));
// 	printf("Most influential vertex is %d\n", dim.infmax(1)[0]);

// 	return 0;
// }