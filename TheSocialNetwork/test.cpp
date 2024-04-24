//Header Files
#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<ctime>
#include<fstream>
using namespace std;

//Forward Declarations
class Activity;
class CommonClass;
class Date;
class Page;
class User;
class Comment;
class Post;
string getCurrentDate();
int idToNum(int, string);

//Classes
class Date {
	int date;
	int month;
	int year;
public:
	Date(int date = 0, int month = 0, int year = 0) : date(date), month(month), year(year) {}
	void print() {
		if (date == 0 || date > 31 || month == 0 || month > 12 || year <= 0) {
			cout << "Date is invalid or unspecified" << endl;
		}
		else {
			cout << date << "/" << month << "/" << year << endl;
		}
	}
};
class CommonClass {
	string id; //Stores the userID with "u" as prefix or pageID with "p" as prefix
	string name; //Stores the full name of page/user
	vector <string> posts; //Stores the ids of all posts
public:
	CommonClass(string id, string name) : id(id), name(name) {}
	string getID() {
		return id;
	}
	string getName() {
		return name;
	}
	vector <string> getPosts() {
		return posts;
	}
	void addPost(string postID) {
		posts.push_back(postID);
	}
};
class Activity {
	int type;
	string value;	
public:
	Activity(int type = 0, string value = "") : type(type), value(value) {}
	int getType() {
		return type;
	}
	string getValue() {
		return value;
	}
	void setActivity() {
		if (type != 0) {
			string temp;
			if (type == 1) {
				cout << "What are you feeling? (Happy/Sad/Excited/Other)" << endl;
				getline(cin, temp);

				value = " is feeling " + temp;
			}
			else if (type == 2) {
				cout << "What are you thinking? (Life/Future/Meaning of Life/Other)" << endl;
				getline(cin, temp);
				value = " is thinking about " + temp;
			}
			else if (type == 3) {
				cout << "What are you making? (Money/Arts/Memories/Other)" << endl;
				getline(cin, temp);
				value = " is making " + temp;
			}
			else if (type == 4) {
				cout << "What are you celebrating? (Birthday/Halloween/Success/Other)" << endl;
				getline(cin, temp);
				value = " is celebrating " + temp;
			}
		}
	}
};
class Post {
	static int currentID;
	int likes = 0; //Stores the number of likes on the post (10 at max)
	int commentsCount = 0; //Stores the number of comments on the post (10 at max) 
	string postID; //Stores the ID of the post [prefix: "up" for user post "pp" for page post]
	string ownerID; //Stores the ID of the owner of the post
	string description; //Stores the text description of the post
	string datePosted; //Stores the date on which the post was created [DD/MM/YYYY]
	vector <string> likedBy; //Stores the IDs of the Users or Pages who liked the post
	vector <string> comments; //Stores the IDs of the comments written
	Activity* activity; //Stores the associated activity with the post
public:
	Post(string description, Activity* activity, int author);
	string getID();
	int getLikesCount();
	void addLikedBy(string liker);
	void incLikes();
	void incComments();
	void setOwnerID(string ownerID);
	void addComment(string commentID);
	string getOwnerID();
	int getCommentCount();
	vector <string> getLikedBy();
	void showPost(vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments);
};
class Comment {
	static int currentID;
	string commentID;
	string postID; //Stores the ID of the original Post
	string posterID; //Stores the ID of Page or User who commented
	string text; //Stores the text of the comment writen
public:
	Comment(string postID, string posterID, string text);
	string getPostID();
	string getCommentID();
	void print(vector <User*> Users, vector <Page*> Pages);
};
class Page : public CommonClass {
	static int currentID; //Keeps track of the current page
	int likes = 0; //Stores the number of likes on the page
	string ownerID; //Stores the ID of the owner of the page
public:
	Page(string ownerID, string title) : CommonClass("p" + to_string(currentID++), title), ownerID(ownerID) {}
	string getID() {
		return CommonClass::getID();
	}
	string getName() {
		return CommonClass::getName();
	}
	vector <string> getPosts() {
		return CommonClass::getPosts();
	}
	string getOwnerID() {
		return ownerID;
	}
	int getLikes() {
		return likes;
	}
	void incLikes() {
		if (likes < 10) {
			likes++;
		}
		else {
			cout << "The page already has 10 likes, no more allowed" << endl;
		}
	}
	void likePost(string postID, vector <Post*>& UserPosts, vector <Post*>& PagePosts) {
		int index = idToNum(2, postID) - 1;
		if (postID[0] == 'u') {
			if (UserPosts[index]->getLikesCount() < 10) {
				UserPosts[index]->addLikedBy(CommonClass::getID());
			}
			else {
				cout << "This post already has 10 comments, no further comments are allowed" << endl;
			}
		}
		else if (postID[0] == 'p') {
			if (PagePosts[index]->getLikesCount() < 10) {
				PagePosts[index]->addLikedBy(CommonClass::getID());
			} 
			else {
				cout << "This post already has 10 comments, no further comments are allowed" << endl;
			}
		}
		else {
			cout << "The given post id is invalid" << endl;
		}
	}
	void comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& UserPosts, vector <Post*>& PagePosts) {
		int index = idToNum(2, postID) - 1;
		if (postID[0] == 'u') {
			if (UserPosts[index]->getCommentCount() < 10) {
				Comment* comment = new Comment(postID, CommonClass::getID(), text);
				Comments.push_back(comment);
				UserPosts[index]->addComment(comment->getCommentID());
			}
			else {
				cout << "This post already has 10 comments, no further comments are allowed" << endl;
			}
		}
		else if (postID[0] == 'p') {
			if (PagePosts[index]->getCommentCount() < 10) {
				Comment* comment = new Comment(postID, CommonClass::getID(), text);
				Comments.push_back(comment);
				PagePosts[index]->addComment(comment->getCommentID());
			}
			else {
				cout << "This post already has 10 comments, no further comments are allowed" << endl;
			}
		}
		else {
			cout << "The given post id is invalid" << endl;
		}
	}
	void viewPage(vector <Post*> PagePosts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
		vector <string> posts = getPosts();
		cout << getName() << endl;
		for (int i = 0; i < posts.size(); i++) {
			int index = idToNum(2, posts[i]) - 1;
			PagePosts[index]->showPost(Users, Pages, Comments);
		}
	}
	void createPost(vector <Post*>& PagePosts, vector <Page*>& Pages) {
		int hasActivity, type;
		string description;
		cout << "What is the description of the post? ";
		getline(cin, description);
		cout << "Do you want to add any activity? (0.No/1.Yes)";
		cin >> hasActivity;
		if (hasActivity) {
			do {
				cout << "What kind of activity is this? (1.Feeling/2.Thinking/3.Making/4.Celebrating)";
				cin >> type;
				if (type < 1 || type > 4) {
					cout << "Invalid type" << endl;
				}
			} while (type < 1 || type > 4);
			cin.ignore(256, '\n');
			Activity* activity = new Activity(type);
			activity->setActivity();
			Post* post = new Post(description, activity, 1);
			post->setOwnerID(CommonClass::getID());
			PagePosts.push_back(post);
			string currentPageID = CommonClass::getID();
			int pageID = idToNum(1, currentPageID) - 1;
			Pages[pageID]->addPost(post->getID());
		}
		else {
			Post* post = new Post(description, nullptr, 0);
			post->setOwnerID(CommonClass::getID());
			PagePosts.push_back(post);						//Added post to main vector to display in file
			string currentUserID = CommonClass::getID();
			int userID = idToNum(1, currentUserID) - 1;
			Pages[userID]->addPost(post->getID());			//Added post's address to Pages' posts vector
			cin.ignore(256, '\n');
		}
	}
};
class User : public CommonClass {
	static int currentID; //Keeps track of the current user
	vector <string> friends; //Stores the userIDs of other users (friends)
	vector <string> ownedPages; //Stores the ids of owned pages by the user
	vector <string> likedPages; //Stores the ids of all liked pages
public:
	User(string userName) : CommonClass("u" + to_string(currentID++), userName) {}
	string getID() {
		return CommonClass::getID();
	}
	string getName() {
		return CommonClass::getName();
	}
	void printUser(vector <User*> Users, vector <Page*> Pages) {
		cout << "Name: " << getName() << endl;
		cout << "UserID: " << getID() << endl;
		showFriends(Users);
		showLikedPages(Pages);
		showOwnedPages(Pages);
	}
	void showOwnedPages(vector <Page*>& Pages) {
		cout << "----------------------------------------------------------" << endl;
		cout << getName() << " - Owned Pages" << endl << endl;
		for (int i = 0; i < ownedPages.size(); i++) {
			int currentPageIndex = idToNum(1, ownedPages[i]) - 1;
			cout << ownedPages[i] << "-" << Pages[currentPageIndex]->getName() << endl;
		}
		cout << "----------------------------------------------------------" << endl;
	}
	void showLikedPages(vector <Page*>& Pages) {
		cout << "----------------------------------------------------------" << endl;
		cout << getName() << " - Liked Pages" << endl << endl;
		for (int i = 0; i < likedPages.size(); i++) {
			int currentPageIndex = idToNum(1, likedPages[i]) - 1;
			cout << likedPages[i] << "-" << Pages[currentPageIndex]->getName() << endl;
		}
		cout << "----------------------------------------------------------" << endl;
	}
	void showFriends(vector <User*>& Users) {
		cout << "----------------------------------------------------------" << endl;
		cout << getName() << " - Friends List" << endl << endl;
		for (int i = 0; i < friends.size(); i++) {
			int currentUserIndex = idToNum(1, friends[i]) - 1;
			cout << friends[i] << "-" << Users[currentUserIndex]->getName() << endl;
		}
		cout << "----------------------------------------------------------" << endl;
	}
	void createPage(string title, vector <Page*>& Pages) {			//page comment shall be analogous
		Page* page = new Page(CommonClass::getID(), title);
		ownedPages.push_back(page->getID());
		Pages.push_back(page);
		cout << "Page created with name " << title << " and id " << page->getID() << endl;
	}
	void likePost(string postID, vector <Post*>& UserPosts, vector <Post*>& PagePosts) {
		int index = idToNum(2, postID) - 1;
		if (postID[0] == 'u') {
			if (UserPosts[index]->getLikesCount() < 10) {
				UserPosts[index]->addLikedBy(CommonClass::getID());
			}
			else {
				cout << "This post already has 10 comments, no further comments are allowed" << endl;
			}
		}
		else if (postID[0] == 'p') {
			if (PagePosts[index]->getLikesCount() < 10) {
				PagePosts[index]->addLikedBy(CommonClass::getID());
			}
			else {
				cout << "This post already has 10 comments, no further comments are allowed" << endl;
			}
		}
		else {
			cout << "The given post id is invalid" << endl;
		}
	}
	void comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& UserPosts, vector <Post*>& PagePosts) {
		int index = idToNum(2, postID) - 1;
		if (postID[0] == 'u') {
			if (UserPosts[index]->getCommentCount() < 10) {
				Comment* comment = new Comment(postID, CommonClass::getID(), text);
				Comments.push_back(comment);
				UserPosts[index]->addComment(comment->getCommentID());
				UserPosts[index]->incComments();
			}
			else {
				cout << "This post already has 10 comments, no further comments are allowed" << endl;
			}
		}
		else if (postID[0] == 'p') {
			if (PagePosts[index]->getCommentCount() < 10) {
				Comment* comment = new Comment(postID, CommonClass::getID(), text);
				Comments.push_back(comment);
				PagePosts[index]->addComment(comment->getCommentID());
				PagePosts[index]->incComments();
			}
			else {
				cout << "This post already has 10 comments, no further comments are allowed" << endl;
			}
		}
		else {
			cout << "The given post id is invalid" << endl;
		}
	}
	void createPost(vector <Post*>& UserPosts, vector <User*>& Users) {
		int hasActivity, type;
		string description;
		cout << "What is the description of the post? ";
		getline(cin, description);
		cout << "Do you want to add any activity? (0.No/1.Yes)";
		cin >> hasActivity;
		if (hasActivity) {
			do {
				cout << "What kind of activity is this? (1.Feeling/2.Thinking/3.Making/4.Celebrating)";
				cin >> type;
				if (type < 1 || type > 4) {
					cout << "Invalid type" << endl;
				}
			} while (type < 1 || type > 4);
			cin.ignore(256, '\n');
			Activity* activity = new Activity(type);
			activity->setActivity();
			Post* post = new Post(description, activity, 0);
			post->setOwnerID(CommonClass::getID());
			UserPosts.push_back(post);
			string currentUserID = CommonClass::getID();
			int userID = idToNum(1, currentUserID) - 1;
			Users[userID]->addPost(post->getID());
		}
		else {
			Post* post = new Post(description, nullptr, 0);
			post->setOwnerID(CommonClass::getID());
			UserPosts.push_back(post);						//Added post to main vector to display in file
			string currentUserID = CommonClass::getID();
			int userID = idToNum(1, currentUserID) - 1;
			Users[userID]->addPost(post->getID());			//Added post's address to User's posts vector
			cin.ignore(256, '\n');
		}	
	}
	void likePage(string& pageID, int& totalPages, vector <Page*>& Pages) {
		if (pageID[0] != 'p') {
			cout << "The given Page ID is invalid" << endl;
			return;
		}
		bool duplicate = false;
		for (int i = 0; i < totalPages; i++) {
			if (likedPages.size() > 0 && likedPages[i] == pageID) {
				duplicate = true;
				cout << "Can not be added to liked pages since it already is there" << endl;
				return;
			}
		}
		if (!duplicate) {
			likedPages.push_back(pageID);
			int index = idToNum(1, pageID) - 1;
			Pages[index]->incLikes();
			cout << "Page added to liked pages successfully" << endl;
		}	
	}
	void addFriend(string& friendID, int& totalUsers) {
		if (friendID[0] != 'u') {
			cout << "The given User ID is invalid" << endl;
			return;
		}
		bool duplicate = false;
		for (int i = 0; i < friends.size(); i++) {
			if (friends[i] == friendID) {
				duplicate = true;
				cout << friendID << " is already your friend" << endl;
				return;
			}
		}
		if (friendID != getID()) {
			if (idToNum(1, friendID) <= totalUsers) {
				friends.push_back(friendID);
				cout << "Friend added successfully" << endl;
			}
			else {
				cout << "The given User ID is invalid" << endl;
			}
		}
		else {
			cout << "You can not friend yourself" << endl;
		}
	}
	void viewTimeline(vector <Post*> UserPosts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
		vector <string> posts = getPosts();
		cout << getName() << " | Timeline" << endl;
		for (int i = 0; i < posts.size(); i++) {
			int index = idToNum(2, posts[i]) - 1;
			UserPosts[index]->showPost(Users, Pages, Comments);
		}
	}
};

