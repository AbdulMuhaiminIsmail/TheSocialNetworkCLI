//#include<iostream>
//#include<string>
//#include<vector>
//using namespace std;
//
////Classes
//
//class Activity {
//	int type;
//	string value;	
//public:
//	Activity(int type = 0) : type(type) {
//		if (type == 1) {
//			cout << "What are you feeling? (Happy/Sad/Excited/Other)" << endl;
//		}
//		else if (type == 2) {
//			cout << "What are you thinking? (Life/Future/Meaning of Life/Other)" << endl;
//		}
//		else if (type == 3) {
//			cout << "What are you making? (Money/Arts/Memories/Other)" << endl;
//		}
//		else if (type == 4) {
//			cout << "What are you celebrating? (Birthday/Halloween/Success/Other)" << endl;
//		}
//		cin >> value;
//		if (type == 0) {
//			cout << "Invalid Type Selected" << endl;
//		}
//	}
//	void print() {
//
//	}
//};
//
//class Date {
//	int date;
//	int month;
//	int year;
//public:
//	Date(int date = 0, int month = 0, int year = 0) : date(date), month(month), year(year) {}
//	void print() {
//		if (date == 0 || date > 31 || month == 0 || month > 12 || year <= 0) {
//			cout << "Date is invalid or unspecified" << endl;
//		}
//		else {
//			cout << date << "/" << month << "/" << year << endl;
//		}
//	}
//};
//
//class Post {
//	static int currentID;
//	int likes; //Stores the number of likes on the post (10 at max)
//	int comments; //Stores the number of comments on the post (10 at max) 
//	string postID; //Stores the ID of the post [prefix: "up" for user post "pp" for page post]
//	string description; //Stores the text description of the post
//	vector <string> likedBy; //Stores the IDs of the Users or Pages who liked the post
//	Date datePosted; //Stores the date on which the post was created [DD/MM/YYYY]
//	Activity activity; //Stores the associated activity with the post
//public:
//	void showLikedBy();
//};
//
//class CommonClass {
//	string id; //Stores the userID with "u" as prefix or pageID with "p" as prefix
//	string name; //Stores the full name of page/user
//	vector <string> posts; //Stores the ids of all posts
//public:
//	CommonClass(string id, string name) : id(id), name(name) {}
//};
//
//class Page : public CommonClass {
//	static int currentID; //Keeps track of the current page
//	int likes = 0; //Stores the number of likes on the page
//	string ownerID; //Stores the ID of the owner of the page
//public:
//	Page(string ownerID, string title) : CommonClass("p" + currentID++, title) , ownerID(ownerID) {}
//};
//
//class User : public CommonClass {
//	static int currentID; //Keeps track of the current user
//	vector <string> friends; //Stores the userIDs of other users (friends)
//	vector <string> ownedPages; //Stores the ids of owned pages by the user
//	vector <string> likedPages; //Stores the ids of all liked pages
//public:
//	User(string userName) : CommonClass("u" + currentID++, userName) {}
//	void viewHome(); //Displays posts of all friends and liked pages shared in the last 24 Hours
//	void likePost(string postID); //Takes the postID and likes the post
//};
//
//class Memory : public Post {
//	Post* source; //Source is pointer storing the address of the original post
//};
//
//class Comment {
//	string postID; //Stores the ID of the original Post
//	string posterID; //Stores the ID of Page or User who commented
//	string text; //Stores the text of the comment writen
//};
//
//
////Requried Functions
//
////User Functions
//void setCurrentUser(string& userID); //Takes userID and sets current user
//void likePost(string& userID, string& postID); //Takes the postID and likes the post
//void viewHome(string& userID); //Displays posts of all friends and liked pages shared in the last 24 Hours
//void viewTimeline(string& userID); //Displays username and all of his/her posts
//void comment(string& postID, string& text); //Writes given comment to a post if comments are < 10
//void shareMemory(string& postID, string& text); //Shares a memory of a post with a text
//void viewFriendsList(string& userID); //Displays list of all friends of a user
////Post Functions
//void viewLikedBy(string& postID); //Takes a postID and shows list of people and pages who liked it
//void viewPost(string& postID); //Shows the post with its comments by its ID
////Page Functions
//void viewPage(string& pageID); //Displays all posts of a page
//
//
////Functions' Definitions
//
//
//
//
//
//
////Initialization of Static Data
//
//int User::currentID = 1;
//int Page::currentID = 1;
//int Post::currentID = 1;
//
////Driver Module : Reads all the existing data from files and stores them into variables and vectors for further functionality
//
//void DriverModule() {
//	int totalUsers = 0;
//	int totalPages = 0;
//	vector <User> Users;
//	vector <Page> Pages;
//}
//
////Entry Point
//
//int main() {
//	cout << "Hello";
//	Date date(18, 8, 2005);
//	Date date2;
//	date.print();
//	date2.print();
//}
//
