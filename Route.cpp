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
    Airport *prev = m_head;
    Airport *curr = m_head;

    if(airport < 0 || airport > m_size){
        cout << "Invalid Size" << endl;
        return;
    }

    //If position is the first node
    if(airport == 0){
        Airport *temp = m_head->GetNext();
        delete temp;
        m_head = temp;
        //m_head = m_head->GetNext();
        
    }else{
        for (int i = 0; i < airport - 1; i++){

            prev = curr;
            curr = curr->GetNext();
        }
        prev->SetNext(curr->GetNext());

        // If the last node is being removed
        if (curr == m_tail){
            m_tail = prev;
        }
        
    }
    m_size--;
    delete curr;
}

string Route::GetName(){
    return m_name;
}

string Route::UpdateName(){
    if(m_head == nullptr || m_tail == nullptr){
        return "";
    }
    else{
        return m_head->GetName() + "to" + m_tail->GetName();
    }
}

int Route::GetSize(){
    return m_size;
}

void Route::ReverseRoute(){
    Airport *curr = m_head;
    Airport *prev = nullptr;
    Airport *next = nullptr;

    while(curr != nullptr){
        next = curr->GetNext();
        curr->SetNext(prev);
        prev = curr;
        curr = next;
    }
    m_head = prev;
}

Airport* Route::GetData(int index){
    if(index < 0 || index >= m_size){
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

    while(curr != nullptr){
        cout << curr->GetName() << "," << curr->GetCity() << " (" << "N" << curr->GetNorth() << "W" << curr->GetWest() << ")" << endl;
        curr = curr->GetNext();
    }
}
