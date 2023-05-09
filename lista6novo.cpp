#include <iostream>  
using namespace std;
int contadorModos = 0;
int Lista[31];

void backtracking(int i, int minItens, int soma, int maxPreco, int itens, int itensDisponiveis){
  if(soma > maxPreco){
    return;
  }
  
  if(i == itensDisponiveis){
    if(itens >= minItens)
      contadorModos++;
      return;
  }
  backtracking(i+1, minItens, Lista[i] + soma, maxPreco, itens+1, itensDisponiveis);
  backtracking(i+1, minItens, soma, maxPreco, itens, itensDisponiveis);
  
}

int main(){
    int NumeroLojas;
    int itensDisponiveis; //max 31
    int preco;
    int menorQuantidade;
    int maxGasto; //Q
    cin >> NumeroLojas; 
    for(int i = 0; i<NumeroLojas;i++){
        cin >> itensDisponiveis;
        for(int w = 0; w < itensDisponiveis; w++){
            cin >> preco;
            Lista[w] = preco;
        }
        cin >> menorQuantidade >> maxGasto;

        contadorModos = 0;
        backtracking(0, menorQuantidade, 0, maxGasto, 0 , itensDisponiveis);
      
        cout << "caso "<< i << ": " << contadorModos << endl;
    }
}