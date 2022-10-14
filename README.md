# Efficient Storage and Retrieval of Data (ESRD)

### Introduction

This project is a solution to a problem statement that was given to my team as part of our Data Structures and C Programming course. It was made with no prior experience in software development, without any references, and only with the knowledge of C Programming and Data Structures.

### Team

<ul>
  <li><a href="https://github.com/tarunkay7">Tarun Kesavan</a></li>
  <li><a href="https://github.com/yaldabaoth007">Gowtham Valluri</a></li>
  <li><a href="https://github.com/D-Arnav">Arnav Devalapally</a></li>
</ul>

### Goal

The Goal is to have a system that can insert, delete, and retrieve data as efficiently as possible. The catch however, is that the data can be searched based on two keys. This disallows the use of hashing and makes the problem a lot more complicated.

In this particular example, the data to be stored is a bank account, and the account details can be retrieved using the owner's name or SSN.

### Approach

Hashing is the fastest algorithm for data retrival, and so this formed the basis of storing the data, the hash key for the data is owner name, which allows you to retrieve bank account details from owner name in close to O(1) time. However, with only hashing, it would be difficult to retrieve data from SSN.
The second data structure used is an AVL Tree. This is the most efficient tree data structure for searching data. However, storing all the data once again in a tree wouldn't be memory efficient. 
The solution was to have the AVL Tree store nodes containing just the SSN and owner name, and structured by SSN. This way, the nodes can be searched by SSN in O(logN) time, and we can get the name from the node. Passing this name into the hash function, would then retrieve the bank account details in a total of O(logN) time.

### Time Complexity
<ul>
  <li>Insertion: O(logN)</li> 
  <li>Deletion: O(logN)</li>
  <li>Search by name: O(1)</li>
  <li>Search by SSN: O(logN)</li>
</ul>
