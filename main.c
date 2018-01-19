#include <stdio.h>
#include <stdlib.h>

typedef struct Noder Noder;

struct Noder{
    char word[10];// assume that the word is less that 15 characters long
    int count;
    Noder* leftPtr;
    Noder* rightPtr;

};
const char input1[] = "input01.txt";
const char input2[] = "input02.txt";
const char output1[] = "outputStudent01.txt";
const char output2[] = "outputStudent02.txt";
//char* ReadFile(char fileName[], char *buffer, long * length);
//FILE * ReadFile(FILE *InputFile , char *buffer, long * position);
int compare(char left[],char right[] );
Noder* read(FILE *file , char *buffer, long * position,  Noder * head);
Noder * searchTree(Noder * head, char item[]);
int length( char item[]);
void insert(Noder * head, char item[]);

int main(int argc, char **argv) {


    char *buffer = NULL;
    long * length;
    Noder  * head = NULL;
    FILE *InputFile = fopen("input02.txt", "r");
    head = read(InputFile,buffer,length, head);


    int some = 3;
if there are repeats we cannot add them to the tree. instead we must increment the count.
            implement a search function
            implement a inorder traversal



//    some = compare("this", "that");
//    if (some == 0) {
//        printf("%s comes before %s", "that","this");
//    }
//    else if (some == 1) {
//        printf("%s comes before %s", "this","that");
//    }
//    else {
//        printf("they are equal ");
//    }
    exit(0);
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
        puts(head->word);
        head->count = 1;
        return;
    }
    int direction = compare(head->word,item);
    // if the current root is the word
    if (direction ==2)
    {
        head->count++;// if found increment the count on it
    }


    // else if the head's word comes first alphabetically
    if (direction ==1 && head->rightPtr != NULL)
    {
        return insert(head->rightPtr, item);// search right
    }
    // else if the word comes first
    if ( direction==0 && head->leftPtr!= NULL)
    {
        return insert(head->leftPtr, item);// search left
    }

    // otherwise we are at null so make a new node and insert the item
    if (direction==1 && head->rightPtr == NULL)// if the word is alphabetically less than the parent and the node is available
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

        return;
    }
    if ( direction==0 && head->leftPtr == NULL)// if the word is alphabetically greater than the parent and the node is available
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


// weird function that i developed and deleted


//Searches for the node in the tree by using the compare function.
//if this function doesn't find the word in the tree them it returns
//NULL. Otherwise it returns the pointer to the node.
//Noder * searchTree(Noder  * head, char item[]){
//    if (head == NULL)
//    {
//        return head;
//    }
//
//    // 0 means that LEFT operand comes first alphabetically
//    // 1 means that RIGHT operand comes first alphabetically
//    // 2 means they're equal.
//
//    int direction = compare(head->word,item);
//    // if the current root is the word
//    if (direction ==2)
//    {
//        head->count++;// if found increment the count on it
//        return head;
//    }
//    // else if the head's word comes first alphabetically
//    if (direction ==1 && head->rightPtr != NULL)
//    {
//        return searchTree(head->rightPtr, item);// search right
//    }
//    // else if the word comes first
//    if ( direction==0 && head->leftPtr!= NULL)
//    {
//        return searchTree(head->leftPtr, item);// search left
//    }
//
//    // otherwise we didn't find it
//    if (direction==1 && head->rightPtr == NULL)
//    {
//        return NULL;
//    }
//    if ( direction==0 && head->leftPtr!= NULL)
//    {
//        return NULL;
//    }
//}




Noder* read(FILE *file , char *buffer, long * position, Noder * head){
                char word[1024];
                /* assumes no word exceeds length of 1023 */
                //https://stackoverflow.com/questions/16400886/reading-from-a-file-word-by-word

                head = (struct Noder *)malloc(sizeof(struct Noder));
                head->word[0] = '\0';
                while (fscanf(file , " %1023s", word) == 1) {
                    puts(word);
                    // search for the word
     //               head = searchTree( head, word);
                    insert(head ,word);
                }
            return head;
        }
