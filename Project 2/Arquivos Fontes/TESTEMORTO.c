/***************************************************************************
*   $MCI Módulo de implementação: TESTEMORTO Teste Morto
*
*  Arquivo gerado:              TESTEMORTO.c
*  Letras identificadoras:      TSTMOR
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

#include	"Morto.h"
#include    "Carta.h"
#include	"PilhadeCartas.h"


static const char CRIAR_MORTO_CMD         [ ] = "=criarmorto"     ;
static const char LIBERA_MORTO_CMD	      [ ] = "=liberarmorto"  ;
static const char POP_MORTO_CMD			  [ ] = "=popmorto"    ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

MOR_tpMorto Morto = NULL;
CAR_tpCarta Carta = NULL;

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{
	CAR_tpCondRet CondRetRecebida;
	CAR_tpCondRet CondRetEsperada;
	
	int numLidos = -1;
	int ValEsp = -1;
	int numElem = -1;

	PILHA_tpPilha pPilha;
	CAR_tpCarta CartaAux1;
	
	/* Testar criarMorto */

	if (strcmp(ComandoTeste, CRIAR_MORTO_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if (numLidos != 1){
			return TST_CondRetParm;
		} /* if */

		PILHA_criarPilha(&pPilha);

		CAR_criarCarta(&CartaAux1);
		CAR_editarCarta(CartaAux1, 'E', 'E', '9');
		PILHA_pushPilha(pPilha, CartaAux1);
		CAR_criarCarta(&CartaAux1);
		CAR_editarCarta(CartaAux1, 'E', 'E', '8');
		PILHA_pushPilha(pPilha, CartaAux1);
		CAR_criarCarta(&CartaAux1);
		CAR_editarCarta(CartaAux1, 'E', 'E', '7');
		PILHA_pushPilha(pPilha, CartaAux1);


		CondRetRecebida = MOR_criarMorto(&Morto, pPilha);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao criar o morto.");

	} /* fim ativa: Testar criarMorto */

	/* Testar liberaMorto  */

	else if (strcmp(ComandoTeste, LIBERA_MORTO_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = MOR_liberaMorto(Morto);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao liberar o morto");

	} /* fim ativa: Testar liberaMorto */

	/* Testar popMorto */

	else if (strcmp(ComandoTeste, POP_MORTO_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */
		
		CondRetRecebida = MOR_popMorto(Morto, &CartaAux1);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao tirar uma carta do morto! ô morto meca suas palavra");

	} /* fim ativa: Testar popMorto */
	
	return TST_CondRetNaoConhec;
} /* Fim função: TESTMOR Efetuar operações de teste específicas para mortos */

/********** Fim do módulo de implementação: Módulo de teste específico **********/