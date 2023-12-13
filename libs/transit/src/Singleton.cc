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


float Singleton::get_speed(IEntity* drone){
  singleton_->drone_speed = drone->getSpeed();
  return drone->getSpeed();
}

// void Singleton::get_drone_startpoint(IEntity* drone){
//     drone_startpoints.push_back(drone->getPosition());
// }

void Singleton::get_package_startpoint(Package package){
  singleton_->package_startpoints.push_back(package.getPosition());
}

void Singleton::get_endpoint(Package package){
  singleton_->endpoints.push_back(package.getDestination());
}

void Singleton::get_distances(Package package){ //ask TA's on friday
  std::string strat = package.getStrategyName();
  singleton_->package_strats.push_back(
      strat);  // quick add the strat to the appropriate array

  Vector3 startpoint = package.getPosition();
  Vector3 endpoint = package.getDestination();
  float distance = startpoint.dist(endpoint);
  singleton_->package_distances.push_back(
      distance);  // quick add the distance to the appropriate array

  if (strat == "astar") {
    singleton_->astar_distances.push_back(distance);
    } else if (strat == "dfs") {
        singleton_->dfs_distances.push_back(distance);
    } else if (strat == "bfs") {
        singleton_->bfs_distances.push_back(distance);
    } else if (strat == "dijkstra") {
        singleton_->dijkstra_distances.push_back(distance);
    } else { //beeline
        singleton_->beeline_distances.push_back(distance);
    }   
}

void Singleton::get_strat_times(){
  float time = 0.0;
  // get astar times
  for (int i = 0; i < singleton_->astar_distances.size(); i++) {
    time = singleton_->astar_distances[i] / drone_speed;
    singleton_->astar_times.push_back(time);
    }
    // get dfs times
    for(int i = 0; i < singleton_->dfs_distances.size(); i++){
        time = singleton_->dfs_distances[i] / drone_speed;
        singleton_->dfs_times.push_back(time);
    }
    // get bfs times
    for(int i = 0; i < bfs_distances.size(); i++){
        time = singleton_->bfs_distances[i] / drone_speed;
        singleton_->bfs_times.push_back(time);
    }
    // get dijkstra times
    for(int i = 0; i < singleton_->dijkstra_distances.size(); i++){
        time = singleton_->dijkstra_distances[i] / drone_speed;
        singleton_->dijkstra_times.push_back(time);
    }
    // get beeline times
    for(int i = 0; i < singleton_->beeline_distances.size(); i++){
        time = singleton_->beeline_distances[i] / drone_speed;
        singleton_->beeline_times.push_back(time);
    }    
}

void Singleton::get_package_times(){
  float time = 0.0;
  for (int i = 0; i < singleton_->package_distances.size(); i++) {
    time = singleton_->package_distances[i] / drone_speed;
    singleton_->package_times.push_back(time);
    }
}

void Singleton::get_downtime(Package package){

  if (singleton_->endpoints.size() > 0) {
    std::cout << "test 8a\n";
    Vector3 drone_pos = singleton_->endpoints[endpoints.size() - 1];
    std::cout << "test 8b\n";
    Vector3 package_pos = package.getPosition();
    std::cout << "test 8c\n";
    double distance = drone_pos.dist(package_pos);
    std::cout << "test d\n";
    singleton_->downtimes.push_back(distance / drone_speed);
    }
}

