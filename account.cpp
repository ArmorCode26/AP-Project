#include "account.h"


User::User()
    : id(0), fullName(""), username(""), biography(""), role("شنونده"), password(""), profilePhoto("") {
}

User::User(int userId, const std::string& name, const std::string& user,
           const std::string& bio, const std::string& userRole,
           const std::string& pass, const std::string& photo)
    : id(userId), fullName(name), username(user), biography(bio), role(userRole), password(pass), profilePhoto(photo) {
}

int User::getId() const { return id; }
std::string User::getFullName() const { return fullName; }
std::string User::getUsername() const { return username; }
std::string User::getBiography() const { return biography; }
std::string User::getRole() const { return role; }
std::string User::getPassword() const { return password; }
std::string User::getProfilePhoto() const { return profilePhoto; }

void User::setId(int userId) { id = userId; }
void User::setFullName(const std::string& name) { fullName = name; }
void User::setUsername(const std::string& user) { username = user; }
void User::setBiography(const std::string& bio) { biography = bio; }
void User::setRole(const std::string& userRole) { role = userRole; }
void User::setPassword(const std::string& pass) { password = pass; }
void User::setProfilePhoto(const std::string& photo) { profilePhoto = photo; }
