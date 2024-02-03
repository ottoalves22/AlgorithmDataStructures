package robo;

/**
	Classe que define a sala por onde o robô passeia. A sala é uma matriz quadrada de largura ISala.TAMANHO_SALA.
	
	Essa classe deve ser implementada pelo aluno
*/
public class Sala implements ISala {
	
			
			public boolean posicaoBuscaValida(int x, int y) {
				if(x>9 || x<0 || y>9 || y<0 || areaArmazenagem(x, y)==true) {
					return false;
				}
				else return true;
			}
					
			
			public int marcadorEm(int x, int y){
				if(room[x][y]==ISala.MARCA_PRESENTE) {
					return ISala.MARCA_PRESENTE;
				}
				else return ISala.POSICAO_VAZIA;
			}
					
					 
					public boolean marcaPosicaoBusca(int x, int y, int marcador){
						if(posicaoBuscaValida(x, y)) {
							room[x][y]=marcador;
							return true;
						}
						else return false;
					}
					
					
					public boolean marcaPosicaoArmazenagem(int x, int y){
						if(x==ISala.X_INICIO_ARM || x==ISala.X_FIM_ARM || y==ISala.Y_INICIO_ARM || y==ISala.Y_FIM_ARM || room[x][y]==ISala.MARCA_PRESENTE) {
							return false;
						}
						else {
							room[x][y]= ISala.BLOCO_PRESENTE;
							return true;
						}
					}
					
					
					public void removeMarcador(int x, int y){
						if(room[x][y]==ISala.MARCA_PRESENTE) {
							room[x][y] = ISala.POSICAO_VAZIA;
						}
					}
					
					
					public boolean areaArmazenagem(int x, int y){
						if(x==0 && y==0 || x==1 && y==0 || x==0 && y==1 || x==1 && y==1) {
							return true;
						}
						else return false;
					}
					
					
					public void removeMarcador(int marcador){ 
						for(int car=0; car<10; car++){
							for(int ole=0; ole<10; ole++){
								if(room[car][ole]==marcador){
									room[car][ole]=ISala.POSICAO_VAZIA;
								}
							}
						}
					}

	 public Sala() {
										 
					for(int x=0; x<ISala.TAMANHO_SALA; x++) { //inicializando room (ambiente de interacado robo
						for(int y=0; y<ISala.TAMANHO_SALA; y++) {
							room[x][y]=ISala.POSICAO_VAZIA;
						}
					}	
	 }
	 
	 static public int[][] room = new int[ISala.TAMANHO_SALA][ISala.TAMANHO_SALA];
}
