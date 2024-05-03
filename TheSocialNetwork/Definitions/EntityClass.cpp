#include"../Headers/EntityClass.hpp"
Entity::Entity() : id(""), name("") {}
Entity::Entity(string id, string name) : id(id), name(name) {}
string Entity::getID() const {
	return id;
}
void Entity::setID(string id) {
	this->id = id;
}
string Entity::getName() const {
	return name;
}
void Entity::setName(string name) {
	this->name = name;
}
vector <string> Entity::getPosts() const {
	return posts;
}
void Entity::setPosts(vector <string> posts) {
	for (int i = 0; i < posts.size(); i++)
	{
			this->posts.push_back(posts[i]);
	}	
}
void Entity::addPost(string postID) {
	posts.push_back(postID);
}