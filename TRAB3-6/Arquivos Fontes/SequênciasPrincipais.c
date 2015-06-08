/***************************************************************************
*  $MCI Módulo de implementação: SQP Sequencias Principais
*
*  Arquivo gerado:              SequenciasPrincipais.C
*  Letras identificadoras:      SQP
*
*
*  Projeto: Disciplinas INF 1301
*  Professor: Flavio
*  Autores: ds  - Daniel Siles
*			fh  - Fernando Homem
*			mr - Mateus Ribeiro
*
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*		4.00 ds/fh/mr 06/06/2015 Adição de funções necessárias.
*       3.00 ds/fh/mr 26/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno.
*       2.00 ds/fh/mr 22/04/2015 Eliminação de código duplicado, reestruturação
*       1.00 ds/fh/mr 17/04/2015 Início do desenvolvimento
*
***************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include "Carta.h"
#include "PilhadeCartas.h"

#define SEQUENCIASPRINCIPAIS_OWN
#include "SequênciasPrincipais.h"
#undef SEQUENCIASPRINCIPAIS_OWN

struct sequenciasPrincipais {
	PILHA_tpPilha sqPrincipal;
};

//#include "sequenciasPrincipais.h"
char naipes[4] = { 'E', 'C', 'P', 'O' };
char cartas[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };

/***********************************************************************
*
*  $FC Função: SQP criar Sequencia
*
*
***********************************************************************/
SQP_tpCondRet SQP_criarSequencia(SQP_tpSQPrincipal *SQPrincipal){
	
	*SQPrincipal = (SQP_tgSQPrincipal *)malloc(sizeof(SQP_tgSQPrincipal));

	if (*SQPrincipal == NULL){
		return SQP_CondRetFaltouMemoria;
	}

	PILHA_criarPilha(&((*SQPrincipal)->sqPrincipal));

	return SQP_CondRetOK;
} /* Fim função: SQP criar Sequencia */

/***********************************************************************
*
*  $FC Função: SQP libera Sequencia
*
*
***********************************************************************/
SQP_tpCondRet SQP_liberaSequencia(SQP_tpSQPrincipal sqPrincipal){
	if (sqPrincipal->sqPrincipal == NULL){
		free(sqPrincipal);
	}
	else{
		PILHA_liberaPilha(sqPrincipal->sqPrincipal);
		free(sqPrincipal);
	}

	return SQP_CondRetOK;
} /* Fim função: SQP libera Sequencia */

int busca_vetor(char *vetor, int n, char elemProc){
	int i;
	for (i = 0; i < n; i++){
		if (vetor[i] == elemProc){
			return i;
		}
	}
	return -1;
}

