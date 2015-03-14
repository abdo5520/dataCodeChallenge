/*
 *
 * @author  Abdallah S. Abdallah <abdo.aast@gmail.com>
 * @file median.c
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
#include "median.h"





#define NONALPH 0
#define ALPH 1
// returns number of words in str
int CountWords(char *str)
{
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



int ExtractFileNames(DIR *dir,char *allNames[],char *allNames2[])
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
		char *name2 = (char *)malloc(sizeof(NAME_LEN));
		strncpy(name, entry->d_name, strlen(entry->d_name));
		strncpy(name2, entry->d_name, strlen(entry->d_name));

		allNames[nFiles - 1] = name;
		allNames2[nFiles - 1] = name2;

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

	//char *list = *names;

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

			{


			//	printf("\n File Name = %s", list[i]);



			}

		 */

	}


	//return(list);



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
	//const char *type = "txt";
	char inputpath[256];
	char alterpath[] = "./wc_input/";
	//char alterpath[] = "./bbb/";
	strcpy(inputpath, alterpath);
	int ret = 1;
	DIR *dir;
	int nFiles;

	/**
	 * Currently the code handles only 100 files.
	 * However, dynamic allocation of dynamic list can be done for an optimized unlimited version
	 *
	 *
	 */
	char *allNames[MAX_NO_FILES];
	char *allNames_toLower[MAX_NO_FILES];
	int i;

	/**
	 *  Define the linked list
	 *	starting with an empty list
	 */

	struct node* res = NULL;
	struct node* myList = NULL;






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
	nFiles = ExtractFileNames(dir,allNames,allNames_toLower);


	if (nFiles <1)
	{
		printf("\n The target folder is empty ! No files exist");
		return (1);
	}





	output =  fopen("./wc_output/med_results.txt", "w");
	if (output == NULL)
	{
		printf("Failed to open the output file\n");


		return 1;
	}


	// printout for debugging
	/*
	for (i = 0; i<nFiles ; i++)

	{
		printf("\n File Name = %s-------------%s", allNames[i] , allNames_toLower[i]);

	}

*/

		for (i=0; i <nFiles;i++)
		{
		int k =0;

			char *dest = allNames_toLower[i];
			int L = strlen(allNames_toLower[i]);

			for (k=0;k < L ;k++)
			{


					*(dest+k) = tolower( *(dest+k)  );


			}


		}

		// printout for debugging
		/*
			for (i = 0; i<nFiles ; i++)

			{
				printf("\n\n\n File Name = %s-------------%s", allNames[i] , allNames_toLower[i]);

			}

		*/
	/**
	 *  Sort the list of file names
	 *
	 */
	int j;
	char *tochange;
	for (i=0; i < nFiles ; ++i)
	{

		for (j=i+1;j<nFiles;++j)
		{

			//swapping

			if (strcmp(allNames_toLower[i],allNames_toLower[j]) >= 0);
			{
				tochange = allNames[j];
				allNames[j] = allNames[i];
				allNames[i] = tochange;

			}


		}


	}


	close(dir);
	/**
	 * --------
	 * --------
	 * --------
	 * --------
	 */




	// printout for debugging
	/*
	for (i = 0; i<nFiles ; i++)

	{
		printf("\n After\n File Name = %s", allNames[i]);

	}

*/

	i = 0;
	fprintf(output,"\n Number of lines scanned \t\t\t The Median Value \n");
	while ( i < nFiles)
	{
		// entry->d_type == strlen(type) &&
		//printf("\n %s",allNames[i]);
		/*
        	if (!strcmp (entry->d_name, "."))
        	            continue;
        	  if (!strcmp (entry->d_name, ".."))
        	            continue;
		 */
		strcat(inputpath,allNames[i]);
		/* Open directory entry file for common operation */
		/* TODO : change permissions to meet your need! */
		// system("cd wc_input");


		input = fopen(inputpath, "r");
		if (input == NULL)
		{
			printf("\nFailed to open the input file named: %s",inputpath);


			return 1;
		}
		else
		{

			//	printKMostFreq (input, k);


			while(	1 )
			{

				fgets(line_string, BUFSIZ, input);

				if(feof(input))
					break;
				// Check for empty lines in order to skip them
				if (line_string[strlen(line_string)-1] == '\n' && strlen(line_string) == 1)
				{

					continue;

				}


				perline_counter = CountWords(line_string);


				if (perline_counter == 0)
					break;
				//insert a new node into the linked list
				Push(&myList, perline_counter);
				/* Sort the above created Linked List */
				MergeSort(&myList);

			//	printf("\n Sorted Linked List is: \n");
			//	PrintList(myList);



			//	printf("\n %s",line_string);
			//	printf("\n %d \n",perline_counter);
				nlines++;

				// print the median

				middle = FindMedianValue(myList,nlines);
			//	printf("\n Number of Nodes = %d \t\t\t The Median Value =  %f \n",nlines,middle);
				fprintf(output,"\n %d \t\t\t\t\t  %f \n",nlines,middle);

				// Display the median
				perline_counter=0;
			} // end of the while infinite lopp
			//	printf("\n Number Of non empty lines = %d \n",nlines);


		}


		fclose(input);


		//printf("BEFORE \n %s",inputpath);
		strcpy(inputpath, alterpath);
		//printf("\n AFTER \n %s",inputpath);
		//getc(stdin);

		i++;
	} // end of while loop over the list of files



	fclose(output);


	printf("\n");

			return (1);

}


