#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/UserClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PageClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/CommentClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ActivityClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/HelperClass.hpp"
#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ChronoClass.hpp"
using namespace std;

class Comment;
class Activity;
class User;
class Page;
class Helper;
class Date;

class Post {
	static int currentUPID;
	static int currentPPID;
	int likes = 0; //Stores the number of likes on the post (10 at max)
	int commentsCount = 0; //Stores the number of comments on the post (10 at max) 
	string postID; //Stores the ID of the post [prefix: "up" for user post "pp" for page post]
	string ownerID; //Stores the ID of the owner of the post
	string description; //Stores the text description of the post
	Date datePosted; //Stores the date on which the post was created [DD/MM/YYYY]
	vector <string> likedBy; //Stores the IDs of the Users or Pages who liked the post
	vector <string> comments; //Stores the IDs of the comments written
	Activity* activity; //Stores the associated activity with the post
public:
	Post(string description, Activity* activity, int author);
	string getID() const;
	string getOwnerID() const;
	int getCommentCount() const;
	int getLikesCount() const;
	Date getDatePosted() const;
	void setDatePosted(Date& d1);
	vector<string> getLikedBy();
	void addLikedBy(string liker);
	void setOwnerID(string id);
	void addComment(string commentID);
	void incLikes();
	void incComments();
	void showPost(vector<User*> Users, vector<Page*> Pages, vector<Comment*> Comments);
};