#include <iostream>
#include <fstream>
#include <map>
#include <iterator>     // std::istream_iterator
#include "resource_pool.h"


int main (void)
{
    ifstream f("node.txt");
    ifstream j("jobs.txt");
    string str;

    resourcePool    respool;
    Jobpool         jpool;

    while (getline(f, str)) {
            int node, res;
            sscanf(str.c_str(), "(%d %d)\n", &node, &res); 
            respool.resourceAdd(node, res);
    }
    respool.display();


    Job *job = NULL;
    while (1) {
        if (job == NULL && getline(j, str)) {
            int res, time;
            sscanf(str.c_str(), "(%d %d)\n", &res, &time); 
            job = new Job(res, time);
        }

        if (job == NULL) {
            jpool.timeOut(&respool);
        }

        while (job) {
            int node = respool.schedule(job);
            if (node == NODE_NOT_ASSIGNED) {
                jpool.timeOut(&respool);
            } else {
                jpool.addJob(job, node); 
                job = NULL;
                break;
            }
        }
    }
}


