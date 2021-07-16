#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 23

//7 é bom
typedef struct sElemento{

struct sElemento* previous;
struct sElemento* next;
char* nome;

}Elemento;

typedef struct sElementoChave{

struct sElementoChave* previous;
struct sElementoChave* next;
int chave;
//
struct Elemento* head;
struct Elemento* tail;
int size;

}ElementoChave;

typedef struct sHash{

struct sElementoChave* head;
struct sElementoChave* tail;
int size;

}Hash;



Elemento* criaElemento(char*);
void insereElemento(ElementoChave*,Elemento*,char*);
void removeElemento(ElementoChave*,Elemento*);
void mostrarLista(ElementoChave*);
//=============================================
        //Tabela Hash
Hash* criaHash();
void inicializarTabelaChaves(Hash*,int);
void insereElementoChave(Hash*,ElementoChave*,int);
ElementoChave* criaElementoChave(int);
FILE* abreArquivo(char*,char*);
void lerArquivo(Hash*);
int funcaoHash(char*);
void inserirNomeHash(Hash*,char*);
Elemento* dividirLista(Elemento*, Elemento*);
void trocarPosicao(Elemento*,Elemento*);
void quicksort(Elemento*,Elemento*);
ElementoChave* encontrarChave(Hash*,int);
void encontrarNome(Hash*,char*);
//int buscarNome(ElementoChave*, char*);
void escreveArquivo(Hash*);
void mostrarListas(Hash*);
void mostrarNomes(Hash*);
void mostrarListaChave(Hash*,int);
void mostrarTamChaves(Hash*);
void removeNome(Hash*,char*);
void interface(Hash*);




//

int main(){
Hash* listaHash = criaHash();

inicializarTabelaChaves(listaHash,TAM);

lerArquivo(listaHash);

ElementoChave* aux = listaHash->head;
    while(aux!=NULL){
        quicksort(aux->head,aux->tail);
         aux = aux->next;
    }

interface(listaHash);

//Mostra quantas chaves tem em cada chave, para analise de nivelamento;
//Para executar tira as duas barras do inicio da função;
//recomendo que coloque duas barras na função interface a cima;
//mostrarTamChaves(listaHash);





}


Elemento* criaElemento(char* nome){

    Elemento* novo = (Elemento*)malloc(sizeof(Elemento));

    novo->previous = NULL;
    novo->next = NULL;
    novo->nome = (char*) malloc (sizeof(char) * 15);
    strcpy(novo->nome,nome);


    return novo;
}


void insereElemento(ElementoChave* lista,Elemento* pivo,char* nome){

    Elemento* novo_elemento = criaElemento(nome);



        if(lista->size == 0){
            lista->head = novo_elemento;
            lista->tail = novo_elemento;
        }else{
            novo_elemento->next = pivo->next;
            novo_elemento->previous = pivo;

                if(pivo->next==NULL){
                    lista->tail=novo_elemento;
                }else{
                    pivo->next->previous = novo_elemento;
                }

            pivo->next = novo_elemento;
        }

    lista->size++;
}

void removeElemento(ElementoChave* lista,Elemento* pivo){
Elemento* antigo;

    if(pivo != NULL && lista->size != 0){
        if(pivo == lista->head){
            lista->head = pivo->next;
                if(lista->head == NULL){
                    lista->head == NULL;
                }else{
                    pivo->next->previous = NULL;
                }
        }else{
            pivo->previous->next = pivo->next;

            if(pivo->next == NULL){
                lista->tail = pivo->previous;
            }else{
                pivo->next->previous = pivo->previous;
            }
        }
        free(pivo);
        lista->size--;
    }
}


//======================================================
        //Tabela Hash

//Inicializa a tabela hash com as chaves
void inicializarTabelaChaves(Hash* listaChave,int tamanho){

   for(int i = 0;i<tamanho;i++){
    insereElementoChave(listaChave,listaChave->tail,i);
   }

}
//aloca a lista hash
Hash* criaHash(){

    Hash* lista=(Hash*)malloc(sizeof(Hash));

    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;



    return lista;
}
//aloca uma chave
ElementoChave* criaElementoChave(int chave){

    ElementoChave* novo = (ElementoChave*)malloc(sizeof(ElementoChave));

    novo->previous = NULL;
    novo->next = NULL;
    novo->head = NULL;
    novo->tail = NULL;
    novo->chave = chave;
    novo->size = 0;

    return novo;
}
//insere um a chave na lista das chaves
void insereElementoChave(Hash* lista, ElementoChave* pivo,int chave){
ElementoChave* novo_elemento = criaElementoChave(chave);

    if(lista->size == 0){
        lista->head = novo_elemento;
        lista->tail = novo_elemento;
    }else{
        novo_elemento->next = pivo->next;
        novo_elemento->previous = pivo;

            if(pivo->next==NULL){
                lista->tail=novo_elemento;
            }else{
                pivo->next->previous = novo_elemento;
            }
            pivo->next = novo_elemento;
        }
    lista->size++;
}

//função hash que retorna a chave que o nome deve ser inserido
int funcaoHash(char* nome){
int soma = 0;
    for (int j = 0; j < strlen(nome); j++){
        soma = (31 * soma + (int)nome[j]) % TAM;
    }
    return soma;
}