//Class Post's Methods' Definitions
Post::Post(string description, Activity* activity, int author) : description(description), activity(activity) {
	datePosted = getCurrentDate();
	if (author == 0) {										//	0->Userpost		1->Pagepost
		postID = "up" + to_string(currentID++);
	}
	else {
		postID = "pp" + to_string(currentID++);
	}
}
string Post::getID() {
	return postID;
}
string Post::getOwnerID() {
	return ownerID;
}
vector <string> Post::getLikedBy() {
	return likedBy;
}
void Post::addLikedBy(string liker) {
	likedBy.push_back(liker);
	incLikes();
}
int Post::getCommentCount() {
	return commentsCount;
}
int Post::getLikesCount() {
	return likes;
}
void Post::setOwnerID(string id) {
	ownerID = id;
}
void Post::addComment(string commentID) {
	comments.push_back(commentID);
}
void Post::incLikes() {
	if (likes < 10) {
		likes++;
	}
}
void Post::incComments() {
	if (commentsCount < 10) {
		commentsCount++;
	}
}
void Post::showPost(vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
	int index = idToNum(1, ownerID) - 1;
	if (ownerID[0] == 'u') {
		cout << "---" << Users[index]->getName();
	}
	else {
		cout << "---" << Pages[index]->getName();
	}
	if (activity == nullptr) {
		cout << " shared \"" << description << "\"" << endl;
	}
	else {
		cout << activity->getValue() << endl << "\"" << description << "\"" << endl;
	}
	for (int i = 0; i < comments.size(); i++) {
		int index = idToNum(1, comments[i]) - 1;
		Comments[index]->print(Users, Pages);
	}
}

