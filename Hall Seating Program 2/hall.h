#ifndef HALL_H
#define HALL_H
#include <iostream>
#include <string>
//Phillip Booth
//date: 4/01/2013

using namespace std;
const int ROW = 14;
const int SPR = 20;

struct Order		//Struct of what goes into each individual order
{
	string name;
	int tic_num;
	string price;
	int day;
};
struct SEAT		//Struct of what goes into each seat
{			//name and value of the seat
	string occupant;
	double value;
};

class Hall
{
public:

Hall();
void print_map();	
bool cancel(Order order);
bool request(Order order);
private:

bool hi_check(Order order);
bool lo_check(Order order);
bool any_check(Order order);
void allocate_hi(Order order);
void allocate_lo_one(Order order);
void allocate_lo_two(Order order);
void allocate_lo_thr(Order order);
void allocate_lo_split(Order order); //places seats in low section(not grouped)
void allocate_lo_any(Order order);  
void allocate_hi_any(Order order, int counter);

double price_finder(Order order); //finds price of each individual order
void seat_print(Order order);	//attaches the letters to each seat order

SEAT seat_chart[ROW][SPR];	//array of seats
};
#endif
