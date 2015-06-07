#if ! defined( MORTO_ )
#define MORTO_
/***************************************************************************
*  $MCI Módulo de implementação: MOR Morto
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
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*		5.00 ds/fh/mr 06/06/2015 Adição da função retorna Morto
*		4.00 ds/fh/mr 27/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte II.
*       3.00 ds/fh/mr 26/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte I.
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
*	MOR_CondRetOK - Criou o morto sem erros.
*	MOR_CondRetFaltouMemoria - Faltou memória na criação do morto.
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
*	MOR_CondRetOK - Morto liberado sem erros.
*
***********************************************************************/
MOR_tpCondRet MOR_liberaMorto(MOR_tpMorto mMorto);

/***********************************************************************
*
*  $FC Função: MOR Pop Morto
*
*  $ED Descrição da função
*     Devolve por referência a carta do topo da pilha do morto.
*
*  $EP Parâmetros
*	mMorto - Endereço de um ponteiro de um morto a ser distribuido.
*	cartaPop - Endereço com um ponteiro que receberá a carta do topo da pilha do morto.
*
*  $FV Valor retornado
*	MOR_CondRetOK - Carta devolvida sem erros.
*	MOR_CondRetMortoVazio - O morto está vazio.
*	MOR_CondRetNaoOK - A carta não foi retirada corretamente da pilha do morto.
*
***********************************************************************/
MOR_tpCondRet MOR_popMorto(MOR_tpMorto mMorto, CAR_tpCarta *cartaPop);

/***********************************************************************
*
*  $FC Função: MOR Retorna Morto
*
*  $ED Descrição da função
*     Devolve a pilha do morto por referência.
*
*  $EP Parâmetros
*	mMorto - Endereço de um ponteiro de um morto que terá a pilha devolvida.
*	pilha - Endereço com um ponteiro que receberá a pilha do morto.
*
*  $FV Valor retornado
*	MOR_CondRetOK - Morto distribuido sem erros.
*	MOR_CondRetMortoVazio - O morto está vazio.
*
***********************************************************************/
MOR_tpCondRet MOR_retornaMorto(MOR_tpMorto mMorto, PILHA_tpPilha * pilha);
/********** Fim do módulo de definição: MOR Morto  **********/

#else
#endif