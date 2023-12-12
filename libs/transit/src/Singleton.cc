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
    drone_speed = drone->getSpeed();
    return drone->getSpeed();
}

void Singleton::get_drone_startpoint(IEntity* drone){
    drone_startpoints.push_back(drone->getPosition());
}

void Singleton::get_package_startpoint(Package package){
    package_startpoints.push_back(package.getPosition());
}

void Singleton::get_endpoint(Package package){
    endpoints.push_back(package.getDestination());
}

void Singleton::get_distances(Package package){ //ask TA's on friday
    std::string strat = package.getStrategyName();
    package_strats.push_back(strat); // quick add the strat to the appropriate array

    Vector3 startpoint = package.getPosition();
    Vector3 endpoint = package.getDestination();
    float distance = startpoint.dist(endpoint);
    package_distances.push_back(distance); // quick add the distance to the appropriate array

    if (strat == "astar"){
        astar_distances.push_back(distance);
    } else if (strat == "dfs") {
        dfs_distances.push_back(distance);
    } else if (strat == "bfs") {
        bfs_distances.push_back(distance);
    } else if (strat == "dijkstra") {
        dijkstra_distances.push_back(distance);
    } else { //beeline
        beeline_distances.push_back(distance);
    }   
}

void Singleton::get_strat_times(){
    float time = 0.0;
    // get astar times
    for(int i = 0; i < astar_distances.size(); i++){
        time = astar_distances[i] / drone_speed;
        astar_times.push_back(time);
    }
    // get dfs times
    for(int i = 0; i < dfs_distances.size(); i++){
        time = dfs_distances[i] / drone_speed;
        dfs_times.push_back(time);
    }
    // get bfs times
    for(int i = 0; i < bfs_distances.size(); i++){
        time = bfs_distances[i] / drone_speed;
        bfs_times.push_back(time);
    }
    // get dijkstra times
    for(int i = 0; i < dijkstra_distances.size(); i++){
        time = dijkstra_distances[i] / drone_speed;
        dijkstra_times.push_back(time);
    }
    // get beeline times
    for(int i = 0; i < beeline_distances.size(); i++){
        time = beeline_distances[i] / drone_speed;
        beeline_times.push_back(time);
    }    
}

void Singleton::get_package_times(){
    float time = 0.0;
    for(int i = 0; i < package_distances.size(); i++){
        time = package_distances[i] / drone_speed;
        package_times.push_back(time);
    }
}

void Singleton::get_downtime(IEntity* drone, Package package){
    Vector3 drone_pos = drone->getPosition();
    Vector3 package_pos = package.getPosition();
    double distance = drone_pos.dist(package_pos);

    downtimes.push_back(distance/drone_speed);
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
    
    for(int i = 0; i < astar_times.size(); i++){
        avg_astar_time += astar_times[i];
        avg_astar_distance += astar_distances[i];
    }
    avg_astar_time = avg_astar_time / astar_times.size();
    avg_astar_distance = avg_astar_distance / astar_distances.size();

    astar_details.push_back(drone_speed);
    astar_details.push_back(avg_astar_distance);
    astar_details.push_back(avg_astar_time);

    

    for(int i = 0; i < beeline_times.size(); i++){
        avg_astar_time += beeline_times[i];
        avg_beeline_distance += beeline_distances[i];
    }
    avg_beeline_time = avg_beeline_time / beeline_times.size();
    avg_beeline_distance = avg_beeline_distance / beeline_distances.size();

    beeline_details.push_back(drone_speed);
    beeline_details.push_back(avg_beeline_distance);
    beeline_details.push_back(avg_beeline_time);
    

    for(int i = 0; i < bfs_times.size(); i++){
        avg_bfs_time += bfs_times[i];
        avg_bfs_distance += bfs_distances[i];
    }
    avg_bfs_time = avg_bfs_time / bfs_times.size();
    avg_bfs_distance = avg_bfs_distance / bfs_distances.size();

    bfs_details.push_back(drone_speed);
    bfs_details.push_back(avg_bfs_distance);
    bfs_details.push_back(avg_bfs_time);
    

    for(int i = 0; i < dfs_times.size(); i++){
        avg_dfs_time += dfs_times[i];
        avg_dfs_distance += dfs_distances[i];
    }
    avg_dfs_time = avg_dfs_time / dfs_times.size();
    avg_dfs_distance = avg_dfs_distance / dfs_distances.size();

    dfs_details.push_back(drone_speed);
    dfs_details.push_back(avg_dfs_distance);
    dfs_details.push_back(avg_dfs_time);
    

    for(int i = 0; i < dijkstra_times.size(); i++){
        avg_dijkstra_time += dijkstra_times[i];
        avg_dijkstra_time += dijkstra_distances[i];
    }
    avg_dijkstra_time = avg_dijkstra_time / dijkstra_times.size();
    avg_dijkstra_distance = avg_dijkstra_distance / dijkstra_distances.size();

    dijkstra_details.push_back(drone_speed);
    dijkstra_details.push_back(avg_dijkstra_distance);
    dijkstra_details.push_back(avg_dijkstra_time);
    
}

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
                package_strats.at(i) + "," +
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
  file << "Dijkstra," + std::to_string(dijkstra_details.at(0)) + "," +
              std::to_string(dijkstra_details.at(1)) + "," +
              std::to_string(dijkstra_details.at(2)) + "\n";
  file << "Beeline," + std::to_string(beeline_details.at(0)) + "," +
              std::to_string(beeline_details.at(1)) + "," +
              std::to_string(beeline_details.at(2)) + "\n";
}
