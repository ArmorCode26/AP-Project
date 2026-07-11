#include "playlist.h"


Playlist::Playlist()
    : playlistId(0), name(""), ListenerId(0) {
}

Playlist::Playlist(int id, const std::string& playlistName, int listener)
    : playlistId(id), name(playlistName), ListenerId(listener) {
}

int Playlist::getPlaylistId() const {
    return playlistId;
}

std::string Playlist::getName() const {
    return name;
}

int Playlist::getOwnerId() const {
    return ListenerId;
}

std::vector<Song> Playlist::getSongs() const {
    return songs;
}

void Playlist::setPlaylistId(int id) {
    playlistId = id;
}

void Playlist::setName(const std::string& playlistName) {
    name = playlistName;
}

void Playlist::setOwnerId(int listener) {
    ListenerId = listener;
}

void Playlist::addSong(const Song& song) {
    songs.push_back(song);
}
