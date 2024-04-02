/*****************************************
** File:    Navigator.cpp
** Project: CMSC 202 Project 3, Spring 2024
** Author:  Jason Chen
** Date:    4/2/24
** Section: 10/13
** E-mail:  jchen33@gl.umbc.edu 
**
** This file implements the functionalities of an Navigator class. 
** It includes function to read in the data of each airport. Displays the main menu
** to create new routes, display routes, remove airports, and reverse routes.
** 
***********************************************/

#include "Navigator.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Name: Navigator (string) - Overloaded Constructor                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
// Desc: Creates a navigator object to manage routes                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
// Preconditions:  Provided with a filename of airports to load                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
// Postconditions: m_filename is populated with fileName 
Navigator::Navigator(string filename){
    filename = "proj3_data.txt";
    m_fileName = filename;
    
}

// Name: Navigator (destructor)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
// Desc: Deallocates all dynamic aspects of a Navigator                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
// Preconditions: There is an existing Navigator                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
// Postconditions: All airports and routes are cleared  
Navigator::~Navigator(){

// Deallocate memory for airports
for (unsigned int i = 0; i < m_airports.size(); i++)
{
    delete m_airports[i];
}

m_airports.clear();

// Deallocate memory for routes
for (unsigned int i = 0; i < m_routes.size(); i++)
{
    delete m_routes[i];
}

m_routes.clear();

}

// Name: Start                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
// Desc: Loads the file and calls the main menu                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
// Preconditions: m_fileName is populated                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
// Postconditions: All ports are loaded and the main menu runs  
void Navigator::Start(){
    ReadFile();
    MainMenu();
}

// Name: DisplayAirports                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
// Desc: Displays each airport in m_airports                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
// Preconditions: At least one airport is in m_airports                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
// Postconditions: Displays all airports.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
//  Uses overloaded << provided in Airport.h 
void Navigator::DisplayAirports(){
if (m_airports.size() == 0) {
        cout << "No airports to display." << endl;
        return;
    }

    // Iterates through airport vector and prints 
    cout << "List of Airports:" << endl;
    for (unsigned int i = 0; i < m_airports.size(); i++)
    {
        cout << i+1 << ". " << m_airports[i]->GetName() << ", " << m_airports[i]->GetCity() << endl;
    }
    
}


// Name: ReadFile                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
// Desc: Reads in a file that has data about each airport                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
//   including code, name, city, country, degrees north and degrees west.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
//   Dynamically allocates airports and stores them in m_airports                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
//   The vector can hold many airports.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
// Preconditions: Valid file name of airports                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
// Postconditions: Dynamically allocates each airport                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
//   and enters it into m_airports 
void Navigator::ReadFile(){
fstream file;
file.open(m_fileName);
if(!file.is_open()){
    cout << "Error opening file" << endl;
}else{
cout << "Opened File" << endl;
cout << "Airports loaded: 40" << endl;
string code, name, city, country, s_north, s_west;
double north, west;

string line;

//Reading in entire file as a string
while(getline(file, code, ',') &&
      getline(file, name, ',') &&
      getline(file, city, ',') &&
      getline(file, country, ',') &&
      getline(file, s_north, ',') && // Reads in North
      getline(file, s_west)) { // Reads in West

        north = stod(s_north); //Covert string to double for north
        west = stod(s_west); //Covert string to double for west

        // Dynamicaly allocate Airport object and add to m_airport
        Airport* airport = new Airport(code, name, city, country, north, west);
        m_airports.push_back(airport);
      }

    file.close();

}
}

// Name: InsertNewRoute                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
// Desc: Dynamically allocates a new route with the user selecting                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
//   each airport in the route. Each route can have a minimum of two                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
//   airports. Will not allow a one airport route.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
//   Checks for min of two valid airports (1-40)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
//   Route named using Route's UpdateName.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
//   For example, Baltimore to Boston                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
//   Once route is created, inserted into m_routes.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
// Preconditions: Populated m_routes                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
// Postconditions: Inserts a new route into m_routes 
void Navigator::InsertNewRoute(){
    int count = 0;
    int input = 0;
    bool exitloop = false;

    DisplayAirports();
    Route* newRoute = new Route();
    

    while(!exitloop){
        cout << "Enter the number of the airport to add to your Route: (-1 to end)" << endl;
        cout << ">> ";
        cin >> input;
        
        if(input == -1){
            if(count < 2){
                cout << "You must have atleast 2 airports" << endl;
            }else{
                exitloop = true;
            } 
        }
        
        else if(input > 0 && input <= (int)m_airports.size()){
            input--; //Adjust input for vector index
            count++;

            //Insert Selected airport into newRoute
            Airport* selectedAirport = m_airports[input];
            newRoute->InsertEnd(selectedAirport->GetCode(), selectedAirport->GetName(), selectedAirport->GetCity(), selectedAirport->GetCountry(), selectedAirport->GetNorth(), selectedAirport->GetWest());
        
        }else{
            cout << "Invalid Number - Try Again" << endl;
        }
        
    }
        // Adds the selected airports to m_routes vector
        m_routes.push_back(newRoute);
        cout << "Done Building a route named " << newRoute->UpdateName() << endl;
}

