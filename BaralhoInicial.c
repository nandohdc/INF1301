/***************************************************************************
*  $MCI Módulo de implementação: BAR Baralho Inicial
*
*  Arquivo gerado:              BaralhoInicial.c
*  Letras identificadoras:      BAR
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
*		4.00 ds/fh/mr 27/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte II.
*       3.00 ds/fh/mr 26/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte I.
*       2.00 ds/fh/mr 22/04/2015 Eliminação de código duplicado, reestruturação
*       1.00 ds/fh/mr 17/04/2015 Início do desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "PilhadeCartas.h"
#include "Carta.h"
#include <time.h>
#include <malloc.h>

#define BARALHO_INICAL_OWN
#include "BaralhoInicial.h"
#undef BARALHO_INICIAL_OWN


//#define TAM_BARALHO 104
//#define VALORES_POSSIVEIS 13
/* A=1, 2=2 ... K=13 */
//#define PILHAS_AUX_EMBARALHAMENTO 10

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de baralho
*
*
***********************************************************************/

struct baralho {

	char nNaipes;
	/* Número de naipes do baralho */

	PILHA_tpPilha pBCartas;
	/* Ponteiro para pilha com todas as cartas do baralho */

};


/***********************************************************************
*
*  $FC Função: BAR criar Baralho
*
*
***********************************************************************/
BAR_tpCondRet BAR_criarBaralho(BAR_tpBaralho * pBaralho){

	*pBaralho = (BAR_tgBaralho*)malloc(sizeof(BAR_tgBaralho));
	if (*pBaralho == NULL)
	{
		return BAR_CondRetFaltouMemoria;
	}

	(*pBaralho)->nNaipes = 0;
	(*pBaralho)->pBCartas = NULL;

	return BAR_CondRetOK;

} /* Fim função: BAR Criar Baralho */ 

/***********************************************************************
*
*  $FC Função: BAR liberar Baralho
*
*
***********************************************************************/
BAR_tpCondRet BAR_liberarBaralho(BAR_tpBaralho pBaralho){
	
	if (pBaralho->pBCartas != NULL){
		PILHA_liberaPilha(pBaralho->pBCartas);
	}

	free(pBaralho);
	pBaralho = NULL;
	
	return BAR_CondRetOK;
} /* Fim função: BAR Liberar Baralho */ 

