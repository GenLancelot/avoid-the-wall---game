#pragma once

#include <vector>

using namespace std;

class Player {

public:
	Player();
	void setBullets();
	void changePlayerPosY(bool up);
	int getPlayerPosX();
	int getPlayerPosY();
	int getBulletsCount();
	void takeBullet();
	bool canShoot();
	void shooting();
	void moving();
private:
	int nPositionX;
	int nPositionY;
	int nBullets;
};

class Walls {

public:
	Walls();
	int getPositionX();
	int getHolePosition(int i);
	int getHoleSize();
	int getHoleCount();
	void newHole(int nPos);
	void moving();
private:
	int nPositionX;
	int nHoleCount;
	vector<int> nHolePosition;
	int nHoleSize;
};

class Opponents {

public:
	Opponents(bool bCan);
	int getPositionX();
	int getPositionY();
	bool getCanShoot();
	void moving();
private:
	int nPositionX;
	int nPositionY;
	bool bCanShoot;
};

class Bullets {
public:
	Bullets();
	int getPositionX();
	int getPositionY();
	bool getTaken();
	void moving();

private:
	int nPositionX;
	int nPositionY;
	bool bTaken;
};

class Shoots {
public:

	Shoots(int nPosX, int nPosY);
	int getPositionX();
	int getPositionY();
	bool getHit();
	void moving();

private:

	int nPositionX;
	int nPositionY;
	bool bHit;
};

class OpponentsShoots {

public:

	OpponentsShoots(int nPosX, int nPosY);
	int getPositionX();
	int getPositionY();
	bool getHit();
	void moving();

private:

	int nPositionX;
	int nPositionY;
	bool bHit;
};