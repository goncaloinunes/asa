#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#define WHITE  0
#define GREY  1
#define BLACK  2
#define GREY_SECOND_DFS 3
#define BLACK_SECOND_DFS 4
#define COMMON_ANCESTOR  5

class Graph {
    public:
        vector<vector<unsigned int>> adj;
        vector<char> colors;
        unsigned int number_vertices;
        unsigned int number_edges;
    
        Graph(unsigned int vertices, unsigned int edges) {
            number_vertices = vertices;
            number_edges = edges;
            adj.resize(number_vertices+1);
            colors.assign(number_vertices+1, WHITE);
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


        void SecondDfsVisit(unsigned int v, vector<unsigned int>* common_ancestors) {
            for(unsigned int u : adj[v]) {
                if(colors[u] == WHITE || colors[u] == BLACK) {
                    SecondDfsVisit(u, common_ancestors);
                }
            }
            if(colors[v] == BLACK) {
                colors[v] = COMMON_ANCESTOR;
                common_ancestors->push_back(v);
            } else {
                colors[v] = BLACK_SECOND_DFS;
            }
            
            
        }

        
        void LCAs(unsigned int v1, unsigned int v2) {
            vector<unsigned int> common_ancestors;
            vector<vector<unsigned int>> common_ancestors_adj;
            vector<vector<unsigned int>> inverted_adj(adj.size());
            vector<unsigned int> lcas;

            FirstDfsVisit(v1);

            if(colors[v2] == BLACK) {
                common_ancestors.push_back(v2);
                colors[v2] = COMMON_ANCESTOR;
            } else {
                SecondDfsVisit(v2, &common_ancestors);
            }

            // Construir um sub-grafo só de ancestrais comuns, com as arestas originais (não invertidas)
            for(unsigned int u : common_ancestors) {
                for(unsigned int v : adj[u]) {
                    if(colors[v] == COMMON_ANCESTOR) {
                        inverted_adj[v].push_back(u);
                    } 
                }
            }


            // Se o out-degree do vertice for 0, então ele é do mais proximos
            for(unsigned int v : common_ancestors) {
                if(inverted_adj[v].size() == 0) {
                    lcas.push_back(v);
                }
            }
            
            sort(lcas.begin(), lcas.end());

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
