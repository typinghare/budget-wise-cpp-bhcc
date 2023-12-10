#include "User.h"

User::User(
    unsigned int id,
    const QString& username,
    const QString& authString,
    const QString& email):
    id(id),
    username(username),
    authString(authString),
    email(email) {
}

unsigned int User::getId() const {
    return id;
}

QString User::getUsername() const {
    return username;
}

QString User::getAuthString() const {
    return authString;
}

QString User::getEmail() const {
    return email;
}
