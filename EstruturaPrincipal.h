#if ! defined( ESTRUTURAPRINCIPAL_ )
#define ESTRUTURAPRINCIPAL_ /*NAO APAGAR*/

/***************************************************************************
*
*  $MCD M�dulo de defini��o: ESP Estrutura Principal
*
*  Arquivo gerado:              EstruturaPrincipal.h
*  Letras identificadoras:      ESP
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

#if defined( ESTRUTURAPRINCIPAL_OWN )/*NAO APAGAR*/
#define ESTRUTURAPRINCIPAL_EXT
#else/*NAO APAGAR*/
#define ESTRUTURAPRINCIPAL_EXT extern
#endif/*NAO APAGAR*/

typedef struct estruturaprincipal ESP_tgEstruturalPrincipal;
typedef ESP_tgEstruturalPrincipal * ESP_tpEstruturalPrincipal;

typedef enum{

	ESP_CondRetOK = 0,
	/*Tudo certo*/

	ESP_CondRetEstruturaPrincipalNaoExiste = 1,
	/*A carta nao existe*/

	ESP_CondRetNivelErrado = 2,
	/*O naipe nao existe || invalido*/

	ESP_CondRetMortoVazio = 3,
	/*A numeracao nao existe || invalida*/

	ESP_CondRetSQPVazia = 4,
	/*Face inserida � invalida*/

	ESP_CondRetFaltouMemoria = 5
	/*Excedeu limite de memoria*/

} ESP_tpCondRet;

//ESP_tpCondRet criaEstruturaPrincipal(ESP_tpEstruturalPrincipal *eESP);
//ESP_tpCondRet escolheDificuldade(int *dificuldade);
//ESP_tpCondRet distribuiMortoJogo(MOR_tpMorto mMorto);

//ESP_tpCondRet ESP_realizaJogada(LIS_tppLista ListaPrincipal, int origem, int destino, CAR_tpCarta carta);

#undef ESTRUTURAPRINCIPAL_EXT /*NAO APAGAR*/

/********** Fim do m�dulo de defini��o: CAR Carta **********/

#else/*NAO APAGAR*/
#endif/*NAO APAGAR*/