/***************************************************************************
*  $MCI Módulo de implementação: PILHA PilhadeCartas
*
*  Arquivo gerado:              PilhadeCartas.c
*  Letras identificadoras:      PILHA
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
*		5.00 ds/fh/mr 06/06/2015 Adição da função retorna número de elementos.
*		4.00 ds/fh/mr 27/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte II.
*       3.00 ds/fh/mr 26/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte I.
*       2.00 ds/fh/mr 22/04/2015 Eliminação de código duplicado, reestruturação
*       1.00 ds/fh/mr 17/04/2015 Início do desenvolvimento
*
***************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#include"Carta.h"
#include"LISTA.h"

#ifdef _DEBUG
#include "GENERICO.H"
#include "cespdin.h"
#include "CONTA.H"
#include "IdTiposEspaco.def"
#endif

#pragma pack (1)

#define PILHADECARTAS_OWN
#include "PilhadeCartas.h"
#undef PILHADECARTAS_OWN


struct pilha{

#ifdef _DEBUG
	int tipo;
	int tam;
#endif

	LIS_tppLista topo;
};

/*****  Código das funções exportadas pelo módulo  *****/



void DestruirCarta(void * pValor);


/***********************************************************************
*
*  $FC Função: PILHA criar Pilha
*
*
***********************************************************************/
PILHA_tpCondRet PILHA_criarPilha(PILHA_tpPilha *pPilha){ //Lembrete: a nossa função cria uma pilhas vazia!
#ifdef _DEBUG
	CNT_CONTAR("PILHA_criarPilha");
#endif
	LIS_tpCondRet auxiliar;

	*pPilha = NULL;

	*pPilha = (PILHA_tgPilha*)malloc(sizeof(PILHA_tgPilha));

	if (*pPilha == NULL){
		return PILHA_CondRetFaltouMemoria;
	}

	auxiliar = LIS_CriarLista(&((*pPilha)->topo), DestruirCarta);
	if (auxiliar == LIS_CondRetFaltouMemoria){
		return PILHA_CondRetFaltouMemoria;
	}

#ifdef _DEBUG
	(*pPilha)->tipo = 'c';
	(*pPilha)->tam = 0;
	CED_MarcarEspacoAtivo(pPilha);
#endif



	return PILHA_CondRetOK;

}/* Fim função: PILHA criar Pilha */

/***********************************************************************
*
*  $FC Função: PILHA push Pilha
*
*
***********************************************************************/
PILHA_tpCondRet PILHA_pushPilha(PILHA_tpPilha pPilha, CAR_tpCarta c){

#ifdef _DEBUG
	CNT_CONTAR("PILHA_pushPilha");
#endif

	LIS_IrInicioLista(pPilha->topo);

	LIS_InserirElementoAntes(pPilha->topo, c);

#ifdef _DEBUG
	pPilha->tam++;
#endif

	return PILHA_CondRetOK;

}/* Fim função: PILHA push Pilha */

/***********************************************************************
*
*  $FC Função: PILHA pop Pilha
*
*
***********************************************************************/
PILHA_tpCondRet PILHA_popPilha(PILHA_tpPilha pPilha, CAR_tpCarta *pCarta){

#ifdef _DEBUG
	CNT_CONTAR("PILHA_popPilha");
#endif

	CAR_tpCondRet cRet;
	char naipe;
	char posicao;
	char face;


	LIS_ObterValor(pPilha->topo, pCarta);
	CAR_retornaFace(*pCarta, &face);
	CAR_retornaNaipe(*pCarta, &naipe);
	CAR_retornaPosicao(*pCarta, &posicao);

	LIS_ExcluirElemento(pPilha->topo);

	/*Como foi excluído o nó da lista, é necessário criar novamente a carta para não perder os dados*/
	CAR_criarCarta(pCarta);
	cRet = CAR_editarCarta(*pCarta, face, naipe, posicao);

	if (cRet == CAR_CondRetFaceErrada){
		return PILHA_CondRetNaoEncontrou;
	}

#ifdef _DEBUG
	pPilha->tam--;
#endif

	return PILHA_CondRetOK;

}/* Fim função: PILHA pop Pilha */

