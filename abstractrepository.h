#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H

#include <optional>

template <typename T>
class AbstractRepository {
public:
    // که اول مخرب فرزند بعد پدر -> مخرب الزامی است
    virtual ~AbstractRepository() = default;

    virtual int save(const T& entity) = 0;//pure virtual->  مجازیه چون قراره تو کلاس فرزند پیاده شه

    virtual bool remove(int id) = 0;

virtual std::optional<T> search(int id) = 0;//یا مقدار پیدا میشه و برمیگردونه یا پیدا نمیشه  و تهی برمیگرده
};

#endif // ABSTRACTREPOSITORY_H
