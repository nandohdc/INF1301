/***************************************************************************
*   $MCI Módulo de implementação: TESTESQP Teste Sequências Principais
*
*  Arquivo gerado:              TESTESQP.c
*  Letras identificadoras:      TSTSQP
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
*	4.00 ds/fh/mr 27/04/2015 criar linguagem script simbólica
*       3.00 ds/fh/mr 26/04/2015 uniformização dos exemplos
*       2.00 ds/fh/mr 22/04/2015 unificação de todos os módulos em um só projeto
*       1.00 ds/fh/mr 17/04/2015 Início do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include	"SequênciasPrincipais.h"
#include    "Carta.h"
#include	"PilhadeCartas.h"


static const char CRIAR_SQP_CMD         [ ] = "=criarsqp";
static const char LIBERAR_SQP_CMD		[ ] = "=liberarsqp";
static const char REMOVER_SQP_CMD		[ ] = "=removersqp";
static const char ADICIONAR_SQP_CMD     [ ] = "=adicionarsqp";
static const char VERIFICA_SQP_CMD      [ ] = "=verificarsqp";



SQP_tpSQPrincipal sqPrincipal;
CAR_tpCarta Carta = NULL;


TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{
	CAR_tpCondRet CondRetRecebida;
	CAR_tpCondRet CondRetEsperada;
	
	int numLidos = -1;
	int ValEsp = -1;
	int numElem = -1;
	

	
	PILHA_tpPilha pPilha;
	PILHA_tpPilha pPilha2;
	CAR_tpCarta cCarta1;
	CAR_tpCarta cCarta2;
	CAR_tpCarta cCarta3;
	CAR_tpCarta cCarta4;
	CAR_tpCarta cCarta5;
	CAR_tpCarta cCarta6;
	CAR_tpCarta cCarta7;
	CAR_tpCarta cCarta8;
	CAR_tpCarta cCarta9;
	CAR_tpCarta cCarta10;
	CAR_tpCarta cCarta11;
	CAR_tpCarta cCarta12;
	CAR_tpCarta cCarta13;
	
	PILHA_criarPilha(&pPilha);
	PILHA_criarPilha(&pPilha2);
	
	CAR_criarCarta(&cCarta1);
	CAR_editarCarta(cCarta1, 'V', 'P', 'K');
	PILHA_pushPilha(pPilha, cCarta1);

	CAR_criarCarta(&cCarta2);
	CAR_editarCarta(cCarta2, 'V', 'P', 'Q');
	PILHA_pushPilha(pPilha, cCarta2);

	CAR_criarCarta(&cCarta3);
	CAR_editarCarta(cCarta3, 'V', 'P', 'J');
	PILHA_pushPilha(pPilha, cCarta3);

	CAR_criarCarta(&cCarta4);
	CAR_editarCarta(cCarta4, 'V', 'P', '1');
	PILHA_pushPilha(pPilha, cCarta4);

	CAR_criarCarta(&cCarta5);
	CAR_editarCarta(cCarta5, 'V', 'P', '9');
	PILHA_pushPilha(pPilha, cCarta5);

	CAR_criarCarta(&cCarta6);
	CAR_editarCarta(cCarta6, 'V', 'P', '8');
	PILHA_pushPilha(pPilha, cCarta6);

	CAR_criarCarta(&cCarta7);
	CAR_editarCarta(cCarta7, 'V', 'P', '7');
	PILHA_pushPilha(pPilha, cCarta7);

	CAR_criarCarta(&cCarta8);
	CAR_editarCarta(cCarta8, 'V', 'P', '6');
	PILHA_pushPilha(pPilha, cCarta8);

	CAR_criarCarta(&cCarta9);
	CAR_editarCarta(cCarta9, 'V', 'P', '5');
	PILHA_pushPilha(pPilha, cCarta9);

	CAR_criarCarta(&cCarta10);
	CAR_editarCarta(cCarta10, 'V', 'P', '4');
	PILHA_pushPilha(pPilha, cCarta10);

	CAR_criarCarta(&cCarta11);
	CAR_editarCarta(cCarta11, 'V', 'P', '3');
	PILHA_pushPilha(pPilha, cCarta11);

	CAR_criarCarta(&cCarta12);
	CAR_editarCarta(cCarta12, 'V', 'P', '2');
	PILHA_pushPilha(pPilha, cCarta12);

	CAR_criarCarta(&cCarta13);
	CAR_editarCarta(cCarta13, 'V', 'P', 'A');
	PILHA_pushPilha(pPilha, cCarta13);
	
	/* Testar criarSQP */
	
	if (strcmp(ComandoTeste, CRIAR_SQP_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if (numLidos != 1){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = SQP_criarSequencia(&sqPrincipal);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao criar a SQP");

	} /* fim ativa: Testar criarSQP */

	/* Testar liberarSQP  */

	else if (strcmp(ComandoTeste, LIBERAR_SQP_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1)){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = SQP_liberaSequencia(sqPrincipal);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao liberar a SQP");

	} /* fim ativa: Testar liberarSQP */

	/* Testar SQP removeDaSequencia*/

	else if (strcmp(ComandoTeste, REMOVER_SQP_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1)){
			return TST_CondRetParm;
		} /* if */

		
		CondRetRecebida = SQP_removeDaSequencia(sqPrincipal, cCarta2, &pPilha2);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao remover a SQP!");

	} /* fim ativa: Testar SQP removeDaSequencia*/
	
	/*Testar SQP adicionaNaSequencia*/
	else if (strcmp(ComandoTeste, ADICIONAR_SQP_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1)){
			return TST_CondRetParm;
		} /* if */


		CondRetRecebida = SQP_adicionaNaSequencia(pPilha, sqPrincipal);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao remover a SQP!");

	} /* fim ativa: Testar SQP adicionaNaSequencia */
	return TST_CondRetNaoConhec;


} /* Fim função: TESTMOR Efetuar operações de teste específicas para mortos */

/********** Fim do módulo de implementação: Módulo de teste específico **********/