#if ! defined( CARTA_ )
#define CARTA_ /*NAO APAGAR*/

/***************************************************************************
*
*  $MCD Módulo de definição: CAR Carta
*
*  Arquivo gerado:              Carta.H
*  Letras identificadoras:      CAR
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

#if defined( CARTA_OWN )/*NAO APAGAR*/
#define CARTA_EXT
#else/*NAO APAGAR*/
#define CARTA_EXT extern
#endif/*NAO APAGAR*/

typedef struct carta CAR_tgCarta;
typedef CAR_tgCarta *CAR_tpCarta;

typedef enum{

	CAR_CondRetOK = 0,
	/*Tudo certo*/

	CAR_CondRetCartaNaoExiste = 1,
	/*A carta nao existe*/

	CAR_CondRetNaipeNaoExiste = 2,
	/*O naipe nao existe || invalido*/

	CAR_CondRetPosicaoNaoExiste = 3,
	/*A numeracao nao existe || invalida*/

	CAR_CondRetFaceErrada = 4,
	/*Face inserida é invalida*/

	CAR_CondRetMemoria = 5
	/*Excedeu limite de memoria*/

} CAR_tpCondRet;



/***********************************************************************
*
*  $FC Função: CAR Criar Carta
*
*  $ED Descrição da função
*     Cria uma carta de baralho vazia
*
*  $EP Parâmetros
*	pCarta - Endereço que receberá um ponteiro para a carta criada.
*
*  $FV Valor retornado
*	CAR_CondRetOK - Criou OK
*	CAR_CondRetFaltouMemoria - Faltou memória na criação da pilha
*
***********************************************************************/
CAR_tpCondRet CAR_criarCarta(CAR_tpCarta *pCarta); /*Cria uma carta(dinamicamente)*/

/***********************************************************************
*
*  $FC Função: CAR Destroi Carta
*
*  $ED Descrição da função
*     Destroi uma carta de baralho liberando seu espaço
*
*  $EP Parâmetros
*	pCarta - Endereço que receberá um ponteiro para a carta a ser destruida.
*
*  $FV Valor retornado
*	CAR_CondRetOK - Destruiu OK
*
***********************************************************************/
CAR_tpCondRet CAR_destruirCarta(CAR_tpCarta pCarta);
/***********************************************************************
*
*  $FC Função: CAR Editar Carta
*
*  $ED Descrição da função
*     Edita/Preenche uma carta de baralho
*
*  $EP Parâmetros
*	pCarta - Endereço que receberá um ponteiro para a carta a ser editada/preenchida.
*	NovaFace - char contendo a informação se a carta está Visivel ('V') ou Escondida ('E').
*	NovaNaipe - char contendo a informação do naipe da carta Espadas ('E'), Ouro ('O') , Paus ('P') , Copas ('C').
*	NovaPosicao - char contendo a informação da posicao da carta 'A','2','3','4','5','6','7','8','9','10','J','Q','K'.
*
*  $FV Valor retornado
*	CAR_CondRetCartaNaoExiste - Carta passada no parâmetro nao existe
*	CAR_CondRetFaceErrada - Face passada no parâmetro é inválida
*	CAR_CondRetNaipeNaoExiste - Naipe passado no parâmetro é inválido
*	CAR_CondRetPosicaoNaoExiste - Posicao passada no parâmetro é inválida
*	CAR_CondRetOK - Editou/Preencheu OK
*
***********************************************************************/
CAR_tpCondRet CAR_editarCarta(CAR_tpCarta pCarta, char NovaFace, char NovoNaipe, char NovaPosicao);/*Edita/Preenche uma carta*/
/***********************************************************************
*
*  $FC Função: CAR Seta Posicao da Carta
*
*  $ED Descrição da função
*     Seta a posicao de uma carta de baralho
*
*  $EP Parâmetros
*	pCarta - Endereço que receberá um ponteiro para a carta a ser editada/preenchida.
*	pPosicao - Ponteiro char contendo a informação da posicao da carta 'A','2','3','4','5','6','7','8','9','10','J','Q','K'.
*
*  $FV Valor retornado
*	CAR_CondRetCartaNaoExiste - Carta passada no parâmetro nao existe
*	CAR_CondRetPosicaoNaoExiste - Posicao passada no parâmetro é inválida
*	CAR_CondRetOK - Editou/Preencheu OK
*
***********************************************************************/
CAR_tpCondRet CAR_retornaPosicao(CAR_tpCarta pCarta, char* pPosicao);
/***********************************************************************
*
*  $FC Função: CAR Seta Naipe da Carta
*
*  $ED Descrição da função
*     Seta o naipe de uma carta de baralho
*
*  $EP Parâmetros
*	pCarta - Endereço que receberá um ponteiro para a carta a ser editada/preenchida.
*	pNaipe - Ponteiro char contendo a informação do naipe da carta Espadas ('E'), Ouro ('O') , Paus ('P') , Copas ('C').
*
*  $FV Valor retornado
*	CAR_CondRetCartaNaoExiste - Carta passada no parâmetro nao existe
*	CAR_CondRetNaipeNaoExiste - Naipe passado no parâmetro é inválido
*	CAR_CondRetOK - Editou/Preencheu OK
*
***********************************************************************/
CAR_tpCondRet CAR_retornaNaipe(CAR_tpCarta pCarta, char* pNaipe);
/***********************************************************************
*
*  $FC Função: CAR Seta Face da Carta
*
*  $ED Descrição da função
*     Seta a face de uma carta de baralho
*
*  $EP Parâmetros
*	pCarta - Endereço que receberá um ponteiro para a carta a ser editada/preenchida.
*	pFace - Ponteiro char contendo a informação se a carta está Visivel ('V') ou Escondida ('E').
*
*  $FV Valor retornado
*	CAR_CondRetCartaNaoExiste - Carta passada no parâmetro nao existe
*	CAR_CondRetFaceErrada - Face passada no parâmetro é inválida
*	CAR_CondRetOK - Editou/Preencheu OK
*
***********************************************************************/
CAR_tpCondRet CAR_retornaFace(CAR_tpCarta pCarta, char* pFace);
/***********************************************************************
*
*  $FC Função: CAR Imprime Carta
*
*  $ED Descrição da função
*     Imprime a posicao , face e naipe de uma carta de baralho
*
*  $EP Parâmetros
*	pCarta - Endereço que receberá um ponteiro para a carta a ser editada/preenchida.
*
*  $FV Valor retornado
*	CAR_CondRetCartaNaoExiste - Carta passada no parâmetro nao existe
*	CAR_CondRetFaceErrada - Face da carta é inválida
*	CAR_CondRetNaipeNaoExiste - Naipe da carta é inválido
*	CAR_CondRetPosicaoNaoExiste - Posicao da carta é inválida
*	CAR_CondRetOK - Editou/Preencheu OK
*
***********************************************************************/
CAR_tpCondRet CAR_imprimeCarta(CAR_tpCarta pCarta);




#undef CARTA_EXT /*NAO APAGAR*/

/********** Fim do módulo de definição: CAR Carta **********/

#else/*NAO APAGAR*/
#endif/*NAO APAGAR*/
