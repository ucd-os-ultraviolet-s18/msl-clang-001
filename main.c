//	Team: Ultraviolet (Kelsey Rocklin & John Williams)
//	Operating Systems
//  Programming assignment 1


#include <stdio.h>
#include <stdlib.h>

typedef struct Noder Noder;

struct Noder{
    char word[15];// assume that the word is less that 15 characters long
    int count;
    Noder* leftPtr;
    Noder* rightPtr;

};

// function declarations

// sees which word comes first in the given character arrays
int compare(char left[],char right[] );

// reads the file and automatically adds words to the tree
Noder* read(FILE *file , char *buffer, long * position,  Noder * head);

// searches the tree for the given word
int searchTree(Noder * head, char item[]);

// finds the length of a word in a character array
int length( char item[]);

// inserts a given node into the tree using the head and new word
// (increments the count if the word exists already)
void insert(Noder * head, char item[]);

// prints the words to the console and a file
void printReport(FILE* outFile, Noder* root);

// deletes the tree and frees the memory
void deleteTree(Noder* root);

int main(int argc, char **argv) {


    char *buffer = NULL;
    long * length;
    Noder  * head = NULL;
    FILE *inputFile = fopen("input01.txt", "r");
    FILE *outputFile = fopen("myoutput01.txt", "w");

    if (inputFile == NULL || outputFile ==NULL)
    {
        printf("ERROR OPENING FILE\n\n\n");
    }

    head = read(inputFile,buffer,length, head);
    fclose(inputFile);

    printReport(outputFile, head);

    // delete the tree after we print the stuff out
    deleteTree(head);
    head = NULL;

    printf("Tree deleted.\n");

    exit(0);
}

// recursive function to delete the tree and free the memory
void deleteTree(Noder* root) {

    if (root == NULL) return; // base case

    deleteTree(root->leftPtr);
    deleteTree(root->rightPtr);

    free(root);
}

// prints a repor of the words in the input file to the output file
// prints like this:
// word: count
// arguments are the root of the tree and the output file
// uses an inorder traversal to print in order
void printReport(FILE* outFile, Noder* root) {

    if (root != NULL) {

        printReport(outFile, root->leftPtr);

        // print everything to console
        printf("%s", root->word);
        printf(": ");
        printf("%i\n", root->count);

        // print to file
        fprintf(outFile, "%s", root->word);
        fprintf(outFile, ": ");
        fprintf(outFile, "%i\n", root->count);

        printReport(outFile, root->rightPtr);
    }
}

int length( char item[]){
    int length = 0;
    while (1 == 1){
        if (item[length] != '\0')
        {
            length++;
        }
        else
        {return length;}
    }
}


// if the word isnt found in the search then we need to insert it
// here we use recursion and the compare function to build the tree.
// I have 4 cases outlined. they are based on weather the node contains something in its
// childrens node and weather we need to go left or right.
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
            return 0;
        }

        else if ((int)left[i] < (int)right[i]){
            return 1;
        }
    }
    return 2;
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




Noder* read(FILE *file , char *buffer, long * position, Noder * head){
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
