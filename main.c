#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/*
 * this code create the tree and prints the children of the tree from the desired node to the file "output.txt".
 * code has not deletion
 * */
int ReadFile1(char *arg, int *first, int *second);
void ReadFile2(char *arg, Node *tree);


int main(int argc, char **argv){

    int first[1000], second[1000];/*first[] : first column in input1 file; second[] : second column in input1 file*/

    printf("Enter the directory :\n");/*user must enter the file directory*/

    char* inp1 = (char*) malloc(sizeof(char)*100);/*the variable to hold the data in the file path to be entered.*/
    char* inp2 = (char*) malloc(sizeof(char)*100);/*the variable to hold the data in the file path to be entered.*/

    scanf("%s",inp1);
    scanf("%s",inp2);

    int n = ReadFile1(inp1, first, second);/*for reading first input file*/

    int NoN = n;        /* Number of Nodes */

    Node *tree = (Node*) malloc(sizeof(Node));/*the field for the tree to be created is opened.*/
    tree->data = first[0];                    /*data of tree's node*/
    tree->childrenCount = 0;                  /*child of tree's node.the counter is zero since there are no children at the beginning.*/
    tree->childrenList = NULL;                /*childrenlist of tree's node. have no children at the beginning that's why NULL */

    Node **leafList;
    int listCount;

    int x, y = 1, z = 0;
    for(n=0; n<NoN; n++){
        leafList = NULL;
        listCount = 0;

        LeafList(&leafList, &tree, &listCount);

        for(x=0; x<second[n]; x++){
            /*insert new node at the tree*/
            Insert( (leafList + ( x % listCount ) ), first[y] );
            y++;
            if( y == NoN ){/*checks whether the nodes to be added are finished.*/
                z = 1;
                break;
            }
        }
        if( z == 1 ){
            break;
        }
        x = 0;
    }

    ReadFile2(inp2, tree);/*for reading second input file*/

    return 0;
}
/*
 * this function read first input file.
 * first column hold the array that name is first;
 * and the second column hold the array that name is second.
 */
int ReadFile1(char *arg, int *first, int *second){
    FILE *f = fopen(arg, "r");                  /*open first input file*/
    char str[10];
    char *token = NULL;
    int n = 0;

    while(fgets(str, sizeof(str), f)){
        token = strtok(str, " ");
        *(first + n) = atoi(token);
        token = strtok(NULL, "\n");
        *(second + n) = atoi(token);
        n++;
    }
    fclose(f);
    return n;
}

/*
 * that function read second input file.
 * operates commands in that file
 */
void ReadFile2(char *arg, Node *tree){
    FILE *f = fopen(arg, "r");
    char str[10];
    char *token = NULL;
    FILE *output = fopen("output.txt","w");     /*creates output.txt file*/
    while(fgets(str, sizeof(str), f)){
        token = strtok(str, " ");
        if( strcmp(token, "l") == 0 ){
            token = strtok(NULL, "\n");
            int i;
            i = atoi(token);
            Node *tmp = NULL;
            tmp = FindingNode(tree, i);             /*finds node which will be the beginning of the listed nodes.*/
            if(tmp != NULL){
                Print(&output,tmp);
                fprintf(output,"\n");
            }
        }
    }
}
