//	Team: Ultraviolet (Kelsey Rocklin & John Williams)
//	Operating Systems
//  Programming assignment 1
//


#include <stdio.h>
#include <stdlib.h>

typedef struct Noder Noder;

struct Noder{
    char word[10];// assume that the word is less that 15 characters long
    int count;
    Noder* leftPtr;
    Noder* rightPtr;
};

int compare(char left[],char right[] );
Noder* read(FILE *file ,  Noder * head);
int searchTree(Noder * head, char item[]);
int length( char item[]);
void insert(Noder * head, char item[]);
void write(Noder *head, FILE* output);
void deleteTree(Noder *head);

int main(int argc, char **argv) {


    Noder  * head = NULL; // head pointer to the tree
    FILE *inputFile = fopen("input02.txt", "r");// open the input and the output file
    FILE *outputFile = fopen("OUTPUT.txt", "w");

    if (inputFile == NULL || outputFile ==NULL)// check to see if either errored out and if so exit
    {
        printf("ERROR OPENING FILE\n\n\n");
        exit(0);
    }

    head = read(inputFile, head);// read in the file and put each word in a distinct node
    fclose(inputFile);// close the file
    write(head, outputFile);// write the tree to the output file
    fclose(outputFile);// close the file



    deleteTree(head);
 head = NULL;
    exit(0);
}
// Function used to find the length of a word
// this is used to give us the parameters for a FOR loop when we
// were looking to copy a word from the input to a file
int length( char item[]){
    int length = 0;
    while (1 == 1){
        if (item[length] != '\0')// seek the null terminator
        {
            length++;
        }
        else
        {return length;}
    }
}
//  function implements a dealocation procedure via depth first traversal
// and the free command using recursion
void deleteTree(Noder *head)
{
    if (head->leftPtr != NULL)// search left
    {
        deleteTree(head->leftPtr);
    }
    if (head->rightPtr != NULL)// search right
    {
        deleteTree(head->rightPtr);
    }
    if (head != NULL)// if head isnt null then free memory
    {
        free(head);
    }
}
//  Procedure Writes the tree, using an in-order traversal
//  and recursion.
void write(Noder *head, FILE * outputFile)// need a file pointer here as well
{
    if (head->leftPtr != NULL)// go left
    {
        write(head->leftPtr, outputFile);
    }
    if (head != NULL)// visit parent
    {
        //printf("%s ~~ %d \n", head->word, head->count);
        fprintf(outputFile, "%s: %d\n",head->word, head->count );
    }
    if (head->rightPtr != NULL)// go right
        {
            write(head->rightPtr, outputFile);
        }
}
// this procedure
// here we use recursion and the compare function to build the tree.
// I have 4 cases outlined. they are based on weather the node contains something in its
// childrens node and weather we need to go left or right.
// we determine direction from the compare function
void insert(Noder * head, char item[]){
    int direction = compare(head->word,item);
    // if the current root is the word

    if (head->word[0] == '\0')// if the signal for the head node is present then populate the head node
    {
        head->rightPtr = NULL;
        head->leftPtr= NULL;
        head->count = 0;

        //issues here creating a dynamic item to put into the tree.
        // need to know the length of the word.
        int size = length(item);

        for (int i = 0; i < size; i++) {
            head->word[i] = item[i];
        }
        head->word[size] = '\0';
        //puts(head->word);
        head->count = 1;
        return;
    }
    else if (direction ==2)
    {
        head->count++;// if found increment the count on it
        return;
    }
    // else if the head's word comes first alphabetically
    else if (direction ==1 && head->rightPtr != NULL)
    {
        return insert(head->rightPtr, item);// search right
    }
    // else if the word comes first
    else if ( direction==0 && head->leftPtr!= NULL)
    {
        return insert(head->leftPtr, item);// search left
    }

    // otherwise we are at null so make a new node and insert the item
    else if (direction==1 && head->rightPtr == NULL)// if the word is alphabetically less than the parent and the node is available
    {
        head->rightPtr = (Noder *)malloc(sizeof(Noder));
        head->rightPtr->rightPtr = NULL;
        head->rightPtr->leftPtr = NULL;
        head->rightPtr->count = 1;
        // need to know the length of the word.
        int size = length(item);
        for (int i = 0; i < size; i++) {
            head->rightPtr->word[i] = item[i];
        }
        head->rightPtr->word[size] = '\0';

        return;
    }
    else if ( direction==0 && head->leftPtr == NULL)// if the word is alphabetically greater than the parent and the node is available
    {
        head->leftPtr = (Noder *)malloc(sizeof(Noder));
        head->leftPtr->rightPtr = NULL;
        head->leftPtr->leftPtr = NULL;
        head->leftPtr->count = 1;
        // need to know the length of the word.
        int size = length(item);
        for (int i = 0; i < size; i++) {
            head->leftPtr->word[i] = item[i];
        }
        head->leftPtr->word[size] = '\0';
        return;
    }
}



// Function compares two words and determines which one is
// alphabetically larger. It then returns a 0 if the left parameter is
// in front of the right parameter. otherwise it returns a 1 if the
// right word is in front of the left word.
int compare(char left[],char right[] ){

    // determine the shorter of the two.
    int length = 0;
    int i = 0;
    while (1 == 1){
        if (left[length] != '\0' && right[length] != '\0')
        {length++;}
        else {
            break;
        }
    }

    while (i <= length)
    {
        if ((int)left[i] == (int)right[i])
        {
            i++;
        }
        else if ((int)left[i] > (int)right[i])
        {
            return 0;// signifying that the right word comes first alphabetically
        }

        else if ((int)left[i] < (int)right[i]){
            return 1;// signifying that the left word comes first alphabetically
        }
    }
        return 2;// signifying that the words are equal alphabetically.

}

//Searches for the node in the tree by using the compare function.
//if this function doesn't find the word in the tree them it returns
//NULL. Otherwise it returns the pointer to the node.
int searchTree(Noder  * head, char item[]){
    if (head == NULL ||head->word == "\0")
    {
        return 0;
    }

    int direction = compare(head->word,item);
    // if the current root is the word
    if (direction ==2)
    {
        //head->count++;// if found increment the count on it
        return head->count;
    }
    // else if the head's word comes first alphabetically
    if (direction ==1 && head->rightPtr != NULL)
    {
        return searchTree(head->rightPtr, item);// search right
    }
    // else if the word comes first
    if ( direction==0 && head->leftPtr!= NULL)
    {
        return searchTree(head->leftPtr, item);// search left
    }

    // otherwise we didn't find it
    if (direction==1 && head->rightPtr == NULL)
    {
        return NULL;
    }
    // otherwise we didn't find it
    if ( direction==0 && head->leftPtr!= NULL)
    {
        return NULL;
    }
}



// function reads file and process the words into the tree
// returns the head pointer to the main procedure.
Noder* read(FILE *file, Noder * head){
                char word[1024];
                /* assumes no word exceeds length of 1023 */
                //https://stackoverflow.com/questions/16400886/reading-from-a-file-word-by-word

                head = (struct Noder *)malloc(sizeof(struct Noder));
                head->word[0] = '\0';
                while (fscanf(file , " %1023s", word) == 1) {
                    //head = searchTree( head, word);
                    insert(head ,word);
                }
            return head;
        }
