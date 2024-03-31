/*****************************************
** File:    Route.cpp
** Project: CMSC 202 Project 3, Spring 2024
** Author:  Jason Chen
** Date:    4/2/24
** Section: 10/13
** E-mail:  jchen33@gl.umbc.edu 
**
** This file implements the functionalities of a Route class. 
** It defines constructors, destructors, and methods to manage 
** a linked list of airports forming a route. The class provides 
** functions to insert airports at the end of the route, remove airports, 
** update the route name, reverse the route, retrieve the size of the route, 
** access airport data at specific indices, and display the route details.
** 
***********************************************/

#include "Route.h"
#include <iostream>

using namespace std;

// Name: Route() - Default Constructor                                                                                                                                                                                                                                                                                                                                                   
// Desc: Used to build a new Route (linked list) make up of airports                                                                                                                                                                                                                                                                                                                     
// Preconditions: None                                                                                                                                                                                                                                                                                                                                                                   
// Postconditions: Creates a new Route where m_head and m_tail                                                                                                                                                                                                                                                                                                                           
//   point to nullptr and size = 0 
Route::Route(){
    m_name = "";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}


// Name: SetName(string)                                                                                                                                                                                                                                                                                                                                                                 
// Desc: Sets the name of the route (usually first                                                                                                                                                                                                                                                                                                                                       
//   airport to last airport)                                                                                                                                                                                                                                                                                                                                                            
// Preconditions: None                                                                                                                                                                                                                                                                                                                                                                   
// Postconditions: Sets name of route 
void Route::SetName(string name){
    m_name = name;
}

// Name: ~Route() - Destructor                                                                                                                                                                                                                                                                                                                                                           
// Desc: Used to destruct a strand of Route                                                                                                                                                                                                                                                                                                                                              
// Preconditions: There is an existing Route strand with at least                                                                                                                                                                                                                                                                                                                        
//   one airport                                                                                                                                                                                                                                                                                                                                                                         
// Postconditions: Route is deallocated (including all                                                                                                                                                                                                                                                                                                                                   
//   dynamically allocated airports) to have no memory leaks!
Route::~Route(){
Airport *curr = m_head;
while(curr != nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;
}
//After delete, the list is deleted so, have to reset 
m_head = nullptr;
m_tail = nullptr;
m_size = 0;
}

// Name: InsertEnd (string, string, double double)                                                                                                                                                                                                                                                                                                                                       
// Desc: Creates a new airport using the data passed to it.                                                                                                                                                                                                                                                                                                                              
//   Inserts the new airport at the end of the route                                                                                                                                                                                                                                                                                                                                     
// Preconditions: Takes in a Airport                                                                                                                                                                                                                                                                                                                                                     
//                Requires a Route                                                                                                                                                                                                                                                                                                                                                       
// Postconditions: Adds the new airport to the end of a route 
void Route::InsertEnd(string code, string name, string city, string country, double north, double west){
    // Insert an airport at the end of the route
    Airport *newAirport = new Airport(code, name, city, country, north, west);
    if(m_head == nullptr){
        m_head = newAirport;
        m_tail = newAirport;
    }
    else{
        m_tail->SetNext(newAirport);
        m_tail = newAirport;
    }
    m_size++;
}

// Name: RemoveAirport(int index)                                                                                                                                                                                                                                                                                                                                                        
// Desc: Removes a airport from the route at the index provided                                                                                                                                                                                                                                                                                                                          
//   Hint: Special cases (first airport, last airport, middle airport)                                                                                                                                                                                                                                                                                                                   
// Preconditions: Index must be less than the size of the route                                                                                                                                                                                                                                                                                                                          
//   Cannot make route less than two airports. If the route has                                                                                                                                                                                                                                                                                                                          
//   two or fewer airports, fails.                                                                                                                                                                                                                                                                                                                                                       
// Postconditions: Name may be updated. Size is reduced.                                                                                                                                                                                                                                                                                                                                 
//   Route has one less airport.  
void Route::RemoveAirport(int airport){
    // Remove an airport from the route
    Airport *prev = m_head;
    Airport *curr = m_head;

    //If position is the first airport
    if(airport == 0){
        m_head = m_head->GetNext();
        delete curr;
        curr = nullptr;
        if(m_size == 1){
            m_tail = nullptr;
        }
    }else{
        // Traverse to the airport to be removed
        for (int i = 0; i < airport; i++){

            prev = curr;
            curr = curr->GetNext();
        }
        prev->SetNext(curr->GetNext());

        // If the last airport is being removed
        if (curr == m_tail){
            m_tail = prev;
        }
        delete curr;
    }
    m_size--;

    m_name = UpdateName();
    
}

