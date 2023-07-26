#ifndef COMPUTERSCIENTIST_H
#define COMPUTERSCIENTIST_H
#include <string>

using namespace std;

class ComputerScientist {	

  public:	
	ComputerScientist(const ComputerScientist& rhs);
	ComputerScientist();
	ComputerScientist(int id);
	~ComputerScientist();

	int getID() const;
	
	friend ostream& operator << (ostream &out,const ComputerScientist &computerScientist);
	bool operator == (const  ComputerScientist& rhs) const;
	bool operator < (const ComputerScientist& rhs) const;
	ComputerScientist & operator = (const  ComputerScientist& rhs) ;

  private:
	int id;

};  // end of ComputerScientist class

#endif

