//																		***GUIDELINES AND WHAT I LEARNT***
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
		
		//Dates and home
		// Date date(25, 4, 2024);
		// UserPosts[1]->setDatePosted(date);
		// u->viewHome(UserPosts, Users, PagePosts, Pages, Comments);

		//Memories
		u->seeMemories(Users, UserPosts, Pages, Comments);
		u->shareMemory("up1", "I did this shit", UserPosts, Users);
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