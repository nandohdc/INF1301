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
#include"Carta.h"
#include"BaralhoInicial.h"
#include"PilhadeCartas.h"
#include"Morto.h"
#include"SequênciasPrincipais.h"
#include"SequênciasFinais.h"
#include"LISTA.h"



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
	LIS_AvancarElementoCorrente(ListaPrincipal, 2);
	LIS_ObterValor(ListaPrincipal, (void**)&lSQP);

	LIS_IrFinalLista(lMorto);
	LIS_ObterValor(lMorto, (void**)&mMorto);

	LIS_IrInicioLista(lSQP);
	for (i = 0; i < 10; i++){
		LIS_ObterValor(lSQP, (void**)&sSQP[i]);
		LIS_AvancarElementoCorrente(lSQP, 1); // Andando para proxima lista
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

		PILHA_pushPilha(pPilha, cCarta);
		SQP_adicionaNaSequencia(pPilha, sSQP[j]);
		PILHA_popPilha(pPilha, &cCarta);
		CAR_destruirCarta(cCarta);
	}

	return 0;

}


int  distribuiBaralho(BAR_tpBaralho pBaralho, SQP_tpSQPrincipal vSQP[], MOR_tpMorto mMorto){
	int i;
	CAR_tpCondRet cRet;
	CAR_tpCarta cCarta;
	PILHA_tpPilha pPilha;
	PILHA_tpPilha pSQP[10];
	PILHA_tpCondRet pRet;
	MOR_tpCondRet mRet;
	PILHA_tpPilha pBCartas;

	BAR_retornaTopoBaralho(pBaralho, &pBCartas);
		
	pRet = PILHA_criarPilha(&pPilha);
	/*
	for (i = 0; i < 10; i++){
		PILHA_criarPilha(&pSQP[i]);
	}
	*/
	for (i = 0; i < 54; i++){

		cRet = CAR_criarCarta(&cCarta);
		PILHA_popPilha(pBCartas, &cCarta);
		PILHA_pushPilha(pPilha, cCarta);

		if (i < 6){
			SQP_pushSQP(vSQP[0], cCarta);
		}

		else if (i >= 6 && i < 12){
			SQP_pushSQP(vSQP[1], cCarta);
		}

		else if (i >= 12 && i < 18){
			SQP_pushSQP(vSQP[2], cCarta);

		}

		else if (i >= 18 && i < 24){
			SQP_pushSQP(vSQP[3], cCarta);
		}

		else if (i >= 24 && i < 29){
			SQP_pushSQP(vSQP[4], cCarta);

		}

		else if (i >= 29 && i < 34){
			SQP_pushSQP(vSQP[5], cCarta);

		}

		else if (i >= 34 && i < 39){
			SQP_pushSQP(vSQP[6], cCarta);

		}

		else if (i >= 39 && i < 44){
			SQP_pushSQP(vSQP[7], cCarta);

		}

		else if (i >= 44 && i < 49){
			SQP_pushSQP(vSQP[8], cCarta);

		}

		else if (i >= 49 && i < 54){
			SQP_pushSQP(vSQP[9], cCarta);

		}
	
		PILHA_popPilha(pPilha, &cCarta);
		CAR_destruirCarta(cCarta);
	}

	mRet = MOR_criarMorto(&mMorto, pBCartas);

	return 0;

}

int  ESP_iniciaNovoJogo(LIS_tppLista * ListaPrincipal){
	int dificuldade;
	int i;
	LIS_tppLista bBaralho = NULL;
	LIS_tppLista mMorto = NULL;
	LIS_tppLista sSeqFinal = NULL;
	LIS_tppLista sSeqPrincipal = NULL;
	
	MOR_tpMorto morto;
	SQP_tpSQPrincipal sqPrincipal[10];
	BAR_tpBaralho baralho = NULL;
	SQF_tpSQFinal sqFinal[8];

	for (i = 0; i < 10; i++){
		SQP_criarSequencia(&sqPrincipal[i]);
	}

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

	distribuiBaralho(baralho, sqPrincipal, &morto);

	LIS_InserirElementoAntes(mMorto, morto);

	for (i = 0; i < 10; i++){
		LIS_InserirElementoAntes(sSeqPrincipal, sqPrincipal[i]);
	}
	for (i = 0; i < 8; i++){
		LIS_InserirElementoAntes(sSeqFinal, sqFinal[i]);
	}

	return 0;

}

