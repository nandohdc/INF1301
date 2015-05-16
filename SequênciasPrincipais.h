#if ! defined( SEQUENCIASPRINCIPAIS_ )
#define SEQUENCIASPRINCIPAIS_ /*NAO APAGAR -> Copiado do Arvore.H*/

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Carta
*
*  Arquivo gerado:              SequenciasPrincipais.h
*  Letras identificadoras:      SQP
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

#if defined( SEQUENCIASPRINCIPAIS_OWN )/*NAO APAGAR -> Copiado do Arvore.H*/
#define SEQUENCIASPRINCIPAIS_EXT
#else/*NAO APAGAR -> Copiado do Arvore.H*/
#define SEQUENCIASPRINCIPAIS_EXT extern
#endif/*NAO APAGAR -> Copiado do Arvore.H*/

#include"PilhadeCartas.h"
#include "Carta.h"

typedef struct sequenciasPrincipais SQP_tgSQPrincipal;
typedef struct sequenciasPrincipais * SQP_tpSQPrincipal;

typedef enum{

	SQP_CondRetOK = 0,
	/*Tudo certo*/

	SQP_CondRetNaoOK = 1,
	/*A carta nao existe*/

	SQP_CondRetFaltouMemoria = 2,
	/*Excedeu limite de memoria*/

	SQP_CondRetPosicaoErrada = 3,
	/*Posicao inserida invalida/errada*/

	SQP_CondRetFaceEscondida = 4,
	/*Retornou face escondida*/

	SQP_CondRetNaipeDiferente = 5,
	/*Retornou naipe valido porem diferente do que deveria ser inserido*/

	SQP_CondRetSequenciaVazia = 6
	/*Sequencia principal vazia*/

} SQP_tpCondRet;

/***********************************************************************
*
*  $FC Função: SQP Criar Sequencia
*
*  $ED Descrição da função
*     Cria uma das sequências principais vazia.
*
*  $EP Parâmetros
*	sqPrincipal - Endereço que receberá um ponteiro para a sequência criada.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Sequencia principal criada sem erros
*
***********************************************************************/
SQP_tpCondRet SQP_criarSequencia(SQP_tpSQPrincipal *SQPrincipal);

/***********************************************************************
*
*  $FC Função: SQP Liberar Sequencia
*
*  $ED Descrição da função
*     Libera o espaço de memória usado pela sequência principal.
*
*  $EP Parâmetros
*	sqPrincipal - Endereço de um ponteiro com a sequência a ser liberada.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Sequencia principal liberada sem erros
*
***********************************************************************/
SQP_tpCondRet SQP_liberaSequencia(SQP_tpSQPrincipal sqPrincipal);

/***********************************************************************
*
*  $FC Função: SQP Remover da Sequencia
*
*  $ED Descrição da função
*     Remove uma pilha de cartas da sequência para fazer um movimento de jogo.
*
*  $EP Parâmetros
*	sqTira - Endereço de um ponteiro com a sequência da qual será retirada a pilha de cartas.
*	cCarta - Endereço de um ponteiro com a carta a ser procurada na sequência.
*	pPilhaGuarda - Endereço com um porteiro para a pilha de cartas retirada.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Pilha removida da sequência sem erros
*	SQP_CondRetSequenciaVazia - Sequência recebida está vazia
*	SQP_CondRetNaoOK - Carta procurada não está na sequência
*	SQP_CondRetFaceEscondida - A carta procurada está com a face escondida
*	SQP_CondRetPosicaoErrada - A carta não está em uma sequência móvel devido à posição (valor) da carta.
*	SQP_CondRetNaipeDiferente - A carta não está em uma sequência móvel devido ao naipe da carta.
*
***********************************************************************/
SQP_tpCondRet SQP_removeDaSequencia(SQP_tpSQPrincipal sqTira, CAR_tpCarta cCarta, PILHA_tpPilha *pPilhaGuarda);

/***********************************************************************
*
*  $FC Função: SQP Adicionar na Sequencia
*
*  $ED Descrição da função
*     Adiciona uma pilha de cartas na sequência para fazer um movimento de jogo.
*
*  $EP Parâmetros
*	sqRecebe - Endereço com a sequência na qual será adicionada a pilha de cartas.
*	pPilhaTira - Endereço com a pilha de cartas a ser adicionada na sequência.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Pilha removida da sequência sem erros
*	SQP_CondRetFaceEscondida - A sequência em que se deseja inserir a pilha está com a face escondida.
*	SQP_CondRetPosicaoErrada - A pilha de cartas não se encaixa devido à posição (valor) da carta.
*	SQP_CondRetNaipeDiferente - A pilha de cartas não possui o mesmo naipe da carta final da sequência.
*
***********************************************************************/
SQP_tpCondRet SQP_adicionaNaSequencia(PILHA_tpPilha pPilhaTira, SQP_tpSQPrincipal sqRecebe);

/***********************************************************************
*
*  $FC Função: SQP Verifica Sequencia Completa
*
*  $ED Descrição da função
*     Verifica se uma sequência principal é uma sequência de Ás a Rei de um mesmo naipe para ser uma sequencia final.
*
*  $EP Parâmetros
*	SQP - Sequência principal a ser verificada.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Sequência verificada está completa.
*	SQP_CondRetSequenciaVazia - Sequência recebida está vazia.
*	SQP_CondRetFaceEscondida - A sequência verificada é interrompida por uma carta 'escondida'.
*	SQP_CondRetPosicaoErrada - A carta do topo da pilha na sequência verificada não é Ás.
*	SQP_CondRetNaipeDiferente - A sequência verificada não obedece a regra dos naipes.
*
***********************************************************************/
SQP_tpCondRet SQP_verificaSequenciaCompleta(SQP_tpSQPrincipal SQP);


#undef SEQUENCIASPRINCIPAIS_EXT

/********** Fim do módulo de definição: Módulo SQP Sequencias Principais **********/

#else
#endif