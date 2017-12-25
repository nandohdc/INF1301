/***************************************************************************
*  $MCI Módulo de implementação: CAR Carta
*
*  Arquivo gerado:              Carta.c
*  Letras identificadoras:      CAR
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
*     Versão  Autor     Data       Observações
*		5.00  ds/fh/mr 27/04/2015  atribuição de condições de retorno para as funções do módulo
*		4.00	avs    01/02/2006  criar linguagem script simbólica
*		3.00	avs    08/12/2004  uniformização dos exemplos
*		2.00	avs    07/07/2003  unificação de todos os módulos em um só projeto
*		1.00	avs    16/04/2003  início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "PilhadeCartas.h"
#ifdef _DEBUG
#include "GENERICO.H"
#include "cespdin.h"
#include "CONTA.H"
#include "IdTiposEspaco.def"
#endif
#pragma pack (1)

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemLista {

	void * pValor;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista * pAnt;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista * pProx;
	/* Ponteiro para o elemento sucessor */

} tpElemLista;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

typedef struct LIS_tagLista {

	tpElemLista * pOrigemLista;
	/* Ponteiro para a origem da lista */

	tpElemLista * pFimLista;
	/* Ponteiro para o final da lista */

	tpElemLista * pElemCorr;
	/* Ponteiro para o elemento corrente da lista */

	int numElem;
	/* Número de elementos da lista */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} LIS_tpLista;

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem);

static tpElemLista * CriarElemento(LIS_tppLista pLista,
	void *       pValor);


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

LIS_tpCondRet LIS_CriarLista(LIS_tppLista *pLista,
	void(*ExcluirValor) (void * pDado))
{

	if (*pLista = NULL)
	{
		LIS_DestruirLista(*pLista);
	}

	*pLista = (LIS_tpLista *)malloc(sizeof(LIS_tpLista));
	if (*pLista == NULL)
	{
		return LIS_CondRetFaltouMemoria;
	} /* if */

	(*pLista)->pOrigemLista = NULL;
	(*pLista)->pFimLista = NULL;
	(*pLista)->pElemCorr = NULL;
	(*pLista)->numElem = 0;

	(*pLista)->ExcluirValor = ExcluirValor;

	return LIS_CondRetOK;

} /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

LIS_tpCondRet LIS_DestruirLista(LIS_tppLista pLista)
{

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	if (pLista != NULL)
	{
		LIS_tpCondRet CondRet;

		CondRet = LIS_EsvaziarLista(pLista);
		if (CondRet != LIS_CondRetOK)
		{
			return CondRet;
		} /* if */

	} /* if */

	free(pLista);

	pLista = NULL;

	return LIS_CondRetOK;

} /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

LIS_tpCondRet LIS_EsvaziarLista(LIS_tppLista pLista)
{

	tpElemLista * pElem;
	tpElemLista * pProx;

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	if (pLista == NULL)
	{
		return LIS_CondRetListaNaoExiste;
	} /* if */

	pElem = pLista->pOrigemLista;
	while (pElem != NULL)
	{
		pProx = pElem->pProx;
		LiberarElemento(pLista, pElem);
		pElem = pProx;
	} /* while */

	pLista->pOrigemLista = NULL;
	pLista->pFimLista = NULL;
	pLista->pElemCorr = NULL;
	pLista->numElem = 0;

	return LIS_CondRetOK;

} /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista,
	void * pValor)
{

	tpElemLista * pElem;

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	/* Criar elemento a inerir antes */

	pElem = CriarElemento(pLista, pValor);
	if (pElem == NULL)
	{
		return LIS_CondRetFaltouMemoria;
	} /* if */

	/* Encadear o elemento antes do elemento corrente */

	if (pLista->pElemCorr == NULL)
	{
		pLista->pOrigemLista = pElem;
		pLista->pFimLista = pElem;
	}
	else
	{
		if (pLista->pElemCorr->pAnt != NULL)
		{
			pElem->pAnt = pLista->pElemCorr->pAnt;
			pLista->pElemCorr->pAnt->pProx = pElem;
		}
		else
		{
			pLista->pOrigemLista = pElem;
		} /* if */

		pElem->pProx = pLista->pElemCorr;
		pLista->pElemCorr->pAnt = pElem;
	} /* if */

	pLista->pElemCorr = pElem;

	return LIS_CondRetOK;

} /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista,
	void * pValor)

