#if ! defined( BARALHO_INICIAL_ )
#define BARALHO_INICIAL_
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
#include<stdlib.h>
#include"Carta.h"
#include"PilhadeCartas.h"

#if defined( BARALHO_INICIAL_OWN )
#define BARALHO_INICIAL_EXT
#else
#define BARALHO_INICIAL_EXT extern
#endif



/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um baralho de cartas */
typedef struct baralho BAR_tgBaralho;
typedef struct baralho * BAR_tpBaralho;

/*Condições de Retorno*/

typedef enum{

	BAR_CondRetOK = 0,
	/*Tudo certo*/

	BAR_CondRetBaralhoNaoExiste = 1,
	/*O Baralho nao existe*/

	BAR_CondRetNaipeNaoExiste = 2,
	/*O naipe nao existe || invalido*/

	BAR_CondRetFaltouMemoria = 3,
	/*Excedeu limite de memoria*/

	BAR_CondRetBaralhoVazio = 4,
	/*Baralho vazio*/

	BAR_CondRetBaralhoPilhaVazia = 5

} BAR_tpCondRet;

/***********************************************************************
*
*  $FC Função: BAR Criar Baralho
*
*  $ED Descrição da função
*     Cria um baralho vazio
*
*  $EP Parâmetros
*	pBaralho - Endereço que receberá um ponteiro para o baralho criado.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Criou o baralho sem erros
*	BAR_CondRetFaltouMemoria - Faltou memória na criação do baralho
*
***********************************************************************/
BAR_tpCondRet BAR_criarBaralho(BAR_tpBaralho *pBaralho);

/***********************************************************************
*
*  $FC Função: BAR Liberar Baralho
*
*  $ED Descrição da função
*     Libera o espaço de memória usado pelo baralho.
*
*  $EP Parâmetros
*	pBaralho - Endereço de um ponteiro com o baralho a ser liberado.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Liberou o baralho sem erros
*
***********************************************************************/
BAR_tpCondRet BAR_liberarBaralho(BAR_tpBaralho pBaralho);

/***********************************************************************
*
*  $FC Função: BAR Inicializar Baralho
*
*  $ED Descrição da função
*     Coloca as cartas no baralho.
*
*  $EP Parâmetros
*	pBaralho - Endereço de um ponteiro com o baralho a ser preenchido.
*	numNaipes - Inteiro que define a quantidade de naipes existentes no baralho a ser preenchido.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Inicializou o baralho sem erros
*	BAR_CondRetNaipeNaoExiste - Não existem essas quantidades de naipes
*
***********************************************************************/
BAR_tpCondRet BAR_inicializarBaralho(BAR_tpBaralho pBaralho, int numNaipes);

/***********************************************************************
*
*  $FC Função: BAR Embaralhar Baralho
*
*  $ED Descrição da função
*     Embaralha as cartas do baralho.
*
*  $EP Parâmetros
*	pBaralho - Endereço de um ponteiro com o baralho a ser embaralhado.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Embaralhou o baralho sem erros.
*	BAR_CondRetFaltouMemoria - Faltou memória na criação da pilha a ser usada no embaralhamento.
*	BAR_CondRetBaralhoVazio - O baralho está vazio.
*
***********************************************************************/
BAR_tpCondRet BAR_embaralharBaralho(BAR_tpBaralho pBaralho);

/***********************************************************************
*
*  $FC Função: BAR Imprime Baralho
*
*  $ED Descrição da função
*     Imprime o baralho recebido.
*
*  $EP Parâmetros
*	pBaralho - Endereço de um ponteiro com o baralho a ser exibido.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Imprimiu o baralho sem erros.
*	BAR_CondRetBaralhoNaoExiste - O baralho a ser impresso não existe.
*
***********************************************************************/
BAR_tpCondRet BAR_imprimeBaralho(BAR_tpBaralho baralho);

BAR_tpCondRet BAR_retornaTopoBaralho(BAR_tpBaralho baralho, PILHA_tpPilha *pilha);

BAR_tpCondRet BAR_popBaralho(BAR_tpBaralho bBaralho, CAR_tpCarta *cCarta);


#undef BARALHO_INICIAL_EXT



/********** Fim do módulo de definição: BAR Baralho Inicial  **********/

#else
#endif