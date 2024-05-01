#include"../Headers/PostClass.hpp"

Post::Post(string description, Activity* activity, int author) : description(description), activity(activity) {
	datePosted = getCurrentDate();
	if (author == 0) {										//	0->Userpost		1->Pagepost
		postID = "up" + to_string(currentUPID++);
	}
	else {
		postID = "pp" + to_string(currentPPID++);
	}
}
string Post::getID() const {
	return postID;
}
string Post::getOwnerID() const {
	return ownerID;
}
string Post::getDescription() const {
	return description;
}
Activity* Post::getActivity() const {
	return activity;
}
int Post::getCommentCount() const {
	return commentsCount;
}
int Post::getLikesCount() const {
	return likes;
}
Date Post::getDatePosted() const {
	return *datePosted; //CHANGED
}
vector <string> Post::getLikedBy() {
	return likedBy;
}
void Post::addLikedBy(string liker) {
	likedBy.push_back(liker);
	incLikes();
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
		cout << "--- " << Users[index]->getName();
	}
	else {
		cout << "--- " << Pages[index]->getName();
	}
	if (activity == nullptr) {
		cout << " shared \"" << description << "\"" << endl;
	}
	else {
		cout << activity->getValue() << "\n\t\"" << description << "\"" << endl;
	}
	for (int i = 0; i < comments.size(); i++) {
		int index = idToNum(1, comments[i]) - 1;
		cout<<"\t\t";
		Comments[index]->print(Users, Pages);
	}
	cout<<endl<<endl;
}

//Static Data
int Post::currentUPID = 1;
int Post::currentPPID = 1;