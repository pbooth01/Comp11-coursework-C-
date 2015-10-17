//Phillip Booth
// date: 4/01/2013


#include "hall.h"

//takes in the seat array and sets each section of the array equal to "---"
//also gives each seat a specific numeric value based on its position in the
//array
Hall::Hall()
{
	for (int r = 0; r < ROW; r++){
		for (int c = 0; c < SPR; c++){
			Hall::seat_chart[r][c].occupant = "---";
			if ((c > 3 || c < 16) && r < 8){
				Hall::seat_chart[r][c].value = 200.00;
			}
			if ((c < 4 || c > 15) || r > 7){
				Hall::seat_chart[r][c].value = 150.00;
			}
		}
	}
} 
//takes in the seat array and prints the string value that is in each
//individual seat.  Also calculates the revenue that the venue is
//recieving from that particual seating array.
void Hall::print_map()
{
	double revenue = 0.00;

	for (int r = 0; r < ROW; r++){
		for (int c = 0; c < SPR; c++){
			cout << seat_chart[r][c].occupant;
			cout << " ";
			if (seat_chart[r][c].occupant != "---"){
				revenue = revenue + seat_chart[r][c].value;
			}
		}
		cout << endl;
	}
	cout << "revenue" << " " << revenue << endl;
}
//function takes in the struct order and also the seating array from the class
//and removes names from the seating chart that match the name in the struct
//order. The function also sets the value of each individual seat back to
//its original initialized numeric value.
bool Hall::cancel(Order order)
{
	int counter = 0;
	for (int r =0; r < ROW; r++){
		for (int c = 0; c < SPR; c++){
			if (order.name == seat_chart[r][c].occupant){
				seat_chart[r][c].occupant = "---";
				if (( c > 3 || c < 16) && r < 8){
					seat_chart[r][c].value = 200.00;
				}
				if (( c < 4 || c > 15) || r > 7){
					seat_chart[r][c].value = 150.00;
				}
				counter++;
			}
		}
	}
	if (counter == 0){
		cout << "no" << " " << order.name << " "<< "no-reservation";
		cout << endl;
		return false;
	}
	else{
		cout << "ok" << " " << order.name << " " << "cancelled";
		cout << endl;
		return true;
	}

}
//fuction takes in the struct order and also the seating array from the 
//class. The function checks to make sure that the ticket number is ok
//and also checks to make sure that the name is not already reserved 
//in the function. If both of these things are ok the the fuction takes
//the value of price and acts as a kiosk
bool Hall::request(Order order)
{
	bool success;
	if (order.tic_num > 12){
		cout << "no" << " " << order.name;
		return false;
	}
	for (int r = 0; r < ROW; r++){
		for (int c = 0; c < SPR; c++){
			if (order.name == seat_chart[r][c].occupant){
			      cout<<"no"<<" "<<order.name<<" already-reserved";
				cout << endl;
				return false;
			}
		}
	}
	if (order.price == "hi"){
		success = hi_check(order);
	}
	else if (order.price == "lo"){
		success = lo_check(order);
			
	} 
	else if (order.price == "any"){
		success = any_check(order);
	}
	return success;
}
//funtion takes in the struct order and also the seating array from the class
//and counts the number of open seats in the hi section of the array to see if
//there are as many open spaces as tickets requested.  If there are it
//returns true and if not it returns false.
bool Hall::hi_check(Order order)
{ 
	int counter = 0;
	for (int row = 0; row < 8; row++){
		for (int col = 4; col < 16; col++){
			if (seat_chart[row][col].occupant == "---"){
				counter++;
			}
		}
	}
	if (counter < order.tic_num){
		cout << "no" << " " << order.name << " " << "not available";
		return false;
	}
	else if (counter >= order.tic_num){
		allocate_hi(order);
		return true;
	}
}
//funtion takes in the srtuct order and the seating array. Counts up the number
//of open seats until it equals ticket number and then allocates seats. If it 
//cant alocate seats in a group it just allocates seats anywhere that there
//is an open seat in the array.
void Hall::allocate_hi(Order order)
{
	int counter = 0;//counts open seats
	int giv = 0; //measures if the seats have been allocated in a group
	
	for (int r = 0; r < 8; r++){
		counter = 0;
		for (int c = 4; c < 16; c++){
			if ( seat_chart[r][c].occupant == "---"){
				counter++;
			}
			if (seat_chart[r][c].occupant != "---"){
				counter = 0;
			}
			if (counter == order.tic_num && giv == 0){
			     for(int alc = c; alc > c - order.tic_num; alc--){
				   seat_chart[r][alc].occupant = order.name;
				}
				giv++;
			}
		}
	}
	if (giv == 0 && order.price == "any"){
		allocate_lo_any(order);
	}
	counter = order.tic_num;
	if (giv == 0 && counter > 0){
		for (int row = 0; row < 8; row++){
			for (int col = 4; col < 16; col++){
				if (seat_chart[row][col].occupant == "---"){
				    seat_chart[row][col].occupant = order.name;
					counter--;
				}
			}
		}
	}
	cout << "ok" << " " << order.name <<" " << price_finder(order); 
	cout << " " << order.tic_num << " ";
	cout << order.day << " ";
	seat_print(order);
	cout  << endl;	
}
//function takes in the struct order and also the seating array from the class
//cycles through the array to see if the seats are seated together or not.
//If they are not grouped together it gives a discount and also changes the 
//the value of the occupied seat to a discounted value. Returns the numerical
//value of the order.
double Hall::price_finder(Order order)
{
	double sum = 0;
	int counter = 0;
	double discount = .9;
	
	for (int r = 0; r < ROW; r++){
		for (int c = 0; c < SPR; c++){
			if ( order.name == seat_chart[r][c].occupant){
				counter++;
				sum = sum + seat_chart[r][c].value;
			}
			if (seat_chart[r][c].occupant != order.name){
				counter = 0;
			}
			if (counter == order.tic_num){
				return sum;
			}
			
		}
	}
	
	if (counter != order.tic_num){
		for (int row = 0; row < ROW; row++){
			for (int col = 0; col < SPR; col++){
			      if (seat_chart[row][col].occupant == order.name){
					seat_chart[row][col].value = 
					(discount * seat_chart[row][col].value);
				}
			}
		}
				return (sum * discount);
	}  
	
}
//function takes in the struct order and also the seating array. IT cycles
//through the array and locates the different positions of the same name
//and gives a a letter value based on row and a numeric value based on
//the position in the row.
void Hall::seat_print(Order order)
{
	char letter[26]= {'A','B','C','D','E','F','G','H','I','J','K','L',
		'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	for( int r = 0; r < ROW; r++){
		for(int c = 0; c < SPR; c++){
			if (seat_chart[r][c].occupant == order.name){
				cout << " " << letter[r] << c + 1 << " ";
			}
		}
	}
	cout << endl;
}
//funtion takes in the struct order and also the seating array from the class
//and counts the number of open seats in the lo section of the array to see if
//there are as many open spaces as tickets requested.  If there are it
//returns true and if not it returns false.
bool Hall::lo_check(Order order)
{
	int counter = 0;
	
	for (int row = 0; row < ROW; row++){
		for (int col = 0; col < SPR; col++){
			if ((col < 4 || col > 15) || row > 7){
				if (seat_chart[row][col].occupant == "---"){
					counter++;
				}
			}
		}
	}
	if (counter < order.tic_num){
		cout << "no" << " " << order.name << " " << "not available";
		return false;
	}
	else if (counter >= order.tic_num){
		allocate_lo_one(order);
		return true;
	}


}
//funtion takes in the struct order and also the seating array from the class
//counts up the number of open seats in each row of the left part of the
//low section to see if there are enough to seat the order in a group. 
//If there are they are seated and if not the order is passed down to another 
//function.
void Hall::allocate_lo_one(Order order)
{
	int counter = 0;
	int giv = 0;
	
	for (int r = 0; r < 8; r++){
		counter = 0;
		for (int c = 0; c < 4; c++){
			if ( seat_chart[r][c].occupant == "---"){
				counter++;
			}
			if (seat_chart[r][c].occupant != "---"){
				counter = 0;
			}
			if (counter == order.tic_num && giv == 0){
			     for(int alc = c; alc > c - order.tic_num; alc--){
			           seat_chart[r][alc].occupant = order.name;
				}
				giv++;
			}
		}
	}
	if (giv == 0){
		allocate_lo_two(order);
	}
	else if (giv != 0){
		cout << "ok" << " " << order.name <<" " << price_finder(order); 
		cout << " " << order.tic_num << " ";
		cout << order.day << " ";
		seat_print(order);
		cout  << endl;
	}	

}
//funtion takes in the struct order and also the seating array from the class
//counts up the number of open seats in each row of the right part of the
//low section to see if there are enough to seat the order in a group. 
//If there are they are seated and if not the order is passed down to another 
//function.
void Hall::allocate_lo_two(Order order)
{
	int counter = 0;
	int giv = 0;
	
	for (int r = 0; r < 8; r++){
		counter = 0;
		for (int c = 16; c < SPR; c++){
			if ( seat_chart[r][c].occupant == "---"){
				counter++;
			}
			if (seat_chart[r][c].occupant != "---"){
				counter = 0;
			}
			if (counter == order.tic_num && giv == 0){
			     for(int alc = c; alc > c - order.tic_num; alc--){
				    seat_chart[r][alc].occupant = order.name;
				}
				giv++;
			}
		}
	}
	if (giv == 0){
		allocate_lo_thr(order);
	}
	else if (giv != 0){
		cout << "ok" << " " << order.name <<" " << price_finder(order); 
		cout << " " << order.tic_num << " ";
		cout << order.day<< " ";
		seat_print(order);
		cout  << endl;
	}	

}
//funtion takes in the struct order and also the seating array from the class
//counts up the number of open seats in each row of the rear part of the
//low section to see if there are enough to seat the order in a group. 
//If there are they are seated and if not the order is passed down to another 
//function.

