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

#include "libtictactoe.h"

int
main (int argc, char **argv) {
	char state[] = "X123456789";
	gameloop(state);
}
