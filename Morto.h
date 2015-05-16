#if ! defined( MORTO_ )
#define MORTO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: MOR Morto
*
*  Arquivo gerado:              Morto.h
*  Letras identificadoras:      MOR
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
*       3.00 ds/fh/mr 26/04/2015 Uniformiza��o da interface das fun��es e
*                                de todas as condi��es de retorno.
*       2.00 ds/fh/mr 22/04/2015 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00 ds/fh/mr 17/04/2015 In�cio do desenvolvimento
*
***************************************************************************/
#include"PilhadeCartas.h"
#include"Carta.h"

#if defined( MORTO_OWN )
#define MORTO_EXT
#else
#define MORTO_EXT extern
#endif

typedef struct morto MOR_tgMorto;
typedef MOR_tgMorto * MOR_tpMorto;

typedef enum {
	MOR_CondRetOK = 0,
	/*Tudo certo*/

	MOR_CondRetNaoOK = 1,
	/*A carta nao existe*/

	MOR_CondRetMortoVazio = 2,
	/*O morto est� vazio*/

	MOR_CondRetFaltouMemoria = 3
	/*O morto n�o existe*/
} MOR_tpCondRet;

#undef MORTO_EXT

/***********************************************************************
*
*  $FC Fun��o: MOR Criar Morto
*
*  $ED Descri��o da fun��o
*     Cria um morto vazio.
*
*  $EP Par�metros
*	mMorto - Endere�o que receber� um ponteiro para o monte de morto criado.
*
*  $FV Valor retornado
*	CAR_CondRetOK - Criou o morto sem erros
*
***********************************************************************/
MOR_tpCondRet MOR_criarMorto(MOR_tpMorto *mMorto, PILHA_tpPilha pPilha);

/***********************************************************************
*
*  $FC Fun��o: MOR Libera Morto
*
*  $ED Descri��o da fun��o
*     Libera o espa�o de mem�ria usado pelo morto.
*
*  $EP Par�metros
*	mMorto - Endere�o de um ponteiro de um morto a ser liberado.
*
*  $FV Valor retornado
*	CAR_CondRetOK - Morto liberado sem erros
*
***********************************************************************/
MOR_tpCondRet MOR_liberaMorto(MOR_tpMorto mMorto);

/***********************************************************************
*
*  $FC Fun��o: MOR Pop Morto
*
*  $ED Descri��o da fun��o
*     Distribui o morto nas 10 sequ�ncias principais de acordo com a regra do jogo.
*
*  $EP Par�metros
*	mMorto - Endere�o de um ponteiro de um morto a ser distribuido.
*
*  $FV Valor retornado
*	CAR_CondRetOK - Morto distribuido sem erros.
*	MOR_CondRetMortoVazio - O morto est� vazio.
*
***********************************************************************/
MOR_tpCondRet MOR_popMorto(MOR_tpMorto mMorto, CAR_tpCarta *cartaPop);
/********** Fim do m�dulo de defini��o: MOR Morto  **********/

#else
#endif