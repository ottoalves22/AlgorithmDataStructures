package robo;

/*********************************************************************/
/** ACH 2002 - Introducao à Análise de Algoritmos          	 **/
/** EACH-USP - Segundo Semestre de 2018               		 **/
/**                                                              **/
/** Otto Alves Antonioli - 10843361             			         **/
/**                                             		            **/
/*********************************************************************/

/**
	Classe que implementa os movimentos do robô.
*/
public class Robo implements IRobo {
	/** Coordenada x de início da busca **/
	private static int x = ISala.X_INICIO_ARM;
	
	/** Coordenada y de início da busca */
	private static int y = ISala.Y_FIM_ARM+1;
	
	/** Mensageiro do robô **/
	public Mensageiro mensageiro;
	
	public Sala sitio;
	/** Construtor padrão para o robô **/
	public Robo() {
		this.mensageiro = new Mensageiro();	
		this.sitio = new Sala();
	}
	
	protected int xMove[] = {0, 1, 0, -1}; //sequencia de movimentos no eixo horizontal
	protected int yMove[] = {1, 0, -1, 0}; //sequencia de movimentos no eixo vertical	
	boolean pegouBloco=false; //true se o robo trombou um bloco, ativando o retorno
	int blocosPegos =0; //conta quantos blocos o robo entregou 
	int marcasPresentes=0;
	int nObstaculos=0;
	int casasVazias=(96-marcasPresentes - nObstaculos);//contador para casas vazias
	
	public void adicionaBloco(int x, int y) {
		if(sitio.posicaoBuscaValida(x, y)) {
			sitio.room[x][y] = ISala.BLOCO_PRESENTE; //room= matriz da sala 
		}
	}
		
	public void adicionaObstaculo(int x, int y) {
		if(sitio.posicaoBuscaValida(x, y)) {
			sitio.room[x][y]= ISala.OBSTACULO_PRESENTE;		
			nObstaculos++;
		}
	}	
	
	public boolean guardaBloco(){
		for(int i=0; i<=1; i++){
			for(int j=0; j<=1; j++){
				if(sitio.room[x][y]==ISala.POSICAO_VAZIA){
					sitio.room[x][y]=ISala.BLOCO_PRESENTE;
					mensageiro.mensagem(mensageiro.ARMAZENAGEM, x, y);
					return true;
				} 
			}
		}
		return false;
	}
	
	public void novaBusca(){
		for(int i=0; i<ISala.TAMANHO_SALA; i++){
			for(int j=0; j<ISala.TAMANHO_SALA; j++){
				if(sitio.room[x][y]==ISala.MARCA_PRESENTE && sitio.posicaoBuscaValida(x, y)){
					sitio.room[x][y]=ISala.POSICAO_VAZIA;
				}
			}
		}
	}
	
	int driftCharm=0; //contador para casas
			
	public boolean buscaBloco(int x, int y){
		int driftCharm=0; //contador para girar as opcoes de movimentos
			while(driftCharm<4){
				int xDrift= x + xMove[driftCharm];
				int yDrift= y + yMove[driftCharm];
				if(sitio.posicaoBuscaValida(xDrift, yDrift)==true){
							if(sitio.room[xDrift][yDrift]==ISala.BLOCO_PRESENTE){
								pegouBloco=true;
								//System.out.println("Captura em "+ xDrift + " "+ yDrift);
								mensageiro.mensagem(mensageiro.CAPTURA, xDrift, yDrift);
								sitio.room[xDrift][yDrift]=ISala.MARCA_PRESENTE;
								mensageiro.mensagem(mensageiro.RETORNO, x, y);
								return pegouBloco;
							}
							else if(sitio.room[xDrift][yDrift]==ISala.POSICAO_VAZIA){
								if(x==0 && y==2){
									mensageiro.mensagem(mensageiro.BUSCA, x, y);
									sitio.room[xDrift][yDrift]=ISala.MARCA_PRESENTE;
								}
								//System.out.println("Buscou("+ xDrift+","+yDrift+")");
								mensageiro.mensagem(mensageiro.BUSCA, xDrift, yDrift);
								sitio.room[xDrift][yDrift]=ISala.MARCA_PRESENTE;
								pegouBloco = buscaBloco(xDrift, yDrift);
								 
							}
							else if(sitio.room[xDrift][yDrift]==ISala.OBSTACULO_PRESENTE){
								//System.out.println("Obstaclo em"+ xDrift + " "+ yDrift);
								mensageiro.mensagem(mensageiro.OBSTACULO, xDrift, yDrift);
								return pegouBloco;
							}
							else if(sitio.room[xDrift][yDrift]==ISala.MARCA_PRESENTE){
								return pegouBloco;
							}	
				}
				//System.out.println("Incrementa");
			driftCharm++;
			}
			
			
			if(pegouBloco==true){
				mensageiro.mensagem(mensageiro.RETORNO, x, y);
				return true;
			}
		
		//System.out.println("deu merda");
		return false;
	}
	
	public void buscaBlocos(){
			//System.out.println("Ta solto o bichao");
			while(blocosPegos<4 && buscaBloco(x, y)){
				if(pegouBloco==true){
					guardaBloco();
					blocosPegos++;
					pegouBloco=false;
					novaBusca();
				}
			}
		//quando pegar os 4 quadrados
			if(blocosPegos==4){
				mensageiro.msgFim();
			}
			else mensageiro.msgNaoAchou();
	}
	
	public Mensageiro mensageiro() {
		return(this.mensageiro);
	}
	
}

