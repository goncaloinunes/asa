#include <iostream>

using namespace std;


int main() {
    unsigned int x, y, v1, v2, numVertices, numEdges;

    scanf("%u %u", &v1, &v2);
    scanf("%u %u", &numVertices, &numEdges);

    // Condição suficiente mas não necessária para o grafo ser um DAG
    if(numVertices < numEdges - 1) {
        puts("0");
    }

    while(scanf("%u %u", &x, &y)) {
        //adicionar x e y a uma estrutura de dados
    }

    
    return 0;
}
