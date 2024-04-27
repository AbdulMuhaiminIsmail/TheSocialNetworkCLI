#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/UserClass.hpp"

User::User(string userName) : Entity("u" + to_string(currentID++), userName) {}
string User::getID() {
	return Entity::getID();
}
string User::getName() {
	return Entity::getName();
}
void User::printUser(vector <User*> Users, vector <Page*> Pages) {
	cout << "Name: " << getName() << endl;
	cout << "UserID: " << getID() << endl;
	showFriends(Users);
	showLikedPages(Pages);
	showOwnedPages(Pages);
}
void User::showOwnedPages(vector <Page*>& Pages) {
	cout << "----------------------------------------------------------" << endl;
	cout << getName() << " - Owned Pages" << endl << endl;
	for (int i = 0; i < ownedPages.size(); i++) {
		int currentPageIndex = idToNum(1, ownedPages[i]) - 1;
		cout << ownedPages[i] << "-" << Pages[currentPageIndex]->getName() << endl;
	}
	cout << "----------------------------------------------------------" << endl;
}
void User::showLikedPages(vector <Page*>& Pages) {
	cout << "----------------------------------------------------------" << endl;
	cout << getName() << " - Liked Pages" << endl << endl;
	for (int i = 0; i < likedPages.size(); i++) {
		int currentPageIndex = idToNum(1, likedPages[i]) - 1;
		cout << likedPages[i] << "-" << Pages[currentPageIndex]->getName() << endl;
	}
	cout << "----------------------------------------------------------" << endl;
}
void User::showFriends(vector <User*>& Users) {
	cout << "----------------------------------------------------------" << endl;
	cout << getName() << " - Friends List" << endl << endl;
	for (int i = 0; i < friends.size(); i++) {
		int currentUserIndex = idToNum(1, friends[i]) - 1;
		cout << friends[i] << "-" << Users[currentUserIndex]->getName() << endl;
	}
	cout << "----------------------------------------------------------" << endl;
}
void User::createPage(string title, vector <Page*>& Pages) {			//page comment shall be analogous
	Page* page = new Page(Entity::getID(), title);
	ownedPages.push_back(page->getID());
	Pages.push_back(page);
	cout << "Page created with name " << title << " and id " << page->getID() << endl;
}
void User::likePost(string postID, vector <Post*>& UserPosts, vector <Post*>& PagePosts) {
	int index = idToNum(2, postID) - 1;
	if (postID[0] == 'u') {
		if (UserPosts[index]->getLikesCount() < 10) {
			UserPosts[index]->addLikedBy(Entity::getID());
		}
		else {
			cout << "This post already has 10 comments, no further comments are allowed" << endl;
		}
	}
	else if (postID[0] == 'p') {
		if (PagePosts[index]->getLikesCount() < 10) {
			PagePosts[index]->addLikedBy(Entity::getID());
		}
		else {
			cout << "This post already has 10 comments, no further comments are allowed" << endl;
		}
	}
	else {
		cout << "The given post id is invalid" << endl;
	}
}
void User::comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& UserPosts, vector <Post*>& PagePosts) {
	int index = idToNum(2, postID) - 1;
	if (postID[0] == 'u') {
		if (UserPosts[index]->getCommentCount() < 10) {
			Comment* comment = new Comment(postID, Entity::getID(), text);
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
			Comment* comment = new Comment(postID, Entity::getID(), text);
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
void User::createPost(vector <Post*>& UserPosts, vector <User*>& Users) {
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
		post->setOwnerID(Entity::getID());
		UserPosts.push_back(post);
		string currentUserID = Entity::getID();
		int userID = idToNum(1, currentUserID) - 1;
		Users[userID]->addPost(post->getID());
	}
	else {
		Post* post = new Post(description, nullptr, 0);
		post->setOwnerID(Entity::getID());
		UserPosts.push_back(post);						//Added post to main vector to display in file
		string currentUserID = Entity::getID();
		int userID = idToNum(1, currentUserID) - 1;
		Users[userID]->addPost(post->getID());			//Added post's address to User's posts vector
		cin.ignore(256, '\n');
	}
}
void User::likePage(string pageID, int& totalPages, vector <Page*>& Pages) {
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
void User::addFriend(string& friendID, int& totalUsers) {
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
void User::viewTimeline(vector <Post*> UserPosts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
	vector <string> posts = getPosts();
	cout << getName() << " | Timeline" << endl;
	for (int i = 0; i < posts.size(); i++) {
		int index = idToNum(2, posts[i]) - 1;
		UserPosts[index]->showPost(Users, Pages, Comments);
	}
}
void User::viewHome(vector <Post*> UserPosts, vector <User*> Users, vector <Post*> PagePosts, vector <Page*> Pages, vector <Comment*> Comments) {
	cout << getName() << "-Home Page" << endl;
	Date currentDate = getCurrentDate();
	for (int i = 0; i < friends.size(); i++)
	{
		int index = idToNum(1, friends[i]) - 1;
		vector<string> posts = Users[index]->getPosts();
		for (int j = 0; j < posts.size(); j++)
		{
			int index2 = idToNum(2, posts[j]) - 1;
			Date datePosted = UserPosts[index2]->getDatePosted();
			if(oneDayDiff(currentDate, datePosted))
				UserPosts[index2]->showPost(Users, Pages, Comments);
		}	
	}	

	for (int i = 0; i < likedPages.size(); i++)
	{
		int index = idToNum(1, likedPages[i]) - 1;
		vector<string> posts = Pages[index]->getPosts();
		for (int j = 0; j < posts.size(); j++)
		{
			int index2 = idToNum(2, posts[j]) - 1;
			Date datePosted = PagePosts[index2]->getDatePosted();
			if(oneDayDiff(currentDate, datePosted))
				PagePosts[index2]->showPost(Users, Pages, Comments);
		}	
	}	

}
//Static Data
int User::currentID = 1;