void Singleton::analyze_data(){
  avg_astar_time = 0;
  avg_beeline_time = 0;
  avg_bfs_time = 0;
  avg_dfs_time = 0;
  avg_dijkstra_time = 0;

  avg_astar_distance = 0;
  avg_beeline_distance = 0;
  avg_bfs_distance = 0;
  avg_dfs_distance = 0;
  avg_dijkstra_distance = 0;

  for (int i = 0; i < singleton_->astar_times.size(); i++) {
    avg_astar_time += singleton_->astar_times[i];
    avg_astar_distance += singleton_->astar_distances[i];
    }
    avg_astar_time = avg_astar_time / singleton_->astar_times.size();
    avg_astar_distance = avg_astar_distance / singleton_->astar_distances.size();

    singleton_->astar_details.push_back(drone_speed);
    singleton_->astar_details.push_back(avg_astar_distance);
    singleton_->astar_details.push_back(avg_astar_time);

    

    for(int i = 0; i < singleton_->beeline_times.size(); i++){
        avg_astar_time += singleton_->beeline_times[i];
        avg_beeline_distance += singleton_->beeline_distances[i];
    }
    avg_beeline_time = avg_beeline_time / singleton_->beeline_times.size();
    avg_beeline_distance = avg_beeline_distance / singleton_->beeline_distances.size();

    singleton_->beeline_details.push_back(drone_speed);
    singleton_->beeline_details.push_back(avg_beeline_distance);
    singleton_->beeline_details.push_back(avg_beeline_time);
    

    for(int i = 0; i < singleton_->bfs_times.size(); i++){
        avg_bfs_time += singleton_->bfs_times[i];
        avg_bfs_distance += singleton_->bfs_distances[i];
    }
    avg_bfs_time = avg_bfs_time / singleton_->bfs_times.size();
    avg_bfs_distance = avg_bfs_distance / singleton_->bfs_distances.size();

    singleton_->bfs_details.push_back(drone_speed);
    singleton_->bfs_details.push_back(avg_bfs_distance);
    singleton_->bfs_details.push_back(avg_bfs_time);
    

    for(int i = 0; i < singleton_->dfs_times.size(); i++){
        avg_dfs_time += singleton_->dfs_times[i];
        avg_dfs_distance += singleton_->dfs_distances[i];
    }
    avg_dfs_time = avg_dfs_time / singleton_->dfs_times.size();
    avg_dfs_distance = avg_dfs_distance / singleton_->dfs_distances.size();

    singleton_->dfs_details.push_back(drone_speed);
    singleton_->dfs_details.push_back(avg_dfs_distance);
    singleton_->dfs_details.push_back(avg_dfs_time);
    

    for(int i = 0; i < singleton_->dijkstra_times.size(); i++){
        avg_dijkstra_time += singleton_->dijkstra_times[i];
        avg_dijkstra_time += singleton_->dijkstra_distances[i];
    }
    avg_dijkstra_time = avg_dijkstra_time / singleton_->dijkstra_times.size();
    avg_dijkstra_distance = avg_dijkstra_distance / singleton_->dijkstra_distances.size();

    singleton_->dijkstra_details.push_back(drone_speed);
    singleton_->dijkstra_details.push_back(avg_dijkstra_distance);
    singleton_->dijkstra_details.push_back(avg_dijkstra_time);
    
}

void Singleton::export_to_csv() {
  std::ofstream file;
  file.open("analysis.csv");
  file << "Raw Data\n";
  file << ",Pickup, Dropoff, Time, Strategy, Downtime, Distance";

  for (int i = 1; i <= singleton_->package_startpoints.size(); i++) {
    file << "package" + std::to_string(i) + ",";
    file << std::to_string(singleton_->package_startpoints.at(i)[0]) + "." +
                std::to_string(singleton_->package_startpoints.at(i)[1]) + "." +
                std::to_string(singleton_->package_startpoints.at(i)[2]) + "," +
                std::to_string(singleton_->endpoints.at(i)[0]) + "." +
                std::to_string(singleton_->endpoints.at(i)[1]) + "." +
                std::to_string(singleton_->endpoints.at(i)[2]) + "," +
                std::to_string(singleton_->package_times.at(i)) + "," +
                singleton_->package_strats.at(i) + "," +
                std::to_string(singleton_->downtimes.at(i)) + "," +
                std::to_string(singleton_->package_distances.at(i)) + ",\n";

  }
  file << "\n";
  file << "\n";

  file << "Analyzed Data\n";
  file << ", Average Speed, Average Distance, Average Crowfly time, Average "
          "Time\n";

  file << "Astar," + std::to_string(singleton_->astar_details.at(0)) + "," +
              std::to_string(singleton_->astar_details.at(1)) + "," +
              std::to_string(singleton_->astar_details.at(2)) + "\n";
  file << "BFS," + std::to_string(singleton_->bfs_details.at(0)) + "," +
              std::to_string(singleton_->bfs_details.at(1)) + "," +
              std::to_string(singleton_->bfs_details.at(2)) + "\n";
  file << "DFS," + std::to_string(singleton_->dfs_details.at(0)) + "," +
              std::to_string(singleton_->dfs_details.at(1)) + "," +
              std::to_string(singleton_->dfs_details.at(2)) + "\n";
  file << "Dijkstra," + std::to_string(singleton_->dijkstra_details.at(0)) + "," +
              std::to_string(singleton_->dijkstra_details.at(1)) + "," +
              std::to_string(singleton_->dijkstra_details.at(2)) + "\n";
  file << "Beeline," + std::to_string(singleton_->beeline_details.at(0)) + "," +
              std::to_string(singleton_->beeline_details.at(1)) + "," +
              std::to_string(singleton_->beeline_details.at(2)) + "\n";
  file.close();

}
