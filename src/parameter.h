#ifndef _PARAMETER_H
#define _PARAMETER_H

#include <iostream>
#include <fstream>
#include <string>

#include "types.h"


namespace _param
{
	static DWORD index = 0;
}

struct Parameter
{
	Parameter(DWORD newId,	DWORD newDeviceId,	std::string newName) : id(newId), deviceId(newDeviceId), name(newName)
	{
	}

	Parameter(DWORD device) : id(_param::index), deviceId(device), name("Parameter" + std::to_string(id))
	{
		_param::index++;
	}
	DWORD id;
	DWORD deviceId;
	std::string name;
};

Parameter getEmptyParameter()
{
	return Parameter(0, 0, "");
}

std::ostream& operator<<(std::ostream& os, const Parameter& param)
{
	os << "Id: " << param.id << " Device id: "<< param.deviceId << " Name: " << param.name;
	return os;
}

std::ofstream& operator<<(std::ofstream& fs, const Parameter& param)
{
	fs.write((const char*)&param.id, sizeof(param.id));
	fs.write((const char*)&param.deviceId, sizeof(param.deviceId));

	fs.write((const char*)param.name.c_str(), param.name.size());
	BYTE null = '\0';
	fs.write((const char*)&null, 1);

	return fs;
}

std::ifstream& operator>>(std::ifstream& fs, Parameter& param)
{
	BYTE symbol = 1;

	fs.read((char*)&param.id, sizeof(param.id));
	fs.read((char*)&param.deviceId, sizeof(param.deviceId));

	param.name.clear();
	while (symbol != '\0')
	{
		fs.read((char*)&symbol, sizeof(symbol));
		param.name += symbol;
	}

	return fs;
}

#endif
