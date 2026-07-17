#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H

#include <vector>
#include "abstractrepository.h"
#include "song.h"
#include"playlistrepository.h"
#include "listenerrepository.h"

// این کلاس از کلاس انتزاعی برای موجودیت Song ارث‌بری می‌کند
class SongRepository : public AbstractRepository<Song> {
private:
    std::vector<Song> songs; // بانک اطلاعاتی موقت برای ذخیره آهنگ‌ها در حافظه
    PlaylistRepository playlistRepo; // برای تابع getByPlaylist
    ListenerRepository listenerRepo;// برای تابع getByPlaylist

public:

    int save(const Song& entity) override;
    bool remove(int id) override;
    std::optional<Song> search(int id) override;

    std::vector<Song> singleSongs(int artistId);
    std::vector<Song> getByAlbum(int albumId);
    std::vector<Song> getByArtist(int artistId);
    std::vector<Song> getByPlaylist(int playlistId);
    std::vector<Song> getByLikedSongs(int listenerId);
};

#endif // SONGREPOSITORY_H
