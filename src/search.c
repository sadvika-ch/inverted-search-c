#include "inverted.h"

void search_database(M_node *HT[])
{
    char word[20];
    printf(GREEN"Enter the word you wanted to search : "RESET);
    scanf("%s",word);
    int index=get_index(word);
    if(HT[index]==NULL){
        printf(RED"NO WORD EXIST\n"RESET);
        return;
    }
    M_node *temp=HT[index];
    while(temp){
        if(strcmp(temp->word,word)==0){
            printf(PINK"Word %s is present %d time in file "RESET,word,temp->file_count);
            S_node *stemp=temp->sub_link;
            while(stemp){
                printf(PINK"%s->%d times  "RESET,stemp->filename,stemp->word_count);
                stemp=stemp->sub_link;
            }
            printf("\n");
            return;
        }
        temp=temp->main_link;
    }
}