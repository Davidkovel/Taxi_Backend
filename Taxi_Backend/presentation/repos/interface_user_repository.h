// IUserRepository.h
#ifndef IUSER_REPOSITORY_H
#define IUSER_REPOSITORY_H

#include "../../domain/domain.h" // temporaly directory path -> the real directory is user.h

class IUserRepository {
public:
    virtual void createUser(const User& user) = 0;
    virtual User* findUserByEmail(const string& email) = 0;
    virtual bool userExists(const string& email) = 0;
    virtual ~IUserRepository() = default;
};

#endif // IUSER_REPOSITORY_H
