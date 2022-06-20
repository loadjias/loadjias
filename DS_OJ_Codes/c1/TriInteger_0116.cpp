#include<stdio.h>

int main()
{
    int t,n[3];
    scanf("%d %d %d",&n[0],&n[1],&n[2]);
    if(n[1] <= n[2])
    {
        t = n[1];
        n[1] = n[2];
        n[2] = t;
    }
    if(n[0] <= n[1])
    {
        t = n[0];
        n[0] = n[1];
           n[1] = t;
    }
    if(n[1] <= n[2])
    {
        t = n[1];
        n[1] = n[2];
        n[2] = t;
    }
    printf("%d %d %d\n",n[0],n[1],n[2]);
    getchar();
    getchar();
    return 0;
}
