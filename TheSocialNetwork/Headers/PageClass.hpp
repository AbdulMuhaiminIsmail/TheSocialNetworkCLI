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

class Page : public Entity {
	int likes; //Stores the number of likes on the page
	static int currentID; //Keeps track of the current page
	string ownerID; //Stores the ID of the owner of the page
public:
	Page(string ownerID, string title);
	string getID();
	string getName();
	vector <string> getPosts();
	string getOwnerID();
	int getLikes();
	void incLikes();
	void likePost(string postID, vector <Post*>& UserPosts, vector <Post*>& PagePosts);
	void comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& UserPosts, vector <Post*>& PagePosts);
	void viewPage(vector <Post*> PagePosts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments);
	void createPost(vector <Post*>& PagePosts, vector <Page*>& Pages);
};


