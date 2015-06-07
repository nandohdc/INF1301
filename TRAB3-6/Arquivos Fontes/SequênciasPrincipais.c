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
	PILHA_tpCondRet pRet;
	PILHA_tpPilha auxiliar;
	CAR_tpCarta cAuxiliar;
	CAR_tpCarta cAuxiliar2;
	CAR_tpCarta cAuxiliar3;

	char posicao;
	char naipe;
	char face;
	int ind;

	char faceCarta;
	char naipeCarta;
	char posCarta;
	
	CAR_retornaFace(cCarta, &faceCarta);
	CAR_retornaNaipe(cCarta, &naipeCarta);
	CAR_retornaPosicao(cCarta, &posCarta);


	PILHA_criarPilha(&auxiliar);
	CAR_criarCarta(&cAuxiliar);
	CAR_criarCarta(&cAuxiliar2);
	CAR_criarCarta(&cAuxiliar3);
	
	if (sqTira == NULL){
		return SQP_CondRetSequenciaVazia;
	}

	if (sqTira->sqPrincipal == NULL){
		return SQP_CondRetSequenciaVazia;
	}

	while (PILHA_verificaPilhaVazia(sqTira->sqPrincipal) == PILHA_CondRetOK){
		pRet = PILHA_popPilha(sqTira->sqPrincipal, &cAuxiliar);
		if (pRet == PILHA_CondRetPilhaVazia){
			return SQP_CondRetNaoOK; // Nao Achou a sequencia para tirar da sequencia
		}
		CAR_retornaPosicao(cAuxiliar, &posicao);
		CAR_retornaNaipe(cAuxiliar, &naipe);
		CAR_retornaFace(cAuxiliar, &face);

		PILHA_pushPilha(auxiliar, cAuxiliar);

		if (face == 'E'){
			while (PILHA_verificaPilhaVazia(auxiliar)== PILHA_CondRetOK){
				CAR_criarCarta(&cAuxiliar);
				PILHA_popPilha(auxiliar, &cAuxiliar);
				PILHA_pushPilha(sqTira->sqPrincipal, cAuxiliar);
			}
			return SQP_CondRetFaceEscondida; // Nao Achou a sequencia para tirar da sequencia
		}
		
		
		if (posicao == posCarta && naipe == naipeCarta){
			break;
		}
	}

	PILHA_popPilha(auxiliar, &cAuxiliar);
	CAR_retornaPosicao(cAuxiliar, &posicao);
	CAR_retornaNaipe(cAuxiliar, &naipe);
	PILHA_pushPilha(*pPilhaGuarda, cAuxiliar);

	while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(auxiliar, &cAuxiliar);
		CAR_retornaPosicao(cAuxiliar, &posCarta);
		CAR_retornaNaipe(cAuxiliar, &naipeCarta);
		CAR_retornaFace(cAuxiliar, &faceCarta);
		CAR_editarCarta(cAuxiliar3, faceCarta, naipeCarta, posCarta);

		ind = busca_vetor(cartas, 13, posicao);

		if (cartas[ind - 1] != posCarta){
			while (PILHA_verificaPilhaVazia(*pPilhaGuarda) == PILHA_CondRetOK){
				PILHA_popPilha(*pPilhaGuarda, &cAuxiliar);
				PILHA_pushPilha(sqTira->sqPrincipal, cAuxiliar);
			}

			while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
				PILHA_popPilha(auxiliar, &cAuxiliar);
				PILHA_pushPilha(sqTira->sqPrincipal, cAuxiliar);
			}
			PILHA_pushPilha(sqTira->sqPrincipal, cAuxiliar3);
			return SQP_CondRetPosicaoErrada;
		}
		if (naipe != naipeCarta){
			while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
				PILHA_popPilha(auxiliar, &cAuxiliar);
				PILHA_pushPilha(sqTira->sqPrincipal, cAuxiliar);
			}
			return SQP_CondRetNaipeDiferente;
		}
		PILHA_pushPilha(*pPilhaGuarda, cAuxiliar);

		posicao = posCarta;
		naipe = naipeCarta;
	}

	return SQP_CondRetOK;
} /* Fim função: SQP remove Da Sequencia */

