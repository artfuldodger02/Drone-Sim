#include "Singleton.h"

#include <fstream>
#include <iostream>

Singleton::Singleton() { singleton_ = nullptr; }

Singleton::~Singleton() { delete singleton_; }

Singleton::Singleton(const Singleton& other) = delete;

Singleton& Singleton::operator=(const Singleton& other) = delete;

Singleton* Singleton::get_instance() {
  if (singleton_ == nullptr) {
    singleton_ = new Singleton();
  } else {
    return singleton_;
  }
}

float Singleton::get_speed(Drone drone) {}

void Singleton::get_drone_startpoint(Drone drone) {}

void Singleton::get_package_startpoint(Package package) {}

void Singleton::get_endpoint(Drone drone) {}

void Singleton::get_distances(IStrategy* strat) {}

void Singleton::get_strat_time(IStrategy* strat) {}

void Singleton::get_downtime() {}

void Singleton::analyze_data() {}

void Singleton::export_to_csv() {
  std::ofstream file;
  file.open("analysis.csv");
  file << "Raw Data\n";
  file << ",Pickup, Dropoff, Time, Strategy, Downtime, Distance";

  for (int i = 1; i <= package_startpoints.size(); i++) {
    file << "package" + std::to_string(i) + ",";
    file << std::to_string(package_startpoints.at(i)[0]) + "." +
                std::to_string(package_startpoints.at(i)[1]) + "." +
                std::to_string(package_startpoints.at(i)[2]) + "," +
                std::to_string(endpoints.at(i)[0]) + "." +
                std::to_string(endpoints.at(i)[1]) + "." +
                std::to_string(endpoints.at(i)[2]) + "," +
                std::to_string(package_times.at(i)) + "," +
                std::to_string(package_strats.at(i)) + "," +
                std::to_string(downtimes.at(i)) + "," +
                std::to_string(package_distances.at(i)) + ",\n";
  }
  file << "\n";
  file << "\n";

  file << "Analyzed Data\n";
  file << ", Average Speed, Average Distance, Average Crowfly time, Average "
          "Time\n";

  file << "Astar," + std::to_string(astar_details.at(0)) + "," +
              std::to_string(astar_details.at(1)) + "," +
              std::to_string(astar_details.at(2)) + "\n";
  file << "BFS," + std::to_string(bfs_details.at(0)) + "," +
              std::to_string(bfs_details.at(1)) + "," +
              std::to_string(bfs_details.at(2)) + "\n";
  file << "DFS," + std::to_string(dfs_details.at(0)) + "," +
              std::to_string(dfs_details.at(1)) + "," +
              std::to_string(dfs_details.at(2)) + "\n";
  file << "Dikjstra," + std::to_string(dikjstra_details.at(0)) + "," +
              std::to_string(dikjstra_details.at(1)) + "," +
              std::to_string(dikjstra_details.at(2)) + "\n";
  file << "Beeline," + std::to_string(beeline_details.at(0)) + "," +
              std::to_string(beeline_details.at(1)) + "," +
              std::to_string(beeline_details.at(2)) + "\n";
}
