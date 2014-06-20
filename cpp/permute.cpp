#include <iostream>
#include "cmn/mygraph.h"

int main ()
{
    mygraph<char, int> mg1;

    mg1.add_vertex('A');
    mg1.add_vertex('B');
    mg1.add_vertex('C');

    mg1.add_edge('B', 'A', 1);
    mg1.add_edge('C', 'A', 1);
    mg1.add_edge('C', 'B', 1);

    mg1.display();

    mg1.show_all_paths('A');
    mg1.show_all_paths('B');
    mg1.show_all_paths('C');

    return 0;
}

