// COMSC-210 | Lab 23 | Diksha Tara Natesan
// IDE used: Vim/Terminal

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

//select_goat() shows the user teh current trip list and takes in the user input to select a goat
//arguments: list<Goat> trip - takes in the list of Goats
//returns the position in the list of the goat the user selected
int select_goat(list<Goat> trip);

//delete_goat() removes a goat from the list based upon the user's choice
//arguments: list<Goat> trip - takes in the list of Goats
void delete_goat(list<Goat> &trip);

//add_goat() randomly creates a new goat and adds it to the end of the trip list
//arguments: list<Goat> trip - takes in the list of Goats, (2) string [] - for the array of names/colors to randomly select from
void add_goat(list<Goat> &trip, string [], string []);

//display_trip() outputs the goats in the trip in order with all their data and numbers them
//arguments: list<Goat> trip - takes in the list of Goats
void display_trip(list<Goat> trip);

//main_menu() displays the list of options for the user to choose from to edit the goat trip list and use the program, then obtains the user's choice
//returns the user's choice from the listed options
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> trip;
    bool run = true;
    while (run){
	int choice = main_menu();
	if (choice == 1)
	    add_goat(trip, names, colors);
	else if (choice == 2)
	    delete_goat(trip);
	else if (choice == 3)
	    display_trip(trip);
 	else
	    run = false;
    }
    cout << "Thanks for using the GOAT MANAGER 3001!" << endl;
    return 0;
}

int select_goat(list<Goat> trip){
    display_trip(trip);
    cout << "\tChoice --> ";
    int input;
    cin >> input;
    if (input > trip.size() || input < 1){
	cout << "\n\tError. Please select a valid choice within the range." << endl;
        input = select_goat(trip);
    }
    return input;
}

void delete_goat(list<Goat> &trip){
    if (trip.empty()){
        cout << "\n\tNo Goats available to remove." << endl;
        return;
    }
    cout << "\n\tPlease select a Goat you would like to remove from the trip." << endl;
    int pos = select_goat(trip);
    auto it = trip.begin();
    for (int i = 1; i < pos; i++)
        it++;
    trip.erase(it);
}

void add_goat(list<Goat> &trip, string names[], string colors[]){
    int age = rand() % (MAX_AGE + 1);  // returns random number 0-20
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    Goat temp(name, age, color);
    trip.push_back(temp);
}

void display_trip(list<Goat> trip){
    int count = 1;
    cout << "\n\tGoat trip list:" << endl;
    for (Goat g : trip){
        cout << "\t[" << count << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")" << endl;
	count += 1;
    }
}

int main_menu(){
    cout << "\n\t*** GOAT MANAGER 3001 ***" << endl;	//choice display
    cout << "\t[1] Add a goat" << endl;
    cout << "\t[2] Delete a goat" << endl;
    cout << "\t[3] List goats" << endl;
    cout << "\t[4] Quit" << endl;
    cout << "\tChoice --> ";
    int input;				//obtain user input
    cin >> input;
    if (input < 1 || input > 4){	//validate user input
	cout << "\n\tError. Please input a value within the range 1-4 to select a choice." << endl;
	input = main_menu();
    } 
    return input;			//return validated user input
}
