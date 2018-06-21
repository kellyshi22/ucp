# ucp
### unix and c programming assignment (comp1000)  

Files submitted:
SpellChecker.c, SpellChecker.h 
Contains main. All files are opened and closed, and all memory is allocated and freed here. 

processarray.c, processarray.h
Contains functions used to create, insert into and free the array. It also has two functions of type ActionFunc, to be used in check(). 

linkedlist.c, linkedlist.h 
Contains linked list operations for a generic list. Files were previously submitted for practical 6 but have been modified since submission.

fileio.c, fileio.h
Contains all functions related to the reading and writing of files. Has a method to process the settings file, storing the settings in a struct. It also reads the user file and dictionary file, storing each in a linked list, and writes the user array back to the user file. 


All functionality as described in the specification should be working and there are no known bugs or memory leaks.


The program was tested on 314.219 0013454
