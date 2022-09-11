#include "Declaration.h"
#include "Definition.h"

int main()
{
	Setup();

	Loop();

	setCursorCoord(0, g_fieldHeight + 3);
	
	cout << "Total Score: " << g_TotalScore << endl;

	cleanUp();

	return 0;
}