#include "UserDatabase.h"
#include "User.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code. [Done]
    m_loaded = false;
}

UserDatabase::~UserDatabase()
{
    vector<User*>::iterator it;
    it = toBeDeleted.begin();
    while (it != toBeDeleted.end()) {
        User* person = *it;
        vector<User*>::iterator del;
        del = it;
        delete person;
        it++;
        toBeDeleted.erase(del);
        it = toBeDeleted.begin();
    }
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (m_loaded == true || !infile) {
        return false;
    }

    string name;
    while (infile && getline(infile, name)) {
        string email;
        getline(infile, email);

        string numOfMovies;
        int moviesWatched = 0;
        getline(infile, numOfMovies);
        for (int k = 0; k < numOfMovies.size(); k++) {
            moviesWatched += numOfMovies.at(k) - '0';
            moviesWatched *= 10;
        }
        moviesWatched /= 10;

        vector<string> temp;
        for (int k = 0; k < moviesWatched; k++) {
            string movieID;
            getline(infile, movieID);
            temp.push_back(movieID);
        }

        User* uptr = new User(name, email, temp);
        //m_users.insert({ email, uptr });
        m_user.insert(email, uptr);
        toBeDeleted.push_back(uptr);

        string nLine;
        getline(infile, nLine);
        if (nLine.size() == 0) {
            continue;
        }
        else {
            return true;
        }
    }

    return true;  // Replace this line with correct code.
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if (!m_user.find(email).is_valid()) {
        return nullptr;
    }
    return m_user.find(email).get_value();  // Replace this line with correct code.
}
