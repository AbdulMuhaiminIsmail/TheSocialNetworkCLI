# TheSocialNetworkCLI

## 🚀 Overview
**TheSocialNetworkCLI** is a command-line social media platform designed to emulate core features of platforms like Facebook. This project is part of my **Object-Oriented Programming coursework** at university, showcasing key concepts like encapsulation, inheritance, and polymorphism. It provides users with a basic yet functional interface to connect, create, and share.

---

## ✨ Features
### **Core Functionalities**
- **User Management**:
  - Create users and add friends to your friend list.
  - View user information and manage connections.
- **Social Interaction**:
  - Create, like, and comment on posts.
  - Share memories and view your shared memories.
- **Pages Management**:
  - Create pages, like pages, and view owned or liked pages.
  - Display likes and posts on specific pages.
- **Personalized Experience**:
  - View a personalized home feed (posts from friends and liked pages).
  - Explore your timeline with posts from friends and yourself.

---

## 🛠️ Functionality Breakdown

### **Data Management**
- `importData()`: Reads data from external files to populate app structures (users, pages, posts, comments).
- `exportData()`: Writes current data structures to files for future use.

### **User Features**
- `createUser(string userName)`: Adds a new user to the platform.
- `addFriend(string friendID)`: Adds a friend to the current user’s friend list.
- `setCurrentUser(string userID)`: Switches the session to the specified user.
- `printUser()`: Displays the current user’s profile information.
- `viewFriends()`: Lists the current user's friends.

### **Post Features**
- `createPost()`: Allows users or pages to create posts.
- `likePost(string postID)`: Lets users like a specific post.
- `showLikers(string postID)`: Displays users who have liked a post.
- `commentPost(string postID, string comment)`: Adds a comment to a specific post.
- `viewPost(string postID)`: Displays a specific post along with its comments.
- `viewHome()`: Shows posts from friends and liked pages in the home feed.
- `viewTimeline()`: Displays the user's timeline, including their posts and content from friends or liked pages.
- `shareMemory(string postID, string text)`: Shares a memory from an existing post.
- `seeYourMemories()`: Displays all shared memories by the user.

### **Page Features**
- `createPage(string title)`: Creates a new page with the given title.
- `likePage(string pageID)`: Likes a specific page.
- `viewPageLikes(string pageID)`: Displays the total likes on a page.
- `viewPage(string pageID)`: Shows the details and posts of a specific page.
- `viewOwnedPages()`: Lists all pages owned by the current user.
- `viewLikedPages()`: Lists all pages liked by the current user.

---
