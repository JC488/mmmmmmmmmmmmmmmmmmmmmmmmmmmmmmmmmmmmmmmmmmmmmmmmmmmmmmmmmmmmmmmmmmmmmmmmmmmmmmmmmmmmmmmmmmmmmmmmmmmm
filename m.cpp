/* gcc: g++ m.cpp -o mcxx
   msvc: use vs, or
   cl m.cpp /Fo.\mcxx.exe
*/

#include <iostream>

#ifdef _MSC_VER
	// Platform SDK uses _ for posix "compat"
	#define getch() _getch()
#endif

#ifdef __linux__
#include <termios.h>
#include <unistd.h>

int getch() {
	struct termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	int ch = getchar();
	// restore terminal settings
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}
#endif

void _pause(){
	// while this will be optimized away
	std::cout << "Press any key to continue...";
	getch();
	std::cout << std::endl;
}

int main(){
	std::cout << "m\n";
	_pause();
	return 0;
}
