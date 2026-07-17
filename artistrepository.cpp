#include "artistrepository.h"

int ArtistRepository::save(const Account& artist) {
    for (size_t i = 0; i < artistsList.size(); i++) {
        if (artistsList[i].getId() == artist.getId()) {
            artistsList[i] = artist;
            return artist.getId();
        }
    }
    artistsList.push_back(artist);
    return artist.getId();
}

bool ArtistRepository::remove(int id) {
    for (size_t i = 0; i < artistsList.size(); i++) {
        if (artistsList[i].getId() == id) {
            artistsList.erase(artistsList.begin() + i);
            return true;
        }
    }
    return false;
}


std::optional<Account> ArtistRepository::search(int id) {
    for (size_t i = 0; i < artistsList.size(); i++) {
        if (artistsList[i].getId() == id) {
            return artistsList[i];
        }
    }
    return std::nullopt;
}

// تابع searchByUserName: پیدا کردن هنرمند بر اساس نام کاربری
std::optional<Account> ArtistRepository::searchByUserName(const std::string& username) {
    for (size_t i = 0; i < artistsList.size(); i++) {
        if (artistsList[i].getUsername() == username) {
            return artistsList[i];
        }
    }
    return std::nullopt;
}
