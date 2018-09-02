/* * * * * * * * * *\
*                   *
* TTTTT| III |CCCCC *
* T T T|  I  |C   C * 
*   T  |  I  |C     *
*   T  |  I  |C   C *
*   T  | III |CCCCC *
* -----/-----\----- *
* TTTTT|  A  |CCCCC *
* T T T| A A |C   C *
*   T  |A   A|C     *
*   T  |AAAAA|C   C *
*   T  |A   A|CCCCC *
* -----\-----/----- *
* TTTTT| OOO |EEEEE *
* T T T|OO OO|E     *
*   T  |O   O|EEEE  *
*   T  |OO OO|E     *
*   T  | OOO |EEEEE *
*                   *
*    tic-tac-toe    *
*   by  kjensenxz   *
\* * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EXIT_DRAW 2
#define EXIT_QUIT 3

void showboard (int, char[10]);
int checkwin (char[10]);

void gameloop (char[10]);
void exitgame (int, char[10]);

int
main (int argc, char **argv) {
	char state[] = "X123456789";
	gameloop(state);
}

void
gameloop(char state[10]) {
	char *player = &state[0];
	char *input = malloc(10);
	int cell, rv;

	showboard(0, state);
	printf("It's %c's turn!\n> ", *player);
	scanf("%s", input);
	printf("\n");
	
	if (strlen(input) == 1 && input[0] >= '1' && input[0] <= '9') {
		cell = input[0] - '0';
		if (state[cell] == cell + '0') {
			state[cell] = *player;
			
			rv = checkwin(state);
			if (rv != EXIT_FAILURE) {
				exitgame(rv, state);
			}
			
			*player = (*player == 'X') ? 'O': 'X';
		}

		else {
			printf("\nInvalid move, %c is already there!\n", 
			       state[cell]);
		}
	}

	else switch(input[0]) {
		case 'h': case 'H': case '?':
			printf("h[elp]: Enter the corresponding cell"
			       " number to place your letter\n"
			       "q[uit]: quit\n");
			break;
		
		case 'q': case 'Q': case '\0':
			exitgame(EXIT_QUIT, state);
		
		default:
			printf("\nInvalid move \"%s\"!\n", input);
			break;
	}

	gameloop(state);
}
 /************************\
 * game  state  explained *
 * ---------------------- *
 *                        *
 * the game state is kept *
 * within a flat char[10] *
 * to represent the cells *
 * and the current player *
 * designed to have a 1:1 *
 * map of cells:indices.  *
 *                        *
 *   0: 'X' or 'O'        *
 * 1-9: by default, the # *
 *      of the cell, 'X', *
 *      or 'O'.           *
 *                        *
 * state[0]  is the  cur- *
 * rent  player.   when a *
 * move is made, state[0] *
 * is   changed  to   the *
 * other player. state[1] *
 * through  state[9]   is *
 * changed when  a player *
 * makes a move, changing *
 * the cell number to the *
 * corresponding  letter. *
 *                        *
 * e.g. "X 123456789":    *
 *       ^ ^^^^^^^^^      *
 * +-----/ \\\\\\\\\----+ *
 * |                    | *
 * it's X's turn        | *
 *      no moves made yet *
 *                        *
 * (prompt)               *
 * > 1                    *
 *                        *
 * X places his letter on *
 * cell 1, the next state *
 * will be  "XX23456789". *
 *                        *
 * every time  a move is  *
 * made, the new state is * 
 * checked in checkwin(), *
 * which returns a  value *
 * corresponding  to  the *
 * winning   cells  (e.g. *
 * 147,  789,  456).      *
 *                        *
 * if there  is  a  win,  *
 * the program terminates *
 * otherwise  the  player *
 * (state[0]) is swapped, *
 * (now,    "OX23456789") *
 * and the next move will *
 * be made with letter O, *
 * and the above will  be *
 * repeated  until  there *
 * is a win or a draw.    *
 *                        *
 * a winning state may be *
 *      X XOX OXO XXO     *
 *      0 123 456 789     *
 *          X O X         *
 *          O X O         *
 *          X X O         *
 *                        *
 * indicating that  X won *
 * with cells 357, a '/'. *
 *                        *
 \************************/

void exitgame(int value, char state[10]) {
	switch (value) {
		case EXIT_QUIT:
			printf("%c is a quitter!\n", state[0]);
			break;

		case EXIT_DRAW:
			showboard(value, state);
			printf("Draw!\n");
			break;
		default:
			showboard(value, state);
			printf("%c wins!\n", state[0]);
			break;
	}

	exit(EXIT_SUCCESS);
}

