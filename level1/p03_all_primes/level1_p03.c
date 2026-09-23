#include <stdio.h>
#include <time.h>

int Prime(int x, int known[], int num)
{
	int ret = 1;
	int i;
	for(i=0;i<num;i++){
		if(x%known[i]==0){
			ret = 0;
			break;
		}
	}
	return ret;
}


int main()
{
	const int number = 167;
	int prime[number];
	prime[0] = 2;
	int count = 1;
	int i = 3;
	
	clock_t time1=clock(); 


	while(count<=number){
		if (Prime(i,prime,count)){
			prime[count++]=i;
		}
		i++;
	}
	
    int c=0; 
	for (i = 0; i < count; i++){
		c++;
        printf("%d\t", prime[i]);
        if (c%10==0){
        	printf("\n");
		} 
	}
	printf("\n");

	clock_t time2=clock();
	double period = (double)(time2 - time1) / CLOCKS_PER_SEC;


	printf("ÓÃÊ±%fÃë\n", period);

    return 0;
		
}
 

