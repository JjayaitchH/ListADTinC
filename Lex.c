//Jesus Hernandez
//jherna83
//PA2
//Lex.c - takes input from file, stores in array, indirectly
//        sorts indecies lexicographically 
//        using linked list manipulated by the List.c ADT

//Most of this was also taken from the examples 
//on the website just modified to fit the assignment 
//The sorting algorithm is essentially the same from 
//my Java version but in C syntax with one new parameter.
//Since it's not as simple to find the size of an array in C,
//I just included it from the start.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

void arrSort(List L, char* b[], int size); //declare sort function beforehand

#define MAX_LEN 160

int main(int argc, char* argv[])
{
    FILE *in1, *in2, *out; 
    char line[MAX_LEN];
    int length = 0;

    if(argc != 3)
    {
        printf("Usage: %s [input file] [output file]\n", argv[0]);
        exit(1);
    }

    in1 = fopen(argv[1], "r");
    in2 = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if(in1 == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }


    //this while loop opens up in1 to read and 
    //get the length of the file
    while(fgets(line, MAX_LEN, in1) != NULL)
    {
        length++;
    }
    fclose(in1);

    char* arr[length];
    int ind = 0;

    //this while loop puts the lines into
    //the array created above.
    while(fgets(line, MAX_LEN, in2) != NULL)
    {
        arr[ind] = malloc(MAX_LEN);
        strcpy(arr[ind], line);
        ind++;
    }
    fclose(in2);

    List nList = newList();

    arrSort(nList, arr, length);
    
    moveFront(nList);

    //this while loop prints out each
    //index of the array in sorted order
    while(index(nList) >= 0)
    {
        fprintf(out, arr[get(nList)]);
        moveNext(nList);
    }
    fclose(out);

    //free the array
    for(int i = 0; i < length; i++)
    {
        free(arr[i]);
    }

    //free the list
    freeList(&nList);
    return(0);
}

//Separate function for the sorting. It takes in
//the list, array of char*, and size of array
void arrSort(List L, char* b[], int size)
{
    //start off by inserting first index
    prepend(L, 0);

    //loop through entire array and sort
    for(int i = 1; i < size; i++)
    {
        //Eachtime a new pass through the loop is performed, the cursor is set 
        //to the front. This makes the index 0 and allows it to enter the while
        //loop from the begining to compare all the indices in the list to the rest in the array
        moveFront(L);

        //compare both values, if element continues to be to the right
        //of the element it is being compared to moveNext will be called
        //and once the comparison fails it will go down to do proper insertion
        while(index(L) >= 0)
        {
            if(strcmp(b[get(L)], b[i]) < 0)
            {
                moveNext(L);
            }
            else
            {
                break;
            }
        }
        //this insert happens if the cursor is not null and
        //the index belongs somewhere insie the list
        if(index(L) != -1)
        {
            insertBefore(L, i);
        }
        //moveNext was called until cursor fell of list
        //means that element belongs at the end.
        else
        {
            append(L, i);
        }
    }
}