void Hall::allocate_lo_thr(Order order)
{
	int counter = 0;
	int giv = 0;
	
	for (int r = 8; r < ROW; r++){
		counter = 0;
		for (int c = 0; c < SPR; c++){
			if ( seat_chart[r][c].occupant == "---"){
				counter++;
			}
			if (seat_chart[r][c].occupant != "---"){
				counter = 0;
			}
			if (counter == order.tic_num && giv == 0){
			      for(int alc = c; alc > c - order.tic_num; alc--){
				    seat_chart[r][alc].occupant = order.name;
				}
				giv++;
			}
		}
	}
	if (giv == 0 && order.price == "lo"){
		allocate_lo_split(order);
	}
	else if (giv == 0 && order.price == "any"){
		allocate_hi(order);
	}
	 if (giv != 0){
		cout << "ok" << " " << order.name <<" " << price_finder(order);
		cout << " " << order.tic_num << " ";
		cout << order.day << " ";
		seat_print(order);
		cout  << endl;
	}	

}
//function takes in the struct order and also the seating array. It cycles 
//through the low part of the array and allocates a seat where ever there 
//is a free seat.
void Hall::allocate_lo_split(Order order)
{
	int counter = order.tic_num;
	for (int r = 0; r < ROW; r++){
		for (int c = 0; c < SPR; c++){
			if ((c < 4 || c > 15) || r > 7){
				if (counter > 0){
				if (seat_chart[r][c].occupant == "---"){
					seat_chart[r][c].occupant = order.name;
					counter--;
				}
				}
			}
		}
	}
	cout << "ok" << " " << order.name <<" " << price_finder(order);
	cout << " " << order.tic_num << " ";
	cout << order.day << " ";
	seat_print(order);
	cout  << endl;	

}
//funtion takes in the struct order and also the seating array from the class
//and counts the number of open seats in the entire array to see if
//there are as many open spaces as tickets requested.  If there are it
//returns true and if not it returns false.
bool Hall::any_check(Order order)
{
	int counter = 0;
	for (int row = 0; row < ROW; row++){
		for (int col = 0; col < SPR; col++){
			if (seat_chart[row][col].occupant == "---"){
				counter++;
			}
		}
	}
	if (counter < order.tic_num){
		cout << "no" << " " << order.name << " " << "not available";
		return false;
	}
	else if (counter >= order.tic_num){
		allocate_lo_one(order);
		return true;
	}

}
//function takes in the struct order and also the seating array. It cycles 
//through the low part of the array and allocates a seat where ever there 
//is a free seat.
void Hall::allocate_lo_any(Order order)
{
	int counter = order.tic_num;
	for (int r = 0; r < ROW; r++){
		for (int c = 0; c < SPR; c++){
			if ((c < 4 || c > 15) || r > 7){
				if (counter > 0){
				if (seat_chart[r][c].occupant == "---"){
					seat_chart[r][c].occupant = order.name;
					counter--;
				}
				}
			}
		}
	}
	if (counter == 0){
		cout << "ok" << " " << order.name <<" " << price_finder(order); 
		cout << " " << order.tic_num << " ";
		cout << order.day << " ";
		seat_print(order);
		cout  << endl;
	}	
	else if (counter != 0){
		allocate_hi_any(order, counter);
	}
}
//function takes in the struct order and also the seating array. It cycles 
//through the hi part of the array and allocates a seat where ever there 
//is a free seat.
void Hall::allocate_hi_any(Order order, int counter)
{
	if (counter > 0){
		for (int row = 0; row < 8; row++){
			for (int col = 4; col < 16; col++){
				if (seat_chart[row][col].occupant == "---"){
				     seat_chart[row][col].occupant = order.name;
					counter--;
				}
			}
		}
	}
	cout << "ok" << " " << order.name <<" " << price_finder(order); 
	cout << " " << order.tic_num << " ";
	cout << order.day << " ";
	seat_print(order);
	cout  << endl;	

}
