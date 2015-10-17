//Phillip Booth
//WordFreqList.h
#include <iostream>
#include <string>

using namespace std;

#ifndef __WORDFREQLIST_H__
#define __WORDFREQLIST_H__
struct Data           //strust of the data in the head of each list node
{
	string word;
	int frequency;
};
struct WordFreqNode  //struct of the data in each node
{
	Data data;
	WordFreqNode *next;
};

typedef WordFreqNode *WordFreqList; //defines WordFreqList as a pointer

WordFreqList empty      (void);  //returns a empty list
bool    isEmpty         (WordFreqList list);//checks if a list is empty
WordFreqList prepend    (Data new_data, WordFreqList list);//adds data to list
Data     head         (WordFreqList list);//returns data in the head of list
WordFreqList tail       (WordFreqList list);//returns the list in the tail
WordFreqList deleteHead (WordFreqList list);//deletes the first list node and
					    //returns its tail
WordFreqList insertAfter (Data new_data, WordFreqList list);//adds data to list 
void set_freq           (WordFreqList list, Data new_data);//updates frequency
							   //in a node
#endif