int checarPilha(PILHA_tpPilha pPilha){ //uso interno

	if (pPilha->topo == NULL){
		return 0;
	}
	return 1;
}

/***********************************************************************
*
*  $FC Função: PILHA libera Pilha
*
*
***********************************************************************/
PILHA_tpCondRet PILHA_liberaPilha(PILHA_tpPilha pPilha){

#ifdef _DEBUG
	CNT_CONTAR("PILHA_liberaPilha");
#endif

	if (checarPilha(pPilha) == 0){
		free(pPilha);
		return PILHA_CondRetOK;
	}

	LIS_DestruirLista(pPilha->topo); //Esvazia a Lista e depois libera o ponteiro para lista.

	return PILHA_CondRetOK;

}/* Fim função: PILHA libera Pilha */

/***********************************************************************
*
*  $FC Função: PILHA verifica Pilha Vazia
*
*
***********************************************************************/
PILHA_tpCondRet PILHA_verificaPilhaVazia(PILHA_tpPilha pPilha){

#ifdef _DEBUG
	CNT_CONTAR("PILHA_verificaPilhaVazia");
#endif

	int n;

	if (LIS_retornaNumElementos(pPilha->topo, &n) == LIS_CondRetOK){
		return PILHA_CondRetOK;
	}
	else{
		return PILHA_CondRetPilhaVazia;
	}
}/* Fim função: PILHA verifica Pilha Vazia */

/***********************************************************************
*
*  $FC Função: PILHA imprime Pilha
*
*
***********************************************************************/
PILHA_tpCondRet PILHA_imprimePilha(PILHA_tpPilha pPilha){

#ifdef _DEBUG
	CNT_CONTAR("PILHA_imprimePilha");
#endif

	PILHA_tpPilha auxiliar2;
	CAR_tpCarta cAuxiliar;
	PILHA_tpPilha auxiliar;
	char posicao;
	char face;
	char naipe;

	PILHA_criarPilha(&auxiliar);
	PILHA_criarPilha(&auxiliar2);
	CAR_criarCarta(&cAuxiliar);

	if (PILHA_verificaPilhaVazia(pPilha) == PILHA_CondRetPilhaVazia){
		return PILHA_CondRetPilhaVazia;
	}

	while (PILHA_verificaPilhaVazia(pPilha) == PILHA_CondRetOK){
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(pPilha, &cAuxiliar);
		PILHA_pushPilha(auxiliar, cAuxiliar);
	}

	while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
		CAR_criarCarta(&cAuxiliar);
		PILHA_popPilha(auxiliar, &cAuxiliar);
		PILHA_pushPilha(auxiliar2, cAuxiliar);
		CAR_retornaFace(cAuxiliar, &face);
		CAR_retornaNaipe(cAuxiliar, &naipe);
		CAR_retornaPosicao(cAuxiliar, &posicao);
		CAR_criarCarta(&cAuxiliar);
		CAR_editarCarta(cAuxiliar, face, naipe, posicao);
		PILHA_pushPilha(pPilha, cAuxiliar);
	}


	while (PILHA_verificaPilhaVazia(auxiliar2) == PILHA_CondRetOK){
		CAR_tpCarta carta;
		CAR_criarCarta(&carta);
		PILHA_popPilha(auxiliar2, &carta);
		CAR_retornaPosicao(carta, &posicao);
		CAR_retornaNaipe(carta, &naipe);
		CAR_retornaFace(carta, &face);
		printf("Carta da Pilha: P: %c N: %c F: %c", posicao, naipe, face);

	}
	return PILHA_CondRetOK;
}/* Fim função: PILHA imprime Pilha */

