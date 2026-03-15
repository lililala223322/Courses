#include<stdio.h>
#include<math.h>

int min(int a,int b)
{
    return a<b? a:b;
}


void Add_36 (int *a,int *b,char *C)
{
    int c[12]={0};

    for (int i = 0; (a[i] || b[i]) && i<10 ; i++)
    {
        c[i] = a[i] + b[i];
    }
    
    int m;

    for (int i = 0 ; i<12 ; i++)
    {
        if ( c[i-1] && !c[i] ) m=i-1;

        if (c[i]>35) {
            int n = floor(c[i]/36);
            c[i] -= n*36;
            c[i+1] += n;
        }

        if(c[i]<10) C[i] = c[i]+48;
        else        C[i] = c[i]+55;

    }

    for (int i = 0 , j = m ; i < j; )
    {
        int t=C[i];
        C[i++]=C[j];
        C[j--]=t;
    }

    C[m+1]='\0';
    
    return;
}

void initialize(int *a,int *b,char *A,char *B)
{
    for (int i=0; i < 10 && A[i] ;)
    {
        if (A[i]>64) a[i] = A[i]-55;
        else         a[i] = A[i]-48;
        i++;
        a[10]=i-1;
    }

    for (int i = 0 , j = a[10] ; i < j; )
    {
        int t=a[i];
        a[i++]=a[j];
        a[j--]=t;
    }
    

    for (int i=0; i < 10 && B[i] ;)
    {
        if (B[i]>64) b[i] = B[i]-55;
        else         b[i] = B[i]-48;
        i++;
        b[10]=i-1;
    }

    for (int i = 0 , j = b[10] ; i < j; )
    {
        int t=b[i];
        b[i++]=b[j];
        b[j--]=t;
    }
}

int main()
{
    char A[11]={0} , B[11]={0} , C[12]={0};

    scanf("%s",A);
    scanf("%s",B);

    int  a[11]={0} , b[11]={0} ;

    initialize(a,b,A,B);

    Add_36(a,b,C);

    printf("%s",C);
}