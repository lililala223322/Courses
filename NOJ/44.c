#include<stdio.h>
#include<math.h>

int Package(int n[])
{ 
    int pre_pack[2]={0},
        pack[3]={0};

    //5+1
    pre_pack[0] += 11*n[4];

    //4+2g
    pre_pack[1] += 5*n[3];
    if (pre_pack[1]>n[1]) {
        pre_pack[0] += (pre_pack[1]-n[1])*4 ;
        pre_pack[1]=n[1];
    }

    //3
    int empty3 = 4*ceil(n[2]/4.0)-n[2];
    pack[2]=ceil(n[2]/4.0);

    switch (empty3){

        case 3: pre_pack[1] += 5*empty3;

                if ( pre_pack[1] > n[1] ) {
                pre_pack[0] += (pre_pack[1]-n[1])*4 ;
                pre_pack[1]=n[1];
                }

                else {pre_pack[0] += 7*empty3;}
                break;

        case 2: pre_pack[1] += 3*empty3;

                if ( pre_pack[1] > n[1] ) {
                pre_pack[0] += (pre_pack[1]-n[1])*4 ;
                pre_pack[1]=n[1];
                }

                else {pre_pack[0] += 6*empty3;}
                break;

        case 1: pre_pack[1] += 1*empty3;

                if ( pre_pack[1] > n[1] ) {
                pre_pack[0] += (pre_pack[1]-n[1])*4 ;
                pre_pack[1]=n[1];
                }

                else {pre_pack[0] += 5*empty3;}
                break;
    }

    if ( n[1] > pre_pack[1] ) {
        pack[1] = ceil((n[1]-pre_pack[1])/9.0);
        pre_pack[0] += 4*pack[1]-n[1]-pre_pack[1];
    }

    if ( n[0] > pre_pack[0] ){
        pack[0] = ceil((n[0]-pre_pack[0])/36.0);
    }
    
    return n[5]+n[4]+n[3]+pack[2]+pack[1]+pack[0];
}

int main()
{
    int n[6] = {0}   ,
        m[100] = {0} ;

    for (int i = 0; 1 ; i++)
    {
        for (int j = 0; j < 6; j++)
        {
                scanf("%d",&n[j]);
        }

        if ( !(n[0]+n[1]+n[2]+n[3]+n[4]+n[5]) ) break;

        m[i] = Package(n);
    }
    
    for(int i = 0; 1 ;i++)
    {
        if (m[i]) printf("%d\n",m[i]);
        else break;
    }
}