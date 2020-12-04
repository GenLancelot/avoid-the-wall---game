#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
#include <game.h>

using namespace std;

int nScreenWidth = 120;//colmums
int nScreenHeight = 40;//rows

int nMapWidth = 81;
int nMapHeight = 15;
unsigned char* pField = nullptr;

string sName;

bool bGameOver = false;
void input(int nPosY);

#pragma region Player_function_implemetation
Player::Player() {
	nPositionX = 26;
	nPositionY = 8;
	nBullets = 3;
}
void Player::setBullets() {
	nBullets = 3;
}
void Player::changePlayerPosY(bool up){
	if (up) nPositionY++;
	else nPositionY--;
}
int Player::getPlayerPosX(){
	return nPositionX;
}
int Player::getPlayerPosY(){
	return nPositionY;
}
int Player::getBulletsCount(){
	return nBullets;
}
void Player::takeBullet(){
	nBullets += 2;
}
bool Player::canShoot(){
	if (nBullets != 0)
		return true;
	return false;
}
void Player::shooting(){
	nBullets--;
}
void Player::moving(){
	input(nPositionY);
}
#pragma endregion

#pragma region Walls_function_implemetation
Walls::Walls() {
		nPositionX = nMapWidth - 1;
		nHoleSize = 1;
		nHoleCount = 1;
		nHolePosition.push_back(rand()%(nMapHeight - nHoleSize - 1) + 3);
}
int Walls::getPositionX(){
	return nPositionX;
}
int Walls::getHolePosition(int i){
	return nHolePosition[i];
}
int Walls::getHoleSize(){
	return nHoleSize;
}
int Walls::getHoleCount(){
	return nHoleCount;
}
void Walls::newHole(int nPos){
	nHoleCount++;
	nHolePosition.push_back(nPos);
}
void Walls::moving(){
	nPositionX--;
}
#pragma endregion

#pragma region Opponents_function_implemetation


Opponents::Opponents(bool bCan){
	nPositionX = nMapWidth - 1;
	nPositionY = rand() % (nMapHeight - 2) + 3;
	bCanShoot = bCan;
}
int Opponents::getPositionX(){
	return nPositionX;
}
int Opponents::getPositionY(){
	return nPositionY;
}
bool Opponents::getCanShoot(){
	return bCanShoot;
}
void Opponents::moving(){
	nPositionX--;
}
#pragma endregion

#pragma region Bullets_function_implemetation

Bullets::Bullets() {
	nPositionX = nMapWidth - 1;
	nPositionY = rand() % (nMapHeight - 2) + 3;
	bTaken = false;
}
int Bullets::getPositionX(){
	return nPositionX;
}
int Bullets::getPositionY(){
	return nPositionY;
}
bool Bullets::getTaken(){
	return bTaken;
}
void Bullets::moving(){
	nPositionX--;
	if (nPositionX < 3)
		bTaken = true;
}
#pragma endregion

#pragma region Shoots_function_implemetation
Shoots::Shoots(int nPosX, int nPosY) {
	nPositionX = nPosX + 1;
	nPositionY = nPosY;
	bHit = false;
}
int Shoots::getPositionX(){
	return nPositionX;
}
int Shoots::getPositionY(){
	return nPositionY;
}
bool Shoots::getHit(){
	return bHit;
}
void Shoots::moving(){
	nPositionX++;
	if (nPositionX > nMapWidth - 1)
		bHit = true;
}
#pragma endregion

#pragma region OpponentsShoots_function_implemetation
OpponentsShoots::OpponentsShoots(int nPosX, int nPosY) {
	nPositionX = nPosX + 1;
	nPositionY = nPosY;
	bHit = false;
}
int OpponentsShoots::getPositionX()
{
	return nPositionX;
}
int OpponentsShoots::getPositionY()
{
	return nPositionY;
}
bool OpponentsShoots::getHit()
{
	return bHit;
}
void OpponentsShoots::moving()
{
	nPositionX-=2;
	if (nPositionX < 3)
		bHit = true;
}
#pragma endregion

Player P1;//tworzenie gracza
vector<Shoots> shoots;

void input(int nPosY)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		{
			if (nPosY > 3) P1.changePlayerPosY(false);
			break;
		}
		case 's':
		{
			if (nPosY < nMapHeight) P1.changePlayerPosY(true);
			break;
		}

		case 72:
		{
			if (nPosY > 3) P1.changePlayerPosY(false);
			break;
		}

		case 80:
		{
			if (nPosY < nMapHeight) P1.changePlayerPosY(true);
			break;
		}
		case 32:
		{
			if (P1.canShoot())
			{
				P1.shooting();
				shoots.push_back(Shoots(P1.getPlayerPosX(), P1.getPlayerPosY()));
			}
		}
		}
		
	}
}

