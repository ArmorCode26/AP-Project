#include "playlistrepository.h"

// ذخیره یا ویرایش پلی‌لیست
int PlaylistRepository::save(const Playlist& entity) {
    for (size_t i = 0; i < playlistsList.size(); i++) {
        if (playlistsList[i].getPlaylistId() == entity.getPlaylistId()) {
            playlistsList[i] = entity;
            return entity.getPlaylistId();
        }
    }

    playlistsList.push_back(entity);
    return entity.getPlaylistId();
}

// حذف پلی‌لیست
bool PlaylistRepository::remove(int id) {
    for (size_t i = 0; i < playlistsList.size(); i++) {
        if (playlistsList[i].getPlaylistId() == id) {
            playlistsList.erase(playlistsList .begin() + i);
            return true;
        }
    }
    return false;
}

// جستجو
std::optional<Playlist> PlaylistRepository::search(int id) {
    for (size_t i = 0; i < playlistsList.size(); i++) {
        if (playlistsList[i].getPlaylistId() == id) {
            return playlistsList[i];
        }
    }
    return std::nullopt;
}

// اضافه کردن آهنگ به پلی‌لیست
bool PlaylistRepository::insertSong(int playlistId, int songId) {
    for (size_t i = 0; i < playlistsList.size(); i++) {
        if (playlistsList[i].getPlaylistId() == playlistId) {
            for (size_t j = 0; j < playlistsList[i].getSongs().size(); j++) {
                if (playlistsList[i].getSongs()[j].getSongId() == songId) {
                    return false; // آهنگ تکراری است
                }
            }
            playlistsList[i].addSong(Song(songId));
            return true;
        }
    }
    return false;
}

// حذف آهنگ از پلی‌لیست
bool PlaylistRepository::removeSong(int playlistId, int songId) {
    for (size_t i = 0; i < playlistsList.size(); i++) {
        if (playlistsList[i].getPlaylistId() == playlistId) {

            std::vector<Song> oldSongs = playlistsList[i].getSongs();
            bool found = false;

            //  چک می‌کنیم ببینیم این آهنگ توی این پلی‌لیست هست یا نه
            for (size_t j = 0; j < oldSongs.size(); j++) {
                if (oldSongs[j].getSongId() == songId) {
                    found = true;
                    break;
                }
            }

            // اگه آهنگ پیدا شد یک پلی‌لیست جدید بدون این آهنگ می‌سازیم و جایگزین می‌کنیم
            if (found) {
                Playlist updatedPlaylist(playlistsList[i].getPlaylistId(), playlistsList[i].getName(), playlistsList[i].getOwnerId());

                for (size_t j = 0; j < oldSongs.size(); j++) {
                    if (oldSongs[j].getSongId() != songId) {
                        updatedPlaylist.addSong(oldSongs[j]);
                    }
                }

                playlistsList[i] = updatedPlaylist; // جایگزینی پلی‌لیست قدیمی با جدید
                return true;
            }
        }
    }
    return false;
}

// برگرداندن تمام پلی‌لیست‌های یک شنونده
std::vector<Playlist> PlaylistRepository::playlists(int listenerId) {
    std::vector<Playlist> result;
    for (size_t i = 0; i < playlistsList.size(); i++) {
        if (playlistsList[i].getOwnerId() == listenerId) {
            result.push_back(playlistsList[i]);
        }
    }
    return result;
}
