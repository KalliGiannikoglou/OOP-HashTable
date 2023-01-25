#include "HashTable.hpp"

HashTable::Iterator:: Iterator(const HashTable *t){

    this->ht = t;
    this->curr = new string*;
}

HashTable::Iterator:: Iterator(const HashTable *t, bool start){

    this->ht = t;   
    this->curr = new string*;
    //start
    if(start == true){  
         
        for(int i=0; i< ht->getCapacity()+1; i++){
            if(ht->table[i] != nullptr && ht->isTomb(i)){
                *this->curr = ht->table[i];
                this->position = i;
                break;
            }
        }
    }
    //end
    else{               
        *this->curr = ht->table[ht->capacity];
        this->position = ht->capacity;
    }
}

//copy constructor
HashTable::Iterator:: Iterator(const Iterator &it){

    this->ht = it.ht;
    this->curr = new string*;
    *this->curr = *it.curr;
    this->position = it.position;
}

HashTable::Iterator:: ~Iterator(){
    delete this->curr;
    
}

int HashTable::Iterator::pos() const{
    return position;
}

const string& HashTable::Iterator:: operator*(){
    return **this->curr;
}

const string* HashTable::Iterator:: operator->(){
    return *this->curr;
}

HashTable::Iterator& HashTable::Iterator::operator=(const Iterator &it){
    
    //call copy constructor
    if(this->ht == nullptr){
        Iterator new_it(it);
    }
    else{   //do not allocate extra space 
        *this->curr = *it.curr;
        this->ht = it.ht;
        this->position = it.position;
    }

    return *this;
}

HashTable::Iterator HashTable::Iterator::operator++(){
    
    for(int i=pos()+1; i < ht->getCapacity() + 1; i++){
        
        if(ht->table[i] !=  nullptr && !ht->isTomb(i)){
            *this->curr = ht->table[i];
            this->position = i;
            break;
        }
    }
    return *this;
}

HashTable::Iterator HashTable::Iterator::operator++(int a){
    
    Iterator old_it(*this);
    
    for(int i=pos()+1; i < ht->getCapacity() + 1; i++){
        if(ht->table[i] !=  nullptr && !ht->isTomb(i)){
            *curr = ht->table[i];
            position = i;
            break;
        }
    }
    return old_it;
}

bool HashTable::Iterator:: operator==( const Iterator &it) const{

    return ( *this->curr == *it.curr &&
            this->position == it.position && 
            this->ht == it.ht  );
}

bool HashTable::Iterator:: operator!=( const Iterator &it) const{

    return !( *this->curr == *it.curr &&
            this->position == it.position && 
            this->ht == it.ht  );
}

string HashTable::Iterator:: getStr() const{
    return **curr;
}