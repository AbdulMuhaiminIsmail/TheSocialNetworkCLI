#pragma once
#include <string>
#include <vector>
using namespace std;

class Entity {
	string id; //Stores the userID with "u" as prefix or pageID with "p" as prefix
	string name; //Stores the full name of page/user
	vector <string> posts; //Stores the ids of all posts
public:
	Entity(string id);
	Entity(string id, string name);
	string getID() const;
	void setID(string id);
	string getName() const;
	void setName(string name);
	vector <string> getPosts() const;
	void setPosts(vector <string> posts);
	void addPost(string postID);
};
