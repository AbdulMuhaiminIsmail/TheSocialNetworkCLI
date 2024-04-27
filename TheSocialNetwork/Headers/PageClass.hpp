#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/EntityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/UserClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PostClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/CommentClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ActivityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/HelperClass.hpp"
using namespace std;

class Entity;
class User;
class Post;
class Comment;
class Activity;
class Helper;
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


