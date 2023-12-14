#ifndef USER_H
#define USER_H

#include <QString>

/**
 * @brief User entity.
 */
class User {
public:
    /**
     * @brief Ceates a user.
     * @param id The ID of this user.
     * @param username The username of this user.
     * @param authString The authentication string (encrypted password).
     * @param email The email of this user.
     */
    User(
        unsigned int id,
        const QString& username,
        const QString& authString,
        const QString& email);

    /**
     * @brief Returns the ID of this user.
     */
    [[nodiscard]] unsigned int getId() const;

    /**
     * @brief Returns the username.
     */
    [[nodiscard]] QString getUsername() const;

    /**
     * @brief Returns the authentication string.
     */
    [[nodiscard]] QString getAuthString() const;

    /**
     * @brief Returns the authentication string.
     */
    [[nodiscard]] QString getEmail() const;

private:
    unsigned int id;
    QString username;
    QString authString;
    QString email;
};

#endif // USER_H
