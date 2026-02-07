#include "inverted.h"

void display_database(M_node *HT[])
{
    printf(YELLOW"\n==================== INVERTED INDEX DATABASE ====================\n");
    printf("------------------------------------------------------------------\n");
    printf(PURPLE"Index | Word           | FileCount | File Name        | WordCount\n"RESET);
    printf("------------------------------------------------------------------\n"RESET);

    for(int i = 0; i < 27; i++)
    {
        if(HT[i] == NULL)
            continue;

        M_node *mtemp = HT[i];

        // Traverse main nodes (words)
        while(mtemp)
        {
            S_node *stemp = mtemp->sub_link;
            int first_file = 1;

            // Traverse sub nodes (files)
            while(stemp)
            {
                if(first_file)
                {
                    // First file row (full details)
                    printf(SKYBLUE"%-5d | %-14s | %-9d | %-16s | %-9d\n",i,mtemp->word,mtemp->file_count,stemp->filename,stemp->word_count);
                    first_file = 0;
                }
                else
                {
                    // Additional files (print below)
                    printf("      |                |           | %-16s | %-9d\n"RESET,stemp->filename,stemp->word_count);
                }

                stemp = stemp->sub_link;
            }

            // Separator line after each word
            printf(YELLOW"------------------------------------------------------------------\n"RESET);

            mtemp = mtemp->main_link;
        }
    }
}
