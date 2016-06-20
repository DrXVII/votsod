#ifndef H_ETOOLS
#define H_ETOOLS

// This is a header file to contain many tools and types used in project VOTSOD

//TODO add the printinmiddle function

class Coord2 {
public:
	Coord2(const unsigned& _y, const unsigned& _x):y(_y), x(_x){};
	~Coord2(){};
	
	unsigned int y, x;
};

#endif //H_ETOOLS