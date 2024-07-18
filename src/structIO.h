#ifndef STRUCTIO_H_
#define STRUCTIO_H_

#include <fstream>
#include <string>
#include <list>

#include "device.h"
#include "parameter.h"

class StructIO
{
	public:
		StructIO(std::string fileName)
		{
			this->fileName = fileName;
			std::ofstream out(fileName, std::ios::out); // to create a new file if none is present
			out.close();
		}

		void save(const std::list<Device>& devices, const std::list<Parameter>& params)
		{
			std::cout << "\nSaving in the file: " << fileName << std::endl;

			std::ofstream out(fileName, std::ios::binary);
			if (!out)
			{
				std::cout << "Can't open the file to write!\n";
				return;
			}

			out.write((char*)(&version), sizeof(version));

			int32_t devicesCount = devices.size();
			out.write((char*)(&devicesCount), sizeof(devicesCount));

			for (const auto& d : devices)
			{
				out << d;
			}

			int32_t parametersCount = params.size();
			out.write((char*)(&parametersCount), sizeof(parametersCount));

			for (const auto& p : params)
			{
				out << p;
			}
		}

		void load(std::list<Device>& devices, std::list<Parameter>& params)
		{
			std::ifstream in(fileName, std::ios::binary);
			if (!in)
			{
				std::cout << "Can't open the file to read!\n";
				return;
			}

			in.read((char*)&version , sizeof(version));

			int32_t devicesCount;
			in.read((char*)&devicesCount , sizeof(devicesCount));

			devices.clear();
			for (int i = 0; i < devicesCount; i++)
			{
				Device d = getEmptyDevice();
				in >> d;
				devices.push_back(d);
			}

			int32_t parametersCount;
			in.read((char*)&parametersCount , sizeof(parametersCount));

			params.clear();
			for (int i = 0; i < parametersCount; i++)
			{
				Parameter p = getEmptyParameter();
				in >> p;
				params.push_back(p);
			}
		}

		void setVersion(int32_t v)
		{
			version = v;
		}

		int32_t getVersion() const
		{
			return version;
		}

	private:
		std::string fileName;
		int32_t version = 0;
};

#endif
