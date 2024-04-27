#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/EntityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/UserClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PageClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PostClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/CommentClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ChronoClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ActivityClass.hpp"
using namespace std;

class User;
class Page;
class Post;
class Date;
//Helper Functions
int idToNum(int start, string id);
void showLikedBy(string postID, vector <User*>& Users, vector <Page*>& Pages, vector <Post*>& UserPosts, vector <Post*>& PagePosts);
void createUser(string userName, vector <User*>& Users);
bool oneDayDiff(Date& d1, Date& d2);
Date getCurrentDate();