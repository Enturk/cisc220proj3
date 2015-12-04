all: main.o trie.o showboard.o readboard.o scoreword.o scoreplay.o words.o weight.o anchorfinder.o -o scrabble
	g++ main.o trie.o showboard.o readboard.o scoreboard.o scoreword.o scoreplay.o words.o weight.o anchorfinder.o -o scrabble

main.o: main.cpp
	g++ -c main.cpp

trie.o: trie.cpp
	g++ -c trie.cpp trie.h

showboard.o: showboard.cpp
	g++ -c showboard.cpp showboard.h

readboard.o: readboard.cpp
	g++ -c readboard.cpp readboard.h

scoreboard.o: scoreboard.cpp
	g++ -c scoreboard.cpp scoreboard.h

scoreword.o: scoreword.cpp
	g++ -c scoreword.cpp scoreword.h
	
scoreplay.o: scoreplay.cpp
	g++ -c scoreplay.cpp scoreplay.h
	
words.o: words.cpp
	g++ -c words.cpp words.h
	
weight.o: weight.cpp
	g++ -c weight.cpp weight.h

anchorfinder.o: anchorfinder.cpp
	g++ -c anchorfinder.cpp anchorfinder.h
	
# this target will remove the extra make files
clean:
	rm -rf *o *.h.gch scrabble