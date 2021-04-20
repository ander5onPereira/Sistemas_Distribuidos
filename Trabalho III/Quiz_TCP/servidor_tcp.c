#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG 1024
#define PORTA 4321

/*
 Servidor recebe mensagem do cliente, imprime na tela e envia uma resposta.
 Se o cliente desconectar, processo do servidor continua ativo esperando
 por novas conexoes.
 */

int main(void){
	//variaveis
	int socket_desc , conexao , c;
	struct sockaddr_in server,client;
	char *mensagem;   
  char resposta[MAX_MSG];
	int tamanho, count;

	// destinado a armazenar o IP e porta do cliente  
	char *client_ip;
	int client_port;

	/*********************************************************/
        //Passo 1: Criar o socket servidor na porta passada por parametro
	// AF_INET = ARPA INTERNET PROTOCOLS
	// SOCK_STREAM = TCP
	// 0 = protocolo IP

	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1) {
		printf("Nao foi possivel criar o socket\n");
		return -1;
	}
     
	// Associar (bind) o socket a todos IPs locais 
        // e a PORTA ESPECIFICA para os clientes se conectarem
	server.sin_family = AF_INET; // AF_INET = ARPA INTERNET PROTOCOLS
	server.sin_addr.s_addr = INADDR_ANY; // Obtem IP do S.O.
	server.sin_port = htons(PORTA);
     
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
		puts("Erro ao fazer bind!!! \n");
	}
	puts("Bind efetuado com sucesso!!! \n");

        // Passo 2: aguarda por conexões de clientes
        // O segundo parametro indica quantos conexoes podem aguardar no buffer
	listen(socket_desc, 3);
	/*********************************************************/

	//Aceitando e tratando conexoes
	puts("Aguardando por conexoes...");
	c = sizeof(struct sockaddr_in);

	
	char *mensagem0="\nEstá com dor de cabeça?\n[(S)Sim|(N)Não]: ";
	char *mensagem1="\nMudanças no olfato ou paladar?\n[(S)Sim|(N)Não]: ";
	char *mensagem2="\nEstá com febre?\n[Sim|Não]: ";
	char *mensagem3="\nEstá com tosse?\n[Sim|Não]: ";
	char *mensagem4="\nTem dor no corpo?\n[Sim|Não]: ";
	char *mensagem5="\nEstá com dor de garganta?\n[Sim|Não]: ";
	char *mensagem6="\nTem diarreia?\n[Sim|Não]: ";
	char *mensagem7="\nSente tremores?\n[Sim|Não]: ";
	char *mensagem8="\nEsta com dificuldade para respirar?\n[Sim|Não]: ";
	char *mensagem9="\nTem palpitação?\n[Sim|Não]: ";
	char *retorno;

	// Fica esperando por conexoes
	while( (conexao = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ){
		if (conexao<0){
			perror("Erro ao receber conexao\n");
			return -1;
		}

		//Passo 3: realizar a comunicação 
		// pegando IP e porta do cliente
		client_ip = inet_ntoa(client.sin_addr);
		client_port = ntohs(client.sin_port);
		printf("Cliente conectou: %s : [ %d ]\n",client_ip, client_port);

		int i=0;
		int numSim=0;
		int numNao=0;
		int ret=0;
		// lendo dados enviados pelo cliente
		while(i<11){
		if((tamanho = read(conexao,resposta, MAX_MSG)) < 0){
			perror("Erro ao receber dados do cliente: ");
			return -1;
		}

		// Coloca terminador de string
		resposta[tamanho] = '\0';
		printf("O cliente falou: %s \n", resposta);
		if('s'==resposta[0]||'S'==resposta[0]){
			numSim++;
			i++;
			//printf("PROXIMO\n");
		}else if('n'==resposta[0]||'N'==resposta[0]){
			numNao++;
			i++;
			//printf("ANTERIOR\n");
		}
		switch(i){
			case 0:
				retorno = mensagem0;
			break;
			case 1:
				retorno = mensagem1;
			break;
			case 2:
				retorno = mensagem2;
			break;
			case 3:
				retorno = mensagem3;
			break;
			case 4:
				retorno = mensagem4;
			break;
			case 5:
				retorno = mensagem5;
			break;
			case 6:
				retorno = mensagem6;
			break;
			case 7:
				retorno = mensagem7;
			break;
			case 8:
				retorno = mensagem8;
			break;
			case 9:
				retorno = mensagem9;
			break;
			case 10:
				switch(numSim){
					case 0:
						retorno="\nVocê tem 0 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 1:
						retorno="\nVocê tem 10 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 2:
						retorno="\nVocê tem 20 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 3:
						retorno="\nVocê tem 30 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 4:
						retorno="\nVocê tem 40 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 5:
						retorno="\nVocê tem 50 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 6:
						retorno="\nVocê tem 60 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 7:
						retorno="\nVocê tem 70 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 8:
						retorno="\nVocê tem 80 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 9:
						retorno="\nVocê tem 90 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
					case 10:
						retorno="\nVocê tem 100 porcento de chance de estar com Covid-19\nFechar Quiz?: ";
					break;
				}	
			break;
		}
			// Enviando resposta para o cliente
			write(conexao , retorno , strlen(retorno));
		}

		//Passo 4: Encerrar conexão
		close(conexao);
	}//fim do while

	/*********************************************************/


	printf("Servidor finalizado...\n");
	return 0;
}
