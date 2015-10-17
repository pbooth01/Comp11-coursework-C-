//Phillip Booth
//FrequencyTable.h
#ifndef Frequency_Table
#define Frequency_Table
#include <iostream>
#include <string>
#include "WordFreqList.h"

using namespace std;

class FrequencyTable
{

public:
FrequencyTable();
bool in(string word);  //checks if a word is already in the list
void insert(string word); //inserts a word into the list
int frequency(string word);  //checks how many times a word is in the list
int size();  //returns how many words are in the list
void get(int n, string *p_word, int *p_frequency); //locates the nth word
						  //and puts in the 
						  //corresponing W/F pair
void destroy(); //destroys a list
void print();  //prints a list
WordFreqList WFList; 
private:



};
#endif
