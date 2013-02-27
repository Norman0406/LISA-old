#include "System.h"

using namespace lisa;

int main(int argc, char *argv[])
{
	// create a system instance
	System* sys = System::init(argc, argv);
	
	// process application
	int retVal = sys->run();

	delete sys;
	return retVal;
}
