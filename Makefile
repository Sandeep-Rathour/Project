#This File is not Necessary, I created this to Run Code more Easily
#You can also Run your Program by Command line
#Make Sure you Link and Compile you Code Correctly
all: link compile run

link: 
	g++ -c Main.cpp -I/home/documents/SFML.2.6.1/include/SFML

compile: 
	g++ Main.o -o Run -lsfml-system -lsfml-window -lsfml-graphics 

run:
	./Run

c: 
	rm Main.o Run -f