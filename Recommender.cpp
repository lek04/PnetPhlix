#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <unordered_map>

//#include <set>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    udb = &user_database; 
    mdb = &movie_database;
    // Replace this line with correct code.
}

bool Recommender::compMovie(MovieAndRank& x, MovieAndRank& y) const {
    if (x.compatibility_score > y.compatibility_score) {
        return true;
    }
    if (x.compatibility_score < y.compatibility_score) {
        return false;
    }
    if (mdb->get_movie_from_id(x.movie_id)->get_rating() > mdb->get_movie_from_id(y.movie_id)->get_rating())
    {
        return true;
    }
    if (mdb->get_movie_from_id(x.movie_id)->get_rating() < mdb->get_movie_from_id(y.movie_id)->get_rating()) {
        return false;
    }
    return mdb->get_movie_from_id(x.movie_id)->get_title() < mdb->get_movie_from_id(y.movie_id)->get_title();
}

bool Recommender::checkDups(string id,vector<Movie*>& x) const
{
    for (int k = 0; k < x.size(); k++) {
        if (id == x[k]->get_id()) {
            return true;
        }
    }
    return false;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if (movie_count < 0) {
        return vector<MovieAndRank>();
    }

    std::unordered_set<Movie*> recMovies;

    User* uptr = udb->get_user_from_email(user_email); //we find the specific user from email
    if (uptr == nullptr) {
        return vector<MovieAndRank>();
    }

    vector<string> watchHistory;
    watchHistory = uptr->get_watch_history(); //store their watch history (string movieID) into a vector

    vector<Movie*> moviesWatched; //convert string movieID into movie ptrs of all movies in history 
    for (int k = 0; k < watchHistory.size(); k++) {
        moviesWatched.push_back(mdb->get_movie_from_id(watchHistory[k]));
    }

    for (int k = 0; k < moviesWatched.size(); k++) {
        if (moviesWatched[k] == nullptr) {
            continue;
        }
        vector<string> directors = moviesWatched[k]->get_directors(); //collect directors of movie[k]
        vector<string> actors = moviesWatched[k]->get_actors();
        vector<string> genres = moviesWatched[k]->get_genres();
        //createScorefomDirectors(directors, uptr);
        for (int i = 0; i < directors.size();  i++) {
            vector<Movie*> dirMovies;
            dirMovies = mdb->get_movies_with_director(directors[i]);
            for (int l = 0; l < dirMovies.size(); l++) {
                if (std::find(watchHistory.begin(), watchHistory.end(), dirMovies[l]->get_id()) == watchHistory.end()/*!checkDups(dirMovies[l]->get_id(), recMovies*/) { //prevents movies that show up here and in history from being pushed
                    recMovies.insert(dirMovies[l]);
                    //recMovies.push_back(dirMovies[l]);
                }
            }
        }
        for (int i = 0; i < actors.size(); i++) {
            vector<Movie*> actMovies;
            actMovies = mdb->get_movies_with_actor(actors[i]);
            for (int l = 0; l < actMovies.size(); l++) {
                if (std::find(watchHistory.begin(), watchHistory.end(), actMovies[l]->get_id()) == watchHistory.end()/*!checkDups(actMovies[l]->get_id(), recMovies*/) {
                    recMovies.insert(actMovies[l]);
                }
            }
        }
        for (int i = 0; i < genres.size(); i++) {
            vector<Movie*> genMovies;
            genMovies = mdb->get_movies_with_genre(genres[i]);
            for (int l = 0; l < genMovies.size(); l++) {
                if (std::find(watchHistory.begin(), watchHistory.end(), genMovies[l]->get_id()) == watchHistory.end()/*!checkDups(genMovies[l]->get_id(), recMovies*/) {
                    recMovies.insert(genMovies[l]);
                }
            }
        }
        //int x = 0;
    }

    vector<string> dirOfWatchHistory;
    for (int k = 0; k < moviesWatched.size(); k++) {
        if (moviesWatched[k] == nullptr) {
            continue;
        }
        vector<string>dirofMovie = moviesWatched[k]->get_directors();
        for (int i = 0; i < dirofMovie.size(); i++) {
            dirOfWatchHistory.push_back(dirofMovie[i]);
        }
    }

    vector<string> actOfWatchHistory;
    for (int k = 0; k < moviesWatched.size(); k++) {
        if (moviesWatched[k] == nullptr) {
            continue;
        }
        vector<string>dirofMovie = moviesWatched[k]->get_actors();
        for (int i = 0; i < dirofMovie.size(); i++) {
            actOfWatchHistory.push_back(dirofMovie[i]);
        }
    }
    vector<string> genOfWatchHistory;
    for (int k = 0; k < moviesWatched.size(); k++) {
        if (moviesWatched[k] == nullptr) {
            continue;
        }
        vector<string>dirofMovie = moviesWatched[k]->get_genres();
        for (int i = 0; i < dirofMovie.size(); i++) {
            genOfWatchHistory.push_back(dirofMovie[i]);
        }
    }



    //THIS FOR BLOCK NEEDS TO BE OPTIMIZED TOO MANY ITEMS BEING PUSHED INTO RECRANKMOVIE
    vector<MovieAndRank> recRankMovie;
    // what I want: if the same director shows up in recDir movie[k] and in dirofwatchHistory[k] add 20
    for (unordered_set<Movie*>::iterator it = recMovies.begin(); it != recMovies.end(); it++) { //NEED TO FIND A BETTER WAY TO PROCESS MOVIES
        if (std::find(moviesWatched.begin(), moviesWatched.end(), (*it)) != moviesWatched.end()) {
            continue;
        }
        //bool repeated = false;
        MovieAndRank recMovie((*it)->get_id(), 0);
        vector<string> recDir;
        recDir = (*it)->get_directors();
        for (int i = 0; i < recDir.size(); i++) { //vector of directors of movie[k]
            for (int j = 0; j < dirOfWatchHistory.size(); j++) {
                if (recDir[i] == dirOfWatchHistory[j]) {
                    recMovie.compatibility_score += 20;
                }
            }
        }
        vector<string> recAct;
        recAct = (*it)->get_actors();
        for (int i = 0; i < recAct.size(); i++) { //vector of actors of movie[k]
            for (int j = 0; j < actOfWatchHistory.size(); j++) {
                if (recAct[i] == actOfWatchHistory[j]) {
                    recMovie.compatibility_score += 30;
                }
            }
        }
        vector<string> recGen;
        recGen = (*it)->get_genres();
        for (int i = 0; i < recGen.size(); i++) { //vector of genres of movie[k]
            for (int j = 0; j < genOfWatchHistory.size(); j++) {
                if (recGen[i] == genOfWatchHistory[j]) {
                    recMovie.compatibility_score += 1;
                }
            }
        }
        recRankMovie.push_back(recMovie);
        //cerr << recRankMovie.size() << endl;
    }

    sort(recRankMovie.begin(), recRankMovie.end(), [&](MovieAndRank x, MovieAndRank y)
    {
    if (x.compatibility_score > y.compatibility_score) {
        return true;
    }
    if (x.compatibility_score < y.compatibility_score) {
        return false;
    }
    if (mdb->get_movie_from_id(x.movie_id)->get_rating() > mdb->get_movie_from_id(y.movie_id)->get_rating())
    {
        return true;
    }
    if (mdb->get_movie_from_id(x.movie_id)->get_rating() < mdb->get_movie_from_id(y.movie_id)->get_rating()) {
        return false;
    }
    return mdb->get_movie_from_id(x.movie_id)->get_title() < mdb->get_movie_from_id(y.movie_id)->get_title();
    });

    vector<MovieAndRank> refinedList;
    for (vector<MovieAndRank>::iterator it = recRankMovie.begin(); it != recRankMovie.end(); it++) {
        refinedList.push_back(*it);
        if (refinedList.size() >= movie_count) {
            break;
        }
    }



    int del = movie_count;
    if (movie_count >= refinedList.size()) {
        del = refinedList.size();
    }
    refinedList.erase(refinedList.begin() + del, refinedList.end());

    return refinedList;  // Replace this line with correct code.
}

/* AS I PUSHBACK INTO REC MOVIES VECOTR, I SHOULD MAKE A NEW SET CONTAINER THAT STORES THE MOVIEID OF STRINGS OF THE
MOVIES I AM PUSHING BACK. ANYTIME I ADD A NEW MOVIE TO THE REC MOVIE VECTOR I SHOULD TAKE ITS ID AND 
REFER TO THE SET. USE THE FIND FUNCTION (O(LOGN)) AND IF THERE ALREADY EXISTS A MOVIEID IN THE SET, DO NOT
ADD IT TO THE VECTOR*/
