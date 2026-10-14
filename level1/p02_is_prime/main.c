#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    int state=1;
    scanf("%d",&n);

    if (n<=1){
        printf("%d不是素数\n",n);
        return 0;
    }

    for(int i=2;i<=sqrt(n);i++){
        if (n%i==0){
            state=0;
            break;
        }
    }

    if (state==1){
        printf("%d是素数\n",n);
    }else{
        printf("%d不是素数\n",n);
    }

    return 0;
}