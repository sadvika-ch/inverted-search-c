#include "inverted.h"


int insert_at_first(F_node **head, char * f_name)
{
	F_node *new = malloc(sizeof(F_node));
    strcpy(new->f_name,f_name);
    new->link = NULL;
    if((*head)==NULL){
        *head = new;
    }
    else{
        new->link=*head;
        *head=new;
    }
}
int update_database(M_node *HT[], F_node **head)
{ 
    char file[10];
    printf("Enter a file name : ");
    scanf("%s",file);
    char *ptr=strstr(file,".txt");
        if(ptr){
            if(strcmp(ptr,".txt")==0){
                FILE *fptr=fopen(file,"r");
                if(fptr!=NULL){
                    fseek(fptr,0,SEEK_END);
                    int size=ftell(fptr);
                    if(size!=0){
                        //printf("Valid File with extension,");
                        if(check_duplicates(*head,file)==FAILURE){
                            insert_at_first(head,file);
                            printf(GREEN"INFO : Successful: inserting file name %s into file linked list \n"RESET,file);
                        }
                        else
                            printf(RED"INFO :%s => This file is repeated,so it will not store into the sll\n"RESET,file);
                    }
                    else
                        printf(RED"INFO: %s => This file is empty\n"RESET,file);
                    fclose(fptr);
                }
                else
                    printf(RED"INFO :%s=>Unable to open file\n"RESET,file);
               
            }
            else 
                printf(RED"INFO :%s =>This file is not a .txt file\n"RESET,file);
        }
        else
            printf(RED"INFO : %s =>This file has without extension\n"RESET,file);

    create_database(HT,*head);
    printf("Update successful\n");
    
    }