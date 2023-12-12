#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo {
public:
    UserInfo();
    UserInfo(unsigned int id, unsigned int userId, double balance);

    /**
     * @brief Returns the ID of this user info.
     */
    [[nodiscard]] unsigned int getId() const;

    /**
     * @brief Returns the ID of this user.
     */
    [[nodiscard]] unsigned int getUserId() const;

    /**
     * @brief Returns the balance of this user.
     */
    [[nodiscard]] double getBalance() const;

private:
    unsigned id;
    unsigned int userId;
    double balance;
};

#endif // USERINFO_H
