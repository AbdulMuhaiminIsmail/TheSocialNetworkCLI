#include"../Headers/HelperClass.hpp"

int idToNum(int start, string id) {
	string index;
	for (int i = start; i < id.length(); i++) {
		index[i - start] = id[i];
	}
	return stoi(index);
}

string getTimeAgo(Post* source) {
	string timeAgo;
	if (source->getDatePosted().year != getCurrentDate()->year) {
		int years = getCurrentDate()->year - source->getDatePosted().year;
		timeAgo = "(" + to_string(years) + " Years Ago)";
	}
	else if (source->getDatePosted().month != getCurrentDate()->month) {
		int months = getCurrentDate()->month - source->getDatePosted().month;
		timeAgo = "(" + to_string(months) + " Months Ago)";
	}
	else if (source->getDatePosted().day != getCurrentDate()->day) {
		int days = getCurrentDate()->day - source->getDatePosted().day;
		timeAgo = "(" + to_string(days) + " Days Ago)";
	}
	else {
		timeAgo = "Just a while ago";
	}
	return timeAgo;
}

void showLikedBy(string postID, vector <User*>& Users, vector <Page*>& Pages, vector <Post*>& UserPosts, vector <Post*>& PagePosts) {
	cout << "----------------------------------------------------------" << endl;
	cout << "Post Liked By: " << endl;
	int size;
	int index = idToNum(2, postID) - 1;
	vector <string> likedBy;
	if (postID[0] == 'u') {
		likedBy = UserPosts[index]->getLikedBy();
		size = likedBy.size();
	}
	else {
		likedBy = PagePosts[index]->getLikedBy();
		size = likedBy.size();
	}
	for (int i = 0; i < size; i++) {
		int currentIndex = idToNum(1, likedBy[i]) - 1;
		if (likedBy[i][0] == 'u') {
			cout << likedBy[i] << "-" << Users[currentIndex]->getName() << endl;
		}
		else {
			cout << likedBy[i] << "-" << Pages[currentIndex]->getName() << endl;
		}
	}
	cout << "----------------------------------------------------------" << endl;
}

Date *getCurrentDate() {
	Date* temp = new Date;
	return temp;
}


void createUser(string userName, vector <User*>& Users) {
	User* user = new User(userName);
	Users.push_back(user);
	cout << "User " << userName << " created successfully with userID: " << user->getID() << endl;
}

bool oneDayDiff(Date& d1, Date& d2) {
    return (d1.day - d2.day <= 1 && d2.month == d1.month && d2.year == d1.year);
}