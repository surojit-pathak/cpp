#include <ctype.h>
#include "cmn/mygraph.h"

char boggle[4][4] = {
     { 'A', 'B', 'C', 'D' },
     { 'E', 'F', 'G', 'H' },
     { 'I', 'J', 'K', 'L' },
     { 'M', 'N', 'O', 'P' }
     };

int main (void)
{

   mygraph<char, int> graph;

   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
         boggle[i][j] = tolower(boggle[i][j]);
         graph.add_vertex(boggle[i][j]);
      }
   }

   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
         if (i + 1 < 4) {
             graph.add_edge(boggle[i][j], boggle[i + 1][j], 0);
             if (j - 1 >= 0) graph.add_edge(boggle[i][j], boggle[i + 1][j - 1], 0);
             if (j + 1 < 4) graph.add_edge(boggle[i][j], boggle[i + 1][j + 1], 0);
         }
         if (j + 1 < 4) graph.add_edge(boggle[i][j], boggle[i][j + 1], 0);
      }
   }

   //graph.display();

   //graph.show_all_paths('a');

   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
         graph.show_all_paths(boggle[i][j]);
      }
   }
}

