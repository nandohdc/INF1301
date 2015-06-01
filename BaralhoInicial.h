#if ! defined( BARALHO_INICIAL_ )
#define BARALHO_INICIAL_
/***************************************************************************
*  $MCI M�dulo de implementa��o: BAR Baralho Inicial
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
#include<stdlib.h>
#include"Carta.h"
#include"PilhadeCartas.h"

#if defined( BARALHO_INICIAL_OWN )
#define BARALHO_INICIAL_EXT
#else
#define BARALHO_INICIAL_EXT extern
#endif



/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um baralho de cartas */
typedef struct baralho BAR_tgBaralho;
typedef struct baralho * BAR_tpBaralho;

/*Condi��es de Retorno*/

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
*  $FC Fun��o: BAR Criar Baralho
*
*  $ED Descri��o da fun��o
*     Cria um baralho vazio
*
*  $EP Par�metros
*	pBaralho - Endere�o que receber� um ponteiro para o baralho criado.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Criou o baralho sem erros
*	BAR_CondRetFaltouMemoria - Faltou mem�ria na cria��o do baralho
*
***********************************************************************/
BAR_tpCondRet BAR_criarBaralho(BAR_tpBaralho *pBaralho);

/***********************************************************************
*
*  $FC Fun��o: BAR Liberar Baralho
*
*  $ED Descri��o da fun��o
*     Libera o espa�o de mem�ria usado pelo baralho.
*
*  $EP Par�metros
*	pBaralho - Endere�o de um ponteiro com o baralho a ser liberado.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Liberou o baralho sem erros
*
***********************************************************************/
BAR_tpCondRet BAR_liberarBaralho(BAR_tpBaralho pBaralho);

/***********************************************************************
*
*  $FC Fun��o: BAR Inicializar Baralho
*
*  $ED Descri��o da fun��o
*     Coloca as cartas no baralho.
*
*  $EP Par�metros
*	pBaralho - Endere�o de um ponteiro com o baralho a ser preenchido.
*	numNaipes - Inteiro que define a quantidade de naipes existentes no baralho a ser preenchido.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Inicializou o baralho sem erros
*	BAR_CondRetNaipeNaoExiste - N�o existem essas quantidades de naipes
*
***********************************************************************/
BAR_tpCondRet BAR_inicializarBaralho(BAR_tpBaralho pBaralho, int numNaipes);

/***********************************************************************
*
*  $FC Fun��o: BAR Embaralhar Baralho
*
*  $ED Descri��o da fun��o
*     Embaralha as cartas do baralho.
*
*  $EP Par�metros
*	pBaralho - Endere�o de um ponteiro com o baralho a ser embaralhado.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Embaralhou o baralho sem erros.
*	BAR_CondRetFaltouMemoria - Faltou mem�ria na cria��o da pilha a ser usada no embaralhamento.
*	BAR_CondRetBaralhoVazio - O baralho est� vazio.
*
***********************************************************************/
BAR_tpCondRet BAR_embaralharBaralho(BAR_tpBaralho pBaralho);

/***********************************************************************
*
*  $FC Fun��o: BAR Imprime Baralho
*
*  $ED Descri��o da fun��o
*     Imprime o baralho recebido.
*
*  $EP Par�metros
*	pBaralho - Endere�o de um ponteiro com o baralho a ser exibido.
*
*  $FV Valor retornado
*	BAR_CondRetOK - Imprimiu o baralho sem erros.
*	BAR_CondRetBaralhoNaoExiste - O baralho a ser impresso n�o existe.
*
***********************************************************************/
BAR_tpCondRet BAR_imprimeBaralho(BAR_tpBaralho baralho);

BAR_tpCondRet BAR_retornaTopoBaralho(BAR_tpBaralho baralho, PILHA_tpPilha *pilha);

BAR_tpCondRet BAR_popBaralho(BAR_tpBaralho bBaralho, CAR_tpCarta *cCarta);


#undef BARALHO_INICIAL_EXT



/********** Fim do m�dulo de defini��o: BAR Baralho Inicial  **********/

#else
#endif