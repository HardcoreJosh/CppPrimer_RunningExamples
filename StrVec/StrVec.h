#pragma once
#ifndef STRVEC_H
#define STRVEC_H

#include <memory>
#include <string>

class StrVec {
public:
	StrVec();
	StrVec(const StrVec &);
	StrVec(StrVec&&) noexcept;
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept;
	~StrVec();

	void push_back(const std::string &);
	size_t size()const;
	size_t capacity()const;
	std::string* begin()const;
	std::string*end()const;


private:
	static std::allocator<std::string> alloc;
	static int i;
	void chk_n_alloc();
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();
	std::string *elements;
	std::string *first_free;
	std::string *cap;
};

#endif 

