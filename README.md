# cisc220proj3
TL;DR: find scrabble words given a specified rack

For this project you're going to design code to give the highest scoring plays given a particular rack, board, and dictionary.

Your goal: produce a list of the top 20 highest scoring plays for that player (perhaps with x,y coordinates and a direction (right or down)). 
Think deep about (or research obscure…) data structures that can help you do this in close to real time. You will receive the rack and board 
in a format I chose for this project. I will give you a dictionary to use. Also I will provide you a Python script and some instructions for 
creating this board format from a real, live, game of Scrabble from facebook (YMMV).

Output format:
The first row will contain the tiles from your rack. (* for wild-card.)
The board is 15x15 and it is on the next 15 rows which contain 15 characters each.
A - is an empty space.
A capital letter is a tile which has been played.
A 2 is a double letter tile.
A 3 is a triple letter tile.
A 4 is a double word tile.
A 9 is a triple word tile.

Sample:

RIFOXOL
9--2---9---2-NO
-4---3---3JOLE-
--4---2-2---I--
2--4---2--MUD-2
----4----MA----
-3---3-GROWTHS-
--2-G-DIED--2U-
9--CAVES---2-QI
--2-ZA2-2---T-N
-3--EN---3-BULK
-T--R-----TAR--
2HUES--2--EYNE2
WAP---2-2---I--
IT---3---3--P4-
G--2---9---2SIB

Flowbart:
http://imgur.com/gallery/YnZXqob

Roadmap and TODO:

1. check and fix board[][] in main, scoreplay and scoreword

2. Import or create board (readboard)

3. Initialize dictionary (trie)
   
    a. fix map type issue in trie

    b. fix insert issue in trie

    c. sort into pre and post-fixes

4. Find anchor positions (anchorfinder)
    
    a. move isBlank to its own file

5. Create list of legal words (Words?). Legal words must:

    a. use letters on the board or the middle square

    b. use letters on the rack

    c. fit on the board

    d. make words in the dictionary in all directions

6. Trim list to top 20 scorers (scoreplay, scoreword, weight)

7. debug & test & repeat

8. Remove space from showboard
