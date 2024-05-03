#pragma once
#include<iostream>
#include<string>
#include<vector>

#include "HelperClass.hpp"
#include "ChronoClass.hpp"
#include "ActivityClass.hpp"
#include "CommentClass.hpp"
#include "PostClass.hpp"
#include "PageClass.hpp"
#include "UserClass.hpp"
#include "EntityClass.hpp"

using namespace std;

//Helper Functions
int idToNum(int start, string id);
void showLikedBy(string postID, vector <User*>& Users, vector <Page*>& Pages, vector <Post*>& Posts);
void createUser(string userName, vector <User*>& Users);
bool oneDayDiff(Date& d1, Date& d2);
string getTimeAgo(Post* source);
Date *getCurrentDate();
