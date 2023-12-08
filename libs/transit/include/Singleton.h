#ifndef SINGLETON_H
#define SINGLETON_H

#include <vector>

#include "Drone.h"
#include "Package.h"
#include "math/vector3.h"

/**
 * @class Singleton
 * @brief collects info regarding scheduled package deliveries,
 * analyzes it, and exports it to a csv file
 */

class Singleton{
    public:
        /**
         * @brief reassigns the = operator to reset singletons
         * @param other Singleton object being assigned
         * @return return the new assigned singleton
         */
        Singleton& operator=(const Singleton& other);
        /**
         * @brief copy constructor for the singleton
         * @param other singleton being copied
         */
        Singleton(const Singleton& other);
        /**
         * @brief get an instance of this singleton
         * @return singleton pointer
         */
        static Singleton* get_instance(); 
        /**
         * @brief gets the speed of the drone
         * @param drone the drone we are getting the speed of
         * @return float representing the speed
         */
        float get_speed(Drone drone);

        /**
         * @brief gets the startpoint of the drone and logs it in drone_startpoints
         * @param drone the drone we are getting the startpoint of
         */
        void get_drone_startpoint(Drone drone);
        /**
         * @brief gets the startpoint of the package and logs it in package_startpoints
         * @param package the package we are getting the startpoint of
         */
        void get_package_startpoint(Package package);
        /**
         * @brief gets the endpoint of the package/drone and logs it in package_startpoints
         * @param drone the package we are getting the endpoint of
         */
        void get_endpoint(Package package);
        /**
         * @brief gets the distance traveled by a strategy and logs it in
         * the appropriate strategy_distance variables
         * @param package the package we get the strat name from
         */
        void get_distances(Package package);
        /**
         * @brief gets the time it takes for a strategy to complete and logs it in
         * the appropriate strategy_time variable
         */
        void get_strat_times();
        /**
         * @brief gets the time between when a drone gets a new scheduled
         * package and when it picks up said package, and stores it in
         * downtimes array
         * @param drone the drone we are getting the downtime of
         * @param package the package we need to get the position of
         */
        void get_downtime(Drone drone, Package package); 
         /**
         * @brief gets the time it takes for the packages to 
         * make it to their destinations, and logs it in array
         */
        void get_package_times();
        /**
         * @brief takes the data we've aquired and computes average speed,
         * average distance, comparing to crowfly time, and the average time
         */
        void analyze_data();
        /**
         * @brief export the collected data to a CSV file upon completion
         * of the program
         */
        void export_to_csv();

    private:
        /**
         * @brief singleton constructor
         */
        Singleton();
        /**
         * @brief singleton deconstructor
         */
        ~Singleton();

        static Singleton* singleton_;
        float drone_speed;

        std::vector<Vector3> drone_startpoints;
        std::vector<Vector3> package_startpoints;
        std::vector<Vector3> endpoints;

        std::vector<float> astar_times;
        std::vector<double> astar_distances;

        std::vector<float> beeline_times;
        std::vector<double> beeline_distances;

        std::vector<float> bfs_times;
        std::vector<double> bfs_distances;

        std::vector<float> dfs_times;
        std::vector<double> dfs_distances;

        std::vector<float> dijkstra_times;
        std::vector<double> dijkstra_distances;

        std::vector<float> downtimes;
        std::vector<float> package_times;
        std::vector<std::string> package_strats;
        std::vector<double> package_distances;

    
};
#endif
