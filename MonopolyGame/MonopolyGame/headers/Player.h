
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
class Tile;
class Player{
public :
	Player(std::vector<Tile*>& tiles,std::string name );
	~Player();
	void move();
	int recieveMoney(int = 0);
	int  payMoney(int = 0);
	std::string& getName();
private:
	int id;
	int totalMoney;
	static int counter;
	std::string name;
	std::vector<Tile*>& tiles;
};
#endif //!PLAYER_H
