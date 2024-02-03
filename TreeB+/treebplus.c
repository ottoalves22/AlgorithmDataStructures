//Otto Alves - NUSP 10843361

#include<stdlib.h>
#include<stdio.h>

#define T 3

struct vertice {
    int numChaves;
    int chaves[T-1];
    struct vertice *filhos[T];
} *raiz = NULL;


enum chaveStatus {
    Duplicado, BuscaFalha, Sucesso, InsereI, MenosChaves
};


void insere(int chave);
void removeChave(int x);
enum chaveStatus ins(struct vertice *r, int x, int *y, struct vertice **u);
int buscaPost(int x, int *arr_chaves, int n);
enum chaveStatus del(struct vertice *r, int x);


void insere(int chave){
    struct vertice *novoVertice;
    int chaveAcima;
    enum chaveStatus valor;
    valor = ins(raiz, chave, &chaveAcima, &novoVertice);
    if(valor==Duplicado){
      return;
    }
    if(valor==InsereI){
        struct vertice *raizAcima = raiz;
        raiz = (struct vertice *) malloc(sizeof(struct vertice));
        raiz->numChaves = 1;
        raiz->chaves[0] = chaveAcima;
        raiz->filhos[0] = raizAcima;
        raiz->filhos[1] = novoVertice;
    }
}


enum chaveStatus ins(struct vertice *x, int chave, int *chaveAcima, struct vertice **novoVertice){
    struct vertice *newx, *lastx;
    int pos, i, n, splitPos;
    int novaChave, lastchave;
    enum chaveStatus valor;
    if(x==NULL){
        *novoVertice = NULL;
        *chaveAcima = chave;
        return InsereI;
    }
    n = x->numChaves;
    pos = buscaPost(chave, x->chaves, n);
    if(pos<n && chave==x->chaves[pos]){
      return Duplicado;
    }
    valor = ins(x->filhos[pos], chave, &novaChave, &newx);
    if(valor!=InsereI){
      return valor;
    }
    if(n<T-1){
        pos = buscaPost(novaChave, x->chaves, n);

        for(i=n; i>pos; i--){
            x->chaves[i] = x->chaves[i-1];
            x->filhos[i+1] = x->filhos[i];
        }

        x->chaves[pos] = novaChave;
        x->filhos[pos+1] = newx;
        ++x->numChaves;
        return Sucesso;
    }

    if(pos==T-1){
        lastchave = novaChave;
        lastx = newx;
    } else
    {
        lastchave = x->chaves[T-2];
        lastx = x->filhos[T-1];
        for(i=T-2; i>pos; i--) {
            x->chaves[i] = x->chaves[i-1];
            x->filhos[i+1] = x->filhos[i];
        }
        x->chaves[pos] = novaChave;
        x->filhos[pos+1] = newx;
    }
    splitPos = (T-1)/2;
    (*chaveAcima) = x->chaves[splitPos];

    (*novoVertice) = (struct vertice *) malloc(sizeof(struct vertice));
    x->numChaves = splitPos;
    (*novoVertice)->numChaves = T-1-splitPos;
    for(i=0; i<(*novoVertice)->numChaves; i++){
        (*novoVertice)->filhos[i] = x->filhos[i+splitPos+1];
        if (i<(*novoVertice)->numChaves-1)
            (*novoVertice)->chaves[i] = x->chaves[i+splitPos+1];
        else
            (*novoVertice)->chaves[i] = lastchave;
    }
    (*novoVertice)->filhos[(*novoVertice)->numChaves] = lastx;
    return InsereI;
}


void display(struct vertice *x, FILE* file_out){
  if(x){
    int i;
    fprintf(file_out, "(");


    for (i = 0; i <= x->numChaves; i++){
      display(x->filhos[i], file_out);
    }
    for (i = 0; i < x->numChaves; i++){
      fprintf(file_out, "%d ", x->chaves[i]);
    }
    fprintf(file_out, ")");
  }
}


void exibeFolhas(struct vertice *x, FILE* file_out){
  int i = 0;
  struct vertice* aux = x;
  while(aux->filhos[i]!=NULL){
    aux = aux->filhos[i];
    exibeFolhas(aux, file_out);
    i++;
  }
  for(i=0; i<=aux->numChaves; i++){
    if(x->chaves[i]!=0){
      fprintf(file_out, "%d ", x->chaves[i]);
    }
  }
}


int buscaPost(int chave, int *arr_chaves, int n){
    int pos = 0;
    while(pos<n && chave>arr_chaves[pos]){
      pos++;
    }
    return pos;
}


void removeChave(int chave){
    struct vertice *raizAcima;
    enum chaveStatus valor;
    valor = del(raiz, chave);
    if(valor==BuscaFalha){
      printf("chave %d is not available\n", chave);
      return;
    }
    if(valor==MenosChaves){
      raizAcima = raiz;
      raiz = raiz->filhos[0];
      free(raizAcima);
      return;
    }
}


enum chaveStatus del(struct vertice *x, int chave){
    int pos, i, chave_aux, n, min, contador;
    int *arr_chaves;
    enum chaveStatus valor;
    struct vertice **p, *pont_esq, *pont_dir;

