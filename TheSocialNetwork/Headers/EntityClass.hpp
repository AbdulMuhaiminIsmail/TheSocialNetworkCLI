#pragma once
#include<string>
#include<vector>
using namespace std;

class Entity {
	string id; //Stores the userID with "u" as prefix or pageID with "p" as prefix
	string name; //Stores the full name of page/user
	vector <string> posts; //Stores the ids of all posts
public:
	Entity(string id, string name);
	string getID();
	string getName();
	vector <string> getPosts();
	void addPost(string postID);
};
