#if ! defined( ESTRUTURAPRINCIPAL_ )
#define ESTRUTURAPRINCIPAL_ /*NAO APAGAR*/

/***************************************************************************
*
*  $MCD Módulo de definição: ESP Estrutura Principal
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
	/*Face inserida é invalida*/

	ESP_CondRetFaltouMemoria = 5
	/*Excedeu limite de memoria*/

} ESP_tpCondRet;

//ESP_tpCondRet criaEstruturaPrincipal(ESP_tpEstruturalPrincipal *eESP);
//ESP_tpCondRet escolheDificuldade(int *dificuldade);
//ESP_tpCondRet distribuiMortoJogo(MOR_tpMorto mMorto);

//ESP_tpCondRet ESP_realizaJogada(LIS_tppLista ListaPrincipal, int origem, int destino, CAR_tpCarta carta);

#undef ESTRUTURAPRINCIPAL_EXT /*NAO APAGAR*/

/********** Fim do módulo de definição: CAR Carta **********/

#else/*NAO APAGAR*/
#endif/*NAO APAGAR*/