int  ESP_realizaJogada(LIS_tppLista ListaPrincipal, int sq_de, int sq_para, CAR_tpCarta carta){

	SQP_tpSQPrincipal sqDe;
	SQP_tpSQPrincipal sqPara;
	LIS_tppLista sSeqPrincipal;
	PILHA_tpPilha auxiliar;
	PILHA_criarPilha(&auxiliar);

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 3);
	LIS_ObterValor(ListaPrincipal, (void**)&sSeqPrincipal);

	LIS_IrInicioLista(sSeqPrincipal);
	LIS_AvancarElementoCorrente(sSeqPrincipal, sq_de);
	LIS_ObterValor(sSeqPrincipal, (void**)&sqDe);

	LIS_IrInicioLista(sSeqPrincipal);
	LIS_AvancarElementoCorrente(sSeqPrincipal, sq_para);
	LIS_ObterValor(sSeqPrincipal, (void**)&sqPara);

	if (SQP_removeDaSequencia(sqDe, carta, &auxiliar) == SQP_CondRetOK){
		SQP_adicionaNaSequencia(auxiliar, sqPara);
		//Sacou?
	}

	SQP_verificaSequenciaCompleta(sqPara);

	return 0;
}

int ESP_salvaJogo(LIS_tppLista ListaPrincipal, char nome[]){
	char naipe;
	char posicao;
	char face;
	int i;
	

	LIS_tppLista listaSqPrincipal;
	LIS_tppLista listaSqFinal;
	SQP_tpSQPrincipal sqPrincipal;
	SQF_tpSQFinal sqFinal;
	CAR_tpCarta carta;

	MOR_tpMorto morto;
	PILHA_tpPilha pilhaMorto;
	PILHA_tpPilha pilha;
	PILHA_tpPilha auxiliar;

	PILHA_criarPilha(&auxiliar);
	PILHA_criarPilha(&pilha);
	PILHA_criarPilha(&pilhaMorto);	

	LIS_CriarLista(&listaSqPrincipal, DestruirLista);
	LIS_CriarLista(&listaSqFinal, DestruirLista);

	SQP_criarSequencia(&sqPrincipal);
	CAR_criarCarta(&carta);
	MOR_criarMorto(&morto, pilhaMorto);

	
	FILE *arq = fopen(nome, "w");
	
	
	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 1);
	LIS_ObterValor(ListaPrincipal, (void**)&morto);

	MOR_retornaMorto(morto, &pilhaMorto);
	fprintf(arq, "M\n");
	while (PILHA_verificaPilhaVazia(pilhaMorto) == PILHA_CondRetOK){
		MOR_popMorto(morto, &carta);
		MOR_retornaMorto(morto, &pilhaMorto);

		CAR_retornaNaipe(carta, &naipe);
		CAR_retornaPosicao(carta, &posicao);
		CAR_retornaFace(carta, &face);

		fprintf(arq, "%c%c%c\n", face, naipe, posicao);

		MOR_retornaMorto(morto, &pilhaMorto);
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

		SQP_retornaPilha(sqPrincipal, &pilha);

		fprintf(arq, "%d\n", i);

		while (PILHA_verificaPilhaVazia(pilha) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(pilha, &carta);
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

			SQP_retornaPilha(sqPrincipal, &pilha);
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

		SQF_retornaPilha(sqFinal, &pilha);

		while (PILHA_verificaPilhaVazia(pilha) == PILHA_CondRetOK){
			CAR_criarCarta(&carta);
			PILHA_popPilha(pilha, &carta);
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

			SQP_retornaPilha(sqPrincipal, &pilha);
		}
		
	}


	return 0;

}

