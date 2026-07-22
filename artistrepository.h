#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H

#include <vector>
#include <optional>
#include <string>
#include "accountrepository.h"
#include "account.h"
class ArtistRepository : public AccountRepository {
private:
    std::vector<Account> artistsList;

public:

    int save(const Account& artist) override;
    bool remove(int id) override;
    std::optional<Account> search(int id) override;

    std::optional<Account> searchByUserName(const std::string& username) override;

    const std::vector<Account>& getAll() const ;
};

#endif // ARTISTREPOSITORY_H
