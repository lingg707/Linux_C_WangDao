#include <stdio.h>
#include <unistd.h>
int main()
{ 
    if(fork()==0)
    {       
        if(execlp("/usr/bin/env","env",NULL)<0)    
        {   
            perror("execlp error!");      
            return -1 ;
        }  
    }
    return 0 ;
}
