/*
** Name: Conner Foster
** Date: Jan 8, 2021
** ASGN: Merge Sort (CS325 section 2)
** DESC: This program performs a simple merge sort for an array of integers. The program reads inputs from a file named “data.txt”. 
**		 data.txt is formatted such that the first value of each line is the number of integers that need to be sorted, followed by the integers
**       to be sorted. The program outputs the sorted values without the preliminary first integer that indicated the number of integers.
**		 I was able to complete this section fo the assignment by watching merge sort tutorials and reading many pages about the sorting method.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


/* Function to print an array */
void output(int inputArr[], int size)
{
	for (int i = 0; i < size; i++)		//loop for the length of the array
		printf("%i, ", inputArr[i]);	//print the array cell by cell
}


/* Function to sort the temp array with the passed array */
void merge(int inputArr[], int leftSize, int rightSize) 
{
	//size is the total size of the original array that was split prior (both sides added), temp[] holds the sorted list, and num1 and
	int size = (leftSize + rightSize), temp[size], num1 = 0, num2 = 0;		//... num2 are storing the positions of the "sub arrays"

	for (int i = num1 + num2; i < size; i++)	//must itterate through num1+num2 to get through full length of the array
	{
		int position = num1 + num2;		//keeps track of the position of the passed in array, again both sub array sizes add up the the full size
		if (leftSize > num1 && inputArr[leftSize + num2] >= inputArr[num1])		//if there are still numbers in the left "sub array" to itterate through and the second number in the list is larger...
			temp[position] = inputArr[num1++];		//keep the numbers in the same position and increment the check position
		else if (leftSize > num1 && num2 >= rightSize)		//if the end of the list is reached for the left sub array (there are numbers to itterate through on the left but not the right)...
			temp[position] = inputArr[num1++];		 //keep the numbers in the same position of the temp array and increment the position of the left "sub array" 
		else if (rightSize > num2 && inputArr[num1] > inputArr[leftSize + num2])		//if there are still numbers in the right "sub array" to itterate through and the second number in the list is smaller...
			temp[position] = inputArr[leftSize + num2++];		//swap the positions of the numbers
		else if (rightSize > num2 && num1 >= leftSize)		//if there are numbers to check from the right "sub array" and no more to check from the left "sub array"
			temp[position] = inputArr[leftSize + num2++];		//swap the positions of the numbers
	}

	for (int i = 0; i < size; i++)
		inputArr[i] = temp[i];
}


/* Function to recursively create the sub arrays and sort them */
void mergeSort(int inputArr[], int size) 
{
	if (size <= 1)		//stop if there is only 1 number left because it can not be split into 2
		return;		//returns recursively
	else 
	{
		int leftSize = size / 2, rightSize = size - leftSize;	 //find the length of the array devided by 2
		mergeSort(inputArr, leftSize);		//split the left side down again
		mergeSort(inputArr + leftSize, rightSize);		//split the right side down again
		merge(inputArr, leftSize, rightSize);		//compare the values and sort the array wit the merge function
	}
}


/*function to open file and fill an integer array*/
void processFile()
{
	int i = 0, size = 0, number = 0;	//var i keeps track of the position of the int array, size stores the first number of each line to determine the length of the array, and number is the number that is retrieved from the file
	FILE* file = fopen("data.txt", "r");	//open data file

	fscanf(file, "%d", &number);	//read first number of the first line to get required array size
	size = number;
	int inputArr[size];		//create an array and set it to the required size
	
	while (true)	//loops infinitely (programmer controlls when the loop stops)
	{
		fscanf(file, "%i", &number);	//get the next number in the file

		if (i <= size)	 //if there are still numbers in the line
		{
			if (i == size)	 //if the the end of the current line is reached
			{
				mergeSort(inputArr, size);
				output(inputArr, size);
				size = number;		//set the new size (first number of next line
				int inputArr[size];		//Re-create the array and set it to the required size for the new line
				printf("\n");
				i = 0;		//reset the conditions for the if statement for the new line
				
				if (feof(file))		//if the end of the text file is reached...
					break;		//end loop
			}
			else
			{
				inputArr[i] = number;		//fill the number array with the fetched integer
				i++;		//itterate through array
			}
		}
	}
	fclose(file);		//end file stream
}


int main() 
{
	processFile();
}