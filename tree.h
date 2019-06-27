
#ifndef EX4_TREE_H
#define EX4_TREE_H

/* declaration of type */

typedef struct node{
    int data;
    int childrenCount;
    struct node **childrenList;
}Node;
/*declaration of the functions*/
void LeafList(Node ***list, Node **node, int *listCount);
void Insert(Node **node, int value);
Node* FindingNode(Node *tree, int n);
void Print(FILE** output,Node *nod);

#endif //EX4_TREE_H
