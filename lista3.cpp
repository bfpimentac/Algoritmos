#include <iostream>
#include <string>
using namespace std;

struct RootNode{
    int informacao;
    RootNode*left;
    RootNode*right;
};

int altura(RootNode *rootPtr, int informacao, int n, bool *flag){

    if(rootPtr == NULL){
        (*flag) = false;
        return n;
    }
    else if(rootPtr->informacao == informacao)
        return n;

    else if(rootPtr->informacao > informacao)
        return altura(rootPtr->left, informacao, n+1, flag);
    
    else if(rootPtr->informacao < informacao)
        return altura(rootPtr->right, informacao, n+1, flag);
    
}

RootNode* GetNewNode(int informacao){
    RootNode* novoNode= new RootNode();
    (*novoNode).informacao= informacao;
    (*novoNode).left= NULL;
    (*novoNode).right= NULL; 
    return novoNode;
}

RootNode *findNode(int informacao, RootNode *root){

    if(informacao < root->informacao && root->left != NULL)
        root = findNode(informacao, root->left);
    else if(informacao > root->informacao && root->right != NULL)
        root = findNode(informacao, root->right);

    return root;
}

RootNode *rotateLeft(RootNode *root){
    RootNode *r, *rl;
    r = root->right;
    rl = r->left;
    r->left = root;
    root->right = rl;

    return r;
}

RootNode *rotateRight(RootNode *root){
    RootNode *l, *lr;
    l = root->left;
    lr = l->right;
    l->right = root;
    root->left = lr;

    return l;
}

RootNode *acharPai(RootNode *root, int informacao){
    if(root == NULL || root->informacao == informacao)
        return NULL;
    
    else if(root->left != NULL && root->left->informacao == informacao)
        return root;

    else if(root->right != NULL && root->right->informacao == informacao)
        return root;

    else if(root->informacao > informacao)
        return acharPai(root->left, informacao);

    else if(root->informacao < informacao)
        return acharPai(root->right, informacao);

    return root;
}

RootNode *rotacionar(RootNode *root, RootNode *node, int profundidade, int informacao){
    RootNode *pai, *avo;

    for(int i = profundidade; i > 0; i--){
        pai = acharPai(root, informacao);

/*         if(pai != NULL)
            cout << "pai = " << pai->informacao << endl; */

        if(pai->informacao > informacao){
            node = rotateRight(pai);
           // cout << "ABC" << endl;
        }
        else if(pai->informacao < informacao){
            node = rotateLeft(pai);
            //cout << "DEF" << endl;
        }

        avo = acharPai(root, pai->informacao);
        if(avo != NULL){
            //cout << "vovo = " << avo->informacao << endl;
            if(avo->informacao > informacao)
                avo->left = node;
            else if(avo->informacao < informacao)
                avo->right = node;
        }
    }

    return node;
}

RootNode *Inserir(RootNode* root, int informacao){
    if(root == NULL){
        //cout << "Aqui 4" << endl;
        RootNode *newNode = new RootNode();
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->informacao = informacao;
        return newNode;
    }

    else if(informacao == root->informacao){
        //cout << "teste" << endl;
        return root;
    }

    else if(informacao < root->informacao){
        //cout << "Aqui 1\n";
        root->left = Inserir(root->left, informacao);
        
    }
    else if(informacao > root->informacao){
        //cout << "Aqui 2\n";
        root->right = Inserir(root->right, informacao);
    }
    return root;
        
}

RootNode *deleteMin(RootNode *root, int *v){
    RootNode *r, *l;

    if(root->left == NULL){
        r = root->right;
        (*v) = root->informacao;
        free(root);
        return r;
    }

    else{
        l = deleteMin(root->left, v);
        root->left = l;
        return root;
    }
}

RootNode *deletar(RootNode *root, int informacao){
    RootNode *r, *l;
    int rootinformacao;

    if(root == NULL)
        return NULL;

    else if(informacao < root->informacao){
        root->left = deletar(root->left, informacao);
        return root;
    }

    else if(informacao > root->informacao){
        root->right = deletar(root->right, informacao);
        return root;
    }

    else{
        if(root->left == NULL){
            r = root->right;
            free(root);
            return r;
        }

        else if(root->right == NULL){
            l = root->left;
            free(root);
            return l;
        }

        else{
            root->right = deleteMin(root->right, &rootinformacao);
            root->informacao = rootinformacao;
            return root;
        }
    }
}

int main()
{
    RootNode* rootPrt = NULL, *pai;
    string comando;
    int informacao;
    bool flag;

    while(1){
        cin >> comando;

        if(comando == "INS"){
            cin >> informacao;
            rootPrt = Inserir(rootPrt, informacao);
            int height = altura(rootPrt, informacao, 0, &flag);
            cout << height << endl;
            rootPrt = rotacionar(rootPrt, findNode(informacao, rootPrt), height, informacao);
        }

        else if(comando == "FND"){
            cin >> informacao;
            flag = true;
            int profundidade = altura(rootPrt, informacao, 0, &flag);
            cout << profundidade << endl;
            if(flag)
                rootPrt = rotacionar(rootPrt, findNode(informacao, rootPrt), profundidade, informacao);
        }

        else if(comando == "DEL"){
            cin >> informacao;
            pai = acharPai(rootPrt, informacao);
            int profundidade = altura(rootPrt, informacao, 0, &flag);
            rootPrt = deletar(rootPrt, informacao);
            cout << profundidade << endl;
            if(pai != NULL)
                rootPrt = rotacionar(rootPrt, pai, profundidade -1, pai->informacao);
        }

        else{
            break;
        }

    }
}