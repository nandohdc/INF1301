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
	int nSQP;
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
		LIS_retornaNumElementos(lSQP, &nSQP);
		if (nSQP == 0){
			return 0; // NAO POPA MORTO PQ SQP EH NULA
		}

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
	LIS_tppLista lSQP;
	LIS_tppLista lSQF;
	SQP_tpSQPrincipal sqpDE;
	SQP_tpSQPrincipal sqpPARA;
	SQF_tpSQFinal sSQF;
	PILHA_tpPilha pRemove;
	PILHA_tpPilha pSQF;
	CAR_tpCarta cRemove;
	CAR_tpCarta cSQF;

	int i;

	PILHA_criarPilha(&pRemove);
	CAR_criarCarta(&cRemove);
	PILHA_criarPilha(&pSQF);
	CAR_criarCarta(&cSQF);
	
	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&lSQP);

	LIS_IrInicioLista(lSQP);
	LIS_AvancarElementoCorrente(lSQP, sq_de);
	LIS_ObterValor(lSQP, (void**)&sqpDE);

	LIS_IrInicioLista(lSQP);
	LIS_AvancarElementoCorrente(lSQP, sq_para);
	LIS_ObterValor(lSQP, (void**)&sqpPARA);

	if (SQP_removeDaSequencia(sqpDE, carta, &pRemove) == SQP_CondRetOK){
		if (SQP_adicionaNaSequencia(pRemove, sqpPARA) == SQP_CondRetOK){
			if (SQP_verificaSequenciaCompleta(sqpPARA) == SQP_CondRetOK){
				LIS_IrInicioLista(ListaPrincipal);
				LIS_AvancarElementoCorrente(ListaPrincipal, 2);
				LIS_ObterValor(ListaPrincipal, (void**)&lSQF);

				for (i = 0; i < 8; i++){
					LIS_IrInicioLista(lSQF);
					LIS_AvancarElementoCorrente(lSQF, i);
					LIS_ObterValor(lSQF, (void**)&sSQF);
					SQF_retornaPilha(sSQF, &pSQF);
					if (PILHA_verificaPilhaVazia(pSQF) == PILHA_CondRetPilhaVazia){
						break;
					}
				}

				for (i = 0; i < 13; i++){
					SQP_popSQP(sqpPARA, &cSQF);
					PILHA_pushPilha(pSQF, cSQF);
				}
				LIS_ExcluirElemento(lSQF);
			}
			return 0;//Return 0 == ok!
		}
		else{
			while (PILHA_verificaPilhaVazia(pRemove) == PILHA_CondRetOK){
				PILHA_popPilha(pRemove, &cRemove);
				SQP_pushSQP(sqpDE, cRemove);
			}
			printf("Adiciona: Jogada Invalida\n");
			return -1;//Return == Nao OK!
		}
	}

	else{
		printf("Remove: Jogada Invalida\n");
		return -1;//Return == Nao OK!
	}

}

