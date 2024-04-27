#include"E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/HelperClass.hpp"

int idToNum(int start, string id) {
	string index;
	for (int i = start; i < id.length(); i++) {
		index[i - start] = id[i];
	}
	return stoi(index);
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

Date getCurrentDate() {
	// Get the current time
	time_t currentTime;
	time(&currentTime);

	// Convert the current time to a tm structure
	tm localTime;
	if (localtime_s(&localTime, &currentTime) != 0) {
		// Handle error if localtime_s fails
		// For simplicity, we'll return a default constructed Date object
		return Date(); // This returns a Date object with all members initialized to 0
	}

	// Create a Date object and fill it with the current date components
	Date currentDate;
	currentDate.day = localTime.tm_mday;
	currentDate.month = localTime.tm_mon + 1; // tm_mon is 0-based
	currentDate.year = localTime.tm_year + 1900; // tm_year is years since 1900

	return currentDate;
}


void createUser(string userName, vector <User*>& Users) {
	User* user = new User(userName);
	Users.push_back(user);
	cout << "User " << userName << " created successfully with userID: " << user->getID() << endl;
}

bool oneDayDiff(Date& d1, Date& d2) {
    return (d1.day - d2.day <= 1 && d2.month == d1.month && d2.year == d1.year);
}