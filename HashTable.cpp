#include "HashTable.hpp"

//***********************************HASHTABLE***************************************
string HashTable:: print() const{
    string str;
    char buf[128];

    for(int i=0; i<capacity; i++){
        if( !isAvailable(i) ){
            sprintf(buf, "%2d. -%s-\n", i, (*table[i]).c_str());
            str.append(buf);
        }
    }

    sprintf(buf, " --- CAPACITY: %d, SIZE: %d ---\n", capacity, size);
    str.append(buf);

    return str; 
}


int HashTable:: getSize() const{
    return size;
}

int HashTable:: getCapacity() const{
    return capacity; 
}

string HashTable:: getStr(const int pos) const{
    string str("");
    if(this->table[pos] != nullptr){
        str =  *this->table[pos];
    }
    return str;
}

//Default Constructor
HashTable:: HashTable(int capacity){

    this->capacity = capacity;      //table capacity
    this->size = 0;                 //# of entries

    this->table = new string*[this->capacity+1];
    if(this->table == nullptr){
        std::bad_alloc alloc_ex;
        throw alloc_ex;
    }

    for(int i=0; i <this->capacity; i++){
        this->table[i] = nullptr;
    }
    this->table[capacity] = new string("");
}

//Copy Constructor
HashTable:: HashTable(const HashTable &ht){

    this->capacity = ht.capacity;      //table capacity
    this->size = ht.size;                 //# of entries

    this->table = new string*[this->capacity+1];
    if(this->table == nullptr){
        std::bad_alloc alloc_ex;
        throw alloc_ex;
    }
    for(int i=0; i<capacity; i++){
        if(ht.table[i] != nullptr){
            table[i] = new string(ht.getStr(i));

        }
        else{
            table[i] = nullptr;
        }
    }
    this->table[capacity] = new string("");
}

//Destructor
HashTable:: ~HashTable(){
   
    for(int i=0;  i< this->getCapacity()+1; i++){
        if(table!= nullptr && table[i] != nullptr){
            delete this->table[i];
        }
    }
    delete [] this->table;
}

//returns True if the position was never used before
bool HashTable:: isEmpty(int pos) const{

    if( pos < capacity && table[pos] == nullptr){
        return true;
    }
    return false;
}

//returns true if the position had a value, which was deleted
bool HashTable:: isTomb(int pos) const{
    
    if(table != nullptr && table[pos] == nullptr){
        return false; 
    }
    if( pos < capacity && *table[pos] == "0xFFFF" ){
        return true;
    }
    return false;
}

//returns true if isEmpty or isTomb returns true
bool HashTable:: isAvailable(int pos) const{

    return (isEmpty(pos) || isTomb(pos));
}

//get the hash value of the str
unsigned long HashTable:: getHashCode(const char *str){
    unsigned long hash = 97;
    int c;

    while((c = *(str++)) != '\0')
        hash = ((hash << 5) + hash) + c; 
    
    return hash;
}


bool HashTable::addHT(const string &s){
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
        if(isAvailable(h) && s != ""){
            table[h] = new string(s);
            size++;
            return true;
        } 
    }
    return false;
}

//Adds a str in the table, after checking that is not already in
bool HashTable:: add(const string &s){

    //check if s is already in the table
    if(contains(s) == 1){
        return false;
    }
    //throw exception if there in no free space 
    if(this->size == this->capacity){
        HashTableException ex;
        throw ex;
    }
    return addHT(s.c_str());
   
}

bool HashTable:: add(const char *s){

    //check if s is already in the table
    if(contains(s) == 1){
        return false;
    }
     //throw exception if there in no free space 
    if(this->size == this->capacity){
        HashTableException ex;
        throw ex;
    }
    return addHT(s);
   
}


bool HashTable:: contains(const string &s) const{
    
    return contains(s.c_str());
}

