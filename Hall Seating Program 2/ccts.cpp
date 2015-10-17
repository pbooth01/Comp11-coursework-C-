//Phillip Booth
//date: 4/02/2013

//program is a seating program for the same concert venue for a week.
//the program works to seat people in groups and then splits them up.
//If a person requests a price any the program seats them in the lower
//section first in order to keep the hi priced seats empty. If people
//are split up it gives them a discount.

#include "hall.h"
#include <sstream>
#include <stdexcept>
const int day_num = 7;

int string2int(string s);

int main()
{
	Hall place[day_num];
 	string action, name, price;
	int tic_num;
	int day;
	bool success = false; //keeps track of were seats allocated
	bool allocated = false; //keeps track of were seats allocated
	string any_all;
	Order order;
	int day_any = -1; //used to keep track of the day while day equals any

	do{
		cin >> action;
		if (action == "rq"){
			cin >> order.name >>order.tic_num >>order.price >> any_all;
			allocated = false;
			day_any = -1;
			if (any_all == "any"){
				for (int r = 0; r < 7; r++){ 
					if ( allocated == false){
					   day_any++;
				           order.day = day_any;
					   allocated = place[r].request(order);
					}
				}
			}
			else{
				order.day = string2int(any_all);
				if (order.day >= 0 && order.day < 8){
				    allocated = place[order.day].request(order);
				}
				else{
				     cout<<"no"<<" "<<name<<" "<< "bad-number";
				}
			}
		}
		else if (action == "ca"){
			cin >> order.name >> any_all;
			order.day = string2int(any_all);
			if (order.day >= 0 && order.day < 8){
				success = place[order.day].cancel(order);
			}
			else{
				cout<<"no"<<" "<<name<<" "<< "bad-number";
			}
		}
		else if (action == "pr"){
			cin >> any_all;
			if (any_all == "all"){
				for(int days = 0; days < 7; days++){
					place[days].print_map();
				}
			}
			else{
				order.day = string2int(any_all);
				if (order.day >= 0 && order.day < 8){
					place[order.day].print_map();
				}
				else{
				    cout <<"no"<<" "<<name<<" "<< "bad-number";
				}
			}
		}
	}while (action != "qu");
	exit(1);
	
}
//the function converts a string to an integer. It takes a string as a 
//parameter and then returns an int. This program was given to me by
//mark sheldon.
int string2int(string s)
{
	stringstream ss(s);
	int result;

	ss >> result;
	if (ss.fail())
	
		throw(runtime_error("string2int:non-numeric value: " + s));

	return result;
}	
