       #include "appmanager.h"
#include<account.h>
#include<artistrepository.h>
#include<listenerrepository.h>
#include<algorithm>
//پیاده سازی بخش حساب کاربری و ورود
// ثبت‌نام کاربر
bool AppManager::registerUser(const std::string& name, const std::string& username,
                              const std::string& password, const std::string& role,
                              const std::string& biography) {
    //  بررسی خالی نبودن اطلاعات ضروری
    if (name.empty() || username.empty() || password.empty() || role.empty()) {
        return false;
    }

    //بررسی تکراری نبودن نام کاربری با استفاده از متد search خودِ ریپازیتوری‌ها
    if (role == "Artist") {
        // ساخت حساب جدید با سازنده اصلی
        Account newArtist(0, name, username, biography, "Artist", password);
        artistRepo.save(newArtist);
        return true;
    }
    else if (role == "Listener") {
        Account newListener(0, name, username, biography, "Listener", password);
        listenerRepo.save(newListener);
        return true;
    }

    return false;
}

//  ورود کاربر به سیستم
bool AppManager::loginUser(const std::string& username, const std::string& password) {
    //  جستجو در بین هنرمندان با متد searchByUserName
    std::optional<Account> artistOpt = artistRepo.searchByUserName(username);
    if (artistOpt.has_value()) {
        Account artist = artistOpt.value();
        if (artist.getPassword() == password) {
            currentUserId = artist.getId();
            currentUserRole = "Artist";
            return true;
        }
    }

    //  جستجو در بین شنوندگان
    std::optional<Account> listenerOpt = listenerRepo.searchByUserName(username);
    if (listenerOpt.has_value()) {
        Account listener = listenerOpt.value();
        if (listener.getPassword() == password) {
            currentUserId = listener.getId();
            currentUserRole = "Listener";
            return true;
        }
    }

    //  اگر کاربر پیدا نشد یا رمز اشتباه بود
    return false;
}
// ۳. خروج از حساب
void AppManager::logoutUser() {
    currentUserId = -1;
    currentUserRole = "";
}
//   پیاده‌سازی قابلیت‌های هنرمندان

//  ایجاد آلبوم جدید
void AppManager::createAlbum(const std::string& title) {
    Album newAlbum;
    newAlbum.setTitle(title);
    newAlbum.setArtistId(currentUserId);
    newAlbum.setAlbumId(0);//شناسه رو صفر میکنیم تا متوجه شویم البوم جدید است

    // ذخیره در ریپازیتوری آلبوم‌ها
    albumRepo.save(newAlbum);
}

//  ایجاد آهنگ جدید
void AppManager::createSong(const std::string& title, int releaseYear, const std::string& genre,
                            const std::string& filePath, int albumId) {
    Song newSong;

    newSong.setTitle(title);
    newSong.setReleaseYear(releaseYear);
    newSong.setGenre(genre);
    newSong.setFilePath(filePath); // مسیر فایل صوتی

    // نسبت دادن خودکار شناسه هنرمند
    newSong.setArtistId(currentUserId);

    // نسبت دادن شناسه آلبوم بر اساس انتخاب کاربر
    newSong.setAlbumId(albumId);

    //  شناسه آهنگ را صفر می‌گذاریم تا ریپازیتوری خودکار شناسه جدید (آخرین آی‌دی + ۱) را تولید کند
    newSong.setSongId(0);

    //   ذخیره نهایی در ریپازیتوری آهنگ‌ها
    songRepo.save(newSong);
}

//  ویرایش اطلاعات آهنگ
void AppManager::editSong(int songId, const std::string& newTitle, int newReleaseYear,
                          const std::string& newGenre, const std::string& newFilePath) {

    // پیدا کردن آهنگ بر اساس آی‌دی با اپشنال
    std::optional<Song> songOpt = songRepo.search(songId);

    if (songOpt.has_value()) {
        Song songToEdit = songOpt.value();

        // به‌روزرسانی تک‌تک اطلاعات آهنگ طبق خواسته داکیومنت
        songToEdit.setTitle(newTitle);
        songToEdit.setReleaseYear(newReleaseYear);
        songToEdit.setGenre(newGenre);
        songToEdit.setFilePath(newFilePath);

        // ذخیره تغییرات
        songRepo.save(songToEdit);
    }
}

