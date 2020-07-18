#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node{
    int item;
    struct node *left;
    struct node *right;
}Node;

// ------------------------------- Protótipos -------------------------------

Node *Initialize();
Node *Insert(Node *root, int item);
Node *Min(Node *root);
Node *Remove(Node *root,int item);
Node *Search(Node *root, int item);
Node *level(Node *root,int item,int nivel);
void Print(Node *root);
void Free(Node *root);

// ----------------------------------- MAIN ---------------------------------

int main(void)
{
    int op = -1;
    int valor;
    int result;
    int nivel = 0;
    Node *aux;
    Node *root = Initialize();

    aux = root;

    while(op!=0)
    {
        system("clear");
        printf("0 - Sair\n");
        printf("1 - Inserir Elemento\n");
        printf("2 - Remover Elemento\n");
        printf("3 - Verificar Elemento\n");
        printf("4 - Exibir a árvore\n");
        printf("5 - Verificar nível do elemento buscado\n");
        printf("Digite uma opção: \n");
        scanf("%d",&op);

        switch(op){
            case 0 :
                break;
            case 1: 
                system("clear");
                printf("Digite um valor para inserir na árvore: \n");
                scanf("%d",&valor);
                root = Insert(root,valor);
                break;
            case 2:
                system("clear");
                printf("Digite um valor para remover da árvore: \n");
                scanf("%d",&valor);
                root = Remove(root,valor);
                break;
            case 3:
                system("clear");
                printf("Digite um valor para verificar na árvore: \n");
                scanf("%d",&valor);
                aux = Search(root,valor);
                if(aux == NULL)
                    printf(">> Elemento %d não encontrado\n",valor);
                else 
                    printf(">> Elemento %d encontrado\n",valor);
                sleep(1.5);
                break;
            case 4:  
                system("clear");
                if(root == NULL) printf("Lista vazia nada a exibir!");
                else{
                Print(root);
                }
                printf("\n");
                sleep(2);
                break;
            case 5:
                system("clear");
                printf("Digite um valor da árvore para testar seu nível: \n");
                scanf("%d",&valor);
                aux = level(root,valor,nivel);
                sleep(2.5);
                break;
            default:
                printf("Escolha uma opção válida! \n");
                break;
        }       
    }
    Free(root);
}

//  --------------------------- Funções --------------------------------------------

Node *Initialize(){
    return NULL;
}

Node *Insert(Node *root, int item)
{
    if(root == NULL){
        Node *aux = (Node*)malloc(sizeof(Node));
        aux->item = item;
        aux->left = NULL;
        aux->right = NULL;
        return aux;
    } else{
        if(item == root->item)
        {
            printf("Elemento %d é repetido, não será inserido!\n",item);
            sleep(2);

        }else if(item > root->item)
        {
            root->right = Insert(root->right,item);
        }else if(item < root->item)
        {
            root->left = Insert(root->left,item);
        }
    }
    return root;
}

void Print(Node *root)                  // Printando in-ordem (ordem crescente)
{
    if(root != NULL){
        printf("%d ",root->item);
        Print(root->left);
        Print(root->right);
    }
}

void Free(Node *root)
{
    if(root != NULL){
        Free(root->left);
        Free(root->right);
        free(root);
    }
}

Node *Search(Node *root, int item)
{
   if(root != NULL){
        if(root->item == item) return root;
        else{
            if (item > root->item) return Search(root->right,item);
            else return Search(root->left,item);
        }
    }
    return NULL;
}

Node *Min(Node *root)
{
    if(root != NULL){
        Node *aux = root->left;
        while(aux->right != NULL)
        {
            aux = aux ->right;
        }
        return aux;
    }
}

Node *Remove(Node *root,int item)
{
    if(root != NULL){
        if(item > root->item )
        {
            root->right = Remove(root->right, item);
        }else if(item < root->item )
        {
            root->left = Remove(root->left, item);
        }else 
        {
            if(root->left == NULL && root->right == NULL)
            {
                free(root);
                return NULL;

            } else if(root->left == NULL && root->right != NULL)
            {
                Node *aux = root->right;
                free(root);
                return aux;

            }else if(root->left != NULL && root->right == NULL)
            {
                Node *aux = root->left;
                free(root);
                return aux;
            }
            else
            {
                Node *aux = Min(root);
                int valor = aux->item;
                root  = Remove(root,valor);
                root->item = valor;
            }
        }
        return root;
    }
    return NULL;
}

Node *level(Node *root,int item,int nivel)
{
     if(root != NULL){
        if(root->item == item) 
            printf(">> Nível: %d\n",nivel);
        else{
            if (item > root->item) return level(root->right,item,nivel+1);
            else return level(root->left,item,nivel+1);
        }
    }
    return NULL;
}

// ---------------------------------------------------------------------------
