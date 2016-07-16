#ifndef H_ETOOLS
#define H_ETOOLS

// This is a header file to contain many tools and types used in project VOTSOD

#include<fstream>
#include<string>

void log_add(std::string _s);
void log_new_session();

//TODO add the printinmiddle function

class Coord2 {
public:
	Coord2(const unsigned& _y, const unsigned& _x):y(_y), x(_x){};
	~Coord2(){};
	
	unsigned int y, x;
};

namespace etools {
	void log_new_session();
	void log_add(std::string _s);
}
#endif //H_ETOOLS