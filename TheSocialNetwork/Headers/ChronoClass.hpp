#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<ctime>

#include "HelperClass.hpp"
#include "ActivityClass.hpp"
#include "CommentClass.hpp"
#include "PostClass.hpp"
#include "PageClass.hpp"
#include "UserClass.hpp"
#include "EntityClass.hpp"

using namespace std;

class Date {
public:
	int day;
	int month;
	int year;
	Date();
	Date(int day, int month, int year);
	string stringDate();
	void print() const;
	void operator = (const Date& d2);
	bool operator == (const Date& d2);
};


