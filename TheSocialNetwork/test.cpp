//Header Files
#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<ctime>
#include<fstream>
using namespace std;

//Helper Functions
int idToNum(int start, string id) {
	string index;
	for (int i = start; i < id.length(); i++) {
		index[i - start] = id[i];
	}
	return stoi(index);
}

string getDate() {
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

//Forward Declarations
class Activity;
class CommonClass;
class Page;
class User;
class Comment;
class Post;

//Classes
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
				cin >> temp;
				value = " is feeling " + temp;
			}
			else if (type == 2) {
				cout << "What are you thinking? (Life/Future/Meaning of Life/Other)" << endl;
				cin >> temp;
				value = " is thinking about " + temp;
			}
			else if (type == 3) {
				cout << "What are you making? (Money/Arts/Memories/Other)" << endl;
				cin >> temp;
				value = " is making " + temp;
			}
			else if (type == 4) {
				cout << "What are you celebrating? (Birthday/Halloween/Success/Other)" << endl;
				cin >> temp;
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
	void incLikes();
	void incComments();
	//void showLikedBy(vector <User*>& Users, vector <Page*>& Pages) {
	//	cout << "----------------------------------------------------------" << endl;
	//	cout << "Post Liked By: " << endl;
	//	for (int i = 0; i < likedBy.size(); i++) {
	//		int currentIndex = idToNum(1, likedBy[i]) - 1;
	//		if (likedBy[i][0] == 'u') {
	//			cout << likedBy[i] << "-" << Users[currentIndex]->getName() << endl;
	//		}
	//		else if (likedBy[i][0] == 'p') {
	//			cout << likedBy[i] << "-" << Pages[currentIndex]->getName() << endl;
	//		}			
	//	}
	//	cout << "----------------------------------------------------------" << endl;
	//}
	void showPost(vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments);
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
		likes++;
	}
	void viewPage(vector <Post*> PagePosts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
		vector <string> posts = getPosts();
		for (int i = 0; i < posts.size(); i++) {
			int index = idToNum(2, posts[i]);
			PagePosts[index]->showPost(Users, Pages, Comments);
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
	void createPage(string& title, vector <Page*>& Pages) {			//page comment shall be analogous
		Page* page = new Page(CommonClass::getID(), title);
		ownedPages.push_back(page->getID());
		Pages.push_back(page);
		cout << "Page created with name " << title << " and id " << page->getID() << endl;
	}
	void createPost(vector <Post*>& UserPosts, vector <User*>& Users) {
		int hasActivity, type;
		string description;
		cout << "What is the description of the post? ";
		cin >> description;
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
			Activity* activity = new Activity(type);
			activity->setActivity();
			Post* post = new Post(description, activity, 0);
		}
		Post* post = new Post(description, nullptr, 0);
		UserPosts.push_back(post);						//Added post to main vector to display in file
		string currentUserID = CommonClass::getID();
		int userID = idToNum(1, currentUserID) - 1;
		Users[userID]->addPost(post->getID());			//Added post's address to User's posts vector
	}
	void likePage(string& pageID, int& totalPages, vector <Page*>& Pages) {
		if (pageID[0] != 'p') {
			cout << "The given Page ID is invalid" << endl;
			return;
		}
		bool duplicate = false;
		for (int i = 0; i < totalPages; i++) {
			if (likedPages[i] == pageID) {
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
};
class Comment {
	string postID; //Stores the ID of the original Post
	string posterID; //Stores the ID of Page or User who commented
	string text; //Stores the text of the comment writen
public:
	Comment(string postID, string posterID, string text);
	string getPostID();
	void print(vector <User*> Users, vector <Page*> Pages);
};

//Class Post's Methods' Definitions
Post::Post(string description, Activity* activity, int author) : description(description), activity(activity) {
	datePosted = getDate();
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
Comment::Comment(string postID, string posterID, string text) : postID(postID), posterID(posterID), text(text) {}
string Comment::getPostID() {
	return postID;
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

//Driver Module
int main() { 
	vector <User*> Users;
	vector <Page*> Pages;
	vector <Post*> UserPosts;
	vector <Post*> PagePosts;
	vector <Comment*> Comments;

	createUser("Muhaimin", Users);
	createUser("Faheem", Users);

	User* muhaimin = Users[0];
	User* faheem = Users[1];
	muhaimin->printUser(Users, Pages);
	string id = "u7";
	int size = Users.size();
	muhaimin->addFriend(id, size);
	muhaimin->printUser(Users, Pages);
	muhaimin->addFriend(id, size);
	faheem->printUser(Users, Pages);
	faheem->addFriend(id, size);
	faheem->printUser(Users, Pages);

	cout << getDate();

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
}