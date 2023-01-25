#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include "HashTableException.hpp"
#include <stdlib.h>

using namespace std; 


class HashTable {
  
    protected:
        int size;
        int capacity;
        string **table;

        static unsigned long getHashCode(const char *str); 

        bool isEmpty(int pos) const;
        bool isTomb(int pos) const;
        bool isAvailable(int pos) const;
    
        HashTable InsertToNewTable(const string& str) const;
        HashTable RemoveFromNewTable(const string& str) const;
        bool addHT(const string &s);
        bool removeHT(const string &s);
    
    public:  
        HashTable(int capacity = 8);
        HashTable(const HashTable &ht);
        ~HashTable();

        int getSize() const;
        int getCapacity() const;
        string getStr(const int pos) const;
        
        bool contains(const string &s) const;
        bool contains(const char *s) const;
        string print() const;

        virtual bool add(const string &s);
        virtual bool add(const char *s);
        virtual bool remove(const string &s);
        virtual bool remove(const char *s);
        
        HashTable& operator = (const HashTable &ht);
        
        HashTable& operator += (const string& str);
        HashTable& operator += (const char* s);
        HashTable& operator -= (const string& str);
        HashTable& operator -= (const char* s);
        
        HashTable operator + (const string& str) const;
        HashTable operator + (const char* s) const;
        HashTable operator - (const string& str) const;
        HashTable operator - (const char* s) const;
        
        //nested class
        class Iterator;

        friend std::ostream& operator<<(std::ostream &stream, const HashTable &t);
        Iterator begin() const;
        Iterator end() const;

};

class HashTable::Iterator {
    string **curr;
    const HashTable *ht;
    int position; 

    public:    
        Iterator(const HashTable *t);
        Iterator(const HashTable *t, bool end);
        Iterator(const Iterator &it);
        ~Iterator();
        Iterator& operator=(const Iterator &it);
        Iterator operator++();
        Iterator operator++(int a);
        bool operator==(const Iterator &it) const ;
        bool operator!=(const Iterator &it) const;
        const string& operator*();
        const string* operator->();
        int pos() const;
        string getStr() const;

};


#endif