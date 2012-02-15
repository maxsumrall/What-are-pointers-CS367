/*
 *  nodes.h
 *  
 *
 *  Created by Jonathan Sumrall on 11/14/11.
 *  Copyright 2011 Personal. All rights reserved.
 *
 
 
 
 How the data strucures work is that I have an impementation of linked lists. 
 These linked lists have graph nodes in them (nodeElement). 
 These graph nodes have a linked list of all of their neighbor nodes. 
 
 Globally, there is a master list containing all graph nodes that have
 been created. 
 */

typedef struct ll_node {
	struct ll_node * next;//the next node in a basic linked list implementation
	struct g_node * dataNode; //pointer to graph nodes
} linkedlist;

typedef struct g_node {
	int name;
	int visited;
	struct ll_node * neighbor; //basic linked list containing neighbors
} nodeElement;