{

	tpElemLista * pElem;

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	/* Criar elemento a inerir após */

	pElem = CriarElemento(pLista, pValor);
	if (pElem == NULL)
	{
		return LIS_CondRetFaltouMemoria;
	} /* if */

	/* Encadear o elemento após o elemento */

	if (pLista->pElemCorr == NULL)
	{
		pLista->pOrigemLista = pElem;
		pLista->pFimLista = pElem;
	}
	else
	{
		if (pLista->pElemCorr->pProx != NULL)
		{
			pElem->pProx = pLista->pElemCorr->pProx;
			pLista->pElemCorr->pProx->pAnt = pElem;
		}
		else
		{
			pLista->pFimLista = pElem;
		} /* if */

		pElem->pAnt = pLista->pElemCorr;
		pLista->pElemCorr->pProx = pElem;

	} /* if */

	pLista->pElemCorr = pElem;

	return LIS_CondRetOK;

} /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista)
{

	tpElemLista * pElem;

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	if (pLista->pElemCorr == NULL)
	{
		return LIS_CondRetListaVazia;
	} /* if */

	pElem = pLista->pElemCorr;

	/* Desencadeia à esquerda */

	if (pElem->pAnt != NULL)
	{
		pElem->pAnt->pProx = pElem->pProx;
		pLista->pElemCorr = pElem->pAnt;
	}
	else {
		pLista->pElemCorr = pElem->pProx;
		pLista->pOrigemLista = pLista->pElemCorr;
	} /* if */

	/* Desencadeia à direita */

	if (pElem->pProx != NULL)
	{
		pElem->pProx->pAnt = pElem->pAnt;
	}
	else
	{
		pLista->pFimLista = pElem->pAnt;
	} /* if */

	LiberarElemento(pLista, pElem);

	return LIS_CondRetOK;

} /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referÍncia para o valor contido no elemento
*  ****/

LIS_tpCondRet LIS_ObterValor(LIS_tppLista pLista, void ** pValor)
{

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	if (pLista == NULL)
	{
		return LIS_CondRetListaNaoExiste;
	} /* if */

	if (pLista->pElemCorr == NULL)
	{
		*pValor = NULL;
		return LIS_CondRetListaVazia;
	} /* if */

	*pValor = pLista->pElemCorr->pValor;

	return LIS_CondRetOK;

} /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

LIS_tpCondRet LIS_IrInicioLista(LIS_tppLista pLista)
{

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	if (pLista == NULL)
	{
		return LIS_CondRetListaNaoExiste;
	} /* if */

	if (pLista->pElemCorr == NULL)
	{
		return LIS_CondRetListaVazia;
	}

	pLista->pElemCorr = pLista->pOrigemLista;

	return LIS_CondRetOK;

} /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

LIS_tpCondRet LIS_IrFinalLista(LIS_tppLista pLista)
{

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	if (pLista == NULL)
	{
		return LIS_CondRetListaNaoExiste;
	} /* if */

	if (pLista->pElemCorr == NULL)
	{
		return LIS_CondRetListaVazia;
	} /* if */

	pLista->pElemCorr = pLista->pFimLista;

	return LIS_CondRetOK;

} /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista,
	int numElem)
{

	int i;

	tpElemLista * pElem;

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	/* Tratar lista vazia */

	if (pLista->pElemCorr == NULL)
	{

		return LIS_CondRetListaVazia;

	} /* fim ativa: Tratar lista vazia */

	/* Tratar avançar para frente */

	if (numElem > 0)
	{

		pElem = pLista->pElemCorr;
		for (i = numElem; i > 0; i--)
		{
			if (pElem == NULL)
			{
				break;
			} /* if */
			pElem = pElem->pProx;
		} /* for */

		if (pElem != NULL)
		{
			pLista->pElemCorr = pElem;
			return LIS_CondRetOK;
		} /* if */

		pLista->pElemCorr = pLista->pFimLista;
		return LIS_CondRetFimLista;

	} /* fim ativa: Tratar avançar para frente */

	/* Tratar avançar para trás */

	else if (numElem < 0)
	{

		pElem = pLista->pElemCorr;
		for (i = numElem; i < 0; i++)
		{
			if (pElem == NULL)
			{
				break;
			} /* if */
			pElem = pElem->pAnt;
		} /* for */

		if (pElem != NULL)
		{
			pLista->pElemCorr = pElem;
			return LIS_CondRetOK;
		} /* if */

		pLista->pElemCorr = pLista->pOrigemLista;
		return LIS_CondRetFimLista;

	} /* fim ativa: Tratar avançar para trás */

	/* Tratar não avançar */

	return LIS_CondRetOK;

} /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista,
	void * pValor)
{

	tpElemLista * pElem;

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	if (pLista->pElemCorr == NULL)
	{
		return LIS_CondRetListaVazia;
	} /* if */

	for (pElem = pLista->pElemCorr;
		pElem != NULL;
		pElem = pElem->pProx)
	{
		if (pElem->pValor == pValor)
		{
			pLista->pElemCorr = pElem;
			return LIS_CondRetOK;
		} /* if */
	} /* for */

	return LIS_CondRetNaoAchou;

} /* Fim função: LIS  &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem)
{

	if ((pLista->ExcluirValor != NULL)
		&& (pElem->pValor != NULL))
	{
		pLista->ExcluirValor(pElem->pValor);
	} /* if */

	free(pElem);

	pLista->numElem--;

} /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

