#ifndef ST_H
#define ST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "fileReader.h"


// Structure of the Node
typedef struct node
{
	struct node* pCh;		// Pointer to child
	struct node* pSib;		// Pointer to sibling
	struct node* pPar;		// Pointer to parent
	struct node* sl;		// Suffix Link Pointer

	int id;			// ID of node

	int i;			// Start of edge Index
	int j;			// End of edge Index (including)
	int sd;			// String Depth
	int colour;

} Node;

typedef struct lcsCoordinate
{
	int x1;
	int y1;
	int x2;
	int y2;
} LcsCoordinate;

typedef struct fingerprint
{
	int x;
	int y;
} Fingerprint;

typedef struct adamFingerprint
{
	int count;
	Node* startNode;
	char* str;
} AdamFingerprint;

// Global variable that is a pointer top the root node
Node* pRoot;
char* gSeq;
int mix_colour;
int cur_colour;
int tipping_point;
int seq_len;
int gJ;
int cur_j;
int cur_i;
int node_count;
int inter_node;
int leafs;

// Description:
//	The function Creates a new Node with ID of global node_count
//	and Initiates start and end indexes to i and j
// Parameters:
//	int i start index of edge
//	int j end index of edge (including)
// Returns:
//	Pointer to new node
Node* New_Node(int i, int j, int sd, int id);

// Description:
//	Dealocates a tree starting from Node u
// Parameters:
//	Root of tree to dealocate
// Returns:
//	None
void Destroy_Tree(Node* u);

// Description:
//	The function checks if the node is a leaf node
// Parameters:
//	Node to check
// Returns:
//	Boolean value of True if Leaf
//	False if not a Leaf
bool Is_Leaf(Node* u);

// Description:
//	The function checks if the node is the root node
// Parameters:
//	Node to check
// Returns:
//	Boolean value of True if Root
//	False if not a Root
bool Is_Root(Node* u);

Node* Build_GSTree(char* l_seq, int start_ind[], int count);

int Colour_Tree(Node* u);

char* Get_Fingerprint(Node* node, int seq_num, int mix_colour);

Node* Find_Fingerprint(Node* node, int seq_num, int mix_colour);

LcsCoordinate* Get_LCS(Node* node);

Node* Find_LCS_Node(Node* node);

void Print_Node(Node* node);

// Description:
//	This function is in charge of adding to the tree and
//	building it up
//	tree is built on the global root
// Parameters:
//	Sequence on which to build tree and alphabet used in the sequence
// Returns:
//	Root Node passed back if build succesfull
//	NUll pointer if build unsucessfull
Node* Insert_Sequence(char* seq, int start_ind[], int count);

// Description:
//	Step 3 of IA
// Parameters:
//	Node v, index i and alpha 
// Returns:
//	New Leaf node that was created
Node* Case_IA(Node* v, int i, int alpha);

// Description:
//	Step 3 of IB
// Parameters:
//	Node v, index i
// Returns:
//	New Leaf node that was created
Node* Case_IB(Node* root, int i);

// Description:
//	Steps 4-6 for Case IIA
// Parameters:
//	Node, , index and beta
// Returns:
//	New Leaf node that was created
Node* Case_IIA(Node* u, Node* v_prime, int i, int alpha_prime, int beta);

// Description:
//	Steps 4-6 for Case IIB
// Parameters:
//	Node, root, index and beta
// Returns:
//	New Leaf node that was created
Node* Case_IIB(Node* u, Node* root, int i, int beta_prime);

// Description:
//	Finds path by matching each value, till mismatch
// Parameters:
//	Node to start matching from
// Returns:
//	New Leaf node that was created
Node* FindPath(Node* u, int i);

// Description:
//	Hops for nodes till beta amount is hoped
// Parameters:
//	U to start hops from
//	Index to hop from
//	Beta value
// Returns:
//	v node that a suffix link will point to
Node* NodeHops(Node* u, int i, int beta);

// Description:
//	This function looks for branch that starts with a specific char
//  If none is found returns false and found pointer is pointting at
//	Node to insert after or NULL (insert as the child of the parent)
// Parameters:
//	First Child node from node in whihc we are searching for char c
//	Node into which a node will be put if needed
// Returns:
//	bool that says if branch was found
//	found node pointer that point to the node if found
//	and if not found, the location of where to insert
bool Find_Branch(Node* u, char c, Node** found);

// Description:
//	Prints all children of Node u
// Parameters:
//	Node u to print children of
// Returns:
//	None
void Get_Children(Node* u, FILE* fp, char* seq);

// Description:
//	Enumerate nodes using DFS traversal (i.e., visit all
//	children from left to right AFTER visiting the parent)
// Parameters:
//	Node u to do DFS traversal from and count for line length
// Returns:
//	returns counts which helps with printing 10 chars a line
int DFS(Node* u, int count, FILE* fp);


// Description:
//	Enumerate nodes using post order traversal (i.e., visit all
//	children from left to right Before the parent)
// Parameters:
//	Node u to do DFS traversal from and count for line length
// Returns:
//	returns counts which helps with printing 10 chars a line
int Post_Order(Node* u, int count, FILE* fp);

// Description:
//	Enumerating ONLY the leaf node id's from left to right
//  (lexicographically smallest to largest) and prints them to desired output
// Parameters:
//	Node u to do BWT traversal from and count for line length
// Returns:
//	NONE
void BWT(Node* u, FILE* fp, char* seq);

// Description:
//	Enumerating ONLY the leaf node id's from left to right
//  (lexicographically smallest to largest) and prints them to desired output
//  with colours
// Parameters:
//	Node u to do BWT traversal from and count for line length
// Returns:
//	NONE
void BWT_Colour(Node* u, FILE* fp, char* seq);

// Description:
//	prints an enumerated leaf to desired output
// Parameters:
//	enumerated position, location to print and seq to print from
// Returns:
//	NONE
void print_BWT(int i, FILE* fp, char* seq);

// Description:
//	Function that can be used to count internal nodes from any "root" node
// Parameters:
//	Node u to do count from
// Returns:
//	Count of Internal Nodes (without root)
int Count_Internal_Nodes(Node* u);

// Description:
//	Function that can be used to count leaf nodes from any "root" node
// Parameters:
//	Node u to do count from
// Returns:
//	Count of Leaf Nodes (without root)
int Count_Leaf_Nodes(Node* u);

// Description:
//	Function that can be used to count total nodes from any "root" node
// Parameters:
//	Node u to do count from
// Returns:
//	Count of Total Nodes (without root)
int Count_Total_Nodes(Node* u);

// Description:
//	Function that can be used to count total string depth for all internal
// nodes from any "root" node
// Parameters:
//	Node u to do count from
// Returns:
//	Count of Total String Depth (without root)
int Total_SD(Node* u);

// Description:
//	Function that can be used to find deepest internal node from any "root" node
// Parameters:
//	Node u to do count from
// Returns:
//	Deepest internal node or NULL (without root)
Node* Deepest_Internal_Node(Node* u);

void Exact_Match_Repeat(Node* u, FILE* fp);

void GetFingerPrints(Node* curNode, AdamFingerprint* fingerprints, int mixedColor);

void Tree_Detailed_Print(Node* node);

#endif