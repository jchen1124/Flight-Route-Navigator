#include "Route.h"
#include <iostream>

using namespace std;

Route::Route(){
    m_name = "";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

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

void Route::SetName(string name){
    m_name = name;
}


void Route::InsertEnd(string code, string name, string city, string country, double north, double west){
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
void Route::RemoveAirport(int airport){

    // if(airport < 0 || airport >= m_size){
    //     cout << "Invalid Input" << endl;
    //     return;
    // }

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

string Route::GetName(){
    return m_name;
}

string Route::UpdateName(){
    if(m_head == nullptr || m_head->GetNext() == nullptr){
        cout << "Route must have at least two airports" << endl;
        return "";
    }
    else{
        string newName = m_head->GetName() + " to " + m_tail->GetName();
        m_name = newName;
        return m_name;
    }


}

int Route::GetSize(){
    return m_size;
}

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

Airport* Route::GetData(int index){
    if(index < 0 || index >= m_size){
        cout << "Invalid index" << endl;
        return nullptr;
    }
    else{
        Airport* curr = m_head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->GetNext();
        }
        return curr;
        
    }
}

void Route::DisplayRoute(){
    Airport* curr = m_head;
    int count = 1;

    while(curr != nullptr){
        cout << count << ". " << curr->GetName() << "," << curr->GetCity() << " (" << "N" << curr->GetNorth() << " " << "W" << curr->GetWest() << ")" << endl;
        curr = curr->GetNext();
        count++;
    }
}
