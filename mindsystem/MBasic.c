#include "MBasic.h"

//复制的长度由len确定
char* Mstrcpy(char* des, char*source, int len)
{
    char* r=des;
    if(des==NULL || source==NULL)
        return NULL;
    int i=0;
    for(i=0; i<len; i++)
    {
        *des++ = *source++;
    }  
    return r; 
}