#include"../Headers/UserClass.hpp"
User::User() : Entity("u" + to_string(currentID++)) {}
User::User(string userName) : Entity("u" + to_string(currentID++), userName) {}
void User::setID(string id) {
	Entity::setID(id);
}
void User::setName(string name) {
	Entity::setName(name);
}
void User::setPosts(vector <string> posts) {
	Entity::setPosts(posts);	
}
void User::setFriends(vector <string> friends) {
	for (int i = 0; i < friends.size(); i++)
	{
		this->friends.push_back(friends[i]);
	}
}
void User::setOwnedPages(vector <string> ownedPages) {
	for (int i = 0; i < ownedPages.size(); i++)
	{
		this->ownedPages.push_back(ownedPages[i]);
	}
}
void User::setLikedPages(vector <string> likedPages) {
	for (int i = 0; i < likedPages.size(); i++)
	{
		this->likedPages.push_back(likedPages[i]);
	}
}
string User::getID() const {
	return Entity::getID();
}
string User::getName() const {
	return Entity::getName();
}
vector <string> User::getPosts() const {
	return Entity::getPosts();
}
vector <string> User::getFriends() const {
	return friends;
}
vector <string> User::getOwnedPages() const {
	return ownedPages;
}
vector <string> User::getLikedPages() const {
	return likedPages;
}
void User::printUser(vector <User*> Users, vector <Page*> Pages) {
	cout << "Name: " << getName() << endl;
	cout << "UserID: " << getID() << endl;
	cout << "Posts: \t";
	vector <string> posts = getPosts();
	for (int i = 0; i < posts.size(); i++) {
		cout << posts[i] << "\t";
	}
	cout << endl;
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
	cout << endl << "Page " << title << " created successfully with page ID - " << page->getID() << endl << endl;
}
void User::createPost(vector<Post*>& Posts) {
	int hasActivity, type;
	string description;
	cin.ignore();
	cout << "What is the description of the post? ";
	getline(cin, description);
	//description = "\n\t\t" + description; //To make the output in five lines
	cout << "Do you want to add any activity? (0.No/1.Yes) ";
	cin >> hasActivity;
	if (hasActivity) {
		do {
			cout << "What kind of activity is this? (1.Feeling/2.Thinking/3.Making/4.Celebrating) ";
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
		Posts.push_back(post);
		addPost(post->getID());
		cout << endl << "Post created successfully with post ID - " << post->getID() << endl << endl;
	}
	else {
		Post* post = new Post(description, nullptr, 0);
		post->setOwnerID(Entity::getID());
		Posts.push_back(post);						//Added post to main vector to display in file
		addPost(post->getID());					//Added post's address to User's posts vector
		cin.ignore(256, '\n');
		cout << endl << "Post created successfully with post ID - " << post->getID() << endl << endl;
	}
}
void User::likePost(string postID, vector <Post*>& Posts) {
	int index = idToNum(4, postID) - 1;
	if (index >= Posts.size() || index < 0) {
		cout << endl << "The given post id is invalid" << endl;
		return;
	}
	vector <string> likers = Posts[index]->getLikedBy();
	for (int i = 0; i < likers.size(); i++) {
		if (likers[i] == Entity::getID()) {
			cout << endl << "You have already liked this post, can't double like it!" << endl;
			return;
		}
	}
	if (Posts[index]->getLikesCount() < 10) {
		Posts[index]->addLikedBy(Entity::getID());
	}
	else {
		cout << endl << "This post already has 10 likes, no further likes are allowed" << endl;
	}
}
void User::comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& Posts) {
	if (postID[4] < 48 || postID[4] > 57 || idToNum(4, postID) - 1 >= Posts.size() || idToNum(4, postID) - 1  < 0) {
		cout << "The given post id is invalid" << endl;
		return;
	}
	int index = idToNum(4, postID) - 1;
	if (Posts[index]->getCommentCount() < 10) {
		Comment* comment = new Comment(postID, Entity::getID(), text);
		Comments.push_back(comment);
		Posts[index]->addComment(comment->getCommentID());
		cout << endl << "Comment added to the post with comment ID - " << comment->getCommentID() << endl;
	}
	else {
		cout << "This post already has 10 comments, no further comments are allowed" << endl;
		return;
	}
}
void User::likePage(string pageID, vector <Page*>& Pages) {
	if (pageID[0] != 'p') {
		cout << "The given Page ID is invalid" << endl;
		return;
	}
	bool duplicate = false;
	for (int i = 0; i < Pages.size(); i++) {
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
void User::addFriend(string friendID, vector<User*> Users) {
	if (friendID[1] < 48 || friendID[1] > 57 || friendID[0] != 'u') {
		cout << "The given user ID is invalid" << endl << endl;
		return;
	}
	bool duplicate = false;
	for (int i = 0; i < friends.size(); i++) {
		if (friends[i] == friendID) {
			duplicate = true;
			cout << Users[idToNum(1, friendID) - 1]->getName() << " is already your friend" << endl << endl;
			return;
		}
	}
	if (friendID != getID()) {
		if (idToNum(1, friendID)  <= Users.size()) {
			friends.push_back(friendID);
			cout << "Friend added successfully" << endl << endl;
		}
		else {
			cout << "The user with given ID does not exist" << endl << endl;
		}
	}
	else {
		cout << "You can not friend yourself" << endl << endl;
	}
}
void User::viewTimeline(vector <Post*> Posts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
	vector <string> posts = getPosts();
	cout << "----------------------------------------------------------" << endl;
	cout << getName() << " | Timeline" << endl;
	for (int i = 0; i < posts.size(); i++) {
		int index = idToNum(4, posts[i]) - 1;
		Posts[index]->showPost(Users, Pages, Comments);
	}
	cout << "\n----------------------------------------------------------" << endl;
}
void User::viewHome(vector <Post*>Posts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
	cout << "----------------------------------------------------------" << endl;
	cout << getName() << " | Home Page" << endl;
	//Friends' Posts
	for (int i = 0; i < friends.size(); i++)
	{
		int index = idToNum(1, friends[i]) - 1;
		vector<string> posts = Users[index]->getPosts();
		for (int j = 0; j < posts.size(); j++)
		{
			int index2 = idToNum(4, posts[j]) - 1;
			Date datePosted = Posts[index2]->getDatePosted();
			Date currentDate = *getCurrentDate();
			if (oneDayDiff(currentDate, datePosted))
				Posts[index2]->showPost(Users, Pages, Comments);
		}
	}
	//Liked Pages' Posts
	for (int i = 0; i < likedPages.size(); i++)
	{
		int index = idToNum(1, likedPages[i]) - 1;
		vector<string> posts = Pages[index]->getPosts();
		for (int j = 0; j < posts.size(); j++)
		{
			int index2 = idToNum(4, posts[j]) - 1;
			Date datePosted = Posts[index2]->getDatePosted();
			Date currentDate = *getCurrentDate();
			if (oneDayDiff(currentDate, datePosted))
				Posts[index2]->showPost(Users, Pages, Comments);
		}
	}
	cout << "----------------------------------------------------------" << endl;
}
void User::shareMemory(string postID, string text, vector<Post*>& Posts, vector<User*>& Users) {
	bool ownPost = false;
	vector <string> posts = getPosts();
	for (int i = 0; i < posts.size();i++) {
		if (posts[i] == postID) {
			ownPost = true;
			Post* source = Posts[idToNum(4, postID) - 1];
			string timeAgo = getTimeAgo(source);
			string description = source->getDescription();
			Date date = source->getDatePosted();
			string userName = getName();
			Activity* activity = source->getActivity();
			string memory;
			if (activity != nullptr)
				memory = "~~~ " + userName + " shared a memory ~~~ ...(" + getCurrentDate()->stringDate() + ")\n\"" + text + "\"\n\t" + timeAgo + "\n--- " + userName + activity->getValue() + "\n\t\"" + description + "\" ...(" + date.stringDate() + ")";
			else
				memory = "~~~ " + userName + " shared a memory ~~~ ...(" + getCurrentDate()->stringDate() + ")\n\"" + text + "\"\n\t" + timeAgo + "\n--- " + userName + " shared \n\t\"" + description + "\" ...(" + date.stringDate() + ")";
			Post* post = new Post(memory, nullptr, 1);
			post->setOwnerID(Entity::getID());
			Posts.push_back(post);
			Users[idToNum(1, Entity::getID()) - 1]->addPost(post->getID());
			cout << endl << "Memory created successfully with post ID - " << post->getID() << endl << endl;
		}
	}
	if (!ownPost) {
		cout << "You can share memories, only of your own posts!" << endl << endl;
		return;
	}
}
void User::seeMemories(vector<User*> Users, vector<Post*> Posts, vector<Page*> Pages, vector<Comment*> Comments) {
	//show post on same date in following years
	int introWritten = 0;
	vector <string> posts = getPosts();
	for (int i = 0; i < posts.size(); i++) {
		Date date = Posts[idToNum(4, posts[i]) - 1]->getDatePosted();
		Date currentDate = *getCurrentDate();
		if (currentDate.year - date.year > 0 && currentDate.month == date.month && currentDate.day == date.day) {
			if (!introWritten) {
				cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n\nOn this Day\n";
				cout << getTimeAgo(Posts[idToNum(4, posts[i]) - 1]) << endl;
				Posts[idToNum(4, posts[i]) - 1]->showPost(Users, Pages, Comments);
				introWritten++;
			}
			else {
				cout << getTimeAgo(Posts[idToNum(4, posts[i]) - 1]) << endl;
				Posts[idToNum(4, posts[i]) - 1]->showPost(Users, Pages, Comments);
			}
		}
	}
	if (!introWritten) {
		cout << "There are no memories right now, check back later." << endl << endl;
	}
}

//Static Data
int User::currentID = 1;