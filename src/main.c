#include "inverted.h"

int update_flag;
int firstcreate;
int main(int argc, char *argv[])
{
    F_node *head = NULL;
    M_node *HT[27];
	for(int i=0;i<27;i++)
    	HT[i] = NULL;

	if(argc==1){
		printf(RED"INFO : Invalid number of CLAs\nPASS at least One file\n"RESET);
		return 0;
	}
    // Validate_files
	validate_files(argv,&head);
    int option;
    do
    {
	printf(SKYBLUE"Select your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice : "RESET);

	scanf("%d", &option);

	switch (option)
	{
	    case 1:
		if(firstcreate==0){
			create_database(HT, head);
			firstcreate=1;
		} 
		else
			printf(RED"DATABASE ALREADY CREATED\n"RESET);
		break;

	    case 2:
		if(firstcreate)
			display_database(HT);  
		else	
			printf(RED"We Can't Display Without Creating Database\n"RESET);	
		break;

	    case 3:
		if(firstcreate)
			save_database(HT);  
		else	
			printf(RED"We Can't Save Without Creating Database\n"RESET);	
		break;

	    case 4:
		if(firstcreate)
			search_database(HT);  
		else	
			printf(RED"We Can't Search Without Creating Database\n"RESET);	
		break;
		break;

	    case 5: 
		if(firstcreate){
			update_flag=1;
			update_database(HT, &head);
		}
		else	
			printf(RED"We Can't Update Without Creating Database\n"RESET);	
		break;

	    case 6:
		break;

	    default:
		printf(RED"INFO : Please enter the valid option\n"RESET);
	}
    }while( option != 6 );

    return 0;
}