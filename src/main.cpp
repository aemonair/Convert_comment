#include <iostream>
#include <stdio.h>
#include "convert_comment.h"
using namespace std;

int main(int argc, char **argv)
{
    FILE *fp_in  = NULL;
    FILE *fp_out = NULL;

    //read the file named "input.c"
    if( (fp_in = fopen(argv[1],"r")) ==NULL) 
    {
        cout<<"Open"<<argv[1]<<File Failure!"<<endl;
        return -1;
    }
    
    //write the file named "output.c"
    if((fp_out = fopen(argv[2],"w")) == NULL)
    {
        cout<<"Open"<<argv[2]<<File Failure!"<<endl;
        return -1;
    }

    convert_comment(fp_in, fp_out);

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
