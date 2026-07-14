#include "songrepository.h"
#include <algorithm>

// تابع ذخیره یا به‌روزرسانی
int SongRepository::save(const Song& entity) {
    // جستجو برای پیدا کردن اینکه آیا این آهنگ از قبل وجود داشته یا نه
    for (size_t i = 0; i < songs.size(); ++i) {
        if (songs[i].getId() == entity.getId()) {
            songs[i] = entity; // به‌روزرسانی با مقدار جدید
            return entity.getId();
        }
    }
    // اگر وجود نداشت، آن را به وکتور اضافه می‌کنیم
    songs.push_back(entity);
    return entity.getId();
}

// تابع حذف آهنگ براساس آیدی
bool SongRepository::remove(int id) {
    for (auto it = songs.begin(); it != songs.end(); ++it) {
        if (it->getId() == id) {
            songs.erase(it); // حذف از وکتور
            return true; // حذف موفقیت‌آمیز
        }
    }
    return false; // پیدا نشد
}

// تابع جستجوی آهنگ (استفاده از جعبه جادویی optional)
std::optional<Song> SongRepository::search(int id) {
    for (const auto& song : songs) {
        if (song.getId() == id) {
            return song; // آهنگ پیدا شد و داخل جعبه برگشت داده می‌شود
        }
    }
    return std::nullopt; // جعبه خالی (یعنی پیدا نشد)
}

// آهنگ‌های یک هنرمند که به هیچ آلبومی تعلق ندارند (آیدی آلبوم صفر است)
std::vector<Song> SongRepository::singleSongs(int artistId) {
    std::vector<Song> result;
    for (const auto& song : songs) {
        if (song.getArtistId() == artistId && song.getAlbumId() == 0) {
            result.push_back(song);
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
    for (const auto& song : songs) {
        if (song.getArtistId() == artistId) {
            result.push_back(song);
        }
    }
    return result;
}

// دریافت آهنگ‌های یک لیست پخش (فعلاً وکتور خالی برمی‌گرداند تا ساختار تعاملی لیست پخش کامل شود)
std::vector<Song> SongRepository::getByPlaylist(int playlistId) {
    std::vector<Song> result;
    // در آینده پیاده‌سازی کامل‌تر می‌شود
    return result;
}

// دریافت آهنگ‌های پسندیده شده توسط یک شنونده
std::vector<Song> SongRepository::getByLikedSongs(int listenerId) {
    std::vector<Song> result;
    // در آینده بر اساس وکتور لایک‌های کاربر پر می‌شود
    return result;
}