//  ویرایش اطلاعات آلبوم
void AppManager::editAlbum(int albumId, const std::string& newTitle, const std::vector<Song>& newSongs) {
    //  جستجوی آلبوم بر اساس آی‌دی در ریپازیتوری
    std::optional<Album> albumOpt = albumRepo.search(albumId);

    // بررسی وجود داشتن آلبوم
    if (albumOpt.has_value()) {
        // استخراج شیء آلبوم از داخل جعبه
        Album albumToEdit = albumOpt.value();

        //  به‌روزرسانی
        albumToEdit.setTitle(newTitle);
        albumRepo.save(albumToEdit);

        // آزاد کردن آهنگ‌های قبلی آلبوم
        std::vector<Song> oldSongs = songRepo.getByAlbum(albumId);
        for (size_t i = 0; i < oldSongs.size(); ++i) {
            oldSongs[i].setAlbumId(0);
            songRepo.save(oldSongs[i]);
        }

        //نسبت دادن آهنگ‌های جدید به این آلبوم
        for (size_t i = 0; i < newSongs.size(); ++i) {
            Song updatedSong = newSongs[i];
            updatedSong.setAlbumId(albumId);
            songRepo.save(updatedSong);
        }
    }
}
// حذف آهنگ
void AppManager::deleteSong(int songId) {
    // حذف خود آهنگ از ریپازیتوری اصلی آهنگ‌ها
    songRepo.remove(songId);

    // گرفتن تمام پلی‌لیست‌ها
    std::vector<Playlist> allPlaylists = playlistRepo.getAllPlaylists();

    //  حذف آهنگ از تمام پلی‌لیست‌ها
    for (size_t i = 0; i < allPlaylists.size(); ++i) {
        playlistRepo.removeSong(allPlaylists[i].getPlaylistId(), songId);
    }
}
//  حذف آلبوم
void AppManager::deleteAlbum(int albumId) {
    // پیدا کردن تمام آهنگ‌هایی که متعلق به این آلبوم
    std::vector<Song> albumSongs = songRepo.getByAlbum(albumId);

    // حذف تک‌تک این آهنگ‌ها
    for (size_t i = 0; i < albumSongs.size(); ++i) {
        deleteSong(albumSongs[i].getSongId());
    }

    //  حذف خودِ آلبوم از ریپازیتوری آلبوم‌ها
    albumRepo.remove(albumId);
}
//  نمایش فهرستی از تمام آلبوم‌ها
std::vector<Album> AppManager::getAlbums(int artistId) {
    return albumRepo.getByArtist(artistId);
}

// نمایش آهنگ‌های بدون آلبوم Singles
std::vector<Song> AppManager::getSingleSongs(int artistId) {
    std::vector<Song> result;
    std::vector<Song> artistSongs = songRepo.getByArtist(artistId);

    for (size_t i = 0; i < artistSongs.size(); ++i) {
        if (artistSongs[i].getAlbumId() == 0) {
            result.push_back(artistSongs[i]);
        }
    }

    return result;
}
//بخش شنوندگان
// مشاهده فهرستی از تمام هنرمندان
std::vector<Account> AppManager::getAllArtists() {
    return artistRepo.getAll();
}


// مشاهده فهرستی از لیست‌های پخش
std::vector<Playlist> AppManager::getMyPlaylists() {
    // گرفتن پلی‌لیست‌های مربوط به شنونده‌ای که الان لاگین است
    return playlistRepo.playlists(currentUserId);
}

//  ایجاد یک لیست پخش
void AppManager::createPlaylist(const std::string& playlistName) {
    if (playlistName.empty() || currentUserId == -1) return;

    // آی‌دی 0 داده می‌شود تا ریپازیتوری خودکار آی‌دی یکتا اختصاص دهد
    Playlist newPlaylist(0, playlistName, currentUserId);
    playlistRepo.save(newPlaylist);
}

//  ویرایش یک لیست پخش (تغییر نام)
void AppManager::editPlaylist(int playlistId, const std::string& newName) {
    std::optional<Playlist> playlistOpt = playlistRepo.search(playlistId);
    if (playlistOpt.has_value()) {
        Playlist playlist = playlistOpt.value();

        // اطمینان از این‌که فقط مالک پلی‌لیست می‌تواند آن را ویرایش کند
        if (playlist.getOwnerId() == currentUserId) {
            playlist.setName(newName);
            playlistRepo.save(playlist);
        }
    }
}
//  حذف یک لیست پخش
void AppManager::deletePlaylist(int playlistId) {
    std::optional<Playlist> playlistOpt = playlistRepo.search(playlistId);
    if (playlistOpt.has_value()) {
        // فقط حذف پلی‌لیست از ریپازیتوری بدون دست زدن به آهنگ‌ها
        if (playlistOpt.value().getOwnerId() == currentUserId) {
            playlistRepo.remove(playlistId);
        }
    }
}

// افزودن آهنگ به لیست پخش
void AppManager::addSongToPlaylist(int playlistId, int songId) {
    // استفاده از  insertSong موجود در PlaylistRepository
    playlistRepo.insertSong(playlistId, songId);
}

// حذف آهنگ از یک لیست پخش
//  حذف آهنگ از لیست پخش، موجب حذف کامل آن از سیستم و آلبوم‌ها نمی‌شود
void AppManager::removeSongFromPlaylist(int playlistId, int songId) {
    // استفاده از  removeSong موجود در PlaylistRepository
    playlistRepo.removeSong(playlistId, songId);
}

