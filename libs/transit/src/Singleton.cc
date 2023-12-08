#include "Singleton.h"

Singleton::Singleton(){

}

Singleton::~Singleton(){

}

Singleton::Singleton(const Singleton& other) = delete;

Singleton& Singleton::operator=(const Singleton& other) = delete;

Singleton* Singleton::get_instance(){
    return singleton_;
}

float Singleton::get_speed(Drone drone){
    return drone.getSpeed();
}

void Singleton::get_drone_startpoint(Drone drone){
    drone_startpoints.push_back(drone->getPosition());
}

void Singleton::get_package_startpoint(Package package){
    package_startpoints.push_back(package->getPosition());
}

void Singleton::get_endpoint(Package package){
    endpoints.push_back(package->getDestination());
}

void Singleton::get_distances(Package package){ //ask TA's on friday
    std::string strat = package->getStrategyName();
    package_strats.push_back(strat); // quick add the strat to the appropriate array

    Vector3 startpoint = package->getPosition();
    Vector3 endpoint = package->getDestination();
    Vector3 distance = startpoint->dist(endpoint);
    package_distances.push_back(distance); // quick add the distance to the appropriate array

    if strat == "astar"{
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
    for(int i = 0; i < beelinedistances.size(); i++){
        time = beeline_distances[i] / drone_speed;
        beeline_times.push_back(time);
    }    
}

void get_package_times(){
    float time = 0.0;
    for(int i = 0; i < package_distances.size(); i++){
        time = package_distances[i] / drone_speed;
        package_times.push_back(time);
    }
}

void Singleton::get_downtime(Drone drone, Package package){
    Vector3 drone_pos = drone.getPosition();
    Vector3 package_pos = package.getPosition();
    double distance = drone_pos->dist(package_pos);

    downtimes.push_back(distance/drone_speed);
}

void Singleton::analyze_data(){

}

void Singleton::export_to_csv(){

}
