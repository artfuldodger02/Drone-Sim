#include "Singleton.h"

Singleton::Singleton(){

}

Singleton::~Singleton(){

}

Singleton::Singleton(const Singleton& other) = delete;

Singleton& Singleton::operator=(const Singleton& other) = delete;

Singleton* Singleton::get_instance(){

}

float Singleton::get_speed(Drone drone){
    
}

void Singleton::get_drone_startpoint(Drone drone){

}

void Singleton::get_package_startpoint(Package package){

}

void Singleton::get_endpoint(Drone drone){

}

void Singleton::get_distances(IStrategy* strat){

}

void Singleton::get_strat_time(IStrategy* strat){

}

void Singleton::get_downtime(){

}

void Singleton::analyze_data(){

}

void Singleton::export_to_csv(){

}
