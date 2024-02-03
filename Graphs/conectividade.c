#include "implementa_grafos.c"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
	FILE *file;
	file = fopen("entrada.txt", "r");
	FILE* file_out;
    file_out= fopen("saida.txt", "w");
    int j=0;
    int i;
    int string_auxiliar[200];
    if(file!=NULL){
	    fscanf(file, "%d", &i);
		while(!feof(file)){
            string_auxiliar[j] = i;
			fscanf (file, "%d", &i);
			j++;
			string_auxiliar[j] = i;
		}
  	fclose(file);
  }
  int num_vertices = string_auxiliar[0];
  int num_arestas = string_auxiliar[1];

    //declaracao do grafo
	Grafo* g1 = cria_grafo(num_vertices, num_arestas);

    // insercao das arestas
  for(int y=2; y<j; y+=3){
  	adiciona_aresta(g1, string_auxiliar[y], string_auxiliar[y+1], string_auxiliar[y+2]);
  }

	printf("%d %d \n", g1->numVertice, g1->numAresta);
	fprintf(file_out, "%d %d  \n", g1->numVertice, g1->numAresta);

  //exibe grafico de acordo com a entrada
	exibe_grafo(g1, file_out);

  printf("\nBL:\n");
	fprintf(file_out, "\nBL:\n");

	BL(g1, 0, file_out);

	//encontra desconexos
	for(int i=0; i<g1->numVertice; i++){
		if(g1->visitados[i]==0){
			BL(g1, i, file_out);
			break;
		}
  }

	//reseta visitados
	for(int i=0; i<g1->numVertice; i++){
      g1->visitados[i] = 0;
  }

	printf("\n\nCaminhos BL:");
	fprintf(file_out, "\n\nCaminhos BL:");

	passeioBL(g1, 0, file_out);

	for(int i=0; i<g1->numVertice; i++){
		if(g1->visitados[i]==0){
			passeioBL(g1, i, file_out);
		}
  }

	for(int i=0; i<g1->numVertice; i++){
      g1->visitados[i] = 0;
  }

	printf("\n\nBP:\n");
	fprintf(file_out, "\n\nBP:\n");

	BP(g1, 0, file_out);

	//encontra desconexos
	for(int i=0; i<g1->numVertice; i++){
		if(g1->visitados[i]==0){
			BP(g1, i, file_out);
		}
  }

	//reseta visitados
	for(int i=0; i<g1->numVertice; i++){
      g1->visitados[i] = 0;
  }

  printf("\n\nCaminhos BP:");
	fprintf(file_out, "\n\nCaminhos BP:");

	Fila* fila_aux = cria_fila();

	passeioBP(g1, 0, file_out, fila_aux);

	for(int i=0; i<100; i++){
    fila_aux->itens[i] = -1;
  }

	//encontra desconexos
	for(int i=0; i<g1->numVertice; i++){
		if(g1->visitados[i]==0){
			printf("\n");
			passeioBP(g1, i, file_out, fila_aux);
		}
  }

	for(int i=0; i<g1->numVertice; i++){
      g1->visitados[i] = 0;
  }

  printf("\n\nComponentes Conectados:");
	fprintf(file_out, "\n\nComponentes Conectados:");

	int contador_aux = 1;

	for(int i=0; i<g1->numVertice; i++){
		if(g1->visitados[i]==0){
			printf("\nC%d: ", contador_aux);
			fprintf(file_out, "\nC%d: ", contador_aux);
			componentes_conextos(g1, i, file_out);
			contador_aux++;
		}
  }

	for(int i=0; i<g1->numVertice; i++){
      g1->visitados[i] = 0;
  }

  printf("\n\nVertices de articulacao:\n");
	fprintf(file_out, "\n\nVertices de articulacao:\n");

	

    return 0;
}
