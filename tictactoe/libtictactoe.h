#define EXIT_DRAW 2
#define EXIT_QUIT 3

#define tictactoe()                                     \
	do {                                            \
		char _TIC_STATE[] = "X123456789";       \
		gameloop(_TIC_STATE);                   \
	} while (0)
void gameloop(char[10]);

