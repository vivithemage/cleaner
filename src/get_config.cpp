/* Retrieve metadata */
#include <iostream>
#include <stdio.h>

using namespace std;

class config
{
   private:
      string sort_directory;
      string check_for_updates;
      int variable;
 
   public:
      void input_value()
      {
         cout << "In function input_value, Enter an integer\n";
         cin >> variable;
      }
 
      void output_value()
      {
         cout << "Variable entered is ";
         cout << variable << "\n";
      }
};

int get_config()  {
  printf("Hai, in get_config\n");
  return 0;
}
