#include"../Headers/PostClass.hpp"
Post::Post() : postID("post" + to_string(currentID++)), description(""), activity(nullptr), isMemory(0), likes(0), commentsCount(0), datePosted(nullptr), ownerID("") {};
Post::Post(string description, Activity* activity, bool isMemory) : description(description), activity(activity), isMemory(isMemory) {
	datePosted = getCurrentDate();
	postID = "post" + to_string(currentID++);
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
bool Post::getIsMemory() const  {
	return isMemory;
}
Date Post::getDatePosted() const {
	return *datePosted; //CHANGED
}
vector <string> Post::getLikedBy() const {
	return likedBy;
}
vector <string> Post::getComments() const {
	return comments;
}
void Post::setID(string id) {
	postID = id;
}
void Post::setOwnerID(string id) {
	ownerID = id;
}
void Post::setDescription(string description) {
	Post::description = description;
}
void Post::setIsMemory(bool isMemory) {
	Post::isMemory = isMemory;
}
void Post::setCommentCount(int comments) {
	commentsCount = comments;
}
void Post::setLikesCount(int likes) {
	Post::likes = likes;
}
void Post::setLikedBy(vector<string> likedBy) {
	for (int i = 0; i < likedBy.size(); i++) {
		this->likedBy.push_back(likedBy[i]);
	}
}
void Post::setComments(vector<string> comments) {
	for (int i = 0; i < comments.size(); i++) {
		this->comments.push_back(comments[i]);
	}
}
void Post::setActivity(Activity* activity) {
	if (activity != nullptr) {
		delete this->activity;
		this->activity = new Activity();
		this->activity->setType(activity->getType());
		this->activity->setValue(activity->getValue());
	}
	else {
		this->activity = activity;
	}

}
void Post::setDatePosted(Date* date) {
	if(datePosted != nullptr)
		delete datePosted;
	datePosted = new Date;
	*datePosted = *date;
}
void Post::addLikedBy(string liker) {
	likedBy.push_back(liker);
	incLikes();
}
void Post::addComment(string commentID) {
	comments.push_back(commentID);
	incComments();
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
	cout << endl;
	if (!isMemory) {
		int index = idToNum(1, ownerID) - 1;
		if (ownerID[0] == 'u') {
			cout << "--- " << Users[index]->getName();
		}
		else {
			cout << "--- " << Pages[index]->getName();
		}
		if (activity == nullptr) {
			cout << " shared\n\t\"" << description << "\"" << endl;
		}
		else {
			cout << activity->getValue() << "\n\t\"" << description << "\"" << endl;
		}
		for (int i = 0; i < comments.size(); i++) {
			int index = idToNum(1, comments[i]) - 1;
			cout << "\t\t";
			Comments[index]->print(Users, Pages);
		}
	}
	else {
		cout << description << endl;
	}
}
Post::~Post() {
	delete activity;
	delete datePosted;
}


//Static Data
int Post::currentID = 1;