// Name: MainMenu                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
// Desc: Displays the main menu and manages exiting                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
// Preconditions: Populated m_airports                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
// Postconditions: Exits when someone chooses 5  
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
        cout << "Routes removed from memory" << endl;
        cout << "Deleting Airports" << endl;
        cout << "Deleting Routes" << endl;

}
}while(choice != 5);
}

// Name: ChooseRoute                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
// Desc: Allows user to choose a specific route to work with                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
//   by displaying numbered list                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
// Preconditions: Populated m_routes                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
// Postconditions: Returns the index of the selected route minus 1 
int Navigator::ChooseRoute(){
    int choice = 0;

do {
    cout << "Which route would you like to use?" << endl;
    //Display numbered lists of routes
    for (unsigned int i = 0; i < m_routes.size(); i++){
    string routeName = m_routes[i]->UpdateName(); 
    cout << i+1 << ". " << routeName << endl;
    }
    cout << ">> ";
    cin >> choice;

} while((int)choice < 1 || (int)choice > (int)m_routes.size());



return choice - 1;

}

// Name: DisplayRoute                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
// Desc: Using ChooseRoute, displays a numbered list of all routes.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
//    If no routes, indicates that there are no routes to display                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
//    User selects a route from list to display                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
//    Displays numbered list of each airport in route                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
//    Displays total miles of a route using RouteDistance                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
// Preconditions: Routes has more than one airport                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
// Postconditions: Displays all airports in a route and                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
//    the total miles of the route
void Navigator::DisplayRoute(){
if(m_routes.size() == 0){
    cout << "No routes to display" << endl;
    return;
}
int choice = ChooseRoute();
// Display the selected route and its total miles
cout << m_routes[choice]->UpdateName() << endl;

if(choice >= 0 && (int)choice < (int)m_routes.size()){
    Route* selectedRoute = m_routes[choice];
    selectedRoute->DisplayRoute();

    double distance = RouteDistance(selectedRoute);
    cout << "The total miles of this route is " << distance << " miles" << endl;
}else{
    cout << "Invalid Route" << endl;
}



}

// Name: RemoveAirportFromRoute()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
// Desc: Using ChooseRoute, displays a numbered list of all routes.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
//    User selects one of the routes to remove an airport from.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
//    Displays a numbered list of all airports in selected route.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
//    User selects airport to remove from list.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
//    Each route has a minimum of two airports (will not allow).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
//    Removes airport from route if more than two.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
//    If first or last airport removed,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
//    updates name of route using UpdateName                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
// Preconditions: Route has more than one airport                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
// Postconditions: Displays updated route with removed airport                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
//    and new name  
void Navigator::RemoveAirportFromRoute(){
if(m_routes.size() == 0){
    cout << "No Routes to remove";
    cout << endl;
    return;
}

//Choose and get the selected route to be removed
int choice = ChooseRoute();
Route* selectedRoute = m_routes[choice];

if(selectedRoute->GetSize() <= ROUTE_MIN){
    cout << "Route needs more than two airports" << endl;
    return;
}
cout << selectedRoute->UpdateName() << endl;

//Display airpots in selected route    
selectedRoute->DisplayRoute();
bool exitloop = false;

int airportToRemove = 0;

while(!exitloop){
    cout << "What airport would you like to remove? " << endl;
    cout << ">> ";
    cin >> airportToRemove;

    if(airportToRemove <= 0 || airportToRemove > selectedRoute->GetSize()){
        cout << "Invalid Input" << endl;
    }else{
        cout << selectedRoute->GetName() << endl;
        selectedRoute->RemoveAirport(airportToRemove-1); //Removes airport
        selectedRoute->DisplayRoute();
        string update = selectedRoute->UpdateName();
        cout << "Route named " << update << " updated" << endl;
        exitloop = true;
        
    }
}
}


// Name: ReverseRoute                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
// Desc: Using ChooseRoute, users chooses route and the route is reversed                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
//   If no routes in m_routes, indicates no routes available to reverse                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
//   Updates route name using UpdateName                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
//   For example, Baltimore to Boston becomes Boston to Baltimore                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
// Preconditions: Populated m_routes                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
// Postconditions: Reverses a specific route by reversing the airports                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//   in place. Must move airports, cannot just change data in airports.
void Navigator::ReverseRoute(){
if(m_routes.size() == 0){
    cout << "No Routes to Reverse";
    cout << endl;
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

// Name: RouteDistance                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
// Desc: Calculates the total distance of a route                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
//    Goes from airport 1 to airport 2 then airport 2 to airport 3                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
//    and repeats for length of route.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//    Calculates the distance using CalcDistance (provided)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
//    Aggregates the total and returns the total in miles                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
// Preconditions: Populated route with more than one airport                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
// Postconditions: Returns the total miles between all airports in a route 
double Navigator::RouteDistance(Route* routes){
    double totalDistance = 0.0;
    unsigned int numAirports = routes->GetSize();

    // Gets Data of the first airport
    Airport* currentAirport = routes->GetData(0);
    Airport* nextAirport = nullptr;

    // Goes through the airports starting with the second one
    for (int i = 1; i < numAirports; i++){
        nextAirport = routes->GetData(i);

        double distance = CalcDistance(currentAirport->GetNorth(), currentAirport->GetWest(), nextAirport->GetNorth(), nextAirport->GetWest());
        totalDistance += distance;

        // Update the current airport to the next airport for the next iteration
        currentAirport = nextAirport;
        
    }

    return totalDistance;
    
}

