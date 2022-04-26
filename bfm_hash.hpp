#ifndef BFM_HPP_
#define BFM_HPP_

/*
* hashMap: A custom class to implement a hash table.
*
*          hashMap<Type1, Type2>::hashMap();
*          hashMap<Type1, Type2>::hashMap(const hashMap<Type1, Type2>&);
*
*          const hashMap<Type1, Type2>& operator=(const hashMap<Type1, Type2>&);
*          Type2 &operator[](Type1);
*
*          size_t tableSize;
*	       size_t items;
*          tableItem *table;
*          void resize();
*          size_t hashFunction01(char) const;
*          size_t hashFunction02(char) const;
*/
template <class Type1, class Type2>
class hashMap {
public :
    hashMap();
    hashMap(const hashMap <Type1, Type2>&);
    const hashMap <Type1, Type2>& operator=(const hashMap <Type1, Type2>&);
    ~hashMap();
    Type2 &operator [](Type1);

private :
    struct tableItem {
        Type1 key ;
        Type2 item ;
    };

    size_t hashFunction01(char) const ;
    size_t hashFunction02(char) const ;
    void resize ();
    size_t tableSize;
    size_t items;
    tableItem *table;
};

/*
* default constructor
*/
template <class Type1, class Type2>
hashMap<Type1, Type2>::hashMap() {
    items = 0;
    tableSize = 5;
    table = new tableItem[tableSize];

    for(auto i = 0; i < tableSize; ++i) {
        table[i].key = Type1();
        table[i].item = Type2();
    }
}

/*
* copy constructor
*/
template <class Type1, class Type2>
hashMap<Type1, Type2>::hashMap(const hashMap<Type1, Type2>& copy) {
    items = copy.items;
    tableSize = copy.tableSize;
    table = new tableItem[tableSize];

    for(auto i = 0; i < tableSize; ++i) {
        table[i].key = copy.table[i].key;
        table[i].item = copy.table[i].item;
    }
}

/*
* default destructor
*/
template <class Type1, class Type2>
hashMap<Type1, Type2>::~hashMap()
{
    delete [] table;
}

/*
* hashFunction01: primary hashing function.
* parameters: key: a unique identifier of an item.
* return value: an encoded form of 'key'.
*/
template <class Type1, class Type2>
size_t hashMap<Type1, Type2>::hashFunction01(char key) const
{
    return (key % tableSize);
}

/*
* hashFunction02: secondary hashing function.
* parameters: key: a unique identifier of an item.
* return value: an encoded form of 'key'.
*/
template <class Type1, class Type2>
size_t hashMap<Type1, Type2>::hashFunction02(char key) const
{
    return ((key % tableSize * (tableSize / 2)) % tableSize);
}

/*
* []: overloaded hash table access operator.
* parameters: key: a unique identifier of an item.
* return value: a reference to the item associated with key.
*/
template <class Type1, class Type2>
Type2& hashMap<Type1, Type2>::operator[](Type1 key)
{
    double load_factor = items / tableSize; //< measures dispersity of items
    size_t index1 = hashFunction01(key);    //< encoded key

    // is rehashing is required?
    if(load_factor >= 0.5) {
        resize();
    }

    // is 'key' a new key?
    if(table[index1].key == key) {
        return table[index1].item;
    }

    // is 'key' an old but uninitialized key?
    if(table[index1].key == Type1(0)) {
        ++items;
        table[index1].key = key;
        return table[index1].item;
    }

    size_t index2 = hashFunction02(key);  //< encoded key

    // did a collision occur?
    if(table[index1].key != key && table[index1].key != Type1(0)) {
        if(table[index2].key == key) {
            return table[index2].item;
        }

        else if(table[index2].key == Type1(0)) {
            table[index2].key = key;
            ++items;
            return table[index2].item;
        }
    }

    // resolve key iteratively when a collision occures again
    for(auto i = 0; ; ++i) {
        size_t index = (index1 + index2 + i) % tableSize;

        if(table[index].key == key) {
            return table[index].item;
        }

        else if(table[index].key == Type1(0)) {
            table[index].key = key;
            ++items;
            return table[index].item;
        }
    }
}

/*
* =: overloaded assignment operator.
* parameters: rhs: a hashMap to assign to caller.
* return value: a reference to the caller.
*/
template <class Type1, class Type2>
const hashMap<Type1, Type2>& hashMap<Type1, Type2>::operator=(const hashMap<Type1, Type2>& rhs)
{
    // check for self-assignment
    if (this == &rhs) {
        return *this;
    }

    // if the current table isn't empty, delete it
    if(table) {
        delete [] table;
    }

    items = rhs.items;
    tableSize = rhs.tableSize;

    // reinitialize hash table entries of caller with 'rhs' values
    for(auto i = 0; i < tableSize; ++i) {
        table[i] = new tableItem;
        table[i].key = rhs.table[i].key;
        table[i].item = rhs.table[i].item;
    }

    return *this;
}

/*
* resize: doubles size of hash table to minimize collision.
*/
template <class Type1, class Type2>
void hashMap<Type1, Type2>::resize()
{
    // saves table into temporary array
    size_t oldSize = tableSize;
    tableItem * oldTable = table;
    tableSize *= 2;
    items = 0;
    table = new tableItem[tableSize]; // creates a new larger table

    for (int i = 0; i < tableSize; i++)
    {
        table[i].key = Type1();
        table[i].item = Type2();
    }

    // rehashes everything from old table into new table
    for (int i = 0; i < oldSize; i++)
        if (oldTable[i].key != Type1())
            (*this)[oldTable[i].key] = oldTable[i].item;

    delete [] oldTable; // deallocate old table

    return;
}

#endif  // BFM_HPP_

/* EOF */