#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account {
private:
    int id;//شناسه کاربر
    std::string fullName;//نام اصلی
    std::string username;//نام کاربری
    std::string biography;//شرح حال
    std::string role;//نقش کاربر
    std::string password;//رمز عبور
    std::string profilePhoto;  // مسیر عکس پروفایل (امتیازی)

    //نیاز داریم برای کلاس account repository:
    std::vector<int> likedSongs;
public:
    Account();

    Account(int userId, const std::string& name, const std::string& user,
         const std::string& bio, const std::string& userRole,
         const std::string& pass, const std::string& photo = "");

    int getId() const;
    std::string getFullName() const;
    std::string getUsername() const;
    std::string getBiography() const;
    std::string getRole() const;
    std::string getPassword() const;
    std::string getProfilePhoto() const;
    std::vector<int> getLikedSongs() const;

    void setId(int userId);
    void setFullName(const std::string& name);
    void setUsername(const std::string& user);
    void setBiography(const std::string& bio);
    void setRole(const std::string& userRole);
    void setPassword(const std::string& pass);
    void setProfilePhoto(const std::string& photo);

    //توابع مورد نیاز برای اهنگ های لایک شده
    void addLikedSong (int songId);
    void removeLikedSong(int songId);
};

#endif // USER_H
