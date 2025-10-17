build:	main.c mapa.c nave.c lista.c backtracking.c gerarMapa.c
	gcc main.c mapa.c nave.c lista.c backtracking.c gerarMapa.c -o Endurance && .\Endurance

analise: main.c mapa.c nave.c lista.c backtracking.c gerarMapa.c
	gcc main.c mapa.c nave.c lista.c backtracking.c gerarMapa.c -o Endurance -DANALISE && .\Endurance

interface: UI.c mapa.c nave.c lista.c backtracking.c gerarMapa.c
	gcc UI.c mapa.c nave.c lista.c backtracking.c gerarMapa.c -o Endurance `pkg-config --cflags --libs gtk+-3.0`

