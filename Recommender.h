#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
//#include "treemm.h"
#include <map>

class UserDatabase;
class MovieDatabase;
class Movie;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
      const UserDatabase* udb;
      const MovieDatabase* mdb;
      bool compMovie(MovieAndRank& x, MovieAndRank& y) const;
      bool checkDups(std::string id,std::vector<Movie*>& x) const;
      //int countTrue(std::vector<MovieAndRank> x, int n) const;
      //std::map<MovieAndRank, int> m_recMovies;
};

#endif // RECOMMENDER_INCLUDED
