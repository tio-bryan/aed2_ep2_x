// EP 2 - AED II - Tarde - 2018 - Profº Xavier
// Nome: Bryan Munekata
// NUSP: 9911444

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct reg {
    int vertice;
    float peso;
    struct reg * prox;
} Reg;

typedef struct reg2 {
    int vertice;
    int cor; // 0 p/ branco, 1 p/ cinza, 2 p/ preto
    int d;
    int pi;
    struct reg2 * prox;
} Reg2;

int v;
Reg2 resultado[10000];
int tempo = 0;

// int dfs_visit(Reg lista_adj[], int vertice) {
//     tempo += 1;
//     resultado[vertice].d = tempo;
//     resultado[vertice].cor = 1;

//     Reg * tmp = &lista_adj[vertice];
    
//     while (tmp->prox != NULL) {
//         tmp = tmp->prox;
//         if (resultado[tmp->vertice].cor == 0) {
//             resultado[tmp->vertice].pi = vertice;
//             dfs_visit(lista_adj, tmp->vertice);
//         }
//     }

//     resultado[vertice].cor = 2;
//     tempo += 1;
//     resultado[vertice].f = tempo;

//     return 0;
// }

// Fila dos vértices
int fila[10000];

int enqueue(int v) {
    int tmp = fila[0];
    int n = 0;
    while (tmp != -1) {
        tmp = fila[++n];
    }
    fila[n] = v;

    return 0;
}

int dequeue() {
    int dequeue_number = fila[0];

    for (int i = 0; i < 10000; i++) {
        fila[i] = fila[i + 1];
    }

    return dequeue_number;
}

int bfs(Reg lista_adj[], int vertice) {
    for (int i = 0; i < v; i++) {
        if (i != vertice) {
            resultado[i].cor = 0;
            resultado[i].d = 2147483647; // Valor max do int
            resultado[i].pi = -1;
        }
    }

    resultado[vertice].cor = 1;
    resultado[vertice].d = 0;
    resultado[vertice].pi = -1;

    enqueue(resultado[vertice].vertice);
    while (fila[0] != -1) {
        int u = dequeue();

        Reg * tmp = &lista_adj[u - 1];
    
        while (tmp->prox != NULL) {
            tmp = tmp->prox;
            if (resultado[tmp->vertice].cor == 0) {
                resultado[tmp->vertice].cor = 1;
                resultado[tmp->vertice].d = resultado[u - 1].d + 1;
                resultado[tmp->vertice].pi = u;
                enqueue(resultado[tmp->vertice].vertice);
            }
        }

        resultado[u - 1].cor = 2;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    //Abre txt
    FILE * fp = fopen(argv[1], "r");

    //Le a primeira linha e armazena o numero de vertices no 'v'
    fscanf(fp, "%i", &v);

    //Monta lista_adj de adjacencia
    Reg lista_adj[v - 1];

    for (int i = 0; i < v; i++) {
        lista_adj[i].vertice = i + 1;
        lista_adj[i].prox = NULL;
    }

    // Monta lista_adj de resultado
    for (int i = 0; i < v; i++) {
        resultado[i].vertice = i + 1;
        resultado[i].cor = 0;
        resultado[i].d = -1;
        resultado[i].pi = -1;
        resultado[i].prox = NULL;
    }

    int origem, destino;
    float peso;
    //Le linha por linha e insere vertices na lista_adj de adjacencia
    while (fscanf(fp, "%i %i %f", &origem, &destino, &peso) != EOF) {
        //printf("%i\n", peso);

        Reg * no_vertice = (Reg *) malloc((int)sizeof(Reg));

        no_vertice->vertice = destino;
        no_vertice->peso = peso;
        no_vertice->prox = NULL;

        Reg * tmp = &lista_adj[origem];

        while (tmp->prox != NULL) {
            tmp = tmp->prox;
        }

        tmp->prox = no_vertice;

        //insere vertices no sentido contrario da lista_adj de adjacencia
        Reg * no_vertice_invertido = (Reg *) malloc((int)sizeof(Reg));

        no_vertice_invertido->vertice = origem;
        no_vertice_invertido->peso = peso;
        no_vertice_invertido->prox = NULL;

        Reg * tmp1 = &lista_adj[destino];

        while (tmp1->prox != NULL) {
            tmp1 = tmp1->prox;
        }

        tmp1->prox = no_vertice_invertido;
    }
    
    fclose(fp);

    // // Algoritmo do DFS. Para cada vertice, se for branco aplica dfs_visit
    // for (int i = 0; i < v; i++) {
    //     if (resultado[i].cor == 0) {
    //         dfs_visit(lista_adj, i);
    //     }
    // }

    for (int i = 0; i < 10000; i++) {
        fila[i] = -1;
    }

    // Executa BFS
    bfs(lista_adj, 0);

    // Imprime resultados
    for (int i = 0; i < v; i++) {
        printf("%i %i %i\n", resultado[i].vertice, resultado[i].d,
                                resultado[i].pi);
    }

    return 0;
}