#include "Navigator.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Navigator::Navigator(string filename){
    //filename = "proj3_data.txt";
    m_fileName = filename;
    //ReadFile();
}

Navigator::~Navigator(){

// Deallocate memory for airports
for (int i = 0; i < m_airports.size(); i++)
{
    delete m_airports[i];
}

m_airports.clear();

for (int i = 0; i < m_routes.size(); i++)
{
    delete m_routes[i];
}

m_routes.clear();

}

void Navigator::Start(){
    ReadFile();
    MainMenu();
}

void Navigator::DisplayAirports(){
if (m_airports.size() == 0) {
        cout << "No airports to display." << endl;
        return;
    }

    cout << "List of Airports:" << endl;
    for (int i = 0; i < m_airports.size(); i++)
    {
        cout << i+1 << ". " << m_airports[i]->GetName() << ", " << m_airports[i]->GetCity() << endl;
    }
    
}



void Navigator::ReadFile(){
fstream file;
file.open(m_fileName);
if(!file.is_open()){
    cout << "Error opening file" << endl;
}

string code, name, city, country, temp;
double north, west;

string line;

// Reading in entire file as a string
// while(getline(file, line)){
//         unsigned int pos = 0;
//         pos = line.find(",");
//         code = line.substr(0, pos);

//         unsigned int prev_position = pos + 1;
//         pos = line.find(",", prev_position);
//         name = line.substr(prev_position, pos - prev_position);

//         prev_position = pos + 1;
//         pos = line.find(",", prev_position);
//         city = line.substr(prev_position, pos - prev_position);

//         prev_position = pos + 1;
//         pos = line.find(",", prev_position);
//         country = line.substr(prev_position, pos - prev_position);

//         prev_position = pos + 1;
//         pos = line.find(",", prev_position);
//         north = atof(line.substr(prev_position, pos - prev_position).c_str());
        
//         prev_position = pos + 1;
//         pos = line.find(",", prev_position);
//         west = atof(line.substr(prev_position, pos - prev_position).c_str());

//         Airport* airport = new Airport(code, name, city, country, north, west);
//         m_airports.push_back(airport);

// }

while(getline(file, code, ',') &&
      getline(file, name, ',') &&
      getline(file, city, ',') &&
      getline(file, country, ',') &&
      getline(file, temp, ',') && // Reads in North
      getline(file, temp)) { // Reads in West

        north = stod(temp); //Covert string to double
        west = stod(temp);

        Airport* airport = new Airport(code, name, city, country, north, west);
        m_airports.push_back(airport);
      }

    file.close();

}

void Navigator::InsertNewRoute(){
    int count = 0;
    int input = 0;
    bool exitloop = false;

    DisplayAirports();
    Route* newRoute = new Route();
    

    while(!exitloop){
        cout << "Enter the number of the airport to add to your Route: (-1 to end)" << endl;
        cin >> input;
        
        if(input == -1){
            if(count < 2){
                cout << "You must have atleast 2 airports" << endl;
                //delete newRoute;
            }else{
                exitloop = true;
            }
        }
        
        else if(input >= 0 && input <= m_airports.size()){
            input--;
            //cout << "good" << endl;
            count++;

            
            // Airport* airport = new Airport(
            //     m_airports[input]->GetCode(),
            //     m_airports[input]->GetName(),
            //     m_airports[input]->GetCity(),
            //     m_airports[input]->GetCountry(),
            //     m_airports[input]->GetNorth(),
            //     m_airports[input]->GetWest()

            // );

            Airport* selectedAirport = m_airports[input];
            newRoute->InsertEnd(selectedAirport->GetCode(), selectedAirport->GetName(), selectedAirport->GetCity(), selectedAirport->GetCountry(), selectedAirport->GetNorth(), selectedAirport->GetWest());
            //cout << newRoute << endl;

            //delete airport;
        
        
        }else{
            cout << "Invalid Number" << endl;
        }
        
    }
        m_routes.push_back(newRoute);


    // string name = newRoute->GetName();
    // cout << "Done Building a route named " << name << endl;

    // cout << "Done Building a route named:: " << m_routes.back()->GetData(0)->GetName() << " to " 
    // << m_routes.back()->GetData(m_routes.back()->GetSize() - 1)->GetName() << endl;

    cout << "Done Building a route named:: " << newRoute->UpdateName() << endl;
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
    int choice = 0;
if(m_routes.size() == 0){
    cout << "No Routes to display";
    return -1;
}


do {
    cout << "Which route would you like to use?" << endl;
    for (unsigned int i = 0; i < m_routes.size(); i++){
    string routeName = m_routes[i]->UpdateName(); //Question
    cout << i+1 << ". " << routeName << endl;
    }

    cin >> choice;

} while(choice < 1 || choice > m_routes.size());



return choice - 1;

}

void Navigator::DisplayRoute(){

int choice = ChooseRoute();
cout << "HERE" << endl;
cout << m_routes[choice]->UpdateName() << endl; //Question

if(choice >= 0 && choice < m_routes.size()){
    Route* selectedRoute = m_routes[choice];
    selectedRoute->DisplayRoute();

    double distance = RouteDistance(selectedRoute);

}else{
    cout << "Invalid Route" << endl;
}



}

void Navigator::RemoveAirportFromRoute(){
if(m_routes.size() == 0){
    cout << "No Routes to remove";
    return;
}

int choice = ChooseRoute();
Route* selectedRoute = m_routes[choice];

if(selectedRoute->GetSize() <= ROUTE_MIN){
    cout << "Route needs more than two airports" << endl;
    return;
}
cout << "Selected Route: " << selectedRoute->GetName() << endl;

    
selectedRoute->DisplayRoute();
bool exitloop = false;

int airportToRemove = 0;

while(!exitloop){
    cout << "What airport would you like to remove? " << endl;
    cin >> airportToRemove;

    if(airportToRemove <= 0 || airportToRemove > selectedRoute->GetSize()){
        cout << "Invalid Input" << endl;
    }else{
        cout << "Selected Route: " << selectedRoute->GetName() << endl;
        selectedRoute->RemoveAirport(airportToRemove-1);
        //cout << "New" << endl;
        selectedRoute->DisplayRoute();
        string update = selectedRoute->UpdateName();
        cout << "Route named " << update << "updated" << endl;
        exitloop = true;
        
    }



}
}

double Navigator::RouteDistance(Route*){
//return CalcDistance(temp->GetNorth(), Route->GetWest(), Route->GetNorth(), Route->GetWest());
return 0;
}

void Navigator::ReverseRoute(){
if(m_routes.size() == 0){
    cout << "No Routes to Reverse";
    return;
}
int choice = ChooseRoute();
Route* selectedRoute = m_routes[choice];

// Reversing
selectedRoute->ReverseRoute();

// // // Update Route Name
string updateName = selectedRoute->UpdateName();
cout << "Done Reversing " << updateName << endl;
}

