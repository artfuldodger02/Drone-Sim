#include "Singleton.h"

#include <fstream>
#include <iostream>

Singleton* Singleton::singleton_ = nullptr;

Singleton::Singleton() {}

Singleton::~Singleton() {}

Singleton::Singleton(const Singleton& other) = delete;

Singleton& Singleton::operator=(const Singleton& other) = delete;

Singleton* Singleton::get_instance() {
  if (singleton_ == nullptr) {
    singleton_ = new Singleton();
  }
  return singleton_;
}

double Singleton::get_speed(IEntity* drone) {
  singleton_->drone_speed = drone->getSpeed();
  return drone->getSpeed();
}

void Singleton::get_package_startpoint(Package package) {
  singleton_->package_startpoints.push_back(package.getPosition());
}

void Singleton::get_endpoint(Package package) {
  singleton_->endpoints.push_back(package.getDestination());
  singleton_->endpoint_counter += 1;
}

void Singleton::get_distances(Package package, const routing::IGraph* graph) {
  std::string strat = package.getStrategyName();
  singleton_->package_strats.push_back(
      strat);  // quick add the strat to the appropriate array

  // Claculating beeline distances
  Vector3 startpoint = package.getPosition();
  Vector3 endpoint = package.getDestination();
  double beelinedistance = startpoint.dist(endpoint);
  singleton_->beeline_distances.push_back(beelinedistance);

  std::vector<float> vStartpoint = {static_cast<float>(startpoint[0]),
                                    static_cast<float>(startpoint[1]),
                                    static_cast<float>(startpoint[2])};

  std::vector<float> vEndpoint = {static_cast<float>(endpoint[0]),
                                  static_cast<float>(endpoint[1]),
                                  static_cast<float>(endpoint[2])};

  double distance = 0.0;
  std::vector<std::vector<float>> path;

  if (strat == "astar") {
    path = graph->GetPath(vStartpoint, vEndpoint, routing::AStar::Default());
    for (int i = 0; i < path.size() - 1; i++) {
      distance += distance_formula(path.at(i), path.at(i + 1));
    }
    singleton_->astar_distances.push_back(distance);

  } else if (strat == "dfs") {
    path = graph->GetPath(vStartpoint, vEndpoint,
                          routing::DepthFirstSearch::Default());
    for (int i = 0; i < path.size() - 1; i++) {
      distance += distance_formula(path.at(i), path.at(i + 1));
    }
    singleton_->dfs_distances.push_back(distance);

  } else if (strat == "bfs") {
    path = graph->GetPath(vStartpoint, vEndpoint,
                          routing::BreadthFirstSearch::Default());
    for (int i = 0; i < path.size() - 1; i++) {
      distance += distance_formula(path.at(i), path.at(i + 1));
    }
    singleton_->bfs_distances.push_back(distance);

  } else {  // dijkstra
    path =
        graph->GetPath(vStartpoint, vEndpoint, routing::Dijkstra::Instance());
    for (int i = 0; i < path.size() - 1; i++) {
      distance += distance_formula(path.at(i), path.at(i + 1));
    }
    singleton_->dijkstra_distances.push_back(distance);
  }
  singleton_->package_distances.push_back(distance);
}

double Singleton::distance_formula(std::vector<float> start,
                                   std::vector<float> end) {
  std::vector<double> x = {static_cast<double>(start.at(0)),
                           static_cast<double>(start.at(1)),
                           static_cast<double>(start.at(2))};
  std::vector<double> y = {static_cast<double>(end.at(0)),
                           static_cast<double>(end.at(1)),
                           static_cast<double>(end.at(2))};

  double d = std::sqrt(std::pow(end.at(0) - start.at(0), 2) +
                       std::pow(end.at(1) - start.at(0), 2));

  return d;
}

