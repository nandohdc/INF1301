#if ! defined( MORTO_ )
#define MORTO_
/***************************************************************************
*
*  $MCD Módulo de definição: MOR Morto
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
*  $HA Histórico de evolução:
*     Versão  Autor         Data     Observações
*       3.00 ds/fh/mr 26/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno.
*       2.00 ds/fh/mr 22/04/2015 Eliminação de código duplicado, reestruturação
*       1.00 ds/fh/mr 17/04/2015 Início do desenvolvimento
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
	/*O morto está vazio*/

	MOR_CondRetFaltouMemoria = 3
	/*O morto não existe*/
} MOR_tpCondRet;

#undef MORTO_EXT

/***********************************************************************
*
*  $FC Função: MOR Criar Morto
*
*  $ED Descrição da função
*     Cria um morto vazio.
*
*  $EP Parâmetros
*	mMorto - Endereço que receberá um ponteiro para o monte de morto criado.
*
*  $FV Valor retornado
*	CAR_CondRetOK - Criou o morto sem erros
*
***********************************************************************/
MOR_tpCondRet MOR_criarMorto(MOR_tpMorto *mMorto, PILHA_tpPilha pPilha);

/***********************************************************************
*
*  $FC Função: MOR Libera Morto
*
*  $ED Descrição da função
*     Libera o espaço de memória usado pelo morto.
*
*  $EP Parâmetros
*	mMorto - Endereço de um ponteiro de um morto a ser liberado.
*
*  $FV Valor retornado
*	CAR_CondRetOK - Morto liberado sem erros
*
***********************************************************************/
MOR_tpCondRet MOR_liberaMorto(MOR_tpMorto mMorto);

/***********************************************************************
*
*  $FC Função: MOR Pop Morto
*
*  $ED Descrição da função
*     Distribui o morto nas 10 sequências principais de acordo com a regra do jogo.
*
*  $EP Parâmetros
*	mMorto - Endereço de um ponteiro de um morto a ser distribuido.
*
*  $FV Valor retornado
*	CAR_CondRetOK - Morto distribuido sem erros.
*	MOR_CondRetMortoVazio - O morto está vazio.
*
***********************************************************************/
MOR_tpCondRet MOR_popMorto(MOR_tpMorto mMorto, CAR_tpCarta *cartaPop);
/********** Fim do módulo de definição: MOR Morto  **********/

#else
#endif