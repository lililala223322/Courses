#include<stdio.h>
#include<string.h>

int main()
{
    {//数据库
        const char s[27][20]; 
        s[1] = "one",
        s[2] = "two",
        s[3] = "three",
        s[4] = "four",
        s[5] = "five",
        s[6] = "six",
        s[7] = "seven",
        s[8] = "eight",
        s[9] = "nine",
        s[10] = "ten",
        s[11] = "eleven",
        s[12] = "twelve",
        s[13] = "thirteen",
        s[14] = "fourteen",
        s[15] = "fifteen",
        s[16] = "sixteen",
        s[17] = "seventeen",
        s[18] = "eighteen",
        s[19] = "nineteen",
        s[20] = "twenty",
        s[21] = "thirty",
        s[22] = "forty",
        s[23] = "fifty",
        s[24] = "sixty",
        s[25] = "seventy",
        s[26] = "eighty",
        s[27] = "ninty";
    }

    char a[20]={0} , b[20]={0};

    for (int i = 0 , j = -1 ; j ; i++)
    {
        int n1;
        switch (j)
        {
        case -1:a[i] = getchar(); 
                if (a[i]==32) {a[i] = 0 ; j = 1 ; n1 = i+1 ;}
                break;

        case 1: b[i-n1] = getchar(); 
                if (b[i-n1]==10) {b[i-n1] = 0 ; j = 0 ;}
                break;
        }
    }


}