tpElemLista * CriarElemento(LIS_tppLista pLista,
	void *       pValor)
{

	tpElemLista * pElem;

	pElem = (tpElemLista *)malloc(sizeof(tpElemLista));
	if (pElem == NULL)
	{
		return NULL;
	} /* if */

	pElem->pValor = pValor;
	pElem->pAnt = NULL;
	pElem->pProx = NULL;

	pLista->numElem++;

	return pElem;

} /* Fim função: LIS  -Criar o elemento */

/***********************************************************************
*
*  $FC Função: LIS  -Retorna Num Elementos
*
***********************************************************************/
LIS_tpCondRet LIS_retornaNumElementos(LIS_tppLista pLista, int *Num){
	*Num = pLista->numElem;

	if (pLista->numElem == 0){
		return LIS_CondRetListaVazia;
	}
	else{
		return LIS_CondRetOK;
	}
} /* Fim função: LIS  -Retorna Num Elementos */

#ifdef _DEBUG

void LIS_eliminaElemCorr(LIS_tppLista pLista){  // 1
	CED_MarcarEspacoNaoAtivo(pLista->pElemCorr);
	free(pLista->pElemCorr);
	
}

void LIS_apontaSucessorNULL(LIS_tppLista pLista){  // 2
	pLista->pElemCorr->pProx = NULL;
}

void LIS_apontaPredecessorNULL(LIS_tppLista pLista){  // 3
	pLista->pElemCorr->pAnt = NULL;
}

void LIS_apontaSucessorLIXO(LIS_tppLista pLista){  // 4
	static char EspacoLixo[256] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	pLista->pElemCorr->pProx = (CAR_tpCarta) EspacoLixo;
}

void LIS_apontaPredecessorLIXO(LIS_tppLista pLista){  // 5
	static char EspacoLixo[256] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	pLista->pElemCorr->pAnt = (CAR_tpCarta) EspacoLixo;
}

void LIS_atribuiConteudoNULL(LIS_tppLista pLista){ //Nao esta atribuindo o conteudo para null, mas sim o ponteiro   // 6
	pLista->pElemCorr->pValor = NULL;
}



void LIS_destacaNo(LIS_tppLista pLista){  // 8
	tpElemLista *L1;
	tpElemLista *L2;
	L1 = pLista->pElemCorr->pAnt;
	L2 = pLista->pElemCorr->pProx;
	L1->pProx = L2;
	L2->pAnt = L1;
	pLista->pElemCorr->pProx = NULL;
	pLista->pElemCorr->pAnt = NULL;
}

void LIS_elemCorrenteNULL(LIS_tppLista pLista){  // 9
	pLista->pElemCorr = NULL;
}

void LIS_elemOrigemNULL(LIS_tppLista pLista){  // 10
	pLista->pOrigemLista = NULL;
}

LIS_tpCondRet LIS_retornaSuc(LIS_tppLista pLista, tpElemLista **suc){
	if (pLista->pElemCorr == NULL){
		*suc = NULL;
		return LIS_CondRetOK;
	}
	*suc = pLista->pElemCorr->pProx;
	return LIS_CondRetOK;
}

LIS_tpCondRet LIS_retornaPred(LIS_tppLista pLista, tpElemLista **pred){
	if (pLista->pElemCorr == NULL){
		*pred = NULL;
		return LIS_CondRetOK;
	}
	*pred = pLista->pElemCorr->pAnt;
	return LIS_CondRetOK;
}

LIS_tpCondRet LIS_retornaCorr(LIS_tppLista pLista, tpElemLista **corr){
	if (pLista->pElemCorr == NULL){
		*corr = NULL;
		return LIS_CondRetOK;
	}
	*corr = pLista->pElemCorr;
	return LIS_CondRetOK;
}

LIS_tpCondRet LIS_retornaOrigem(LIS_tppLista pLista, tpElemLista **origem){
	if (pLista->pOrigemLista == NULL){
		*origem = NULL;
		return LIS_CondRetOK;
	}
	*origem = pLista->pOrigemLista;
	return LIS_CondRetOK;
}

LIS_tpCondRet LIS_retornaPValor(LIS_tppLista pLista, CAR_tpCarta *pValor, int qual){
	if (pLista->pElemCorr == NULL){
		*pValor = NULL;
		return LIS_CondRetOK;
	}
	if (qual == 0){
		if (pLista->pElemCorr == NULL){
			*pValor = NULL;
			return LIS_CondRetOK;
		}
		*pValor = pLista->pElemCorr->pValor;
	}
	else if (qual == 1){
		if (pLista->pElemCorr->pAnt == NULL){
			*pValor = NULL;
			return LIS_CondRetOK;
		}
		*pValor = pLista->pElemCorr->pAnt->pValor;
	}
	else if (qual == 2){
		if (pLista->pElemCorr->pProx == NULL){
			*pValor = NULL;
			return LIS_CondRetOK;
		}
		*pValor = pLista->pElemCorr->pProx->pValor;
	}
	return LIS_CondRetOK;
}



#endif

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

