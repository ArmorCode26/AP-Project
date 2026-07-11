#include "album.h"


Album::Album()
    : albumId(0), title(""), artistId(0) {
}

Album::Album(int id, const std::string& albumTitle, int artist)
    : albumId(id), title(albumTitle), artistId(artist) {
}

int Album::getAlbumId() const {
    return albumId;
}

std::string Album::getTitle() const {
    return title;
}

int Album::getArtistId() const {
    return artistId;
}

std::vector<Song> Album::getSongs() const {
    return songs;
}

void Album::setAlbumId(int id) {
    albumId = id;
}

void Album::setTitle(const std::string& albumTitle) {
    title = albumTitle;
}

void Album::setArtistId(int artist) {
    artistId = artist;
}


void Album::addSong(const Song& song) {
    songs.push_back(song);
}
