/***************************************************************************
*  $MCI Módulo de implementação: ESP EstruturaPrincipal
*
*  Arquivo gerado:              EstruturaPrincipal.c
*  Letras identificadoras:      ESP
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
*		4.00 ds/fh/mr 15/05/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte II.
*       3.00 ds/fh/mr 15/05/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte I.
*       2.00 ds/fh/mr 15/05/2015 Eliminação de código duplicado, reestruturação
*       1.00 ds/fh/mr 15/05/2015 Início do desenvolvimento
*
***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include"Carta.h"
#include"BaralhoInicial.h"
#include"PilhadeCartas.h"
#include"Morto.h"
#include"SequênciasPrincipais.h"
#include"SequênciasFinais.h"
#include"LISTA.h"

#define ESTRUTURAPRINCIPAL_OWN
#include "EstruturaPrincipal.h"
#undef ESTRUTURAPRINCIPAL_OWN

struct estruturaprincipal{
	LIS_tppLista *pESP;
};

void DestruirCarta(void * pValor)
{
	CAR_destruirCarta((CAR_tpCarta)pValor);
}

void DestruirLista(void * pLista)
{
	LIS_DestruirLista((LIS_tppLista)pLista);
}

void DestruirMorto(void * mMorto)
{
	MOR_liberaMorto((MOR_tpMorto)mMorto);
}

void DestruirSeqPrincipal(void * sSeqPrincipal)
{
	SQP_liberaSequencia((SQP_tpSQPrincipal)sSeqPrincipal);
}

void DestruirSeqFinal(void * sSeqFinal)
{
	SQF_liberaSQFinal((SQF_tpSQFinal)sSeqFinal);
}

void DestruirBaralho(void * bBaralho)
{
	BAR_liberarBaralho((BAR_tpBaralho)bBaralho);
}

ESP_tpCondRet criaEstruturaPrincipal(ESP_tpEstruturalPrincipal *eESP){
	LIS_tpCondRet auxiliar;

	*eESP = (ESP_tgEstruturalPrincipal*)malloc(sizeof(ESP_tgEstruturalPrincipal));

	if (eESP == NULL){
		return ESP_CondRetFaltouMemoria;
	}

	auxiliar = LIS_CriarLista(&((*eESP)->pESP), DestruirCarta);
	if (auxiliar == LIS_CondRetFaltouMemoria){
		return PILHA_CondRetFaltouMemoria;
	}
}

ESP_tpCondRet escolheDificuldade(int *dificuldade){
	ESP_tpCondRet auxiliar;
	
	printf("Escolha o nivel de dificuldade:\n");
	
	printf("1 -> 1 Naipe  -> Facil\n");
	printf("2 -> 2 Naipes -> Medio\n");
	printf("3 -> 3 Naipes -> Dificil\n");
	printf("4 -> 4 Naipes -> Muito Dificil\n");
	
	printf("Digite o nivel escolhido :\n");
	
	scanf("%d", &dificuldade);

	auxiliar = checadorDificuldade(&dificuldade);

	if (auxiliar == 0){
		return ESP_CondRetNivelErrado;
	}

	return ESP_CondRetOK;

}

int checarDificuldade(int dificuldade){
	int checador[4] = { 1, 2, 3, 4 };
	int i;

	for (i = 0; i < 4; i++){
		if (checador[i] == dificuldade)
			return 1;
	}
	return 0;
}

ESP_tpCondRet distribuiMortoJogo(MOR_tpMorto mMorto, SQP_tpSQPrincipal vSQP[10]){
	ESP_tpCondRet eRet;
	PILHA_tpPilha pAuxiliar;
	PILHA_tpCondRet pRet;
	CAR_tpCarta cAuxiliar;
	CAR_tpCondRet cRet;
	int i;
		
	pRet = PILHA_criarPilha(&pAuxiliar);

	if (pRet == PILHA_CondRetFaltouMemoria){
		return ESP_CondRetFaltouMemoria;
	}
	
	if (mMorto == NULL){
		return ESP_CondRetMortoVazio;
	}

	
	for (i = 0; i < 10; i++){

		if (vSQP[i] == NULL){
			return ESP_CondRetSQPVazia;
		}
	}
	
	
	for (i = 0; i < 10; i++){

		cRet = CAR_criarCarta(&cAuxiliar);
		if (cRet == CAR_CondRetMemoria){
			return ESP_CondRetFaltouMemoria;
		}
		
		MOR_popMorto(mMorto, &cAuxiliar);
		PILHA_pushPilha(pAuxiliar, cAuxiliar);
		SQP_adicionaNaSequencia(pAuxiliar, vSQP[i]);
		PILHA_popPilha(pAuxiliar, &cAuxiliar);
		CAR_destruirCarta(cAuxiliar);
	}

	return ESP_CondRetOK;

}


ESP_tpCondRet distribuiBaralho(BAR_tpBaralho pBaralho, SQP_tpSQPrincipal vSQP[10], MOR_tpMorto *mMorto){
	CAR_tpCondRet cRet;
	CAR_tpCarta cCarta;
	PILHA_tpPilha pPilha;
	PILHA_tpCondRet pRet;
	MOR_tpCondRet mRet;
	PILHA_tpPilha pBCartas;

	BAR_retornaPilhaBaralho(pBaralho, pBCartas);

	int i;

	pRet = PILHA_criarPilha(&pPilha);

	for (i = 0; i< 54; i++){

		cRet = CAR_criarCarta(&cCarta);
		PILHA_popPilha(pBCartas, &cCarta);
		PILHA_pushPilha(pPilha, cCarta);

		if (i < 6){
			SQP_adicionaNaSequencia(pPilha, vSQP[0]);

		}

		if (i >= 6 && i < 12){
			SQP_adicionaNaSequencia(pPilha, vSQP[1]);

		}

		if (i >= 12 && i < 18){
			SQP_adicionaNaSequencia(pPilha, vSQP[2]);

		}

		if (i >= 18 && i < 24){
			SQP_adicionaNaSequencia(pPilha, vSQP[3]);

		}

		if (i >= 24 && i < 29){
			SQP_adicionaNaSequencia(pPilha, vSQP[4]);

		}

		if (i >= 29 && i < 34){
			SQP_adicionaNaSequencia(pPilha, vSQP[5]);

		}

		if (i >= 34 && i < 39){
			SQP_adicionaNaSequencia(pPilha, vSQP[6]);

		}

		if (i >= 39 && i < 44){
			SQP_adicionaNaSequencia(pPilha, vSQP[7]);

		}

		if (i >= 44 && i < 49){
			SQP_adicionaNaSequencia(pPilha, vSQP[8]);

		}

		if (i >= 49 && i < 54){
			SQP_adicionaNaSequencia(pPilha, vSQP[9]);

		}

		PILHA_popPilha(pPilha, &cCarta);
		CAR_destruirCarta(cCarta);
	}

	mRet = MOR_criarMorto(&mMorto, pBCartas);

	return ESP_CondRetOK;

}

ESP_tpCondRet ESP_iniciaNovoJogo(LIS_tppLista * ListaPrincipal){
	int dificuldade;
	CAR_tpCarta carta;
	LIS_tppLista bBaralho;
	LIS_tppLista mMorto;
	LIS_tppLista sSeqFinal;
	LIS_tppLista sSeqPrincipal;
	
	MOR_tpMorto morto;
	SQP_tpSQPrincipal sqPrincipal[10];
	BAR_tpBaralho baralho;
	SQF_tpSQFinal sqFinal[8] = NULL;

	escolheDificuldade(&dificuldade);

	LIS_CriarLista(&bBaralho, DestruirBaralho);
	LIS_CriarLista(&mMorto, DestruirMorto);
	LIS_CriarLista(&sSeqFinal, DestruirSeqFinal);
	LIS_CriarLista(&sSeqPrincipal, DestruirSeqPrincipal);

	LIS_CriarLista(ListaPrincipal, DestruirLista);

	LIS_InserirElementoApos(*ListaPrincipal, bBaralho);
	LIS_InserirElementoApos(*ListaPrincipal, mMorto);
	LIS_InserirElementoApos(*ListaPrincipal, sSeqFinal);
	LIS_InserirElementoApos(*ListaPrincipal, sSeqPrincipal);

	BAR_criarBaralho(&baralho);

	BAR_inicializarBaralho(baralho, dificuldade);
	BAR_embaralharBaralho(baralho);

	LIS_InserirElementoApos(bBaralho, baralho);

	distribuiBaralho(baralho, sqPrincipal, morto);

	LIS_InserirElementoAntes(&mMorto, morto);

	for (int i = 0; i < 10; i++){
		LIS_InserirElementoAntes(&mMorto, sqPrincipal[i]);
	}
	for (int i = 0; i < 8; i++){
		LIS_InserirElementoAntes(&mMorto, sqFinal[i]);
	}

	return ESP_CondRetOK;

}

ESP_tpCondRet ESP_realizaJogada(LIS_tppLista ListaPrincipal, int sq_de, int sq_para, CAR_tpCarta carta){

	SQP_tpSQPrincipal sqDe;
	SQP_tpSQPrincipal sqPara;
	LIS_tppLista sSeqPrincipal;
	PILHA_tpPilha auxiliar;
	PILHA_criarPilha(&auxiliar);

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&sSeqPrincipal);

	LIS_IrInicioLista(sSeqPrincipal);
	LIS_AvancarElementoCorrente(sSeqPrincipal, sq_de);
	LIS_ObterValor(sSeqPrincipal, (void**)&sqDe);

	LIS_IrInicioLista(sSeqPrincipal);
	LIS_AvancarElementoCorrente(sSeqPrincipal, sq_para);
	LIS_ObterValor(sSeqPrincipal, (void**)&sqPara);

	if (SQP_removeDaSequencia(sqDe, carta, &auxiliar) == SQP_CondRetOK){
		SQP_adicionaNaSequencia(auxiliar, sqPara);
		//Sacou?
	}

	SQP_verificaSequenciaCompleta(sqPara);

	return ESP_CondRetOK;
}

ESP_tpCondRet ESP_salvaJogo(LIS_tppLista ListaPrincipal, char nome[]){

	LIS_tppLista listaSqPrincipal;
	LIS_tppLista listaSqFinal;
	SQP_tpSQPrincipal sqPrincipal;
	SQF_tpSQFinal sqFinal;
	CAR_tpCarta carta;
	
	SQF_tpSQFinal sqFinal;
	MOR_tpMorto morto;
	PILHA_tpPilha pilhaMorto;
	PILHA_tpPilha pilha;
	PILHA_tpPilha auxiliar;

	
	char naipe;
	char posicao;
	char face;
	int i, j, k;

	LIS_CriarLista(&listaSqPrincipal, DestruirLista);
	LIS_CriarLista(&listaSqFinal, DestruirLista);
	SQP_criarSequencia(&sqPrincipal);
	CAR_criarCarta(&carta);
	MOR_criarMorto(morto, pilhaMorto);

	PILHA_criarPilha(&auxiliar);
	PILHA_criarPilha(&pilha);
	PILHA_criarPilha(&pilhaMorto);
	FILE *arq = fopen(nome, "w");
	
	
	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 1);
	LIS_ObterValor(ListaPrincipal, (void**)&morto);

	MOR_retornaMorto(morto, &pilhaMorto);
	fprintf(arq, "morto{\n");
	while (PILHA_verificaPilhaVazia(pilhaMorto) == PILHA_CondRetOK){
		MOR_popMorto(morto, &carta);
		MOR_retornaMorto(morto, &pilhaMorto);

		CAR_retornaNaipe(carta, &naipe);
		CAR_retornaPosicao(carta, &posicao);
		CAR_retornaFace(carta, &face);

		fprintf(arq, "%c%c%c\n", face, naipe, posicao);

		MOR_retornaMorto(morto, &pilhaMorto);
	}
	fprintf(arq, "}\n");

	//SEQUENCIAS PRINCIPAIS

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqPrincipal);

	fprintf(arq, "sqPrincipais{");

	for (i = 0; i < 10; i++){

		LIS_IrInicioLista(listaSqPrincipal);
		LIS_AvancarElementoCorrente(listaSqPrincipal, i);
		LIS_ObterValor(listaSqPrincipal, (void**)&sqPrincipal);

		SQP_retornaPilha(sqPrincipal, &pilha);

		fprintf(arq, "%d{\n", i);

		while (PILHA_verificaPilhaVazia(pilha) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(pilha, &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);
			CAR_editarCarta(carta, face, naipe, posicao);
			PILHA_pushPilha(auxiliar, carta);
		}
		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(auxiliar, &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);

			fprintf(arq, "%c%c%c\n", face, naipe, posicao);

			SQP_retornaPilha(sqPrincipal, &pilha);
		}
		fprintf(arq, "}\n");

	}


	fprintf(arq, "}\n");


	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 2);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqFinal);

	//SEQUENCIAS FINAIS

	fprintf(arq, "sqFinais{\n");

	for (i = 0; i < 8; i++){

		LIS_IrInicioLista(listaSqPrincipal);
		LIS_AvancarElementoCorrente(listaSqPrincipal, i);
		LIS_ObterValor(listaSqPrincipal, (void**)&sqFinal);

		SQF_retornaPilha(sqFinal, &pilha);

		fprintf(arq, "%d{\n", i);

		while (PILHA_verificaPilhaVazia(pilha) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(pilha, &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);
			CAR_editarCarta(carta, face, naipe, posicao);
			PILHA_pushPilha(auxiliar, carta);
		}
		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(auxiliar, &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);

			fprintf(arq, "%c%c%c\n", face, naipe, posicao);

			SQP_retornaPilha(sqPrincipal, &pilha);
		}
		fprintf(arq, "}\n");

	}


	fprintf(arq, "}\n");
	

	return ESP_CondRetOK;

}