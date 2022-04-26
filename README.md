
# Best Friend Match

# Description

It’s been a long past year and a half of isolation. Now you’re ready to get out there and mingle and meet
new people. As a computer science student, you’ve devised an algorithm to find new friends. This algorithm
is to match with people with the most letters in their name in common with yours, this definitely cannot fail.
Of course, you want to avoid doing this in a brute force fashion, but rather use some hash map structure to
speed up this algorithm since fall semester is coming up really soon so you don’t want to waste time. Here
is the following hash map structure you would need to implement.

```
template <class Type1 , class Type2 >
class hashMap
{
public:
hashMap ();
hashMap(const hashMap <Type1 , Type2 >&);
const hashMap <Type1 , Type2 >& operator =(const hashMap <Type1 , Type2 >&);
~hashMap ();
Type2& operator []( Type1 );
private:
struct tableItem
{
Type1 key;
Type2 item;
};
```
```
size_t hashFunction01(char) const;
size_t hashFunction02(char) const;
void resize ();
size_t tableSize;
size_t items;
tableItem * table;
};
```
# Contents of Main/Input

The first line of the input file will be a name `N` and an integer `T` that denotes the number of test cases. For
each test case there will be

- an integer `J`
- an integer `K`

Where `J` denotes the amount of names in the test case to compare with `N`, and `K` denotes to print out the
top `K` people that have the most letters in common, from most to least, see the sample output for more
details.

# Specifications

- Document your code (any function and all member functions of `myHash` class)
- Do not modify the class, do not modify member functions return types or their parameter types/amount
- No global variables
- Make sure your program is memory leak free

# Example Output

```
$ g++ Assignment06.cpp
$ ./a.out
```
```
Enter input file: A6Input01.txt
```
```
Case 1: Jonas Tom
Case 2: Craig
Case 3: Sparow Jack Fido Kyle
Case 4: RumpleStilkn Brawndo Cartman
```
```
$ ./a.out
```
```
Enter input file: MoreInputAssignment6.txt
```
```
Case 1: Phoenix Aaron Brian Rob Justin
Case 2: Ethan Lawrence
```