/***********************************************************************
*
*  $FC Função: SQP remove Da Sequencia
*
*
***********************************************************************/
SQP_tpCondRet SQP_removeDaSequencia(SQP_tpSQPrincipal sqTira, CAR_tpCarta cCarta, PILHA_tpPilha *pPilhaGuarda){
	char faceRecebe;
	char naipeRecebe;
	char posicaoRecebe;
	char faceTirada;
	char naipeTirada;
	char posicaoTirada;

	PILHA_tpPilha pTirada;
	PILHA_tpPilha pTirada2;
	CAR_tpCarta cTirada;
	CAR_tpCarta cDevolve; //Devolve a carta retirada
	PILHA_criarPilha(&pTirada);
	PILHA_criarPilha(&pTirada2);
	CAR_criarCarta(&cTirada);
	CAR_criarCarta(&cDevolve);
	

	if (sqTira == NULL){
		return SQP_CondRetNaoExiste;
	}

	else if (sqTira->sqPrincipal == NULL){
		return SQP_CondRetSequenciaVazia;
	}

	else{
		CAR_retornaFace(cCarta, &faceRecebe);
		CAR_retornaNaipe(cCarta, &naipeRecebe);
		CAR_retornaPosicao(cCarta, &posicaoRecebe);

		while (PILHA_verificaPilhaVazia(sqTira->sqPrincipal) == PILHA_CondRetOK){
			PILHA_popPilha(sqTira->sqPrincipal, &cTirada);
			CAR_retornaFace(cTirada, &faceTirada);
			CAR_retornaNaipe(cTirada, &naipeTirada);
			CAR_retornaPosicao(cTirada, &posicaoTirada);

			if (faceTirada == 'E'){
				PILHA_pushPilha(sqTira->sqPrincipal, cTirada);
				while (PILHA_verificaPilhaVazia(pTirada) == PILHA_CondRetOK){
					PILHA_popPilha(pTirada, &cDevolve);
					PILHA_pushPilha(sqTira->sqPrincipal, cDevolve);
				}
				return SQP_CondRetFaceEscondida;
			}

			else if (naipeRecebe != naipeTirada){
				PILHA_pushPilha(sqTira->sqPrincipal, cTirada);
				while (PILHA_verificaPilhaVazia(pTirada) == PILHA_CondRetOK){
					PILHA_popPilha(pTirada, &cDevolve);
					PILHA_pushPilha(sqTira->sqPrincipal, cDevolve);
				}
				return SQP_CondRetNaipeDiferente;
			}

			else if (busca_vetor(cartas, 13, posicaoRecebe) < busca_vetor(cartas, 13, posicaoTirada)){
				PILHA_pushPilha(sqTira->sqPrincipal, cTirada);
				while (PILHA_verificaPilhaVazia(pTirada) == PILHA_CondRetOK){
					PILHA_popPilha(pTirada, &cDevolve);
					PILHA_pushPilha(sqTira->sqPrincipal, cDevolve);
				}
				return SQP_CondRetPosicaoErrada;
			}

			else{
				if (posicaoRecebe == posicaoTirada){
					PILHA_pushPilha(pTirada2, cTirada);
					while (PILHA_verificaPilhaVazia(pTirada) == PILHA_CondRetOK){
						PILHA_popPilha(pTirada, &cDevolve);
						PILHA_pushPilha(pTirada2, cDevolve);
					}

					while (PILHA_verificaPilhaVazia(pTirada2) == PILHA_CondRetOK){
						PILHA_popPilha(pTirada2, &cDevolve);
						PILHA_pushPilha(*pPilhaGuarda, cDevolve);
					}
					return SQP_CondRetOK;
				}
				PILHA_pushPilha(pTirada, cTirada);
			}
			
		}
		return SQP_CondRetNaoOK;
	}
} /* Fim função: SQP remove Da Sequencia */

/***********************************************************************
*
*  $FC Função: SQP adiciona Na Sequencia
*
*
***********************************************************************/
SQP_tpCondRet SQP_adicionaNaSequencia(PILHA_tpPilha pPilhaRecebida, SQP_tpSQPrincipal sqRecebe){

	CAR_tpCarta cRecebida;
	CAR_tpCarta cRecebe;
	CAR_criarCarta(&cRecebida);
	CAR_criarCarta(&cRecebe);

	char posicaoRecebida;
	char posicaoRecebe;
	int Recebida = 0;
	int Recebe = 0;

	if (PILHA_verificaPilhaVazia(sqRecebe->sqPrincipal) == PILHA_CondRetPilhaVazia){
		while (PILHA_verificaPilhaVazia(pPilhaRecebida) == PILHA_CondRetOK){
			PILHA_popPilha(pPilhaRecebida, &cRecebida);
			PILHA_pushPilha(sqRecebe->sqPrincipal, cRecebida);
		}
		return SQP_CondRetOK;
	}

	else{
		PILHA_popPilha(pPilhaRecebida, &cRecebida);
		CAR_retornaPosicao(cRecebida, &posicaoRecebida);
		PILHA_pushPilha(pPilhaRecebida, cRecebida);

		PILHA_popPilha(sqRecebe->sqPrincipal, &cRecebe);
		CAR_retornaPosicao(cRecebe, &posicaoRecebe);
		PILHA_pushPilha(sqRecebe->sqPrincipal, cRecebe);

		Recebida = busca_vetor(cartas, 13, posicaoRecebida);
		Recebe = busca_vetor(cartas, 13, posicaoRecebe);

		if (Recebida == (Recebe -1)){
			while (PILHA_verificaPilhaVazia(pPilhaRecebida) == PILHA_CondRetOK){
				PILHA_popPilha(pPilhaRecebida, &cRecebida);
				PILHA_pushPilha(sqRecebe->sqPrincipal, cRecebida);
			}
			return SQP_CondRetOK;
		}

		else{
			return SQP_CondRetPosicaoErrada;
		}
	}

} /* Fim função: SQP adiciona Na Sequencia */

