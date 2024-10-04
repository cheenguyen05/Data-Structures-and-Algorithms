// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include "customtypes.hh"
#include <utility>
#include <vector>
#include <unordered_map>

// Add your own STL includes below this comment
#include <string>
#include <set>

template <typename Type>
Type random_in_range(Type start, Type end);

// This is the class you are supposed to implement

class Datastructures
{
public:
  Datastructures();
  ~Datastructures();

  // Estimate of performance:
  // Short rationale for estimate:
  unsigned int get_bite_count();

  // Estimate of performance:
  // Short rationale for estimate:
  void clear_all();

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> all_bites();

  // Estimate of performance:
  // Short rationale for estimate:
  bool add_bite(BiteID id, const Name &name, Coord xy);

  // Estimate of performance:
  // Short rationale for estimate:
  Name get_bite_name(BiteID id);

  // Estimate of performance:
  // Short rationale for estimate:
  Coord get_bite_coord(BiteID id);

  // We recommend you implement the operations below only after implementing the
  // ones above

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_alphabetically();

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_distance_increasing();

  // Estimate of performance:
  // Short rationale for estimate:
  BiteID find_bite_with_coord(Coord xy);

  // Estimate of performance:
  // Short rationale for estimate:
  bool change_bite_coord(BiteID id, Coord newcoord);

  // Estimate of performance:
  // Short rationale for estimate:
  bool add_contour(ContourID id, const Name & name, ContourHeight height,
                   std::vector<Coord> coords);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> all_contours();

  // Estimate of performance:
  // Short rationale for estimate:
  Name get_contour_name(ContourID id);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<Coord> get_contour_coords(ContourID id);

  // Estimate of performance:
  // Short rationale for estimate:
  ContourHeight get_contour_height(ContourID id);

  // Estimate of performance:
  // Short rationale for estimate:
  bool add_subcontour_to_contour(ContourID id, ContourID parentid);

  // Estimate of performance:
  // Short rationale for estimate:
  bool add_bite_to_contour(BiteID biteid, ContourID contourid);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> get_bite_in_contours(BiteID id);

  // Non-compulsory operations

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> all_subcontours_of_contour(ContourID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_closest_to(Coord /*xy*/);

  // Estimate of performance:
  // Short rationale for estimate:
  bool remove_bite(BiteID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  ContourID get_closest_common_ancestor_of_contours(ContourID /*id1*/,
                                                    ContourID /*id2*/);

private:
  struct BiteInfo {
      Name name;
      Coord coord;
  };
  struct ContourInfo {
      Name name;
      ContourHeight height;
      std::vector<Coord> coords;
      std::vector<ContourID> subcontours; // To store IDs of subcontours
      std::vector<BiteID> bites; // Assuming contours can contain multiple bites
      ContourID parentID;
  };
  // Add stuff needed for your class implementation here
  std::unordered_map<BiteID, BiteInfo> bites_;
  std::unordered_map<ContourID, ContourInfo> contours;
};

#endif // DATASTRUCTURES_HH