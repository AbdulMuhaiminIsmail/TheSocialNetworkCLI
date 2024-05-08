#include"../Headers/HelperClass.hpp"

int idToNum(int start, string id) {
	char* index = new char[3];
	for (int i = start; i < id.length(); i++) {
		index[i - start] = id[i];
	}
	int result = stoi(index);
	delete index;
	return result;
}

string getTimeAgo(Post* source) {
	string timeAgo;
	if (source->getDatePosted().year != getCurrentDate()->year) {
		int years = getCurrentDate()->year - source->getDatePosted().year;
		timeAgo = "(" + to_string(years) + " Year(s) Ago)";
	}
	else if (source->getDatePosted().month != getCurrentDate()->month) {
		int months = getCurrentDate()->month - source->getDatePosted().month;
		timeAgo = "(" + to_string(months) + " Month(s) Ago)";
	}
	else if (source->getDatePosted().day != getCurrentDate()->day) {
		int days = getCurrentDate()->day - source->getDatePosted().day;
		timeAgo = "(" + to_string(days) + " Day(s) Ago)";
	}
	else {
		timeAgo = "(Just a while ago)";
	}
	return timeAgo;
}

void showLikedBy(string postID, vector <User*>& Users, vector <Page*>& Pages, vector <Post*>& Posts) {
	cout << "----------------------------------------------------------" << endl;
	cout << "Post Liked By: " << endl;
	int index = idToNum(4, postID) - 1;
	vector <string> likedBy = Posts[index]->getLikedBy();
	for (int i = 0; i < likedBy.size(); i++) {
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

Date* getCurrentDate() {
	// Get the current time
	std::time_t currentTime;
	std::time(&currentTime);

	// Convert the current time to a tm structure
	std::tm localTime;
	localtime_s(&localTime, &currentTime);

	// Create a new Date object and fill it with the current date components
	Date* currentDate = new Date;
	currentDate->day = localTime.tm_mday;
	currentDate->month = localTime.tm_mon + 1; // tm_mon is 0-based
	currentDate->year = localTime.tm_year + 1900; // tm_year is years since 1900

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