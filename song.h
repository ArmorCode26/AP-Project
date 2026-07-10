#ifndef SONG_H
#define SONG_H
#include<string>
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

public:
    Song();
    Song(string title, int releaseYear, string gener,string filePath, int songId, int artistId, int albumId);

    string getTitle()const;
    int getReleaseYear()const;
    string getGenre()const;
    string getFilePath()const;
    int getSongId()const;
    int getArtistId()const;
    int getAlbumId()const;

    void setTitle(string title);
    void setReleaseYear(int releaseYear);
    void setGenre(string genre);
    void setFilePath(string filePath);
    void setSongId(int songId);
    void setArtistId(int artistId);
    void setAlbumId(int albumId);
};

#endif // SONG_H
