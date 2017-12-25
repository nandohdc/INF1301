/***************************************************************************
*  $MCI M�dulo de implementa��o: TESTESQF Teste Sequ�ncias Finais
*
*  Arquivo gerado:              TESTESQF.c
*  Letras identificadoras:      TSTSQF
*
*  Projeto: Disciplinas INF 1301
*  Professor: Flavio
*  Autores: ds  - Daniel Siles
*			fh  - Fernando Homem
*			mr  - Mateus Ribeiro
*
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*	4.00 ds/fh/mr 27/04/2015 criar linguagem script simb�lica
*       3.00 ds/fh/mr 26/04/2015 uniformiza��o dos exemplos
*       2.00 ds/fh/mr 22/04/2015 unifica��o de todos os m�dulos em um s� projeto
*       1.00 ds/fh/mr 17/04/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include	"Sequ�nciasFinais.h"
#include    "Carta.h"
#include	"PilhadeCartas.h"


static const char CRIAR_SQF_CMD         [ ] = "=criarsqf"		;
static const char EDITAR_SQF_CMD	    [ ] = "=editarsqf"		;
static const char LIBERAR_SQF_CMD		[ ] = "=liberarsqf"		;
static const char RETORNA_PILHA_CMD		[ ] = "=retornapilha"	;


SQF_tpSQFinal sqFinal = NULL;
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
	
	/* Testar criarSQF */

	if (strcmp(ComandoTeste, CRIAR_SQF_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if (numLidos != 1){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = SQF_criarSQFinal(&sqFinal);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao criar a SQF");

	} /* fim ativa: Testar criarSQF */

	/* Testar retornaPilha  */

	else if (strcmp(ComandoTeste, RETORNA_PILHA_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1)){
			return TST_CondRetParm;
		} /* if */
		PILHA_criarPilha(&pPilha2);
		CondRetRecebida = SQF_retornaPilha(sqFinal, &pPilha2);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao retornar a pilha da SQF");

	} /* fim ativa: Testar retornaPilha */

	/* Testar liberarSQF  */

	else if (strcmp(ComandoTeste, LIBERAR_SQF_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1)){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = SQF_liberaSQFinal(sqFinal);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao liberar a SQF");

	} /* fim ativa: Testar liberarSQF */

	/* Testar inicializaSQF */

	else if (strcmp(ComandoTeste, EDITAR_SQF_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1)){
			return TST_CondRetParm;
		} /* if */

		PILHA_criarPilha(&pPilha);

		CAR_criarCarta(&cCarta1);
		CAR_editarCarta(cCarta1, 'V','O', 'A');
		PILHA_pushPilha(pPilha, cCarta1);
		CAR_criarCarta(&cCarta1);
		CAR_editarCarta(cCarta1, 'V','C', '2');
		PILHA_pushPilha(pPilha, cCarta1);
		CAR_criarCarta(&cCarta1);
		CAR_editarCarta(cCarta1, 'V','E', '3');
		PILHA_pushPilha(pPilha, cCarta1);

		
		
		CondRetRecebida = SQF_inicializaSQFinal(sqFinal, pPilha);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao editar a SQF!");

	} /* fim ativa: Testar inicializaSQF */
	
	return TST_CondRetNaoConhec;
} /* Fim fun��o: TESTMOR Efetuar opera��es de teste espec�ficas para mortos */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/