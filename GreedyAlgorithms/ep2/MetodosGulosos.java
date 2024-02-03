package ep2;

/*********************************************************************/
/** ACH 2002 - Introducao a Ciencia da Computacao II                **/
/** EACH-USP - Segundo Semestre de 2010                             **/
/**                                                                 **/
/** <04> - <Norton Trevisan Roman>                                   **/
/**                                                                 **/
/** Terceiro Exercicio-Programa                                     **/
/**                                                                 **/
/** <Otto Alves Antonioli> <10843361>                              **/
/**                                                                 **/
/*********************************************************************/


/**
	COMENTARIOS GERAIS

	Seguindo os criterios de selecao, um objeto só poderá ser colocado na
	mochila caso ela suporte o total de peso.

	O total de peso ao se colocar um objeto (do tipo Objeto) é dado por
	mochila.getPesoUsado() + objeto.getPeso()

	Colocar um objeto na mochila significa alterar os seguintes campos da mochila:

	pesoUsado,

	valorDentroDaMochila, e

	numObjetosNaMochila.
*/
public abstract class MetodosGulosos {


	public static void sortPeso(Objeto[] A){
		Objeto aux;
		for(int i=0; i < A.length; i++){
			for(int j=1; j < (A.length-i); j++){
				if(A[j-1].getPeso() > A[j].getPeso()){
					aux = A[j-1];
					A[j-1] = A[j];
					A[j] = aux;
				}
				else if(A[j-1].getPeso()==A[j].getPeso()){
					if(A[j-1].getValor() < A[j].getValor()){
						aux = A[j-1];
						A[j-1] = A[j];
						A[j] = aux;
					}
				}
			}
		}
	}

	public static void sortValor(Objeto[] A){
		Objeto aux;
		for(int i=0; i<A.length-1; i++){
			for(int j=0; j<A.length; j++){
				if(A[i].getValor()<A[i+1].getValor()){
					aux = A[i+1];
					A[i+1] = A[i];
					A[i]=aux;
					if(A[i].getPeso()<	A[i+1].getPeso()){
						aux = A[i+1];
						A[i+1] = A[i];
						A[i]=aux;
					}
				}
			}
		}
	}


	public static void sortRelacao(Objeto[] A){
		Objeto aux;
		for(int i=0; i<A.length-1; i++){
			for(int j=0; j<A.length; j++){
				if(A[i].getValor()/A[i].getPeso()<A[i+1].getValor()/A[i+1].getPeso()){
					aux = A[i+1];
					A[i+1] = A[i];
					A[i]=aux;
				}
				if(A[i].getValor()/A[i].getPeso()==A[i+1].getValor()/A[i].getPeso()){
						if(A[i].getPeso()<	A[i+1].getPeso()){
							aux = A[i+1];
							A[i+1] = A[i];
							A[i]=aux;
						}
					} 
			}
		}
}


	/**
		Este método deve implementar um algoritmo guloso que selecione objetos
		da listaDeObjetosDisponiveis a serem colocados na mochila, de acordo
		com o critério 'objetos de menor peso primeiro'. Caso dois objetos
		tenham o mesmo peso, o critério de desempate será 'objetos de maior
		valor primeiro' (apenas para os empates em peso).

		@param pesoMaximoDaMochila Peso máximo suportado pela mochila
		@param listaDeObjetosDisponiveis Arranjo de objetos considerados no problema

		@return Mochila carregada conforme essa estratégia
	 */
	public static Mochila utilizaMenorPeso(double pesoMaximoDaMochila, Objeto[] listaDeObjetosDisponiveis) {
		Mochila mochila = new Mochila(pesoMaximoDaMochila);
		sortPeso(listaDeObjetosDisponiveis);
		double pesoAux = 0;
		double valorAux = 0;
		int itensAux = 0;
		mochila.setPesoUsado(pesoAux);
		mochila.setNumObjetosNaMochila(itensAux);
		mochila.setValorDentroDaMochila(valorAux);
		for(int i=0; i<listaDeObjetosDisponiveis.length && mochila.getPesoUsado() < pesoMaximoDaMochila; i++){
			if(pesoAux + listaDeObjetosDisponiveis[i].getPeso()<=pesoMaximoDaMochila){
					pesoAux += listaDeObjetosDisponiveis[i].getPeso();
					mochila.setPesoUsado(pesoAux);
					itensAux++;
					mochila.setNumObjetosNaMochila(itensAux);
					valorAux += listaDeObjetosDisponiveis[i].getValor();
					mochila.setValorDentroDaMochila(valorAux);

						}

					}

		// COMPLETAR

		return mochila;
	}


