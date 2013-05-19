/*
 *  Copyright (C) 2013 by Reza Snowdon <rs@mage.me.uk>
 *
 *  magicleaner is a file sorter that can learn how to sort files.
 *
 *  This file is part of magicleaner.
 *
 *  Magicleaner is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Magicleaner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with magicleaner.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#define VERSION "0.3"

// standard libs
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Non standard libs
#include "fann.h"
#include "update_check.h"
#include "neural_network.h"
#include "get_metadata.h"
#include "get_config.h"
#include "utils.h"

using namespace std;
//static magic_t magic_cookie;

int main(int argc, char *argv[])
{	
    // magic database needs to be initialized before use
    magic_database_init();	
    printf("first argument: %s\n", argv[1]);
    get_metadata();

    const char *config_file_name;
    // check you a config has been passed in, if not default to
    // magic-cleaner.conf
    if (argv[1] == NULL)        {
        config_file_name = "magic-cleaner.conf";
    } else {
        config_file_name = argv[1];
    }

    // check config file exists and is readable
    if (FILE * file = fopen(config_file_name, "r")) 
    {
        fclose(file);
    } else {
        cout << "config file could not be opened, exiting.." << endl;
        exit(1);
    }
  
    ConfigFile cf(config_file_name);
    
    std::string directorytosort;
    directorytosort = cf.Value("main","directory_to_sort");
    
    std::cout << directorytosort << std::endl;
    
    // Main organization function
    //organize();
    
    return 0;
}
