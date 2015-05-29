#if ! defined( SEQUENCIASFINAIS_ )
#define SEQUENCIASFINAIS_
/***************************************************************************
*
*  $MCD Módulo de definição: SQF Sequencias Finais
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
*  $HA Histórico de evolução:
*     Versão  Autor         Data     Observações
*       3.00 ds/fh/mr 26/04/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno.
*       2.00 ds/fh/mr 22/04/2015 Eliminação de código duplicado, reestruturação
*       1.00 ds/fh/mr 17/04/2015 Início do desenvolvimento
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
	/*Pilha enviada para a função está vazia*/
} SQF_tpCondRet;

/***********************************************************************
*
*  $FC Função: SQF Criar Sequência Final
*
*  $ED Descrição da função
*     Cria uma sequência final vazia
*
*  $EP Parâmetros
*	SQFinal - Endereço que receberá um ponteiro para a sequência final vazia criada.
*
*  $FV Valor retornado
*	SQF_CondRetOK - Criou a sequência final sem erros
*	SQF_CondRetFaltouMemoria - Faltou memória na criação da sequência final
*
***********************************************************************/

SQF_tpCondRet SQF_criarSQFinal(SQF_tpSQFinal *SQFinal);

/***********************************************************************
*
*  $FC Função: SQF Libera Sequência Final
*
*  $ED Descrição da função
*     Libera a memória utilizada pela sequência final
*
*  $EP Parâmetros
*	SQFinal - Endereço do ponteiro com a pilha a ser liberada.
*
*  $FV Valor retornado
*	SQF_CondRetOK - Liberou a sequência final sem erros
*
***********************************************************************/
SQF_tpCondRet SQF_liberaSQFinal(SQF_tpSQFinal SQFinal);

/***********************************************************************
*
*  $FC Função: SQF Inicializa Sequência Final
*
*  $ED Descrição da função
*     Adiciona uma pilha completa de 13 cartas em uma sequência final vazia criada.
*
*  $EP Parâmetros
*	SQFinal - Endereço do ponteiro com a sequência final que receberá uma pilha completa.
*	pilhaCompleta - Endereço do ponteiro contendo a pilha completa a ser adicionada a sequências finais.
*
*  $FV Valor retornado
*	SQF_CondRetOK - Sequência final adicionada com sucesso
*	SQF_CondRetPilhaVazia - Sequência final não existe.
*
***********************************************************************/
SQF_tpCondRet SQF_inicializaSQFinal(SQF_tpSQFinal SQFinal, PILHA_tpPilha sqFinal);
SQF_tpSQFinal SQF_retornaPilha(SQF_tpSQFinal sqf, PILHA_tpPilha * pilha);
#undef SEQUENCIASFINAIS_EXT

/********** Fim do módulo de definição: SQF Sequencias Finais  **********/

#else
#endif