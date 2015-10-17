//Philip Booth
//FrequencyTable.cpp
#include <iostream>
#include "FrequencyTable.h"

using namespace std;

//initializes the linked list WFList to empty
FrequencyTable::FrequencyTable()
{
	WFList = empty();
}
//takes in the linked list and a word and cycles through the linked list
//returns true if the word is in the list and returns false otherwise
bool FrequencyTable::in (string word)
{
	bool Located = false;
	WordFreqList temp = WFList;

	while (!isEmpty(temp)){
		if (head(temp).word == word){
			Located = true;
			return Located;
		}
		
		temp = tail(temp);
	}
	return Located; 
}
//takes in the linked list and a word and passes the word into the prepend
//function in the WordFreqList file. Does not return anything.
void FrequencyTable::insert (string word)
{
	bool Located;
	Data data;
	data.word = word;
	data.frequency = 1;
	Located = in(word);
	int freq;
	if (Located == false){
		WFList = prepend(data, WFList);
	}
	else if (Located == true){
		WordFreqList temp = WFList;
		while (!isEmpty (temp)){
			if (head(temp).word == word){
				freq = head(temp).frequency;
				freq = freq + 1;
				temp->data.frequency = freq;
					
			}
			temp = tail(temp);
		}
	}
}
//takes in the linked list and a word and returns the frequency that the word
//appears in the list				
int FrequencyTable::frequency (string word)
{
	bool Located;     //flag if a word is already in the list
	Located = in(word);
	WordFreqList temp = WFList;

	if (Located == false){
		return 0;
	}
	else if (Located == true){
		while (!isEmpty(temp)){
			if (head(temp).word == word){
				return head(temp).frequency;
			}
			temp = tail(temp);
		}
	}
}
//takes in the linked list and returns how many words are in the list
int FrequencyTable::size ()
{
	int sum = 0;
	WordFreqList temp = WFList;

	while (!isEmpty(temp)){
		sum = sum + 1;
		temp = tail(temp);
	}
	return sum;	 
}
//locates the nth word in the liked list and puts the corresponding frequency
//and string in the locations pointed to by the pointers *p_word/*p_frequency
void FrequencyTable::get (int n, string *p_word, int *p_frequency)
{
	int counter = 0;
	WordFreqList temp = WFList;
	if (n <= size()){
		while (!isEmpty(temp)){
			counter++;
			if (counter == n){
				p_word = &head(temp).word;
				p_frequency = &head(temp).frequency;
			}
			temp = tail(temp);
		}
	}
}
//takes in the liked list and destroys it to save memory		
void FrequencyTable::destroy ()
{
	while (!isEmpty(WFList)){
		WFList = deleteHead(WFList);
	}
}
//takes in the linked list and prints it
void FrequencyTable::print()
{
	WordFreqList temp_point;
	temp_point = WFList;
	while (!isEmpty(temp_point)){
		cout << head(temp_point).frequency << " "
		     << head(temp_point).word << endl;
		temp_point = tail(temp_point);
	}
	
}