void leaderbord();
void game();
void settings();
void quit();

void start()
{
	system("cls");
	cout << string(52,'-') <<"MENU" << string(52, '-') << endl;
	cout << '|' << string(108, ' ') << '|' << endl;
	cout << '|' << string(51, ' ') << "1.PLAY" << string(51, ' ') << '|' << endl;
	cout << '|' << string(108, ' ') << '|' << endl;
	cout << '|' << string(48, ' ') << "2.LEADERBORD" << string(48, ' ') << '|' << endl;
	cout << '|' << string(108, ' ') << '|' << endl;
	cout << '|' << string(49, ' ') << "3.SETTINGS" << string(49, ' ') << '|' << endl;
	cout << '|' << string(108, ' ') << '|' << endl;
	cout << '|' << string(51, ' ') << "4.QUIT" << string(51, ' ') << '|' << endl;
	cout << '|' << string(108, ' ') << '|' << endl;
	cout <<  string(110, '-') << endl << endl;
	char i;
	cin >> i;
	switch (i)
	{
	case '1':
		cout << "Podaj imie:";
		cin >> sName;
		game();
		break;
	case '2':
		leaderbord();
		break;
	case '3':
		settings();
		break;
	case '4':
		quit();
		break;
	}
}

void leaderbord() {
	system("cls");
	fstream file;
	string sLine;
	cout << "                      LEADERBORD" << endl;
	file.open("leaderbord.txt", ios::in);
	int i = 1;
	while (!file.eof()){
		getline(file, sLine);
		cout << i << "." << sLine << endl;
		i++;
	}
	file.close();

	_getch();
	start();
}

bool sortByVal(const pair<string, int>& a,
	const pair<string, int>& b)
{
	return (a.second > b.second);
}

void leaderbordUpdate(string sName, int nScore, int nKills) {
	string sBlank;
	sBlank.assign(30, ' ');
	nScore += 3 * nKills;
	cout << endl << endl << endl << sBlank <<" G A M E    O V E R ! ! !" << endl << endl;
	cout << sBlank << " Your Score is: " << nScore;
	_getch();
	fstream file;
	vector<pair<string, int>> Scores;
	file.open("leaderbord.txt", ios::in);
	int nTemporaryScore;
	string sTemporaryName;
	while (!file.eof()){
		file >> sTemporaryName >> nTemporaryScore;
		Scores.push_back(make_pair(sTemporaryName, nTemporaryScore));
	}
	file.close();
	file.open("leaderbord.txt", ios::out);
	Scores.push_back(make_pair(sName, nScore));
	sort(Scores.begin(), Scores.end(), sortByVal);
	for (int i = 0; i < Scores.size()-1; i++)
		file << Scores[i].first << " " << Scores[i].second << endl;
	file << Scores[Scores.size() - 1].first << " " << Scores[Scores.size() - 1].second;
	file.close();
	start();
}

void settings()
{
	//colors are 0=black 1=blue 2=green and so on to 15=white  
	// colorattribute = foreground + background * 16
	//white/black,whie/brown,red/blue,blue/black,green/pink,white/blue,
	system("cls");
	cout << "Set colors:" << endl;
	cout << "white/black(15)                yellow/black(14)                red/blue(28)" << endl << "blue/black(9)                green/pink(82)                white/blue(23)";
	cout << endl;
	int i;
	cin >> i;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
	_getch();
	start();
}

