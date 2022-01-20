#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

enum COLOR {
    WHITE,
    GREY,
    BLACK
};

class Graph {
    public:
        vector<vector<unsigned int>> adj;
        vector<COLOR> colors;
        unsigned int numVertices;
        unsigned int numEdges;
    
        Graph(unsigned int vertices, unsigned int edges) {
            numVertices = vertices;
            numEdges = edges;
            adj.resize(numVertices+1);
            colors.assign(numVertices+1, WHITE);
        }

        void addEdge(unsigned int v1, unsigned int v2) {
            adj[v1].push_back(v2);

            // Se o vertice tem mais de dois pais, saimos
            if(adj[v1].size() > 2) {
                puts("0");
                exit(EXIT_SUCCESS);
            }
        }

        bool IsDAG() {
            // Encontrar o vertice com out-degree 0
            unsigned int vertice = 0;
            for (size_t i = 1; i < adj.size(); i++) {
                if(adj[i].size() == 0) {
                    vertice = i;
                    break;
                }
            }

            // Se esse vertice não existir, então o grafo não é um DAG
            if(vertice == 0) {
                return false;
            }

            // Fazer DFS  apartir desse vertice 
            return Dfs(vertice);
        }


        bool Dfs(unsigned int v) {
            colors[v] = WHITE;
            for (unsigned int u : adj[v]) {
                if (colors[u] == WHITE) {
                    if(!Dfs(u)) {
                        return false;
                    }
                } else if (colors[u] == GREY) {
                    return false;
                }
            }
            colors[v] = BLACK;
            return true;

        }   
};


void build_inverted_graph(Graph* graph) {
    unsigned int x, y;
    
    for(size_t i = 0; i < graph->numVertices; i++) {
        if(scanf("%u %u", &x, &y) != 2) {
            puts("0");
            exit(EXIT_SUCCESS);
        }

        graph->addEdge(y, x);
    }
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

    Graph* graph = new Graph(numVertices, numEdges);
    build_inverted_graph(graph);

    
    return 0;
}
