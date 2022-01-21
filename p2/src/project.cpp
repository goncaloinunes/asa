#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#define WHITE  0
#define GREY  1
#define BLACK  2
#define GREY_SECOND_DFS 3
#define COMMON_ANCESTOR  4

class Graph {
    public:
        vector<vector<unsigned int>> adj;
        vector<char> colors;
        vector<unsigned int> original_out_degrees;
        unsigned int number_vertices;
        unsigned int number_edges;
    
        Graph(unsigned int vertices, unsigned int edges) {
            number_vertices = vertices;
            number_edges = edges;
            adj.resize(number_vertices+1);
            colors.assign(number_vertices+1, WHITE);
            original_out_degrees.assign(number_vertices+1, 0);
        }

        void addEdge(unsigned int v1, unsigned int v2) {
            adj[v1].push_back(v2);

            // Se o vertice tem mais de dois pais, saimos
            if(adj[v1].size() > 2) {
                puts("0");
                exit(EXIT_SUCCESS);
            }

            original_out_degrees[v2]++;
        }

        bool IsDAG() {
            // Condição suficiente mas não necessária para o grafo não ser um DAG
            if(number_vertices < number_edges - 1) {
                return false;
            }

            for (size_t v = 1; v < number_vertices+1; v++) {
                if (colors[v] == WHITE && IsDagVisit(v)) {
                    colors.assign(number_vertices+1, WHITE);
                    return false;
                }
            }

            colors.assign(number_vertices+1, WHITE);
            return true;
        }


        bool IsDagVisit(unsigned int v) {
            colors[v] = GREY;
            for(unsigned int u : adj[v]) {
                if (colors[u] == WHITE) {
                    if(IsDagVisit(u)) {
                        return true;
                    }
                } else if (colors[u] == GREY) {
                    return true;
                }
            }
            colors[v] = BLACK;
            
            return false;

        }

        void FirstDfsVisit(unsigned int v) {
            colors[v] = GREY;
            for(unsigned int u : adj[v]) {
                if(colors[u] == WHITE) {
                    FirstDfsVisit(u);
                }
            }
            colors[v] = BLACK;
        }

        void unmarkParents(unsigned int v) {
            for(unsigned int u : adj[v]) {
                if(colors[u] == BLACK) {
                    FirstDfsVisit(u);
                }
            }
            colors[v] = GREY;
        }

        void SecondDfsVisit(unsigned int v, list<unsigned int>* lcas) {
            colors[v] = GREY_SECOND_DFS;
            for(unsigned int u : adj[v]) {
                if(colors[u] == WHITE) {
                    SecondDfsVisit(u, lcas);
                } else if (colors[u] == BLACK) {
                    for(unsigned int parent : adj[v]) {
                        lcas->remove(parent);
                    }

                    unmarkParents(u);
                    lcas->push_front(u);
                    colors[u] = COMMON_ANCESTOR;
                    continue;
                }
            }
            colors[v] = BLACK;
            
        }

        void LCAs(unsigned int v1, unsigned int v2) {
            list<unsigned int> lcas;

            FirstDfsVisit(v1);

            if(colors[v2] == BLACK) {
                lcas.push_front(v2);
                colors[v2] = COMMON_ANCESTOR;
            } else {
                SecondDfsVisit(v2, &lcas);
            }

            
            lcas.sort();

            if(lcas.size() > 0) {
                for(unsigned int v : lcas) {
                    cout << v << " ";
                }
                cout << endl;
                return;
            }

            puts("-");

        }


};


void build_inverted_graph(Graph* graph) {
    unsigned int x, y;
    
    for(size_t i = 0; i < graph->number_edges; i++) {
        if(scanf("%u %u", &x, &y) != 2) {
            puts("0");
            exit(EXIT_SUCCESS);
        }

        graph->addEdge(y, x);
    }
}


int main() {
    
    unsigned int v1, v2, number_vertices, number_edges;

    scanf("%u %u", &v1, &v2);
    scanf("%u %u", &number_vertices, &number_edges);

    Graph* graph = new Graph(number_vertices, number_edges);
    build_inverted_graph(graph);

    if(!graph->IsDAG()) {
        puts("0");
        return 0;
    }

    graph->LCAs(v1, v2);
    
    return 0;
}
