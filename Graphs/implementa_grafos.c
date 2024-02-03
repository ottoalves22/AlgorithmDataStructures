#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define retorno 12616161

Grafo* cria_grafo(int vertices, int arestas){
  Grafo* g1 = malloc(sizeof(Grafo));
  g1->numVertice = vertices;
  g1->numAresta = arestas;

  g1->lista_adjacencia = malloc(vertices * sizeof(Aresta));
  g1->visitados = malloc(vertices* sizeof(int));

  for(int i=0; i<vertices; i++){
    g1->lista_adjacencia[i] = NULL;
    g1->visitados[i] = 0;
  }
  g1->tempo = 0;

  return g1;
}


void exibe_grafo(Grafo* g1, FILE* file_out){
  for(int i=0; i<g1->numVertice; i++){
        struct Aresta* temp = g1->lista_adjacencia[i];
        while (temp) {
          if(temp->peso!=retorno){
            printf("%d %d %d\n", i, temp->vertice, temp->peso);
            fprintf(file_out, "%d %d %d\n", i, temp->vertice, temp->peso);
          }
          temp = temp->prox;
        }
  }
}


Aresta* cria_aresta(int chave, int peso){
  Aresta* nova_aresta = malloc(sizeof(Aresta));
  nova_aresta->vertice = chave;
  nova_aresta->peso = peso;
  nova_aresta->prox = NULL;
  return nova_aresta;
}


void adiciona_aresta(Grafo* g1, int origem, int destino, int peso){
  //ida
  Aresta* a1 = cria_aresta(destino, peso);
  a1->prox = g1->lista_adjacencia[origem];
  g1->lista_adjacencia[origem] = a1;

  //volta
  a1 = cria_aresta(origem, retorno);
  a1->prox = g1->lista_adjacencia[destino];
  g1->lista_adjacencia[destino] = a1;
}


Fila* cria_fila(){
  Fila* f1 = malloc(sizeof(Fila));
  f1->prox = -1;
  f1->ant = -1;
  for(int i=0; i<100; i++){
    f1->itens[i] = -1;
  }
  return f1;
}


int fila_vazia(Fila* f1){
  if(f1->ant==-1){
    return 1;
  }
  return 0;
}


void push(Fila* f1, int valor){
  if(f1->ant==99){
    printf("\nFila cheia!");
  }
  else {
    if(f1->prox==-1){
      f1->prox = 0;
    }
    f1->ant++;
    f1->itens[f1->ant] = valor;
  }
}


int pop(Fila* f1){
  int item;
  if(fila_vazia(f1)){
    item = -1;
    printf("fila vazia\n");
  }
  else {
    item = f1->itens[f1->prox];
    f1->prox++;
    if(f1->prox > f1->ant){
      //reseta fila
      f1->prox = f1->ant = -1;
    }
  }
  return item;
}


//Busca em profundidade
void BP(Grafo* g1, int inicio, FILE* file_out){
  Aresta* listaAdjacenciaInicio = g1->lista_adjacencia[inicio];
  Aresta* aux = listaAdjacenciaInicio;

  g1->visitados[inicio] = 1;
  printf("%d ", inicio);
  fprintf(file_out, "%d ", inicio);

  while(aux!=NULL){
    int vertice_conexo = aux->vertice;
    if(g1->visitados[vertice_conexo]==0){
      BP(g1, vertice_conexo, file_out);
    }
    aux = aux->prox;
  }
}


void passeioBP(Grafo* g1, int inicio, FILE* file_out, Fila* f1){
  Aresta* listaAdjacenciaInicio = g1->lista_adjacencia[inicio];
  Aresta* aux = listaAdjacenciaInicio;

  g1->visitados[inicio] = 1;
  push(f1, inicio);
  printf("\n");
  fprintf(file_out, "\n");
  for(int i=0; i<100; i++){
    if(f1->itens[i]!=-1){
      printf("%d ", f1->itens[i]);
      fprintf(file_out, "%d ", f1->itens[i]);

    }
  }
  while(aux!=NULL){
    int vertice_conexo = aux->vertice;
    if(g1->visitados[vertice_conexo]==0){
      passeioBP(g1, vertice_conexo, file_out, f1);
    }
    aux = aux->prox;
  }
}

//Busca em largura
void BL(Grafo* g1, int inicio, FILE* file_out){
  Fila* f1 = cria_fila();

  //reseta visitados
  for(int i=0; i<g1->numVertice; i++){
      g1->visitados[i] = 0;
  }

  g1->visitados[inicio] = 1;
  push(f1, inicio);

  while(!fila_vazia(f1)){
    int vertice_atual = pop(f1);
    printf("%d ", vertice_atual);
    fprintf(file_out, "%d ", vertice_atual);
    Aresta* aresta_auxiliar = g1->lista_adjacencia[vertice_atual];
    while(aresta_auxiliar){
      int vert_adj = aresta_auxiliar->vertice;

      if(g1->visitados[vert_adj]==0){
        g1->visitados[vert_adj] = 1;
        push(f1, vert_adj);
      }
      aresta_auxiliar = aresta_auxiliar->prox;
    }
  }
}


void passeioBL(Grafo* g1, int inicio, FILE* file_out){
  Fila* f1 = cria_fila();

  //reseta visitados
  for(int i=0; i<g1->numVertice; i++){
      g1->visitados[i] = 0;
  }

  g1->visitados[inicio] = 1;
  push(f1, inicio);

  while(!fila_vazia(f1)){
    int vertice_atual = pop(f1);
    printf("\n");
    fprintf(file_out, "\n");
    for(int i=0; i<100; i++){
      if(f1->itens[i]!=-1){
        printf("%d ", f1->itens[i]);
        fprintf(file_out, "%d ", f1->itens[i]);

      }
    }
    Aresta* aresta_auxiliar = g1->lista_adjacencia[vertice_atual];
    while(aresta_auxiliar){
      int vert_adj = aresta_auxiliar->vertice;

      if(g1->visitados[vert_adj]==0){
        g1->visitados[vert_adj] = 1;
        push(f1, vert_adj);
      }
      aresta_auxiliar = aresta_auxiliar->prox;
    }
  }
}

//componentes conectados
void componentes_conextos(Grafo* g, int inicio, FILE* file_out){
  Grafo* g1 = g;
  Aresta* listaAdjacenciaInicio = g1->lista_adjacencia[inicio];
  Aresta* aux = listaAdjacenciaInicio;

  g1->visitados[inicio] = 1;
  printf("%d ", inicio);
  fprintf(file_out, "%d ", inicio);
  while(aux!=NULL){
    int vertice_conexo = aux->vertice;
    if(g1->visitados[vertice_conexo]==0){
      BP(g1, vertice_conexo, file_out);
    }
    aux = aux->prox;
  }
}
