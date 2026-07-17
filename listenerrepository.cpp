#include "listenerrepository.h"

int ListenerRepository::save(const Account& listener) {
    for (size_t i = 0; i < listenersList.size(); i++) {
        if (listenersList[i].getId() == listener.getId()) {
            listenersList[i] = listener;
            return listener.getId();
        }
    }
    listenersList.push_back(listener);
    return listener.getId();
}

bool ListenerRepository::remove(int id) {
    for (size_t i = 0; i < listenersList.size(); i++) {
        if (listenersList[i].getId() == id) {
            listenersList.erase(listenersList.begin() + i);
            return true;
        }
    }
    return false;
}

std::optional<Account> ListenerRepository::search(int id) {
    for (size_t i = 0; i < listenersList.size(); i++) {
        if (listenersList[i].getId() == id) {
            return listenersList[i];
        }
    }
    return std::nullopt;
}

// ۴. تابع searchByUsername
std::optional<Account> ListenerRepository::searchByUserName(const std::string& username) {
    for (size_t i = 0; i < listenersList.size(); i++) {
        if (listenersList[i].getUsername() == username) {
            return listenersList[i];
        }
    }
    return std::nullopt;
}

//  اضافه یا حذف کردن لایک یک آهنگ برای یک کاربر
void ListenerRepository::updateLiked(int listenerId, int songId, bool likeStatus) {
    for (size_t i = 0; i < listenersList.size(); i++) {
        if (listenersList[i].getId() == listenerId) {

            if (likeStatus == true) {
                // اول چک می‌کنیم که این آهنگ از قبل لایک نشده باشد تا تکراری اضافه نشود
                bool alreadyLiked = false;
                std::vector<int> userLikes = listenersList[i].getLikedSongs();
                for (size_t j = 0; j < userLikes.size(); j++) {
                    if (userLikes[j] == songId) {
                        alreadyLiked = true;
                        break;
                    }
                }
                // اگر قبلاً لایک نشده بود، الان اضافه‌اش می‌کنیم
                if (alreadyLiked == false) {
                    listenersList[i].addLikedSong(songId);
                }
            }
            else {
              //اگه false بود حذف میکنیم
                listenersList[i].removeLikedSong(songId);
            }

            break; // کاربر موردنظر پیدا شد
        }
    }
}

//  ببینیم آیا کاربر این آهنگ را لایک کرده است یا نه
bool ListenerRepository::isLiked(int listenerId, int songId) {
    for (size_t i = 0; i < listenersList.size(); i++) {
        if (listenersList[i].getId() == listenerId) {
            std::vector<int> userLikes = listenersList[i].getLikedSongs();

            // چک می‌کنیم آیا این آی‌دی آهنگ در لیست لایک‌های کاربر هست یا نه
            for (size_t j = 0; j < userLikes.size(); j++) {
                if (userLikes[j] == songId) {
                    return true; // بله، لایک کرده
                }
            }
            return false; // کاربر پیدا شد ولی این آهنگ را لایک نکرده
        }
    }
    return false; // اگر اصلاً کاربر با این آی‌دی پیدا نشد
}
