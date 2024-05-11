# TheSocialNetworkCLI
This project involves developing a rudimentary command-line interface social media platform, designed to emulate the core features of Facebook. This assignment is part of my coursework in Object-Oriented Programming at university.

Description:

It allows users to create posts, like and comment on posts, connect with friends, create and like pages, and more.

Functions:

importData()

    Reads data from external files to populate the app's data structures, including users, pages, posts, and comments.

exportData()

    Writes data from the app's data structures to external files for storage and future use.

createUser(string userName)

    Creates a new user with the given name and adds them to the app.

addFriend(string friendID)

    Adds a friend to the current user's friend list.

printUser()

    Displays information about the current user.

createPost()

    Allows the user to create a post as either a user or a page.

createPage(string title)

    Creates a new page with the given title.

likePage(string pageID)

    Allows the current user to like a page.

viewPageLikes(string pageID)

    Displays the total number of likes for a page.

setCurrentUser(string userID)

    Sets the current user to the user with the given ID.

viewOwnedPages()

    Displays the pages owned by the current user.

viewLikedPages()

    Displays the pages liked by the current user.

viewHome()

    Displays the home feed of the current user, including posts from friends and liked pages.

likePost(string postID)

    Allows the current user to like a post.

showLikers(string postID)

    Displays the users who have liked a post.

commentPost(string postID, string comment)

    Allows the current user to comment on a post.

viewPost(string postID)

    Displays a specific post with its details and comments.

shareMemory(string postID, string text)

    Allows the current user to share a memory from a post.

seeYourMemories()

    Displays memories shared by the current user.

viewTimeline()

    Displays the timeline of the current user, including their own posts and posts from friends and liked pages.

viewFriends()

    Displays the friends of the current user.

viewPage(string pageID)

    Displays the details and posts of a specific page.

Usage:

    Use the provided functions to navigate and interact with TheSocial Media App.
    Follow the prompts and input requirements to perform various actions such as creating users, posts, pages, liking content, and more.

Feel free to explore the app and enjoy connecting with others in the virtual realm of TSN!
