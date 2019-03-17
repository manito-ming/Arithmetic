#include <iostream>
using namespace std;
#define LH 1   //左子树高了
#define EH 0
#define RH -1  //右子树高了
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef struct BiNode{
    int data;
    int bf;
    struct BiNode *lchild, *rchild;
}*BiTree;
//像右旋转
void  R_Rotate(BiTree *p){
    BiTree L;
    L = (*p)->lchild;
    (*p)->lchild = L->rchild;
    L->rchild = (*p);
    *p = L;//此处可以不写吗？不行，以为需要把传进来的指针指向R,因为此时R便是旋转之后的局部平衡树，出去之后整棵树就旋转完毕
}
//像左旋转
void L_Rotate(BiTree *p){
    BiTree R;
    R = (*p)->rchild;
    (*p)->rchild = R->lchild;//把R的左孩子连到p的右结点上,把
    R->lchild = (*p);//因为上面已经将R的左孩子给了P,所以将P这个结点连到R的左结点上，此时完成旋转
    *p = R;//这一步是为了将这个指针指向R，整个就完成了一次旋转
}
//下面是左平衡树，当向左插入结点时，会导致左边失衡,
void LeftBalance(BiTree *T){
    BiTree L , Lr;
    L = (*T)->lchild;
    switch (L->bf)
    {
        case LH:
            (*T)->bf = L->bf = EH;//因为要旋转，旋转完之后便平衡了，所以提前改变bf的数值
            R_Rotate(T);
            break;
        case RH:               ///下面是一种双旋转的情况,因为是左边失衡，但是有局部是右边失衡，所以先将局部失衡改变，然后在向右旋转
            Lr = L->rchild;
            switch (Lr->bf)
            {
                case LH:
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = L->bf = EH;
                    break;
                case RH:                //在此处找到局部失衡的树
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(&(*T)->lchild);//T->rchild失衡,调整局部失衡
            R_Rotate(T);//上面调整完成之后便,T开始向右旋转

    }
}
void RightBalance(BiTree *T){
    BiTree L , Lr;
    L = (*T)->rchild;
    switch (L->bf)
    {
        case RH:
            (*T)->bf = L->bf = EH;
            L_Rotate(T);
            break;
        case LH:
            Lr = L->lchild;
            switch (Lr->bf)
            {
                case LH:  //代表新插入的节点在左孩子
                    (*T)->bf = EH;
                    L->bf = RH;
                    break;
                case EH:
                    (*T)->bf = L->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;///因为这颗树失衡，旋转之后会平衡，所以在此赋值为0
                    L->bf = LH;//并且
                    break;
            }
            Lr->bf = EH;
            R_Rotate(&(*T)->rchild);
            L_Rotate(T);

    }
}
Status InsertAVL(BiTree *T, int e ,int *taller){
    if(!*T)
    {
        *T = (BiTree)malloc(sizeof(BiNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        *taller = TRUE;
    }else
    {
        if (e == (*T)->data)
        {
            *taller = FALSE;
            return FALSE;
        }else if (e < (*T)->data)
        {
            if (!InsertAVL(&(*T)->lchild ,e , taller))//找到了e没有插入，所以i要返回FALSE
            {
                return FALSE;
            }
            if (*taller)///如果taller为真，说明是不平衡的
            {
                switch ((*T)->bf)
                {
                    case LH:
                        LeftBalance(T);
                        *taller = FALSE;
                        break;
                    case EH:
                        (*T)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH:
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                }
            }
        }else if(e > (*T)->data)
        {
            if(!InsertAVL(&(*T)->rchild ,e , taller))
            {
                return TRUE;
            }
            if (*taller)
            {
                switch ((*T)->bf)
                {
                    case LH:
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                    case EH:
                        (*T)->bf = RH;
                        *taller = TRUE;
                        break;
                    case RH:
                        RightBalance(T);
                        *taller = FALSE;
                        break;
                }
            }

        }

    }
    return TRUE;
}
void InOrder(BiTree T){
    if(T)
    {
        InOrder(T->lchild);
        cout<<T->data<<"\t";
        InOrder(T->rchild);
    }
}
void PreOrder(BiTree T){
    if(T)
    {
        cout<<T->data<<"\t";
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
int main() {
int i;
    int a[10] ={3,2,1,4,5,6,7,10,9,8};
    BiTree  T = NULL;
    Status taller;
    for(i= 0; i< 10; i++)
    {
        InsertAVL(&T,a[i],&taller);
    }
    cout<<"中序遍历"<<endl;
    InOrder(T);
    cout<<endl;
    cout<<"先序遍历"<<endl;
    PreOrder(T);
    delete(T);
    return 0;
}