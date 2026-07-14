#include "account.h"


Account::Account()
    : id(0), fullName(""), username(""), biography(""), role("شنونده"), password(""), profilePhoto("") {
}

Account::Account(int userId, const std::string& name, const std::string& user,
           const std::string& bio, const std::string& userRole,
           const std::string& pass, const std::string& photo)
    : id(userId), fullName(name), username(user), biography(bio), role(userRole), password(pass), profilePhoto(photo) {
}

int Account::getId() const { return id; }
std::string Account::getFullName() const { return fullName; }
std::string Account::getUsername() const { return username; }
std::string Account::getBiography() const { return biography; }
std::string Account::getRole() const { return role; }
std::string Account::getPassword() const { return password; }
std::string Account::getProfilePhoto() const { return profilePhoto; }

void Account::setId(int userId) { id = userId; }
void Account::setFullName(const std::string& name) { fullName = name; }
void Account::setUsername(const std::string& user) { username = user; }
void Account::setBiography(const std::string& bio) { biography = bio; }
void Account::setRole(const std::string& userRole) { role = userRole; }
void Account::setPassword(const std::string& pass) { password = pass; }
void Account::setProfilePhoto(const std::string& photo) { profilePhoto = photo; }