	/**
		Este método deve implementar um algoritmo guloso que selecione objetos
		da listaDeObjetosDisponiveis a serem colocados na mochila, de acordo
		com o critério 'objetos de maior valor primeiro'. Caso dois objetos
		tenham o mesmo valor, o critério de desempate sera 'objetos de menor peso
		primeiro' (apenas para os empates em valor).

		@param pesoMaximoDaMochila Peso máximo suportado pela mochila
		@param listaDeObjetosDisponiveis Arranjo de objetos considerados no problema

		@return Mochila carregada conforme essa estratégia
	 */
	public static Mochila utilizaMaiorValor(double pesoMaximoDaMochila,	Objeto[] listaDeObjetosDisponiveis) { //feito
		Mochila mochila = new Mochila(pesoMaximoDaMochila);
		sortValor(listaDeObjetosDisponiveis);
		double pesoAux = 0;
		double valorAux = 0;
		int itensAux = 0;
		mochila.setPesoUsado(pesoAux);
		mochila.setNumObjetosNaMochila(itensAux);
		mochila.setValorDentroDaMochila(valorAux);
		for(int i=0; i<listaDeObjetosDisponiveis.length && mochila.getPesoUsado() < pesoMaximoDaMochila; i++){
			if(pesoAux + listaDeObjetosDisponiveis[i].getPeso()<=pesoMaximoDaMochila){
					pesoAux += listaDeObjetosDisponiveis[i].getPeso();
					mochila.setPesoUsado(pesoAux);
					itensAux++;
					mochila.setNumObjetosNaMochila(itensAux);
					valorAux += listaDeObjetosDisponiveis[i].getValor();
					mochila.setValorDentroDaMochila(valorAux);
						}
					}
		// COMPLETAR

		return mochila;
	}


	/**
		Este método deve implementar um algoritmo guloso que selecione objetos
		da listaDeObjetosDisponiveis a serem colocados na mochila, de acordo
		com o critério 'objetos de maior valor/peso primeiro (valor dividido por
		peso primeiro)'. Caso dois objetos tenham o mesmo valor/peso, o critério
		de desempate sera 'objetos de maior peso primeiro' (apenas para os empates).

		@param pesoMaximoDaMochila Peso máximo suportado pela mochila
		@param listaDeObjetosDisponiveis Arranjo de objetos considerados no problema

		@return Mochila carregada conforme essa estratégia
	 */
	public static Mochila utilizaMaiorValorDivididoPorPeso(double pesoMaximoDaMochila, Objeto[] listaDeObjetosDisponiveis) {
		Mochila mochila = new Mochila(pesoMaximoDaMochila);
		sortRelacao(listaDeObjetosDisponiveis);
		double pesoAux = 0;
		double valorAux = 0;
		int itensAux = 0;
		mochila.setPesoUsado(pesoAux);
		mochila.setNumObjetosNaMochila(itensAux);
		mochila.setValorDentroDaMochila(valorAux);
		for(int i=0; i<listaDeObjetosDisponiveis.length && mochila.getPesoUsado() < pesoMaximoDaMochila; i++){
			if(pesoAux + listaDeObjetosDisponiveis[i].getPeso()<=pesoMaximoDaMochila){
					System.out.println( listaDeObjetosDisponiveis[i].getPeso() + " | "+ listaDeObjetosDisponiveis[i].getValor());
					pesoAux += listaDeObjetosDisponiveis[i].getPeso();
					mochila.setPesoUsado(pesoAux);
					itensAux++;
					mochila.setNumObjetosNaMochila(itensAux);
					valorAux += listaDeObjetosDisponiveis[i].getValor();
					mochila.setValorDentroDaMochila(valorAux);
						}
					}

		return mochila;
	}

}
