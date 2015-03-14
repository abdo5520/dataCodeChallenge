/*
 *
 * @author  Abdallah S. Abdallah <abdo.aast@gmail.com>
 * @file README.txt
 * @version 0.1
 * @date Mar 13, 2015
 *
 */







Instructions to run the code
--------------------------------

run the script run.sh in order to compile and run the code.
The code run in the following order:
Firstly countword will run. countword.c prints the frequency of the words in the txt files found into (wc_input).
The print out is given into the file ./wc_output/wc_results.txt.


Secondly, the program median will run. It finds/calcualtes the median value for the number of words per line as requested in the problem definition. 
Unluckily, the process of sorting the files' names still needs debugging. Hence, the files' names are not always sorted correctly. 

----------------------------------------


Algorithms & Implementation
-------------------------------
(Notice) 
1) All the files in the folder wc_input must be text files. The program does not check for the file types.
2) Number of files are limited by 100
3) Maximum acceptable length of a word is 50 letters


1) Word counting
----------------

For both problems, I used pretty straightforward linked list implementation. 
I use linear search to access the linked list for the countword problem, which is not efficient. If time allowed, I would implement hashing with Trie datastructure. 
This would be more efficient. 


2) Find the median
--------------------

I almost used the same linked list data structure with minor modifications. 
I also used (MergeSort) in order to sort the list (which stores the number of words per each line) , after each insertion. 
During the insertion, I kept track of how many elements were inserted earlier, then I implemented linear traversing that stopped at the middle node to calculate the median.
It is straitforward but not efficient. The time complexity is approximately (N/2) (for the traversing) + (NlogN) for the MergeSort after the insertion.

If the time allowed, I would implement more efficient solution, where the list is ordered on the fly before the insertion. 
This can be done by having a kind of Binary Tree, where each node (in the tree) keeps track of how many nodes inserted into its right or its left.
This would save the traversing time.  

Another required improvement is to insert based on comparing the stored values against the new value. If the new value is already inserted into its appropriate location after finding the greatest number smaller than the value to insert then the list will be always sorted and no need to run the MergeSort after every insertion. Sorting is currently needed only because the insertion (pushing) is a blind insertion at the head of the list. 




