#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
/*
 * find leaf nodes in the tree
 * and keeps them in the array which name is "list".
 * arguments are list, node, listCount
 * list used for leaf nodes
 * node used for finding desired node
 * listCount used for the number of leaf nodes
 */
void LeafList(Node ***list, Node **node, int *listCount){
    if( ( *(node) )->childrenList == NULL ){   /*if the node has no children, it is a leaf node.*/
        if( *(listCount) < 1 ){                 /*and then add it to list array*/
            *(listCount) = 1;
            *(list) = (Node**) malloc( *(listCount) * sizeof(Node*) );
            *( *( list ) + ( *(listCount) - 1 ) ) = *node;
        } else{                                 /*if list is not empty then run this code block*/
            *(listCount) += 1;
            *(list) = (Node**) realloc( *(list), *(listCount) * sizeof(Node*) );
            *( *( list ) + ( *(listCount) - 1 ) ) = *node;
        }
    } else {                                    /*If there is a child of the node, the child of this node is looked after.*/
        int i = 0;
        while( i != ( *(node) )->childrenCount ){
            LeafList( list, ( ( *(node) )->childrenList + i ), listCount );
            i++;
        }
    }
    return;
}
/*
 * this function is used to add nodes to the tree.
 * function's arguments are node and value
 * node used for node to be added
 * value used for the data of node to be added
 */
void Insert(Node **node, int value) {
    if (*(node) == NULL) {                  /*if the node is null, then add the new node here*/
        *(node) = (Node *) malloc(sizeof(Node));
        (*(node))->data = value;
        (*(node))->childrenCount = 0;
        (*(node))->childrenList = NULL;
        return;
    }
    if ((*(node))->childrenCount == 0) {    /*if the node has no children, then it creates list for hold the child nodes. */
        (*(node))->childrenCount += 1;
        (*(node))->childrenList = (Node**) malloc((*(node))->childrenCount * sizeof(Node*));
        *((*(node))->childrenList + ((*(node))->childrenCount - 1)) = NULL;
        Insert(((*(node))->childrenList + ((*(node))->childrenCount - 1)), value);
    } else {                                /*if the node has children, then increases the size of the list which keeps the child nodes.*/
        (*(node))->childrenCount = (*(node))->childrenCount + 1;
        (*(node))->childrenList = (Node**) realloc((*(node))->childrenList, (*(node))->childrenCount * sizeof(Node*));
        *((*(node))->childrenList + ((*(node))->childrenCount - 1)) = NULL;
        Insert(((*(node))->childrenList + ((*(node))->childrenCount - 1)), value);
    }
}
/*
 * this function used to find desired node.
 * function's arguments are node and n
 * node is desired node
 * n is the value of desired node
 */
Node* FindingNode(Node *node, int n){
    if( node != NULL ){                 /*if the node is not null then it looks tree*/
        if( node->data == n ){          /*if the desired node is equal to the looking node,then returns that node*/
            return node;
        } else{                         /*if the desired node is not equal to the looking node, then look the tree's other nodes*/
            int i;
            Node *tmp = NULL;
            for(i=0; i<node->childrenCount; i++){
                tmp = FindingNode( *(node->childrenList +i), n);
                if( tmp != NULL ){
                    break;
                }
            }
            return tmp;
        }
    } else{
        return NULL;
    }
}
/*
 * prints the list beginning from desired node
 * arguments are output and node
 */
void Print(FILE** output,Node *node){
    if(node){
        int i = 0;
        fprintf(*output,"%d ", node->data);
        while( i < node->childrenCount ){
            Print(output, *( node->childrenList + i) );
            i++;
        }
    }
}

