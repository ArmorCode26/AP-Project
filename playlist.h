 #ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "song.h"

class Playlist {
private:
    int playlistId;//شناسه لیست پخش
    std::string name;
    int ListenerId;// شناسه شنونده صاحب
    std::vector<Song> songs; // مجموعه آهنگ‌های لیست پخش

public:

    Playlist();
    Playlist(int id, const std::string& playlistName, int listener);

    int getPlaylistId() const;
    std::string getName() const;
    int getOwnerId() const;
    std::vector<Song> getSongs() const;

    void setPlaylistId(int id);
    void setName(const std::string& playlistName);
    void setOwnerId(int listener);

    void addSong(const Song& song);
};

#endif // PLAYLIST_H
