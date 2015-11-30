all: main.o trie.o
	g++ main.o trie.o showboard.o readboard.o scoreword.o scoreplay.o weight.o -o scrabble

main.o: main.cpp
	g++ main.cpp
	
trie.o: trie.cpp
	g++ trie.cpp trie.h
	
showboard.o: showboard.cpp
	g++ showboard.cpp showboard.h
	
readboard.o: readboard.cpp
	g++ readboard.cpp readboard.h
	
scoreword.o: scoreboard.cpp
	g++ scoreboard.cpp scoreword.h
	
scoreplay.o: scoreplay.cpp
	g++ scoreplay.cpp scoreplay.h
	
weight.o: weight.cpp
	g++ weight.cpp weight.h
	
# this target will remove the extra make files
clean:
	rm -rf *o scrabble