//																		***GUIDELINES AND WHAT I LEARNT***
//Exhibit abstraction and encapsulation and always make all getters and setters for all data members of all classes used
//Header files and classes must not have the same name
//Try adding forward declarations in case stuff does not work
//Professionaly speaking, make header and implementation files separately
//Keep committing to the main branch to keep track of code changes on GitHub
//Use pragma once and guards to thwart cases of circular dependencies and self inclusion
//Included header files and implementation files go to external dependencies so they should not be reincluded in the project anywhere else
//When working in a large project, prefer aggregation over composition as it would throw a bunch of errors when not working with pointers

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Definitions/EntityClass.cpp"
#include "Definitions/UserClass.cpp"
#include "Definitions/ChronoClass.cpp"
#include "Definitions/PageClass.cpp"
#include "Definitions/PostClass.cpp"
#include "Definitions/CommentClass.cpp"
#include "Definitions/ActivityClass.cpp"
#include "Definitions/HelperClass.cpp"

#include "Headers/HelperClass.hpp"
#include "Headers/ChronoClass.hpp"
#include "Headers/ActivityClass.hpp"
#include "Headers/CommentClass.hpp"
#include "Headers/PostClass.hpp"
#include "Headers/PageClass.hpp"
#include "Headers/UserClass.hpp"
#include "Headers/EntityClass.hpp"

using namespace std;

