/* gcc: gcc m.c -o m
   msvc: use vs, or
   cl m.c /Fo.\m.exe
*/

#include <stdio.h>

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
	printf("Press any key to continue...");
	getch();
	puts("");
}

int main(){
	puts("m");
	_pause();
	return 0;
}
