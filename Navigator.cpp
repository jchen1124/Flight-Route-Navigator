#include "Navigator.h"
#include <iostream>
#include <fstream>
using namespace std;

Navigator::Navigator(string filename){
    filename = "proj_data.txt";
    m_fileName = filename;

}

Navigator::~Navigator(){

}

void Navigator::Start(){
ifstream file(m_fileName);
if(!file.is_open()){
    cout << "Unable to open file" << endl;
    return;
}

file.close();

MainMenu();

}

void Navigator::DisplayAirports(){

}

void Navigator::ReadFile(){
fstream file;
file.open(m_fileName);
if(!file.is_open()){
    cout << "Error opening file" << endl;
}

string code, name, city, country;
double north, west;

while(file >> code >> name >> city >> country >> north >> west){
    Airport* airport = new Airport(code, name, city, country, north, west);
    m_airports.push_back(airport);
}
file.close();
}

void Navigator::InsertNewRoute(){

}

void Navigator::MainMenu(){
int choice = 0;
do{
   cout << endl;
   cout << "What would you like to do?: " << endl; 
   cout << "1. Create New Route" << endl;
   cout << "2. Display Route" << endl;
   cout << "3. Remove Airport From Route" << endl;
   cout << "4. Reverse Route" << endl;
   cout << "5. Exit" << endl;
   cout << ">> ";
   cin >> choice;
switch(choice){
    case 1:
        InsertNewRoute();
        break;
    case 2:
        DisplayRoute();
        break;
    case 3:
        RemoveAirportFromRoute();
        break;
    case 4:
        ReverseRoute();
        break;
    case 5:
        cout << endl;
        cout << "Thanks for playing !" << endl;

}
}while(choice != 5);
}

int Navigator::ChooseRoute(){
    return 0;
}

void Navigator::DisplayRoute(){

}

void Navigator::RemoveAirportFromRoute(){

}

double Navigator::RouteDistance(Route*){
return 0;
}

void Navigator::ReverseRoute(){

}
