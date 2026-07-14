#ifndef ALBUMREPOSITORY_H
#define ALBUMREPOSITORY_H

#include "abstractrepository.h"
#include "album.h"
#include <vector>
#include <optional>

// ارث‌بری از کلاس پایه برای آلبوم
class AlbumRepository : public AbstractRepository<Album> {
private:
    std::vector<Album> albums; // بانک اطلاعاتی موقت درون رم برای آلبوم‌ها

public:

    int save(const Album& entity) override;
    bool remove(int id) override;
    std::optional<Album> search(int id) override;

    std::vector<Album> getByArtist(int artistId);
};

#endif // ALBUMREPOSITORY_H
