#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void counting_sort(char **str, char **str_aux, int k, int N, int indice, int *C);
void radix_sort(char **str, char **str_aux, int aux_tam, int N, int *C);

int main (){

  int N;
  char **str, **str_aux;
  int vet[2];

  scanf("%d", &N);

  int *C = (int*) malloc (27 * sizeof(int));

  str = (char **) malloc(N * sizeof(char *));

  for (int i = 0; i < N; i++){
    str[i] = (char *) malloc(21 * sizeof(char));
  }

  str_aux = (char **) malloc(N * sizeof(char *));

  for(int j = 0; j < N; j++){
    str_aux[j] = (char*) malloc(21* sizeof(char));
  }

  for (int i = 0; i < N; i++){
    scanf("%s", str[i]);
  }
  

  for(int i = 0; i < 2; i++){
    scanf("%d",&vet[i]);
  }

  
  for (int i = 0; i < N; i++){ // Transforma as strings em minusculo
    for (int j = 0; j < strlen(*(str+i)); j++){
      if (str[i][j] < 97 || str[i][j] > 122){
        str[i][j] = tolower(str[i][j]);
      }        
    }
  }

  for (int i = 0; i < N; i++){ // Printa as strings com pontuação no final
    for (int j = 0; j < strlen(*(str+i)); j++){
      printf("%c", str[i][j]);
    }
    printf(".\n");
  }

  int aux_tam = strlen(*(str+0)); // Pega o tamanho da primeira string

  for (int i = 1; i < N; i++){ // A variavel "aux_tam é usada para saber o tamanho da maior string
    if (strlen(*(str+i)) > aux_tam){
      aux_tam = strlen(*(str+i));
      }
  }

  printf("%d\n",aux_tam);

  for(int i = 0; i < N; i++){

    for (int j = strlen(*(str+i)); j < aux_tam; j++){
      *(*(str+i)+j) = ' '; // Preenche com espaços
    }

  }
  
  radix_sort(str, str_aux, aux_tam, N, C);


  for (int i = vet[0]-1; i < (vet[0]+vet[1])-1; i++){ // Printa as strings requeridas
    
    printf("%s\n", str[i]);
    
  }

    for (int i = 0; i < N; i++){ // Libera a memória alocada
      if(str_aux[i])
        free(str_aux[i]);
      if(str[i])
        free(str[i]);
    }

  if(str)
    free(str); // Libera a memória alocada da matriz original
  
  if(str_aux)
    free(str_aux); // Libera a memória alocada da matriz original
  
  if(C)
    free(C);

    
  return 0;
}

void radix_sort(char **str, char **str_aux, int aux_tam, int N, int *C){

  for(int i = aux_tam-1 ; i >= 0; i--){

    counting_sort(str, str_aux, 26, N, i, C);
    
  }
  
} 

void counting_sort(char **str, char **str_aux, int k, int N, int indice, int *C){ // k = 26; N = quantas palavras existem

    int i, auxx;

    for(int i = 0; i < 28; i++){
      C[i] = 0;
    }

  // memset(C, 0 ,sizeof(*C));

    for (i = 0; i < N; i++){

      if(str[i][indice] == ' '){
        C[0]++; // os espaços estão no indice 0
      }
      else{
        C[str[i][indice] - 'a' + 1]++; // acrescenta 1 para que o indice seja igual ao valor da letra
      }

    }

    for (i = 1; i <= k; i++){
      C[i] += C[i-1]; // Soma o valor do indice anterior com o valor do indice atual
    }

    for(i = 0; i <= 26; i++){ // Printa o conteúdo do vetor C
      printf("%d ", C[i]);
    }
  
    printf("\n");


    for(i = N - 1; i >= 0; i--){ // Preenche o vetor str com os valores do vetor C
        
      if(str[i][indice] == ' '){
        auxx = 0;
      } else {
          auxx = (str[i][indice] - 'a' + 1);
        }

      C[auxx]--;

      str_aux[C[auxx]] = str[i];
      
    }

    for(i = 0; i < N; i++){ // Copia o vetor str_aux para o vetor str
      str[i] = str_aux[i];
    }

}