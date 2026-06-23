#include <cstdio>
#include "unistd.h"

class MainProgram
{
	public:
		void Main_Program()
		{
			printf("Hello World！！！\n");
		}
};

int main()
{
	MainProgram prog;
	prog.Main_Program();
	return 0;
}