void Singleton::get_strat_times() {
  double time = 0.0;
  // get astar times
  if (singleton_->astar_distances.size() > 0) {
    for (int i = 0; i < singleton_->astar_distances.size(); i++) {
      time = singleton_->astar_distances[i] / singleton_->drone_speed;
      singleton_->astar_times.push_back(time);
    }
  }
  // get dfs times
  if (singleton_->dfs_distances.size() > 0) {
    for (int i = 0; i < singleton_->dfs_distances.size(); i++) {
      time = singleton_->dfs_distances[i] / singleton_->drone_speed;
      singleton_->dfs_times.push_back(time);
    }
  }
  // get bfs times
  if (singleton_->bfs_distances.size() > 0) {
    for (int i = 0; i < singleton_->bfs_distances.size(); i++) {
      time = singleton_->bfs_distances[i] / singleton_->drone_speed;
      singleton_->bfs_times.push_back(time);
    }
  }
  // get dijkstra times
  if (singleton_->dijkstra_distances.size() > 0) {
    for (int i = 0; i < singleton_->dijkstra_distances.size(); i++) {
      time = singleton_->dijkstra_distances[i] / singleton_->drone_speed;
      singleton_->dijkstra_times.push_back(time);
    }
  }
  // get beeline times
  if (singleton_->beeline_distances.size() > 0) {
    for (int i = 0; i < singleton_->beeline_distances.size(); i++) {
      time = singleton_->beeline_distances[i] / singleton_->drone_speed;
      singleton_->beeline_times.push_back(time);
    }
  }
}

void Singleton::get_package_times() {
  double time = 0.0;
  for (int i = 0; i < singleton_->package_distances.size(); i++) {
    time = singleton_->package_distances[i] / singleton_->drone_speed;
    singleton_->package_times.push_back(time);
  }
}

void Singleton::get_downtime(Package package) {
  if (singleton_->endpoint_counter >= 1) {
    Vector3 drone_pos = singleton_->endpoints[singleton_->endpoint_counter - 1];

    Vector3 package_pos = package.getPosition();

    double distance = drone_pos.dist(package_pos);

    double dtime = distance / singleton_->drone_speed;

    singleton_->downtimes.push_back(dtime);

  } else {  // add a 0 to the front, so downtimes can be the same size as
            // everything else

    singleton_->downtimes.push_back(0.0);
  }
}

void Singleton::analyze_data() {
  singleton_->avg_astar_time = 0.0;
  singleton_->avg_beeline_time = 0.0;
  singleton_->avg_bfs_time = 0.0;
  singleton_->avg_dfs_time = 0.0;
  singleton_->avg_dijkstra_time = 0.0;

  singleton_->avg_astar_distance = 0.0;
  singleton_->avg_beeline_distance = 0;
  singleton_->avg_bfs_distance = 0.0;
  singleton_->avg_dfs_distance = 0.0;
  singleton_->avg_dijkstra_distance = 0.0;

  // check to see if we have any astar times
  if (singleton_->astar_times.size() > 0) {
    for (int i = 0; i < singleton_->astar_times.size(); i++) {
      singleton_->avg_astar_time += singleton_->astar_times[i];
      singleton_->avg_astar_distance += singleton_->astar_distances[i];
    }
    // if we do, calculate averages
    singleton_->avg_astar_time =
        singleton_->avg_astar_time / singleton_->astar_times.size();
    singleton_->avg_astar_distance =
        singleton_->avg_astar_distance / singleton_->astar_distances.size();
  }
  // assign details
  // if there is no entries in astar, it'll default to 0
  singleton_->astar_details.push_back(singleton_->drone_speed);
  singleton_->astar_details.push_back(singleton_->avg_astar_distance);
  singleton_->astar_details.push_back(singleton_->avg_astar_time);

  // repeat above for each strat
  // beeline
  if (singleton_->beeline_times.size() > 0) {
    for (int i = 0; i < singleton_->beeline_times.size(); i++) {
      singleton_->avg_beeline_time += singleton_->beeline_times[i];
      singleton_->avg_beeline_distance += singleton_->beeline_distances[i];
    }
    singleton_->avg_beeline_time =
        singleton_->avg_beeline_time / singleton_->beeline_times.size();
    singleton_->avg_beeline_distance =
        singleton_->avg_beeline_distance / singleton_->beeline_distances.size();
  }
  singleton_->beeline_details.push_back(singleton_->drone_speed);
  singleton_->beeline_details.push_back(singleton_->avg_beeline_distance);
  singleton_->beeline_details.push_back(singleton_->avg_beeline_time);

  // bfs
  if (singleton_->bfs_times.size() > 0) {
    for (int i = 0; i < singleton_->bfs_times.size(); i++) {
      singleton_->avg_bfs_time += singleton_->bfs_times[i];
      singleton_->avg_bfs_distance += singleton_->bfs_distances[i];
    }
    singleton_->avg_bfs_time =
        singleton_->avg_bfs_time / singleton_->bfs_times.size();
    singleton_->avg_bfs_distance =
        singleton_->avg_bfs_distance / singleton_->bfs_distances.size();
  }
  singleton_->bfs_details.push_back(singleton_->drone_speed);
  singleton_->bfs_details.push_back(singleton_->avg_bfs_distance);
  singleton_->bfs_details.push_back(singleton_->avg_bfs_time);

  // dfs
  if (singleton_->dfs_times.size() > 0) {
    for (int i = 0; i < singleton_->dfs_times.size(); i++) {
      singleton_->avg_dfs_time += singleton_->dfs_times[i];
      singleton_->avg_dfs_distance += singleton_->dfs_distances[i];
    }
    singleton_->avg_dfs_time =
        singleton_->avg_dfs_time / singleton_->dfs_times.size();
    singleton_->avg_dfs_distance =
        singleton_->avg_dfs_distance / singleton_->dfs_distances.size();
  }
  singleton_->dfs_details.push_back(singleton_->drone_speed);
  singleton_->dfs_details.push_back(singleton_->avg_dfs_distance);
  singleton_->dfs_details.push_back(singleton_->avg_dfs_time);

  // dijkstra
  if (singleton_->dijkstra_times.size() > 0) {
    for (int i = 0; i < singleton_->dijkstra_times.size(); i++) {
      singleton_->avg_dijkstra_time += singleton_->dijkstra_times[i];
      singleton_->avg_dijkstra_distance += singleton_->dijkstra_distances[i];
    }
    singleton_->avg_dijkstra_time =
        singleton_->avg_dijkstra_time / singleton_->dijkstra_times.size();
    singleton_->avg_dijkstra_distance = singleton_->avg_dijkstra_distance /
                                        singleton_->dijkstra_distances.size();
  }
  singleton_->dijkstra_details.push_back(singleton_->drone_speed);
  singleton_->dijkstra_details.push_back(singleton_->avg_dijkstra_distance);
  singleton_->dijkstra_details.push_back(singleton_->avg_dijkstra_time);
}

