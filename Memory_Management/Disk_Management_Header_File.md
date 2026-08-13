Well the header file that i have created is simple and the steps are ,
1:- 
pick the size of what size do we need to bring in memory , 
and yes industry standard is 4KB and 8KB so we picked 4KB
which is defined in:-  int Blocksize = 4096

2:- 
then we need disk management class :-
what does it do? :->
It allocates the size that we discussed , HOW?
it comtains 4 things namely:-
2A:- char RawSize whihc is given block size it is the main block
2B:- We have Interference_Thread thing here which shows how many currently are interacting either read or write
2C:- Then we have Block ID which is the representation of the allocated block from which our page is being bought
2D:- Last one is boolean where we would be doing simple thing whihc is :- "IS THE CHANGES THAT WE HAVE MADE IN MEMORY HAS BEEN SAVED?"

then there is just getter and setter 

so overall it is just a simple thing
That we are just making protocols so that when applied it would follow it 