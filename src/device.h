#ifndef _DEVICE_H
#define _DEVICE_H

#include <iostream>
#include <fstream>
#include <string>

#include "types.h"

namespace _device
{
	static DWORD index = 0;
}

struct Device
{
	Device() : id(_device::index), name("Device" + std::to_string(id)), port(8000)
	{
		_device::index++;
	}
	Device(DWORD newId, std::string newName, WORD newPort) : id(newId), name(newName), port(newPort)
	{
	}

	DWORD id;
	std::string name;
	WORD port;
};

Device getEmptyDevice()
{
	return Device(0, "", 0);
}

std::ostream& operator<<(std::ostream& os, const Device& dev)
{
	os << "Id: " << dev.id << " Name: " << dev.name << " Port: " << dev.port;
	return os;
}

std::ofstream& operator<<(std::ofstream& fs, const Device& dev)
{
	fs.write((const char*)&dev.id, sizeof(dev.id));

	fs.write((const char*)dev.name.c_str(), dev.name.size());
	BYTE null = '\0';
	fs.write((const char*)&null, 1);
	fs.write((const char*)&dev.port, sizeof(dev.port));

	return fs;
}

std::ifstream& operator>>(std::ifstream& fs, Device& dev)
{
	BYTE symbol = 1;

	fs.read((char*)&dev.id, sizeof(dev.id));

	dev.name.clear();
	while (symbol != '\0')
	{
		fs.read((char*)&symbol, sizeof(symbol));
		dev.name += symbol;
	}
	fs.read((char*)&dev.port, sizeof(dev.port));

	return fs;
}

#endif

