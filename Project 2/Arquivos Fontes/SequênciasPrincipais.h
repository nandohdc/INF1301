#if ! defined( SEQUENCIASPRINCIPAIS_ )
#define SEQUENCIASPRINCIPAIS_ /*NAO APAGAR -> Copiado do Arvore.H*/

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo Carta
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor         Data     Observa��es
*       3.00 ds/fh/mr 26/04/2015 Uniformiza��o da interface das fun��es e
*                                de todas as condi��es de retorno.
*       2.00 ds/fh/mr 22/04/2015 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00 ds/fh/mr 17/04/2015 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
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
*  $FC Fun��o: SQP Criar Sequencia
*
*  $ED Descri��o da fun��o
*     Cria uma das sequ�ncias principais vazia.
*
*  $EP Par�metros
*	sqPrincipal - Endere�o que receber� um ponteiro para a sequ�ncia criada.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Sequencia principal criada sem erros
*
***********************************************************************/
SQP_tpCondRet SQP_criarSequencia(SQP_tpSQPrincipal *SQPrincipal);

/***********************************************************************
*
*  $FC Fun��o: SQP Liberar Sequencia
*
*  $ED Descri��o da fun��o
*     Libera o espa�o de mem�ria usado pela sequ�ncia principal.
*
*  $EP Par�metros
*	sqPrincipal - Endere�o de um ponteiro com a sequ�ncia a ser liberada.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Sequencia principal liberada sem erros
*
***********************************************************************/
SQP_tpCondRet SQP_liberaSequencia(SQP_tpSQPrincipal sqPrincipal);

/***********************************************************************
*
*  $FC Fun��o: SQP Remover da Sequencia
*
*  $ED Descri��o da fun��o
*     Remove uma pilha de cartas da sequ�ncia para fazer um movimento de jogo.
*
*  $EP Par�metros
*	sqTira - Endere�o de um ponteiro com a sequ�ncia da qual ser� retirada a pilha de cartas.
*	cCarta - Endere�o de um ponteiro com a carta a ser procurada na sequ�ncia.
*	pPilhaGuarda - Endere�o com um porteiro para a pilha de cartas retirada.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Pilha removida da sequ�ncia sem erros
*	SQP_CondRetSequenciaVazia - Sequ�ncia recebida est� vazia
*	SQP_CondRetNaoOK - Carta procurada n�o est� na sequ�ncia
*	SQP_CondRetFaceEscondida - A carta procurada est� com a face escondida
*	SQP_CondRetPosicaoErrada - A carta n�o est� em uma sequ�ncia m�vel devido � posi��o (valor) da carta.
*	SQP_CondRetNaipeDiferente - A carta n�o est� em uma sequ�ncia m�vel devido ao naipe da carta.
*
***********************************************************************/
SQP_tpCondRet SQP_removeDaSequencia(SQP_tpSQPrincipal sqTira, CAR_tpCarta cCarta, PILHA_tpPilha *pPilhaGuarda);

/***********************************************************************
*
*  $FC Fun��o: SQP Adicionar na Sequencia
*
*  $ED Descri��o da fun��o
*     Adiciona uma pilha de cartas na sequ�ncia para fazer um movimento de jogo.
*
*  $EP Par�metros
*	sqRecebe - Endere�o com a sequ�ncia na qual ser� adicionada a pilha de cartas.
*	pPilhaTira - Endere�o com a pilha de cartas a ser adicionada na sequ�ncia.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Pilha removida da sequ�ncia sem erros
*	SQP_CondRetFaceEscondida - A sequ�ncia em que se deseja inserir a pilha est� com a face escondida.
*	SQP_CondRetPosicaoErrada - A pilha de cartas n�o se encaixa devido � posi��o (valor) da carta.
*	SQP_CondRetNaipeDiferente - A pilha de cartas n�o possui o mesmo naipe da carta final da sequ�ncia.
*
***********************************************************************/
SQP_tpCondRet SQP_adicionaNaSequencia(PILHA_tpPilha pPilhaTira, SQP_tpSQPrincipal sqRecebe);

/***********************************************************************
*
*  $FC Fun��o: SQP Verifica Sequencia Completa
*
*  $ED Descri��o da fun��o
*     Verifica se uma sequ�ncia principal � uma sequ�ncia de �s a Rei de um mesmo naipe para ser uma sequencia final.
*
*  $EP Par�metros
*	SQP - Sequ�ncia principal a ser verificada.
*
*  $FV Valor retornado
*	SQP_CondRetOK - Sequ�ncia verificada est� completa.
*	SQP_CondRetSequenciaVazia - Sequ�ncia recebida est� vazia.
*	SQP_CondRetFaceEscondida - A sequ�ncia verificada � interrompida por uma carta 'escondida'.
*	SQP_CondRetPosicaoErrada - A carta do topo da pilha na sequ�ncia verificada n�o � �s.
*	SQP_CondRetNaipeDiferente - A sequ�ncia verificada n�o obedece a regra dos naipes.
*
***********************************************************************/
SQP_tpCondRet SQP_verificaSequenciaCompleta(SQP_tpSQPrincipal SQP);


#undef SEQUENCIASPRINCIPAIS_EXT

/********** Fim do m�dulo de defini��o: M�dulo SQP Sequencias Principais **********/

#else
#endif