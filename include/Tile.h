#ifndef TILE_H
#define TILE_H


class Tile{
public:
	Tile();
	virtual ~Tile();

	char get_icon();
	void set_icon(char _icon);
	bool get_ispassable();
	void set_ispassable(bool _b);
private:
	char m_icon;
	bool m_ispassable;
};

#endif // TILE_H
