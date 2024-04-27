#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<ctime>
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/EntityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PageClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PostClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/CommentClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ActivityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/HelperClass.hpp"
using namespace std;
class Date {
public:
	int day;
	int month;
	int year;
	Date();
	Date(int day, int month, int year);
	string getTimeDate();
	string getCurrentDate();
	void print() const;
	void operator = (const Date& d2);
};


