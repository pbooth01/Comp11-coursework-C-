//WordFreqList Implementation
//Phillip Booth
#include <iostream>

using namespace std;

#include "WordFreqList.h"
//function returns an empty list
WordFreqList empty(void)
{
	return NULL;
}
//takes in a list and returns true if the list is empty and false otherwise
bool isEmpty(WordFreqList list)
{
	return list == NULL;
}
//function takes in a pointer to a list and a word and adds the word 
//to a linked list the function returns a pointer to the head of the list
WordFreqList prepend (Data new_data, WordFreqList list)
{
	if (isEmpty(list)){
		WordFreqNode *p_node = new WordFreqNode; //creation of node
		p_node->data = new_data;
		p_node->next = list;
		return p_node;
	}
	else {
		return insertAfter (new_data, list);
	}
}
//function takes in the pointer to the front of the list and returns the data
//in the head of the list
Data head (WordFreqList list)
{
	return list->data;
}
//function takes in the pointer to the front of the list and returns a 
//pointer to the tail of the list
WordFreqList tail (WordFreqList list)
{
	return list->next;
}
//function takes in a pointer to the list and also a word and inserts the 
//word into the list. returns a pointer to the front of the list
WordFreqList insertAfter (Data new_data, WordFreqList list)
{
	WordFreqNode *p_node = new WordFreqNode;
	p_node->data = new_data;
	WordFreqList temp_cur;
	WordFreqList temp_old;
	WordFreqList original;
	
	temp_cur = list;
	original = list;
	if (temp_cur->data.word > new_data.word){
		p_node->next = list;
		return p_node;
	}


	while (!isEmpty(list)){
		temp_cur = list;

		if (temp_cur->data.word < new_data.word){
			temp_old = temp_cur;
				if (temp_cur->next != empty()){
					temp_cur = temp_cur->next;
				}

				else{
					temp_cur-> next = p_node;
					return original;
				}
		}
		else if (temp_cur->data.word > new_data.word){
			temp_old->next = p_node;
			p_node->next = temp_cur;
			return original;
		}
		list = tail(list);
		}	
}
//function takes in a pointer to a list and delets the nodes of the list
//returns a pointer to the tail of the list
WordFreqList deleteHead (WordFreqList list)
{
	WordFreqList rest = tail(list);
	list->next = NULL;
	delete list;
	return rest;
}				
