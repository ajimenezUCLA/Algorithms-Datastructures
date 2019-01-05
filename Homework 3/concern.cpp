#include <iostream>
#include <string>
#include <cassert>

using namespace std;


//////////////////////////////////////
//		Concern - (Base Class)		//
//////////////////////////////////////

class Concern	// base class
{
public:
	Concern(string name);					// constructor
	string person() const;					// returns the name of person, shouldn't modify
	virtual ~Concern();						// desctructor, which other functions will use
	virtual string description() const = 0;	// pure virtual function, no tangible concern
	virtual bool possibleFelony() const;
private:
	string m_name;
};

Concern::Concern(string name)
	: m_name(name)
{}

Concern::~Concern()					// empty, 
{}

string Concern::person() const
{
	return m_name;					// for displaying the persons name
}

bool Concern::possibleFelony() const
{
	return false;					// most concerns aren't felonius 
}

//////////////////////////////////////////
//		EthicsMatter - (Sub Class)		//
//////////////////////////////////////////

class EthicsMatter : public Concern		// sub class
{
public:
	EthicsMatter(string name);				// Consctructor
	virtual string description() const;		//
	virtual ~EthicsMatter();
private:
};

EthicsMatter::EthicsMatter(string name)	
	: Concern(name)
{}

string EthicsMatter::description() const
{
	return "An ethics matter";
}

EthicsMatter::~EthicsMatter()
{
	cout << "Destroying " << person() << "'s ethics matter" << endl;
}

//////////////////////////////////////////
//		HushPayment - (Sub Class)		//
//////////////////////////////////////////

class HushPayment : public Concern		// sub class
{
public:
	HushPayment(string name, int payment);
	virtual ~HushPayment();
	virtual string description() const;
private:
	int m_payment;

};

HushPayment::HushPayment(string name, int payment)
	: Concern(name), m_payment(payment)
{}

HushPayment::~HushPayment()
{
	cout << "Destroying " << person() << "'s hush payment" << endl;
}

string HushPayment::description() const
{
	// string s("A $" + to_string(m_payment));
	return "A $" + to_string(m_payment) + " payment";
}

//////////////////////////////////////////
//		Investigation - (Sub Class)		//
//////////////////////////////////////////

class Investigation : public Concern	// sublclass
{
public:
	Investigation(string name);
	virtual ~Investigation();
	virtual bool possibleFelony() const;
	virtual string description() const;
private:
};

Investigation::Investigation(string name)
	: Concern(name)
{}

Investigation::~Investigation()
{
	cout << "Destroying " << person() << "'s investigation" << endl;
}

bool Investigation::possibleFelony() const
{
	return true;
}

string Investigation::description() const
{
	return "An investigation";
}

//////////////////////////////
//		Main & Display		//
//////////////////////////////

/*
void display(const Concern* c)
{
	cout << c->description() << " involving " << c->person();
	if (c->possibleFelony())
		cout << ", possibly felonious";
	cout << endl;
}

int main()
{

	Concern* concerns[4];
	concerns[0] = new EthicsMatter("Pruitt");
	// Hush payments have a person's name and an amount of money (an int).
	concerns[1] = new HushPayment("Clifford", 130000);
	concerns[2] = new HushPayment("McDougal", 150000);
	concerns[3] = new Investigation("Mueller");

	cout << "Here are the concerns:" << endl;
	for (int k = 0; k < 4; k++)
		display(concerns[k]);

	// Clean up the concerns before exiting
	cout << "Cleaning up:" << endl;
	for (int k = 0; k < 4; k++)
		delete concerns[k];

}
*/