bool HashTable:: contains(const char *s) const{
    int h;
    unsigned long x = getHashCode(s);
    int initial_pos = x % capacity;
    
    for(int n=0; n<capacity; n++){
        h = (x+n) % capacity;
        //if we returned in the first pos for n=0, we cannot place str in this table
        if(h == initial_pos && n != 0){
            return false;
        }
        //an element was deleted from this pos, continue searching
        if(isTomb(h)){
            continue;
        }
        //the element is not in the table
        if(isAvailable(h)){
            return false;
        }
       
        if(table[h]!=nullptr && table[h]->compare(s) == 0){
            return true;
        }

    }
    return false;
}

bool HashTable::removeHT(const string &s){
    int h;
    unsigned long x = getHashCode(s.c_str());
    
    for(int n=0; n<capacity; n++){
        h = (x+n) % capacity;
       
        if(table[h]!=nullptr && table[h]->compare(s) == 0){
            //"0xFFFF" is for tomb positions of the table
            *table[h] = "0xFFFF";
            size--;
            break;
        }
    }
    return true;
}

bool HashTable:: remove(const string &s){
    if(contains(s) == false){
        return false;
    }
    return removeHT(s);
}

bool HashTable:: remove(const char *s){

    if(contains(s) == false){
        return false;
    }
    return removeHT(s);
   
}

//assigns ht to this->ht
HashTable& HashTable::operator = (const HashTable &ht){
    
    for(int i=0;  i< this->getCapacity()+1; i++){
        if(table!= nullptr && table[i] != nullptr){
            delete this->table[i];
        }
    }
    delete [] this->table;
    //change the size of this->table to be equal to ht.size
    this->table = new string*[ht.getCapacity()+1];
    this->size = ht.getSize();
    this->capacity = ht.getCapacity();
    //assign all the ptrs of this->table to be equal with ht->table
    for(int i=0; i<capacity; i++){
       if(ht.table[i] != nullptr && *ht.table[i] != ""){
            table[i] = new string(ht.getStr(i));

        }
        else{
            table[i] = nullptr;
        }
    }
    this->table[capacity] = new string("");

    return *this;
}

HashTable& HashTable::operator += (const string& str){

    //throw exception if there in no free space 
    if(this->size == this->capacity){
        HashTableException ex;
        throw ex;
    }
    add(str);
    return *this;
}

HashTable& HashTable::operator += (const char *str){
    
    //throw exception if there in no free space 
    if(this->size == this->capacity){
        HashTableException ex;
        throw ex;
    }
    add(str);
    return *this;
}

HashTable& HashTable::operator -= (const string& str){

    remove(str);
    return *this;
}

HashTable& HashTable::operator -= (const char *str){

    remove(str);
    return *this;
}

HashTable HashTable::InsertToNewTable(const string& str) const{
    
    HashTable ht = *this;
    ht.add(str);

    return ht;
}

HashTable HashTable::operator + (const string& str) const{
    //throw exception if there in no free space 
    if(this->size == this->capacity){
        HashTableException ex;
        throw ex;
    }
   return InsertToNewTable(str);
}

HashTable HashTable::operator + (const char *str) const{
     //throw exception if there in no free space 
    if(this->size == this->capacity){
        HashTableException ex;
        throw ex;
    }
    return InsertToNewTable(str);
}

HashTable HashTable::RemoveFromNewTable(const string& str) const{
    HashTable ht;
            
    ht = *this;
    ht.remove(str);

    return ht;
}

HashTable HashTable::operator - (const string& str) const{
   return RemoveFromNewTable(str);
}

HashTable HashTable::operator - (const char *str) const{
   return RemoveFromNewTable(str);
}

std::ostream& operator << ( std::ostream &stream, const HashTable &t){
    
    return stream << t.print() << endl; 
}

HashTable::Iterator HashTable::begin() const{

    HashTable::Iterator it(this, true);
    return it;
}

HashTable::Iterator HashTable::end() const{

    HashTable::Iterator it(this, false);
    return it;
}