// امکان لایک آهنگ‌ها توسط شنوندگان
void AppManager::toggleLikeSong(int songId) {
    if (currentUserId == -1) return;

    std::optional<Account> listenerOpt = listenerRepo.search(currentUserId);
    if (listenerOpt.has_value()) {
        Account listener = listenerOpt.value();
        std::vector<int> likedSongs = listener.getLikedSongs();

        bool isLiked = false;
        std::vector<int> updatedLiked;
        // بررسی اینکه آیا آهنگ قبلاً لایک شده یا خیر
                for (size_t i = 0; i < likedSongs.size(); ++i) {
                    if (likedSongs[i] == songId) {
                        isLiked = true; // اگر لایک شده بود، منتقلش نمی‌کنیم
                    } else {
                        updatedLiked.push_back(likedSongs[i]);
                    }
                }

                // اگر لایک نشده بود، اضافه می‌شود
                if (!isLiked) {
                    updatedLiked.push_back(songId);
                }

                // به‌روزرسانی لیست لایک‌ها و ذخیره‌سازی
                listener.getLikedSongs() = updatedLiked; // یا ست کردن متغیر likedSongs
                listenerRepo.save(listener);
            }
        }
//قابلیت های مشترک

//  جستجو و فیلتر آهنگ‌ها
std::vector<Song> AppManager::filterSongs(const std::vector<Song>& songList,
                                          const std::string& nameQuery,
                                          const std::string& genre,
                                          int releaseYear) {
    std::vector<Song> filteredResult;

    for (const auto& song : songList) {
        bool matchName = true;
        bool matchGenre = true;
        bool matchYear = true;

        // فیلتر بر اساس نام (در صورت وارد کردن در جستجو)
        if (!nameQuery.empty()) {
            if (song.getTitle().find(nameQuery) == std::string::npos) {
                matchName = false;
            }
        }

        // فیلتر بر اساس سبک موسیقی (Genre)
        if (!genre.empty()) {
            if (song.getGenre() != genre) {
                matchGenre = false;
            }
        }

        // فیلتر بر اساس سال انتشار
        if (releaseYear > 0) {
            if (song.getReleaseYear() != releaseYear) {
                matchYear = false;
            }
        }

        // اگر تمام فیلترهای انتخاب‌شده برقرار بودند
        if (matchName && matchGenre && matchYear) {
            filteredResult.push_back(song);
        }
    }

    return filteredResult;
}
//  مرتب‌سازی‌ها
// مرتب‌سازی آهنگ‌ها بر اساس نام (صعودی/الفبایی)
std::vector<Song> AppManager::sortSongsByName(std::vector<Song> songList) {
    std::sort(songList.begin(), songList.end(), [](const Song& a, const Song& b) {
        return a.getTitle() < b.getTitle();
    });
    return songList;
}

// مرتب‌سازی آهنگ‌ها بر اساس سال انتشار
std::vector<Song> AppManager::sortSongsByReleaseYear(std::vector<Song> songList) {
    std::sort(songList.begin(), songList.end(), [](const Song& a, const Song& b) {
        return a.getReleaseYear() < b.getReleaseYear();
    });
    return songList;
}

// مرتب‌سازی آلبوم‌ها بر اساس نام (صعودی)
std::vector<Album> AppManager::sortAlbumsByName(std::vector<Album> albumList) {
    std::sort(albumList.begin(), albumList.end(), [](const Album& a, const Album& b) {
        return a.getTitle() < b.getTitle();
    });
    return albumList;
}

// مرتب‌سازی پلی‌لیست‌ها بر اساس نام (صعودی)
std::vector<Playlist> AppManager::sortPlaylistsByName(std::vector<Playlist> playlistList) {
    std::sort(playlistList.begin(), playlistList.end(), [](const Playlist& a, const Playlist& b) {
        return a.getName() < b.getName();
    });
    return playlistList;
}

//  ویرایش حساب کاربری
bool AppManager::updateAccountInfo(const std::string& newName,
                                   const std::string& newUsername,
                                   const std::string& newPassword) {
    if (currentUserId == -1) return false;

    // الف) اگر کاربر آنلاین هنرمند است
    if (currentUserRole == "Artist") {
        std::optional<Account> artistOpt = artistRepo.search(currentUserId);
        if (artistOpt.has_value()) {
            Account artist = artistOpt.value();
            if (!newName.empty()) artist.setFullName(newName);
            if (!newUsername.empty()) artist.setUsername(newUsername);
            if (!newPassword.empty()) artist.setPassword(newPassword);

            artistRepo.save(artist);
            return true;
        }
    }
    // ب) اگر کاربر آنلاین شنونده است
    else if (currentUserRole == "Listener") {
            std::optional<Account> listenerOpt = listenerRepo.search(currentUserId);
            if (listenerOpt.has_value()) {
                Account listener = listenerOpt.value();
                if (!newName.empty()) listener.setFullName(newName);
                if (!newUsername.empty()) listener.setUsername(newUsername);
                if (!newPassword.empty()) listener.setPassword(newPassword);

                listenerRepo.save(listener);
                return true;
            }
        }

        return false;
    }

    //  حذف حساب کاربری جاری
    bool AppManager::deleteCurrentAccount() {
        if (currentUserId == -1) return false;

        bool deleted = false;

        if (currentUserRole == "Artist") {
            deleted = artistRepo.remove(currentUserId);
        } else if (currentUserRole == "Listener") {
            deleted = listenerRepo.remove(currentUserId);
        }

        // پس از حذف حساب، خروج خودکار انجام می‌شود
        if (deleted) {
            logoutUser();
        }

        return deleted;
    }
