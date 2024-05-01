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

