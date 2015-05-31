#if ! defined( PILHADECARTAS_ )
#define PILHADECARTAS_
/***************************************************************************
*
*  $MCD Módulo de definição: PILHA PilhadeCartas
*
*  Arquivo gerado:              PilhadeCartas.h
*  Letras identificadoras:      PILHA
*
*
*  Projeto: Disciplinas INF 1301
*  Professor: Flavio
*  Autores: ds	- Daniel Siles
*			fh	- Fernando Homem
*			mr	- Mateus Ribeiro
*
*  $HA Histórico de evolução:
*     Versão  Autor         Data     Observações
*       3.00 ds/fh/mr 26/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno.
*       2.00 ds/fh/mr 22/04/2015 Eliminação de código duplicado, reestruturação
*       1.00 ds/fh/mr 17/04/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar cartas.
*
***************************************************************************/

#if defined( PILHADECARTAS_OWN )
#define PILHADECARTAS_EXT
#else
#define PILHADECARTAS_EXT extern
#endif

#include"Carta.h"
#include"LISTA.h"

typedef struct pilha PILHA_tgPilha;
typedef PILHA_tgPilha *PILHA_tpPilha;


typedef enum {

	PILHA_CondRetOK = 0,
	/* TUDO CERTO */

	PILHA_CondRetPilhaVazia = 1,
	/* A Pilha não contém elementos */

	PILHA_CondRetFimPilha = 2,
	/* Foi atingido o fim da Pilha */

	PILHA_CondRetNaoEncontrou = 3,
	/* Não encontrou o valor procurado */

	PILHA_CondRetFaltouMemoria = 4
	/* Faltou memória ao tentar criar um elemento de lista */

} PILHA_tpCondRet;

/***********************************************************************
*
*  $FC Função: PILHA Criar Pilha
*
*  $ED Descrição da função
*     Cria uma pilha vazia
*
*  $EP Parâmetros
*	pPilha - Endereço que receberá um ponteiro para a pilha criada.
*
*  $FV Valor retornado
*	PILHA_CondRetOK - Criou a pilha sem erros
*	PILHA_CondRetFaltouMemoria - Faltou memória na criação da pilha
*
***********************************************************************/
PILHA_tpCondRet PILHA_criarPilha(PILHA_tpPilha *pPilha);

/***********************************************************************
*
*  $FC Função: PILHA Push Pilha
*
*  $ED Descrição da função
*     Insere um elemento no topo da pilha.
*
*  $EP Parâmetros
*	pPilha - Endereço que receberá um ponteiro para a pilha na qual será inserida uma carta.
*   c - Endereço da carta a ser inserida no topo da pilha.
*
*  $FV Valor retornado
*	PILHA_CondRetOK - Inseriu o elemento sem erros
*
***********************************************************************/

PILHA_tpCondRet PILHA_pushPilha(PILHA_tpPilha pPilha, CAR_tpCarta c);

/***********************************************************************
*
*  $FC Função: PILHA Pop Pilha
*
*  $ED Descrição da função
*     Retira o último elemento inserido na pilha.
*
*  $EP Parâmetros
*	pPilha - Endereço que receberá um ponteiro para a pilha da qual será retirada uma carta.
*   pCarta - Endereço que recebera um ponteiro para a carta retirada da pilha.
*
*  $FV Valor retornado
*	PILHA_CondRetOK - Retirou o elemento sem erros
*	PILHA_CondRetNaoEncontrou - Carta não encontrada na pilha
*	PILHA_CondRetFimPilha - Final da pilha foi atingido
*	PILHA_CondRetPilhaVazia - A Pilha está vazia
*
***********************************************************************/

PILHA_tpCondRet PILHA_popPilha(PILHA_tpPilha pPilha, CAR_tpCarta *pCarta);

/***********************************************************************
*
*  $FC Função: PILHA Libera Pilha
*
*  $ED Descrição da função
*     Libera a memória utilizada pela pilha.
*
*  $EP Parâmetros
*	pPilha - Endereço do ponteiro com a pilha a ser liberada.
*
*  $FV Valor retornado
*	PILHA_CondRetOK - Pilha liberada com sucesso
*
***********************************************************************/
PILHA_tpCondRet PILHA_liberaPilha(PILHA_tpPilha pPilha);

/***********************************************************************
*
*  $FC Função: PILHA Verifica Pilha Vazia
*
*  $ED Descrição da função
*     Verifica se a pilha está vazia.
*
*  $EP Parâmetros
*	pPilha - Endereço do ponteiro com a pilha a ser verificada.
*
*  $FV Valor retornado
*	PILHA_CondRetOK - Pilha recebida não está vazia.
*	PILHA_CondRetPilhaVazia - Pilha recebida está vazia.
*
*  $EAE Assertivas de entradas esperadas
*     pPilha != NULL
*
***********************************************************************/
PILHA_tpCondRet PILHA_verificaPilhaVazia(PILHA_tpPilha pPilha);

/***********************************************************************
*
*  $FC Função: PILHA Imprime Pilha
*
*  $ED Descrição da função
*     Imprime as cartas contidas na pilha.
*
*  $EP Parâmetros
*	pPilha - Endereço do ponteiro com a pilha a ser exibida.
*
*  $FV Valor retornado
*	PILHA_CondRetOK - Pilha impressa sem erros.
*
*  $EAE Assertivas de entradas esperadas
*     pPilha != NULL
*
***********************************************************************/
PILHA_tpCondRet PILHA_imprimePilha(PILHA_tpPilha pPilha);

PILHA_tpCondRet PILHA_retornaNumElem(PILHA_tpPilha pPilha, int *num);

#undef PILHADECARTAS_EXT

/********** Fim do módulo de definição: PILHA PilhadeCartas **********/

#else
#endif