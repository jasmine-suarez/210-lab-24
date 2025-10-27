#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
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
    int choice;

    do {
        choice = main_menu();

        switch (choice) {
            case 1: // add
                add_goat(trip, names, colors);
                break;
            case 2: // delete
                delete_goat(trip);
                break;
            case 3: // list
                display_trip(trip);
                break;
            case 4: // quit
                cout << "Exiting..." << endl;
                break;
        }
        cout << endl;

    } while (choice != 4);

    return 0;
}

int select_goat(list<Goat> trip) {
    display_trip(trip);

    int choice;
    cout << endl << "Select goat by # --> ";
    cin >> choice;
    cout << endl;

    while (choice < 1 || choice > trip.size()) {
        cout << "Invaid choice. Enter 1-" << trip.size() << "--> ";
        cin >> choice;
        cout << endl;
    }

    return choice;
}

void delete_goat(list<Goat> &trip) {
    int choice = select_goat(trip);

    auto it = trip.begin();
    advance(it, choice - 1);
    trip.erase(it);
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
    int randName = rand() % SZ_NAMES;
    int randColor = rand() % SZ_COLORS;
    int randAge = rand() % (MAX_AGE + 1);

    Goat newGoat(names[randName], randAge, colors[randColor]);
    trip.push_back(newGoat);
}

void display_trip(list<Goat> trip) {
    int index = 1;
    for (const Goat &g : trip) {
        cout << "    [" << index << "] "
             << g.get_name() << " ("
             << g.get_age() << ", "
             << g.get_color() << ")" << endl;

        index++;
    }
}

int main_menu() {
    int choice;

    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";

    cin >> choice;
    cout << endl;

    // validates choice
    while (choice < 1 || choice > 4) {
        cout << "Invaid choice. Enter 1-4 --> ";
        cin >> choice;
        cout << endl;
    }

    return choice;
}