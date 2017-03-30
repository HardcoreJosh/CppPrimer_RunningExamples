#include "TextQuery.h"
#include <sstream>
using namespace std;

TextQuery::TextQuery(std::istream& cin):
	file(make_shared<vector<string>>())
{

	string line;
	while (getline(cin, line)) {
		file->push_back(line);
		auto n = file->size() - 1;
		istringstream is(line);
		string word;
		while (is >> word) {
			// Unnessesary
			//if (wm.find(word) == wm.end()) {
			//}

			// auto handle = wm[word]; ! Error, must be reference 
			auto& handle = wm[word];
			if (!handle) {
				// handle = new set<line_no>(); !wrong NO OPERAND '=' MATCHES
				handle.reset(new set<line_no>());
			}
			handle->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string& q) const
{

	auto lines = wm.find(q);
	if (lines != wm.end()) {
		return QueryResult(q, lines->second, file);
	}
	return QueryResult(q, nullptr, file);
}

std::ostream & print(std::ostream& out, const QueryResult& result)
{
	if (!result.lines)
		return out;
	auto line_set = *result.lines;
	auto file = *result.file;
	for (auto line_num : line_set) {
		out << line_num << ": " << file[line_num] << endl;
	}
	return out;
}

void runQueries(std::istream& in)
{
	TextQuery tq(in);

	while (true)
	{
		string single_query;
		if (!(std::cin >> single_query) || single_query == "q")
			break;
		print(cout, tq.query(single_query)) << endl;
	}
	
}