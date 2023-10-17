#include "MovieDatabase.h"
#include "Movie.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
    m_loaded = false;
}

MovieDatabase::~MovieDatabase()
{
    vector<Movie*>::iterator it;
    it = toBeDeleted.begin();
    while (it != toBeDeleted.end()) {
        Movie* film = *it;
        vector<Movie*>::iterator del;
        del = it;
        delete film;
        it++;
        toBeDeleted.erase(del);
        it = toBeDeleted.begin();
    }
}

string MovieDatabase::lowerize(const string& x) const
{
    string lowed;
    for (int k = 0; k < x.size(); k++) {
        lowed += tolower(x.at(k));
    }
    return lowed;
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (m_loaded == true || !infile) {
        return false;
    }

    string movieID;
    while (infile && getline(infile, movieID)) {

        string movieName;
        getline(infile, movieName);

        string movieYear;
        getline(infile, movieYear);

        string movieDirector;
        getline(infile, movieDirector);
        std::vector<std::string> m_directors;
        for (int k = 0; k < movieDirector.size();k++) {
            string singleDir;
            for (; k < movieDirector.size(); k++) {
                if (movieDirector.at(k) != ',') {
                    singleDir += movieDirector.at(k);
                }
                if (movieDirector.at(k) == ',') {
                    break;
                }
            }
            m_directors.push_back(singleDir);
        }

        string movieActors;
        getline(infile, movieActors);
        std::vector<std::string> m_actors;
        for (int k = 0; k < movieActors.size(); k++) {
            string singleDir;
            for (; k < movieActors.size(); k++) {
                if (movieActors.at(k) != ',') {
                    singleDir += movieActors.at(k);
                }
                if (movieActors.at(k) == ',') {
                    break;
                }
            }
            m_actors.push_back(singleDir);
        }

        string movieGenres;
        getline(infile, movieGenres);
        std::vector<std::string> m_genres;
        for (int k = 0; k < movieGenres.size(); k++) {
            string singleDir;
            for (; k < movieGenres.size(); k++) {
                if (movieGenres.at(k) != ',') {
                    singleDir += movieGenres.at(k);
                }
                if (movieGenres.at(k) == ',') {
                    break;
                }
            }
            m_genres.push_back(singleDir);
        }

        string movieRating;
        getline(infile, movieRating);
        float rating;
        /*for (int k = 0; k < movieRating.size(); k++) {
            if (isdigit(movieRating.at(k))) {
                rating += movieRating.at(k) - '0';
                rating *= 10;
            }
        }*/
        rating = stof(movieRating);

        Movie* mptr = new Movie(movieID, movieName, movieYear, m_directors, m_actors, m_genres, rating);
        m_movies.insert(movieID, mptr);
        toBeDeleted.push_back(mptr);

        for (int k = 0; k < m_directors.size(); k++) {
            m_dirMovie.insert(lowerize(m_directors[k]), mptr);
        }
        for (int k = 0; k < m_actors.size(); k++) {
            m_actMovie.insert(lowerize(m_actors[k]), mptr);
        }
        for (int k = 0; k < m_genres.size(); k++) {
            m_genMovie.insert(lowerize(m_genres[k]), mptr);
        }

        string nLine;
        getline(infile, nLine);
        if (nLine.size() == 0) {
            continue;
        }
        else {
            return false;
        }
    }

    return true;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    //multimap<string, Movie*>::const_iterator it;
    /*TreeMultimap<string, Movie*>::Iterator it;
    it = m_movies.find(id);*/
    if (!m_movies.find(id).is_valid()) {
        return nullptr;
    }

    return m_movies.find(id).get_value();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string lowedDir = director;
    lowedDir = lowerize(lowedDir);
    if (!m_dirMovie.find(lowedDir).is_valid()) {
        return vector<Movie*>();
    }
    TreeMultimap<string, Movie*>::Iterator it;
    it = m_dirMovie.find(lowedDir);
    
    vector<Movie*> directedMovies;
    while (it.is_valid()) {
        directedMovies.push_back(it.get_value());
        it.advance();
    }
    return directedMovies;  // Replace this line with correct code. [done]
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string lowedDir = actor;
    lowedDir = lowerize(lowedDir);
    if (!m_actMovie.find(lowedDir).is_valid()) {
        return vector<Movie*>();
    }
    TreeMultimap<string, Movie*>::Iterator it;
    it = m_actMovie.find(lowedDir);

    vector<Movie*> actedMovies;
    while (it.is_valid()) {
        actedMovies.push_back(it.get_value());
        it.advance();
    }
    return actedMovies;  // Replace this line with correct code. [done]
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string lowedDir = genre;
    lowedDir = lowerize(lowedDir);
    if (!m_genMovie.find(lowedDir).is_valid()) {
        return vector<Movie*>();
    }
    TreeMultimap<string, Movie*>::Iterator it;
    it = m_genMovie.find(lowedDir);

    vector<Movie*> genMovies;
    while (it.is_valid()) {
        genMovies.push_back(it.get_value());
        it.advance();
    }
    return genMovies;  // Replace this line with correct code. [done]
}
