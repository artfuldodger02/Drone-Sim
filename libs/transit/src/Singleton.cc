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


double Singleton::get_speed(IEntity* drone){
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
  singleton_->endpoint_counter += 1;
}

void Singleton::get_distances(Package package){ //ask TA's on friday
  std::string strat = package.getStrategyName();
  singleton_->package_strats.push_back(
      strat);  // quick add the strat to the appropriate array

  Vector3 startpoint = package.getPosition();
  Vector3 endpoint = package.getDestination();
  double distance = startpoint.dist(endpoint);
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
  std::cout << "test 1a\n";
  double time = 0.0;
  // get astar times
  if(singleton_->astar_distances.size() > 0){
    for (int i = 0; i < singleton_->astar_distances.size(); i++) {
      time = singleton_->astar_distances[i] / singleton_->drone_speed;
      singleton_->astar_times.push_back(time);
      }
  }
  // get dfs times
  if(singleton_->dfs_distances.size() > 0){
    for(int i = 0; i < singleton_->dfs_distances.size(); i++){
        std::cout << "test 1c\n";
        time = singleton_->dfs_distances[i] / singleton_->drone_speed;
        singleton_->dfs_times.push_back(time);
    }
  }
  // get bfs times
  if(singleton_->bfs_distances.size() > 0){
    for(int i = 0; i < bfs_distances.size(); i++){
        std::cout << "test 1d\n";
        time = singleton_->bfs_distances[i] / singleton_->drone_speed;
        singleton_->bfs_times.push_back(time);
    }
  }
  // get dijkstra times
  if(singleton_->dijkstra_distances.size() > 0){
    for(int i = 0; i < singleton_->dijkstra_distances.size(); i++){
        std::cout << "test 1e\n";
        time = singleton_->dijkstra_distances[i] / singleton_->drone_speed;
        singleton_->dijkstra_times.push_back(time);
    }
  }
  // get beeline times
  if(singleton_->beeline_distances.size() > 0){
    for(int i = 0; i < singleton_->beeline_distances.size(); i++){
        std::cout << "test 1f\n";
        time = singleton_->beeline_distances[i] / singleton_->drone_speed;
        singleton_->beeline_times.push_back(time);
    }    
  }
}

void Singleton::get_package_times(){
  double time = 0.0;
  for (int i = 0; i < singleton_->package_distances.size(); i++) {
    time = singleton_->package_distances[i] / drone_speed;
    singleton_->package_times.push_back(time);
    }
}

void Singleton::get_downtime(Package package){

  if (singleton_->endpoint_counter >= 1) {

    Vector3 drone_pos = singleton_->endpoints[singleton_->endpoint_counter - 1];

    Vector3 package_pos = package.getPosition();

    double distance = drone_pos.dist(package_pos);

    double dtime = distance / singleton_->drone_speed;

    singleton_->downtimes.push_back(dtime);
    
    }
}

void Singleton::analyze_data(){
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

  std::cout << "test astar\n";
  // check to see if we have any astar times
  if(singleton_->astar_times.size() > 0){
    for (int i = 0; i < singleton_->astar_times.size(); i++) {
      singleton_->avg_astar_time += singleton_->astar_times[i];
      singleton_->avg_astar_distance += singleton_->astar_distances[i];
    }
    // if we do, calculate averages
    singleton_->avg_astar_time = singleton_->avg_astar_time / singleton_->astar_times.size();
    singleton_->avg_astar_distance = singleton_->avg_astar_distance / singleton_->astar_distances.size();
  }
  // assign details
  // if there is no entries in astar, it'll default to 0
  singleton_->astar_details.push_back(singleton_->drone_speed);
  singleton_->astar_details.push_back(singleton_->avg_astar_distance);
  singleton_->astar_details.push_back(singleton_->avg_astar_time);

  // repeat above for each strat
  // beeline
  std::cout << "test beeline\n";
  if(singleton_->beeline_times.size() > 0){
    for(int i = 0; i < singleton_->beeline_times.size(); i++){
        singleton_->avg_astar_time += singleton_->beeline_times[i];
        singleton_->avg_beeline_distance += singleton_->beeline_distances[i];
    }
    singleton_->avg_beeline_time = singleton_->avg_beeline_time / singleton_->beeline_times.size();
    singleton_->avg_beeline_distance = singleton_->avg_beeline_distance / singleton_->beeline_distances.size();
  }
  singleton_->beeline_details.push_back(singleton_->drone_speed);
  singleton_->beeline_details.push_back(singleton_->avg_beeline_distance);
  singleton_->beeline_details.push_back(singleton_->avg_beeline_time);
  
  // bfs
  std::cout << "test bfs\n";
  if(singleton_->bfs_times.size() > 0){
    for(int i = 0; i < singleton_->bfs_times.size(); i++){
        singleton_->avg_bfs_time += singleton_->bfs_times[i];
        singleton_->avg_bfs_distance += singleton_->bfs_distances[i];
    }
    singleton_->avg_bfs_time = singleton_->avg_bfs_time / singleton_->bfs_times.size();
    singleton_->avg_bfs_distance = singleton_->avg_bfs_distance / singleton_->bfs_distances.size();
  }
  singleton_->bfs_details.push_back(singleton_->drone_speed);
  singleton_->bfs_details.push_back(singleton_->avg_bfs_distance);
  singleton_->bfs_details.push_back(singleton_->avg_bfs_time);
  
  // dfs
  std::cout << "test dfs\n";
  if(singleton_->dfs_times.size() > 0){
    for(int i = 0; i < singleton_->dfs_times.size(); i++){
        singleton_->avg_dfs_time += singleton_->dfs_times[i];
        singleton_->avg_dfs_distance += singleton_->dfs_distances[i];
    }
    singleton_->avg_dfs_time = singleton_->avg_dfs_time / singleton_->dfs_times.size();
    singleton_->avg_dfs_distance = singleton_->avg_dfs_distance / singleton_->dfs_distances.size();
  }
  singleton_->dfs_details.push_back(singleton_->drone_speed);
  singleton_->dfs_details.push_back(singleton_->avg_dfs_distance);
  singleton_->dfs_details.push_back(singleton_->avg_dfs_time);
  
  //dijkstra
  std::cout << "test dijkstra\n";
  if(singleton_->dijkstra_times.size() > 0){
    for(int i = 0; i < singleton_->dijkstra_times.size(); i++){
        singleton_->avg_dijkstra_time += singleton_->dijkstra_times[i];
        singleton_->avg_dijkstra_time += singleton_->dijkstra_distances[i];
    }
    singleton_->avg_dijkstra_time = singleton_->avg_dijkstra_time / singleton_->dijkstra_times.size();
    singleton_->avg_dijkstra_distance = singleton_->avg_dijkstra_distance / singleton_->dijkstra_distances.size();
  }
  singleton_->dijkstra_details.push_back(singleton_->drone_speed);
  singleton_->dijkstra_details.push_back(singleton_->avg_dijkstra_distance);
  singleton_->dijkstra_details.push_back(singleton_->avg_dijkstra_time);
  
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
