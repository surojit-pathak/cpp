
using namespace std;
#define NODE_NOT_ASSIGNED -1


class Job {
     int    jid;
     int    node;
     int    res;
     int    time;

     public:
     Job (int r, int t) { res = r; time = t; node = NODE_NOT_ASSIGNED; }
     int getRes() { return res; }

     friend class Jobpool;
};

class resourcePool {
     map<int, int> nodes; // Node indexed by node-id, and keeping resources

     public:
     void resourceAdd (int node, int res) 
     {
            map<int, int>::iterator present = nodes.find(node);
            if (present == nodes.end()) {
                nodes.insert(pair<int, int>(node, res));
            } else {
                int nres = present->second + res;
                int nnode = node;
                nodes.erase(node);
                this->resourceAdd(nnode, nres);
                //nodes.insert(pair<int, int>(nnode, nres));
            }
     }

     int schedule (int res) 
     {
         int node = NODE_NOT_ASSIGNED;
        typename std::map<int, int>::iterator it;
         
        for (it = nodes.begin(); it != nodes.end(); it++) {
             if (res <= it->second) {
                 // First Fit 
                 node = it->first;
                 break;
             }
        }

        if (node == NODE_NOT_ASSIGNED) return node;
        
        nodes.erase(node);        
        nodes.insert(pair<int, int>(it->first, it->second - res));
        
        return node;
     }

     void display (void) 
     {
        cout << "Rpool -->";
        for (typename std::map<int, int>::iterator it = nodes.begin();
             it != nodes.end(); it++) {
            cout << "(" << it->first << " ," << it->second << "), ";
        }
        cout << endl;
     }
};
class Jobpool {
     map<int, Job> jobQ;
     int    jid_max;
     int    timeout;

     public:
     Jobpool (void) { jid_max = 1; timeout = 0;}
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
             if (it->second.time == 0) {
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
     }
    
};

