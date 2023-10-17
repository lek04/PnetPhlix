#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
      //std::multimap<std::string, User*> m_users;
      TreeMultimap<std::string, User*> m_user;
      bool m_loaded;
      std::vector<User*> toBeDeleted;
};

#endif // USERDATABASE_INCLUDED
