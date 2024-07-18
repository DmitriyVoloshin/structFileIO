#include <iostream>
#include <list>
#include <random>

#include "structIO.h"

int main(int argc, char** argv)
{
	std::list<Device> devices;
	std::list<Parameter> parameters;

	if (argc < 3)
	{
		std::cout << "Invalid parameters.\n";
		std::cout << "Example run \"./structIO 10 5\" Where:\n";
		std::cout << "10 - devices count.\n";
		std::cout << "5 - parameters count.\n";
		return 0;
	}


	int requiredDevices = std::stoi(argv[1]);
	std::cout << "Entered devices - " << requiredDevices << ":\n";
	for (int i = 0; i < requiredDevices; i++)
	{
		devices.push_back(Device());
		std::cout << devices.back() << std::endl;
	}

	int requiredParameters = std::stoi(argv[2]);
	std::cout << "\nEntered parameters - " << requiredParameters << ":\n";
	for (int i = 0; i < requiredParameters; i++)
	{
		int device = rand() % devices.size();
		parameters.push_back(Parameter(device));
		std::cout << parameters.back() << std::endl;
	}

	StructIO structIO("demo");
	structIO.setVersion(101);
	structIO.save(devices , parameters);

	structIO.load(devices, parameters);

	std::cout << "Loaded file version: " << structIO.getVersion() << std::endl;

	std::cout << "\nDevices loaded - " << devices.size() << ":\n";
	for (const auto& d : devices)
	{
		std::cout << d << std::endl;
	}

	std::cout << "\nParameters loaded - " << parameters.size() <<":\n";
	for (const auto& p : parameters)
	{
		std::cout << p << std::endl;
	}

	return 0;
}


