#include"Main_ALG.h"
vuint8 ret;
int main()
{
	// Initialize the application
	ret = App_Initialization();
	
	// Continuous monitoring loop
	while (1)
	{
		ret = Start_App();
	}

	// The program should never reach this point
	return 0;
}