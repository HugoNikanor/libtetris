// for direct input
// termios, TCSANOW, ECHO, ICANON
#include <termios.h>
#include <unistd.h>

// for non blocking input
#include <fcntl.h>

#include "game.h"

int main() {

	// makes IO non-blocking
	fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

	// makes io don't wait for enter
	static struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	//

	game_loop();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
