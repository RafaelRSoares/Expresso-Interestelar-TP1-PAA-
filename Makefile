build:	main.c mapa.c nave.c lista.c backtracking.c
	gcc main.c mapa.c nave.c lista.c backtracking.c -o Endurance && .\Endurance

analise: main.c mapa.c nave.c lista.c backtracking.c
	gcc main.c mapa.c nave.c lista.c backtracking.c -o Endurance -DANALISE && .\Endurance