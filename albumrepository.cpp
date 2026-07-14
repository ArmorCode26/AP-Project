 #include "albumrepository.h"

//  تابع ذخیره یا به‌روزرسانی آلبوم
int AlbumRepository::save(const Album& entity) {

    for (size_t i = 0; i < albums.size(); ++i) {
        if (albums[i].getAlbumId() == entity.getAlbumId()) {
            albums[i] = entity;
            return entity.getAlbumId();
        }
    }

    albums.push_back(entity);
    return entity.getAlbumId();
}

//  تابع حذف آلبوم براساس آیدی
bool AlbumRepository::remove(int id) {
    for (size_t i = 0; i < albums.size(); ++i) {
        if (albums[i].getAlbumId() == id) {
            albums.erase(albums.begin() + i);
            return true;
        }
    }
    return false;
}

//  تابع جستجوی آلبوم
std::optional<Album> AlbumRepository::search(int id) {
    for (size_t i = 0; i < albums.size(); ++i) {
        if (albums[i].getAlbumId() == id) {
            return albums[i];
        }
    }
    return std::nullopt; // جعبه‌ی خالی برمی‌گردانیم
}

//   دریافت تمام آلبوم‌های یک هنرمند خاص
std::vector<Album> AlbumRepository::getByArtist(int artistId) {
    std::vector<Album> result;
    for (size_t i = 0; i < albums.size(); ++i) {
        if (albums[i].getArtistId() == artistId) {
            result.push_back(albums[i]);
        }
    }
    return result;
}
