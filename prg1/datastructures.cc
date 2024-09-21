#include "datastructures.hh"
#include "customtypes.hh"
#include <algorithm>
#include <stdexcept>

Datastructures::Datastructures()
{
    // Constructor: nothing special required here.
}

Datastructures::~Datastructures()
{
    // Destructor: the unordered_map will clean itself up.
}

unsigned int Datastructures::get_bite_count()
{
    return bites_.size();
}

void Datastructures::clear_all()
{
    bites_.clear();
    contours_.clear();
}

std::vector<BiteID> Datastructures::all_bites()
{
    std::vector<BiteID> bite_ids;
    for (const auto& [id, bite] : bites_) {
        bite_ids.push_back(id);
    }
    return bite_ids;
}

bool Datastructures::add_bite(BiteID id, const Name &name, Coord xy)
{
    if (bites_.find(id) != bites_.end()) {
        return false; // Bite with this ID already exists
    }
    bites_[id] = Bite{name, xy};
    return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
    if (bites_.find(id) != bites_.end()) {
        return bites_.at(id).name;
    }
    throw std::out_of_range("Bite ID not found");
}

Coord Datastructures::get_bite_coord(BiteID id)
{
    if (bites_.find(id) != bites_.end()) {
        return bites_.at(id).coord;
    }
    throw std::out_of_range("Bite ID not found");
}

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
    std::vector<BiteID> bite_ids = all_bites();
    std::sort(bite_ids.begin(), bite_ids.end(), [this](BiteID a, BiteID b) {
        return bites_[a].name < bites_[b].name;
    });
    return bite_ids;
}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
    std::vector<BiteID> bite_ids = all_bites();
    std::sort(bite_ids.begin(), bite_ids.end(), [this](BiteID a, BiteID b) {
        auto dist_a = bites_[a].coord.x * bites_[a].coord.x + bites_[a].coord.y * bites_[a].coord.y;
        auto dist_b = bites_[b].coord.x * bites_[b].coord.x + bites_[b].coord.y * bites_[b].coord.y;
        return dist_a < dist_b;
    });
    return bite_ids;
}
