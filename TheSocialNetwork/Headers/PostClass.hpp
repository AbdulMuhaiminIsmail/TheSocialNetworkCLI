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

class Date;
class Entity;
class User;
class Page;
class Post;
class Comment;
class Activity;

class Post {
	static int currentID;
	int likes = 0; //Stores the number of likes on the post (10 at max)
	int commentsCount = 0; //Stores the number of comments on the post (10 at max) 
	bool isMemory; //Depending on this value the post is printed in a format
	string postID; //Stores the ID of the post [prefix: "up" for user post "pp" for page post]
	string ownerID; //Stores the ID of the owner of the post
	string description; //Stores the text description of the post
	Date* datePosted; //Stores the date on which the post was created [DD/MM/YYYY]
	vector <string> likedBy; //Stores the IDs of the Users or Pages who liked the post
	vector <string> comments; //Stores the IDs of the comments written
	Activity* activity; //Stores the associated activity with the post
public:
	Post();
	Post(string description, Activity* activity, bool isMemory);
	string getID() const;
	string getOwnerID() const;
	string getDescription() const;
	bool getIsMemory() const;
	int getCommentCount() const;
	int getLikesCount() const;
	Date getDatePosted() const;
	vector<string> getLikedBy() const;
	vector<string> getComments() const;
	Activity* getActivity() const;
	void setID(string id);
	void setOwnerID(string id);
	void setDescription(string description);
	void setIsMemory(bool isMemory);
	void setCommentCount(int comments);
	void setLikesCount(int likes);
	void setDatePosted(Date* date);
	void setLikedBy(vector<string> likedBy);
	void setComments(vector<string> comments);
	void setActivity(Activity* activity);
	void addLikedBy(string liker);
	void addComment(string commentID);
	void incLikes();
	void incComments();
	void showPost(vector<User*> Users, vector<Page*> Pages, vector<Comment*> Comments);
	~Post();
};
