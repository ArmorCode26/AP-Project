#ifndef SONG_H
#define SONG_H
#include<string>
#include<vector>
using namespace std;

class Song
{
private:
      string title; // نام اهنگ
      int releaseYear;//سال انتشار
      string genre;//سبک اهنک
      string filePath;//فایل صوتی
      int songId;//شناسه اهنگ
      int artistId;//شماسه هنرمند
      int albumId;//شناسه البوم
       int playlistId=-1;//شناسه پلی لیست برای تابع getByplaylist
        std::vector<int>likedUserIds;//ایدی کاربرانی ک اهنگ لایک کردند برای تابع getByLikedSongs
public:
    Song();
    Song(int id); //برای تابعinsertSong در playlistRepository
    Song(string title, int releaseYear, string gener,string filePath, int songId, int artistId, int albumId);

    string getTitle()const;
    int getReleaseYear()const;
    string getGenre()const;
    string getFilePath()const;
    int getSongId()const;
    int getArtistId()const;
    int getAlbumId()const;
    int getPlaylistId()const;
    std::vector<int> getlikedUserIds()const;

    void setTitle(string title);
    void setReleaseYear(int releaseYear);
    void setGenre(string genre);
    void setFilePath(string filePath);
    void setSongId(int songId);
    void setArtistId(int artistId);
    void setAlbumId(int albumId);
    void setPlaylistId(int albumId);

    void addlikedUserIds(int userId);
};

#endif // SONG_H
