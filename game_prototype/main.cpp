#include<iostream>

int random(int MIN = 0, int MAX = 9) {
	return rand() % (MAX - MIN + 1) + MIN;
}

class Point
{
private:
	int x{};
	int y{};
public:
	Point(int x = 3, int y = 5) :
		x{ x },
		y{ y }
	{}

	int getX() { return this->x; };
	int getY() { return this->y; };

	void setX(int x) { this->x = x; };
	void setY(int y) { this->y = y; };
};

class Unit
{
private:
	int hp{};
	int force{};
	int power{};
	bool alive{};
	Point* position{ nullptr };
public:
	Unit(const Point& p = {0, 0}, int hp = 100, int force = 100, int power = 10, bool alive = true) :
		position{ new Point{p} },
		hp{ hp },
		force{ force },
		power{ power },
		alive{ alive }
	{}

	virtual void attack(Unit& unit) = 0;

	virtual void defend(Unit& unit) = 0;

	virtual void changePosition(Point* position) = 0;

	void setHp(int hp) { this->hp = hp; }
	void setForce(int force) { this->force = force; }
	void setPower(int power) { this->power = power; }
	void setAlive(bool alive) { this->alive = alive; }
	void setPosition(Point* position)
	{ 
		this->position->setX(position->getX());
		this->position->setY(position->getY());
	}

	int getHp() { return this->hp; }
	int getForce() { return this->force; }
	int getPower() { return this->power; }
	int getAlive() { return this->alive; }
	Point* getPosition() { return this->position; }

	~Unit()
	{
		if (this->position == nullptr)
			delete position;
	}
};

class Archer : public Unit
{
public:
	Archer(const Point& p = { 0, 0 }, int hp = 100, int force = 100, int power = 10, bool alive = true) : Unit{ p, hp, force, alive }{}

	virtual void attack(Unit& unit) override
	{
		unit.setForce(unit.getForce() - random(10, 15));
		if (unit.getForce() <= 0)
			unit.setHp(unit.getHp() - random(30, 35));
		if (unit.getHp() <= 0)
			std::cout << "Unit is not alive";
	}
	
	virtual void defend(Unit& unit) override
	{
		unit.setForce(unit.getForce() + random(15, 30));
	}

	virtual void changePosition(Point* position) override
	{
		setPosition(position);
	}
};

class Warrior : public Unit
{
public:
	Warrior(const Point& p = { 0, 0 }, int hp = 100, int force = 100, int power = 10, bool alive = true) : Unit{ p, hp, force, alive }{}

	virtual void attack(Unit& unit) override
	{
		unit.setForce(unit.getForce() - random(25, 35));
		if (unit.getForce() <= 0)
			unit.setHp(unit.getHp() - random(20, 25));
		if (unit.getHp() <= 0)
			std::cout << "Unit is not alive";
	}

	virtual void defend(Unit& unit) override
	{
		unit.setForce(unit.getForce() + random(10, 35));
	}

	virtual void changePosition(Point* position) override
	{
		setPosition(position);
	}
};

int main()
{
	Archer archer;
	Warrior warrior;
	Point newPos{ 3, 5 };
	Point* position = &newPos;
	
	archer.attack(warrior);

	//std::cout << warrior.getForce();

	warrior.changePosition(position);

	//std::cout << warrior.getPosition();

	return 0;
}