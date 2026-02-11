#include "inverted.h"

void save_database(M_node *HT[])
{
    char database[20];
    printf(GREEN"Enter the file name to store the data :"RESET);
    scanf("%s",database);
    char *ptr=strstr(database,".");
        if(ptr){
            if(strcmp(ptr,".txt")==0){
                FILE *fp=fopen(database,"w");
                fprintf(fp,"#INDEX;WORD;FILECOUNT;FILENAME;WORDCOUNT\n");
                for(int i = 0; i < 27; i++)
                {
                    if(HT[i] == NULL)
                        continue;

                    M_node *mtemp = HT[i];

                    // Traverse main nodes (words)
                    while(mtemp)
                    {
                        S_node *stemp = mtemp->sub_link;
                        fprintf(fp,"#%d;%s;%d;",i,mtemp->word,mtemp->file_count);
                        // Traverse sub nodes (files)
                        while(stemp)
                        {
                            fprintf(fp,"%s;%d;",stemp->filename,stemp->word_count);
                            stemp = stemp->sub_link;
                        }
                        // Separator line after each word
                        fprintf(fp,"#\n");

                        mtemp = mtemp->main_link;
                    }
                }
                fclose(fp);
                printf(GREEN"DATABASE SAVED SUCCESSFULLY\n"RESET);
                return;

            }
            else{
                printf(RED"ONLY .txt ARE ACCEPTED\n"RESET);
                return ;
            }
        }
        printf(RED"EXTENTION OF FILE IS NEEDED\n"RESET);
         
}