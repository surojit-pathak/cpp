#include <iostream>
#include "cmn/mygraph.h"

int main (void)
{
    mygraph<char, int> mg1;

    mg1.add_vertex('A');
    mg1.add_vertex('B');
    mg1.add_vertex('C');
    mg1.add_vertex('D');
    mg1.add_vertex('E');

    mg1.add_edge('B', 'A', 5);
    mg1.add_edge('B', 'C', 5);
    mg1.add_edge('C', 'A', 6);
    mg1.add_edge('D', 'A', 3);
    mg1.add_edge('C', 'D', 4);
    mg1.add_edge('E', 'D', 7);

    mg1.display();

    mg1.show_all_paths('A');

    mygraph<char, int> *mg2 = mg1.build_spanning_tree();
    mg2->display();
    mg2->show_all_paths('A');

    return 0;
}


