#include"etools.h"

void etools::log_add(std::string _s)
{
	std::ofstream file_out;
	
	if(_s.back() != '\n') {_s = _s + "\n";}
	
	file_out.open("debug.log", std::ios::out | std::ios::app | std::ios::binary);
	file_out << _s;
	file_out.close();
}

void etools::log_new_session()
{
	std::ofstream file_out;
	
	file_out.open("debug.log", std::ios::out | std::ios::app | std::ios::binary);
	file_out << "\n[NEW SESSION]\n";
	file_out.close();
}