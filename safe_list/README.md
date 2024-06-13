# Safe List Implementation

Design a data structure for an array that is safe for concurrent reading and writing. This structure should allow simultaneous reading from different indices of the array by multiple threads, preventing any kind of conflict that could occur when accessing the same index concurrently.

## Problem Requirements

Your task is to design a class or data structure in a programming language that ensures safe concurrent access to array indices for both reading and writing. This class or structure should provide mechanisms for synchronizing access to array elements so that simultaneous read and write operations by multiple threads on the same index do not conflict. For example, if two threads attempt to access indices 3 and 4 concurrently, there should be no interference. However, if both threads want to access the same index, a lock or similar mechanism should ensure safe access.

- This structure should support the following functions: read, write, length, append, and delete.

## Additional Score Sections (<u>not implementated</u>)
- Management of fundamental resources like Lock and Condition.
- Use of Readers-Writers lock.
- Reading and writing to a specific range of array indices.