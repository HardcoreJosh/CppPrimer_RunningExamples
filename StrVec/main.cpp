#include <iostream>
#include <string>
#include "StrVec.h"
using namespace std;

int main()
{
	// cout << wrp_str(10, 's') << endl;
	StrVec sv;
	for (size_t i = 0; i < 10; ++i)
	{
		sv.push_back(to_string(i));
	}

	StrVec sv2 = sv;
	for (auto p = sv2.begin(); p != sv2.end(); ++p)
	{
		cout << *p << " ";
	}
	cout << endl;
	StrVec sv3;
	sv3 = sv;
	for (auto p = sv3.begin(); p != sv3.end(); ++p)
	{
		cout << *p << " ";
	}
	cout << endl;

	StrVec sv4 = std::move(sv3);
	for (auto p = sv4.begin(); p != sv4.end(); ++p)
	{
		cout << *p << " ";
	}
	cout << endl;

	
}