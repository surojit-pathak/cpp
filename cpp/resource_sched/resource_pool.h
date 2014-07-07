
using namespace std;
#define NODE_NOT_ASSIGNED -1


class Job {
     int    jid;
     int    node;
     int    res;
     int    time;
     int    time_spent;
     int    time_req;

     public:
     Job (int r, int t) { res = r; time = t; node = NODE_NOT_ASSIGNED;
time_spent = 0; time_req = t; }
     int getRes() { return res; }

     friend class Jobpool;
     friend class resourcePool;
};

class resource {
    int res;
    int id;
    int totalRes;
    float loadAvg;
   
    public:
    resource (int i, int r) { id = i; res = r; totalRes = r; loadAvg = 0;}
    friend class resourcePool;
};

class resourcePool {
     map<int, resource> nodes; // Node indexed by node-id, and keeping resources

     public:
     void resourceAdd (int node, int res) 
     {
            map<int, resource>::iterator present = nodes.find(node);
            if (present == nodes.end()) {
                resource *r = new resource(node, res);  
                nodes.insert(pair<int, resource>(node, *r));
            } else {
                present->second.res += res;
            }
     }

     int schedule (Job *job) 
     {
        int res = job->res;
        int node = NODE_NOT_ASSIGNED;
        typename std::map<int, resource>::iterator it;

        for (it = nodes.begin(); it != nodes.end(); it++) {
             if (res <= it->second.res) {
                 // First Fit 
                 node = it->first;
                 break;
             }
        }

        if (node == NODE_NOT_ASSIGNED) {
            job->time_spent++;
            return node;
        }
        
        it->second.res -= res;
        return node;
     }

     void display (void) 
     {
        cout << "Rpool -->";
        for (typename std::map<int, resource>::iterator it = nodes.begin();
             it != nodes.end(); it++) {
            int usage = it->second.totalRes - it->second.res;
            float load = (float)usage / it->second.totalRes;
            if (it->second.loadAvg != 0) {
                it->second.loadAvg = (it->second.loadAvg + load) / 2;
                if (it->second.loadAvg < 0.001) {
                    it->second.loadAvg = 0;
                }
            } else {
                it->second.loadAvg = load;
            }
            cout << "(" << it->first << " ," << it->second.res << " ," << it->second.loadAvg << "), ";
        }
        cout << endl;
     }
};
class Jobpool {
     map<int, Job> jobQ;
     int    jid_max;
     int    timeout;
     int    total_time_req;
     int    total_time_taken;
     float  avg_utilization;

     public:
     Jobpool (void) { 
         jid_max = 1; timeout = 0; 
         total_time_req = 0;
         total_time_taken = 0;
         avg_utilization = 0;
     }
     int addJob (Job *jp, int node) {
         Job j = *jp;
         j.jid = jid_max;
         j.node =  node;
         jobQ.insert(pair<int, Job>(jid_max, j));
         jid_max++;
     }

     void timeOut (resourcePool *rpool) {
        sleep(1);
        timeout++;
        cout << "After timeout " << timeout << endl;
        for (typename std::map<int, Job>::iterator it = jobQ.begin();
             it != jobQ.end(); ) {
             it->second.time--;
             it->second.time_spent++;
             if (it->second.time == 0) {
                 total_time_req += it->second.time_req;
                 total_time_taken += it->second.time_spent;
                 if (avg_utilization != 0) {
                     avg_utilization = (avg_utilization + (float)(it->second.time_spent / it->second.time_req)) / 2;
                 } else { 
                     avg_utilization = (float)(it->second.time_spent / it->second.time_req);
                 }

                 int node = it->second.node;
                 int res = it->second.res;
                 int jid = it->first; it++;
                 jobQ.erase(jid);
                 rpool->resourceAdd(node, res);
             } else {
                 it++;
             }
        }
        rpool->display();
        this->display();
     }
         
     void display (void) 
     {
        cout << "JobQ -->";
        for (typename std::map<int, Job>::iterator it = jobQ.begin();
             it != jobQ.end(); it++) {
            cout << "(" << it->first << " ," << it->second.res << ", " << it->second.time << ", " << it->second.node << "), ";
        }
        cout << endl;
        cout << "Utilization --> " << avg_utilization << ", Request: " <<
            total_time_req << " , Used: " << total_time_taken << endl;
     }
    
};

