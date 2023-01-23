# huffman
Performs file compression and decompression in C++ by building and processing a tree of structs to execute Huffman's encoding algorithm.

ZIP & UNZIP = non-binary, standard compression & uncompression
              minimum program requirements
./ZIP sample1 = creates a sample1.zip compressed file & deletes sample1
./UNZIP sample1.zip = uncompress sample1.zip to sample1

c++ -c huffman.cpp
c++ zip.cpp huffman.o
c++ unzip.cpp

////////////////////////////////////////////////////////////////////////

The purpose of this project is to develop the huffman.cpp implementation
file such that it can be used to drive the zip.cpp and unzip.cpp client
files.The unzip.cpp file simply receives the compressed file as input
character by character and traverses the huffman tree until it reaches
a leaf node. This node is always a character and is then sequentially
concatenated into the output string.

The zip.cpp file has a more complicated approach. The program will
count the number of times a character is used and store it in a map.
This is how to store each value's frequency and character. Next,
this map (vector of structs) will be converted into a min heap to be 
utilized effectively as a priority queue. The least frequent character
is root.

Once the min heap is built, extract the first two values from the min
heap. From these two values, create an internal node of type struct
with a frequency of the sum of the two frequencies. The two extracted
nodes will be the left and right children of the new node. Repeat
this step until only one node remains which will now be the root.

Once the huffman tree is built, a file of characters can be converted
into a string of 1s and 0s and is now compressed. This file can be
uncompressed as well by using the huffman tree. Now I will cover
features and functions of this project:

compression ratio=1-(# Bits Compressed File)/(# Chars in Source File*8)
	> the only output of the zip.cpp file is the following:
	   "File Succesfully Compressed To X Bits (Y% Less)"

file format
	> after compression: sample1.zip
		>top line: # of chars being compressed
			>aka # of leaves in tree
		>assignment lines:
			>ASCII value of char in base 10
			>string binary representation of char
		>output line:
			>the compressed file output in binary
		
Important operations: Huffman class
	insert: inserts a char and it's frequency into Huffman Tree
	inTree: true/false indicating whether char is store in tree
	GetFrequency: return the weight of a indicated char
	GetCode: returns compressed code of char using recursion
	numNodes: returns number of nodes = 2 * # chars - 1
	PrintTable: displays table with following information
		>index
		>char
		>weight
		>parents
		>child type

EXAMPLE: 	MERCER SOCCER

To encode, build a Huffman Tree, here is an example:  
T7  
/ \  
T5 T6  
/ \ / \  
E R T3 T4  
_____/ \_ / \  
____S T1 T2 C  
____/ \ / \  
___nl sp M O  
Notice: 
	the smallest frequency characters are at the bottom
	all internal nodes are non-characters: only fillers
	the parents node has weight = sum of child weights

For each character, going to the right = 1, left = 0.
Using a recursive function, an output string can be read to the
output file compressed line to give an encoded result.
example: MERCER SOCCER = 1100000111100011011100110111111100011010
Notice:
	Not every encoding algorithm will be the same, so the
	results won't be idential either.

The header line above will work like the previous example.
The number of unique characters in MERCER SOCCER = 8.
The encoded characters following are respectively:
10->1010->		nl ;  
32-> 1011->		sp;  
99-> 111->		C;  
101-> 00->		E;  
109-> 1100->	M;  
111-> 1101->	O;  
114-> 01->		R;  
115-> 100->		S;  
(The notation is ASCII value-> encoded value-> character.)
 
