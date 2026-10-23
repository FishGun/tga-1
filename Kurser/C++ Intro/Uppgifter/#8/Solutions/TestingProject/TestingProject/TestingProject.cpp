#include <iostream>
#include <Windows.h>

#include <Timer.h>

int main()
{
	CommonUtilities::Timer timer;
	std::cout << std::fixed << std::setprecision(7);
	while (true)
	{
		timer.Update();
		Sleep(100);

		std::cout << "DeltaTime: " << timer.GetDeltaTime() << "\t Total time: " << timer.GetTotalTime() << "\n";
	}
}