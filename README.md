# Bloom Filter

![CMake](https://github.com/avivnaaman/HashTable/workflows/CMake/badge.svg?branch=master)

An implementation of the [Bloom Filter](https://en.wikipedia.org/wiki/Bloom_filter) (Hash Table-like) Data Structure using The C programming language for Data Structures & Intoduction to Algorithms Coure @ The Open University of Israel (Course 20407, Semester 2021a, Maman 14).

The code is licensed under the MIT license (excpet for the contents of the murmur.[c|h] files, which are public domain and sourced [here](https://github.com/PeterScott/murmur3).

## Implementation
Hash function is implemented using [MurmurHash3](https://github.com/PeterScott/murmur3) by Austin Appleby & Peter Scott,
Under a Public Domain License.

Hash to find the cell is done by: (1) calculating the MurmurHash3 (32bit) of the value and then (2) "Normalize" it to the size of the array (by 
calculating the mod of the hash by the table size - which is, assuming the table is not too big, accurate enough and distributs uniformly).

