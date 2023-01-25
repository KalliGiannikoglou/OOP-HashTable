#include "ExtHashTable.hpp"

ExtHashTable:: ExtHashTable( double upper_bound_ratio, double lower_bound_ratio, int size) : 
    HashTable(size),    
    upper_bound_ratio(upper_bound_ratio), 
    lower_bound_ratio(lower_bound_ratio) { }


    
   

ExtHashTable:: ExtHashTable(const ExtHashTable &t):
    HashTable(t),
    upper_bound_ratio(t.upper_bound_ratio), 
    lower_bound_ratio(t.lower_bound_ratio){ }


bool ExtHashTable::addHT(const string &s){
    int h;
    unsigned long x = getHashCode(s.c_str());
    int initial_pos = x % capacity;
    
    for(int n=0; n<capacity; n++){
        h = (x+n) % capacity;
        //if we returned in the first pos for n=0, we cannot place str in this table
        if(h == initial_pos && n != 0){
            return false;
        }
        //check if pos h is available for adding
        if(isAvailable(h) && s != "" && s != "0xFFFF"){
            table[h] = new string(s);
            size++;
            return true;
        } 
    }
    return false;
}


//Virtual methods of parent class
bool ExtHashTable::add(const string &s){
    //check if s is already in the table
    if(contains(s) == 1){
        return false;
    }
    rehash();
    bool res =  addHT(s);
   
    return res; 
}
bool ExtHashTable::add(const char *s){
    //check if s is already in the table
    if(contains(s) == 1){
        return false;
    }
    rehash();
    bool res =  addHT(s);
    
    return res; 
}
bool ExtHashTable::remove(const string &s){
   
    if(contains(s) == false){
        return false;
    }
    if(removeHT(s)){
        rehash();
        return true;
    }
    return false;
}


bool ExtHashTable::remove(const char *s){
   if(contains(s) == false){
        return false;
    }
    if(removeHT(s)){
        rehash();
        return true;
    }
    return false;
}

void ExtHashTable:: rehash(){
    double load_factor =  size /(double) capacity;
    int new_capacity;

    if(size == 0){
        return;
    }
    //check if there is need for new capacity
    else if(load_factor > upper_bound_ratio){
        new_capacity = 2*getCapacity();
    }
    else if(load_factor < lower_bound_ratio){
        new_capacity =  getCapacity()/2;
    }
    else{
        return;
    }

    //create the new table with the new_capacity
    ExtHashTable new_ht(upper_bound_ratio, lower_bound_ratio, new_capacity);
    
    //for every entry in the old ht, find the new pos in the new ht
    for(int i=0; i<this->capacity; i++){
        if(this->table != nullptr && this->table[i] != nullptr && *this->table[i] != ""){
            new_ht.addHT( this->getStr(i));
        }
    }

    

    //assign the new array to this class
    *this = new_ht;
    cout << "--> Size: " << new_ht.getSize() << ", New capacity: " << new_ht.getCapacity() << endl;
}

double ExtHashTable:: getUpperBoundRatio() const{
    return this->upper_bound_ratio;
}

double ExtHashTable:: getLowerBoundRatio() const{
    return this->lower_bound_ratio;
}


ExtHashTable& ExtHashTable:: operator= (const ExtHashTable &t){
    
    for(int i=0;  i< this->getCapacity()+1; i++){
        if(table!= nullptr && table[i] != nullptr){
            delete this->table[i];
        }
    }
    delete [] this->table;
  
    // //change the size of this->table to be equal to ht.size
    this->table = new string*[t.getCapacity()+1];
    this->size = t.getSize();
    this->capacity = t.getCapacity();
    this->upper_bound_ratio = t.getUpperBoundRatio();
    this->lower_bound_ratio = t.getLowerBoundRatio();
 

    //assign all the ptrs of this->table to be equal with ht->table
    for(int i=0; i<capacity; i++){
       if(t.table[i] != nullptr && *t.table[i] != ""){
            table[i] = new string(t.getStr(i));

        }
        else{
            table[i] = nullptr;
        }
    }
    this->table[capacity] = new string("");
  
    return *this;
}

ExtHashTable ExtHashTable::operator+(const string &str) const{
    
    ExtHashTable ht = *this;
    ht.add(str);
  
    return ht;
}

ExtHashTable  ExtHashTable::operator+(const char* s) const{
    ExtHashTable ht = *this;
    ht.add(s);
  
    return ht;
}

ExtHashTable ExtHashTable::operator-(const string &str) const{
    
    ExtHashTable ht = *this;
    ht.remove(str);
  
    return ht;
}

ExtHashTable  ExtHashTable::operator-(const char* s) const{
    ExtHashTable ht = *this;
    ht.remove(s);
  
    return ht;
}

ExtHashTable& ExtHashTable::operator+= (const string &str){
    
    add(str);
    return *this;
}

ExtHashTable&  ExtHashTable::operator+= (const char* s){
    
    add(s);
    return *this;
}

ExtHashTable& ExtHashTable::operator-= (const string &str){
    
    remove(str);
    return *this;
}

ExtHashTable&  ExtHashTable::operator-= (const char* s){
    
    remove(s);
    return *this;
}

ExtHashTable ExtHashTable::operator+(const ExtHashTable &t) const{

    //copy constructor
    ExtHashTable new_ht = *this;

    for(int i=0; i<t.capacity; i++){
        if(t.table[i] != nullptr)
            //copy the entries from t.table
            new_ht.add(t.getStr(i));
    }    
    return new_ht;
}


ExtHashTable& ExtHashTable::operator+=(const ExtHashTable &t){

    for(int i=0; i < t.capacity; i++){
        if(t.table[i] != nullptr)
            add(t.getStr(i));
    }
    return *this;
}

