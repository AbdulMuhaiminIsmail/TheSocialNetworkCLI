#include"../Headers/CommentClass.hpp"
Comment::Comment() : postID(""), posterID(""), text("") {}
Comment::Comment(string postID, string posterID, string text) : commentID("c" + to_string(currentID++)), postID(postID), posterID(posterID), text(text) {}
string Comment::getPostID() const {
	return postID;
}
string Comment::getCommentID() const {
	return commentID;
}
string Comment::getPosterID() const {
	return posterID;
}
string Comment::getText() const {
	return text;
}
void Comment::setPostID(string postID) {
	this->postID = postID;
}

void Comment::setCommentID(string commentID) {
	this->commentID = commentID;
}

void Comment::setPosterID(string posterID) {
	this->posterID = posterID;
}

void Comment::setText(string text) {
	this->text = text;
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

//Static data
int Comment::currentID = 1;
