typedef struct Aresta{
  int vertice;
  int peso;
  struct node* prox;
}Aresta;


typedef struct Grafo{
  int numVertice;
  int numAresta;
  int* visitados;
  struct Aresta** lista_adjacencia;
  int tempo;
}Grafo;


typedef struct Fila {
    int itens[100];
    int prox; //sucessor
    int ant; //anterior
} Fila;


typedef struct Lista{
  int valor;
  struct Lista* prox;
} Lista;
