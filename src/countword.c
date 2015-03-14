/*
 *
 * @author  Abdallah S. Abdallah <abdo.aast@gmail.com>
 * @file countword.c
 * @version 0.1
 * @date Mar 13, 2015
 *
 */

/**
 *  COPYRIGHT Disclaimer
 *
 *  The linked list handling code is heavily depending on the code found in the following  link
 *
 *  http://www.geeksforgeeks.org/merge-sort-for-linked-list/
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#include <sys/types.h>


#include <dirent.h>

#define NAME_LEN 256
#define MAX_NO_FILES 100
#define WORD_LEN 50



#define DISPLAYDEBUG printf ("\nThis is line %d of file %s (function %s)\n",__LINE__, __FILE__, __func__)






#include<stdio.h>
#include<stdlib.h>

/* Link list wordnode */
struct wordnode
{

	int frequency;
	char member[WORD_LEN];
	struct wordnode* next;
};

/* function prototypes */
struct wordnode* SortedMerge(struct wordnode* a, struct wordnode* b);
void FrontBackSplit(struct wordnode* source,
		struct wordnode** frontRef, struct wordnode** backRef);

/**
 *
 * sorts the linked list by changing next pointers (not frequency)
 *
 */
void MergeSort(struct wordnode** headRef)
{
	struct wordnode* head = *headRef;
	struct wordnode* a;
	struct wordnode* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

/**
 *
 *  ReCombine the sub -lists again into one list with one root wordnode
 *
 *
 */
struct wordnode* SortedMerge(struct wordnode* a, struct wordnode* b)
{
	struct wordnode* result = NULL;

	/* Base cases */
	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (a->frequency <= b->frequency)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return(result);
}

/**
 *
 *  split any linked list into two halfs and return a pointer to the first member wordnode
 *  in each half
 *
 */

void FrontBackSplit(struct wordnode* source,
		struct wordnode** frontRef, struct wordnode** backRef)
{
	struct wordnode* fast;
	struct wordnode* slow;
	if (source==NULL || source->next==NULL)
	{
		/* length < 2 cases */
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		/* Advance 'fast' two wordnodes, and advance 'slow' one wordnode */
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		/* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

/**
 *
 *  Return pointer to the wordnode if the word already exists
 *  return NULL otherwise
 *
 */
struct wordnode *DoesItExist(struct wordnode** head_ref, char *target)
{


	//DISPLAYDEBUG;
	int counter =0;

	struct wordnode* tracer;

	tracer = *head_ref;


	while (tracer != NULL)
	{

		if (strcmp(tracer->member,target ) ==0)
			return(tracer);

		tracer = tracer->next;

	}


	return(NULL);



}


/**
 *
 *  Receives the linked list root and traverse the list until the middle wordnodes
 *  then calcualtes/returns the median value
 *
 *
 */
float FindMedianValue(struct wordnode* source, int nwordnodes)
{

	int counter =0;

	struct wordnode* tracer;

	tracer = source;

	if (nwordnodes <=0)
		return (-1);

	if (nwordnodes == 1)
		return tracer->frequency;

	if (nwordnodes == 2)
		return ((float)(  tracer->frequency  +  ((tracer->next)->frequency )  )/2 );


	// Odd number of wordnodes
	if (nwordnodes%2 == 1 )
	{
		while (counter < (int)(nwordnodes/2) -1)
		{
			tracer = tracer->next;

			counter++;

		}
		//printf("internal counter = %d", counter);
		return (tracer->next->frequency);


	}

	// Even Number of wordnodes
	else
	{
		while (counter <  (nwordnodes/2) -1 )
		{
			tracer = tracer->next;

			counter++;

		}
	//	printf("internal counter = %d", counter);
		return ((float)(  tracer->frequency  +  (tracer->next->frequency )  )/ 2 );


	}




	/* 'slow' is before the midpoint in the list, so split it in two
      at that point. */


}


/**
 * Function to print wordnodes in a given linked list
 *
 */



void PrintList(struct wordnode *wordnode,FILE *fp)
{

//	printf("\n----------------------------------------------------------------");
//	printf("\n----------------------------------------------------------------");
//	printf("\nNode's Value		 \t\t 		Frequency ");
//	printf("\n----------------------------------------------------------------");
//	printf("\n----------------------------------------------------------------");
	while(wordnode!=NULL)
	{
		fprintf(fp,"\n%s \t\t 					%d ", wordnode->member ,wordnode->frequency);
		wordnode = wordnode->next;
	}
//	printf("\n----------------------------------------------------------------");
//	printf("\n----------------------------------------------------------------");
//	printf("\n----------------------------------------------------------------");

}

/* Function to insert a wordnode at the beginging of the linked list */
int Push(struct wordnode** head_ref, char *value)
{

	//DISPLAYDEBUG;
	struct wordnode *alreadyThere;
	struct wordnode* new_wordnode;
	if (*head_ref !=NULL)
	{
		alreadyThere = DoesItExist(head_ref,value);
		if ( alreadyThere != NULL)
		{

			(alreadyThere->frequency)++;
			return (alreadyThere->frequency);

		}

		/* allocate wordnode */
		new_wordnode =(struct wordnode*) malloc(sizeof(struct wordnode));

		/* put in the frequency  */
		new_wordnode->frequency = 1;

		//copy the word to new element
		strncpy(new_wordnode->member,value,strlen(value));



		/* link the old list off the new wordnode */
		new_wordnode->next = (*head_ref);

		/* move the head to point to the new wordnode */
		(*head_ref)    = new_wordnode;

		return (new_wordnode->frequency);



	}

	/* allocate wordnode */
	new_wordnode = (struct wordnode*) malloc(sizeof(struct wordnode));

	/* put in the frequency  */
	new_wordnode->frequency = 1;

	//copy the word to new element
	strncpy(new_wordnode->member,value,strlen(value));



	/* link the old list off the new wordnode */
	new_wordnode->next = (*head_ref);

	/* move the head to point to the new wordnode */
	(*head_ref)    = new_wordnode;

	return (new_wordnode->frequency);




}



#define NONALPH 0
#define ALPH 1

/**
 *  Count words per line and extract them word by word
 *
 */

int ExtractWords(FILE *fileP , struct wordnode **list)
{
	//DISPLAYDEBUG;


	// A buffer to store one word at a time
	char buffer[WORD_LEN];


	while( fscanf( fileP, "%s", buffer ) != EOF )
	{

	//	printf("\n[%s] ",buffer);
		Push(list,buffer);
			//printf("[%s] created New node",buffer);


	}

	// insert into new node;








	return (1);
}



/**
 *
 * Count words per line ONLY and return the count
 *
 */

int CountWords(char *str)
{

	//DISPLAYDEBUG;
	int state = NONALPH;
	unsigned wc = 0;  // word count
	int i;

	int len;

	len =strlen	(str);

	// Scan all characters one by one
	for (i=0; i <len;i++)
	{
		// If next character is a separator, set the state as OUT
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			state = NONALPH;

		// If next character is not a word separator and state is OUT,
		// then set the state as IN and increment word count
		else if (state == NONALPH)
		{
			state = ALPH;
			++wc;
		}

		// Move to next character
		// ++str;
	}

	return wc;
}



/**
 *
 *  Extract the list of file names from a directory
 *
 */



int ExtractFileNames(DIR *dir,char *allNames[])
{
	struct dirent *entry;

	int nFiles = 0;
	while ((entry = readdir (dir)) != NULL)
	{

		if (!strcmp (entry->d_name, "."))
			continue;
		if (!strcmp (entry->d_name, ".."))
			continue;

		nFiles++;
		if (nFiles > MAX_NO_FILES)
		{
			printf("\n Too many files, the limit is 100 \n Program will exit");
			return (0);
		}

		char *name = (char *)malloc(sizeof(NAME_LEN));
		strncpy(name, entry->d_name, strlen(entry->d_name));

		allNames[nFiles - 1] = name;

	}



	return(nFiles);




}


/**
 *
 *  Orders alphapatically a list of filenames
 *
 */

void SortFileNames(char *list[], int llen)
{

	char *buffer;
	int i;
	int j;
	for (i=0; i < llen-1 ; i++)
	{

		for (j=i+1;j<llen;j++)
		{

			//swapping

			if (strcmp(list[i],list[j]) > 0);
			{
				buffer = list[j];
				list[j] = list[i];
				list[i] = buffer;

			}


		}

		/*
		printf("\n Internal.......................... ");
		for (i = 0; i<llen ; i++)
		printf("\n File Name = %s", list[i]);
		*/



	}





}







/**
 * @param number og arguments
 * @param list of arguments
 * @return
 *
 */
int main(int argc, char *argv[])
{


	FILE *input;

	FILE *output;
	int string_size;
	char word_string[BUFSIZ];
	char line_string[BUFSIZ];

	int perline_counter=0;
	int nlines =0;
	float middle;

	struct dirent *entry;
	const char *type = "txt";
	char inputpath[256];
	char alterpath[] = "./wc_input/";
	//char alterpath[] = "./bbb/";
	strcpy(inputpath, alterpath);
	int ret = 1;
	DIR *dir;
	int nFiles;
	char *allNames[MAX_NO_FILES];
	int i;

	/**
	 *  Define the linked list
	 *	starting with an empty list
	 */

	struct wordnode* myList = NULL;




	/* Scanning the in directory */
	if (NULL == (dir = opendir (inputpath)))
	{
		printf("Failed to open input directory \n");


		return 1;
	}



	/**
	 *  Extract the list of files from the target folder
	 *
	 */
	nFiles = ExtractFileNames(dir,allNames);
	close(dir);

	if (nFiles <1)
	{
		printf("\n The target folder is empty ! No files exist");
		return (1);
	}



	output =  fopen("./wc_output/wc_results.txt", "w");
	if (output == NULL)
	{
		printf("Failed to open the output file\n");


		return 1;
	}


	/**
	 *  Sort the list of file names
	 *
	 */
	SortFileNames(allNames,nFiles);

	// printout for debugging
	/*
	for (i = 0; i<nFiles ; i++)

	{
		printf("\n File Name = %s", allNames[i]);

	}

*/

	i = 0;
	while ( i < nFiles)
	{

		//printf("\n %s",allNames[i]);

		// attach the target path to the file name
		strcat(inputpath,allNames[i]);



		input = fopen(inputpath, "r");
		if (input == NULL)
		{
			printf("\nFailed to open an input file");


			return 1;
		}
		else
		{


			ExtractWords (input, &myList);
			PrintList(myList,output);



		}


		fclose(input);


		//printf("BEFORE \n %s",inputpath);
		strcpy(inputpath, alterpath);
		//printf("\n AFTER \n %s",inputpath);
		//getc(stdin);

		i++;
	} // end of while loop over the list of files



	fclose(output);
	free(myList);




}






