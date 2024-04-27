#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/EntityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PageClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PostClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/CommentClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ActivityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/HelperClass.hpp"
using namespace std;

class Entity;
class Page;
class Post;
class Comment;
class Activity;
class Helper;

class User : public Entity {
	static int currentID; //Keeps track of the current user
	vector <string> friends; //Stores the userIDs of other users (friends)
	vector <string> ownedPages; //Stores the ids of owned pages by the user
	vector <string> likedPages; //Stores the ids of all liked pages
public:
	User(string userName);
	string getID();
	string getName();
	void printUser(vector <User*> Users, vector <Page*> Pages);
	void showOwnedPages(vector <Page*>& Pages);
	void showLikedPages(vector <Page*>& Pages);
	void showFriends(vector <User*>& Users);
	void createPage(string title, vector <Page*>& Pages);
	void likePost(string postID, vector <Post*>& UserPosts, vector <Post*>& PagePosts);
	void comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& UserPosts, vector <Post*>& PagePosts);
	void createPost(vector <Post*>& UserPosts, vector <User*>& Users);
	void likePage(string pageID, int& totalPages, vector <Page*>& Pages);
	void addFriend(string& friendID, int& totalUsers);
	void viewTimeline(vector <Post*> UserPosts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments);
	void viewHome(vector <Post*> UserPosts, vector <User*> Users, vector <Post*> PagePosts, vector <Page*> Pages, vector <Comment*> Comments);
};

