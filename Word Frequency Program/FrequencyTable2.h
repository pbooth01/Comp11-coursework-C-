//Phillip Booth
//FrequencyTable1.h
#ifndef Frequency_Table
#define Frequency_Table
#include <iostream>
#include <string>
#include "WordFreqList.h"

using namespace std;

class FrequencyTable
{

public:
FrequencyTable(); //constuctor that initializes the Table
bool in(string word); //indicates whether a word is in the table or not
void insert(string word); //sends a word to the insert funtion in WordFreqList
                          //file
int frequency(string word);//returns the number of times a word is in list
int size();  //returns the number of words in the list

void get(int n, string *p_word, int *p_frequency); //finds nth word and puts
                                                   //corresponding string and
					           //freq in pointer locations
void destroy(); //destroys the list
void print(); //prints the list
WordFreqList WFList;
private:



};
#endif

