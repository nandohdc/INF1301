#if ! defined( SEQUENCIASFINAIS_ )
#define SEQUENCIASFINAIS_
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
*       3.00 ds/fh/mr 26/04/2015 Uniformiza��o da interface das fun��es e
*                                de todas as condi��es de retorno.
*       2.00 ds/fh/mr 22/04/2015 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00 ds/fh/mr 17/04/2015 In�cio do desenvolvimento
*
***************************************************************************/
#include "PilhadeCartas.h"
#include"Carta.h"

#if defined( SEQUENCIASFINAIS_OWN )
#define SEQUENCIASFINAIS_EXT
#else
#define SEQUENCIASFINAIS_EXT extern
#endif

typedef struct sequenciaFinal SQF_tgSQFinal;
typedef SQF_tgSQFinal * SQF_tpSQFinal;

typedef enum {
	SQF_CondRetOK = 0,
	/*Tudo certo*/

	SQF_CondRetFaltouMemoria = 1,
	/*Excedeu limite de memoria*/

	SQF_CondRetPilhaVazia = 2
	/*Pilha enviada para a fun��o est� vazia*/
} SQF_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: SQF Criar Sequ�ncia Final
*
*  $ED Descri��o da fun��o
*     Cria uma sequ�ncia final vazia
*
*  $EP Par�metros
*	SQFinal - Endere�o que receber� um ponteiro para a sequ�ncia final vazia criada.
*
*  $FV Valor retornado
*	SQF_CondRetOK - Criou a sequ�ncia final sem erros
*	SQF_CondRetFaltouMemoria - Faltou mem�ria na cria��o da sequ�ncia final
*
***********************************************************************/

SQF_tpCondRet SQF_criarSQFinal(SQF_tpSQFinal *SQFinal);

/***********************************************************************
*
*  $FC Fun��o: SQF Libera Sequ�ncia Final
*
*  $ED Descri��o da fun��o
*     Libera a mem�ria utilizada pela sequ�ncia final
*
*  $EP Par�metros
*	SQFinal - Endere�o do ponteiro com a pilha a ser liberada.
*
*  $FV Valor retornado
*	SQF_CondRetOK - Liberou a sequ�ncia final sem erros
*
***********************************************************************/
SQF_tpCondRet SQF_liberaSQFinal(SQF_tpSQFinal SQFinal);

/***********************************************************************
*
*  $FC Fun��o: SQF Inicializa Sequ�ncia Final
*
*  $ED Descri��o da fun��o
*     Adiciona uma pilha completa de 13 cartas em uma sequ�ncia final vazia criada.
*
*  $EP Par�metros
*	SQFinal - Endere�o do ponteiro com a sequ�ncia final que receber� uma pilha completa.
*	pilhaCompleta - Endere�o do ponteiro contendo a pilha completa a ser adicionada a sequ�ncias finais.
*
*  $FV Valor retornado
*	SQF_CondRetOK - Sequ�ncia final adicionada com sucesso
*	SQF_CondRetPilhaVazia - Sequ�ncia final n�o existe.
*
***********************************************************************/
SQF_tpCondRet SQF_inicializaSQFinal(SQF_tpSQFinal SQFinal, PILHA_tpPilha sqFinal);
SQF_tpSQFinal SQF_retornaPilha(SQF_tpSQFinal sqf, PILHA_tpPilha * pilha);
#undef SEQUENCIASFINAIS_EXT

/********** Fim do m�dulo de defini��o: SQF Sequencias Finais  **********/

#else
#endif