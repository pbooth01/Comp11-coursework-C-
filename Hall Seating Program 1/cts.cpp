//Modified by: Phillip Booth
// 3/06/2013
// cts.cpp
// purpose: allows people to selecet seats in a rectangular concert venue.
// the venue has 14 rows and 20 seats per row. The program reads from cin
// data and also allows people to make cancelations, print out a seating
// chart and end the program.

//Goals: the program tries to group people together first before it splits
//them up.  The program always tries to seat people as close to the stage 
//as possible before it fills the rows that are farther back.
 

#include <iostream>

using namespace std;

struct SEAT // values that go into each indivdual seat
{
	string occupant;
	double value;
};
// one dimensional array that will be used show a person the seats that they
// have been allocated when they run the request function.
/size of seating area

const int R = 14;
const int SPR = 20;

//operations:
void print_map              (SEAT seats[R][SPR], double total);
double reserve_space        (SEAT seats[R][SPR]);
double allocate_hi_check    (SEAT seats[R][SPR], string name, int tic_num); 	
double  allocate_hi_group   (SEAT seats[R][SPR], string name, int tic_num);
double allocate_hi_split    (SEAT seats[R][SPR], string name, int tic_num);
double allocate_any_check   (SEAT seats[R][SPR], string name, int tic_num);
double allocate_any_group   (SEAT seats[R][SPR], string name, int tic_num);
double allocate_any_split   (SEAT seats[R][SPR], string name, int tic_num);
double allocate_lo_check    (SEAT seats[R][SPR], string name, int tic_num);
double allocate_lo_groupone (SEAT seats[R][SPR], string name, int tic_num);
double allocate_lo_grouptwo (SEAT seats[R][SPR], string name, int tic_num);
double allocate_lo_groupL   (SEAT seats[R][SPR], string name, int tic_num);
double allocate_lo_split    (SEAT seats[R][SPR], string name, int tic_num);
double cancel               (SEAT seats[R][SPR]);
double price_finder_group   (SEAT seats[R][SPR], string name);
double price_finder_split   (SEAT seats[R][SPR], string name);
double cancel_revenue       (SEAT seats[R][SPR], string name);
void seat_display	    (SEAT seats[R][SPR], string name);

//Utilities:
void initialize_empty_seats (SEAT seats[R][SPR]);
void run_command_loop       (SEAT seats[R][SPR]);


