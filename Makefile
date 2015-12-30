all: clean main.o menu.o window.o textbox.o text.o net.o
	clang++ net.o text.o textbox.o main.o menu.o window.o -lSDL2 -lSDL2_ttf -lSDL2_net -g -std=c++11

clean:
	rm -rf *.o a.out

main.o:
	clang++ -c main.cpp -g -std=c++11

menu.o:
	clang++ -c menu.cpp -g -std=c++11

window.o:
	clang++ -c window.cpp -g -std=c++11

textbox.o:
	clang++ -c textbox.cpp -g -std=c++11

text.o:
	clang++ -c text.cpp -g -std=c++11

net.o:
	clang++ -c net.cpp -g -std=c++11
