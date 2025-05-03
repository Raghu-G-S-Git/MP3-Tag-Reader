#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "headers.h"

//Based on character type entered to edit particular type of data, call copy function with its code
void edit(FILE *fptr,char ch, char *song, char *new_content)
{
    FILE *newf = fopen("new_file.mp3","w");
    if(fptr == NULL)
    {
        printf("\n***Failed to open the file***\n");
        return ;
    }

    char *arr[6] = {"TIT2","TPE1","TALB","TYER","TCON","TCOM"}; // 2D Array to send diffrent frame header code for diffrent type of content

    switch(ch)
    {
        case 't':
            copy(fptr,newf,arr[0],new_content,song);
            break;
        case 'a':
            copy(fptr,newf,arr[1],new_content,song);
            break;
        case 'A':
            copy(fptr,newf,arr[2],new_content,song);
            break;
        case 'y':
            copy(fptr,newf,arr[3],new_content,song);
            break;
        case 'c':
            copy(fptr,newf,arr[4],new_content,song);
            break;
        case 'm':
            copy(fptr,newf,arr[5],new_content,song);
            break;
        default :
            error_msg();           
    }

}

//copy function rewrites the hole file by copying the data to new file with the changes made 
void copy(FILE *fptr, FILE *newf, char *arr,char *new_content, char *song)
{
    char name[50],old[2000],ch;
    int position,size,new_size = (strlen(new_content)+1);
    
    fseek(fptr,10,SEEK_SET);            //Move old file pointer to 11th position where frame headers starts
    do 
    {
        size = search(fptr,name,arr);
    }while(size == 0);                  //search for the frame headers code until the type matches

    fseek(fptr,-(size+7),SEEK_CUR);     //Bring the pointer to the position to which the data from begining must be copyed
    position = ftell(fptr);
    
    rewind(fptr);                       //Bring back the pointer to begining of the file to start copying data

    fread(old,(position+1),1,fptr);     //Read the data from old file to a variable till to position
    fwrite(old,(position+1),1,newf);    //Copy or Write the same to the new file 

    swap((char*)&new_size);             //Convert size of new content data to Big endian 
    fwrite(&new_size,4,1,newf);
    //Copy the flag and null characters to new file
    fseek(fptr,4,SEEK_CUR);

    fread(old,3,1,fptr);
    fwrite(old,3,1,newf);
    
    fwrite(new_content,strlen(new_content),1,newf); //write the new content to new file
    //Skip the position of old file pointer of old content and copy remaining data to new file
    fseek(fptr,size-1,SEEK_CUR);
    while(1)
    {
        if(!(fread(&ch,1,1,fptr)))
            break;
        fwrite(&ch,1,1,newf);
    }

    fclose(newf);

    remove(song);                           //After editing and copying entire data remove old file

    if (rename("new_file.mp3", song) == 0)  //After removing old file rename the new file same as old file and validate
    {
        FILE *newf = fopen(song, "r");
        if(newf == NULL)
        {
            printf("\n***Failed to open the file***\n");
            return ;
        }
        fseek(newf,10,SEEK_SET);
        view(newf);
    }  
    else
    {
        printf("\n***Error renaming file***\n\n");
    }
}

//View function is used to display the content
void view(FILE *fptr)
{
    int size;
    char content[50];
    char *arr[6] = {"TIT2","TPE1","TALB","TYER","TCON","TCOM"};
    char *type[6] = {"TITLE","ARTIST","ALBUM","YEAR","CONTENT","COMPOSER"};
    for(int i=0; i<6; i++)
    {
            printf("\n");
            size = search(fptr,content,arr[i]);    //Based on the Frame header code found display content accordingly
            if(size)
                printf("%s\t\t: ",type[i]); print(size,content);
    }
}

//This funtion contains logic to convert 4 Bytes of data from Big Endian to Little or vice versa
void swap(char *num)
{
    int i=0;
    while(i < 2)
    {
        char temp = num[i];
        num[i] = num[3-i];
        num[3-i] = temp;
        i++;
    }
}

//This function searches the header file code and returns content size 
int search(FILE *fptr, char *content, char *header)
{
    int size;
    char mode[5];

    fseek(fptr,0,SEEK_CUR);     
    fread(mode,4,1,fptr);           //Read 4 bytes of size data of Big Endian tpye

    fread(&size,4,1,fptr);      
    swap((char*)&size);             //Convert the size data to Little Endian type

    fseek(fptr,3,SEEK_CUR);         //Skip the position of pointer from flag and null character
    fread(content,size-1,1,fptr);   //neglecting null character read the content
    if(strcmp(mode,header) != 0)    //If the header file is not found return 0
    {
        return 0;
    }
    return size;  
}

//This function prints the content data character by character
void print(int size, char *str)
{
    int i=0;
    while(i<size-1)
    {
        printf("%c",str[i]);
        i++;
    }
    printf("\n");
}

void error_msg(void)
{
    printf("\n*******************************************************************************\n");
    printf("ERROR : INVALID ARGUMENTS.\nUSAGE:\n");
    printf("To VIEW pass like : ./a.out -v <mp3filename>\n");
    printf("To EDIT pass like : ./a.out -e -t/-a/-A/-y/-c/-m <new_content> <mp3filename>\n");
    printf("\t-t  --->   Modifies TITLE tag\n");
    printf("\t-a  --->   Modifies ARTIST tag\n");
    printf("\t-A  --->   Modifies ALBUM tag\n");
    printf("\t-y  --->   Modifies YEAR tag\n");
    printf("\t-c  --->   Modifies CONTENT tag\n");
    printf("\t-m  --->   Modifies COMPOSER tag\n");
    printf("\n*******************************************************************************\n\n");

    exit(-1);
}