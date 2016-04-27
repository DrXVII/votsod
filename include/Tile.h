#ifndef TILE_H
#define TILE_H


class Tile
{
	public:
		Tile();
		virtual ~Tile();

		char get_icon();
		void SetIcon(char _icon);
		bool GetPassable();
		void SetPassable(bool _b);
	protected:
	private:
		char Icon;
		bool Passable;
};

#endif // TILE_H
