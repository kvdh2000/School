/*
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Critter
{
public:
	Critter(const string& name = "");
	string GetName() const;

private:
	string m_Name;
};

Critter::Critter(const string& name) :
	m_Name(name)
{}

inline string Critter::GetName() const
{
	return m_Name;
}

class Farm
{
public:
	Farm(int spaces = 1);
	void Add(const Critter& aCritter);
	void RollCall() const;
	friend ostream& operator<<(ostream& os, const Farm& aFarm);

private:
	vector<Critter> m_Critters;
};

Farm::Farm(int spaces)
{
	m_Critters.reserve(spaces);
}

void Farm::Add(const Critter& aCritter)
{
	m_Critters.push_back(aCritter);
}

void Farm::RollCall() const
{
	for (vector<Critter>::const_iterator iter = m_Critters.begin();
		iter != m_Critters.end();
		++iter)
	{
		cout << iter->GetName() << " here.\n";
	}
}

ostream& operator<<(ostream& os, const Critter& aCritter)
{
	os << aCritter.GetName();
	return os;
}ostream& operator<<(ostream& os, const Farm& aFarm)
{
	for (vector<Critter>::const_iterator iter = aFarm.m_Critters.begin();
		iter != aFarm.m_Critters.end();
		++iter)
	{
		os << iter->GetName() << " here.\n";
	}

	return os;
}

int main()
{
	Critter crit("Poochie");
	cout << "My critter's name is " << crit << endl;

	cout << "\nCreating critter farm.\n";
	Farm myFarm(3);

	cout << "\nAdding three critters to the farm.\n";
	myFarm.Add(Critter("Moe"));
	myFarm.Add(Critter("Larry"));
	myFarm.Add(Critter("Curly"));

	cout << myFarm;

	return 0;
}
*/