void game() {
	system("cls");
	pField = new unsigned char[nMapWidth * nMapHeight];
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
			pField[y * nMapWidth + x] = (x == 0 || x == nMapWidth - 1 || y == nMapHeight - 1 || y == 0) ? 5 : 0; // ustawianie krancowych wartosci, tam gdzie 4 tam orbamowanie a tam gdzie 0 to pusta klatka
	//utworz buffer obrazu
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';//filling with blank spaces L na przodzei ponieważ wchar_t
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	vector<Walls> walls;
	walls.push_back(Walls());
	vector<Opponents> opponents;
	vector<Bullets> bullets;
	vector<OpponentsShoots> opponentsShoots;
	int nScore = 0;
	int nKills = 0;
	P1.setBullets();
	int nSpeed = 80;
	bGameOver = false;
	//gameloop

	while (!bGameOver) {

		//GAME SPEED 
		Sleep(nSpeed);
		if (nSpeed > 40)
			if (rand() % 100 < nScore && rand() % 100 < nScore)
				nSpeed--;

		//INPUT
		input(P1.getPlayerPosY());

		//collision detection with shots 

		//taking shoots by player
		for (int i = 0; i < opponentsShoots.size(); i++)
			if ((P1.getPlayerPosY() == opponentsShoots[i].getPositionY() && P1.getPlayerPosX() == opponentsShoots[i].getPositionX()) ||
				(screen[P1.getPlayerPosY() * nScreenWidth + P1.getPlayerPosX() + 1] == L'~' && P1.getPlayerPosX() + 1 == opponentsShoots[i].getPositionX()))
				bGameOver = true;


		//taking shoots by opponent
		for (int i = 0; i < opponents.size(); i++) {
			for (int m = 0; m < shoots.size(); m++) {
				if ((opponents[i].getPositionY() == shoots[m].getPositionY()) && (opponents[i].getPositionX() == shoots[m].getPositionX() || opponents[i].getPositionX() - 1 == shoots[m].getPositionX())) {
					opponents.erase(opponents.begin() + i);
					shoots.erase(shoots.begin() + m);
					nKills ++;
					break;
				}
			}
		}

		//taking shoots by walls from player shot

		for (int i = 0; i < walls.size(); i++) {
			vector<int> nHoles;
			for (int n = 0; n < walls[i].getHoleCount(); n++)
				nHoles.push_back(walls[i].getHolePosition(n));
			for (int m = 0; m < shoots.size(); m++) {
				bool bHit = true;
				if (walls[i].getPositionX() == shoots[m].getPositionX() || walls[i].getPositionX() - 1 == shoots[m].getPositionX()) {
					for (int j = 0; j < nHoles.size(); j++)
						if (nHoles[j] == shoots[m].getPositionY())
							bHit = false;
					if (bHit) {
						walls[i].newHole(shoots[m].getPositionY());
						shoots.erase(shoots.begin() + m);
					}
				}
			}
		}

		//taking shoots by walls from opponent shot

		if(!opponentsShoots.empty()){
			for (int i = 0; i < walls.size(); i++) {
				vector<int> nHoles;
				for (int n = 0; n < walls[i].getHoleCount(); n++)
					nHoles.push_back(walls[i].getHolePosition(n));
				for (int m = 0; m < opponentsShoots.size(); m++) {
					bool bHit = true;
					if (walls[i].getPositionX() == opponentsShoots[m].getPositionX() || walls[i].getPositionX() - 1 == opponentsShoots[m].getPositionX()) {
						for (int j = 0; j < nHoles.size(); j++)
							if (nHoles[j] == opponentsShoots[m].getPositionY())
								bHit = false;
						if (bHit) {
							walls[i].newHole(opponentsShoots[m].getPositionY());
							opponentsShoots.erase(opponentsShoots.begin() + m);
						}
					}
				}
			}
		}
		
		//shoots collision

		if (!opponentsShoots.empty() && !shoots.empty()) {
			for (int m = 0; m < opponentsShoots.size(); m++) {
				for(int i = 0; i < shoots.size(); i++)
					if (shoots[i].getPositionX() == opponentsShoots[m].getPositionX() || shoots[i].getPositionX() - 1 == opponentsShoots[m].getPositionX()) {
						opponentsShoots.erase(opponentsShoots.begin() + m);
						shoots.erase(shoots.begin() + i);
					}
			}
		}

		//taking bullets
		for (int i = 0; i < bullets.size(); i++) {
			if ((P1.getPlayerPosY() == bullets[i].getPositionY()) && (P1.getPlayerPosX() == bullets[i].getPositionX())) {
				bullets.erase(bullets.begin() + i);
				P1.takeBullet();
			}
		}

		//collision detection 
		int nCount1 = 0;//liczy czy bylo zrobione przejscie
		int nCount2 = 0;//liczy czy byla kolizja
		for (int i = 0; i < walls.size(); i++) {
			for (int m = 0; m < walls[i].getHoleCount(); m++) {
				if ((walls[i].getPositionX() == P1.getPlayerPosX()) && (walls[i].getHolePosition(m) == P1.getPlayerPosY())) {
					nScore++;
					nCount1++;
				}
				else if (walls[i].getPositionX() == P1.getPlayerPosX())
					nCount2++;
			}

		}
		if (nCount1 == 0 && nCount2 != 0)
			bGameOver = true;
		for (int i = 0; i < opponents.size(); i++)
			if ((opponents[i].getPositionY() == P1.getPlayerPosY()) && (opponents[i].getPositionX() == P1.getPlayerPosX()))
				bGameOver = true;

		//spawning walls

		if (walls.size() < 3)
		{
			bool bNeedSpawnWall = false;
			for (int i = 0;i < walls.size();i++) {
				if (walls[i].getPositionX() == (nMapWidth/3) * 2) {
					bNeedSpawnWall = true;
					break;
				}
			}
			if (bNeedSpawnWall)
				walls.push_back(Walls());
		}

		//spawning opponents && bullets
		bool bWallsOnEnd = false;
		for (int i = 0; i < walls.size(); i++) {
			if (walls[i].getPositionX() == nMapWidth - 1) {
				bWallsOnEnd = true;
				break;
			}
		}
		if (!bWallsOnEnd)//wykluczenie pojawienia sie pocisku lub przeciwnika tam gdzie sciana
		{
			bool bSpawned = false;
			if (opponents.size() < 5) {
				bool bNeedSpawnOpponent = (rand() % 100) < nScore && (rand() % 100) < nScore;
				if (bNeedSpawnOpponent) {
					opponents.push_back(Opponents(rand() % 100 < nScore));
					bSpawned = true;
				}
			}
			if (bSpawned)
			{
				if (rand() % 1000 > 250  && bullets.empty()) {
					bullets.push_back(Bullets());
					if (opponents[opponents.size() - 1].getPositionY() == bullets[0].getPositionY())
						bullets.erase(bullets.begin(), bullets.end());//wykluczenie pojawienia sie pocisku tam gdzie przeciwnik 
				}

			}
			else
			{
				if (rand() % 1000 > 250 && bullets.empty())
					bullets.push_back(Bullets());
			}
		}


		//draw map
		for (int x = 0; x < nMapWidth; x++)
			for (int y = 0; y < nMapHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ><~|#:"[pField[y * nMapWidth + x]];

		//draw score,kills and bullets
		swprintf_s(&screen[2 * nScreenWidth + nMapWidth + 6], 16, L"Bullets: %d", P1.getBulletsCount());
		swprintf_s(&screen[3 * nScreenWidth + nMapWidth + 6], 16, L"Score: %d", nScore);
		swprintf_s(&screen[4 * nScreenWidth + nMapWidth + 6], 16, L"Kills: %d", nKills);

		//draw walls and moving
		for (int i = 0; i < walls.size(); i++) {
			for (int y = 3; y <= nMapHeight; y++)
				for (int m = 0; m < walls[i].getHoleCount(); m++) {
					screen[nScreenWidth * y + walls[i].getPositionX()] = (y != walls[i].getHolePosition(m)) ? L'|' : L' ';
					if (screen[nScreenWidth * y + walls[i].getPositionX()] == ' ')
						break;
				}

			walls[i].moving();
			if (walls[i].getPositionX() < 3) {
				walls.erase(walls.begin() + i);
				i--;
			}
		}

		//draw opponents 
		for (int i = 0; i < opponents.size(); i++) {
			screen[opponents[i].getPositionY() * nScreenWidth + opponents[i].getPositionX()] = L'<';
			opponents[i].moving();

		}

		//opponenets shooting
		if (!opponents.empty())
			for (int i = 0; i < opponents.size(); i++)
				if (opponents[i].getCanShoot())
					if (rand() % 100 < 5)
						opponentsShoots.push_back(OpponentsShoots(opponents[i].getPositionX() - 1, opponents[i].getPositionY()));



		//erase opponent
		for (int i = 0; i < opponents.size(); i++) {
			if (opponents[i].getPositionX() < 3)
				opponents.erase(opponents.begin() + i);
		}


		//draw bullets
		if (!bullets.empty()) {
			screen[bullets[0].getPositionY() * nScreenWidth + bullets[0].getPositionX()] = L':';
			bullets[0].moving();
			if (bullets[0].getTaken())
				bullets.erase(bullets.begin(), bullets.end());
		}

		//draw shoots
		if (!shoots.empty()) {
			for (int i = 0; i < shoots.size(); i++) {
				screen[shoots[i].getPositionY() * nScreenWidth + shoots[i].getPositionX()] = L'~';
				shoots[i].moving();
				if (shoots[i].getHit())
					shoots.erase(shoots.begin(), shoots.end());
			}

		}

		if (!opponentsShoots.empty()) {
			for (int i = 0; i < opponentsShoots.size(); i++) {
				screen[opponentsShoots[i].getPositionY() * nScreenWidth + opponentsShoots[i].getPositionX()] = L'~';
				opponentsShoots[i].moving();
				if (opponentsShoots[i].getHit())
					opponentsShoots.erase(opponentsShoots.begin(), opponentsShoots.end());
			}

		}
		//draw player
		screen[P1.getPlayerPosY() * nScreenWidth + P1.getPlayerPosX()] = L'>';

		//wyswietlanie klatki
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten); //{0,0} - top left corner

	}
	CloseHandle(hConsole);
	leaderbordUpdate(sName, nScore, nKills);
}

void quit(){
	system("cls");
	cout << "Goodbye";
	system("pause");
}

int main(int argc, char** argv) {
	 
	srand(time(NULL));
	
	start();

	return 0;
}