//Class Comment's Methods' Definitions
Comment::Comment(string postID, string posterID, string text) : commentID("c" + to_string(currentID++)), postID(postID), posterID(posterID), text(text) {}
string Comment::getPostID() {
	return postID;
}
string Comment::getCommentID() {
	return commentID;
}
void Comment::print(vector <User*> Users, vector <Page*> Pages) {
	int index = idToNum(1, posterID) - 1;
	if (posterID[0] == 'u') {
		cout << Users[index]->getName() << " wrote: " << text << endl;
	}
	else {
		cout << Pages[index]->getName() << " wrote: " << text << endl;
	}
}

//Static Data
int Page::currentID = 1;
int User::currentID = 1;
int Post::currentID = 1;
int Comment::currentID = 1;

//Helper Functions
int idToNum(int start, string id) {
	string index;
	for (int i = start; i < id.length(); i++) {
		index[i - start] = id[i];
	}
	return stoi(index);
}

void showLikedBy(string postID, vector <User*>& Users, vector <Page*>& Pages, vector <Post*>& UserPosts, vector <Post*>& PagePosts) {
	cout << "----------------------------------------------------------" << endl;
	cout << "Post Liked By: " << endl;
	int size;
	int index = idToNum(2, postID) - 1;
	vector <string> likedBy;
	int user;
	if (postID[0] == 'u') {
		likedBy = UserPosts[index]->getLikedBy();
		size = likedBy.size();
	}
	else {
		likedBy = PagePosts[index]->getLikedBy();
		size = likedBy.size();
	}
	for (int i = 0; i < size; i++) {
		int currentIndex = idToNum(1, likedBy[i]) - 1;
		if (likedBy[i][0] == 'u') {
			cout << likedBy[i] << "-" << Users[currentIndex]->getName() << endl;
		}
		else {
			cout << likedBy[i] << "-" << Pages[currentIndex]->getName() << endl;
		}			
	}
	cout << "----------------------------------------------------------" << endl;
}

