#include"../Headers/CommentClass.hpp"

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

//Static data
int Comment::currentID = 1;
