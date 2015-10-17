//Phillip Booth
//WordFreq.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include "FrequencyTable.h"

using namespace std;
const int LETTERS = 26;

int main()
{
	char filename[50];
	
	FrequencyTable Table[LETTERS];  //Code for inputing data from a text
	string data;                    //file. Could not find code for it on
	ifstream fin;                   //piazza so I got it from the internet. 
	cin.getline(filename, 50);      //the way it works is you run
	fin.open(filename);             //WordFreq.cpp and then enter the name
	if (!fin.is_open()){            //of the file including the .text
		exit(EXIT_FAILURE);     // ex: "who-put-the-bomp.text"
	}
	
	char word[50];
	fin >> word;
	while(fin.good()){
		word[0] = tolower(word[0]);
		if (word[0] == 'a'){ 
			Table[0].insert(word);
		}
		if (word[0] == 'b'){ 
			Table[1].insert(word);
		}
		if (word[0] == 'c'){ 
			Table[2].insert(word);
		}
		if (word[0] == 'd'){ 
			Table[3].insert(word);
		}
		if (word[0] == 'e'){ 
			Table[4].insert(word);
		}
		if (word[0] == 'f'){ 
			Table[5].insert(word);
		}
		if (word[0] == 'g'){ 
			Table[6].insert(word);
		}
		if (word[0] == 'h'){ 
			Table[7].insert(word);
		}
		if (word[0] == 'i'){ 
			Table[8].insert(word);
		}
		if (word[0] == 'j'){ 
			Table[9].insert(word);
		}
		if (word[0] == 'k'){ 
			Table[10].insert(word);
		}
		if (word[0] == 'l'){ 
			Table[11].insert(word);
		}
		if (word[0] == 'm'){ 
			Table[12].insert(word);
		}
		if (word[0] == 'n'){ 
			Table[13].insert(word);
		}
		if (word[0] == 'o'){ 
			Table[14].insert(word);
		}
		if (word[0] == 'p'){ 
			Table[15].insert(word);
		}
		if (word[0] == 'q'){ 
			Table[16].insert(word);
		}
		if (word[0] == 'r'){ 
			Table[17].insert(word);
		}
		if (word[0] == 's'){ 
			Table[18].insert(word);
		}
		if (word[0] == 't'){ 
			Table[19].insert(word);
		}
		if (word[0] == 'u'){ 
			Table[20].insert(word);
		}
		if (word[0] == 'v'){ 
			Table[21].insert(word);
		}
		if (word[0] == 'w'){ 
			Table[22].insert(word);
		}
		if (word[0] == 'x'){ 
			Table[23].insert(word);
		}
		if (word[0] == 'y'){ 
			Table[24].insert(word);
		}
		if (word[0] == 'z'){ 
			Table[25].insert(word);
		}

		fin >> word;
	}
	for (int i = 0; i < 26; i++){
		Table[i].print();
		Table[i].destroy();
		}
	system ("pause");
	return 0;
}
