/***************************************************************************
*   $MCI Módulo de implementação: TESTEPILHA Teste Pilha
*
*  Arquivo gerado:              TESTEPILHA.c
*  Letras identificadoras:      TSTPILHA
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


#include    "LerParm.h"

#include    "Carta.h"
#include	"PilhadeCartas.h"

#ifdef _DEBUG
#include "GENERICO.H"
#include "cespdin.h"
#include "CONTA.H"
#include "IdTiposEspaco.def"
#endif

#pragma pack (1)


#define CRIAR_PILHA_CMD         "=criarpilha"
#define LIBERA_PILHA_CMD        "=liberapilha"
#define PUSH_PILHA_CMD          "=pushpilha"
#define POP_PILHA_CMD           "=poppilha"
#define VERIFICA_PILHA_CMD		"=verificapilha"
#define IMPRIME_PILHA_CMD		"=imprimepilha"
#define RETORNA_NUM_ELEM_CMD	"=retornanumelem"

/* os comandos a seguir somente operam em modo _DEBUG */
#ifdef _DEBUG

const char VER_TOPO_CMD[] = "=verificarcabeca";
const char VER_PILHA_CMD[] = "=verificarpilha";
const char VER_MEMORIA_CMD[] = "=verificarmemoria";
const char DETURPAR_CMD[] = "=deturpar";

#endif

PILHA_tpPilha nPilhas[10];


TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{
	PILHA_tpCondRet CondRetRecebida;
	PILHA_tpCondRet CondRetEsperada;

	CAR_tpCarta CartaDada;
	CAR_tpCarta CartaObtida;

	int acao;
	int nElem;
	int NumLidos = -1;
	int PosicaoPilha = -1;
	int numeroPilha = -1;

	char FaceEsperada = 'V';
	char FaceObtida = 'E';
	char FaceDada;

	char NaipeEsperado = 'A';
	char NaipeObtido = 'E';
	char NaipeDado = 'O';

	char PosicaoEsperada = '1';
	char PosicaoObtida = '2';
	char PosicaoDada = '4';
	
	int numAlocAnt = CED_ObterNumeroEspacosAlocados();

	/* Testar PILHA criarPilha */

	if (strcmp(ComandoTeste, CRIAR_PILHA_CMD) == 0)
	{

		NumLidos = LER_LerParametros("ii", &numeroPilha, &CondRetEsperada);

		if (NumLidos != 2 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = PILHA_criarPilha(&nPilhas[numeroPilha]);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao criar a Pilha.");

	} /* fim ativa: Testar PILHA criarPilha */

	/* Testar PILHA liberaPilha */

	else if (strcmp(ComandoTeste, LIBERA_PILHA_CMD) == 0)
	{

		NumLidos = LER_LerParametros("ii", &numeroPilha, &CondRetEsperada);

		if (NumLidos != 2 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = PILHA_liberaPilha(nPilhas[numeroPilha]);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao destruir a Pilha");

	} /* fim ativa: Testar PILHA liberaPilha */

	/* Testar PILHA num elem */
	else if (strcmp(ComandoTeste, RETORNA_NUM_ELEM_CMD) == 0)
	{
		NumLidos = LER_LerParametros("ii", &numeroPilha, &CondRetEsperada);
		if (NumLidos != 2 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = PILHA_retornaNumElem(nPilhas[numeroPilha], &nElem);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao saber a quantidade de cartas da Pilha");
	}

	/* Testar PILHA pushPilha */

	else if (strcmp(ComandoTeste, PUSH_PILHA_CMD) == 0)
	{
		char naipe;
		char posicao;
		char face;

		NumLidos = LER_LerParametros("iccci", &numeroPilha, &FaceDada, &NaipeDado, &PosicaoDada, &CondRetEsperada);

		if (NumLidos != 5 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */
		CAR_criarCarta(&CartaDada);
		CAR_editarCarta(CartaDada, FaceDada, NaipeDado, PosicaoDada);

		CondRetRecebida = PILHA_pushPilha(nPilhas[numeroPilha], CartaDada);


		//(CAR_tpCarta)LIS_ObterValor(nPilhas[numeroPilha], &CartaDada);
		CAR_retornaFace(CartaDada, &face);
		CAR_retornaNaipe(CartaDada, &naipe);
		CAR_retornaPosicao(CartaDada, &posicao);
		printf("Carta Push: %c %c %c", face, naipe, posicao);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao push a Pilha.");

	} /* fim ativa: Testar PILHA pushPilha  */

	/* Testar PILHA popPilha */

	else if (strcmp(ComandoTeste, POP_PILHA_CMD) == 0)
	{

		NumLidos = LER_LerParametros("ii", &numeroPilha, &CondRetEsperada);

		if (NumLidos != 2 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = PILHA_popPilha(nPilhas[numeroPilha], &CartaObtida);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao pop a pilha.");


	} /* fim ativa: Testar PILHA popPilha */

	/* Testar PILHA verificaPilhaVazia */
	else if (strcmp(ComandoTeste, VERIFICA_PILHA_CMD) == 0)
	{

		NumLidos = LER_LerParametros("ii", &numeroPilha, &CondRetEsperada);

		if (NumLidos != 2 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = PILHA_verificaPilhaVazia(nPilhas[numeroPilha]);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao verificar a Pilha");

	} /* fim ativa: Testar PILHA verificaPilhaVazia */
	/* Testar PILHA imprimePilha */
	else if (strcmp(ComandoTeste, IMPRIME_PILHA_CMD) == 0)
	{

		NumLidos = LER_LerParametros("ii", &numeroPilha, &CondRetEsperada);

		if (NumLidos != 2 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = PILHA_imprimePilha(nPilhas[numeroPilha]);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao imprimir a Pilha");

	} /* fim ativa: Testar PILHA imprimePilha */

#ifdef _DEBUG

	else if (strcmp(ComandoTeste, DETURPAR_CMD) == 0)
	{

		NumLidos = LER_LerParametros("iii", &numeroPilha, &acao, &CondRetEsperada);

		if (NumLidos != 3 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		if (acao == 1){
			numAlocAnt = CED_ObterNumeroEspacosAlocados();
		}

		CondRetRecebida = PILHA_deturpaPilha(nPilhas[numeroPilha], acao, &numAlocAnt);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao Deturpar a Pilha");

	} /* fim ativa: Testar PILHA DeturpaPilha */

#endif

#ifdef _DEBUG

	else if (strcmp(ComandoTeste, VER_PILHA_CMD) == 0)
	{

		NumLidos = LER_LerParametros("ii", &numeroPilha, &CondRetEsperada);

		if (NumLidos != 2 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = PILHA_verificaNo(nPilhas[numeroPilha], numAlocAnt);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao Verificar a Pilha");

	} /* fim ativa: Testar PILHA VerificaPilha */

#endif

	return TST_CondRetNaoConhec;

} /* Fim função: TESTPILHA Efetuar operações de teste específicas para cartas */

/********** Fim do módulo de implementação: Módulo de teste específico **********/