int ESP_salvaJogo(LIS_tppLista ListaPrincipal, char nome[]){
	char naipe;
	char posicao;
	char face;
	char finalizador;
	char terminator;
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
	PILHA_tpPilha pilhaMorto[5];
	PILHA_tpPilha pilhaSQP[10];
	PILHA_tpPilha pilhaSQF[8];
	PILHA_tpPilha auxiliar;
	PILHA_criarPilha(&auxiliar);

	for (i = 0; i < 5; i++)
	PILHA_criarPilha(&pilhaMorto[i]);
	for (i = 0; i < 10; i++)
	PILHA_criarPilha(&pilhaSQP[i]);
	for (i = 0; i < 8; i++)
	PILHA_criarPilha(&pilhaSQF[i]);

	//LIS_CriarLista(&listaSqPrincipal, DestruirLista);
	//LIS_CriarLista(&listaSqFinal, DestruirLista);

	//SQP_criarSequencia(&sqPrincipal);

	//MOR_criarMorto(&morto, pilhaMorto);


	arq = fopen(nome, "w");

	if (arq == NULL){
		printf("SalvoJogo: ARQ esta nulo!\n");
	}
	finalizador = '@';
	terminator = '#';
	// MORTO
	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 1);
	LIS_ObterValor(ListaPrincipal, (void**)&lMorto);

	fprintf(arq, "M\n");
	for (i = 0; i < 5; i++){
		LIS_IrInicioLista(lMorto);
		LIS_AvancarElementoCorrente(lMorto, i);
		LIS_ObterValor(lMorto, (void**)&mMorto);

		MOR_retornaMorto(mMorto, &pilhaMorto[i]);


		//fprintf(arq, "%d\n", i);

		while (PILHA_verificaPilhaVazia(pilhaMorto[i]) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			MOR_popMorto(mMorto, &carta);
			MOR_retornaMorto(mMorto, &pilhaMorto[i]);
			PILHA_pushPilha(auxiliar, carta);

			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaFace(carta, &face);

			fprintf(arq, "%c\n%c\n%c\n", face, naipe, posicao);

			MOR_retornaMorto(mMorto, &pilhaMorto[i]);
		}

		fprintf(arq, "%c\n", finalizador);
		
		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(auxiliar, &carta);
			MOR_retornaMorto(mMorto, &pilhaMorto[i]);
			PILHA_pushPilha(pilhaMorto[i], carta);
			MOR_retornaMorto(mMorto, &pilhaMorto[i]);
		}
		
	}

	//SEQUENCIAS PRINCIPAIS

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqPrincipal);

	fprintf(arq, "S\n");

	for (i = 0; i < 10; i++){

		LIS_IrInicioLista(listaSqPrincipal);
		LIS_AvancarElementoCorrente(listaSqPrincipal, i);
		LIS_ObterValor(listaSqPrincipal, (void**)&sqPrincipal);

		SQP_retornaPilha(sqPrincipal, &pilhaSQP[i]);


		//fprintf(arq, "%d\n", i);

		while (PILHA_verificaPilhaVazia(pilhaSQP[i]) == PILHA_CondRetOK){
			CAR_criarCarta(&cCarta);
			PILHA_popPilha(pilhaSQP[i], &cCarta);
			CAR_retornaPosicao(cCarta, &posicao);
			CAR_retornaNaipe(cCarta, &naipe);
			CAR_retornaFace(cCarta, &face);
			CAR_editarCarta(cCarta, face, naipe, posicao);
			PILHA_pushPilha(auxiliar, cCarta);
		}
		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){

			CAR_criarCarta(&cCarta);
			PILHA_popPilha(auxiliar, &cCarta);
			//SQP_retornaPilha(sqPrincipal, &pilhaSQP);
			CAR_retornaPosicao(cCarta, &posicao);
			CAR_retornaNaipe(cCarta, &naipe);
			CAR_retornaFace(cCarta, &face);
			fprintf(arq, "%c\n%c\n%c\n", face, naipe, posicao);

			SQP_pushSQP(sqPrincipal, cCarta);

			SQP_retornaPilha(sqPrincipal, &pilhaSQP[i]);
		}
		fprintf(arq, "%c\n", finalizador);
	}

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 2);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqFinal);

	//SEQUENCIAS FINAIS

	fprintf(arq, "F\n");

	for (i = 0; i < 8; i++){

		LIS_IrInicioLista(listaSqFinal);
		LIS_AvancarElementoCorrente(listaSqFinal, i);
		LIS_ObterValor(listaSqFinal, (void**)&sqFinal);

		SQF_retornaPilha(sqFinal, &pilhaSQF[i]);

		//fprintf(arq, "%d\n", i);

		while (PILHA_verificaPilhaVazia(pilhaSQF[i]) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(pilhaSQF[i], &carta);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);
			CAR_editarCarta(carta, face, naipe, posicao);
			PILHA_pushPilha(auxiliar, carta);
		}
		while (PILHA_verificaPilhaVazia(auxiliar) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(auxiliar, &carta);
			//SQF_retornaPilha(sqFinal, &pilhaSQF);
			CAR_retornaPosicao(carta, &posicao);
			CAR_retornaNaipe(carta, &naipe);
			CAR_retornaFace(carta, &face);

			fprintf(arq, "%c\n%c\n%c\n", face, naipe, posicao);

			PILHA_pushPilha(pilhaSQF[i], cCarta);

			SQF_retornaPilha(sqFinal, &pilhaSQF[i]);
		}
		fprintf(arq, "%c\n", finalizador);
	}
	fprintf(arq, "%c\n", terminator);

	fclose(arq);
	return 0;

}

