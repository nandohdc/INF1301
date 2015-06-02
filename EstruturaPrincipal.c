/***************************************************************************
*  $MCI Módulo de implementação: ESP EstruturaPrincipal
*
*  Arquivo gerado:              EstruturaPrincipal.c
*  Letras identificadoras:      ESP
*
*
*  Projeto: Disciplinas INF 1301
*  Professor: Flavio
*  Autores: ds  - Daniel Siles
*			fh  - Fernando Homem
*			mr - Mateus Ribeiro
*
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*		4.00 ds/fh/mr 15/05/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte II.
*       3.00 ds/fh/mr 15/05/2015 Uniformização da interface das funções e
*                                de todas as condições de retorno - Parte I.
*       2.00 ds/fh/mr 15/05/2015 Eliminação de código duplicado, reestruturação
*       1.00 ds/fh/mr 15/05/2015 Início do desenvolvimento
*
***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include"Carta.h"
#include"BaralhoInicial.h"
#include"PilhadeCartas.h"
#include"Morto.h"
#include"SequênciasPrincipais.h"
#include"SequênciasFinais.h"
#include"LISTA.h"


void CriaPilha(PILHA_tpPilha *pPilha, BAR_tpBaralho bBaralho, int nCartas){
	int i;
	CAR_tpCarta cCarta;

	PILHA_criarPilha(pPilha);

	for (i = 0; i < nCartas; i++){
		BAR_popBaralho(bBaralho, &cCarta);
		PILHA_pushPilha(*pPilha, cCarta);
	}

}

void DestruirLista(void * pLista)
{
	LIS_DestruirLista((LIS_tppLista)pLista);
}

void DestruirMorto(void * mMorto)
{
	MOR_liberaMorto((MOR_tpMorto)mMorto);
}

void DestruirSeqPrincipal(void * sSeqPrincipal)
{
	SQP_liberaSequencia((SQP_tpSQPrincipal)sSeqPrincipal);
}

void DestruirSeqFinal(void * sSeqFinal)
{
	SQF_liberaSQFinal((SQF_tpSQFinal)sSeqFinal);
}

void DestruirBaralho(void * bBaralho)
{
	BAR_liberarBaralho((BAR_tpBaralho)bBaralho);
}


int checarDificuldade(int dificuldade){
	int checador[4] = { 1, 2, 3, 4 };
	int i;

	for (i = 0; i < 4; i++){
		if (checador[i] == dificuldade){
			return 1;
		}
	}
	return 0;
}


int escolheDificuldade(void){// criar na main uma variavel para receber o retorno dessa funcao
	int dificuldade;

	printf("Escolha o nivel de dificuldade:\n");

	printf("1 -> 1 Naipe  -> Facil\n");
	printf("2 -> 2 Naipes -> Medio\n");
	printf("3 -> 3 Naipes -> Dificil\n");
	printf("4 -> 4 Naipes -> Muito Dificil\n");

	printf("Digite o nivel escolhido :\n");

	scanf("%d", &dificuldade);

	if (checarDificuldade(dificuldade) == 1){
		return dificuldade;
	}

	return 0;

}


int  distribuiBaralho(BAR_tpBaralho pBaralho, SQP_tpSQPrincipal vSQP[], MOR_tpMorto mMorto[]){
	int i;
	PILHA_tpPilha pMorto[5];
	PILHA_tpPilha pSQP[10];

	for (i = 0; i < 5; i++){
		CriaPilha(&pMorto[i], pBaralho, 10);
		MOR_criarMorto(&mMorto[i], pMorto[i]);
		PILHA_liberaPilha(pMorto[i]);
	}

	for (i = 0; i < 10; i++){
		if (i < 6){
			CriaPilha(&pSQP[i], pBaralho, 5);
			SQP_criarSequencia(&vSQP[i]);
			SQP_adicionaNaSequencia(pSQP[i], vSQP[i]);
			PILHA_liberaPilha(pSQP[i]);
		}

		else{
			CriaPilha(&pSQP[i], pBaralho, 6);
			SQP_criarSequencia(&vSQP[i]);
			SQP_adicionaNaSequencia(pSQP[i], vSQP[i]);
			PILHA_liberaPilha(pSQP[i]);
		}


	}

	return 0;

}

int  ESP_iniciaNovoJogo(LIS_tppLista * ListaPrincipal){
	int dificuldade;
	int i;
	LIS_tppLista bBaralho = NULL;
	LIS_tppLista mMorto = NULL;
	LIS_tppLista sSeqFinal = NULL;
	LIS_tppLista sSeqPrincipal = NULL;

	MOR_tpMorto morto[5];
	SQP_tpSQPrincipal sqPrincipal[10];
	BAR_tpBaralho baralho = NULL;
	SQF_tpSQFinal sqFinal[8];

	dificuldade = escolheDificuldade();

	LIS_CriarLista(ListaPrincipal, DestruirLista);

	LIS_CriarLista(&bBaralho, DestruirBaralho);
	LIS_CriarLista(&mMorto, DestruirMorto);
	LIS_CriarLista(&sSeqFinal, DestruirSeqFinal);
	LIS_CriarLista(&sSeqPrincipal, DestruirSeqPrincipal);



	LIS_InserirElementoApos(*ListaPrincipal, bBaralho);
	LIS_InserirElementoApos(*ListaPrincipal, mMorto);
	LIS_InserirElementoApos(*ListaPrincipal, sSeqFinal);
	LIS_InserirElementoApos(*ListaPrincipal, sSeqPrincipal);

	BAR_criarBaralho(&baralho);

	BAR_inicializarBaralho(baralho, dificuldade);
	BAR_embaralharBaralho(baralho);

	LIS_InserirElementoApos(bBaralho, baralho);

	distribuiBaralho(baralho, sqPrincipal, morto);

	for (i = 0; i < 5; i++){
		LIS_InserirElementoAntes(mMorto, morto[i]);
	}

	for (i = 0; i < 10; i++){
		LIS_InserirElementoAntes(sSeqPrincipal, sqPrincipal[i]);
	}
	for (i = 0; i < 8; i++){
		SQF_criarSQFinal(&sqFinal[i]);
		LIS_InserirElementoAntes(sSeqFinal, sqFinal[i]); //Optamos fazer SQF igual ao MORTO, somente um pilha de Cartas.
	}
	return 0;

}

int  distribuiMortoJogo(LIS_tppLista ListaPrincipal){
	LIS_tppLista lMorto;
	LIS_tppLista lSQP;
	MOR_tpMorto mMorto;
	SQP_tpSQPrincipal sSQP[10];
	CAR_tpCarta cCarta;
	CAR_tpCondRet cRet;
	PILHA_tpPilha pPilha;
	PILHA_criarPilha(&pPilha);
	int i;
	int j;
	char NovaFace = 'V';
	char NaipeAntigo;
	char PosicaoAntiga;


	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 1);
	LIS_ObterValor(ListaPrincipal, (void**)&lMorto);

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&lSQP);

	LIS_IrInicioLista(lMorto);
	LIS_ObterValor(lMorto, (void**)&mMorto);

	
	for (i = 0; i < 10; i++){
		LIS_IrInicioLista(lSQP);
		LIS_AvancarElementoCorrente(lSQP, i); // Andando para proxima lista
		LIS_ObterValor(lSQP, (void**)&sSQP[i]);

	}


	for (j = 0; j < 10; j++){
		cRet = CAR_criarCarta(&cCarta);
		if (cRet == CAR_CondRetMemoria){
			return 1;
		}

		MOR_popMorto(mMorto, &cCarta);

		CAR_retornaNaipe(cCarta, &NaipeAntigo);
		CAR_retornaPosicao(cCarta, &PosicaoAntiga);
		CAR_editarCarta(cCarta, NovaFace, NaipeAntigo, PosicaoAntiga);// VIRANDO A FACE DA CARTA

		//PILHA_pushPilha(pPilha, cCarta);
		SQP_pushSQP(sSQP[j], cCarta);
		//SQP_adicionaNaSequencia(pPilha, sSQP[j]);
		//PILHA_popPilha(pPilha, &cCarta);
		//CAR_destruirCarta(cCarta);
	}

	LIS_ExcluirElemento(lMorto);
	return 0;

}

int  ESP_realizaJogada(LIS_tppLista ListaPrincipal, int sq_de, int sq_para, CAR_tpCarta carta){

	SQP_tpSQPrincipal sqDe;
	SQP_tpSQPrincipal sqPara;
	SQP_tpCondRet retSQP;
	LIS_tppLista sSeqPrincipal;
	CAR_tpCarta cCarta;
	CAR_tpCarta cAuxiliar;
	CAR_tpCarta cAuxiliar2;
	PILHA_tpPilha auxiliar;
	PILHA_tpPilha auxiliar2;
	PILHA_tpPilha sSalva;
	PILHA_tpPilha sSalva2;
	PILHA_tpPilha pSQP;

	char cNaipe;
	char cPosicao;
	char cFace = 'V';

	CAR_retornaNaipe(carta, &cNaipe);
	CAR_retornaPosicao(carta, &cPosicao);

	CAR_criarCarta(&cCarta);
	CAR_criarCarta(&cAuxiliar);
	CAR_criarCarta(&cAuxiliar2);
	PILHA_criarPilha(&auxiliar);
	PILHA_criarPilha(&auxiliar2);
	PILHA_criarPilha(&pSQP);
	PILHA_criarPilha(&sSalva);
	PILHA_criarPilha(&sSalva2);

	CAR_editarCarta(cCarta, cFace, cNaipe, cPosicao);

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&sSeqPrincipal);

	LIS_IrInicioLista(sSeqPrincipal);
	printf("SQde: %d\n", sq_de);
	LIS_AvancarElementoCorrente(sSeqPrincipal, sq_de);
	printf("SQde2: %d\n", sq_de);
	LIS_ObterValor(sSeqPrincipal, (void**)&sqDe);

	LIS_IrInicioLista(sSeqPrincipal);
	LIS_AvancarElementoCorrente(sSeqPrincipal, sq_para);
	LIS_ObterValor(sSeqPrincipal, (void**)&sqPara);

	if (SQP_removeDaSequencia(sqDe, cCarta, &auxiliar) == SQP_CondRetOK){
		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
			PILHA_popPilha(auxiliar, &cAuxiliar2);
			PILHA_pushPilha(sSalva, cAuxiliar2);
			PILHA_pushPilha(sSalva2, cAuxiliar2);
		}

		while (PILHA_verificaPilhaVazia(sSalva2) == PILHA_CondRetOK){
			PILHA_popPilha(sSalva2, &cAuxiliar2);
			PILHA_pushPilha(auxiliar, cAuxiliar2);
		}
		retSQP = SQP_adicionaNaSequencia(auxiliar, sqPara);
		//Sacou?
	}

	if (retSQP != SQP_CondRetOK){
		while (PILHA_verificaPilhaVazia(sSalva) == PILHA_CondRetOK){
			PILHA_popPilha(sSalva, &cAuxiliar);
			PILHA_pushPilha(auxiliar2, cAuxiliar);
		}

		while (PILHA_verificaPilhaVazia(auxiliar2) == PILHA_CondRetOK){
			PILHA_popPilha(auxiliar2, &cAuxiliar);
			SQP_retornaPilha(sqDe, &pSQP);
			PILHA_pushPilha(pSQP, cAuxiliar);
		}
	}

	SQP_verificaSequenciaCompleta(sqPara);

	return 0;
}

int ESP_salvaJogo(LIS_tppLista ListaPrincipal, char *nome){
	char naipe;
	char posicao;
	char face;
	int i;
	FILE *arq;

	LIS_tppLista listaSqPrincipal;
	LIS_tppLista listaSqFinal;
	LIS_tppLista lMorto;
	SQP_tpSQPrincipal sqPrincipal;
	SQF_tpSQFinal sqFinal;
	CAR_tpCarta carta;
	CAR_tpCarta cCarta;

	MOR_tpMorto mMorto;
	PILHA_tpPilha pilhaMorto;
	PILHA_tpPilha pilhaSQP;
	PILHA_tpPilha pilhaSQF;
	PILHA_tpPilha auxiliar;

	PILHA_criarPilha(&pilhaMorto);
	PILHA_criarPilha(&pilhaSQP);
	PILHA_criarPilha(&auxiliar);
	PILHA_criarPilha(&pilhaSQF);

	//LIS_CriarLista(&listaSqPrincipal, DestruirLista);
	//LIS_CriarLista(&listaSqFinal, DestruirLista);

	//SQP_criarSequencia(&sqPrincipal);
	CAR_criarCarta(&carta);
	//MOR_criarMorto(&morto, pilhaMorto);


	arq = fopen(nome, "w");

	if (arq == NULL){
		printf("SalvoJogo: ARQ esta nulo!\n");
	}

	// MORTO
	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 1);
	LIS_ObterValor(ListaPrincipal, (void**)&lMorto);

	fprintf(arq, "M\n");
	for (i = 0; i < 5; i++){
		LIS_IrInicioLista(lMorto);
		LIS_AvancarElementoCorrente(lMorto, i);
		LIS_ObterValor(lMorto, (void**)&mMorto);

		MOR_retornaMorto(mMorto, &pilhaMorto);
		fprintf(arq, "%d\n", i);
		while (PILHA_verificaPilhaVazia(pilhaMorto) == PILHA_CondRetOK){
			MOR_popMorto(mMorto, &carta);
			MOR_retornaMorto(mMorto, &pilhaMorto);

			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaFace(carta, &face);

			fprintf(arq, "%c%c%c\n", face, naipe, posicao);

			MOR_retornaMorto(mMorto, &pilhaMorto);
		}
	}

	//SEQUENCIAS PRINCIPAIS

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqPrincipal);

	fprintf(arq, "P\n");

	for (i = 0; i < 10; i++){

		LIS_IrInicioLista(listaSqPrincipal);
		LIS_AvancarElementoCorrente(listaSqPrincipal, i);
		LIS_ObterValor(listaSqPrincipal, (void**)&sqPrincipal);

		SQP_retornaPilha(sqPrincipal, &pilhaSQP);

		fprintf(arq, "%d\n", i);

		while (PILHA_verificaPilhaVazia(pilhaSQP) == PILHA_CondRetOK){
			CAR_criarCarta(&cCarta);
			PILHA_popPilha(pilhaSQP, &cCarta);
			CAR_retornaPosicao(cCarta, &posicao);
			CAR_retornaNaipe(cCarta, &naipe);
			CAR_retornaFace(cCarta, &face);
			CAR_editarCarta(cCarta, face, naipe, posicao);
			//printf("Face: %c -- Naipe: %c -- Posicao: %c\n", face, naipe, posicao);
			PILHA_pushPilha(auxiliar, cCarta);
		}
		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){

			CAR_criarCarta(&cCarta);
			PILHA_popPilha(auxiliar, &cCarta);
			CAR_retornaPosicao(cCarta, &posicao);
			CAR_retornaNaipe(cCarta, &naipe);
			CAR_retornaFace(cCarta, &face);
			//printf("Face: %c -- Naipe: %c -- Posicao: %c\n", face, naipe, posicao);
			fprintf(arq, "%c%c%c\n", face, naipe, posicao);

			SQP_retornaPilha(sqPrincipal, &pilhaSQP);
		}

	}

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 2);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqFinal);

	//SEQUENCIAS FINAIS

	fprintf(arq, "F\n");

	for (i = 0; i < 8; i++){

		LIS_IrInicioLista(listaSqPrincipal);
		LIS_AvancarElementoCorrente(listaSqPrincipal, i);
		LIS_ObterValor(listaSqPrincipal, (void**)&sqFinal);

		SQF_retornaPilha(sqFinal, &pilhaSQF);

		fprintf(arq, "%d\n", i);
		while (PILHA_verificaPilhaVazia(pilhaSQF) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(pilhaSQF, &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);
			CAR_editarCarta(carta, face, naipe, posicao);
			PILHA_pushPilha(auxiliar, carta);
		}
		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(auxiliar, &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);

			fprintf(arq, "%c%c%c\n", face, naipe, posicao);

			SQP_retornaPilha(sqPrincipal, &pilhaSQF);
		}

	}

	fclose(arq);
	return 0;

}

int  ESP_CarregaJogoSalvo(LIS_tppLista *ListaPrincipal, char nome[]){
	char opcao;
	int nSQP;
	int nMorto;
	int nSQF;
	int i;
	char face;
	char naipe;
	char posicao;

	LIS_tppLista lBaralho;
	LIS_tppLista lMorto;
	LIS_tppLista lSeqFinal;
	LIS_tppLista lSeqPrincipal;

	CAR_tpCarta cCarta;
	BAR_tpBaralho baralho;
	MOR_tpMorto mMorto[5];
	SQP_tpSQPrincipal SQP[10];
	for (i = 0; i < 10; i++){
		SQP_criarSequencia(&SQP[i]);
	}

	SQF_tpSQFinal SQF[8];
	for (i = 0; i < 8; i++){
		SQF_criarSQFinal(&SQF[i]);
	}

	PILHA_tpPilha pMorto[5];
	for (i = 0; i < 5; i++){
		PILHA_criarPilha(&pMorto[i]);
	}

	PILHA_tpPilha pSQP[10];
	for (i = 0; i < 10; i++){
		PILHA_criarPilha(&pSQP[i]);
	}

	PILHA_tpPilha pSQF[8];
	for (i = 0; i < 8; i++){
		PILHA_criarPilha(&pSQF[i]);
	}

	LIS_CriarLista(ListaPrincipal, DestruirLista);

	LIS_CriarLista(&lBaralho, DestruirBaralho);
	LIS_CriarLista(&lMorto, DestruirMorto);
	LIS_CriarLista(&lSeqFinal, DestruirSeqFinal);
	LIS_CriarLista(&lSeqPrincipal, DestruirSeqPrincipal);



	LIS_InserirElementoApos(*ListaPrincipal, lBaralho);
	LIS_InserirElementoApos(*ListaPrincipal, lMorto);
	LIS_InserirElementoApos(*ListaPrincipal, lSeqFinal);
	LIS_InserirElementoApos(*ListaPrincipal, lSeqPrincipal);



	FILE *salvo = fopen(nome, "r");
	if (salvo == NULL){
		printf("Ler Salvo: Erro arquivo NULL!\n");
	}

	LIS_IrInicioLista((*ListaPrincipal));
	LIS_AvancarElementoCorrente((*ListaPrincipal), 1);

	while (fscanf(salvo, "%c", &opcao) == 1){

		if (opcao == 'M'){

			while (fscanf(salvo, "%d", &nMorto) == 1){

				if (nMorto == 0){
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						printf("FACE: %c ---- NAIPE: %c ---- POSICAO: %c\n", face, naipe, posicao);
						PILHA_pushPilha(pMorto[0], cCarta);
					}
				}

				else if (nMorto == 1){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						printf("FACE: %c ---- NAIPE: %c ---- POSICAO: %c\n", face, naipe, posicao);
						PILHA_pushPilha(pMorto[1], cCarta);
					}
				}

				else if (nMorto == 2){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						printf("FACE: %c ---- NAIPE: %c ---- POSICAO: %c\n", face, naipe, posicao);
						PILHA_pushPilha(pMorto[2], cCarta);
					}
				}

				else if (nMorto == 3){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						printf("FACE: %c ---- NAIPE: %c ---- POSICAO: %c\n", face, naipe, posicao);
						PILHA_pushPilha(pMorto[3], cCarta);
					}
				}

				else if (nMorto == 4){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						printf("FACE: %c ---- NAIPE: %c ---- POSICAO: %c\n", face, naipe, posicao);
						PILHA_pushPilha(pMorto[4], cCarta);
					}
				}
			}

		}

		// SEQUENCIAS PRINCIPAIS
		else if (opcao == 'P'){
			while (fscanf(salvo, " %d", &nSQP) == 1){

				if (nSQP == 0){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[0], cCarta);
						SQP_adicionaNaSequencia(pSQP[0], SQP[0]);
						PILHA_popPilha(pSQP[0], &cCarta);
					}
				}

				else if (nSQP == 1){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[1], cCarta);
						SQP_adicionaNaSequencia(pSQP[1], SQP[1]);
						PILHA_popPilha(pSQP[1], &cCarta);
					}
				}

				else if (nSQP == 2){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[1], cCarta);
						SQP_adicionaNaSequencia(pSQP[2], SQP[2]);
						PILHA_popPilha(pSQP[2], &cCarta);
					}
				}

				else if (nSQP == 3){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[3], cCarta);
						SQP_adicionaNaSequencia(pSQP[3], SQP[3]);
						PILHA_popPilha(pSQP[3], &cCarta);
					}
				}

				else if (nSQP == 4){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[4], cCarta);
						SQP_adicionaNaSequencia(pSQP[4], SQP[4]);
						PILHA_popPilha(pSQP[4], &cCarta);
					}
				}


				else if (nSQP == 5){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[5], cCarta);
						SQP_adicionaNaSequencia(pSQP[5], SQP[5]);
						PILHA_popPilha(pSQP[5], &cCarta);
					}
				}

				else if (nSQP == 6){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[6], cCarta);
						SQP_adicionaNaSequencia(pSQP[6], SQP[6]);
						PILHA_popPilha(pSQP[6], &cCarta);
					}
				}

				else if (nSQP == 7){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[7], cCarta);
						SQP_adicionaNaSequencia(pSQP[7], SQP[7]);
						PILHA_popPilha(pSQP[7], &cCarta);
					}
				}

				else if (nSQP == 8){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[8], cCarta);
						SQP_adicionaNaSequencia(pSQP[8], SQP[8]);
						PILHA_popPilha(pSQP[8], &cCarta);
					}
				}

				else if (nSQP == 9){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQP[9], cCarta);
						SQP_adicionaNaSequencia(pSQP[9], SQP[9]);
						PILHA_popPilha(pSQP[9], &cCarta);
					}
				}
			}

		}

		// SEQUENCIAS FINAIS
		else if (opcao == 'F'){
			while (fscanf(salvo, " %d", &nSQF) == 1){

				if (nSQF == 0){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQF[0], cCarta);
						//SQF_inicializaSQFinal(SQF[0], pSQF[0]);
					}
				}

				else if (nSQF == 1){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQF[1], cCarta);
						//SQF_inicializaSQFinal(SQF[0], pSQF[0]);
					}
				}

				else if (nSQF == 2){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQF[2], cCarta);
						//SQF_inicializaSQFinal(SQF[0], pSQF[0]);
					}
				}

				else if (nSQF == 3){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQF[3], cCarta);
						//SQF_inicializaSQFinal(SQF[0], pSQF[0]);
					}
				}

				else if (nSQF == 4){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQF[4], cCarta);
						//SQF_inicializaSQFinal(SQF[0], pSQF[0]);
					}
				}

				else if (nSQF == 5){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQF[5], cCarta);
						//SQF_inicializaSQFinal(SQF[0], pSQF[0]);
					}
				}

				else if (nSQF == 6){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQF[6], cCarta);
						//SQF_inicializaSQFinal(SQF[0], pSQF[0]);
					}
				}

				else if (nSQF == 7){
					while (fscanf(salvo, " %c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pSQF[7], cCarta);
						//SQF_inicializaSQFinal(SQF[0], pSQF[0]);
					}
				}
			}
		}
	}


	BAR_criarBaralho(&baralho);

	LIS_InserirElementoAntes(lBaralho, baralho);
	for (i = 0; i < 5; i++){
		MOR_criarMorto(&mMorto[i], pMorto[i]);
		LIS_InserirElementoAntes(lMorto, mMorto[i]);
		PILHA_liberaPilha(pMorto[i]);
	}


	for (i = 0; i < 10; i++){
		LIS_InserirElementoAntes(lSeqPrincipal, SQP[i]);
		PILHA_liberaPilha(pSQP[i]);
	}

	for (i = 0; i < 8; i++){
		SQF_inicializaSQFinal(SQF[i], pSQF[i]);
		LIS_InserirElementoAntes(lSeqFinal, SQF[i]);
		PILHA_liberaPilha(pSQF[i]);
	}


	fclose(salvo);

	return 0;
}

void ESP_ImprimeJogo(LIS_tppLista ListaPrincipal){
	int j;
	int i;
	int numeronormal = 0;
	int numMorto;
	int numSQF;
	char face;
	char naipe;
	char posicao;

	LIS_tppLista listaSqPrincipal = NULL;
	LIS_tppLista listaSqFinal= NULL;
	LIS_tppLista lMorto = NULL;
	CAR_tpCarta carta;
	MOR_tpMorto morto;
	SQF_tpSQFinal sqFinal = NULL;
	SQP_tpSQPrincipal sqPrincipal= NULL;

	PILHA_tpPilha pilha;
	PILHA_tpPilha auxiliar = NULL;
	PILHA_tpPilha pPilha;
	PILHA_tpPilha pSQF;

	PILHA_criarPilha(&auxiliar);
	PILHA_criarPilha(&pilha);
	PILHA_criarPilha(&pPilha);
	PILHA_criarPilha(&pSQF);
	//SQP_criarSequencia(&sqPrincipal);

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqPrincipal);

	//SQP_adicionaNaSequencia(auxiliar, sqPrincipal);

	LIS_IrInicioLista(listaSqPrincipal);


	for (i = 0; i < 10; i++){
		j = 0;//NAO TIRAR DAQUI!!! SE TIRAR, NAO FUNCIONA.
		printf("%d - ", i);
		LIS_IrInicioLista(listaSqPrincipal);
		LIS_AvancarElementoCorrente(listaSqPrincipal, i);
		LIS_ObterValor(listaSqPrincipal, (void**)&sqPrincipal);

		SQP_retornaPilha(sqPrincipal, &pilha);

		while (PILHA_verificaPilhaVazia(pilha) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(pilha, &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);

			if (j == 0){
				CAR_editarCarta(carta, 'V', naipe, posicao);
				j++;
			}
			else{
				CAR_editarCarta(carta, face, naipe, posicao);
			}

			PILHA_pushPilha(auxiliar, carta);
		}


		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(auxiliar, &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);
			if (face == 'V'){
				printf("%c%c ", naipe, posicao);
			}
			else{
				printf("%c ", 223);
			}
			//PILHA_pushPilha(pilha, carta);
			//SQP_adicionaNaSequencia(pilha, sqPrincipal);
			SQP_retornaPilha(sqPrincipal, &pilha);
			SQP_pushSQP(sqPrincipal, carta);
		}
		printf("\n");
	}


	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 1);
	LIS_ObterValor(ListaPrincipal, (void**)&lMorto);

	for (i = 0; i < 5; i++){
		LIS_IrInicioLista(lMorto);
		LIS_AvancarElementoCorrente(lMorto, i);
		LIS_ObterValor(lMorto, (void**)&morto);
		MOR_retornaMorto(morto, &pPilha);
		LIS_retornaNumElementos(lMorto, &numMorto);
	}
	printf("Morto: %d\n", numMorto);

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 2);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqFinal);

	for (i = 0; i < 8; i++){
		LIS_IrInicioLista(listaSqFinal);
		LIS_AvancarElementoCorrente(listaSqFinal, i);
		LIS_ObterValor(listaSqFinal, (void**)&sqFinal);
		SQF_retornaPilha(sqFinal, &pSQF);
		LIS_retornaNumElementos(listaSqFinal, &numSQF);
	}
	printf("Sequencias Completas: %d\n", numSQF);

}


int main(void){
	LIS_tppLista ListaPrincipal = NULL;
	LIS_tppLista lMorto = NULL;
	CAR_tpCarta cCarta;
	char *NomeArquivo = "JogoSalvo.txt";
	int SQPde;
	int SQPpara;
	int numMorto;
	int opcao;
	char escolha;
	//char face;
	char naipe;
	char posicao;

	CAR_criarCarta(&cCarta);

	printf("Bem vindo a Interface Bem Bosta!\n");
	printf("Escolha a opcao desejada: \n");
	printf("1 - Para iniciar um novo Jogo.\n");
	printf("2 - Para carregar um jogo salvo.\n");
	printf("3 - Para sair do jogo.\n");
	printf("4 - Para tacar fogo no baralho.\n");
	printf("Digite a opcao escolhida:\n");
	scanf("%d", &opcao);

	if (opcao == 1){
		ESP_iniciaNovoJogo(&ListaPrincipal);
		ESP_ImprimeJogo(ListaPrincipal);
		while (1){

			printf("Proximo comando:\n");
			printf("S - Para Salvar o Jogo.\n");
			printf("F - Para Fechar o Jogo.\n");
			printf("J - Para Realizar Jogada.\n");
			printf("M - Para Utilizar o Morto.\n");
			scanf(" %c", &escolha);

			if (escolha == 'S'){
				ESP_salvaJogo(ListaPrincipal, NomeArquivo);

			}

			else if (escolha == 'F'){
				printf("Fechando programa em 5 seg");



			}

			else if (escolha == 'J'){
				printf("Digite numero da sequencia que deseja remover a carta:\n");
				scanf("%d", &SQPde);
				printf("Digite numero da sequencia que deseja adicionar a carta:\n");
				scanf("%d", &SQPpara);


				printf("Digite o naipe da carta que deseja remover:\n");
				scanf(" %c", &naipe);
				printf("Digite a posicao da carta que deseja remover:\n");
				scanf(" %c", &posicao);

				CAR_editarCarta(cCarta, 'V', naipe, posicao);

				ESP_realizaJogada(ListaPrincipal, SQPde, SQPpara, cCarta);
				ESP_ImprimeJogo(ListaPrincipal);

			}


			else if (escolha == 'M'){
				
				LIS_IrInicioLista(ListaPrincipal);
				LIS_AvancarElementoCorrente(ListaPrincipal, 1);
				LIS_ObterValor(ListaPrincipal, (void**)&lMorto);
				LIS_retornaNumElementos(lMorto, &numMorto);

				if (numMorto > 0){
					distribuiMortoJogo(ListaPrincipal);
					ESP_ImprimeJogo(ListaPrincipal);
				}

				else{
					printf("Nao existe morto disponivel!\n");
				}
			}
			else{
				printf("Opcao digitada invalida!\n");
				printf("Digite a opcao novamente!\n");
			}
			//system("cls");
		}
	}

	else if (opcao == 2){
		ESP_CarregaJogoSalvo(&ListaPrincipal, NomeArquivo);
		ESP_ImprimeJogo(ListaPrincipal);

	}

	else if (opcao == 3){
		printf("O Jogo sera fechado!\n");
		exit(1);
	}

}