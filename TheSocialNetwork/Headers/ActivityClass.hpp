#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/EntityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PageClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PostClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/CommentClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/HelperClass.hpp"
using namespace std;

class Activity {
	int type;
	string value;
public:
	Activity(int type = 0, string value = "");
	int getType() const;
	string getValue() const;
	void setActivity();
};