/***********************************************************************
*
*  $FC Função: PILHA retorna Num Elem
*
*
***********************************************************************/
PILHA_tpCondRet PILHA_retornaNumElem(PILHA_tpPilha pPilha, int *num){

#ifdef _DEBUG
	CNT_CONTAR("PILHA_retornaNumElem");
#endif

	LIS_retornaNumElementos(pPilha->topo, num);
	return PILHA_CondRetOK;
}/* Fim função: PILHA retorna Num Elem */


void DestruirCarta(void * pValor)
{
	CAR_destruirCarta((CAR_tpCarta)pValor);
}

#ifdef _DEBUG

PILHA_tpCondRet PILHA_deturpaPilha(PILHA_tpPilha pPilha, int acao, int *numAlocAnt){

	CAR_tpCarta cCarta;

#ifdef _DEBUG
	//CNT_CONTAR("PILHA_deturpaPilha");
#endif
	*numAlocAnt = CED_ObterNumeroEspacosAlocados();
	printf("( %d )", *numAlocAnt);
	if (acao == 1){
		
		LIS_eliminaElemCorr(pPilha->topo);
	}
	else if (acao == 2){
		LIS_apontaSucessorNULL(pPilha->topo);
	}
	else if (acao == 3){
		LIS_apontaPredecessorNULL(pPilha->topo);
	}
	else if (acao == 4){
		LIS_apontaSucessorLIXO(pPilha->topo);
	}
	else if (acao == 5){
		LIS_apontaPredecessorLIXO(pPilha->topo);
	}
	else if (acao == 6){
		LIS_atribuiConteudoNULL(pPilha->topo);
	}
	else if (acao == 7){
		pPilha->tipo = 'i';
	}
	else if (acao == 8){
		LIS_destacaNo(pPilha->topo);
	}
	else if (acao == 9){
		LIS_elemCorrenteNULL(pPilha->topo);
	}
	else if (acao == 10){
		LIS_elemOrigemNULL(pPilha->topo);
	}
	else if (acao == 11){
		LIS_retornaPValor(pPilha->topo, &cCarta, 0);
		CAR_setTipo(cCarta, 'i');
	}
	else{
		//Nao vai deturpar
		printf("\nAção deturpadora invalida");
		return PILHA_CondRetNaoEncontrou;
	}

	return PILHA_CondRetOK;

}

#endif

#ifdef _DEBUG