/***********************************************************************
*
*  $FC Função: SQP verifica Sequencia Completa
*
*
***********************************************************************/
SQP_tpCondRet SQP_verificaSequenciaCompleta(SQP_tpSQPrincipal SQP){
	char posicao;
	char naipe;
	char face;

	char posicao2;
	char naipe2;
	char face2;
	int ind;

	PILHA_tpPilha auxiliar;
	PILHA_criarPilha(&auxiliar);
	PILHA_tpPilha auxiliar2;
	PILHA_criarPilha(&auxiliar2);

	

	CAR_tpCarta cAuxiliar;
	CAR_criarCarta(&cAuxiliar);
	CAR_tpCarta cAuxiliar2;
	CAR_criarCarta(&cAuxiliar2);

	while (PILHA_verificaPilhaVazia(SQP->sqPrincipal) == PILHA_CondRetOK){
		PILHA_popPilha(SQP->sqPrincipal, &cAuxiliar);
		CAR_retornaPosicao(cAuxiliar, &posicao);
		PILHA_pushPilha(auxiliar, cAuxiliar);
	}
	while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
		PILHA_popPilha(auxiliar, &cAuxiliar);
		PILHA_pushPilha(SQP->sqPrincipal, cAuxiliar);
		CAR_retornaFace(cAuxiliar, &face);
		CAR_retornaNaipe(cAuxiliar, &naipe);
		CAR_retornaPosicao(cAuxiliar, &posicao);
		CAR_editarCarta(cAuxiliar, face, naipe, posicao);
		PILHA_pushPilha(auxiliar2, cAuxiliar);
		
	}
	PILHA_popPilha(auxiliar2, &cAuxiliar);

	CAR_retornaFace(cAuxiliar, &face);
	CAR_retornaPosicao(cAuxiliar, &posicao);
	CAR_retornaNaipe(cAuxiliar, &naipe);

	if (posicao != 'A'){
		return SQP_CondRetPosicaoErrada;
	}
	if (face != 'V'){
		return SQP_CondRetFaceEscondida;
	}

	while (PILHA_verificaPilhaVazia(auxiliar2) == PILHA_CondRetOK){
		
		PILHA_popPilha(auxiliar2, &cAuxiliar2);
		PILHA_pushPilha(auxiliar, cAuxiliar2);
		
		CAR_retornaFace(cAuxiliar2, &face2);
		CAR_retornaPosicao(cAuxiliar2, &posicao2);
		CAR_retornaNaipe(cAuxiliar2, &naipe2);

		CAR_editarCarta(cAuxiliar2, face2, naipe2, posicao2);

		if (naipe != naipe2){
			return SQP_CondRetNaipeDiferente;
		}
		if (face2 != 'V'){
			return SQP_CondRetFaceEscondida;
		}

		ind = busca_vetor(cartas, 13, posicao);

		if (cartas[ind + 1] != posicao2){
			return SQP_CondRetPosicaoErrada;
		}

		if (posicao2 == 'K'){
			return SQP_CondRetOK;
		}

		face = face2;
		naipe = naipe2;
		posicao = posicao2;
	}
	return SQP_CondRetNaoOK;
} /* Fim função: SQP verifica Sequencia Completa */

/***********************************************************************
*
*  $FC Função: SQP retorna Pilha
*
*
***********************************************************************/
SQP_tpCondRet SQP_retornaPilha(SQP_tpSQPrincipal sqp, PILHA_tpPilha * pilha){
	(*pilha) = sqp->sqPrincipal;

	return SQP_CondRetOK;
} /* Fim função: SQP retorna Pilha */

/***********************************************************************
*
*  $FC Função: SQP push SQP
*
*
***********************************************************************/
SQP_tpCondRet SQP_pushSQP(SQP_tpSQPrincipal sSQP, CAR_tpCarta cCarta){
	PILHA_pushPilha(sSQP->sqPrincipal, cCarta);

	return SQP_CondRetOK;
} /* Fim função: SQP push SQP */

/***********************************************************************
*
*  $FC Função: SQP pop SQP
*
*
***********************************************************************/
SQP_tpCondRet SQP_popSQP(SQP_tpSQPrincipal sSQP, CAR_tpCarta *Carta){
	PILHA_popPilha(sSQP->sqPrincipal, Carta);

	return SQP_CondRetOK;
} /* Fim função: SQP pop SQP */
/********** Fim do módulo de implementação: SQP Sequencias Principais **********/