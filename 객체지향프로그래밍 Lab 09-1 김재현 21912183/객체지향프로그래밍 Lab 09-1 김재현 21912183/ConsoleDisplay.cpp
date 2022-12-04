#include "ConsoleDisplay.h"
HANDLE consoleHandler;
HANDLE initConsoleHandler()				// init Console Handler
{
	HANDLE stdCnslHndlr;
	stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE);		// STD_OUTPUT_HANDLE은 표준 출력장치 Handle
	consoleHandler = stdCnslHndlr;
	return consoleHandler;				// Return Handle
}

void cls(HANDLE hConsole)				// clear screen
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}
	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;
	// Scroll it upwards off the top of the buffer
	// with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);
	// Fill with empty spaces with the buffer’s
	// default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;
	/* ConsoleDisplay.cpp (3) */
	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);
	
	// Move the Cursor (0, 0)
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void closeConsoleHandler(HANDLE hndlr)	//Close Handle
{
	CloseHandle(hndlr);
}

int gotoxy(HANDLE consHndlr, int x, int y)
{
	if (consHndlr == INVALID_HANDLE_VALUE)
		return 0;
	COORD coords = { static_cast<short>(x), static_cast<short>(y) };	// Cursor Position
	SetConsoleCursorPosition(consHndlr, coords);						// Cursor Position Setting
}