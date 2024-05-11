#include"../Headers/PageClass.hpp"
Page::Page() : Entity("p" + to_string(currentID++)) { likes = 0; }
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
		cout << " \t\t\t\t\t\t\t\t\tThe page already has 10 likes, no more allowed" << endl;
	}
}
void Page::viewPage(vector <Post*> Posts, vector <User*> Users, vector <Page*> Pages, vector <Comment*> Comments) {
	vector <string> posts = getPosts();
	cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << "						   \t\t\t\t" << getName() << " | View Page" << endl;
	for (int i = 0; i < posts.size(); i++) {
		int index = idToNum(4, posts[i]) - 1;
		Posts[index]->showPost(Users, Pages, Comments);
	}
	cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
void Page::likePost(string postID, vector <Post*>& Posts) {
	int index = idToNum(4, postID) - 1;
	if (index >= Posts.size() || index < 0) {
		cout << " \t\t\t\t\t\t\t\t\tThe given post id is invalid" << endl;
		return;
	}
	if (Posts[index]->getLikesCount() < 10) {
		Posts[index]->addLikedBy(Entity::getID());
	}
	else {
		cout << " \t\t\t\t\t\t\t\t\tThis post already has 10 comments, no further comments are allowed" << endl;
	}
}
void Page::comment(string postID, string text, vector <Comment*>& Comments, vector <Post*>& Posts) {
	int index = idToNum(4, postID) - 1;
	if (index >= Posts.size() || index < 0) {
		cout << " \t\t\t\t\t\t\t\t\tThe given post id is invalid" << endl;
		return;
	}
	if (Posts[index]->getCommentCount() < 10) {
		Comment* comment = new Comment(postID, Entity::getID(), text);
		Comments.push_back(comment);
		Posts[index]->addComment(comment->getCommentID());
	}
	else {
		cout << " \t\t\t\t\t\t\t\t\tThis post already has 10 comments, no further comments are allowed" << endl;
	}
}
void Page::createPost(vector <Post*>& Posts, vector <Page*>& Pages) {
	int hasActivity, type;
	string description;
	cout << endl << " \t\t\t\t\t\t\t\t\t    What is the description of the post? ";
	getline(cin, description);

	do {
		cout << " \t\t\t\t\t\t\t\t\t    Do you want to add any activity? (0.No/1.Yes) ";
		cin >> hasActivity;
		if (hasActivity != 0 && hasActivity != 1) {
			cout << " \t\t\t\t\t\t\t\t\t    Enter 0 or 1 only!" << endl;
		}
	} while ((hasActivity != 0 && hasActivity != 1));

	if (hasActivity) {
		do {
			cout << " \t\t\t\t\t\t\tWhat kind of activity is this? (1.Feeling/2.Thinking/3.Making/4.Celebrating) ";
			cin >> type;
			if (type < 1 || type > 4) {
				cout << " \t\t\t\t\t\t\t\t\t\tInvalid type" << endl;
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
		cout << " \t\t\t\t\t\t\t\t\tPost created successfully, with post ID - " << post->getID() << endl;
	}

	else {
		Post* post = new Post(description, nullptr, 0);
		post->setOwnerID(Entity::getID());
		Posts.push_back(post);					
		string currentPageID = Entity::getID();
		int pageID = idToNum(1, currentPageID) - 1;
		Pages[pageID]->addPost(post->getID());	
		cout << " \t\t\t\t\t\t\t\t\tPost created successfully, with post ID - " << post->getID() << endl;
		cin.ignore(256, '\n');
	}
}

//Static data
int Page::currentID = 1;