#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include "customtypes.hh"
#include <unordered_map>
#include <vector>
#include <string>

template <typename Type>
Type random_in_range(Type start, Type end);

// This is the class you are supposed to implement

class Datastructures
{
public:
  Datastructures();
  ~Datastructures();

  unsigned int get_bite_count();
  void clear_all();
  std::vector<BiteID> all_bites();
  bool add_bite(BiteID id, const Name &name, Coord xy);
  Name get_bite_name(BiteID id);
  Coord get_bite_coord(BiteID id);
  
  std::vector<BiteID> get_bites_alphabetically();
  std::vector<BiteID> get_bites_distance_increasing();
  BiteID find_bite_with_coord(Coord xy);
  bool change_bite_coord(BiteID id, Coord newcoord);

  bool add_contour(ContourID id, const Name &name, ContourHeight height, std::vector<Coord> coords);
  std::vector<ContourID> all_contours();
  Name get_contour_name(ContourID id);
  std::vector<Coord> get_contour_coords(ContourID id);
  ContourHeight get_contour_height(ContourID id);
  bool add_subcontour_to_contour(ContourID id, ContourID parentid);
  bool add_bite_to_contour(BiteID biteid, ContourID parentid);
  std::vector<ContourID> get_bite_in_contours(BiteID id);

  std::vector<ContourID> all_subcontours_of_contour(ContourID id);
  std::vector<BiteID> get_bites_closest_to(Coord xy);
  bool remove_bite(BiteID id);
  ContourID get_closest_common_ancestor_of_contours(ContourID id1, ContourID id2);

private:
  struct Bite {
    Name name;
    Coord coord;
  };

  struct Contour {
    Name name;
    ContourHeight height;
    std::vector<Coord> coords;
  };

  std::unordered_map<BiteID, Bite> bites_;
  std::unordered_map<ContourID, Contour> contours_;
};

#endif // DATASTRUCTURES_HH
