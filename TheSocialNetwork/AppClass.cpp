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
	string currentUser = "";
public:
	void run()
	{
		//Import Data from Files
		importData();
		//Interaction Main Menu
		mainMenu();
		//Exporting Data to Files
		exportData();
		//Deallocating Memory
		deallocMem();
	}
	void mainMenu() {
		int choice;

		do {

			// Clear the screen
			cout << "\033[2J\033[1;1H"; 

			// Print title
			printTitle();

			// Display menu options
			printMenu();

			// Get user choice
			cout << " \t\t\t\t\t\t\t\t\t\t    Enter your choice: ";

			// If character is entered (cin returns 0 --> fail)
			if (!(cin >> choice)) {
				cin.clear();
				choice = -2;
			}

			// If current user not selected
			if (choice != 0 && choice != 1 && choice != 2 && currentUser == "" && (choice > -1 && choice < 20)) {
				choice = -1;
			}

			// Required variables
			string userID, postID, pageTitle, pageID, commentText, text, username;

			// Perform action based on user choice
			switch (choice) {
			case -2:
				cout << endl << " \t\t\t\t\t\t\t\t    Entering characters is not allowed, use numbers only!" << endl;
				break;
			case -1:
				cout << "     \t\t\t\t\t\tAccessing this functionality, without setting up a user first, is an act of absurdity!" << endl;
				break;
			case 1:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter User ID: ";
				cin >> userID;
				setCurrentUser(userID);
				break;
			case 2:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter User Name: ";
				cin.ignore();
				getline(cin, username);
				createUser(username);
				break;
			case 3:
				viewHome();
				break;
			case 4:
				viewTimeline();
				break;
			case 5:
				viewOwnedPages();
				break;
			case 6:
				viewLikedPages();
				break;
			case 7:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Page Title: ";
				cin.ignore();
				getline(cin, pageTitle);
				createPage(pageTitle);
				break;
			case 8:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Page ID: ";
				cin >> pageID;
				viewPage(pageID);
				break;
			case 9:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Page ID: ";
				cin >> pageID;
				likePage(pageID);
				break;
			case 10:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Page ID: ";
				cin >> pageID;
				viewPageLikes(pageID);
				break;
			case 11:
				createPost();
				break;
			case 12:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Post ID: ";
				cin >> postID;
				viewPost(postID);
				break;
			case 13:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Post ID: ";
				cin >> postID;
				likePost(postID);
				break;
			case 14:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Post ID: ";
				cin >> postID;
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Comment: ";
				cin.ignore();
				getline(cin, commentText);
				commentPost(postID, commentText);
				break;
			case 15:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Post ID: ";
				cin >> postID;
				showLikers(postID);
				break;
			case 16:
				seeYourMemories();
				break;
			case 17:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Post ID: ";
				cin >> postID;
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter Text: ";
				cin.ignore();
				getline(cin, text);
				shareMemory(postID, text);
				break;
			case 18:
				viewFriends();
				break;
			case 19:
				cout << " \t\t\t\t\t\t\t\t\t\t    Enter User ID: ";
				cin >> userID;
				addFriend(userID);
				break;
			case 0:
				cout << " \t\t\t\t\t\t\t      Exporting the data, closing the files, exiting program, success!" << endl;
				break;
			default:
				cout << " \t\t\t\t\t\t\t      This option is not available, as it is out of the allowed range!" << endl;
				break;
			}

			// Wait for user input before clearing the screen
			cout << "\t\t\t\t\t\t\t\t\t      Press Enter to clear the screen!";
			cin.ignore(); // Ignore any leftover newline characters
			cin.get(); // Wait for Enter key press

		} while (choice != 0);
	}
	void printTitle() {
		std::cout << "\t\t\t\t\t _____   _              ____                   _           _   _   _          _                               _    " << std::endl;
		std::cout << "\t\t\t\t\t|_   _| | |__     ___  / ___|    ___     ___  (_)   __ _  | | | \\ | |   ___  | |_  __      __   ___    _ __  | | __" << std::endl;
		std::cout << "\t\t\t\t\t  | |   |  _ \\   / _ \\ \\___ \\   / _ \\   / __| | |  / _` | | | |  \\| |  / _ \\ | __| \\ \\ /\\ / /  / _ \\  | '__| | |/ /" << std::endl;
		std::cout << "\t\t\t\t\t  | |   | | | |  | __/  ___) | | (_) | | (__  | | | (_| | | | | |\\  |  | __/ | |_   \\ V  V /  | (_) | | |    |   < " << std::endl;
		std::cout << "\t\t\t\t\t  |_|   |_| |_|  \\___| |____/   \\___/   \\___| |_|  \\__,_| |_| |_| \\_|  \\___| \\__|    \\_/\\_/    \\___/  |_|    |_|\\_\\" << std::endl;
		std::cout << "\t\t\t\t\t                                                                                                                    " << std::endl;
	}
	void printMenu() {
				std::cout << R"(
							  +---------------------------------------------------------------------+
							  |                                                                     |
							  |                           <<< Main Menu >>>                         |
							  |                                                                     |
							  |           User                         General                      |
							  |           ------------------           -------------------          |
							  |           1. Set/Switch User           3. View Home                 |
							  |           2. Create User               4. View Timeline             |
							  |                                                                     |
							  |           Pages                        Posts                        |
							  |           -------------------          -------------------          |
							  |           5. View Owned Pages          11. Create Post              |
							  |           6. View Liked Pages          12. View Post                |
							  |           7. Create Page               13. Like Post                |
							  |           8. View Page                 14. Comment Post             |
							  |           9. Like Page                 15. View Likers              |
							  |           10. View Likes                                            |
							  |                                                                     |
							  |           Memories                     Friends                      |
							  |           -------------------          -------------------          |
							  |           16. View Memories            18. View Friends             |
							  |           17. Share Memory             19. Add Friend               |
							  |                                                                     |
							  |				 0. Exit                                |
							  |                                                                     |
							  +---------------------------------------------------------------------+
			)" << std::endl;

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
				//Name
				string userName;
				usersFile.ignore();
				getline(usersFile,  userName);
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
				//Name
				string pageName;
				pagesFile.ignore();
				getline(pagesFile, pageName);
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
				//OwnerID
				string ownerID;
				postsFile >> ownerID;
				post->setOwnerID(ownerID);
				//Description
				string description;
				postsFile.ignore();
				getline(postsFile, description);
				if (description[0] != '~') {
					post->setDescription(description);
				}
				else {
					string memoryDescription = description + '\n';
					string line1, line2, line3, line4;
					getline(postsFile, line1);
					getline(postsFile, line2);
					getline(postsFile, line3);
					getline(postsFile, line4);
					memoryDescription = description + "\n" + line1 + "\n" + line2 + "\n" + line3 + "\n"  + line4;
					post->setDescription(memoryDescription);
				}
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
					postsFile.ignore();
					getline(postsFile, value);
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
				post->setComments(comments);
				//Likers
				vector <string> likedBy;
				for (int i = 0; i < totalLikes; i++)
				{
					string currentLiker;
					postsFile >> currentLiker;
					likedBy.push_back(currentLiker);
				}
				post->setLikedBy(likedBy);
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
				commentsFile.ignore();
				getline(commentsFile, text);
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
				//Name
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
				//Name
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
				//OwnerID, Likes, Comments, isMemory, Description
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
				//PostID, PosterID, Text
				commentsFile << Comments[i]->getPostID() << endl;
				commentsFile << Comments[i]->getPosterID() << endl;
				commentsFile << Comments[i]->getText() << endl;
			}
			commentsFile.close();
		}
	}
	void createUser(string userName) {
		if (userName != "" && userName != " ") {
			User* user = new User(userName);
			Users.push_back(user);
			cout << " \t\t\t\t\t\t\t\t\tUser " << userName << " created successfully with user ID -  " << user->getID() << endl;
		}
		else {
			cout << " \t\t\t\t\t\t\t\t\t     You must enter a name for the user!" << endl;
		}
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
		int poster;
		cout << " \t\t\t\t\t\t\t\t\t   Do you want to post as a User or Page? (0.User/1.Page)";
		if ((cin >> poster)) {
			int index = idToNum(1, currentUser) - 1;
			if (poster == 0) {
				cin.ignore();
				Users[index]->createPost(Posts);
			}
			else if (poster == 1) {
				vector <string> ownedPages = Users[index]->getOwnedPages();
				if (ownedPages.size()) {
					string pageID;
					cout << " \t\t\t\t\t\t\t\t\t   Enter page ID from which you want to post: ";
					cin >> pageID;
					if (!(pageID[1] < 48 || pageID[1] > 57 || tolower(pageID[0]) != 'p')) {
						int index2 = idToNum(1, pageID) - 1;
						if (index2 < Pages.size()) {
							bool found = false;
							for (int i = 0; i < ownedPages.size(); i++) {
								if (pageID == ownedPages[i]) {
									found = true;
									cin.ignore();
									Pages[index2]->createPost(Posts, Pages);
									break;
								}
							}
							if (!found) {
								cout << " \t\t\t\t\t\t\t\t\t   The given page is not owned by you!" << endl;
							}
						}
						else {
							cout << " \t\t\t\t\t\t\t\t\t   The given page ID exceeds total number of pages!" << endl;
						}
					}
					else {
						cout << " \t\t\t\t\t\t\t\t\t   The given page ID is invalid!" << endl;
					}
				}
				else {
					cout << " \t\t\t\t\t\t\t\t\t   You do not have any pages of your own to post from!" << endl;
				}
			}
		}
		else {
			cin.clear();
			cout << " \t\t\t\t\t\t\t\t\t   Invalid option has been chosen!" << endl;
		}
	}
	void createPage(string title) {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->createPage(title, Pages);
	}
	void likePage(string pageID) {
		if (pageID[1] < 48 || pageID[1] > 57 || pageID[0] != 'p') {
			cout << " \t\t\t\t\t\t\t\t\t\tThe given page ID is invalid!" << endl << endl;
			return;
		}
		int index = idToNum(1, pageID) - 1;
		if (index >= Pages.size()) {
			cout << " \t\t\t\t\t\t\t\t\t\tThe page with given ID does not exist!" << endl << endl;
			return;
		}
		index = idToNum(1, currentUser) - 1;
		Users[index]->likePage(pageID, Pages);
	}
	void viewPageLikes(string pageID) {
		if (pageID[1] < 48 || pageID[1] > 57 || pageID[0] != 'p') {
			cout << " \t\t\t\t\t\t\t\t\t\tThe given page ID is invalid!" << endl << endl;
			return;
		}
		int index = idToNum(1, pageID) - 1;
		if (index >= Pages.size()) {
			cout << " \t\t\t\t\t\t\t\t\t\tThe page with given ID does not exist!" << endl << endl;
			return;
		}
		index = idToNum(1, pageID) - 1;
		cout << endl << " \t\t\t\t\t\t\t\t\t\t   Total Page Likes: " << Pages[index]->getLikes() << endl;
	}
	void setCurrentUser(string userID) {
		if (userID[1] < 48 || userID[1] > 57 || userID[0] != 'u') {
			cout << "\t\t\t\t\t\t\t\t\t\tThe given user ID is invalid" << endl << endl;
			return;
		}
		int index = idToNum(1, userID) - 1;
		if (index >= Users.size()) {
			cout << "\t\t\t\t\t\t\t\t\t   The user with given ID does not exist" << endl << endl;
		}
		else {
			currentUser = userID;
			cout << " \n\t\t\t\t\t\t\t\t   " << Users[index]->getName() << " (" << userID << ") successfully set as the current user!" << endl << endl;
		}
	}
	void viewOwnedPages() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->showOwnedPages(Pages);
	}
	void viewLikedPages() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->showLikedPages(Pages);
	}
	void viewHome() {
		int index = idToNum(1, currentUser) - 1;
		Users[index]->viewHome(Posts, Users, Pages, Comments);
	} 
	void likePost(string postID) {
		string temp;
		for (int i = 0; i < 4; i++) { temp += postID[i]; }
		if (postID.length() < 5 || temp != "post" || idToNum(4, postID) - 1 >= Posts.size()) {
			cout << " \t\t\t\t\t\t\t\t\t\tThe post with given ID does not exist" << endl << endl;
			return;
		}
		int index = idToNum(1, currentUser) - 1;
		Users[index]->likePost(postID, Posts);
	}
	void showLikers(string postID) {
		string temp;
		for (int i = 0; i < 4; i++) { temp += postID[i]; }
		if (postID.length() < 5 || temp != "post" || idToNum(4, postID) - 1 >= Posts.size()) {
			cout << " \t\t\t\t\t\t\t\t\t\tThe post with given ID does not exist" << endl << endl;
			return;
		}
		showLikedBy(postID, Users, Pages, Posts);
	}
	void commentPost(string postID, string comment) {
		string temp;
		for (int i = 0; i < 4; i++) { temp += postID[i]; }
		if (postID.length() < 5 || temp != "post" || idToNum(4, postID) - 1 >= Posts.size()) {
			cout << " \t\t\t\t\t\t\t\t\t\tThe post with given ID does not exist" << endl << endl;
			return;
		}
		int index = idToNum(1, currentUser) - 1;
		Users[index]->comment(postID, comment, Comments, Posts);
	}
	void viewPost(string postID) {
		string temp;
		for (int i = 0; i < 4; i++) { temp += postID[i]; }
		if (postID.length() < 5 || temp != "post" || idToNum(4, postID) - 1 >= Posts.size()) {
			cout << " \t\t\t\t\t\t\t\t\t\tThe post with given ID does not exist" << endl << endl;
			return;
		}
		int index = idToNum(4, postID) - 1;
		Posts[index]->showPost(Users, Pages, Comments);
	}
	void shareMemory(string postID, string text) {
		string temp;
		for (int i = 0; i < 4; i++) { temp += postID[i]; }
		if (postID.length() < 5 || temp != "post" || idToNum(4, postID) - 1 >= Posts.size()) {
			cout << " \t\t\t\t\t\t\t\t\t\tThe post with given ID does not exist" << endl << endl;
			return;
		}
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
		if (pageID[1] < 48 || pageID[1] > 57 || pageID[0] != 'p') {
			cout << " \t\t\t\t\t\t\t\t\t\tThe given page ID is invalid!" << endl << endl;
			return;
		}
		int index = idToNum(1, pageID) - 1;
		if (index >= Pages.size()) {
			cout << " \t\t\t\t\t\t\t\t\t\tThe page with given ID does not exist!" << endl << endl;
			return;
		}
		index = idToNum(1, pageID) - 1;
		Pages[index]->viewPage(Posts, Users, Pages, Comments);
	}
	void deallocMem() {
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

int main() {
	App app;
	app.run();
}   