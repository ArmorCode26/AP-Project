 #ifndef APPMANAGER_H
#define APPMANAGER_H

#include <vector>
#include <string>

#include "song.h"
#include "playlist.h"
#include "album.h"
#include "account.h"

#include "songrepository.h"
#include "playlistrepository.h"
#include "albumrepository.h"
#include "accountrepository.h"
#include "artistrepository.h"
#include "listenerrepository.h"

class AppManager {
private:
    // انبار داده‌ها (ریپازیتوری‌ها)
    SongRepository songRepo;
    PlaylistRepository playlistRepo;
    AlbumRepository albumRepo;
    ArtistRepository artistRepo;
    ListenerRepository listenerRepo; //

    int currentUserId = -1;//مدیریت وضعیت کاربر فعلی
    std::string currentUserRole = ""; // Artist یا Listener

public:
    AppManager() = default;

    //  مدیریت حساب کاربر، ورود و ثبت‌نام
    bool registerUser(const std::string& name, const std::string& username,
                      const std::string& password, const std::string& role,
                      const std::string& biography);
    bool loginUser(const std::string& username, const std::string& password);
    void logoutUser();

    // قابلیت‌های هنرمندان
    void createAlbum(const std::string& title);
    void createSong(const std::string& title,int releaseYear,const std::string& genre, const std::string& filePath ,int albumId);
    void editSong(int songId, const std::string& newTitle, int newReleaseYear,const std::string& newGenre, const std::string& newFilePath  );
   void editAlbum(int albumId, const std::string& newTitle, const std::vector<Song>& newSongs);
    void deleteSong(int songId);
    void deleteAlbum(int albumId);

    std::vector<Album> getAlbums(int artistId);
    std::vector<Song> getSingleSongs(int artistId);

    // قابلیت‌های شنوندگان
    std::vector<Account> getAllArtists();
    std::vector<Playlist> getMyPlaylists();

    void createPlaylist(const std::string& playlistName);
    void editPlaylist(int playlistId, const std::string& newName);
    void deletePlaylist(int playlistId);
    void addSongToPlaylist(int playlistId, int songId);
    void removeSongFromPlaylist(int playlistId, int songId);
    void toggleLikeSong(int songId);
    //  قابلیت‌های مشترک
    std::vector<Song> filterSongs(const std::vector<Song>& songList,const std::string& nameQuery = "",const std::string& genre = "",int releaseYear = 0);

    std::vector<Song> sortSongsByName(std::vector<Song> songList);
    std::vector<Song> sortSongsByReleaseYear(std::vector<Song> songList);
    std::vector<Album> sortAlbumsByName(std::vector<Album> albumList);
    std::vector<Playlist> sortPlaylistsByName(std::vector<Playlist> playlistList);

    bool updateAccountInfo(const std::string& newName, const std::string& newUsername,  const std::string& newPassword);

    bool deleteCurrentAccount();
    //گتر ها
    int getCurrentUserId() const { return currentUserId; }
    std::string getCurrentUserRole() const { return currentUserRole; }
};

#endif // APPMANAGER_H
