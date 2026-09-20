#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int main()
{
    int x=0,d=1;
    int i;
    char s[]="A";
    
    while(1)
	{
    	system("cls");
    	
        for(i=0;i<x;i++){
			putchar(' ');
		}
			
        printf("%s",s);
        
        for(i=0; i<119-x;i++){
			putchar(' ');
		}
		
        x+=d;
        
        if(x>=120)
		{
            x=119;
            d=-1;
        }else if(x< 0)
		{
            x=0;
            d=1;
        }
		
        Sleep(100);
    }
    return 0;
}