/***********************************************************************
*
*  $FC Função: SQP adiciona Na Sequencia
*
*
***********************************************************************/
SQP_tpCondRet SQP_adicionaNaSequencia(PILHA_tpPilha pPilhaTira, SQP_tpSQPrincipal sqRecebe){
	char posicao1;
	char naipe1;

	char posicao2;
	char naipe2;
	char face2;

	int ind;

	PILHA_tpPilha auxiliar;
	PILHA_criarPilha(&auxiliar);

	CAR_tpCarta cAuxiliar;
	CAR_criarCarta(&cAuxiliar);
	CAR_tpCarta cAuxiliar2;
	CAR_criarCarta(&cAuxiliar2);

	if (sqRecebe == NULL){
		return SQP_CondRetSequenciaVazia;
	}

	while (PILHA_verificaPilhaVazia(pPilhaTira) == PILHA_CondRetOK){
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(pPilhaTira, &cAuxiliar);
		PILHA_pushPilha(auxiliar, cAuxiliar);
	}
	CAR_retornaNaipe(cAuxiliar, &naipe1);
	CAR_retornaPosicao(cAuxiliar, &posicao1);

	//PILHA_popPilha(auxiliar , &cAuxiliar2);
	//PILHA_pushPilha(auxiliar, cAuxiliar2);

	if (PILHA_verificaPilhaVazia(sqRecebe->sqPrincipal) == PILHA_CondRetOK){
		PILHA_popPilha(sqRecebe->sqPrincipal, &cAuxiliar2);
		PILHA_pushPilha(sqRecebe->sqPrincipal, cAuxiliar2);
	}

	CAR_retornaNaipe(cAuxiliar2, &naipe2);
	CAR_retornaPosicao(cAuxiliar2, &posicao2);
	CAR_retornaFace(cAuxiliar2, &face2);

	
	
	ind = busca_vetor(cartas, 13, posicao2);

	
	if (face2 == 'E' && PILHA_verificaPilhaVazia(sqRecebe->sqPrincipal) == PILHA_CondRetOK){
		return SQP_CondRetFaceEscondida;
	}
	
	if (naipe1 != naipe2 && PILHA_verificaPilhaVazia(sqRecebe->sqPrincipal) == PILHA_CondRetOK){
		return SQP_CondRetNaipeDiferente;
	}
	
	if (cartas[ind - 1] != posicao1 && PILHA_verificaPilhaVazia(sqRecebe->sqPrincipal) == PILHA_CondRetOK){

		return SQP_CondRetPosicaoErrada;
	}

	while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(auxiliar, &cAuxiliar);
		PILHA_pushPilha(sqRecebe->sqPrincipal, cAuxiliar);
	}
	
	return SQP_CondRetOK;
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

	if (SQP == NULL){
		return SQP_CondRetSequenciaVazia;
	}
	while (PILHA_verificaPilhaVazia(SQP->sqPrincipal) == PILHA_CondRetOK){
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(SQP->sqPrincipal, &cAuxiliar);
		CAR_retornaPosicao(cAuxiliar, &posicao);
		PILHA_pushPilha(auxiliar, cAuxiliar);
	}
	while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(auxiliar, &cAuxiliar);
		PILHA_pushPilha(SQP->sqPrincipal, cAuxiliar);
		CAR_retornaFace(cAuxiliar, &face);
		CAR_retornaNaipe(cAuxiliar, &naipe);
		CAR_retornaPosicao(cAuxiliar, &posicao);
		CAR_editarCarta(cAuxiliar, face, naipe, posicao);
		PILHA_pushPilha(auxiliar2, cAuxiliar);
		
	}
	PILHA_popPilha(auxiliar2, &cAuxiliar);
	//PILHA_pushPilha(auxiliar2, cAuxiliar);

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
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(auxiliar2, &cAuxiliar);
		PILHA_pushPilha(auxiliar, cAuxiliar);

		CAR_retornaFace(cAuxiliar, &face2);
		CAR_retornaPosicao(cAuxiliar, &posicao2);
		CAR_retornaNaipe(cAuxiliar, &naipe2);

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
*  $FC Função: SQP SQP pop SQP
*
*
***********************************************************************/
SQP_tpCondRet SQP_popSQP(SQP_tpSQPrincipal sSQP, CAR_tpCarta *Carta){
	PILHA_popPilha(sSQP->sqPrincipal, Carta);

	return SQP_CondRetOK;
} /* Fim função: SQP SQP pop SQP */
/********** Fim do módulo de implementação: SQP Sequencias Principais **********/