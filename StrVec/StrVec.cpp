#include "StrVec.h"
#include <iostream>
using namespace std;

StrVec::StrVec():elements(nullptr), first_free(nullptr), cap(nullptr)
{
}

StrVec::StrVec(const StrVec & sv)
{
	cout << "& cpconstructor" << endl;
	auto data = alloc_n_copy(sv.begin(), sv.end());
	
	elements = data.first;
	first_free = data.second;
	cap = data.second;
}

StrVec::StrVec(StrVec && sv) noexcept
	:elements(sv.elements), first_free(sv.first_free), cap(sv.cap)
{
	cout << "&& cp constructor" << endl;
	sv.elements = sv.first_free = sv.cap = nullptr;
}

StrVec & StrVec::operator=(const StrVec & rhs)
{
	if (this != &rhs)
	{
		auto data = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		first_free = cap = data.second;
	}
	return *this;
}

StrVec & StrVec::operator=(StrVec && rhs) noexcept
{
	if (this != &rhs)
	{
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

StrVec::~StrVec()
{
	free();
}

std::allocator<string> StrVec::alloc;
void StrVec::reallocate()
{
	auto new_capacity = capacity() ? capacity() * 2 : 1;
	auto new_beg = alloc.allocate(new_capacity);
	auto new_end = new_beg;

	if (elements)
	{
		for (auto old_p = elements; old_p != first_free; ++old_p)
		{
			alloc.construct(new_end++, std::move(*old_p));
		}
	}

	free();
	elements = new_beg;
	first_free = new_end;
	cap = elements + new_capacity;
	
}

void StrVec::chk_n_alloc()
{
	if (first_free == cap)
		reallocate();
}

void StrVec::push_back(const string & s)
{
	chk_n_alloc();

	alloc.construct(first_free++, s);
}

size_t StrVec::size() const
{
	return first_free - elements;
}
size_t StrVec::capacity() const
{
	return cap - elements;
}

std::string * StrVec::begin() const
{
	return elements;
}

std::string * StrVec::end() const
{
	return first_free;
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e)
{
	auto new_beg = alloc.allocate(e - b);
	return { new_beg, uninitialized_copy(b, e, new_beg) };
}

void StrVec::free()
{
	if (elements)
	{
		// This is suboptimal. Better in reverse order.
		for (auto p = elements; p != first_free; ++p)
		{
			alloc.destroy(p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}


