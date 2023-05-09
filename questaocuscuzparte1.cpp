#include <iostream>
using namespace std;
class Carta{ // definindo o tipo carta
    public: // as informacoes podem ser acessadas fora da classe
        string name; // nome carta
        Carta* next; // ponteiro p proxima carta 

        Carta(){
            this->next = NULL; // tem q apontar p nulo so p existir
        }
        Carta(string name, Carta* next){
            this->name = name; 
            this->next = next;
        }

};

class PlayersList{
    private:
        Carta* head;
        Carta* tail;
        int tam;

    public:
        PlayersList(){
            this->head = this->tail  = new Carta();
            int tam = 0;
        }

        void colocarnoultimoelemento(string name){
            Carta* p = new Carta(name, NULL);
            this->tail->next = p;
            this->tail= this->tail->next;
            if(this->tam == 0){
                this->head = this->tail;
            }
            this->tam++;
        }

        void print(){
            Carta* aux = this->head;
            while (aux != NULL){
                if(tam>0){
                    if(aux->next==NULL){
                        cout << aux->name << endl;
                        break;
                    }
                    else{
                        cout << aux->name << " ";
                        aux = aux->next;
                    }
                }
            }
        }
};

int main(){
    int quantidadepessoas; // criando varivel quantidade de pessos
    cin >> quantidadepessoas; // pegando o valor da variavel 
    PlayersList * lista= new PlayersList [quantidadepessoas]; // alocacao dinamica 
    bool end= false; // variavel p parar o while 
    while(end==false){
        string entrada; // qual comando?
        cin >> entrada; // pega o comando 
        if (entrada== "END"){
            end= true; // se for end para o codigo
            }else if (entrada== "DEA"){ // se for dea
            for(int i=0;i<quantidadepessoas;i++){ // loop pq tem mais de uma pessoa 
                string carta;
                cin >> carta; // recebendo a carta
                lista[i].colocarnoultimoelemento(carta);// inserindo na lista
                }

            } else if (entrada=="PRT"){ // se for prt, a gente printa
            int pos;
            cin>> pos;
            lista[pos].print();// printando

        }
        }
        cout << lista << endl
        }
        
