Assignment 1: Revisiting DS

Design and Analysis of Algorithms,

Even Semester, 2020-2021

Date: 22/1/2021

Deadline: 9/3/2021
Total Marks: 18
Late Submission: 20% penalty if delayed by one week. 50% penalty if delayed by two week. No
evaluation after that.

1. Write a program (WAP) to create an undirected graph using adjacency matrix representation.
Number of nodes and edges should be taken from the user. After creating the graph, perform
following operations: (6 Marks)

(i) Search a node. Take the node number from the user. If the node is found then print its associated
edges.

(ii) Insert a node in the graph.

(iii) Insert an edge in the graph. Take the node numbers from the user between which the edge is to
be inserted.

(iv) Delete a node from the graph. Take the node number to be deleted from the user.

(v) Apply DFS on the graph and print the graph traversal.

(vi) Apply BFS on the graph and print the graph traversal.

2. Solve the above problem using adjacency list representation. (3 Marks)

3. (i) WAP to create, insert, search and delete operations in a binary search tree (BST). (3 Marks)

(ii) WAP to store a BST in a file. Here, you have to write two programs in which the first program
will write the BST in the file and the second programs will read the file and reconstruct the BST.
(Hint: As we know that if preorder or postorder traversal of a BST is given then the original BST
can be constructed using it. So, in his question, you have to store the preorder or postorder traversal
of the BST in the file. While reconstructing the BST just retrieve the traversal from the file and
construct the BST. (2 Marks)

4. Use the solution of 3 (i) and 3 (ii) to solve this question. (4 Marks)
In this question, with the help of BST , develop a file search utility in which the user will be asked
to enter a word to be searched in a text file. As an output, the program should print (a) total number
of occurrences of the given word in the text file (b) Line numbers in which the given word is
present.

In order to construct the BST, scan each word of the text file. Let the first word of the file be the
root node of the BST. So, the second word, be its left child or right child, will depend on the value
returned by STRCMP (firstword, secondword) function. If the returned value is positive then the
second word will be the left child. If the returned value is negative then the second word will be the
right child. Similarly, the whole BST can be constructed. With each node, a linked list should be
associated to store the line numbers on which the word occurs. So, a node in the linked list will
have three fields, (a) line number, (b) number of occurrences of the word in that line number (c)
pointer to the next node. Store the constructed BST in a file so that in the next execution of the
program, the same BST can be reconstructed.
