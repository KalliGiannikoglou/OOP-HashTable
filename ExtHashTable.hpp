#include <iostream>
#include <cstring>
#include <stdexcept>
#include "HashTable.hpp"

class ExtHashTable: public HashTable {
    private:
        double upper_bound_ratio, lower_bound_ratio;
        void rehash();
        double getUpperBoundRatio() const;
        double getLowerBoundRatio() const;
        bool addHT(const string &s);

    public:
        ExtHashTable( double upper_bound_ratio=0.5, double lower_bound_ratio=0.125, int size=8);  
        ExtHashTable(const ExtHashTable &t); 
        bool add(const string &str);
        bool add(const char *s);
        bool remove(const string &str); 
        bool remove(const char *s);

        ExtHashTable &operator = (const ExtHashTable &t);
        
        ExtHashTable operator+(const string &str) const;
        ExtHashTable operator+(const char* s) const;
        ExtHashTable operator-(const string &str) const;
        ExtHashTable operator-(const char *s) const;
        
        ExtHashTable& operator += (const string &str);
        ExtHashTable& operator += (const char* s);
        ExtHashTable& operator -= (const string &str);
        ExtHashTable& operator -= (const char *s);
        
        ExtHashTable operator+(const ExtHashTable &t) const;
        ExtHashTable &operator+=(const ExtHashTable &t);
};