PILHA_tpCondRet PILHA_verificaNo(PILHA_tpPilha pPilha, int numAlocAnt){


	CNT_CONTAR("PILHA_verificaNo");

	tpElemLista *suc = NULL;
	tpElemLista *pred = NULL;
	tpElemLista *corr = NULL;
	tpElemLista *origem = NULL;
	CAR_tpCarta pValAnt = NULL;
	CAR_tpCarta pValProx = NULL;
	CAR_tpCarta pVal = NULL;
	char tpCarta = NULL;
	int numCarta = NULL;
	int numAlocDps;
	CAR_tpCarta cCarta;

	LIS_retornaSuc(pPilha->topo, &suc);
	LIS_retornaPred(pPilha->topo, &pred);
	LIS_retornaCorr(pPilha->topo, &corr);
	LIS_retornaCorr(pPilha->topo, &origem);
	LIS_retornaPValor(pPilha->topo, &pVal, 0);
	LIS_retornaPValor(pPilha->topo, &pValAnt, 1);
	LIS_retornaPValor(pPilha->topo, &pValProx, 2);
	CAR_retornaTipo(pValAnt, &tpCarta);
	LIS_retornaNumElementos(pPilha->topo, &numCarta);

	numAlocDps = CED_ObterNumeroEspacosAlocados(); // #now. A TV do jeito que vc quer!
	printf("%d - %d", numAlocAnt, numAlocDps);
	if (numAlocAnt != numAlocDps){ // 1
		CNT_CONTAR("PILHA_MER_1");
		printf("\nAção 1 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_1");
		printf("\nAção 1 de acordo.");
	}

	if (suc == NULL){ // 2
		CNT_CONTAR("PILHA_MER_2");
		printf("\nAção 2 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_2");
		printf("\nAção 2 de acordo.");
	}

	if (pred == NULL){ // 3
		CNT_CONTAR("PILHA_MER_3");
		printf("\nAção 3 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_3");
		printf("\nAção 3 de acordo.");
	}

	if (pValAnt == 0x78787878){ // 4
		CNT_CONTAR("PILHA_MER_4");
		printf("\nAção 4 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_4");
		printf("\nAção 4 de acordo.");
	}

	if (pValProx == 0x78787878){ // 5
		CNT_CONTAR("PILHA_MER_5");
		printf("\nAção 5 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_5");
		printf("\nAção 5 de acordo.");
	}

	if (pVal == NULL){  // 6
		CNT_CONTAR("PILHA_MER_6");
		printf("\nAção 6 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_6");
		printf("\nAção 6 de acordo.");
	}

	if (pPilha->tipo != 'c') // 7
	{
		CNT_CONTAR("PILHA_MER_7");
		printf("\nAção 7 verificada.");
	} /* if */
	else {
		CNT_CONTAR("PILHA_ACO_7");
		printf("\nAção 7 de acordo.");
	}

	if (suc == NULL && pred == NULL){ // 8
		CNT_CONTAR("PILHA_MER_8");
		printf("\nAção 8 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_8");
		printf("\nAção 8 de acordo.");
	}

	if (corr == NULL){ // 9
		CNT_CONTAR("PILHA_MER_9");
		printf("\nAção 9 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_9");
		printf("\nAção 9 de acordo.");
	}

	if (origem == NULL){ // 10
		CNT_CONTAR("PILHA_MER_10");
		printf("\nAção 10 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_10");
		printf("\nAção 10 de acordo.");
	}

	if (pPilha->tam <= 1 && pred != NULL ){//11
		CNT_CONTAR("PILHA_MER_11");
		printf("\nAção 11 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_11");
		printf("\nAção 11 de acordo.");
	}

	if (pPilha->tam > 1 && tpCarta != 'c'){//12
		CNT_CONTAR("PILHA_MER_12");
		printf("\nAção 12 verificada.");
	}
	else {
		CNT_CONTAR("PILHA_ACO_12");
		printf("\nAção 12 de acordo.");
	}

	if (corr != origem){ // 13
		CNT_CONTAR("PILHA_MER_13");
		printf("\nAção 13 verificada");
	}
	else {
		CNT_CONTAR("PILHA_ACO_13");
		printf("\nAção 13 de acordo.");
	}

	return PILHA_CondRetOK;
}

#endif
/********** Fim do módulo de implementação: PILHA PilhadeCartas **********/
/*
int main(void){
	PILHA_tpPilha pPilha;
	CAR_tpCarta cCarta;


//	CAR_criarCarta(&cCarta);
//	CAR_editarCarta(cCarta, 'V', 'E', '4');

	PILHA_criarPilha(&pPilha);
//	PILHA_pushPilha(pPilha, cCarta);

//	CAR_editarCarta(cCarta, 'V', 'E', '6');
//	PILHA_pushPilha(pPilha, cCarta);

//	CAR_editarCarta(cCarta, 'V', 'E', 'K');
//	PILHA_pushPilha(pPilha, cCarta);
#ifdef _DEBUG
	//PILHA_deturpaPilha(pPilha, 4);
//	PILHA_deturpaPilha(pPilha, 7);
	//PILHA_deturpaPilha(pPilha, 10);
	//PILHA_deturpaPilha(pPilha, 9);

//	PILHA_verificaNo(pPilha);
#endif
	return 0;
}
*/
