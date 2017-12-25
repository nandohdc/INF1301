/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			ds  - Daniel Siles
*			fh  - Fernando Homem
*			mr - Mateus Ribeiro
*
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*		4.00 ds/fh/mr 25/03/2015 Criação da função Costureira	
*       3.00   avs    28/02/2003 Uniformização da interface das funções e
*                                de todas as condições de retorno.
*       2.00   avs    03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs    15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */
		 
		 struct tgNoArvore * pNoCostura;
				/* Ponteiro para costurar as folhas*/

		 char pNoChave;
				/*Ponteiro auxiliar para armazenar as folhas anteriores*/

         char Valor ;
               /* Valor do nó */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpArvore ;

/*****  Dados encapsulados no módulo  *****/

      static tpArvore * pArvore = NULL ;
            /* Ponteiro para a cabe‡a da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void )
   {

      if ( pArvore != NULL )
      {
         ARV_DestruirArvore( ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

   void ARV_DestruirArvore( void )
   {

      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         pArvore = NULL ;
      } /* if */

   } /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */
      * ValorParm = pArvore->pNoCorr->Valor ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
	  pNo->Valor  = ValorParm ;
      pNo->pNoChave  = ValorParm ;
      return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( char ValorParm )
   {

      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;

      if ( pArvore == NULL )
      {
         CondRet = ARV_CriarArvore( ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: ARV Destruir a estrutura da árvore */

/***********************************************************************
*
*  $FC Função: ARV Conta Folhas
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/
   int ARV_ContaFolhas(tpNoArvore * arvore){
	   //Verifica se a arvore não está vazia
	   if(arvore == NULL){
		   return 0;
	   }
	   //Varifica se o nó da árvore é uma folha
	   else if((arvore->pNoEsq == NULL) && (arvore->pNoDir == NULL)){
		   return 1;
	   }
	   
	   else{
		   return ((ARV_ContaFolhas(arvore->pNoEsq)) + (ARV_ContaFolhas(arvore->pNoDir)));
	   }
   } /* Fim função: ARV Conta Folhas */
   
/***********************************************************************
*
*  $FC Função: ARV Pega Chave
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/
   char* ARV_PegaChave(tpNoArvore *arvore, char *vetorA, char *indice){
	   if(arvore->pNoEsq != NULL){
		   ARV_PegaChave(arvore->pNoEsq, vetorA, indice);
	   }
	   if(arvore->pNoDir != NULL){
		   ARV_PegaChave(arvore->pNoDir, vetorA, indice);
	   }
	   //Acha folha, retorna a chave e armazena no vetor
	   if(arvore->pNoDir == NULL && arvore->pNoEsq == NULL){
		   vetorA[*indice] = arvore->pNoChave;
		   *indice = *indice + 1;

	   }
	   return vetorA;
   } /* Fim função: ARV Pega Chave */

  /***********************************************************************
*
*  $FC Função: ARV Ordena Vetor
*
***********************************************************************/
 
   void ARV_OrdenaVetor(char* VetorA, int nfolhas){
	   int fim, i;
	   for( fim = nfolhas-1 ; fim > 0 ; fim--){
		   for(i = 0 ; i < fim ; i++){
			   if(VetorA[i] > VetorA[i+1]){
			   int temp = VetorA[i];
			   VetorA[i] = VetorA[i+1];
			   VetorA[i+1] = temp;
			   }
		   }
	   }
   } /* Fim função: ARV Ordena Vetor */
   
   /***********************************************************************
*
*  $FC Função: ARV Busca e Costura
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/


   void ARV_BuscaECostura(tpNoArvore * arvore, char elemento){
	   
	   if (arvore->pNoEsq != NULL){
		   ARV_BuscaECostura(arvore->pNoEsq, elemento);
	   }

	   if (arvore->pNoDir != NULL){
		   ARV_BuscaECostura(arvore->pNoDir, elemento);
	   }
	   //Encontra uma folha com o elemento procurado e realiza a costura
	   if ((arvore->pNoDir == NULL) && (arvore->pNoEsq == NULL) && (arvore->pNoChave == elemento)){
		   arvore->pNoCostura = pArvore->pNoCorr;
		   pArvore->pNoCorr = arvore;
	   }
   } /* Fim função: ARV Busca e Costura */

   /***********************************************************************
*
*  $FC Função: ARV Imprime
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/
   void ARV_Imprime(tpNoArvore * arvore, char elemento, int nfolhas){
	   
	   int i;

	   if (arvore->pNoEsq != NULL){
		   ARV_Imprime(arvore->pNoEsq, elemento, nfolhas);
	   }
	   if (arvore->pNoDir != NULL){
		   ARV_Imprime(arvore->pNoDir, elemento, nfolhas);
	   }
	   if ((arvore->pNoDir == NULL) && (arvore->pNoEsq == NULL) && (arvore->pNoChave == elemento)){
		   //Encontra a folha que contém o primeiro elemento a ser costura e segue a costura pelo ponteiro pNoCostura
		   for (i = 0; i < nfolhas; i++)
		   {
			   printf("%c ", arvore->pNoChave);
			   arvore = arvore->pNoCostura;
		   }
	   }
	   
   } /* Fim função: ARV Imprime */

/***********************************************************************
*
*  $FC Função: ARV Costureira
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/
   ARV_tpCondRet ARV_Costureira(void){
	   int nfolhas = 0, i = 0;
	   char indice = 0;
	   char *VetorA;

	    if (pArvore == NULL){
		   return ARV_CondRetArvoreNaoExiste;
	   }

	   if (pArvore->pNoRaiz == NULL){
		   return ARV_CondRetArvoreVazia;
	   }   

	   //Recebe o numero de folhas da árvore
	   nfolhas = ARV_ContaFolhas(pArvore->pNoRaiz);

	   VetorA = (char*) malloc (nfolhas * sizeof(char));

	   if(VetorA == NULL){
		   return ARV_CondRetFaltouMemoria;
	   }
		
	   //Preenche o vetor com as chaves das folhas
	   VetorA = ARV_PegaChave(pArvore->pNoRaiz, VetorA, &indice);
	   
	   //Ordena o vetor em ordem alfanumérica
	   ARV_OrdenaVetor(VetorA, nfolhas);

	   pArvore->pNoCorr = NULL;

	   //Costura as folhas da árvore partindo do último elemento a ser costurado
	   //O último aponta para NULL
	   //Os demais apontam para o que foi costurado anteriormente
	   for (i = nfolhas - 1; i >= 0; i--){
		   ARV_BuscaECostura(pArvore->pNoRaiz, VetorA[i]);
	   }

	   printf("\n");

	   //Imprime a chave das folhas seguindo a costura (em órdem alfanumérica)
	   ARV_Imprime(pArvore->pNoRaiz, VetorA[0], nfolhas);

	   free(VetorA);

	   return ARV_CondRetOK;
   } /* Fim função: ARV Costureira */

      
/********** Fim do módulo de implementação: Módulo árvore **********/

