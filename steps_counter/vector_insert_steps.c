#include <stdio.h> 
#include <stdlib.h>
#include<string.h>
#include "ADTVector.h"
int* create_int(int i)  {
    int* p;
    p=malloc(sizeof(*p));
    *p=i;
    return p;
}
int main(int argc,char *argv[])  {
    int N=1000;
    char flag;
    int sum;
    if (strcmp(argv[1],"armortized")==0)  {
        flag=1;
    }
    else if (strcmp(argv[1],"real")==0)  {
        flag=0;
    }
    else  {
        printf("Error \n");
        return 0;
    }
    sum=0;
    int n=0;
    Vector vec=vector_create(0,free);
    for (int i=1;i<N;i++)  {
        vector_insert_last(vec,create_int(i)); 
        n=vector_steps(vec);
        sum=sum+n;
        if (flag==1)  {
            printf("%d \n",sum/i);
        }
        else if (flag==0)  {
            printf("%d \n",n);
        }
    }
    vector_destroy(vec);
}

