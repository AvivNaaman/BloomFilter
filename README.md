# HashTable

![CMake](https://github.com/avivnaaman/HashTable/workflows/CMake/badge.svg?branch=master)

An implementation of a Hash Table in C for Data Structures & Algorithms Coure in the Open University of Israel (20407).
(Rights to the structure idea is reserved to the Open University of Israel)
## Data Structure
The data structure is Hash-Table based. The user chooses the size of the table and the number of hash functions.
The table is full with 0/FALSEs at start.
##### Insertion
Each value that is inserted into the table is hashed with each hash function (That is created on table initialization).
Each hash function result is in the range of the size of the array.
For each result of hash function, the array value in the index of the result is set to TRUE/1.
##### Checking Existence
To check existance, the value is hashed again and the cell in the index of the hash result is checked for 1/TRUE.
if It's FALSE then (for sure) the value was not inserted.
if It's TRUE the value is considered as inseretd (The chance of error is very low).
## Implementation
Hash function is implemented using [MurmurHash3](https://github.com/PeterScott/murmur3) by Austin Appleby & Peter Scott,
Under a Public Domain License.

Hash to find the cell is done by calculating the MurmurHash3 (32bit) of the value and then "Normalize" it to the size of the array by 
calculating the hash mod size.
