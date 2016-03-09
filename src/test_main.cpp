#include <iostream>
#include <stdio.h>
#include "convert_comment.h"
using namespace std;

int main(int argc, char **argv)
{
    FILE *fp_in  = NULL;
    FILE *fp_out = NULL;

    //read the file named "input.c"
    if( (fp_in = fopen("file/input.c","r")) ==NULL) 
    {
        cout<<"Open input.c File Failure!"<<endl;
        return -1;
    }
    
    //write the file named "output.c"
    if((fp_out = fopen("file/output.c","w")) == NULL)
    {
        cout<<"Open output.c File Failure!"<<endl;
        return -1;
    }

    convert_comment(fp_in, fp_out);

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
