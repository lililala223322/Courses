#include<stdio.h>
#include<string.h>

struct tagStudent {
    char id[11];
    char name[31];
    int score;
};

int main()
{
    int n;
    scanf("%d",&n);
    struct tagStudent ST[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            ST[i].name[j]=0;
        }
        
        scanf("%s %s %d",&ST[i].id,&ST[i].name,&ST[i].score);
    }

    for (int i=0;i<n;i++) {
      for (int j=0;j<n-i;j++) { 
        if (ST[i].score < ST[i+j].score || (ST[i].score == ST[i+j].score && strcmp(ST[i].id,ST[i+j].id)>0) ) 
        {
            struct tagStudent t = ST[i];
            ST[i] = ST[i+j];
            ST[i+j] = t;
        }
      }    
   }

   for (int i = 0; i < n; i++)
   {
    printf("%s %s %d\n",ST[i].id,ST[i].name,ST[i].score);
   }
}