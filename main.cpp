#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void runQueries(std::istream& in);
void input(istream& in)
{
	string s;
	while ((in >> s) && s != "q") {
		cout << s << endl;
	}
}

int main()
{
	istringstream is(string("1 2 3\n 2 2 2\n 3 3 3\n"));
	runQueries(is);

}