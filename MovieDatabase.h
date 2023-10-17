#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include"treemm.h"
//#include <map>


class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
      TreeMultimap<std::string, Movie*> m_movies;
      //TreeMultimap<std::string, std::vector<Movie*>> m_dirMovie;
      TreeMultimap<std::string, Movie*> m_dirMovie;
      TreeMultimap<std::string, Movie*> m_actMovie;
      TreeMultimap<std::string, Movie*> m_genMovie;
      bool m_loaded;
      std::string lowerize(const std::string& x) const;
      std::vector<Movie*> toBeDeleted;
};

#endif // MOVIEDATABASE_INCLUDED
