#include <iostream>
#include <malloc.h>
#include <string>
#include <stdlib.h>

using namespace std;

typedef struct {
    int timestamp;  // struct do cliente 
    unsigned ip;
} Connection;

typedef struct {
    int tamanho;  // struct do array 
    int quantidade;
} Array;

int queryConnection(int value, int begin, int end, Connection *arr){

    int middle = (begin + end)/2;   // busca binÃ¡ria 

    if(begin > end)
        return -1;

    if(arr[middle].timestamp == value)
        return middle;

    if(arr[middle].timestamp > value)
        return queryConnection(value, begin, middle-1, arr);

    else
        return queryConnection(value, middle+1, end, arr);}
        
int Partition(Connection arr[], int low, int high){
    int pivot = arr[high].timestamp;
    int i = (low - 1);         // PartiÃ§Ã£o
  
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].timestamp < pivot) {
            i++; 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void QuickSort(Connection arr[], int low, int high)    // quicksort em si
{
    if (low < high) {
        int pi = Partition(arr, low, high);
  
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}        


int DispersionFunction(int t, int m){ // funcao dispersao
    return (t%m);
}

int FatordeCarga(int tamanho, int Lmax){
    int maximo;
    maximo= tamanho*Lmax;    // funcao para achar o maximo
    return maximo;
}


int main()
{
// declarando variaveis 
int Tamanho; // tamanho da hashtable m
int Lmax; // fator de carga
string Comando; // comando acao
int index; //index maximo
int tsp; // timestamp
unsigned client; // ip do cliente
int contador = 0; // contador
int total;
int aux;
cin >> Tamanho; //
cin >> Lmax; 
total = FatordeCarga(Tamanho, Lmax);

Connection **coluna = (Connection**)malloc(Tamanho*sizeof(Connection));
Array *linha = (Array*)malloc(Tamanho*sizeof(Array)); 

for(int cont = 0; cont < Tamanho; cont++){
    linha[cont].quantidade = 0;
    linha[cont].tamanho = 1;}
for(int cont = 0; cont < Tamanho; cont++){
    Connection*ponteiro= (Connection*)malloc(linha[cont].tamanho*sizeof(Connection));
    coluna[cont]= ponteiro;
}

while (1){
    cin >> Comando; 
    if (Comando == "END"){
        break;
    }
    else if (Comando == "NEW"){
        if(contador > total){
            aux = Tamanho;
            Connection **colunaaux = coluna;
            Array *linhaaux = linha;
            Tamanho= (2*Tamanho) + 1;
            total = FatordeCarga(Tamanho, Lmax);
            coluna = (Connection**) malloc(Tamanho*sizeof(Connection));
            linha = (Array*) malloc(Tamanho*sizeof(Array));
            for (int i = 0; i < Tamanho; i++){
                linha[i].quantidade = 0;
                linha[i].tamanho = 1;}
            for (int i = 0; i < Tamanho; i++){
                Connection * ponteiro = (Connection*)malloc(linha[i].tamanho*sizeof(Connection));
                coluna[i]= ponteiro;}
            for(int b = 0; b < aux; b++){
                if(linhaaux[b].quantidade != 0){
                    for(int j = 0; j < linhaaux[b].quantidade; j++){
                        index = colunaaux[b][j].timestamp%Tamanho;
                        if (linha[index].quantidade == linha[index].tamanho){
                            linha[index].tamanho = linha[index].tamanho * 2;
                            coluna[index] = (Connection*) realloc(coluna[index],linha[index].tamanho * sizeof(Connection));
                            coluna[index][linha[index].quantidade].timestamp = colunaaux[b][j].timestamp;
                            coluna[index][linha[index].quantidade].ip = colunaaux[b][j].ip;
                            linha[index].quantidade = linha[index].quantidade + 1;
                                }
                        else{
                            coluna[index][linha[index].quantidade].timestamp = colunaaux[b][j].timestamp;
                            coluna[index][linha[index].quantidade].ip = colunaaux[b][j].ip;
                            linha[index].quantidade = linha[index].quantidade + 1;                  
                        } 
                for(int i = 0; i < Tamanho; i ++){
                    if(linha[i].quantidade >= 2){
                        QuickSort(coluna[i] ,0, linha[i].quantidade - 1);
                        } }
                    } } } }
        cin >> tsp;
        cin >> client;
        int index = DispersionFunction(tsp, Tamanho);
        if (linha[index].quantidade == linha[index].tamanho){
            linha[index].tamanho = linha[index].tamanho * 2;
            coluna[index] = (Connection*) realloc(coluna[index],linha[index].tamanho * sizeof(Connection));
            coluna[index][linha[index].quantidade].timestamp = tsp;
            coluna[index][linha[index].quantidade].ip = client;
            linha[index].quantidade = linha[index].quantidade + 1;
            contador ++;
            }
        else {
            coluna[index][linha[index].quantidade].timestamp = tsp;
            coluna[index][linha[index].quantidade].ip = client;
            linha[index].quantidade = linha[index].quantidade + 1;
            contador ++;
            }
        cout<<index<<" "<<linha[index].quantidade<<endl;
    }
    else if ( Comando == "QRY"){
            cin>>tsp;
            index = DispersionFunction(tsp, Tamanho);           
            int resultado = (queryConnection(tsp, -1, linha[index].quantidade, coluna[index]));
            if(coluna[index][resultado].timestamp == tsp){
                cout<<coluna[index][resultado].ip<<" "<<resultado<<endl;
            }
            else{
                cout<<-1<<" "<<-1<<endl;}}
    
}

}