// Name: GetName()                                                                                                                                                                                                                                                                                                                                                                       
// Desc: Returns the name of the route (Usually starting                                                                                                                                                                                                                                                                                                                                 
//  airport to last airport)                                                                                                                                                                                                                                                                                                                                                             
//  For example: Baltimore to Boston                                                                                                                                                                                                                                                                                                                                                     
// Preconditions: Requires a Route                                                                                                                                                                                                                                                                                                                                                       
// Postconditions: Returns m_name; 
string Route::GetName(){
    return m_name;
}

// Name: UpdateName()                                                                                                                                                                                                                                                                                                                                                                    
// Desc: Updates m_name based on the name of the first airport                                                                                                                                                                                                                                                                                                                           
//   in the route and the last airport in the route                                                                                                                                                                                                                                                                                                                                      
//       For example: Baltimore to Boston                                                                                                                                                                                                                                                                                                                                                
// Preconditions: Requires a Route with at least two airports                                                                                                                                                                                                                                                                                                                            
// Postconditions: Returns m_name; 
string Route::UpdateName(){
    // Update the name of the route
    if(m_head == nullptr || m_head->GetNext() == nullptr){
        cout << "Route must have at least two airports" << endl;
        return "";
    }
    else{
        string newName = m_head->GetCity() + " to " + m_tail->GetCity();
        m_name = newName;
        return m_name;
    }


}

// Name: GetSize()                                                                                                                                                                                                                                                                                                                                                                       
  // Desc: Returns the number of airports in a route                                                                                                                                                                                                                                                                                                                                       
  // Preconditions: Requires a Route                                                                                                                                                                                                                                                                                                                                                       
  // Postconditions: Returns m_size; 
int Route::GetSize(){
    return m_size;
}

// Name: ReverseRoute                                                                                                                                                                                                                                                                                                                                                                    
// Desc: Reverses a route                                                                                                                                                                                                                                                                                                                                                                
// Preconditions: Reverses the Route                                                                                                                                                                                                                                                                                                                                                     
// Postconditions: Route is reversed in place; nothing returned 
void Route::ReverseRoute(){
    if(m_head == nullptr || m_head->GetNext() == nullptr){
        cout << "Route must have at least two airports" << endl;
        return;
    }

    Airport *curr = m_head;
    Airport *prev = nullptr;
    Airport *next = nullptr;

    while(curr != nullptr){
        next = curr->GetNext();
        curr->SetNext(prev);
        prev = curr;
        curr = next;
    }
    m_tail = m_head;
    m_head = prev;
}

// Name: GetData (int)                                                                                                                                                                                                                                                                                                                                                                   
// Desc: Returns an airport at a specific index                                                                                                                                                                                                                                                                                                                                          
// Preconditions: Requires a Route                                                                                                                                                                                                                                                                                                                                                       
// Postconditions: Returns the airport from specific item 
Airport* Route::GetData(int index){
    if(index < 0 || index >= m_size){
        cout << "Invalid index" << endl;
        return nullptr;
    }
    else{
        // Traverse the linked list to find the airport at the given index
        Airport* curr = m_head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->GetNext();
        }
        return curr;
        
    }
}

// Name: DisplayRoute                                                                                                                                                                                                                                                                                                                                                                    
// Desc: Displays all of the airports in a route                                                                                                                                                                                                                                                                                                                                         
// Preconditions: Requires a Route                                                                                                                                                                                                                                                                                                                                                       
// Postconditions: Displays all of the airports in a route                                                                                                                                                                                                                                                                                                                               
// Formatted: Baltimore, Maryland (N39.209 W76.517) 
void Route::DisplayRoute(){
    Airport* curr = m_head;
    int count = 1;

    // Traverse the linked list and display information for each airport
    while(curr != nullptr){
        cout << count << ". " << curr->GetCode() << ", " << curr->GetName() << ", " << curr->GetCity() << " (" << "N" << curr->GetNorth() << " " << "W" << curr->GetWest() << ")" << endl;
        curr = curr->GetNext();
        count++;
    }
}
