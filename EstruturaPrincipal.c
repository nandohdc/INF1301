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