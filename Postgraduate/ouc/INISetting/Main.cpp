/* 2017.3.25 21:17
	≈‰÷√Œƒº˛∂¡–¥
*/
#include <iostream>
#include "INIReader.h"
#include "INIWriter.h"
//using namespace std;

int main(void)
{
	INIWriter iniWriter(".\\setting.ini");
	iniWriter.WriteString("Info", "Name", "Jack");
	iniWriter.WriteInteger("Info", "Age", 24);
	iniWriter.WriteFloat("Info", "Height", 1.75f);
	iniWriter.WriteBoolean("Info", "Marriage", false);

	INIReader iniReader(".\\setting.ini");
	char* name = iniReader.ReadSring("Info", "Name", "");
	int age = iniReader.ReadInteger("Info", "Age", 0);
	float height = iniReader.ReadFloat("Info", "Height", 1.0f);
	bool marriage = iniReader.ReadBoolean("Info", "Marriage", true);

	std::cout << "name = " << name << "\nage = " << age
		      << "\nheight = " << height<< "\nmarriage = "  << (marriage?"True":"False") << std::endl;
	delete name;
	return 1;
}