# Bloom Filter

![CMake](https://github.com/avivnaaman/HashTable/workflows/CMake/badge.svg?branch=master)

An implementation of the Bloom Filter (Hash-Table-like) Data Structure in C for Data Structures & Algorithms Coure in the Open University of Israel (20407).

## Implementation
Hash function is implemented using [MurmurHash3](https://github.com/PeterScott/murmur3) by Austin Appleby & Peter Scott,
Under a Public Domain License.

Hash to find the cell is done by calculating the MurmurHash3 (32bit) of the value and then "Normalize" it to the size of the array by 
calculating the hash mod size.
