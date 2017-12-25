/***************************************************************************
*   $MCI Módulo de implementação: TESTECARTA Teste Carta
*
*  Arquivo gerado:              TESTECARTA.c
*  Letras identificadoras:      TSTCARTA
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


static const char CRIAR_CARTA_CMD         [ ] = "=criarcarta"     ;
static const char DESTRUIR_CARTA_CMD      [ ] = "=destruircarta"  ;
static const char EDITAR_CARTA_CMD        [ ] = "=editarcarta"    ;
static const char RETORNA_POSICAO_CMD     [ ] = "=retornaposicao" ;
static const char RETORNA_NAIPE_CMD       [ ] = "=retornanaipe"   ;
static const char RETORNA_FACE_CMD        [ ] = "=retornaface"    ;
static const char IMPRIME_CARTA_CMD       [ ] = "=imprimecarta"   ;


CAR_tpCarta Carta = NULL;


TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{
	CAR_tpCondRet CondRetRecebida;
	CAR_tpCondRet CondRetEsperada;
	
	int numLidos = -1;
	int ValEsp = -1;
	int numElem = -1;
	
	char FaceRecebida = 'M';
	char FaceEsperada = 'D';

	char NaipeRecebido = '&';
	char NaipeEsperado = '#';
	
	char PosicaoRecebida = '1';
	char PosicaoEsperada = '2';
	
	/* Testar criarCarta */

	if (strcmp(ComandoTeste, CRIAR_CARTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if (numLidos != 1){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = CAR_criarCarta(&Carta);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao criar a carta.");

	} /* fim ativa: Testar criarCarta */

	/* Testar destruirCarta  */

	else if (strcmp(ComandoTeste, DESTRUIR_CARTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = CAR_destruirCarta(Carta);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao destruir a Carta");

	} /* fim ativa: Testar destruirCarta */

	/* Testar editarCarta */

	else if (strcmp(ComandoTeste, EDITAR_CARTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("ccci", &FaceRecebida, &NaipeRecebido, &PosicaoRecebida, &CondRetEsperada);

		if ((numLidos != 4))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = CAR_editarCarta(Carta, FaceRecebida, NaipeRecebido, PosicaoRecebida);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao editar a Carta");

	} /* fim ativa: Testar editarCarta */

	/* Testar retornaPosicao */

	else if (strcmp(ComandoTeste, RETORNA_POSICAO_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = CAR_retornaPosicao(Carta, &PosicaoEsperada);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao retornar Posicao da Carta");

	} /* fim ativa: Testar retornaPosicao */

	/* Testar retornaNaipe */

	else if (strcmp(ComandoTeste, RETORNA_NAIPE_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = CAR_retornaNaipe(Carta, &NaipeEsperado);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao retornar Naipe da Carta.");

	} /* fim ativa: Testar retornaNaipe */

	/* Testar retornaFace */

	else if (strcmp(ComandoTeste, RETORNA_FACE_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = CAR_retornaFace(Carta, &FaceEsperada);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao retornar Face da Carta.");

	} /* fim ativa: Testar retornaFace */

	/* Testar imprimeCarta  */

	else if (strcmp(ComandoTeste, IMPRIME_CARTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = CAR_imprimeCarta(Carta);

		return TST_CompararInt(CondRetEsperada,CondRetRecebida,"Erro ao imprimir a carta.");

	} /* fim ativa: Testar imprimeCarta  */

	return TST_CondRetNaoConhec;

} /* Fim função: TESTCAR Efetuar operações de teste específicas para cartas */

/********** Fim do módulo de implementação: Módulo de teste específico **********/