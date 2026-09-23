#include <stdio.h>
#include <math.h>

int main()
{
	int n,i;
	int state=1;
	scanf("%d",&n);
	
	if (n==1){
		printf("%d不是素数",n);
	}
	
	for(i=2;i<=sqrt(n);i++){
		if (n%i==0){
			state=0;
			break;
		}
	}
	
	if (state==1){
		printf("%d是素数",n);
	}else{
		printf("%d不是素数",n); 
	}
	
	return 0;
}
