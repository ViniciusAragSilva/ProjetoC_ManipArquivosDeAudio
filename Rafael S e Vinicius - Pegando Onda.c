/*********************************************************************
* @author Rafael Soares Baierle & Vinícius Aragão
* @version 0.1
* @date 2020
***********************************************************************/

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/
/*																											*/
/*											INCLUDES														*/
/*																											*/
/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/
/*																											*/
/*											FUNCOES EXTERNAS												*/
/*																											*/
/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

typedef struct{												//struct de cabeçalho do .wav
	char ChunkID[4]; 
	uint32_t Chunksize;
	char Format [4];
	char SubchunkID [4];
	uint32_t Subchunksize;
	uint16_t Audioformat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate; 
	uint16_t BlockAlign;
	uint16_t BytesPerSample;
	char Subchunk2ID [4];
	uint32_t Subchunk2size;

	}cabecario_t;

void p4(char *str){											//funcao que verifica o chunkID
	
	int i=4;
	while (i)												//while que escreve cada caractere
	{
		putchar(*str);										//escreve carctere no console
		str++;       										//incrementa o endereço do ponteiro
		i--;         										//diminui a quantidade de repetições
	}
}

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/
/*																											*/
/*											MAIN															*/
/*																											*/
/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

int main()//inicio main
{
	setlocale(LC_ALL,"");
	
    FILE *in;                   							//cria o ponteiro para entrada de dados
    FILE *out;                    							//cria o ponteiro para saída de dados
    int16_t data;                 							//dados da musica
    cabecario_t original, alterado;							//cabeçário original, cabeçário alterado
	char nome[50],n_exten[50];    							//nome do arquivo sem extenção, nome do arquivo mais extenção
    int opcao,i;											// <opcao> dentre modificar volume e cortar trecho do wav, <i> variavel de controle
	float percent;											// a porcentagem de aumento do som do wav
	int tempo, inicio, fim;									// tempos de corte do wav
 
 
 /*	======================================================================================================	*/
/*																											*/
/*											APRESENTANDO O ARQUIVO											*/
/*																											*/
/*	======================================================================================================	*/
    
    printf("\t\t================================================\n");
    printf("\t\t||            EDITOR DE ARQUIVO .WAV          ||\n");
    printf("\t\t||                                            ||\n");
    printf("\t\t|| Nomes: Rafael S.B. & Vinícius A.           ||\n");
    printf("\t\t|| Turma: 4323      	       Ano: 2020      ||\n");
	printf("\t\t================================================\n");
    printf("\n     ;;;;;;;;;;;;;;;;;;;			;");
    printf("\n     ;;;;;;;;;;;;;;;;;;;			;;           ;");
    printf("\n     ;                 ;			;';.	     ;;");
    printf("\n     ;                 ;			;  ;;	     ;';.");
    printf("\n     ;                 ;			;   ;;       ;  ;;");
    printf("\n     ;                 ;	.WAV    	;    ;;	     ;   ;;");
    printf("\n     ;                 ;	EDITOR		;    ;;      ;    ;;");
    printf("\n     ;                 ;			;   ;'       ;    ;;");
    printf("\n     ;                 ;			;  '	     ;   ;'");
    printf("\n,;;;;;            ,;;;;;		   ,;;;,;	     ;  '");
    printf("\n,;;;;;            ,;;;;;	   	   ;;;;;;	,;;;,; ");
    printf("\n;;;;;;            ;;;;;;		   `;;;;'	;;;;;; ");
	printf("\n`;;;;'            `;;;;'				`;;;;' \n");
   	printf("\n------------------------------------------------------------------------\n");
   
	
	printf("\n\n \t* Escreva o nome do arquivo WAVE para editá-lo.	");
		printf("\n\n \t(Obs: Será criado um novo arquivo com a edição feita): ");
	scanf("%s",&nome);

    strcpy(n_exten,nome);										// copia o <nome> para a string <n_exten>
    strcat(n_exten,".wav");										// concatena <adiciona> n_exten com .wav, pra dar o formato
    in=fopen(n_exten,"rb");										//abre o arquivo para leitura no modo binario
			
	if (in==NULL)
	{												//verifica se o arquivo existe
	    printf("\n\t !!! ERRO AO ABRIR O ARQUIVO !!!");
	    printf("\n\t Verifique o nome do arquivo e sua extensão e tente de novo...");
	    return (-1);
	}
	
	fread((void*)&original,sizeof(original),1,in);				//le o cabeçário do arquivo .wav
	
	printf("\n\t\t\t * DADOS DO ARQUIVO:\n");
	
/*	======================================================================================================	*/
/*																											*/
/*											EXIBINDO A HEADER												*/
/*																											*/
/*	======================================================================================================	*/
	printf("\n-----------------------------------------\n");
	printf("\t *ChunkID:");
	p4(original.ChunkID);												// deve ser RIFF
	printf("			|\n");
	printf("\t *Chunksize: %d		|\n",original.Chunksize);			// tamanho da musica
	printf("\t *Format:");								
	p4(original.Format);												// deve ser WAVE
	printf("			|\n");

	printf("\t *SubchunkID:");
	p4(original.SubchunkID);
	printf("		|\n");	
	printf("\t *Subchunksize:	%d		|\n", original.Subchunksize);
	printf("\t *Audioformat:	%d		|\n", original.Audioformat);
	printf("\t *NumChannelst:	%d		|\n", original.NumChannels);
	printf("\t *SampleRate:	%d		|\n", original.SampleRate);			
	printf("\t *ByteRate:	%d		|\n", original.ByteRate);
	printf("\t *BlockAlign:	%d		|\n", original.BlockAlign);		
	printf("\t *BytesPerSample: %d		|\n", original.BytesPerSample);
	printf("\t *Subchunk2ID:");
	p4(original.Subchunk2ID);
	printf("		|\n");	
	printf("\t *Subchunk2size: %d	|\n",original.Subchunk2size);

		
	printf("-----------------------------------------\n");
	
/*	======================================================================================================	*/
/*																											*/
/*											PEDINDO QUAL FUNCAO												*/
/*																											*/
/*	======================================================================================================	*/
	
	printf("\n\t* Você deseja alterar o volume ou cortar um trecho do audio?\n");
	
	//do while que verifica se o usuario quer cortar ou alterar volume
	do{															
	
	fflush(stdin);	
	printf("\n\t\t ->1 para alterar o volume \n\t\t ->2 para cortar um trecho: ");
	scanf("%d",&opcao);
	
	}while(opcao<1 || opcao>2);
	
/*	======================================================================================================	*/
/*																											*/
/*											REALIZANDO FUNCAO 1												*/
/*																											*/
/*	======================================================================================================	*/
	
	if(opcao==1)
	{
		
		out=fopen("Editado_Volume.wav","wb");						// abre um novo arquivo para manipular o original pelo volume			
		fwrite((void*)&original, sizeof(original), 1, out);			// escreve no arquivo de out as informacoes de cabeçalho do original
		printf("\n\t* Você deseja aumentar ou diminuir o volume?\n");

		do
		{
			fflush(stdin);	
			printf("\t\t ->1 para aumentar o volume\n\t\t ->2 para diminuir o volume: ");
			scanf("%d",&opcao);
			
	    }while(opcao<1 || opcao>2);
	    
/*	======================================================================================================	*/
/*																											*/
/*										REALIZANDO FUNCAO 1: OPCAO 1 E 2									*/
/*																											*/
/*	======================================================================================================	*/
	    
	    
	    if(opcao==1)
		{
	    	printf("\n\t* Defina quantos porcento você deseja aumentar (No maximo 100, só números): ");
	    	if(percent<=100)
	    	{
	    		scanf("%f",&percent);												//pede os numeros da porcentagem
	    		percent=(100+percent)/100;											// adiciona 100 e divide por 100 pra ver quantos x devera multiplicar por
			}
														
		}
		else
		{
	    	printf("\n\t* Defina quantos porcento você deseja diminuir: ");
	    	scanf("%f",&percent);
	    	percent=(100-percent)/100;
		}
		printf("\n%f\n", percent);
		printf("\n\t* Processando o arquivo...\n");
		
		for(i=0; i< (original.Subchunk2size)/2 ; i++)								// o SubChunk2Size tem q ser dividido por 2 nesse for, pois sera pegado de 16 em 16 bits
		{	
			fread((void*)&data, sizeof(uint16_t), 1, in);							// lendo o conteudo da wav do lugar onde parou (fim da header) e vai ate o fim da wav, de 16 em 16
			
			data =((int16_t) (data * percent));										// multiplicando data pelo percentual de diminuicao/aumento
			
			fwrite((void*)&data, sizeof(uint16_t), 1, out);
		}
		
	
		for(i= 0; i<400; i++)
		{
			fread((void*)&data, sizeof(uint16_t), 1, in);
			fwrite((void*)&data, sizeof(uint16_t), 1, out);
		}
		
	}
	
/*	======================================================================================================	*/
/*																											*/
/*										REALIZANDO FUNCAO 2													*/
/*																											*/
/*	======================================================================================================	*/
	    
	else
	{
		out=fopen("Editado_Tempo.wav","wb");										//cria um arquivo diferente do editado volume
		rewind(in);																	// rebobina <in> até o inicio
		 
		fread((void *)&alterado, sizeof(alterado), 1, in);							// rele os valores de <in>, o arquivo original
		tempo= (alterado.Chunksize)/(original.ByteRate);							// calcula o tempo maximo da musica: (tamanho do arquivo= 4,44Mb) / (taxa de bytes= 88200) 
		
		printf("\n O tempo total é %d segundos\n",tempo);
		printf("\n\t* Defina o tempo onde iniciará o corte, em segundos: ");
		scanf("%d",&inicio);
		printf("\n\t* Defina o tempo onde finalizará o corte, em segundos:");
		scanf("%d",&fim);
		
		printf("\nProcessando o arquivo...\n");
		
		alterado.Chunksize= (fim-inicio)*alterado.ByteRate;							//novo chunksize (tamanho do arquivo) para alterado: (tempo final - tempo inicial) * (a taxa de bytes= 88200)
		alterado.Subchunk2size= alterado.Chunksize-36;								//subchunksize2 (tamanho do arquivo sem o header) de alterado: chunksize de alterado - 44 (o tamanho do header que tá dentro do chunksize)
		
		inicio= alterado.ByteRate*inicio;											// o inicio troca de valor: byterate (taxa de bytes = 88200) * (valor de inicio do corte)
		
		fwrite((void*)&alterado, sizeof(alterado), 1, out);							// escrever no file de saida: os valores da header do alterado
		fseek(in, inicio, 1);														//fseek percorre o arquivo na in, <inicio> vezes, a partir do inicio de in
		
		/* por exemplo, o arquivo tem 49 segundos, e quero do segundo 10 ao 20
		*  o inicio vai ser 88.200 * 10 = 882.000, então o fseek percorreria in,
		* que é o arquivo inicial que foi rewinded no inicio, 882000 bytes, porem
		* A PARTIR DA POSICAO ATUAL, que seria a posicao inicial de data
		
		*/
		for(i=0; i< (alterado.Subchunk2size)/2; i++)
		{	
			fread((void*)&data, sizeof(uint16_t), 1, in);							// le o <in> a partir do fim da header, e armazena em <data> todo o data dele
			fwrite((void*)&data, sizeof(uint16_t), 1, out);							// escreve aquilo q o <data> contem  em <out>
		}
		
		fseek(in, (original.Subchunk2ID-alterado.Subchunk2size), 1);
			for(i= 0; i<400; i++)
		{
			fread((void*)&data, sizeof(uint16_t), 1, in);
			fwrite((void*)&data, sizeof(uint16_t), 1, out);
		}
	}
	
	
	
	fclose(in);
	fclose(out);
	printf("\n Novo Arquivo Adicionado! Verifique sua pasta.");	
    return 0;
}



