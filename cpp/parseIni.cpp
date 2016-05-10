#include "lift.h"
#include <fstream>
#include <map>

using namespace std;

bool Lift::parseIni(map<string, IniField>& paras)
{
	ifstream file(INI_FILE_PATH);
	if (!file.is_open())
	{
		return false;
	}

	string paraName, tmp;
	while (file >> paraName)
	{
		IniField para = paras.find(paraName)->second;
		if (paraName.compare(para.name) != 0)
			return false;
		switch (para.type)
		{
			case INT:
				file >> tmp;	// skip =
				file >> *((int*)para.addr);
				break;
			case STRING:
				break;
				// not implement
		}
	}
	if (!file.eof())
		return false;

	return true;
}