class App
{
	vector<User*> Users;
	vector<Page*> Pages;
	vector<Post*> Posts;
	vector<Comment*> Comments;
	string currentUser = "u1";
public:
	void Run()
	{
		//Import Data from Files
		importData();
		printUser();
		setCurrentUser("u2");
		printUser();
		//Displaying Main Menu
		createUser("Abdul Muhaimin");
		createUser("Salman Khan");
		createPage("CNN");
		printUser();
		addFriend("u2");
		createPost();
		commentPost("post1", "This is a meta comment!");
		viewTimeline();
		setCurrentUser("u2");
		commentPost("post1", "This is sample comment 2!");
		createPost();
		viewTimeline();
		setCurrentUser("u1");
		viewTimeline();
		//Exporting Data to Files
		exportData();
		//Deallocating Memory
		DeallocMem();
	}
	void importData() {
		ifstream usersFile("DataFiles/Users.txt");
		if (!usersFile.is_open()) {
			cout << "Error opening Users file." << endl;
		}
		else {
			//Total users
			int totalUsers;
			usersFile >> totalUsers;
			for (int i = 0; i < totalUsers; i++) {
				User* user = new User();
				//ID
				string userID;
				usersFile >> userID;
				user->setID(userID);
				//Name
				string userName;
				getline(usersFile, userName);
				user->setName(userName); 
				//Posts
				int totalPosts;
				usersFile >> totalPosts;
				vector<string> posts;
				for (int j = 0; j < totalPosts; j++) {
					string currentPost;
					usersFile >> currentPost;
					posts.push_back(currentPost);
				}
				user->setPosts(posts);
				//Friends
				int totalFriends;
				usersFile >> totalFriends;
				vector<string> friends;
				for (int j = 0; j < totalFriends; j++) {
					string currentFriend;
					usersFile >> currentFriend;
					friends.push_back(currentFriend);
				}
				user->setFriends(friends);
				//Liked Pages
				int totalLikedPages;
				usersFile >> totalLikedPages;
				vector<string> likedPages;
				for (int j = 0; j < totalLikedPages; j++) {
					string currentPage;
					usersFile >> currentPage;
					likedPages.push_back(currentPage);
				}
				user->setLikedPages(likedPages);
				//Owned Pages
				int totalOwnedPages;
				usersFile >> totalOwnedPages;
				vector<string> ownedPages;
				for (int j = 0; j < totalOwnedPages; j++) {
					string currentPage;
					usersFile >> currentPage;
					ownedPages.push_back(currentPage);
				}
				user->setOwnedPages(ownedPages);
				//Adding user to main vector
				Users.push_back(user);
			}
			usersFile.close();
		}
		ifstream pagesFile("DataFiles/Pages.txt");
		if (!pagesFile.is_open()) {
			cout << "Error opening Pages file." << endl;
		}
		else {
			//Total pages
			int totalPages;
			pagesFile >> totalPages;
			for (int i = 0; i < totalPages; i++) {
				Page* page = new Page();
				//ID
				string pageID;
				pagesFile >> pageID;
				page->setID(pageID);
				//Name
				string pageName;
				pagesFile >> pageName;
				page->setName(pageName); 
				//Likes
				int totalLikes;
				pagesFile >> totalLikes;
				page->setLikes(totalLikes);
				//OwnerID
				string ownerID;
				pagesFile >> ownerID;
				page->setOwnerID(ownerID);
				//Posts
				int totalPosts;
				pagesFile >> totalPosts;
				vector<string> posts;
				for (int j = 0; j < totalPosts; j++) {
					string currentPost;
					pagesFile >> currentPost;
					posts.push_back(currentPost);
				}
				page->setPosts(posts);
				//Adding page to main vector
				Pages.push_back(page);
			}
			pagesFile.close();
	}
	ifstream postsFile("DataFiles/Posts.txt");
		if (!postsFile.is_open()) {
			cout << "Error opening Posts file." << endl;
		}
		else {
			//Total posts
			int totalPosts;
			postsFile >> totalPosts;
			for (int i = 0; i < totalPosts; i++) {
				Post* post = new Post();
				//ID
				string postID;
				postsFile >> postID;
				post->setID(postID);
				//OwnerID
				string ownerID;
				postsFile >> ownerID;
				post->setOwnerID(ownerID);
				//Description
				string description;
				postsFile >> description;
				post->setDescription(description);
				//Memory
				bool isMemory;
				postsFile >> isMemory;
				post->setIsMemory(isMemory);
				//Comments
				int totalComments;
				postsFile >> totalComments;
				post->setCommentCount(totalComments);
				//Likes
				int totalLikes;
				postsFile >> totalLikes;
				post->setLikesCount(totalLikes);
				//Date
				int day, month, year;
				postsFile >> day;
				postsFile >> month;
				postsFile >> year;
				Date* date = new Date(day, month, year);
				post->setDatePosted(date);
				//Activity
				int hasActivity;
				postsFile >> hasActivity;
				if(hasActivity) {
					int type;
					string value;
					postsFile >> type;
					postsFile >> value;
					Activity* activity = new Activity(type, value);
					post->setActivity(activity);
				}
				else {
					post->setActivity(nullptr);
				}
				//Comments
				vector <string> comments;
				for (int i = 0; i < totalComments; i++)
				{
					string currentComment;
					postsFile >> currentComment;
					comments.push_back(currentComment);
				}
				//Likers
				vector <string> likedBy;
				for (int i = 0; i < totalLikes; i++)
				{
					string currentLiker;
					postsFile >> currentLiker;
					comments.push_back(currentLiker);
				}
				//Adding post to main vector
				Posts.push_back(post);
			}
			postsFile.close();
		}
		ifstream commentsFile("DataFiles/Comments.txt");
		if (!commentsFile.is_open()) {
			cout << "Error opening Comments file." << endl;
		}
		else {
			//Total comments
			int totalComments;
			commentsFile >> totalComments;
			for (int i = 0; i < totalComments; i++)
			{
				Comment* comment = new Comment();
				//CommentID
				string commentID;
				commentsFile >> commentID;
				comment->setCommentID(commentID);
				//PostID
				string postID;
				commentsFile >> postID;
				comment->setPostID(postID);
				//PosterID
				string posterID;
				commentsFile >> posterID;
				comment->setPosterID(posterID);
				//Text
				string text;
				commentsFile >> text;
				comment->setText(text);
				//Adding comment to main vector
				Comments.push_back(comment);
			}
			
		}
			commentsFile.close();
}
	void exportData() {
		ofstream usersFile("DataFiles/Users.txt");
		if (!usersFile.is_open()) {
			cout << "Error opening Users file." << endl;
		}
		else {
			//Total users
			usersFile << Users.size() << endl;
			for (int i = 0; i < Users.size();i++) {
				//ID, Name and PostIDs
				usersFile << Users[i]->getID() << endl;
				usersFile << Users[i]->getName() << endl;
				//Posts
				usersFile << Users[i]->getPosts().size() << endl;
				for (int j = 0;j < Users[i]->getPosts().size(); j++) {
					usersFile << Users[i]->getPosts()[j] << endl;
				}
				//Friends
				usersFile << Users[i]->getFriends().size() << endl;
				for (int j = 0;j < Users[i]->getFriends().size(); j++) {
					usersFile << Users[i]->getFriends()[j] << endl;
				}
				//Liked Pages
				usersFile << Users[i]->getLikedPages().size() << endl;
				for (int j = 0;j < Users[i]->getLikedPages().size(); j++) {
					usersFile << Users[i]->getLikedPages()[j] << endl;
				}
				//Owned Pages
				usersFile << Users[i]->getOwnedPages().size() << endl;
				for (int j = 0;j < Users[i]->getOwnedPages().size(); j++) {
					usersFile << Users[i]->getOwnedPages()[j] << endl;
				}
			}
			usersFile.close();
		}
		ofstream pagesFile("DataFiles/Pages.txt");
		if (!pagesFile.is_open()) {
			cout << "Error opening Pages file." << endl;
		}
		else {
			//Total Pages
			pagesFile << Pages.size() << endl;
			for (int i = 0; i < Pages.size();i++) {
				//ID, Name, Likes, OwnerID
				pagesFile << Pages[i]->getID() << endl;
				pagesFile << Pages[i]->getName() << endl;
				pagesFile << Pages[i]->getLikes() << endl;
				pagesFile << Pages[i]->getOwnerID() << endl;
				//Posts
				pagesFile << Pages[i]->getPosts().size() << endl;
				for (int j = 0;j < Pages[i]->getPosts().size(); j++) {
					pagesFile << Pages[i]->getPosts()[j] << endl;
				}
			}
			pagesFile.close();
		}
		ofstream postsFile("DataFiles/Posts.txt");
		if (!postsFile.is_open()) {
			cout << "Error opening Posts file." << endl;
		}
		else {
			//Total Posts
			postsFile << Posts.size() << endl;
			for (int i = 0; i < Posts.size();i++) {
				//ID, OwnerID, Likes, Comments, isMemory, Description
				postsFile << Posts[i]->getID() << endl;
				postsFile << Posts[i]->getOwnerID() << endl;
				postsFile << Posts[i]->getDescription() << endl;
				postsFile << Posts[i]->getIsMemory() << endl;
				postsFile << Posts[i]->getCommentCount() << endl;
				postsFile << Posts[i]->getLikesCount() << endl;
				//Date Posted
				postsFile << Posts[i]->getDatePosted().day << endl;
				postsFile << Posts[i]->getDatePosted().month << endl;
				postsFile << Posts[i]->getDatePosted().year << endl;
				//Activity
				if (Posts[i]->getActivity() != nullptr) {
					postsFile << 1 << endl;
					postsFile << Posts[i]->getActivity()->getType() << endl;
					postsFile << Posts[i]->getActivity()->getValue() << endl;
				}
				else {
					postsFile << 0 << endl;
				}
				//Comments
				for (int j = 0;j < Posts[i]->getComments().size(); j++) {
					postsFile << Posts[i]->getComments()[j] << endl;
				}
				//Likers
				for (int j = 0;j < Posts[i]->getLikedBy().size(); j++) {
					postsFile << Posts[i]->getLikedBy()[j] << endl;
				}
			}
			postsFile.close();
		}
		ofstream commentsFile("DataFiles/Comments.txt");
		if (!commentsFile.is_open()) {
			cout << "Error opening Comments file." << endl;
		}
		else {
			//Total Comments
			commentsFile << Comments.size() << endl;
			for (int i = 0; i < Comments.size();i++) {
				//ID, PostID, PosterID, Text
				commentsFile << Comments[i]->getCommentID() << endl;
				commentsFile << Comments[i]->getPostID() << endl;
				commentsFile << Comments[i]->getPosterID() << endl;
				commentsFile << Comments[i]->getText() << endl;
			}
			commentsFile.close();
		}
	}
	void createUser(string userName) {
		User* user = new User(userName);
		Users.push_back(user);
		cout << "User " << userName << " created successfully with userID: " << user->getID() << endl;
	}
	void addFriend(string friendID) {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->addFriend(friendID, Users);
	}
	void printUser() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->printUser(Users, Pages);
	}
	void createPost() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->createPost(Posts);
	}
	void createPage(string title) {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->createPage(title, Pages);
	}
	void setCurrentUser(string userID) {
		currentUser = userID;
	}
	void viewLikesPages() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->showLikedPages(Pages);
	}
	void viewHome() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->viewHome(Posts, Users, Pages, Comments);
	} 
	void likePost(string postID) {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->likePost(postID, Posts);
	}
	void showLikers(string postID) {
		showLikedBy(postID, Users, Pages, Posts);
	}
	void commentPost(string postID, string comment) {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->comment(postID, comment, Comments, Posts);
	}
	void viewPost(string postID) {
		int index = idToNum(4, postID) - 1;
		Posts[index]->showPost(Users, Pages, Comments);
	}
	void shareMemory(string postID, string text) {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->shareMemory(postID, text, Posts, Users);
	}
	void seeYourMemories() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->seeMemories(Users, Posts, Pages, Comments);
	}
	void viewTimeline() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->viewTimeline(Posts, Users, Pages, Comments);
	}
	void viewFriends() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->showFriends(Users);
	}
	void viewPage(string pageID) {
		int index = idToNum(1, pageID) - 1;
		Pages[index]->viewPage(Posts, Users, Pages, Comments);
	}
	void DeallocMem() {
		for (User *user : Users)
		{
			delete user;
		}
		for (Page *page : Pages)
		{
			delete page;
		}
		for (Post *post : Posts)
		{
			delete post;
		}
		for (Comment *comment : Comments)
		{
			delete comment;
		}
	}
};

int main()
{
	App app;
	app.Run();
}