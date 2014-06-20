#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <list>
#include "dictionary.h"

dictionary dict;

template <class V, class C> class mygraph {
    public:
    std::set<V> vertices;
    std::set<std::pair<V, V> > edges;
    std::map<V, std::map<V, C> > adjacencies;

    void add_vertex (V v)
    {
        this->vertices.insert(v);
    }
    void add_edge (V u, V v, C c)
    {
        this->edges.insert(std::pair<V, V>(u, v));
        this->adjacencies[u].insert(std::pair<V,C>(v, c));
        this->adjacencies[v].insert(std::pair<V,C>(u, c));
    }

    void bfs (V u) {
      std::queue<V> visitq;
      std::set<V>   visited;

      visitq.push(u);
      while (!visitq.empty()) {
          V node = visitq.front();
          visitq.pop();

          // Nodes might have been added multiple times, if not visited.
          if (visited.find(node) == visited.end()) {
              typename std::map<V,C>::iterator adj;
              for (adj = this->adjacencies[node].begin(); adj != this->adjacencies[node].end(); adj++) {
                  if (visited.find(adj->first) == visited.end()) {
                      visitq.push(adj->first);
                  }
              }
              visited.insert(node);
              std::cout << node;
          }
      }
      std::cout << std::endl;
    }

    void dfs (V u) {
      std::stack<V> visitq;
      std::set<V>   visited;

      visitq.push(u);
      while (!visitq.empty()) {
          V node = visitq.top();
          visitq.pop();

          if (visited.find(node) == visited.end()) {
              typename std::map<V,C>::iterator adj;
              for (adj = this->adjacencies[node].begin(); adj != this->adjacencies[node].end(); adj++) {
                  if (visited.find(adj->first) == visited.end()) {
                      visitq.push(adj->first);
                  }
              }
              visited.insert(node);
              std::cout << node;
          }
      }
      std::cout << std::endl;
    }

    void display (void)
    {
        std::cout << "Vertices (" << vertices.size() << ") are - { ";
        for (typename std::set<V>::iterator it = this->vertices.begin();
             it != this->vertices.end(); it++) {
            std::cout << *it << ", ";
        }
        std::cout << " } " << std::endl;

        std::cout << "Edges (" << edges.size() << ") are - { ";
        for (typename std::set<std::pair<V, V> >::iterator it = this->edges.begin();
             it != this->edges.end(); it++) {
            std::cout << "(" << it->first << "," << it->second << "), ";
        }
        std::cout << " } " << std::endl;
    }

    void print_path (std::set<V> hist)
    {
        for (typename std::set<V>::iterator it = hist.begin();
             it != hist.end(); it++) {
            std::cout << *it;
        }
        std::cout << std::endl;
    }

    /* Regular
    void print_path (char *str, int strlen)
    {
        if (strlen != vertices.size()) return;
        str[strlen] = '\0';
        std::cout << str << std::endl;
    }
    */

    /* Boggle */
    void print_path (char *str, int strlen)
    {
        if (strlen < 3) return;
        str[strlen] = '\0';
        if (dict.isValidWord(str)) std::cout << str << std::endl;
    }

    void show_all_paths_internal (V u, char *str, int strlen, std::set<V> hist = std::set<V>())
    {
        if (hist.find(u) == hist.end()) {
            hist.insert(u);
            str[strlen++] = u;
        }

        this->print_path(str, strlen);

        for (typename std::map<V,C>::iterator it = this->adjacencies[u].begin();
             it != this->adjacencies[u].end(); it++) {
             if (hist.find(it->first) == hist.end()) {
                hist.insert(it->first);
                 str[strlen++] = it->first;
                 this->show_all_paths_internal(it->first, str, strlen, hist);
                 hist.erase(it->first);
                 strlen--;
             }
        }
    }

    V get_first_vertex (mygraph<V,C> mg)
    {
        return *mg->vertices.begin();
    }

    void show_all_paths (V u)
    {
        char *str = new char [vertices.size()];
        show_all_paths_internal(u, str, 0);
        delete str;
    }

    mygraph *build_spanning_tree (void)
    {
        mygraph *spt = new mygraph<V, C>();
        for (typename std::set<V>::iterator it = this->vertices.begin();
             it != this->vertices.end(); it++) {
            if (spt->vertices.find(*it) == spt->vertices.end()) {
                for (typename std::map<V, C>::iterator adj = this->adjacencies[*it].begin();
                     adj != this->adjacencies[*it].end(); adj++) {
                     if (spt->vertices.find(adj->first) == spt->vertices.end()
                         || spt->vertices.find(*it) == spt->vertices.end()) {
                         spt->add_vertex(adj->first);
                         spt->add_edge(*it, adj->first, adj->second);
                     }
                }
                spt->add_vertex(*it);
            }
        }

        return spt;
    }
   bool is_connected_graph ()
    {
        bool ans = false;
        mygraph *spt = this->build_spanning_tree();
        if (spt->vertices.size() - 1 == spt->edges.size()) {
            ans = true;
        }

        delete spt;
        return ans;
    }
};


