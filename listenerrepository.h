#ifndef LISTENERREPOSITORY_H
#define LISTENERREPOSITORY_H

#include <vector>
#include <optional>
#include <string>
#include "accountrepository.h"
#include "account.h"

class ListenerRepository : public AccountRepository {
private:
    std::vector<Account> listenersList;


public:

    int save(const Account& listener) override;
    bool remove(int id) override;
    std::optional<Account> search(int id) override;


    std::optional<Account> searchByUserName(const std::string& username) override;

    void updateLiked(int listenerId, int songId, bool likeStatus);
    bool isLiked(int listenerId, int songId);
};

#endif // LISTENERREPOSITORY_H
