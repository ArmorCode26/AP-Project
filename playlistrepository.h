#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H

#include <vector>
#include <optional>
#include "abstractrepository.h"
#include "playlist.h"

class PlaylistRepository : public AbstractRepository<Playlist> {
private:
    std::vector<Playlist> playlistsList;

public:

    int save(const Playlist& entity) override;
    bool remove(int id) override;
    std::optional<Playlist> search(int id) override;

    bool insertSong(int playlistId, int songId);
    bool removeSong(int playlistId, int songId);
    std::vector<Playlist> playlists(int listenerId);
};

#endif // PLAYLISTREPOSITORY_H
