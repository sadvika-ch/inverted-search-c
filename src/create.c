#include "inverted.h"

void create_database(M_node *HT[], F_node *head)
{
    F_node *temp = head;          // File list traversal
    char word[50];                // Buffer for each word

    while (temp)                  // Loop through all files
    {
        FILE *fp = fopen(temp->f_name, "r");   // Open file

        // Read words from file
        while (fscanf(fp, "%s", word) == 1)
        {
            int index = get_index(word);   // Hash index
            M_node *mtemp = HT[index];     // Head of main list at index

            /* ---------------- Case 1: No node at this index ---------------- */
            if (mtemp == NULL)
            {
                // Create main node
                M_node *new_m = malloc(sizeof(M_node));
                strcpy(new_m->word, word);
                new_m->file_count = 1;
                new_m->main_link = NULL;

                // Create sub node
                S_node *new_s = malloc(sizeof(S_node));
                strcpy(new_s->filename, temp->f_name);
                new_s->word_count = 1;
                new_s->sub_link = NULL;

                new_m->sub_link = new_s;
                HT[index] = new_m;          // Attach to hash table
            }

            /* ---------------- Case 2: Index already has nodes ---------------- */
            else
            {
                /* ---- Check first main node ---- */
                if (strcmp(mtemp->word, word) == 0)
                {
                    S_node *stemp = mtemp->sub_link;
                    S_node *prev = NULL;

                    // Traverse sub list (files list)
                    while (stemp)
                    {
                        // Same file → increase count
                        if (strcmp(stemp->filename, temp->f_name) == 0)
                        {
                            stemp->word_count++;
                            break;
                        }
                        prev = stemp;
                        stemp = stemp->sub_link;
                    }

                    // Word not present in this file → add new sub node
                    if (stemp == NULL)
                    {
                        S_node *new = malloc(sizeof(S_node));
                        strcpy(new->filename, temp->f_name);
                        new->word_count = 1;
                        new->sub_link = NULL;
                        prev->sub_link = new;
                        mtemp->file_count++;    // New file added
                    }
                }

                /* ---- Word not in first main node ---- */
                else
                {
                    // If no collision chain yet → directly attach
                    if (mtemp->main_link == NULL)
                    {
                        M_node *new = malloc(sizeof(M_node));
                        strcpy(new->word, word);
                        new->file_count = 1;
                        new->main_link = NULL;

                        S_node *snew = malloc(sizeof(S_node));
                        strcpy(snew->filename, temp->f_name);
                        snew->word_count = 1;
                        snew->sub_link = NULL;

                        new->sub_link = snew;
                        mtemp->main_link = new;
                    }

                    /* ---- Collision chain exists ---- */
                    else
                    {
                        M_node *prev = HT[index];   // Start from bucket head
                        int found = 0;

                        // Traverse main linked list
                        while (mtemp)
                        {
                            // Word found in chain
                            if (strcmp(mtemp->word, word) == 0)
                            {
                                found = 1;

                                S_node *stemp = mtemp->sub_link;
                                S_node *prevs = mtemp->sub_link;

                                // Traverse sub list
                                while (stemp)
                                {
                                    if (strcmp(stemp->filename, temp->f_name) == 0)
                                    {
                                        stemp->word_count++;
                                        break;
                                    }
                                    prevs = stemp;
                                    stemp = stemp->sub_link;
                                }

                                // New file for existing word
                                if (stemp == NULL)
                                {
                                    S_node *new = malloc(sizeof(S_node));
                                    strcpy(new->filename, temp->f_name);
                                    new->word_count = 1;
                                    new->sub_link = NULL;
                                    prevs->sub_link = new;
                                    mtemp->file_count++;
                                }

                                break;
                            }

                            // Move in main chain
                            prev = mtemp;
                            mtemp = mtemp->main_link;
                        }

                        /* ---- Word not found in chain → create new main node ---- */
                        if (!found)
                        {
                            M_node *new = malloc(sizeof(M_node));
                            strcpy(new->word, word);
                            new->file_count = 1;
                            new->main_link = NULL;

                            S_node *snew = malloc(sizeof(S_node));
                            strcpy(snew->filename, temp->f_name);
                            snew->word_count = 1;
                            snew->sub_link = NULL;

                            new->sub_link = snew;
                            prev->main_link = new;   // Attach to chain
                        }
                    }
                }
            }
        }

        fclose(fp);              // Close file
        temp = temp->link;       // Move to next file
    }
    printf(GREEN"CREATED DATABASE SUCCESSFULLY!!!\n"RESET);
}

   

int get_index(char *word)
{
    if (word[0] >= 'a' && word[0] <= 'z'){
        return word[0]-'a';
        }
    else if (word[0] >= 'A' && word[0] <= 'Z'){
            return word[0]-'A';
        }
    else{
        return 26;
    }
}