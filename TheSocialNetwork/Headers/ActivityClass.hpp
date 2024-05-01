#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"EntityClass.hpp"
#include"PageClass.hpp"
#include"PostClass.hpp"
#include"CommentClass.hpp"
#include"HelperClass.hpp"

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