//Abre o arquivo de texto
FILE* abreArquivo(char* mode,char* nomeArquivo){
FILE* arquivo = fopen(nomeArquivo, mode);
    if (arquivo == NULL) {
        perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	return arquivo;
}

//Le o arquivo e insere na tabela
void lerArquivo(Hash* hash){
FILE *arquivo;
char* nome[15];
char *result;
arquivo = abreArquivo("rt", "nomes.txt");
int i = 0;
    while (!feof(arquivo)){
        result = fgets(nome, 99, arquivo);
        if (result != NULL){
            nome[15] = result;
            nome[15][strcspn(nome[15], "\n")] = 0;
            inserirNomeHash(hash,nome);
        }
        i++;
    }
    fclose(arquivo);
}

//insere o na tabela hash
void inserirNomeHash(Hash* hash,char* nome){
int chave = funcaoHash(nome);
    ElementoChave* lista = encontrarChave(hash,chave);
    insereElemento(lista, lista->head, nome);
return;
}



//encontrarChave e retorna elemento chave
ElementoChave* encontrarChave(Hash* lista,int chave){
ElementoChave* aux = lista->head;
    while(aux!=NULL){
        if(aux->chave == chave){
           // printf("\n[%i]",aux->chave);
            return aux;
        }
         aux = aux->next;
    }
}

// Orndenaçao Quicksort
Elemento* dividirLista(Elemento* comeco, Elemento* fim){
Elemento* pivo = fim;
Elemento* i = comeco->previous;
    for (Elemento* x = comeco; x != fim; x = x->next){
        if (strcmp(x->nome,pivo->nome) < 0){
            i = (i == NULL ? comeco : i->next);
            trocarPosicao(i,x);
        }
    }
i = (i == NULL ? comeco : i->next);
trocarPosicao(i,pivo);
return i;
}

void trocarPosicao(Elemento* nome1, Elemento* nome2){
  char* nomeAux = (char*) malloc(sizeof(char) * 15);

strcpy(nomeAux, nome1->nome);
strcpy(nome1->nome, nome2->nome);
strcpy(nome2->nome, nomeAux);
free(nomeAux);
}

void quicksort(Elemento* comeco, Elemento* fim){
 if(fim != NULL && comeco != fim && comeco != fim->next){
        Elemento* p = dividirLista(comeco, fim);
        quicksort(comeco, p->previous);
        quicksort(p->next, fim);
    }
}

//Monstra a todos os nomes

void mostrarNomes(Hash* lista){
int i = 0;
    for(ElementoChave* chave = lista->head; chave != NULL; chave = chave->next){
      printf("Chave [%d] (Tamanho: %i)\n",i,chave->size);
      mostrarLista(chave);
      printf("\n");
      i++;
    }
}
void mostrarLista(ElementoChave* lista){
int i = 0;
    for(Elemento* nome = lista->head; nome != NULL; nome = nome->next){
      printf("\tNome posicao[%i]->%s \n",i,nome->nome);
      i++;
    }
}

//mostra a lista com todas as chaves
void mostrarListaChave(Hash* lista,int chave){
Elemento* listaChave = encontrarChave(lista,chave);
mostrarLista(listaChave);
}

void mostrarTamChaves(Hash* lista){
int i = 0;
    for(ElementoChave* chave = lista->head; chave != NULL; chave = chave->next){
      printf("Chave [%d] (Tamanho: %i)\n",i,chave->size);
      printf("\n");
      i++;
    }
}


//busca um nome
void encontrarNome(Hash* lista,char* nome){
int chave = funcaoHash(nome);
int posicao = 0;

    for(ElementoChave* chaveEscolhida = lista->head; chaveEscolhida != NULL; chaveEscolhida = chaveEscolhida->next){
        if(chaveEscolhida->chave == chave){

            for(Elemento* nomeLista = chaveEscolhida->head; nomeLista != NULL; nomeLista = nomeLista->next){
                if(strcmp(nomeLista->nome,nome)==0){
                    printf("\n\tNome encontrado Chave[%i] Posicao[%i]->%s\t\n\n",chave,posicao,nome);
                    return;
                }
                posicao++;
            }

        }
    }

}



void removeNome(Hash* lista,char* nome){
int chave = funcaoHash(nome);
int posicao = 0;
    for(ElementoChave* chaveEscolhida = lista->head; chaveEscolhida != NULL; chaveEscolhida = chaveEscolhida->next){
        if(chaveEscolhida->chave == chave){
            for(Elemento* nomeLista = chaveEscolhida->head; nomeLista != NULL; nomeLista = nomeLista->next){
                if(strcmp(nomeLista->nome,nome)== 0){
                    removeElemento(chaveEscolhida,nomeLista);
                    return;
                }else{
                    return NULL;
                }
            }
        }
    }
}

void interface(Hash* lista){
char* nome = (char*) malloc(sizeof(char) * TAM);
int opcao;
int chave = 0;


    do{
        printf("\t\t\t=========== Tabela Hash ===========\n\n");
        printf("Menu\t[1]Adicionar Nome\n\n\t[2]Excluir Nome\n\n\t[3]Procurar Nome\n\n\t[4]Mostrar Tabela\n\n\t[5]Mostrar uma Chave\n\n\t[0]Sair\n");
        scanf("%i",&opcao);

        if(opcao == 1){
            printf("\tEscreva o nome que deseja adicionar:");
            scanf("%s",nome);
            inserirNomeHash(lista,nome);
        }else if(opcao == 2){
            printf("Digite o nome que deseja deletar:");
            scanf("%s",nome);
            removeNome(lista,nome);
        }else if(opcao == 3){
            printf("Digite o nome que deseja buscar:");
            scanf("%s",nome);
            encontrarNome(lista,nome);
        }else if(opcao == 4){
            mostrarNomes(lista);
        }else if(opcao == 5){
            printf("Digite a chave que deseja mostrar:");
            scanf("%i", &chave);
            printf("\nChave[%i]\n",chave);
            mostrarListaChave(lista,chave);
        }



    }while(opcao != 0);


}
