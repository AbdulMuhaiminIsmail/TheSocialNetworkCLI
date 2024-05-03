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

class User : public Entity {
	static int currentID; //Keeps track of the current user
	vector <string> friends; //Stores the userIDs of other users (friends)
	vector <string> ownedPages; //Stores the ids of owned pages by the user
	vector <string> likedPages; //Stores the ids of all liked pages
public:
	User();
	User(string userName);
	string getID() const;
	string getName() const;
	vector <string> getPosts() const;
	vector <string> getFriends() const;
	vector <string> getOwnedPages() const;
	vector <string> getLikedPages() const;
	void setID(string ID);
	void setName(string name);
	void setFriends(vector <string> friends);
	void setOwnedPages(vector <string> ownedPages);
	void setLikedPages(vector <string> likedPages);
	void setPosts(vector <string> posts);
	void printUser(vector <User*> Users, vector <Page*> Pages);
	void showOwnedPages(vector <Page*>& Pages);
	void showLikedPages(vector <Page*>& Pages);
	void showFriends(vector <User*>& Users);
	void createPage(string title, vector <Page*>& Pages);
	void createPost(vector <Post*>& Posts);
	void likePage(string pageID, vector <Page*>& Pages);
	void addFriend(string friendID, vector<User*>Users);
	void comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& Posts);
	void likePost(string postID, vector <Post*>& Posts);
	void viewTimeline(vector <Post*> Posts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments);
	void viewHome(vector <Post*> Posts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments);
	void shareMemory(string postID, string text, vector<Post*>& Posts, vector<User*>& Users);
	void seeMemories(vector<User*> Users, vector<Post*> Posts, vector<Page*> Pages, vector<Comment*> Comments);
};