string getCurrentDate() {
	// Get the current system time point
	auto now = std::chrono::system_clock::now();

	// Convert system time to time_t
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// Convert time_t to a string representation
	char dateString[11]; // DD/MM/YYYY + '\0'
	struct tm timeinfo;
	localtime_s(&timeinfo, &currentTime);
	std::strftime(dateString, sizeof(dateString), "%d/%m/%Y", &timeinfo);

	// Return the current system date
	return dateString;
}

void createUser(string userName, vector <User*>& Users) {
	User* user = new User(userName);
	Users.push_back(user);
	cout << "User " << userName << " created successfully with userID: " << user->getID() << endl;
}

//Driver Module
int main() { 
	vector <User*> Users;
	vector <Page*> Pages;
	vector <Post*> UserPosts;
	vector <Post*> PagePosts;
	vector <Comment*> Comments;

	//testing users
	createUser("Muhaimin", Users);
	createUser("Salman", Users);
	User* u = Users[0];
	User* uu = Users[1];
	string id = uu->getID();
	int users = Users.size();
	u->addFriend(id, users);
	u->printUser(Users, Pages);
	u->createPage("Al Jazeera", Pages);
	string pageID = "p1";
	int pages = Pages.size();
	uu->likePage(pageID, pages, Pages);
	u->likePage(pageID, pages, Pages);
	cout << "Likes: " << Pages[0]->getLikes() << endl;
	uu->showLikedPages(Pages);
	uu->printUser(Users, Pages);
	u->printUser(Users, Pages);
	Pages[0]->viewPage(PagePosts, Users, Pages, Comments);
	u->createPost(UserPosts, Users);
	u->likePost("up1", UserPosts, PagePosts);
	uu->likePost("up1", UserPosts, PagePosts);
	u->comment("up1", "Wow", Comments, UserPosts, PagePosts);
	uu->comment("up1", "Wow", Comments, UserPosts, PagePosts);
	
	//testing pages
	Page* page = Pages[0];
	page->comment("up1", "Nice", Comments, UserPosts, PagePosts);
	page->likePost("up1", UserPosts, PagePosts);
	u->viewTimeline(UserPosts, Users, Pages, Comments);
	showLikedBy("up1", Users, Pages, UserPosts, PagePosts);
	//page->createPost(PagePosts, Pages);
	//page->createPost(PagePosts, Pages);
	//page->createPost(PagePosts, Pages);
	//page->createPost(PagePosts, Pages);
	//page->viewPage(PagePosts, Users, Pages, Comments);
	








	for (User* user : Users) {
		delete user;
	}
	for (Page* page : Pages) {
		delete page;
	}
	for (Post* post : UserPosts) {
		delete post;
	}
	for (Post* post : PagePosts) {
		delete post;
	}
	for (Comment* comment : Comments) {
		delete comment;
	}
}