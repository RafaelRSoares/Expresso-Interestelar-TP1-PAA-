build:	main.c mapa.c nave.c lista.c backtracking.c gerarMapa.c
	gcc main.c mapa.c nave.c lista.c backtracking.c gerarMapa.c -o Endurance

analise: main.c mapa.c nave.c lista.c backtracking.c gerarMapa.c
	gcc main.c mapa.c nave.c lista.c backtracking.c gerarMapa.c -o Endurance -DANALISE

interface: UI.c mapa.c nave.c lista.c backtracking.c gerarMapa.c
	gcc UI.c mapa.c nave.c lista.c backtracking.c gerarMapa.c -o Endurance `pkg-config --cflags --libs gtk+-3.0`

interface-WIN: UI.c mapa.c nave.c lista.c backtracking.c gerarMapa.c
	gcc UI.c mapa.c nave.c lista.c backtracking.c gerarMapa.c -o Endurance.exe `pkg-config --cflags --libs gtk+-3.0` && ./Endurance.exe

run:
	./Endurance

