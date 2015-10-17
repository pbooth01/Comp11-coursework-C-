#include <iostream>

#include "WordFreqList.h"

using namespace std;

void command_loop (void);
string get_command(void);
void prompt_for_command(void);
WordFreqList prepend_cmd(WordFreqList list);
void print (WordFreqList list);

int main ()
{
	command_loop();
	return 0;
}

void command_loop(void)
{
	string cmd;
	WordFreqList list = empty();

	while ((cmd = get_command ()) != "quit"){
		if (cmd == "print"){
			print(list);
			cout << endl;
		}
		else if (cmd == "prepend"){
			list = prepend_cmd(list);
		}
	}
}

string get_command(void)
{
	string cmd;
	
	prompt_for_command();
	cin >> cmd;
	return cmd;
}

void prompt_for_command(void)
{
	cout << "prepend to list" << endl
	     << "print the list" << endl
	     << "quit" << endl
	     << ": ";
}

WordFreqList prepend_cmd (WordFreqList list)
{
	Data  new_data;
	new_data.frequency = 1;
	cout << "Enter word to prepend: ";
	cin >> new_data.word;
	return prepend(new_data, list);
}

void print (WordFreqList list)
{
	cout << "[";
	while (!isEmpty(list)){
		cout << head(list).word;
		if (!isEmpty(tail(list))){
			cout << ", ";
		}
		list = tail(list);
	}
	cout << "]";
}

