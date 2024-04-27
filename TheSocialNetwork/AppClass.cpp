#include <iostream>
#include <string>
#include <vector>

#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Definitions/EntityClass.cpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Definitions/UserClass.cpp"

#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Definitions/PageClass.cpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Definitions/PostClass.cpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Definitions/CommentClass.cpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Definitions/ChronoClass.cpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Definitions/ActivityClass.cpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Definitions/HelperClass.cpp"

#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/HelperClass.hpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ChronoClass.hpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ActivityClass.hpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/CommentClass.hpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PostClass.hpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/PageClass.hpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/UserClass.hpp"
#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/EntityClass.hpp"

using namespace std;

class Entity;
class User;
class Page;
class Post;
class Comment;
class Activity;
class Helper;
class Date;

class App
{
public:
	void Run()
	{
		vector<User *> Users;
		vector<Page *> Pages;
		vector<Post *> UserPosts;
		vector<Post *> PagePosts;
		vector<Comment *> Comments;

		// creating users and pages
		createUser("Muhaimin", Users);
		createUser("Salman", Users);
		User *u = Users[0];
		User *uu = Users[1];
		u->createPage("Al Jazeera", Pages);
		u->createPage("CNN", Pages);
		Page *page = Pages[0];


		//adding user as friend
		string id = uu->getID();
		int users = Users.size();
		u->addFriend(id, users);
		id = u->getID();
		uu->addFriend(id, users);

		//creating posts
		u->createPost(UserPosts, Users);	//post1
		uu->createPost(UserPosts, Users);	//post2
		u->createPost(UserPosts, Users);	//post3
		uu->createPost(UserPosts, Users);	//post4
		page->createPost(PagePosts, Pages);	//post5

		//likes and comments
		u->likePost("up1", UserPosts, PagePosts);
		uu->likePost("up1", UserPosts, PagePosts);
		u->comment("up1", "Wow", Comments, UserPosts, PagePosts);
		uu->comment("up1", "Wow", Comments, UserPosts, PagePosts);
		page->comment("up1", "Nice", Comments, UserPosts, PagePosts);
		page->likePost("up1", UserPosts, PagePosts);
		int pages = Pages.size();
		uu->likePage("p1", pages, Pages);
		u->likePage("p1", pages, Pages);

		//printing users and pages
		u->printUser(Users, Pages);	
		uu->printUser(Users, Pages);
		page->viewPage(PagePosts, Users, Pages, Comments);
		u->viewTimeline(UserPosts, Users, Pages, Comments);
		uu->viewTimeline(UserPosts, Users, Pages, Comments);
		u->viewHome(UserPosts, Users, PagePosts, Pages, Comments);
		uu->viewHome(UserPosts, Users, PagePosts, Pages, Comments);
		
		Date date(25, 4, 2024);
		UserPosts[1]->setDatePosted(date);
		u->viewHome(UserPosts, Users, PagePosts, Pages, Comments);


		//Deallocating memory
		DeallocMem(Users, Pages, UserPosts, PagePosts, Comments);
		
	}
	void DeallocMem(vector<User*>& Users, vector<Page*>& Pages, vector<Post*>& UserPosts, vector<Post*>& PagePosts, vector<Comment*>& Comments) {
		for (User *user : Users)
		{
			delete user;
		}
		for (Page *page : Pages)
		{
			delete page;
		}
		for (Post *post : UserPosts)
		{
			delete post;
		}
		for (Post *post : PagePosts)
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