int  ESP_CarregaJogoSalvo(LIS_tppLista *ListaPrincipal, char nome[]){
	char opcao;
	//int nSQP;
	//int nMorto;
	//int nSQF;
	int ind;
	int ind2;
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

	LIS_CriarLista(&lBaralho, DestruirLista);
	LIS_CriarLista(&lMorto, DestruirLista);
	LIS_CriarLista(&lSeqFinal, DestruirLista);
	LIS_CriarLista(&lSeqPrincipal, DestruirLista);
		
	LIS_InserirElementoApos(*ListaPrincipal, lBaralho);
	LIS_InserirElementoApos(*ListaPrincipal, lMorto);
	LIS_InserirElementoApos(*ListaPrincipal, lSeqFinal);
	LIS_InserirElementoApos(*ListaPrincipal, lSeqPrincipal);

	ind2 = 0;
	ind = 0;
	FILE *salvo = fopen(nome, "r");
	if (salvo == NULL){
		printf("Ler Salvo: Erro arquivo NULL!\n");
	}

	//LIS_IrInicioLista((*ListaPrincipal));
	//LIS_AvancarElementoCorrente((*ListaPrincipal), 1);

	fscanf(salvo, "%c", &opcao);

	while (1){
		fscanf(salvo, " %c", &face);
		while (face == '@'){
			fscanf(salvo, " %c", &face);
			ind++;
		}
		if (face == 'S'){
			break;
		}

		else{
			fscanf(salvo, " %c", &naipe);
			fscanf(salvo, " %c", &posicao);
			CAR_criarCarta(&cCarta);
			CAR_editarCarta(cCarta, face, naipe, posicao);
			ind2 = 4 - ind;
			PILHA_pushPilha(pMorto[ind2], cCarta);
		}
	}
	ind = 0;
	while (1){
		fscanf(salvo, " %c", &face);
		while (face == '@'){
			fscanf(salvo, " %c", &face);
			ind++;
		}

		if (face == 'F'){
			break;
		}

		else{
			fscanf(salvo, " %c", &naipe);
			fscanf(salvo, " %c", &posicao);
			CAR_criarCarta(&cCarta);
			CAR_editarCarta(cCarta, face, naipe, posicao);
			SQP_pushSQP(SQP[9 - ind], cCarta);
		}
	}
	ind = 0;
	while (fscanf(salvo, " %c", &face) == 1){
		while (face == '@'){
			fscanf(salvo, " %c", &face);
			ind++;
		}
		if (face == '#'){
			break;
		}

		else{
			fscanf(salvo, " %c", &naipe);
			fscanf(salvo, " %c", &posicao);
			CAR_criarCarta(&cCarta);
			CAR_editarCarta(cCarta, face, naipe, posicao);
			PILHA_pushPilha(pSQF[ind], cCarta);

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
		//PILHA_liberaPilha(pSQP[i]);
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
	int caracter;
	char face;
	char naipe;
	char posicao;

	LIS_tppLista listaSqPrincipal = NULL;
	LIS_tppLista listaSqFinal = NULL;
	LIS_tppLista lMorto = NULL;
	CAR_tpCarta carta;
	MOR_tpMorto morto;
	SQF_tpSQFinal sqFinal = NULL;
	SQP_tpSQPrincipal sqPrincipal = NULL;

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
				if (naipe == 'P'){
					caracter = 5;
				}
				if (naipe == 'C'){
					caracter = 3;
				}
				if (naipe == 'E'){
					caracter = 6;
				}

				if (naipe == 'O'){
					caracter = 4;
				}
				printf("%c%c ", caracter, posicao);
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
	printf("Sequencias Completas Faltando: %d\n", numSQF);

}


int main(void){
	LIS_tppLista ListaPrincipal = NULL;
	LIS_tppLista lMorto = NULL;
	LIS_tppLista lSQF;
	CAR_tpCarta cCarta;
	char NomeArquivo[200];
	int SQPde;
	int SQPpara;
	int numMorto;
	int numSQF;
	int opcao;
	char escolha;
	char vontade;
//	char idioma;
	//char face;
	char naipe;
	char posicao;

	CAR_criarCarta(&cCarta);

	printf("Bem vindo a Interface Bem Bosta!\n");
REINICIO:
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
		INICIO:
			printf("Proximo comando:\n");
			printf("S - Para Salvar o Jogo.\n");
			printf("F - Para Fechar o Jogo.\n");
			printf("J - Para Realizar Jogada.\n");
			printf("M - Para Utilizar o Morto.\n");
			scanf(" %c", &escolha);

			if (escolha == 'S'){
				printf("Digite o nome do arquivo como deseja salvar!\n");
				printf("Por exemplo: JogoSalvo.txt, nao esqueca do .txt\n");
				scanf(" %s", &NomeArquivo);
				ESP_salvaJogo(ListaPrincipal, NomeArquivo);

			}

			else if (escolha == 'F'){
				goto SAIR;

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

				LIS_IrInicioLista(ListaPrincipal);
				LIS_AvancarElementoCorrente(ListaPrincipal, 3);
				LIS_ObterValor(ListaPrincipal, (void**)&lSQF);
				LIS_retornaNumElementos(lSQF, &numSQF);

				if (numSQF == 0){
					printf("Parabens! Voce completou o jogo!\n");
				VONTADE:
					printf("Voce deseja sair do jogo?\n");
					printf("Digite: S - Sim ou N - Nao\n");
					scanf(" %c", &vontade);

					if (vontade == 'S'){

						goto SAIR;
					}

					else if (vontade == 'N'){

						goto REINICIO;
					}

					else{

						goto VONTADE;

					}
				}

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

		}
	}

	else if (opcao == 2){
		printf("Digite o nome do arquivo como deseja carregar!\n");
		printf("Por exemplo: JogoSalvo.txt, nao esqueca do .txt\n");
		scanf(" %s", &NomeArquivo);
		ESP_CarregaJogoSalvo(&ListaPrincipal, NomeArquivo);
		ESP_ImprimeJogo(ListaPrincipal);
		goto INICIO;

	}

	else if (opcao == 3){
	SAIR:
		printf("O Jogo sera fechado!\n");
		system("exit");
	}

}