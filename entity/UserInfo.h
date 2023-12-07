#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo {
public:
    UserInfo();
    UserInfo(unsigned int id);

    /**
     * @brief Returns the ID of this user.
     */
    [[nodiscard]] unsigned int getId() const;

private:
    unsigned id;
};

#endif // USERINFO_H
