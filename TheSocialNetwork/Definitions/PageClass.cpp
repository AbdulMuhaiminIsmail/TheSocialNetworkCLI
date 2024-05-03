#include"../Headers/PageClass.hpp"
Page::Page() : Entity() {}
Page::Page(string ownerID, string title) : Entity("p" + to_string(currentID++), title), ownerID(ownerID) { likes = 0; }
string Page::getID() {
	return Entity::getID();
}
string Page::getName() {
	return Entity::getName();
}
vector <string> Page::getPosts() {
	return Entity::getPosts();
}
string Page::getOwnerID() {
	return ownerID;
}
int Page::getLikes() {
	return likes;
}
void Page::setID(string ID) {
	Entity::setID(ID);
}

void Page::setName(string name) {
	Entity::setName(name);
}
void Page::setPosts(vector <string> posts) {
	Entity::setPosts(posts);
}

void Page::setLikes(int likes) {
	this->likes = likes;
}
void Page::setOwnerID(string ownerID) {
	this->ownerID = ownerID;
}
void Page::incLikes() {
	if (likes < 10) {
		likes++;
	}
	else {
		cout << "The page already has 10 likes, no more allowed" << endl;
	}
}
void Page::viewPage(vector <Post*> Posts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
	vector <string> posts = getPosts();
	cout << getName() << endl;
	for (int i = 0; i < posts.size(); i++) {
		int index = idToNum(4, posts[i]) - 1;
		Posts[index]->showPost(Users, Pages, Comments);
	}
}
void Page::likePost(string postID, vector <Post*>& Posts) {
	int index = idToNum(4, postID) - 1;
	if (index >= Posts.size() || index < 0) {
		cout << "The given post id is invalid" << endl;
		return;
	}
	if (Posts[index]->getLikesCount() < 10) {
		Posts[index]->addLikedBy(Entity::getID());
	}
	else {
		cout << "This post already has 10 comments, no further comments are allowed" << endl;
	}
}
void Page::comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& Posts) {
	int index = idToNum(4, postID) - 1;
	if (index >= Posts.size() || index < 0) {
		cout << "The given post id is invalid" << endl;
		return;
	}
	if (Posts[index]->getCommentCount() < 10) {
		Comment* comment = new Comment(postID, Entity::getID(), text);
		Comments.push_back(comment);
		Posts[index]->addComment(comment->getCommentID());
	}
	else {
		cout << "This post already has 10 comments, no further comments are allowed" << endl;
	}
}
void Page::createPost(vector <Post*>& Posts, vector <Page*>& Pages) {
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
		Posts.push_back(post);
		string currentPageID = Entity::getID();
		int pageID = idToNum(1, currentPageID) - 1;
		Pages[pageID]->addPost(post->getID());
	}
	else {
		Post* post = new Post(description, nullptr, 0);
		post->setOwnerID(Entity::getID());
		Posts.push_back(post);						//Added post to main vector to display in file
		string currentUserID = Entity::getID();
		int userID = idToNum(1, currentUserID) - 1;
		Pages[userID]->addPost(post->getID());			//Added post's address to Pages' posts vector
		cin.ignore(256, '\n');
	}
}

//Static data
int Page::currentID = 1;