int  ESP_CarregaJogoSalvo(LIS_tppLista *ListaPrincipal, char nome[]){
	char opcao;
	int nSQP;
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
	MOR_tpMorto mMorto;
	SQP_tpSQPrincipal SQP[10];
	SQP_criarSequencia(&SQP[10]);
	SQF_tpSQFinal SQF;
	SQF_criarSQFinal(&SQF);
	PILHA_tpPilha pPilha;
	PILHA_tpPilha pPilha2;
	PILHA_tpPilha pPilha3;
	PILHA_criarPilha(&pPilha);
	PILHA_criarPilha(&pPilha2);
	PILHA_criarPilha(&pPilha3);

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
		switch (opcao){
		case 'M': // MORTO
			while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
				CAR_criarCarta(&cCarta);
				CAR_editarCarta(cCarta, face, naipe, posicao);
				PILHA_pushPilha(pPilha, cCarta);
			}
			break;

		case 'P': // SEQUENCIAS PRINCIPAIS
			while (fscanf(salvo, "%d", &nSQP) == 1){

				switch (nSQP){ // TESTA PARA VER QUAL EH A ORDEM DA SEQUENCIA
				case 0:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[0]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 1:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[1]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 2:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[2]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 3:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[3]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 4:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[4]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 5:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[5]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 6:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[6]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 7:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[7]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 8:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[8]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;

				case 9:
					while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
						CAR_criarCarta(&cCarta);
						CAR_editarCarta(cCarta, face, naipe, posicao);
						PILHA_pushPilha(pPilha2, cCarta);
						SQP_adicionaNaSequencia(pPilha2, SQP[9]);
						PILHA_popPilha(pPilha2, &cCarta);
					}
					break;
				}
			}

			break;

		case 'F': // SEQUENCIAS FINAIS

			while (fscanf(salvo, "%c%c%c", &face, &naipe, &posicao) == 3){
				CAR_criarCarta(&cCarta);
				CAR_editarCarta(cCarta, face, naipe, posicao);
				PILHA_pushPilha(pPilha3, cCarta);
			}
			break;
		}

	}

	SQF_inicializaSQFinal(SQF, pPilha3);
	MOR_criarMorto(&mMorto, pPilha);
	BAR_criarBaralho(&baralho);

	LIS_InserirElementoAntes(lBaralho, baralho);
	LIS_InserirElementoAntes(lMorto, mMorto);
	
	for (i = 0; i < 10; i++){
		LIS_InserirElementoAntes(lSeqPrincipal, SQP[i]);
	}
	
	LIS_InserirElementoAntes(lSeqFinal, SQF);

	PILHA_liberaPilha(pPilha);
	PILHA_liberaPilha(pPilha2);
	PILHA_liberaPilha(pPilha3);

	fclose(salvo);

	return 0;
}

void ESP_ImprimeJogo(LIS_tppLista ListaPrincipal){
	
	
	int i;
	int numero;
	char face;
	char naipe;
	char posicao;

	LIS_tppLista listaSqPrincipal = NULL;
	//LIS_tppLista listaSqFinal;
	LIS_tppLista lMorto;
	SQP_tpSQPrincipal sqPrincipal = NULL;
	//SQF_tpSQFinal sqFinal;
	CAR_tpCarta carta;

	MOR_tpMorto morto;
	PILHA_tpPilha pilha;
	PILHA_tpPilha auxiliar = NULL;
	PILHA_tpPilha pPilha;

	//PILHA_criarPilha(&auxiliar);
	
	//SQP_criarSequencia(&sqPrincipal);
	//LIS_CriarLista(&listaSqPrincipal, DestruirSeqPrincipal);

	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 2);
	LIS_ObterValor(ListaPrincipal, (void**)&listaSqPrincipal);

	LIS_CriarLista(&lMorto, DestruirMorto);
	

	for (i = 0; i < 10; i++){
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
			CAR_editarCarta(carta, face, naipe, posicao);
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

			SQP_retornaPilha(sqPrincipal, &pilha);
		}
		//printf("\n");
	}

	/*
	LIS_IrInicioLista(ListaPrincipal);
	LIS_AvancarElementoCorrente(ListaPrincipal, 1);
	LIS_ObterValor(ListaPrincipal, (void**)&lMorto);
	LIS_ObterValor(lMorto, (void**)&morto);


	PILHA_criarPilha(&pPilha);

	MOR_retornaMorto(morto, &pPilha);

	PILHA_retornaNumElem(pPilha, &numero);
	printf("Morto: %d\n", numero);
	*/
}


int main(void){
	LIS_tppLista ListaPrincipal = NULL;
	int opcao;

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

	}

	else if (opcao == 2){

	}

	else if (opcao == 3){
		printf("O Jogo sera fechado!\n");
		exit(1);
	}

}