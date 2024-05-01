#include"../Headers/EntityClass.hpp"

Entity::Entity(string id, string name) : id(id), name(name) {}
string Entity::getID() {
	return id;
}
string Entity::getName() {
	return name;
}
vector <string> Entity::getPosts() {
	return posts;
}
void Entity::addPost(string postID) {
	posts.push_back(postID);
}