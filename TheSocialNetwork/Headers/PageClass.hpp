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
	static int currentID; //Keeps track of the current page
	int likes; //Stores the number of likes on the page
	string ownerID; //Stores the ID of the owner of the page
public:
	Page();
	Page(string ownerID, string title);
	int getLikes();
	string getID();
	string getName();
	string getOwnerID();
	vector <string> getPosts();
	void setLikes(int likes);
	void setID(string ID);
	void setName(string name);
	void setOwnerID(string ownerID);
	void setPosts(vector <string> posts);
	void incLikes();
	void likePost(string postID, vector <Post*>& Posts);
	void comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& Posts);
	void viewPage(vector <Post*> Posts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments);
	void createPost(vector <Post*>& Posts, vector <Page*>& Pages);
};


