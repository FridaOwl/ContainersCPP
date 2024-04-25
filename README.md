# ContainersCPP

## Contents

1. [Part 1. Implementation of the d3_containers.h library](#part-1-implementation-of-the-d3_containersh-library)
2. [Part 2. Bonus. Implementation of the d3_containers.h library](#part-2-bonus-implementation-of-the-d3_containersplush-library)
3. [Part 3. Bonus. Implementation of the `insert_many` method](#part-3-bonus-implementation-of-the-insert_many-method)

## Part 1. Implementation of the d3_containers.h library

You need to implement the `d3_containers.h` library classes (specifications are given in the relevant material sections, see **"Main containers"**). \
List of classes: `list`, `map`, `queue`, `set`, `stack`, `vector`.
- Make it as a header file `d3_containers.h` which includes different header files with implementations of the specified containers (`d3_list.h`, `d3_map.h`, and etc.) 
- Provide a Makefile for testing the library (with targets clean, test)
- The classical implementation of containers should be considered as a basis, but the final choice of implementations remains free. Except for the list - it should be implemented via the list structure rather than the array

## Part 2. Bonus. Implementation of the d3_containersplus.h library.

You need to implement the `d3_containers.h` library functions (see **"Additional containers"** for specifications). \
List of classes to be implemented additionally: `array`, `multiset`.
- Make it as a header file `d3_containers.h` which includes different header files with implementations of the specified containers (`d3_array.h`, `d3_multiset.h`) 
- Provide a Makefile for testing the library (with targets clean, test)
- The classical implementation of containers should be considered as a basis, but the final choice of the algorithm remains free.

## Part 3. Bonus. Implementation of the `insert_many` method.

You need to complete the classes with the appropriate methods, according to the table:

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator insert_many(const_iterator pos, Args&&... args)`          | inserts new elements into the container directly before `pos`  | List, Vector |
| `void insert_many_back(Args&&... args)`          | appends new elements to the end of the container  | List, Vector, Queue |
| `void insert_many_front(Args&&... args)`          | appends new elements to the top of the container  | List, Stack |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)`          | inserts new elements into the container  | Map, Set, Multiset |

Note: the arguments are the already created elements of the appropriate container that should be inserted into this container.

Remember to test methods for different cases, including boundary ones.

