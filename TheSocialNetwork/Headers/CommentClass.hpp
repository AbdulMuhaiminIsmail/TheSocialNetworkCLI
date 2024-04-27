#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/EntityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/UserClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PageClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PostClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ChronoClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ActivityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/HelperClass.hpp"
using namespace std;

class User;
class Page;
	
class Comment {
	static int currentID;
	string commentID;
	string postID; //Stores the ID of the original Post
	string posterID; //Stores the ID of Page or User who commented
	string text; //Stores the text of the comment writen
public:
	Comment(string postID, string posterID, string text);
	string getPostID();
	string getCommentID();
	void print(vector <User*> Users, vector <Page*> Pages);
};