/***********************************************************************
*
*  $FC Função: BAR inicializar Baralho
*
*
***********************************************************************/
BAR_tpCondRet BAR_inicializarBaralho(BAR_tpBaralho pBaralho, int numNaipes){
	CAR_tpCarta c;
	PILHA_tpCondRet pRet;
	
	char naipes[4] = { 'E', 'C', 'P', 'O' };
	char cartas[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K' };

	char posicao = '0';
	char naipe = '0';
	char face = '0';

	int i = 0;
	int j = 0;
	int n = 0;
	int carta;
	
	if (pBaralho == NULL){
		return BAR_CondRetBaralhoNaoExiste;
	}
	pBaralho->nNaipes = numNaipes;

	pRet = PILHA_criarPilha(&(pBaralho->pBCartas));
	
	if (pRet == PILHA_CondRetFaltouMemoria){
		return BAR_CondRetFaltouMemoria;
	}
		
	if (numNaipes == 1){
		for (j = 0; j < 8; j++){
			for (carta = 0; carta < 13; carta++){
				CAR_criarCarta(&c);
				CAR_editarCarta(c, 'E', naipes[n], cartas[carta]);
				PILHA_pushPilha(pBaralho->pBCartas, c); 
			}
		}
	}

	else if (numNaipes == 2){
		for (j = 0; j < 8; j++){
			if (j % 4 == 0 && j != 0){
				n++;
			}			
			for (carta = 0; carta < 13; carta++){
				CAR_criarCarta(&c);
				CAR_editarCarta(c, 'E', naipes[n], cartas[carta]);
				PILHA_pushPilha(pBaralho->pBCartas, c);
				
			}
		}
	}
	else if (numNaipes == 3){
		for (j = 0; j < 8; j++){
			if (j % 3 == 0 && j != 0){
				n++;
			}
			for (carta = 0; carta < 13; carta++){
				CAR_criarCarta(&c);
				CAR_editarCarta(c, 'E', naipes[n], cartas[carta]);
				PILHA_pushPilha(pBaralho->pBCartas, c);
			}
		}
	}
	else if (numNaipes == 4){
		for (j = 0; j < 8; j++){
			if (j % 2 == 0 && j != 0){
				n++;
			}
			for (carta = 0; carta < 13;carta++){
				CAR_criarCarta(&c);
				CAR_editarCarta(c, 'E', naipes[n], cartas[carta]);
				PILHA_pushPilha(pBaralho->pBCartas, c);
			}
		}
	}
	else{
		return BAR_CondRetNaipeNaoExiste;
	}
	
	return BAR_CondRetOK;
} /* Fim função: BAR Inicializar Baralho */ 

/***********************************************************************
*
*  $FC Função: BAR embaralhar Baralho
*
*
***********************************************************************/
BAR_tpCondRet BAR_embaralharBaralho(BAR_tpBaralho pBaralho){
	CAR_tpCondRet cRet = CAR_CondRetOK;
	PILHA_tpCondRet pRet;
	
	CAR_tpCarta cAuxiliar;
	PILHA_tpPilha pPilha[2];


	int rand1;
	int rand2;
	int i;
	int j = 0;
	
	char posicao;
	char naipe;
	char face;
	
	if (pBaralho == NULL){
		return BAR_CondRetBaralhoNaoExiste;
	}
	
	
	if (cRet == CAR_CondRetMemoria){
		return BAR_CondRetFaltouMemoria;
	}
	
	pRet = PILHA_criarPilha(&pPilha[0]);
	if (pRet == PILHA_CondRetFaltouMemoria){
		return BAR_CondRetFaltouMemoria;
	}
	pRet = PILHA_criarPilha(&pPilha[1]);
	if (pRet == PILHA_CondRetFaltouMemoria){
		return BAR_CondRetFaltouMemoria;
	}
	
	while (j < 1000){
		
		srand(time(NULL)); // OK->Valido
		
		for (i = 0; i < 52; i++){
			
			CAR_criarCarta(&cAuxiliar);
			PILHA_popPilha(pBaralho->pBCartas, &cAuxiliar);// Pensando em condicao de retorno
			CAR_retornaPosicao(cAuxiliar, &posicao);
			CAR_retornaNaipe(cAuxiliar, &naipe);
			CAR_retornaFace(cAuxiliar, &face);
			CAR_editarCarta(cAuxiliar, face, naipe, posicao);
			PILHA_pushPilha(pPilha[0], cAuxiliar);
		}
		for (i = 0; i < 52; i++){
			CAR_criarCarta(&cAuxiliar);
			PILHA_popPilha(pBaralho->pBCartas, &cAuxiliar);
			CAR_retornaPosicao(cAuxiliar, &posicao);
			CAR_retornaNaipe(cAuxiliar, &naipe);
			CAR_retornaFace(cAuxiliar, &face);
			CAR_editarCarta(cAuxiliar, face, naipe, posicao);
			PILHA_pushPilha(pPilha[1], cAuxiliar);
		}
		
		if (pBaralho->pBCartas == NULL){
			printf("Eu sou de null");
		}
		int k = 0;
		while (PILHA_verificaPilhaVazia(pPilha[0]) == PILHA_CondRetOK  || PILHA_verificaPilhaVazia(pPilha[1]) == PILHA_CondRetOK){
			
			rand1 = rand() % 4;
			rand2 = rand() % 4;
			
			for (i = 0; i < rand1; i++){
				if (PILHA_verificaPilhaVazia(pPilha[0]) == PILHA_CondRetOK){
					if (PILHA_verificaPilhaVazia(pPilha[0]) == PILHA_CondRetOK){
						CAR_criarCarta(&cAuxiliar);
						PILHA_popPilha(pPilha[0], &cAuxiliar);
						PILHA_pushPilha(pBaralho->pBCartas, cAuxiliar);
						k++;
					}
				}
			}

			for (i = 0; i < rand2; i++){
				if (PILHA_verificaPilhaVazia(pPilha[1]) == PILHA_CondRetOK){
					if (PILHA_verificaPilhaVazia(pPilha[1]) == PILHA_CondRetOK){
						CAR_criarCarta(&cAuxiliar);
						PILHA_popPilha(pPilha[1], &cAuxiliar);
						PILHA_pushPilha(pBaralho->pBCartas, cAuxiliar);
						k++;
					}
					
				}
			}
			
		}
		j++;
	}
	
	return BAR_CondRetOK;
} /* Fim função: BAR Embaralhar Baralho */ 

/***********************************************************************
*
*  $FC Função: BAR imprime Baralho
*
*
***********************************************************************/
BAR_tpCondRet BAR_imprimeBaralho(BAR_tpBaralho baralho){
	
	PILHA_tpPilha auxiliar;
	CAR_tpCarta carta;
	
	
	if (baralho == NULL){
		return BAR_CondRetBaralhoNaoExiste;
	}
	
	PILHA_criarPilha(&auxiliar);
	CAR_criarCarta(&carta);

	while (PILHA_verificaPilhaVazia(baralho->pBCartas) == PILHA_CondRetOK){
		PILHA_popPilha(baralho->pBCartas, &carta);
		CAR_imprimeCarta(carta);
		PILHA_pushPilha(auxiliar, carta);
	}

	return BAR_CondRetOK;
} /* Fim função: BAR Imprime Baralho */ 

BAR_tpCondRet BAR_popBaralho(BAR_tpBaralho bBaralho, CAR_tpCarta *cCarta){
	if (bBaralho->pBCartas == NULL){
		*cCarta = NULL;
		return BAR_CondRetBaralhoVazio;
	}

	if (PILHA_verificaPilhaVazia(bBaralho->pBCartas) == PILHA_CondRetPilhaVazia){
		*cCarta = NULL;
		return BAR_CondRetBaralhoPilhaVazia;
	}

	PILHA_popPilha(bBaralho->pBCartas, cCarta);

	return BAR_CondRetOK;

}


BAR_tpCondRet BAR_retornaTopoBaralho(BAR_tpBaralho baralho, PILHA_tpPilha *pilha){
	(*pilha) = baralho->pBCartas;
	return BAR_CondRetOK;
}

/********** Fim do módulo de implementação: BAR  Baralho Inicial  **********/

