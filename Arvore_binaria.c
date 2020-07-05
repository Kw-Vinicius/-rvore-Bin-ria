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
void Print(Node *root);
void Free(Node *root);

// ----------------------------------- MAIN ---------------------------------

int main(void)
{
    int op = -1;
    int valor;
    int result;
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
                Print(root);
                printf("\n");
                sleep(2);
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
        if(item > root->item)
        {
            root->right = Insert(root->right,item);
        }else if(item < root->item)
        {
            root->left = Insert(root->left,item);
        }
    }
    return root;
}

void Print(Node *root)
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
        Node *aux = root;
        while(aux->left != NULL)
        {
            aux = aux ->left;
        }
        return aux;
    }
}

Node *Remove(Node *root,int item)
{
    if(root != NULL){
        if(root->item < item)
        {
            root->right = Remove(root->right, item);
        }else if(root->item > item)
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
                Node *aux = Min(root->right);
                int valor = aux->item;
                root->right  = Remove(root->right,valor);
                root->item = valor;
            }
        }
        return root;
    }
    return NULL;
}

// ---------------------------------------------------------------------------