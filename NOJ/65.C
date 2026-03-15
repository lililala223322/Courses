#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void itoa_gugugu(int num,char s[])
{
    while (num>=16)
    {
        num -= 16;
        s[1]++;
        if ( s[1]==16 )
        {
            s[1] = 0;
            s[2]++;
        }
    }

    s[0] = num;
    if (s[1])
        if ( s[2] )
        {
            int t = s[0];
            s[0] = s[2];
            s[2] = t;
        }
        else
        {
            int t = s[0];
            s[0] = s[1];
            s[1] = t;
        }
    s[0] +=48;
    s[1] +=48;
    s[2] +=48;
    return ;
}

int check_sum(char str[])
{
    int checksum1 = str[1];
    char checksum2[3]={0};

    for (int i = 2 ; 1 ; i++)
    {
        
        if ( str[i] != '*' ) 
        {
                checksum1 ^= str[i];
                continue;
        }

        else 
        { 
                checksum1 %= 65536; 

                itoa_gugugu(checksum1,checksum2);
                i++;     
        }
        
        for (int k = 0; str[i+k] ; k++)
        {
                if ( str[i+k] != checksum2[k] ) return 1;
        }
            
        return 0;
        
    }
    
}

int main()
{
    char s[100][5] = {0};
    int n = 0;

    while ( 1 )
    {
        const char s1[] = {"$GPRMC"};
        char str[100] = {0} , s2[7]={0};
        scanf("%s",str);

        if (str[0]=='E' && str[1]=='N' && str[2] =='D') break;

        //不是GPRMC就进入下一轮
        {
            for (int i = 0; i <= 5; i++)
            {
                s2[i] = str[i];
            }

            if (strcmp(s2,s1)) continue;
        }

        //检查校验值
        if (check_sum(str)) {s[n][0]='*'; n++ ; continue;}

        {
            char hour1[2] ={str[7],str[8]};
            int hour2 = atoi(hour1);
            hour2 += 8 ;
            if (hour2 >= 24) hour2-=24;
            s[n][0] = hour2;
            s[n][1] = str[9];
            s[n][2] = str[10];
            s[n][3] = str[11];
            s[n][4] = str[12];
            n++;
        }
    }

    for (int i = 0 ; i < n ; i++ )
    {
        if (s[i][0]=='*') printf("error\n");
        else printf("%d:%c%c:%c%C\n",s[i][0],s[i][1],s[i][2],s[i][3],s[i][4]);
    }

}