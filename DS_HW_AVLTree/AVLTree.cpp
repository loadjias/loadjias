#include <stdio.h>
#include <stdlib.h>

#define LH +1
#define EH 0
#define RH -1

typedef int Status;
typedef int Elemtype;
typedef struct BSTNode {//树结点
    Elemtype data;
    int bf;//平衡因子
    struct BSTNode* lchild, * rchild;
} BSTNode, * BSTree;
void R_Rotate(BSTree& p) {//右单旋
    BSTree lc;
    lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}
void L_Rotate(BSTree& p) {//左单旋
    BSTree rc;
    rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}
void L_balance(BSTree& T, int pa) {//左平衡
    BSTree lc, rd;
    lc = T->lchild;
    switch (lc->bf)
    {
    case LH:
        T->bf = lc->bf = EH;
        R_Rotate(T);
        break;
    case EH:
        if (pa)
        {
            T->bf = EH;
            lc->bf = EH;
            R_Rotate(T);
            break;
        }
        else
            break;
    case RH:
        rd = lc->rchild;
        switch (rd->bf) {
        case LH:
            T->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            T->bf = lc->bf = EH;
            break;
        case RH:
            T->bf = EH;
            lc->bf = LH;
            break;
        }
        rd->bf = EH;
        L_Rotate(T->lchild);
        R_Rotate(T);
        break;
    default:
        break;
    }
}
void R_balance(BSTree& T, int pa) {//右平衡
    BSTree rc, ld;
    rc = T->rchild;
    switch (rc->bf)
    {
    case RH:
        T->bf = rc->bf = EH;
        L_Rotate(T);
        break;
    case EH:
        if (pa)
        {
            T->bf = EH;
            rc->bf = EH;
            L_Rotate(T);
            break;
        }
        else
            break;
    case LH:
        ld = rc->lchild;
        switch (ld->bf) {
        case LH:
            T->bf = RH;
            rc->bf = EH;
            break;
        case EH:
            T->bf = rc->bf = EH;
            break;
        case RH:
            T->bf = EH;
            rc->bf = LH;
            break;
        }
        ld->bf = EH;
        R_Rotate(T->rchild);
        L_Rotate(T);
        break;
    default:
        break;
    }
}
void Ex_Delete(BSTree& T, BSTree& q, BSTree& s, int& shorter) {
    //删除的辅助函数：交换待删除节点与其中序前驱并执行删除操作
    if (s->rchild) {
        Ex_Delete(T, s, s->rchild, shorter);
        if (shorter)
            switch (s->bf) {
            case EH:
                s->bf = LH;
                shorter = 0;
                break;
            case RH:
                s->bf = EH;
                shorter = 1;
                break;
            case LH:
                L_balance(s, 1);
                shorter = 0;
                break;
            }
        return;
    }
    T->data = s->data;
    if (q != T)
        q->rchild = s->lchild;
    else
        q->lchild = s->lchild;
    shorter = 1;
}
Status InsertAVL(BSTree& T, Elemtype e, int& taller) {//插入
    if (!T) {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->data = e;
        T->lchild = T->rchild = NULL;
        T->bf = EH;
        taller = 1;
    }
    else {
        if (e == T->data) {
            taller = 0;
            return 0;
        }
        if (e < T->data) {
            if (!InsertAVL(T->lchild, e, taller))
            {
                return 0;
            }
            if (taller)
                switch (T->bf)
                {
                case LH:
                    L_balance(T, 0);
                    taller = 0;
                    break;
                case EH:
                    T->bf = LH;
                    taller = 1;
                    break;
                case RH:
                    T->bf = EH;
                    taller = 0;
                    break;
                default:
                    break;
                }
        }
        else {
            if (!InsertAVL(T->rchild, e, taller))
            {
                return 0;
            }
            if (taller)
                switch (T->bf)
                {
                case LH:
                    T->bf = EH;
                    taller = 0;
                    break;
                case EH:
                    T->bf = RH;
                    taller = 1;
                    break;
                case RH:
                    R_balance(T, 0);
                    taller = 0;
                    break;
                default:
                    break;
                }
        }
    }
    return 1;
}
Status DeleteAVL(BSTree& T, Elemtype e, int& shorter) {//删除
    shorter = 1;
    int sign = 0;
    BSTree p, t;
    BSTree After;
    Elemtype k;
    if (T == NULL)
        return 0;
    if (e < T->data)
    {
        sign = DeleteAVL(T->lchild, e, shorter);
        if (shorter)
            switch (T->bf)
            {
            case LH:
                T->bf = EH;
                shorter = 1;
                break;
            case EH:
                T->bf = RH;
                shorter = 0;
            case RH:
                R_balance(T, 1);
                shorter = 0;
                break;
            default:
                break;
            }
        return sign;
    }
    else if (e > T->data)
    {
        sign = DeleteAVL(T->rchild, e, shorter);
        if (shorter)
            switch (T->bf) {
            case EH:
                T->bf = LH;
                shorter = 0;
                break;
            case RH:
                T->bf = EH;
                shorter = 1;
                break;
            case LH:
                L_balance(T, 1);
                shorter = 0;
                break;
            }
        return sign;
    }
    else//相等
    {
        //如果被删结点x最多只有一个子女，可做简单删除
        if (!T->rchild)
        {
            p = T;
            T = T->lchild;
            free(p);
            shorter = 1;
        }
        else if (!T->lchild)
        {
            p = T;
            T = T->rchild;
            free(p);
            shorter = 1;
        }
        else//有两个子女的情况
        {
            Ex_Delete(T, T, T->lchild, shorter);
            if (shorter)
            switch (T->bf)
                {
                    case EH:
                        T->bf = RH;
                        shorter = 0;
                        break;
                    case LH:
                        T->bf = EH;
                        shorter = 1;
                        break;
                    case RH:
                        R_balance(T, 1);
                        shorter = 0;
                        break;
                    }

        }

    }
    return 1;
}
void merge(BSTree& T1, BSTree& T2) {//合并
    int taller = 0;
    if (!T2)
        return;
    merge(T1, T2->lchild);
    InsertAVL(T1, T2->data, taller);
    merge(T1, T2->rchild);
}
void split(BSTree T, Elemtype e, BSTree& T1, BSTree& T2) {
    int taller = 0;
    if (!T)
        return;
    split(T->lchild, e, T1, T2);
    if (T->data > e)
        InsertAVL(T2, T->data, taller);
    else
        InsertAVL(T1, T->data, taller);
    split(T->rchild, e, T1, T2);
}
void ShowTable(BSTree head, int level) {//遍历并生成凹入表
    //打印当前结点元素
    for (int i = 0; i < level; i++)
        printf("-");
    printf("%d\n", head->data);
    //判断是否有左孩子
    if (head->lchild)
        ShowTable(head->lchild, level + 1);
    //判断右孩子
    if (head->rchild)
        ShowTable(head->rchild, level + 1);
}
void CreateAVL(BSTree& T) {
    int num, i, e, taller = 0;
    printf("请输入结点数：\n");
    scanf_s("%d",&num);
    printf("按序输入节点的值.\n");
    for (i = 0; i < num; i++) 
    {
        //printf("输入第%d个节点的值.", i + 1);
        scanf_s("%d", &e);
        InsertAVL(T, e, taller);
    }
}
Status SearchAVL(BSTree T, Elemtype e) {
    if (!T)
        return 0;
    else if (e == T->data)
        return 1;
    else if (e < T->data)
        return SearchAVL(T->lchild, e);
    else
        return SearchAVL(T->rchild, e);
}
int main(void)
{
    int i,op,taller = 0;
    int e,t = 0;
    BSTree T1 = NULL;
    BSTree T2 = NULL;
    BSTree t1, t2;
    t1 = NULL; t2 = NULL;
    while (1)
    {
        system("cls");
        printf("----------平衡二叉树操作的演示----------\n");
        printf("T1树\n");
        if (!T1)
            printf("当前为空树\n\n");
        else 
            ShowTable(T1, 0);
        printf("T2树\n");
        if (!T2)
            printf("当前为空树\n\n");
        else
            ShowTable(T2, 0);
        printf("\n");
        printf("操作说明:\n");
        printf("T1操作:1.创立 2.插入 3.查找 4.删除 5.分裂\n");
        printf("T2操作:6.创立 7.插入 8.查找 9.删除 10.分裂\n");
        printf("11.合并两树");
        printf("\n");
        printf("输入你要进展的操作：");
        scanf_s("%d", &op);
        switch (op)
        {
            case 1:
                CreateAVL(T1);
                break;
            case 2:
                printf("请输入要插入关键字的值");
                scanf_s("%d", &e);
                InsertAVL(T1, e, taller);
                break;
            case 3:
                printf("请输入要查找关键字的值");
                scanf_s("%d", &e);
                if (SearchAVL(T1, e))
                    printf("查找成功！\n");
                else
                    printf("查找失败！\n");
                system("pause");
            case 4:
                printf("请输入要删除关键字的值");
                scanf_s("%d", &e);
                if (DeleteAVL(T1, e, t))
                    printf("删除成功！\n");
                else
                    printf("删除失败！\n");
                system("pause");
                break;
            case 5:
                t1 = NULL; t2 = NULL;
                printf("请输入要中间值字的值");
                scanf_s("%d", &e);
                split(T1, e, t1, t2);
                T1 = t1;
                T2 = t2;
                break;
            case 6:
                CreateAVL(T2);
                break;
            case 7:
                printf("请输入要插入关键字的值");
                scanf_s("%d", &e);
                InsertAVL(T2, e, taller);
                break;
            case 8:
                printf("请输入要查找关键字的值");
                scanf_s("%d", &e);
                if (SearchAVL(T2, e))
                    printf("查找成功！\n");
                else
                    printf("查找失败！\n");
                system("pause");
            case 9:
                printf("请输入要删除关键字的值");
                scanf_s("%d", &e);
                if (DeleteAVL(T2, e, t))
                    printf("删除成功！\n");
                else
                    printf("删除失败！\n");
                system("pause");
            case 10:
                t1 = NULL; t2 = NULL;
                printf("请输入要中间值字的值");
                scanf_s("%d", &e);
                split(T1, e, t1, t2);
                T1 = t1;
                T2 = t2;
            case 11:
                merge(T1, T2);
                T2 = NULL;
                printf("合并成功，按任意键返回");
                system("pause");
                break;
            default:
                break;
        }
        getchar();
    }


    return 0;
}



