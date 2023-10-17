#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>
struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to close this window . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include "Recommender.h"
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";


void findMatches(const Recommender& r,
	const MovieDatabase& md,
	const string& user_email,
	int num_recommendations) {
	// get up to ten movie recommendations for the user
	vector<MovieAndRank> recommendations =
		r.recommend_movies(user_email, num_recommendations);
	if (recommendations.empty())
		cout << "We found no movies to recommend :(.\n";
	else {
		for (int i = 0; i < recommendations.size(); i++) {
			const MovieAndRank& mr = recommendations[i];
			Movie* m = md.get_movie_from_id(mr.movie_id);
			cout << i << ". " << m->get_title() << " ("
				<< m->get_release_year() << ")\n Rating: "
				<< m->get_rating() << "\n Compatibility Score: "
				<< mr.compatibility_score << "\n \n";
		}
	}
}

int main()
{
	UserDatabase udb;
	if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
	
	MovieDatabase mdb;
	if (!mdb.load(MOVIE_DATAFILE)) {
		cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
		return 1;
	}

	Recommender x(udb, mdb);
	cout << "Enter user email address (or quit): ";
	string email;
	getline(cin, email);
	cout << "Enter #: ";
	int y;
	cin >> y;
	findMatches(x, mdb, email, y);

	/*for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			break;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
			cout << "Found " << u->get_full_name() << endl;
	}
	
	for (;;)
	{
		cout << "Enter movieID (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			break;
		Movie* m = mdb.get_movie_from_id(email);
		if (m == nullptr)
			cout << "No movie in the database has that movieID." << endl;
		else
			cout << "Found " << m->get_title() << endl;
	}

	for (;;)
	{
		cout << "Enter Director name: ";
		string name;
		getline(cin, name);
		if (name == "quit")
			break;
		vector<Movie*> x;
		x = mdb.get_movies_with_director(name);
		if (x.size() == 0)
			cout << "Invalid Director or Directed no movies" << endl;
		else {
			cout << "Found. Director has made these movies: " << endl;
			for (int k = 0; k < x.size(); k++) {
				cout << x[k]->get_title() << endl;
			}
		}

	}
	for (;;)
	{
		cout << "Enter actor name: ";
		string name;
		getline(cin, name);
		if (name == "quit")
			break;
		vector<Movie*> x;
		x = mdb.get_movies_with_actor(name);
		if (x.size() == 0)
			cout << "Invalid actor or acted in no movies" << endl;
		else {
			cout << "Found. actor has made these movies: " << endl;
			for (int k = 0; k < x.size(); k++) {
				cout << x[k]->get_title() << endl;
			}
		}

	}
	for (;;)
	{
		cout << "Enter genre: ";
		string name;
		getline(cin, name);
		if (name == "quit")
			break;
		vector<Movie*> x;
		x = mdb.get_movies_with_genre(name);
		if (x.size() == 0)
			cout << "Invalid genre or no movies w/ that genre" << endl;
		else {
			cout << "Found. These movies are in this genre: " << endl;
			for (int k = 0; k < x.size(); k++) {
				cout << x[k]->get_title() << endl;
			}
		}

	}*/
}
