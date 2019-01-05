#include <iostream>
#include <string>
#include <vector>

using namespace std;

class File
{
public:
	File(string nm) : m_name(nm) {}
	virtual ~File() {}
	string name() const { return m_name; }
	virtual bool add(File* f) = 0;
	virtual const vector<File*>* files() const = 0;
private:
	string m_name;
};

class PlainFile : public File
{
public:
	PlainFile(string nm) : File(nm) {}
	virtual bool add(File* f) { return false; }
	virtual const vector<File*>* files() const { return nullptr; }
};

class Directory : public File
{
public:
	Directory(string nm) : File(nm) {}
	virtual ~Directory();
	virtual bool add(File* f) { m_files.push_back(f); return true; }
	virtual const vector<File*>* files() const { return &m_files; }
private:
	vector<File*> m_files;
};

Directory::~Directory()
{
	for (int k = 0; k < m_files.size(); k++)
		delete m_files[k];
}

// Must be Recursive
void listAll(string path, const File* f)  // two-parameter overload
{
	
	if (f->files() == NULL)		// Exit Condition
	{
		cout << "/" << path << f->name() << endl;
		return;	// print directory and exit
	}
	if (f->name() != "")		// if the string is empty, print directory
	{
		cout << "/" << path << f->name() << endl;
	}
	for (vector<File*>::const_iterator it = f->files()->begin(); it != f->files()->end(); it++)	// this prints out files
	{
		string temp;
		if (f->name() != "")
		{
			temp = path + f->name() + "/";
		}
		listAll(temp, (*it));
	}
}

void listAll(const File* f)  // one-parameter overload
{
	if (f != nullptr)
		listAll("", f);
}

int main()
{
	Directory* d1 = new Directory("Fun");
	d1->add(new PlainFile("party.jpg"));
	d1->add(new PlainFile("beach.jpg"));
	d1->add(new PlainFile("skitrip.jpg"));
	Directory* d2 = new Directory("Work");
	d2->add(new PlainFile("seaslab.jpg"));
	Directory* d3 = new Directory("My Pictures");
	d3->add(d1);
	d3->add(new PlainFile("me.jpg"));
	d3->add(new Directory("Miscellaneous"));
	d3->add(d2);
	listAll(d3);
	delete d3;
	string dot;
	cout << dot << endl;
	cout << dot.size() << endl;
	if (dot == "")
	{
		cout << "HODOR" << endl;
	}
}