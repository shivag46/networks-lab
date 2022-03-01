#include<stdio.h>
#include<math.h>
#include<string.h>

int m,r,tot;

int isPowerOfTwo(int n)
{
    if (n == 0)
        return 0;
    while (n != 1)
    {
        if (n%2 != 0)
            return 0;
        n = n/2;
    }
    return 1;
}

int main(int argc, char **argv){
    m = strlen(argv[1]);
    r = 0;
    while((1<<r) < (m+r+1)) r++;
    tot = m+r;

    char ans[tot+1];

    for(int i=tot,j=m-1;i>=1;i--){
        int idx = tot - i + 1;
        if(isPowerOfTwo(idx)){
            ans[i] = '!';
            continue;
        }
        ans[i] = argv[1][j];
        j--;
    }

    for(int i=1;i<=tot;i++)
        printf("%c",ans[i]);
    printf("\n");

    for(int i=1;i<=r;i++){
        int pos = (1<<(i-1));
        int cnt = 0;
        for(int j=tot;j>=0;j--){
            int idx = tot - j + 1;
            if((pos & idx)>0 && ans[j] == '1')
                cnt++;
        }

        if(cnt%2)
            ans[tot - pos + 1] = '1'; 
        else
            ans[tot - pos + 1] = '0';
    }

    for(int i=1;i<=tot;i++)
        printf("%c",ans[i]);
        printf("\n%d",r);
}