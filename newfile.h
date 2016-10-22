#ifndef NEWFILE_H
#define NEWFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define BUFFER_SIZE 256
#define N 1000
#define FLAGS 2
//listnode Id is basicaly our data of the Node
typedef int listNodeId;

typedef struct listNode lnode;
//listNode is out vertical Node every new Node will be added to the list
struct listNode {
  listNodeId id;
  int visited;
  int incoming;
  int outgoing;
  int countedge;
  int countInEdge;
  struct listEdge *edge;
  //struct listNode *next;
};

typedef struct listEdge ledge;

//every new connection will have a listedge in this case we make our matrix
struct listEdge {
  struct listNode *linkToLnode;
  struct listEdge *next;
  double transaction;
};


typedef struct bucketmember BucketMember;

//objects of the bucket
struct bucketmember{
        int key;
        lnode *p;
};

typedef struct bucket Bucket;
//the bucket
struct bucket {
        BucketMember * bucketarray;
        int count;
        int size;
};
//o pinakas twn bucket kathe thesh deixnei se ena bucket
Bucket ** BucketArray;
Bucket * p;


// Infos struct 
struct infos {
        // to arxiko plhthos stoixeiwn enos bucket
        int startbucketsize ;
        // to plhthos twn stoixeiwn tou hashtable
        int countentries;
        char *DataFile;
        // to megethos tou buffer kathe fora
        int bufsize;
	// edw mpainoun oi entoles tou xrhsth meta to parsing
	char *commandsarray[N];
	// o arithmos twn entolwn tou xrhsth
	int commandsarraysize;
	// edw mpainoun arxika oti dinei o xrhsths apo to prompt ths efarmoghs
	char buffer[BUFFER_SIZE];
        //filename for the output
        char filename[25];
        int cyclesExists ;
} Infos;

// Is the Linked List For Printing Purposes of the recursive functions
struct Node {
	int data;
	struct Node* next;
};



//our graph We Dont Use this Pointers any more
//was only implement before we add the hash table!!!
typedef struct graph graphos;
struct graph {
  lnode *lnptr;
};
typedef struct graph *graphs;


//Functions Of Our Programm

//Function To check the user input @run
void checkargs(int argc, char **argv);
//Function To Parse the arg tou our programm
void parsingargs(int argc, char **argv);
//Function to make our User Interfase
char parsingcommandline();
//Function to Initialize the Hush table
void initHashtable(int k);
//Function to Initialize our flags arrays
void initarrays();
//Function to read the Commands from the file
void readexecopfile();
//Function to trim white spaces
void trimwhitespace(char *str) ;
//Function for User Interface
char parsingcommandline();
//Free memory Function
void freememory();
//init the graph .Helper function we dont use it
graphs InitGraph();
//add node function
lnode *addNode(listNodeId id);
//search the graph .Helper function we dont use it
lnode *searchInGraph(graphs graph, listNodeId id);
//search node in the hastable
lnode *searchGraphWithHashtable(listNodeId id);
//functions for adding the Node
void bucketentry(lnode *node);
void putinbucket(BucketMember temp, int position);
//hash function
int hashfunction1(int key);
//helper Function that prints the Hash table
void printhashtable();
// helper function that print all the edges of a Node
void printedge(listNodeId id1);
//Function That deletes the Node from the Hash Table
void dellFromHashTable(listNodeId id);
//Function That deletes the Node
void dellNode(listNodeId id) ;
//Function that add an edge
void addEdge(listNodeId id1, listNodeId id2, double amount);
//Function that updates the edge transaction
void edgeupdate(lnode* lnode1, lnode* lnode2, double amount);
//function that checks if the edge exists
int checkEdge(lnode* lnode1, lnode* lnode2);
//Function that delete an edge
void dellEdge(listNodeId id1, listNodeId id2);
// the true Delete Edge Function
void retEdge(lnode* lnode1, lnode* lnode2);
// function that prints all incoming transactions
void lookupIn(listNodeId id);
// function that prints all outgoing transactions
void lookupOut(listNodeId id);
// function that prints the summary of all incoming and outgoing transactions
void lookupSum(listNodeId id) ;
// helper function tha checks if we can call isTriangle
void helperTriangle(listNodeId id,double k) ;
// function that checks for triangels transactions
int isTriangle(listNodeId dest, lnode *startP,double k);
//Function that set visited to Zero
void setvisetedXero();
//Function that helps Conn
void helperConn(listNodeId id1,listNodeId id2);
//Function that Check if there is a path between 2 nodes
int conn(listNodeId dest, lnode *startP);
// Function To put in queue a Node Id..Is for only for a Good Printing
void Enqueue(int x);
// Function To pop a Node from the queue ..Is  only for a Good Printing
void Dequeue() ;
// Function To pop the fisrt Node from the queue ..Is  only for a Good Printing
int Front();
// Function that prints the queue ..Is  only for a Good Printing
void PrintL() ;
// Function that prints the queue is Used only in traceflow function ..Is  only for a Good Printing
void PrintLwithAmount() ;
// Function that free the memory of the queue..Is  only for a Good Printing
void freeStackList();
//helper Function that will call cycle
void mycycle(listNodeId dest);
//Function that found all the cycles in our Graph
int cycle(listNodeId dest, lnode *startP, int depth);
//helper Function that will call trace
void tracehelper(listNodeId id1, int total);
//Function that traces the N depth and print the total amount of transactions
int trace(lnode *startP, listNodeId id, int depth, int total);
// Function that return the transaction of an edge
double getEdgeTransaction(listNodeId id1, listNodeId id2);
//Function tha will Print the Graph - node
void printTheNode(listNodeId id1);
//Function tha will Print the Graph
void printTheGraph();
//Function for implementing bye
void freeThemALl();
//Function to delete all edge list and after all the Node
void freeAllEdge(lnode* lnode);
//Function for the Bonus
void dump();
#endif  /* NEWFILE_H */

