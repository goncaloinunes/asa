#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef vector<vector<unsigned int>> graph;


graph* build_graph(unsigned int numVertices) {
    unsigned int x, y;
    graph graph(numVertices+1);
    unordered_map<unsigned int, unsigned int> map;
    

    for(size_t i = 0; i < numVertices; i++) {
        if(scanf("%u %u", &x, &y) != 2) {
            puts("0");
            exit(EXIT_SUCCESS);
        }

        graph[x].push_back(y);

        // Se o vertice tem mais de dois pais, saimos
        if(++map[y] > 2) {
            puts("0");
            exit(EXIT_SUCCESS);
        }
    }

    return &graph;
}


int main() {
    
    unsigned int v1, v2, numVertices, numEdges;

    scanf("%u %u", &v1, &v2);
    scanf("%u %u", &numVertices, &numEdges);

    // Condição suficiente mas não necessária para o grafo ser um DAG
    if(numVertices < numEdges - 1) {
        puts("0");
        return 0;
    }

    graph *graph = build_graph(numVertices);

    
    return 0;
}
