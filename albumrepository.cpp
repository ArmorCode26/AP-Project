 #include "albumrepository.h"

//  تابع ذخیره یا به‌روزرسانی آلبوم
int AlbumRepository::save(const Album& entity) {
    Album tempEntity = entity;

    //  اگر آلبوم از قبل وجود داشته باشد وآی‌دی آن صفر نباشد
    for (size_t i = 0; i < albums.size(); ++i) {
        if (albums[i].getAlbumId() == tempEntity.getAlbumId() && tempEntity.getAlbumId() != 0) {
            albums[i] = tempEntity;
            return tempEntity.getAlbumId();
        }
    }

    //   تولید آی‌دی خودکار: اگر آی‌دی آلبوم صفر باشد
    if (tempEntity.getAlbumId() == 0) {
        int nextId = 1; // اگر وکتور خالی باشد، آی‌دی اولین آلبوم می‌شود ۱

        if (albums.empty() == false) {
            // اگر خالی نباشد، آی‌دی آخرین آلبوم وکتور را می‌گیریم و یکی به آن اضافه می‌کنیم
            nextId = albums.back().getAlbumId() + 1;
        }

        // تنظیم آی‌دی جدید روی آلبوم
        tempEntity.setAlbumId(nextId);
    }

    // اضافه کردن آلبوم جدید به وکتور)
    albums.push_back(tempEntity);

    // برگرداندن آی‌دی نهایی آلبوم
    return tempEntity.getAlbumId();
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
