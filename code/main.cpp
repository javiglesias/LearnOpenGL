#include "App.h"
#include <wtypes.h>
#include <fstream>

// Dedicated GPU for laptops with 2 https://stackoverflow.com/questions/16823372/forcing-machine-to-use-dedicated-graphics-card
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main(int args, char** argv)
{
	std::string hero_name;
	std::ifstream introduction;
	introduction.open("resources\\introduction.txt", std::ios_base::in);
	if (introduction.is_open())
	{
		std::string line_readed = "";
		while(std::getline(introduction, line_readed))
		{
			
			std::cout << line_readed << '\n';
		}
		introduction.close();
		//fprintf(stdout, "Escribe el nombre de tu HEROE para continuar: ");
		//std::cin >> hero_name;
		App* app = new App("");
		return app->run();
	}
	return 0;
}