#include <GLFW\glfw3.h>
#include <iostream>

int main()
{
	if (!glfwInit())
	{
		std::cout << "Error!" << std::endl;
	}
	else
	{
		std::cout << "Success!" << std::endl;
	}
	std::cin.get();
	return 0;
}