void Singleton::export_to_csv() {
  std::ofstream file;
  file.open("analysis.csv");
  file << "Raw Data\n";
  file << "Packages, Pickup, Dropoff, Time, Strategy, Downtime, Distance\n";

  for (int i = 0; i < singleton_->package_startpoints.size(); i++) {
    file << "package " + std::to_string(i) + ", ";

    file << std::to_string(singleton_->package_startpoints.at(i)[0]) + " . " +
                std::to_string(singleton_->package_startpoints.at(i)[1]) +
                " . " +
                std::to_string(singleton_->package_startpoints.at(i)[2]) +
                ", " + std::to_string(singleton_->endpoints.at(i)[0]) + " . " +
                std::to_string(singleton_->endpoints.at(i)[1]) + " . " +
                std::to_string(singleton_->endpoints.at(i)[2]) + ", " +
                std::to_string(singleton_->package_times.at(i)) + ", " +
                singleton_->package_strats.at(i) + ", " +
                std::to_string(singleton_->downtimes.at(i)) + ", " +
                std::to_string(singleton_->package_distances.at(i)) + ", \n";
  }

  file << "\n";
  file << "\n";

  file << "Analyzed Data\n";
  file << "Strategies, Average Speed, Average Distance, Average "
          "Time\n";

  file << "Astar, " + std::to_string(singleton_->astar_details.at(0)) + ", " +
              std::to_string(singleton_->astar_details.at(1)) + ", " +
              std::to_string(singleton_->astar_details.at(2)) + "\n";

  file << "BFS," + std::to_string(singleton_->bfs_details.at(0)) + ", " +
              std::to_string(singleton_->bfs_details.at(1)) + ", " +
              std::to_string(singleton_->bfs_details.at(2)) + "\n";

  file << "DFS," + std::to_string(singleton_->dfs_details.at(0)) + ", " +
              std::to_string(singleton_->dfs_details.at(1)) + ", " +
              std::to_string(singleton_->dfs_details.at(2)) + "\n";

  file << "Dijkstra," + std::to_string(singleton_->dijkstra_details.at(0)) +
              ", " + std::to_string(singleton_->dijkstra_details.at(1)) + ", " +
              std::to_string(singleton_->dijkstra_details.at(2)) + "\n";

  file << "Beeline," + std::to_string(singleton_->beeline_details.at(0)) +
              ", " + std::to_string(singleton_->beeline_details.at(1)) + ", " +
              std::to_string(singleton_->beeline_details.at(2)) + "\n";

  file.close();
}
