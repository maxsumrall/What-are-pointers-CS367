#include "nodes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
 Jonathan Sumrall
 CS367
 Programming Lab 2
 */
/*
 given a linked list, calls free on each element in the list, and its sub elements. 
 PARAM: LINKEDLIST*
 */
void free_the_list(linkedlist * ll){
	while(ll != NULL){
		linkedlist * temp = ll->next;
		free(ll->dataNode);
		free(ll);
		ll = temp;}}
/*
 RETURNS a new linked list node
 */
linkedlist * newll_elt () {
	linkedlist *llp = (linkedlist *) malloc (sizeof(linkedlist));
	llp->dataNode = NULL;
	llp->next = NULL;
	return llp;}
/*
 returns a new graph node 
 PARAM: INT NAMEOFGRAPHNODE
 RETURNS: NEW GRAPH NODE
 */
nodeElement * newg_elt (int name) {
	nodeElement *gp = (nodeElement *) malloc (sizeof(nodeElement));
	gp->name = name;
	gp->visited = 1;
	gp->neighbor = newll_elt();
	return gp;}
/*
 given a linked list and the name of the node you want, returns 1 if it found the node, 0 if it did not find it.
 PARAM: LINKEDLIST*, INT TARGETNODENAME
 RETURNS: 1 IF FOUND, OTHERWISE 0
 */
int searchfornode(linkedlist * ll, int targetname){

	while (ll !=NULL){
		nodeElement * temp = ll->dataNode;
		if(temp == NULL){temp = newg_elt(0);}//short out
			if(temp->name == targetname){
				return 1;}
		else {ll = ll->next;}
	}
	return 0;}	
/*
 given a linked list and the name of the node you're interested in, returns the graph node from the linked list. 
 Better hope its in the list!
 PARAM: LINKEDLIST*, INT TARGETNODENAME
 RETURNS: NODEELEMENT *			GRAPHNODE THAT IT FOUND
 */
nodeElement * getnode(linkedlist * ll, int targetname){
	if(ll->dataNode->name == targetname){return ll->dataNode;}
	else {
		if(ll->next != NULL){
			return getnode(ll->next, targetname);}}}
/*
 given a node and a TTL, will visit the node and recursevly call visit node of all neighbors, decrementing TTL. 
 PARAM: NODE*, INT TTL
 */
void visitNode(nodeElement * node, int TTL){
	node->visited = 0;
	if (TTL != 0) {
		linkedlist * temp = node->neighbor;
		while (temp->next != NULL) {
			visitNode(temp->dataNode, TTL-1);
			temp = temp->next;}}}
/*
 given a linked list, traverses the linked list, setting all their graphNode elements "visited" field to 1. 1 means "not visited"
 PARAM: LINKED LIST*	
 */
void resetNodes(linkedlist * ll){
	while (ll->next != NULL) {
		ll->dataNode->visited = 1;
		ll = ll->next;
	}
	}
/*
 given a linked list, traverses the list and counts how many had their graph nodes visited field flagged.
 Has some bug, so I call resetNodes() and things work. 
 PARAM: LINKED LIST*
 RETURNS: INT COUNT				HOW MANY HAD THEIR VISITED FLAG RAISED
 */
int countVisitedAndReset(linkedlist * ll){
	int count = 0;
	while(ll ->dataNode != NULL){
		if(ll->dataNode->visited == 1){
			count++;}
		ll = ll->next;
	}
	
	return count;}
/*
 given a linked list and a graph node, appends the graph node to the list. Does not check for repeats
 PARAM: LINKED LIST*, NODEELEMENT*
 */
void addNode(linkedlist * ll, nodeElement * newNode){
	while (ll->dataNode != NULL) {
		ll=ll->next;
	}
	ll->dataNode = newNode;
	ll->next = newll_elt();}
/*
 given a linked list, a starting node, and the TTL, prettyly prints out how many
 unreachable nodes there are. Restores the "visited" flags when done.
 PARAM: LINKEDLIST*, INT STARTINGNODE, INT TTL
 */
void testing(linkedlist * masterListHead, int startingNode, int TTL){
	nodeElement * tempNode = getnode(masterListHead,startingNode);
	if(tempNode != NULL){
		visitNode(tempNode,TTL);}
	
		int visited = countVisitedAndReset(masterListHead);
	resetNodes(masterListHead);
		printf("%d nodes not reachable from node %d with TTL = %d\n",visited, startingNode,TTL);}
/*
 helper function for printGraph
 DO NOT USE
 */
void printGraphHelper(linkedlist * ll, int headName){
	if(ll != NULL){
		while(ll->dataNode != NULL){
			printf("%d --> %d\n", headName, ll->dataNode->name);
			ll = ll->next;
		}}}
/*
 prettly print out the connections in the graph. 
 PARAM: LINKEDLIST*, INT NAMEOFFIRSTNODEINLINKEDLIST
 */
void printGraph(linkedlist * ll, int headName){
	if(ll != NULL){
		while(ll->dataNode != NULL){
			printf("%d is set to %d\n",ll->dataNode->name, ll->dataNode->visited);
			printGraphHelper(ll->dataNode->neighbor, ll->dataNode->name);
			ll = ll->next;
		}}}
/*
 builds the graph structure. 
 PARAM: LINKEDLIST*, INT NUMBEROFCONNECTIONS
 */
void buildGraph(linkedlist * masterListHead,int connections){
		int iVal = 0;
		while(iVal < connections){
			int firstNode;
			int secondNode;
			
			fscanf(stdin, "%d", &firstNode);
			fscanf(stdin, "%d", &secondNode);
			/////////////////////////////////////////////
			nodeElement * nodeA;
			if(searchfornode(masterListHead,firstNode) == 1){
				nodeA = getnode(masterListHead,firstNode);}
			else {
				nodeA = newg_elt(firstNode);
				addNode(masterListHead,nodeA);
			}
			
			////////////////////////////////////////////
			nodeElement * nodeB;
			if(searchfornode(masterListHead,secondNode) == 1){
				nodeB = getnode(masterListHead,secondNode);}
			else {
				nodeB = newg_elt(secondNode);
				addNode(masterListHead,nodeB);
			}
			
			//////////////////////////////////////////////
			//printf("%d",nodeA->name);
			//printf("%d",nodeB->name);
			addNode(nodeA->neighbor,nodeB);
			addNode(nodeB->neighbor, nodeA);
			
			iVal++;
		}}
/*
 MAIN FUNCTION
 */
int main()
{
	
	linkedlist * masterListHead = newll_elt();
	int connections;
	fscanf(stdin, "%d", &connections);//how many node to node conenctions
	
	while(connections > 0){
		buildGraph(masterListHead,connections);
		int TTL;
		int startingNode;
		fscanf(stdin, "%d", &startingNode);
		fscanf(stdin, "%d", &TTL);
		int keepGoing = 1;
		int counter =1;
		printf("\n");
		while (keepGoing == 1) {
			printf("%d - ",counter);
			counter++;
			testing(masterListHead, startingNode,TTL);	
			fscanf(stdin, "%d", &startingNode);
			fscanf(stdin, "%d", &TTL);
			
			if(TTL == 0){
				if(startingNode == 0){
					keepGoing = 0;}}
			}
		free_the_list(masterListHead);//freeing all the graph nodes and linked list nodes
		masterListHead = newll_elt();
			
		fscanf(stdin, "%d", &connections);//how many node to node conenctions
		}
	return 0;
}
	




