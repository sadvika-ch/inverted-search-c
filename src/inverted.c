#include "inverted.h"

/* Function definitions */
#include "inverted.h"

/* Function definitions */
void validate_files(char *argv[], F_node **head){
    int i=1;
    while(argv[i]){
        char *ptr=strstr(argv[i],".txt");
        if(ptr){
            if(strcmp(ptr,".txt")==0){
                FILE *fptr=fopen(argv[i],"r");
                if(fptr!=NULL){
                    fseek(fptr,0,SEEK_END);
                    int size=ftell(fptr);
                    if(size!=0){
                        //printf("Valid File with extension,");
                        if(check_duplicates(*head,argv[i])==FAILURE){
                            insert_last(head,argv[i]);
                            printf(GREEN"INFO : Successful: inserting file name %s into file linked list \n"RESET,argv[i]);
                        }
                        else{
                            printf(RED"INFO :%s => This file is repeated,so it will not store into the sll\n"RESET,argv[i]);
                        }
                    }
                    else{
                        printf(RED"INFO: %s => This file is empty\n"RESET,argv[i]);
                    }
                    fclose(fptr);
                }
                else{
                    printf(RED"INFO :%s=>Unable to open file\n"RESET,argv[i]);
                }
               
            }
            else {
                printf(RED"INFO :%s =>This file is not a .txt file\n"RESET,argv[i]);
            }
        }
        else{
            printf(RED"INFO : %s =>This file has without extension\n"RESET,argv[i]);
        }
        i++;
    }
    printf("\n");
    print_filenames(*head);
}

int check_duplicates(F_node *head, char *f_name){
    F_node *temp=head;
    while(temp){
        if(strcmp(temp->f_name,f_name)==0){
            return SUCCESS;
        }
        temp=temp->link;
    }
    return FAILURE;
}
int insert_last(F_node **head, char *f_name){
    F_node *new = malloc(sizeof(F_node));
    strcpy(new->f_name,f_name);
    new->link = NULL;
    if((*head)==NULL){
        *head=new;
        return SUCCESS;
    }
    F_node *temp=*head;
    
    while(temp->link!=NULL){
        temp=temp->link;
    }
    temp->link = new;
    return SUCCESS;
}

int print_filenames(F_node *head){
    F_node *temp=head;
    printf(PURPLE"File list:\n");
    while(temp){
        printf("%s\n",temp->f_name);
        temp=temp->link;
    }
    printf("\n"RESET);
    return SUCCESS;
}