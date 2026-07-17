#include "song.h"

Song::Song()
    : title(""), releaseYear(0), genre(""), filePath(""), songId(0), artistId(0), albumId(0) {

}
Song::Song(int id):songId(id){

}
Song::Song(std::string title, int releaseYear, std::string genre, std::string filePath, int songId, int artistId, int albumId)
    : title(title), releaseYear(releaseYear), genre(genre), filePath(filePath), songId(songId), artistId(artistId), albumId(albumId) {

}


std::string Song::getTitle() const { return title; }
int Song::getReleaseYear() const { return releaseYear; }
std::string Song::getGenre() const { return genre; }
std::string Song::getFilePath() const { return filePath; }
int Song::getSongId() const { return songId; }
int Song::getArtistId() const { return artistId; }
int Song::getAlbumId() const { return albumId; }
int Song::getPlaylistId() const { return playlistId; }
std::vector<int> Song:: getlikedUserIds()const {return likedUserIds; }

void Song::setTitle(std::string title) { this->title = title; }
void Song::setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }
void Song::setGenre(std::string genre) { this->genre = genre; }
void Song::setFilePath(std::string filePath) { this->filePath = filePath; }
void Song::setSongId(int songId) { this->songId = songId; }
void Song::setArtistId(int artistId) { this->artistId = artistId; }
void Song::setAlbumId(int albumId) { this->albumId = albumId; }
void Song::setPlaylistId(int playlistId) { this->playlistId = playlistId; }

void Song::addlikedUserIds(int userId){getlikedUserIds().push_back(userId); }
