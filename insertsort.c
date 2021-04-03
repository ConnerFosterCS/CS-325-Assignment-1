/*
** Name: Conner Foster
** Date: Jan 8, 2021
** ASGN: Merge Sort (CS325 section 2)
** DESC: This program performs a simple insertion sort for an array of integers. The program reads inputs from a file named “data.txt”.
**		 data.txt is formatted such that the first value of each line is the number of integers that need to be sorted, followed by the integers
**       to be sorted. The program outputs the sorted values without the preliminary first integer that indicated the number of integers.
**		 I was able to code this by working off of the psuedo code for insertion sort given in the class slides.
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


/*Function to sort an array using insertion sort*/
void insertionSort(int inputArr[], int n)
{
	for (int j = 1; j < n; j++)		//start at second position of the array and loop through it
	{
		int key = inputArr[j];		//duplicate the value from the second position
		int i = j - 1;		//create an int to read the array from the start

		while (i >= 0 && inputArr[i] > key)		//compare the values, run code below if the second number is smaller than the first
		{
			inputArr[i + 1] = inputArr[i];		//swap the numbers
			i = i - 1;		//decrement to keep position of the number that was just swapped 
		}
		inputArr[i + 1] = key;		//finish the swap by changing the second number
	}
	output(inputArr, n); //print the array to the terminal after the swaping loop is complete
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
				insertionSort(inputArr, size);
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
				//printf("%i, ", number);
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
