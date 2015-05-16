/***************************************************************************
*  $MCI M�dulo de implementa��o: MOR Morto
*
*  Arquivo gerado:              Morto.c
*  Letras identificadoras:      MOR
*
*
*  Projeto: Disciplinas INF 1301
*  Professor: Flavio
*  Autores: ds  - Daniel Siles
*			fh  - Fernando Homem
*			mr  - Mateus Ribeiro
*
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*		4.00 ds/fh/mr 27/04/2015 Uniformiza��o da interface das fun��es e
*                                de todas as condi��es de retorno - Parte II.
*       3.00 ds/fh/mr 26/04/2015 Uniformiza��o da interface das fun��es e
*                                de todas as condi��es de retorno - Parte I.
*       2.00 ds/fh/mr 22/04/2015 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00 ds/fh/mr 17/04/2015 In�cio do desenvolvimento
*
***************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#include"PilhadeCartas.h"

#define MORTO_OWN
#include "Morto.h"
#undef MORTO_OWN

struct morto{
	PILHA_tpPilha morto;
};

/***********************************************************************
*
*  $FC Fun��o: MOR criar Morto
*
*
***********************************************************************/
MOR_tpCondRet MOR_criarMorto(MOR_tpMorto *mMorto, PILHA_tpPilha pPilha){

	PILHA_tpCondRet cRet;
	CAR_tpCarta cAuxiliar;

	*mMorto = (MOR_tgMorto*)malloc(sizeof(MOR_tpMorto));
	if (*mMorto == NULL)
	{
		return MOR_CondRetFaltouMemoria;
	}
	cRet = PILHA_criarPilha(&((*mMorto)->morto));

	if (cRet == PILHA_CondRetFaltouMemoria)
	{
		return MOR_CondRetFaltouMemoria;
	}

	while (PILHA_verificaPilhaVazia(pPilha) == PILHA_CondRetOK)
	{
		
		PILHA_popPilha(pPilha, &cAuxiliar);
		PILHA_pushPilha((*mMorto)->morto, cAuxiliar);
	}

	return MOR_CondRetOK;
}/* Fim fun��o: MOR criar Morto */

/***********************************************************************
*
*  $FC Fun��o: MOR liberar Morto
*
*
***********************************************************************/
MOR_tpCondRet MOR_liberaMorto(MOR_tpMorto mMorto){
	if (mMorto->morto == NULL){
		free(mMorto);
		return MOR_CondRetOK;
	}
	else{
		PILHA_liberaPilha(mMorto->morto);
		free(mMorto);
		return MOR_CondRetOK;
	}
}/* Fim fun��o: MOR liberar Morto */

/***********************************************************************
*
*  $FC Fun��o: MOR pop Morto
*
*
***********************************************************************/
MOR_tpCondRet MOR_popMorto(MOR_tpMorto mMorto, CAR_tpCarta * cartaPop){
	PILHA_tpCondRet pRet;
	if (mMorto->morto == NULL){
		return MOR_CondRetMortoVazio;
	}
	
	pRet = PILHA_popPilha(mMorto->morto, cartaPop);
	if (pRet == PILHA_CondRetOK){
		return MOR_CondRetOK;
	}
		return MOR_CondRetNaoOK;
}/* Fim fun��o: MOR pop Morto */

/********** Fim do m�dulo de implementa��o: MOR Morto **********/