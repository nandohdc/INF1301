/***************************************************************************
*
*  $MCD M�dulo de defini��o: SQF Sequencias Finais
*
*  Arquivo gerado:              SequenciasFinais.h
*  Letras identificadoras:      SQF
*
*
*  Projeto: Disciplinas INF 1301
*  Professor: Flavio
*  Autores: ds	- Daniel Siles
*			fh	- Fernando Homem
*			mr	- Mateus Ribeiro
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor         Data     Observa��es
*		4.00 ds/fh/mr 06/06/2015 Adi��o da fun��o retorna pilha.
*       3.00 ds/fh/mr 26/04/2015 Uniformiza��o da interface das fun��es e
*                                de todas as condi��es de retorno.
*       2.00 ds/fh/mr 22/04/2015 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00 ds/fh/mr 17/04/2015 In�cio do desenvolvimento
*
***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#include"PilhadeCartas.h"
#include"Carta.h"


#define SEQUENCIASFINAIS_OWN
#include "Sequ�nciasFinais.h"
#undef SEQUENCIASFINAIS_OWN

struct sequenciaFinal{
	PILHA_tpPilha sqFinal;
};

/***********************************************************************
*
*  $FC Fun��o: SQF criar SQFinal
*
*
***********************************************************************/
SQF_tpCondRet SQF_criarSQFinal(SQF_tpSQFinal *SQFinal){
	PILHA_tpCondRet pRet;

	*SQFinal = (SQF_tgSQFinal*)malloc(sizeof(SQF_tpSQFinal));
	if (*SQFinal == NULL)
	{
		return SQF_CondRetFaltouMemoria;
	}
	pRet = PILHA_criarPilha(&((*SQFinal)->sqFinal));

	if (pRet == PILHA_CondRetFaltouMemoria){
		return SQF_CondRetFaltouMemoria;
	}

	return SQF_CondRetOK;
}/* Fim fun��o: SQF criar SQFinal */

/***********************************************************************
*
*  $FC Fun��o: SQF libera SQFinal
*
*
***********************************************************************/
SQF_tpCondRet SQF_liberaSQFinal(SQF_tpSQFinal SQFinal){
	
	if(SQFinal->sqFinal == NULL){
		free(SQFinal);
	}
	else{
		PILHA_liberaPilha(SQFinal->sqFinal);
	}
	
	return SQF_CondRetOK;
}/* Fim fun��o: SQF libera SQFinal */

/***********************************************************************
*
*  $FC Fun��o: SQF inicializa SQFinal
*
*
***********************************************************************/
SQF_tpCondRet SQF_inicializaSQFinal(SQF_tpSQFinal SQFinal, PILHA_tpPilha sqFinal){
	
	CAR_tpCarta cAuxiliar;
	
	if (SQFinal == NULL){
		return SQF_CondRetPilhaVazia;
	}
	


	while (PILHA_verificaPilhaVazia(sqFinal) == PILHA_CondRetOK){
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(sqFinal, &cAuxiliar);
		PILHA_pushPilha(SQFinal->sqFinal, cAuxiliar);
		
	}


	return SQF_CondRetOK;

}/* Fim fun��o: SQF inicializa SQFinal */

/***********************************************************************
*
*  $FC Fun��o: SQF retorna Pilha
*
*
***********************************************************************/
SQF_tpCondRet SQF_retornaPilha(SQF_tpSQFinal SQF, PILHA_tpPilha *pPilha){
	if (SQF->sqFinal == NULL){
		return SQF_CondRetPilhaVazia;
	}

	(*pPilha) = SQF->sqFinal;

	return SQF_CondRetOK;
}/* Fim fun��o: SQF retorna Pilha */

/********** Fim do m�dulo de implementa��o: SQF Sequencias Finais **********/
