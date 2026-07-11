#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include <vector>
#include "song.h"

class Album {
private:
    int albumId;//شناسه البوم
    std::string title;//نام
    int artistId;//شناسه هنرمند صاحب
    std::vector<Song> songs; // لیستی از آهنگ‌های این آلبوم

public:
    Album();

    Album(int id, const std::string& albumTitle, int artist);

    int getAlbumId() const;
    std::string getTitle() const;
    int getArtistId() const;
    std::vector<Song> getSongs() const;

    void setAlbumId(int id);
    void setTitle(const std::string& albumTitle);
    void setArtistId(int artist);

    void addSong(const Song& song);
};

#endif // ALBUM_H
