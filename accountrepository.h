#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H

#include "abstractrepository.h"
#include "account.h"
#include <optional>
#include <string>

class AccountRepository : public AbstractRepository<Account> {
public:
    virtual ~AccountRepository() = default;

    //  هم مجازی  برای فرزندان، هم اوررایدِ پدر
    virtual int save(const Account& entity) override = 0;
    virtual bool remove(int id) override = 0;
    virtual std::optional<Account> search(int id) override = 0;

    // تابع اختصاصی داک پروژه بدون پیاده‌سازی
    virtual std::optional<Account> searchByUsername(const std::string& username) = 0;
};

#endif // ACCOUNTREPOSITORY_H