int main ()
{
	SEAT seats[R][SPR];
	
	initialize_empty_seats(seats);
	run_command_loop(seats);
	
	return 0;

}
// Function takes in the 2D array seats.
// Function sets all of the spaces in the array to the string value "---".
// This value will then be interpreted as empty in the rest of the program.
// The function also sets each individual seat to a numerical value based
// on its position in the array.
void initialize_empty_seats (SEAT seats[R][SPR])
{
	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			seats[row][seat].occupant = "---";
			if ((seat > 3 || seat < 16) && row < 8){
				seats[row][seat].value = 200.0;
			}
			if ((seat < 4 || seat > 15) || row > 7){
				seats[row][seat].value = 150.0;
			}
		}
	}
}
// Function takes in the 2D array seats.
// Function acts as a kiosk function that has the user cin what they want
// the program to do.
void run_command_loop (SEAT seats[R][SPR])
{
	string choice;
	double total = 0.0;
	
	do {
		cin >> choice;
		
		if (choice == "RQ" || choice == "rq"){
			total += reserve_space(seats);
		}
		else if (choice == "PR" || choice == "pr"){
			print_map(seats, total);
		}
		else if (choice == "CA" || choice == "ca"){
			total -= cancel(seats);
		}
	
	} while (choice != "QU" || choice == "qu");
}
// Funtion takes in the 2D array seats and couts the array.
void print_map (SEAT seats[R][SPR], double total)
{
	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			cout << seats[row][seat].occupant << " ";
		}
		cout << endl;
	}
	cout << "revenue" << " " << total << ".00" << endl;
}
//Function takes in the 2D array seats.
// user inputs name, number of tickets, and price range. Then the program
// relays this information to seat allocation functions. The funtion
//returns the value of total.
double reserve_space (SEAT seats[R][SPR])
{
	string name;
	int tic_num;
	string price_range;
	int counter = 0;
	int max_tickets = 12;
	double total = 0.0;

	cin >> name;
	cin >> tic_num;
	cin >> price_range;

	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			if ( name == seats[row][seat].occupant ){
				counter++;
			}
		}
	}
	
	if (counter != 0){
		cout << "no" <<" "<< name <<" "<< "already-reserved" << endl;
	}	

	if (tic_num > max_tickets){
		cout << "no" << " " << name << " "<< "bad-number" << endl;
	}

	if (counter == 0 && tic_num <= max_tickets){
		
		if (price_range == "hi"){
			total = allocate_hi_check(seats, name, tic_num);
		}
		
		else if (price_range == "lo"){
			total = allocate_lo_check(seats, name, tic_num);
		}
		
		else if (price_range == "any"){
			total = allocate_any_check(seats, name, tic_num);
		}
	}
	return total;
}
//Function takes in the 2D array seats, a name, and the number of tickets
//and then checks to make sure that there are enough open seats in the
//hi priced section to fill the ticket order. The function returns
//the value of total.
double allocate_hi_check (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int counter = 0;
	double total = 0.0;

	for ( int row = 0; row < 8; row++){
		for ( int seat = 4; seat < 16; seat++){
			if (seats[row][seat].occupant == "---"){
				counter++;
			}
		}
	}
	if (counter >= num_of_tics){
		total = allocate_hi_group(seats, name, num_of_tics);
	}
	else if (counter < num_of_tics){
		cout << "no" << name << "not-available" << endl;
	}
	return total;	
}
//Function takes in the 2D array seats, a name, and the number of tickets.
//Function counts the number of consequtive empty seats in the same row
//in the high section of the array  and
//if they add up to the number of requested seats the function fills those
//seats in the array with the person's name. The function returns the value
//of total.
double allocate_hi_group (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int counter = 0; // marks number of open seats
	int times_allocated = 0; // marks whether seats have been allocated
	double total = 0.0;
	for ( int row = 0; row < 8; row++){
		counter = 0;
		for ( int seat = 4; seat < 16; seat++){
			if (seats[row][seat].occupant == "---"){
				counter++;
			}
			if (seats[row][seat].occupant != "---"){
				counter = 0;
			}
			if (counter == num_of_tics && times_allocated == 0){
				for( int allocator = seat; allocator > 
				   (seat - num_of_tics); allocator--){
					seats[row][allocator].occupant = name;
				}
				times_allocated++;
			}
		}
	}
	if (times_allocated != 0){
		cout << "ok" << " " << name << " ";
		total = price_finder_group(seats, name);
		cout << " ";
		seat_display(seats, name);
	}
	else if (times_allocated == 0){
		total = allocate_hi_split(seats, name, num_of_tics);
	}
	return total;
}
//Function takes in the 2D array seats, name, and the number of tickets.
//Function allocates a seat to any open seat in the high section of the array
//until the number of seats allocated is the same as the number of tickets
//requested. The function returns the value of total.
double allocate_hi_split (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int tracker = 0; //tracks seats being filled
	int times_allocated = 0; //traks number of times seats were allocated
	int allocator = num_of_tics;
	double total = 0.0;

	for ( int row = 0; row < 8; row++){
		for ( int seat = 4; seat < 16; seat++){
			if (seats[row][seat].occupant == "---" && 
			    tracker < allocator && times_allocated == 0){
				seats[row][seat].occupant = name;
				tracker++;
			}
		}
	}
	if (tracker == allocator){
		times_allocated++;
		cout << "ok" << " " << name << " ";
		total = price_finder_split(seats, name);
		cout << " ";
		seat_display(seats, name);
	}

	return total;
}
//Function takes in the 2D array seats, a name, and the number of tickets
//and then counts the number of empty seats in the array to see if there
//are enough open seats to fill the ticket number. The funtion returns
//the value of total.
double allocate_any_check (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int counter = 0;
	double total = 0.0;

	for ( int row = 0; row < R; row++){
		for ( int seat = 0; seat < SPR; seat++){
			if (seats[row][seat].occupant == "---"){
				counter++;
			}
		}
	}
	if (counter >= num_of_tics){
		total = allocate_any_group(seats, name, num_of_tics);
	}
	else if (counter < num_of_tics){
		cout << "no" << name << "not-available" << endl;
	}
	return total;
}
//Function takes in the 2D array seats, a name, and the number of tickets.
//Function counts the number of consequtive empty seats in the same row
//and if they add up to the number of requested seats the function fills those
//seats in the array with the person's name. The function returns the value
//of total.
double  allocate_any_group (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int counter = 0;
	int times_allocated = 0;
	double total = 0.0;

	for ( int row = 0; row < R; row++){
		counter = 0;
		for ( int seat = 0; seat < SPR; seat++){
			if (seats[row][seat].occupant == "---"){
				counter++;
			}
			if (seats[row][seat].occupant != "---"){
				counter = 0;
			}
			
			if (counter == num_of_tics && times_allocated == 0){
				for( int seat_giv = seat; seat_giv > 
				     (seat - num_of_tics); seat_giv--){
					seats[row][seat_giv].occupant = name;
				}
				times_allocated++;
			}
		}
	}
	if (times_allocated != 0){
		cout << "ok" << " " << name << " ";
		total = price_finder_group(seats, name);
		cout << " ";
		seat_display(seats, name);
	}
	else if (times_allocated == 0){
		total = allocate_any_split(seats, name, num_of_tics);
	}
	return total;
}
//Function takes in the 2D array seats, name, and the number of tickets.
//Function allocates a seat to any open seat in the the array
//until the number of seats allocated is the same as the number of tickets
//requested. The function returns the value of total.
double allocate_any_split (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int seat_trac = 0;
	int times_allocated = 0;
	int seat_giv = num_of_tics;
	double total = 0.0;

	for ( int row = 0; row < R; row++){
		for ( int seat = 0; seat < SPR; seat++){
			if (seats[row][seat].occupant == "---" && 
			     seat_trac  < seat_giv && times_allocated == 0){
				seats[row][seat].occupant = name;
				seat_trac++;
			}
		}
	}
	if (seat_trac == seat_giv){
		times_allocated++;
		cout << "ok" << " " << name << " ";
		total = price_finder_split(seats, name);
		cout << " ";
		seat_display(seats, name);
	}

	return total;
}
//Function takes in the 2D array seats, a name, and the number of tickets.
//the function breaks the lo section into 3 seperate 2D arrays and
//and then counts the number of empty seats in the lo sections of the array 
//to see if there are enough open seats to fill the ticket order number.
//The function returs the value of total.
double  allocate_lo_check (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int counter = 0;
	double total = 0.0;

	for ( int row = 0; row < 8; row++){
		for ( int seat = 0; seat < 4; seat++){
			if (seats[row][seat].occupant == "---"){
				counter++;
			}
		}
	}
	if (counter >= num_of_tics){
		total = allocate_lo_groupone(seats, name, num_of_tics);
	}
	else if (counter < num_of_tics){
		for ( int row = 0; row < 8; row++){
			for ( int seat = 16; seat < SPR; seat++){
				if (seats[row][seat].occupant == "---"){
					counter++;
				}
			}
		}
		if (counter >= num_of_tics){
			total = allocate_lo_groupone(seats, name, num_of_tics);
		}
		else if (counter < num_of_tics){
			for ( int row = 8; row < R; row++){
				for ( int seat = 0; seat < SPR; seat++){
					if (seats[row][seat].occupant == "---"){
						counter++;
					}
				}
			}
			if (counter >= num_of_tics){
			 total = allocate_lo_groupone(seats, name, num_of_tics);
			}
			else if (counter < num_of_tics){
				cout << "no" << name << "not-available" << endl;
			}
		}
	}
	return total;
}
//Function takes in the 2D array seats, a name, and the number of tickets.
//Function counts the number of consequtive empty seats in the same row
//in the first of 3 2D arrays that the lo section was broken up into.
//when the seats add up to the number of requested seats the function fills 
//those seats in the array with the person's name. The function returns the
//value of total.
double allocate_lo_groupone (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int counter = 0;
	int times_allocated = 0;
	double total = 0.0;

	for ( int row = 0; row < 8; row++){
		counter = 0;
		for ( int seat = 0; seat < 4; seat++){
			if (seats[row][seat].occupant == "---"){
				counter++;
			}
			if (seats[row][seat].occupant != "---"){
				counter = 0;
			}
			if (counter == num_of_tics && times_allocated == 0){
				for( int seat_giv = seat; seat_giv > 
				     (seat - num_of_tics); seat_giv--){
					seats[row][seat_giv].occupant = name;
				}
				times_allocated++;
			}
		}
	}
	if (times_allocated != 0){
		cout << "ok" << " " << name << " ";
		total = price_finder_group(seats, name);
		cout << " ";
		seat_display(seats, name);
	}
	else if (times_allocated == 0){
		total = allocate_lo_grouptwo(seats, name, num_of_tics);
	}
	return total;
}
//Function takes in the 2D array seats, a name, and the number of tickets.
//Function counts the number of consequtive empty seats in the same row
//in the second of 3 2D arrays that the lo section was broken up into.
//when the seats add up to the number of requested seats the function fills 
//those seats in the array with the person's name. The function returns the
//value of total.
double allocate_lo_grouptwo (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int counter = 0;
	int times_allocated = 0;
	double total = 0.0;

	for ( int row = 0; row < 8; row++){
		counter = 0;
		for ( int seat = 16; seat < SPR; seat++){
			if (seats[row][seat].occupant == "---"){
				counter++;
			}
			if (seats[row][seat].occupant != "---"){
				counter = 0;
			}
			if (counter == num_of_tics && times_allocated == 0){
				for( int seat_giv = seat; seat_giv > 
				     (seat - num_of_tics); seat_giv--){
					seats[row][seat_giv].occupant = name;
				}
				times_allocated++;
			}
		}
	}
	if (times_allocated != 0){
		cout << "ok" << " " << name << " ";
		total = price_finder_group(seats, name);
		cout << " ";
		seat_display(seats, name);
	}
	else if (times_allocated == 0){
		total = allocate_lo_groupL(seats, name, num_of_tics);
	}
	return total;
}
//Function takes in the 2D array seats, a name, and the number of tickets.
//Function counts the number of consequtive empty seats in the same row
//in the third of 3 2D arrays that the lo section was broken up into.
//when the seats add up to the number of requested seats the function fills
//those seats in the array with the person's name. The function returns
//the value of total.
double allocate_lo_groupL (SEAT seats[R][SPR], string name, int num_of_tics)
{
	int counter = 0;
	int times_allocated = 0;
	double total = 0.0;

	for ( int row = 8; row < R; row++){
		counter = 0;
		for ( int seat = 0; seat < SPR; seat++){
			if (seats[row][seat].occupant == "---"){
				counter++;
			}
			if (seats[row][seat].occupant != "---"){
				counter = 0;
			}
			if (counter == num_of_tics && times_allocated == 0){
				for( int seat_giv = seat; seat_giv > 
			             (seat - num_of_tics); seat_giv--){
					seats[row][seat_giv].occupant = name;
				}
				times_allocated++;
			}
		}
	}
	if (times_allocated != 0){
		cout << "ok" << " " << name << " ";
		total = price_finder_group(seats, name);
		cout << " ";
		seat_display(seats, name);
	}
	else if (times_allocated == 0){
		total = allocate_lo_split(seats, name, num_of_tics);
	}
	return total;
}
//Function takes in the 2D array seats, name, and the number of tickets.
//Function allocates a seat to any open seat in the low section of the array
//until the number of seats allocated is the same as the number of tickets.
//the function calls a price function and returns the value that the price
//function callculates.
double allocate_lo_split(SEAT seats[R][SPR], string name, int num_of_tics)
{
	int seat_trac = 0;
	int times_allocated = 0;
	int seat_giv = num_of_tics;
	double total = 0.0;

	for ( int row = 0; row < R; row++){
		for ( int seat = 0; seat < SPR; seat++){
			if (seats[row][seat].occupant == "---" && 
			     seat_trac  < seat_giv && times_allocated == 0){
				if((seat < 4 || seat > 15) ||  row > 7){
					seats[row][seat].occupant = name;
					seat_trac++;
				}
			}
		}
	}
	if (seat_trac == seat_giv){
		times_allocated++;
		cout << "ok" << " " << name << " ";
		total = price_finder_split(seats, name);
		cout << " ";
		seat_display(seats, name);
	}

	return total;
}
//function takes in the seating array and has the user cin the name
//they want to cancel. Everytime the name in the array is the same as the name
//that the user inputed the name in that index of the array gets the same
//string as what the seats were intialized to, to represent empty. The 
//function runs 12 times becuae that is the max number of tickets a person
//can order. the function returns the value of discount.
double cancel(SEAT seats[R][SPR])
{
	string name;
	int counter = 0;
	int max_reserve = 12;
	double discount = 0.0;

	cin >> name;
	discount = cancel_revenue(seats, name);

	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			if ( name == seats[row][seat].occupant ){
				counter++;
			}
		}
	}
	if (counter == 0){
		cout << "no" << " " << name << " " << "no-reservation" << endl;
	}	
	else if (counter != 0){
		for (int cancel_num = 0; cancel_num < max_reserve; 
			cancel_num++){
			for (int row = 0; row < R; row++){
				for (int seat = 0; seat < SPR; seat++){
				     if ( name == seats[row][seat].occupant ){
					      seats[row][seat].occupant = "---";
					}
				}
			}
		}
		cout << "ok" << " " << name << " " << "cancelled" << endl;
	}
	return discount;
}	
//fuction takes in 2D array seats and a name. It counts up the number 
//of seats in the array that are then same as the name and adds
//the value of the seat to a vaiable sum. The function returns sum.
double price_finder_group (SEAT seats[R][SPR], string name)
{
	double sum = 0.0;

	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			if (name == seats[row][seat].occupant){
				sum += seats[row][seat].value;
			}
		}
	}
	cout << sum << endl;
	return sum;
}
//fuction takes in the 2D array seats and a name. It counts up the number 
//of seats in the array that are the same as the name and adds
//the value of the seat multiplied by the discount (.9)
//to a vaiable sum. returns the value of sum.
double price_finder_split (SEAT seats[R][SPR], string name)
{
	double sum = 0.0;
	int counter = 0;
	double discount = .9;
	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			if (name == seats[row][seat].occupant){
				counter++;
			}
		}
	}
	if (counter == 1){
		for (int isle = 0; isle < R; isle++){
			for ( int spaces = 0; spaces < SPR; spaces++){
				if (name == seats[isle][spaces].occupant){
					sum += seats[isle][spaces].value;
				}
			}
		}
	}	
	if (counter != 1){
		for (int i = 0; i < R; i++){
			for (int j = 0; j < SPR; j++){
				if (name == seats[i][j].occupant){
					sum += ((seats[i][j].value) * discount);
				}
			}
		}
	}
	cout << sum << endl;
	return sum;
}
//function takes in the 2D array seats and a name.
//the function runs through the entire function and everytime
//that the string in the index equals the variable name the function
//adds to a counter.  Then the function goes back through the array
//the first time it gets a value that matches name it starts a for
//loop that runs betwwen the current seat and the value of the current
//seat plus the value of the counter from the previous for loop.
//everytime a value in this new for loop equals name another counter gets
//added to.  It then compares the two counters and if they are the same
//adds a  regular value ticket order to a variable discount.  If they are 
//not the same it adds a discounted ticket value order to a variable discount.
//the function returns the value of discount.
double cancel_revenue (SEAT seats[R][SPR], string name)
{
	int match = 0;
	int counter = 0;
	int already_matched = 0;
	double sum = 0.0;
	double sum_split = 0.0;
	double discount_rate = .9;
	double discount = 0.0;

	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			if (seats[row][seat].occupant == name){
				match++; //counter 1
				sum_split += seats[row][seat].value;
			}
		}
	}
	for (int i = 0; i < R; i++){
		for (int j = 0; j < SPR; j++){
			if (name == seats[i][j].occupant){
			      for(int marker = j; marker < j + match; marker++){
					if (name == seats[i][marker].occupant 
					    && already_matched == 0){
						counter++; //counter 2
						sum += seats[i][marker].value;
					}
				}
				already_matched++;
			}
		}
	}
	if (counter == match){
		discount = sum;
	}
	else if (counter != match){
		discount = (sum_split * discount_rate);
	}
	return discount;
}
//function gets the 2D array seats and a name. It runs through the entire
//array and every time that an index of the array equals name it prints out
//a letter value from a different array that corresponds to the row number of the
//2D array seats.
void seat_display (SEAT seats[R][SPR], string name)
{
	int num = 0;
	char letter[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
			  'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			if (seats[row][seat].occupant == name){
				num++;
			}
			
		}
	}
	cout << num;
	for (int row = 0; row < R; row++){
		for (int seat = 0; seat < SPR; seat++){
			if (seats[row][seat].occupant == name){
				cout << " " << letter[row] << seat + 1 << " "; 
			}
		}
	}
	cout << endl;
}