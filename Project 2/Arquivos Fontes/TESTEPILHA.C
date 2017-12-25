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

#include    "Generico.h"
#include    "LerParm.h"

#include    "Carta.h"
#include	"PilhadeCartas.h"


#define CRIAR_PILHA_CMD         "=criarpilha"
#define LIBERA_PILHA_CMD        "=liberapilha"
#define PUSH_PILHA_CMD          "=pushpilha"
#define POP_PILHA_CMD           "=poppilha"
#define VERIFICA_PILHA_CMD		"=verificapilha"
#define IMPRIME_PILHA_CMD		"=imprimepilha"



PILHA_tpPilha nPilhas[10];


TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{
	PILHA_tpCondRet CondRetRecebida;
	PILHA_tpCondRet CondRetEsperada;

	CAR_tpCarta CartaDada;
	CAR_tpCarta CartaObtida;

	TST_tpCondRet auxiliar;

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
		/*
		if (auxiliar != TST_CondRetOK){
		return auxiliar;
		} /* if */
		/*
		if (CondRetRecebida != PILHA_CondRetOK)
		{
		return CondRetRecebida;
		} /* if */
		/*
		CAR_retornaNaipe(CartaObtida, &NaipeObtido);
		auxiliar = TST_CompararInt(NaipeEsperado, NaipeObtido, "Carta retornada é inválida.");

		if (auxiliar != TST_CondRetOK)
		{
		return auxiliar;
		} /* if */
		/*
		if (CondRetRecebida != PILHA_CondRetOK)
		{
		return CondRetRecebida;
		} /* if */
		/*
		CAR_retornaPosicao(CartaObtida, &PosicaoObtida);
		auxiliar = TST_CompararInt(PosicaoEsperada, PosicaoObtida,"Carta retornada é inválida.");
		/*
		if (auxiliar != TST_CondRetOK)
		{
		return auxiliar;
		} /* if */
		/*
		CAR_retornaFace(CartaObtida, &FaceObtida);
		return TST_CompararInt(FaceEsperada, FaceObtida, "Carta retornada é inválida.");
		*/

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
	} /* Testar PILHA imprimePilha */
	else if (strcmp(ComandoTeste, IMPRIME_PILHA_CMD) == 0)
	{

		NumLidos = LER_LerParametros("ii", &numeroPilha, &CondRetEsperada);

		if (NumLidos != 2 || numeroPilha >= 10 || numeroPilha < 0){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = PILHA_imprimePilha(nPilhas[numeroPilha]);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao imprimir a Pilha");

	} /* fim ativa: Testar PILHA imprimePilha */
	
	return TST_CondRetNaoConhec;

} /* Fim função: TESTPILHA Efetuar operações de teste específicas para cartas */

/********** Fim do módulo de implementação: Módulo de teste específico **********/