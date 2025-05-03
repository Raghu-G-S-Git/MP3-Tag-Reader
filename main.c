/*
    Name : Raghu G s
    Date : 02-05-2025
    Project : MP3 TAG READER
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "headers.h"

//Collect Cmmand Line Arguments for user inputs
int main(int arg_count, char *arg[])
{
    //Validate input arguments 
    if(arg_count != 3 && arg_count != 5)
    {
        error_msg();
    }

    if(arg[1][0] != '-')
    {
        error_msg();
    }

    char song[30], op[3], tag[3], new_content[50],ch;
    strcpy(op, arg[1]);

    //Call the function according to the user input 
    if(op[1] == 'v')
    {    
        strcpy(song, arg[2]);

        FILE *fptr = fopen(song, "r");
        if(fptr == NULL)
        {
            printf("\n***Failed to open the file***\n");
            return 0;
        }
        //Validate if the mp3file is ID3 v2.3 or Not
        char str1[3],str2[3]={'I','D','3'};
        int num;
        fread(str1,3,1,fptr);
        fread(&num,2,1,fptr);
        if(strcmp(str1,str2) != 0 && num != 3)
        {
            printf("\n****Invalid File type, please provide ID3 v2.3 file****\n\n");
            exit(-1);
        }

        fseek(fptr,10,SEEK_SET);

        view(fptr);
    }
    else if(op[1] == 'e')
    {
        strcpy(song, arg[4]);
        strcpy(new_content, arg[3]);
        ch = arg[2][1];

        if(arg[2][0] != '-')
        {
            error_msg();
        }

        FILE *fptr = fopen(song, "r");
        if(fptr == NULL)
        {
            printf("\n***Failed to open the file***\n");
            return 0;
        }
        //Validate if the mp3file is ID3 v2.3 or Not
        char str1[3],str2[3]={'I','D','3'};
        int num;
        fread(str1,3,1,fptr);
        fread(&num,2,1,fptr);
        if(strcmp(str1,str2) != 0 && num != 3)
        {
            printf("\n****Invalid File type, please provide ID3 v2.3 file****\n\n");
            exit(-1);
        }

        fseek(fptr,10,SEEK_SET);
        
        edit(fptr,ch,song,new_content);
    }
    else
    {
        error_msg();        //Error message for invalid input arguments
    }

    return 0;
}