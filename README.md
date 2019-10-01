# Huffman-Coding

While generating Huffman Tree, I got help from unordered linked list type, also I created my own HuffmanNode type. I added  nodeType that is used for linked list type frequency variable. In HuffmanNode type there are info, frequency, left and right variables.
I used unordered linked list type to read from file and then store the frequency of each character read which is 1 for initial. 
I used bitset type in order to present character in ascii codes then I converted bitset to string and opened and wrote to new file.
Later I created another unordered linked list and stored characters in it according to their overall frequencies. List is formed in such an order whick starts from highest frequency and ends with lowest one. 
Then by using this frequency list I applied Huffman algorithm which selects the two characters with lowest frequencies which are children. And parent of these children has the frequency which is the sum of its children’s frequencies. And then parent is positioned to the list according to its frequency.
If the parents frequency is not added to the end of the array which it will be considered, it will be added to the correct position and the element which was in its place and the elements after it will be shifted by one.
Later, to generate Huffman code of character to be serached I assigned 0 to every path taken to left and 1 to each path taken to right. And function repeats itself until it reaches the desired character.
A new file is opened and each characters generated Huffman code is written to file.