int
checkwin (char state[10]) {
	char who = state[0];
	int i;

	// 1 2 3
	// 4 5 6
	// 7 8 9

	/* Check horizontals
	 * 1 2 3, 4 5 6, 7 8 9
	 */
	for (i = 1; i <= 7; i += 3) {
		if (state[i]   == who &&
		    state[i+1] == who &&
		    state[i+2] == who)
			return i*100 + (i+1)*10 + (i+2);
	}

	/* Check verticals
	 * 1 4 7, 2 5 8, 3 6 9
	 */
	for (i = 1; i <= 3; ++i) {
		if (state[i]   == who &&
		    state[i+3] == who &&
		    state[i+6] == who)
			return i*100 + (i+3)*10 + (i+6);
	}

	/* Check both diagonals
	 * 1 5 9, 3 5 7
	 */
	if (state[5] == who) {
		if (state[1] == who && state[9] == who) {
			return 159;
		}
		if (state[3] == who && state[7] == who) {
			return 357;
		}
	}

	/* Check for a draw */
	if (state[1] != '1' && state[2] != '2' && state[3] != '3' &&
	    state[4] != '4' && state[5] != '5' && state[6] != '6' &&
	    state[7] != '7' && state[8] != '8' && state[9] != '9')
	    	return EXIT_DRAW;

	return EXIT_FAILURE;
}
 /*****************************\
 *   return values explained   *
 * +-------------------------+ *
 * | see gameloop() for info | *
 * |     on  game  state     | *
 * +-------------------------+ *
 *    cells in line =  XYZ     *
 *           cell 1 = X        *
 *           cell 2 = Y        *
 *           cell 3 = Z        *
 * cells are collated into re- *
 * turn values by lexiographic *
 * order  (e.g. 357, not 753); *
 * although, reading  left-to- *
 * right puts cell 7 ahead  of *
 * cell 3.                     *
 *                             *
 * the best way to concatenate *
 * decimal numbers  is just to *
 * multiply the ordered values *
 * by the corresponding  power *
 * of tens. for more informat- *
 * ion on this, read up on how *
 * number bases work.          *
 \*****************************/

void
showboard (int winval, char state[10]) {
	char style[16] = "        |||---++";
	if (winval != EXIT_FAILURE) {
		switch(winval) {
			case 123:
				style[0] = style[8] = '-';
				break;
			case 456:
				style[1] = style[9] = '-';
				break;
			case 789:
				style[2] = style[10] = '-';
				break;
			
			case 147:
				style[3] = style[11] = '|';
				break;
			case 258:
				style[4] = style[12] = '|';
				break;
			case 369:
				style[5] = style[13] = '|';
				break;

			case 159:
				style[6] = style[14] = '\\';
				break;
			case 357:
				style[7] = style[15] = '/';
				break;

			case EXIT_DRAW:
			case EXIT_QUIT:
			default:
				break;
		}
	}

	printf("%c%c | %c | %c%c\n"
	       "%c%c%c%c%c%c%c%c%c%c%c\n"
	       " %c%c| %c |%c%c\n"
	       "-%c-%c-%c-%c-%c-\n"
	       " %c |%c%c%c| %c\n"
	       "%c%c%c%c%c%c%c%c%c%c%c\n"
	       " %c |%c%c%c| %c\n"
	       "-%c-%c-%c-%c-%c-\n"
	       " %c%c| %c |%c%c\n"
	       "%c%c%c%c%c%c%c%c%c%c%c\n"
	       "%c%c | %c | %c%c\n",
	       /*        COL 1               BAR                COL 2               BAR                COL 3          */
	       style[6],style[3],                              style[4],                              style[5],style[7],
	       style[0],state[1],style[0], style[8],  style[0],state[2],style[0], style[8],  style[0],state[3],style[0],
	                style[3],style[6],                     style[4],                              style[7],style[5],
	                style[11],         style[14],          style[12],         style[15],          style[13],
	                style[3],                     style[6],style[4],style[7],                     style[5],
	       style[1],state[4],style[1], style[9],  style[1],state[5],style[1], style[9],  style[1],state[6],style[1],
	                style[3],                     style[7],style[4],style[6],                     style[5],
	                style[11],         style[15],          style[12],         style[14],          style[13],
	                style[3],style[7],                     style[4],                              style[6],style[5],
	       style[2],state[7],style[2], style[10], style[2],state[8],style[2], style[10], style[2],state[9],style[2],
	       style[7],style[3],                              style[4],                              style[5],style[6]);
}
 /*********************\
 *  style[] explained  *
 * +-----------------+ *
 * | see  checkwin() | *
 * |  for  info  on  | *
 * |  return values  | *
 * +-----------------+ *
 *     --- ||| \/      *
 *     ABC DEF GH      *
 *     012 345 67      *
 *                     *
 *     123 = A = 0     *
 *     456 = B = 1     *
 *     789 = C = 2     *
 *                     *
 *     147 = D = 3     *
 *     258 = E = 4     *
 *     369 = F = 5     *
 *                     *
 *     159 = G = 6     *
 *     357 = H = 7     *
 *                     *
 *    |||  ---  ++     *
 *    IJK  LMN  OP     *
 *    890  123  45     *
 *                     *
 *    123 = I = 8      *
 *    456 = J = 9      *
 *    789 = K = 10     *
 *                     *
 *    147 = L = 11     *
 *    258 = M = 12     *
 *    369 = N = 13     *
 *                     *
 *    159 = O = 14     *
 *    357 = P = 15     *
 *                     *
 *     GD | E | FH     *
 *     A1AIA2AIA3A     *
 *      DG| E |HF      *
 *     -L-O-M-P-N-     *
 *      D |GEH| F      *
 *     B4BJB5BJB6B     *
 *      D |HEG| F      *
 *     -L-P-M-O-N-     *
 *      DH| E |GF      *
 *     C7CKC8CKC9C     *
 *     HD | E | FG     *
 \*********************/
/* EOF */