    if (x == NULL)
        return BuscaFalha;

    n = x->numChaves;
    arr_chaves = x->chaves;
    p = x->filhos;
    min = (T-1)/2;

    pos = buscaPost(chave, arr_chaves, n);
    if(p[0]==NULL){
        if(pos==n || chave<arr_chaves[pos]){
          return BuscaFalha;
        }
        for(i=pos+1; i<n; i++){
            arr_chaves[i-1] = arr_chaves[i];
            p[i] = p[i+1];
        }
        if(x==raiz){
          contador = 1;
        } else {
          contador = min;
        }
        if(--x->numChaves >= contador){
          return Sucesso;
        }else{
          return MenosChaves;
        }
    }

    if(pos<n && chave==arr_chaves[pos]){
        struct vertice *qp = p[pos], *qp1;
        int nchave;
        while(1){
            nchave = qp->numChaves;
            qp1 = qp->filhos[nchave];
            if(qp1==NULL){
              break;
            }
            qp = qp1;
        }
        arr_chaves[pos] = qp->chaves[nchave-1];
        qp->chaves[nchave-1] = chave;
    }
    valor = del(p[pos], chave);
    if(valor!=MenosChaves)
        return valor;

    if(pos>0 && p[pos-1]->numChaves>min){
        chave_aux = pos-1;
        pont_esq = p[chave_aux];
        pont_dir = p[pos];

        pont_dir->filhos[pont_dir->numChaves+1] = pont_dir->filhos[pont_dir->numChaves];
        for (i=pont_dir->numChaves; i>0; i--) {
            pont_dir->chaves[i] = pont_dir->chaves[i-1];
            pont_dir->filhos[i] = pont_dir->filhos[i-1];
        }
        pont_dir->numChaves++;
        pont_dir->chaves[0] = arr_chaves[chave_aux];
        pont_dir->filhos[0] = pont_esq->filhos[pont_esq->numChaves];
        arr_chaves[chave_aux] = pont_esq->chaves[--pont_esq->numChaves];
        return Sucesso;
    }

    if(pos<n && p[pos+1]->numChaves>min){
        chave_aux = pos;
        pont_esq = p[chave_aux];
        pont_dir = p[chave_aux + 1];

        pont_esq->chaves[pont_esq->numChaves] = arr_chaves[chave_aux];
        pont_esq->filhos[pont_esq->numChaves+1] = pont_dir->filhos[0];
        arr_chaves[chave_aux] = pont_dir->chaves[0];
        pont_esq->numChaves++;
        pont_dir->numChaves--;

        for (i = 0; i < pont_dir->numChaves; i++) {
            pont_dir->chaves[i] = pont_dir->chaves[i+1];
            pont_dir->filhos[i] = pont_dir->filhos[i+1];
        }
        pont_dir->filhos[pont_dir->numChaves] = pont_dir->filhos[pont_dir->numChaves+1];

        return Sucesso;
    }

    if(pos == n){
      chave_aux = pos - 1;
    }
    else{
      chave_aux = pos;
    }
    pont_esq = p[chave_aux];
    pont_dir = p[chave_aux + 1];

    pont_esq->chaves[pont_esq->numChaves] = arr_chaves[chave_aux];
    pont_esq->filhos[pont_esq->numChaves+1] = pont_dir->filhos[0];

    for(i=0; i<pont_dir->numChaves; i++){
        pont_esq->chaves[pont_esq->numChaves+1+i] = pont_dir->chaves[i];
        pont_esq->filhos[pont_esq->numChaves+2+i] = pont_dir->filhos[i+1];
    }
    pont_esq->numChaves = pont_esq->numChaves+pont_dir->numChaves+1;
    free(pont_dir);

    for(i=pos+1; i<n; i++){
        arr_chaves[i-1] = arr_chaves[i];
        p[i] = p[i+1];
    }
    if(x==raiz){
      contador = 1;
    } else {
      contador = min;
    }
    if(--x->numChaves >= contador){
      return Sucesso;
    }else{
      return MenosChaves;
    }
  }


int main(int argc, char *argv[]){
  int chave;
  char entrada;
  FILE *file;
  file = fopen(argv[1], "r");
  FILE* file_out;
  file_out= fopen(argv[2], "w");
  if(file!=NULL){
  		while(!feof(file)){
        fscanf(file, "%c", &entrada);
        if(entrada=='i'){
          fscanf (file, "%d", &chave);
          insere(chave);
        }
        else if(entrada=='r'){
          fscanf (file, "%d", &chave);
          removeChave(chave);
        }
        else if(entrada=='p'){
          if(raiz==NULL){
            fprintf(file_out, "Arvore vazia\n");
          } else {
            fprintf(file_out, "\n(");
            display(raiz, file_out);
            fprintf(file_out, ")\n\n");
            fprintf(file_out, "folhas: ");
            exibeFolhas(raiz, file_out);
            fprintf(file_out, "\n");
          }
        }
        else if(entrada=='f'){
          return 0;
        }
    }
  } else{
      printf("Arquivos invalidos\n");
    }
  return 0;

}
