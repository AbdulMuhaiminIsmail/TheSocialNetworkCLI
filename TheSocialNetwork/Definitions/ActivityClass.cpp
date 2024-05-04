#include"../Headers/ActivityClass.hpp"

Activity::Activity(int type, string value) : type(type), value(value) {}
int Activity::getType() const {
	return type;
}
string Activity::getValue() const {
	return value;
}
void Activity::setType(int type) {
	this->type = type;
}
void Activity::setValue(string value) {
	this->value = value;
}
void Activity::setActivity() {
	if (type != 0) {
		string temp;
		if (type == 1) {
			cout << "What are you feeling? (Happy/Sad/Excited/Other) ";
			getline(cin, temp);
			value = " is feeling " + temp;
		}
		else if (type == 2) {
			cout << "What are you thinking? (Life/Future/Meaning of Life/Other) ";
			getline(cin, temp);
			value = " is thinking about " + temp;
		}
		else if (type == 3) {
			cout << "What are you making? (Money/Arts/Memories/Other) ";
			getline(cin, temp);
			value = " is making " + temp;
		}
		else if (type == 4) {
			cout << "What are you celebrating? (Birthday/Halloween/Success/Other) ";
			getline(cin, temp);
			value = " is celebrating " + temp;
		}
	}
}