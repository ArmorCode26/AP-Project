#include "songrepository.h"
#include<playlist.h>
#include<playlistrepository.h>
#include<listenerrepository.h>
#include <algorithm>
#include<optional>

// تابع ذخیره یا به‌روزرسانی
int SongRepository::save(const Song& entity) {
    Song tempEntity = entity;

    // بخش به‌روزرسانی
    for (size_t i = 0; i < songs.size(); ++i) {
        if (songs[i].getSongId() == tempEntity.getSongId() && tempEntity.getSongId() != 0) {
            songs[i] = tempEntity;
            return tempEntity.getSongId();
        }
    }

    // بخش ایجاد جدید و تولید آی‌دی خودکار
    if (tempEntity.getSongId() == 0) {
        int nextId = 1;

        if (songs.empty() == false) {
            nextId = songs.back().getSongId() + 1;
        }

        tempEntity.setSongId(nextId);
    }

    songs.push_back(tempEntity);
    return tempEntity.getSongId();
}

// تابع حذف آهنگ براساس آیدی
bool SongRepository::remove(int id) {
    for (size_t i = 0; i < songs.size(); ++i) {
        if (songs[i].getSongId() == id) {
            songs.erase(songs.begin()+i);
            return true;
        }
    }
    return false;
}

// تابع جستجوی آهنگ
std::optional<Song> SongRepository::search(int id) {
    for (size_t i = 0; i < songs.size(); ++i) {
        if (songs[i].getSongId() == id) {
            return songs[i];
        }
    }
    return std::nullopt; // جعبه خالی
}

// آهنگ‌های یک هنرمند که به هیچ آلبومی تعلق ندارند
std::vector<Song> SongRepository::singleSongs(int artistId) {
    std::vector<Song> result;
    for (size_t i = 0; i < songs.size(); ++i) {
        if (songs[i].getArtistId() == artistId && songs[i].getAlbumId() == 0) {
            result.push_back(songs[i]);
        }
    }
    return result;
}

// دریافت آهنگ‌های یک آلبوم خاص
std::vector<Song> SongRepository::getByAlbum(int albumId) {
    std::vector<Song> result;
    for (const auto& song : songs) {
        if (song.getAlbumId() == albumId) {
            result.push_back(song);
        }
    }
    return result;
}

// دریافت تمام آهنگ‌های یک هنرمند
std::vector<Song> SongRepository::getByArtist(int artistId) {
    std::vector<Song> result;
    for (size_t i = 0; i < songs.size(); ++i) {
        if (songs[i].getArtistId() == artistId) {
            result.push_back(songs[i]);
        }
    }
    return result;
}

// دریافت آهنگ‌های یک لیست پخش
std::vector<Song> SongRepository::getByPlaylist(int playlistId) {
    std::vector<Song> result;

    for (size_t i = 0; i < songs.size(); i++) {
        if (songs[i].getPlaylistId() == playlistId) {
            result.push_back(songs[i]);
        }
    }

    return result;
}
// دریافت آهنگ‌های پسندیده شده توسط یک شنونده
std::vector<Song> SongRepository::getByLikedSongs(int listenerId) {
    std::vector<Song> result;

    for (size_t i = 0; i < songs.size(); i++) {
        std::vector<int> users = songs[i].getlikedUserIds();

        // چک می‌کنیم آیا این کاربر در لیست لایک‌کننده‌های این آهنگ هست یا نه
        for (size_t j = 0; j < users.size(); j++) {
            if (users[j] == listenerId) {
                result.push_back(songs[i]);
                break;
            }
        }
    }

    return result;
}
