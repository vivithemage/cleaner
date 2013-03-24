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
#include <magic.h>

// Non standard libs
#include "fann.h"
#include "update_check.h"
#include "neural_network.h"
#include "get_metadata.h"
//#include "ConfigFile.h"
#include "get_config.h"
#include "utils.h"

using namespace std;
static magic_t magic_cookie;

/* Initialising magic database for use */
int magic_database_init(void) 
{
	magic_cookie = magic_open(MAGIC_MIME);
	if (magic_cookie == NULL) {
	        printf("Unable to initialize magic library\n");
	        return 1;
	}
	printf("Loading default magic database\n");
	if (magic_load(magic_cookie, NULL) != 0) {
		printf("Cannot load magic database - %s\n", magic_error(magic_cookie));
	        magic_close(magic_cookie);
		return 1;
	}
	return 0;
}

/*look at the mime, if the directory does not already exist, make it*/
char *make_dir(const char *mime_to_sort, char *move_to_dir)
{
	char *full_mvpath;
	char *images;
	char *directory;
	char *unknown;	

	strcpy(full_mvpath, move_to_dir);
	if (strstr(mime_to_sort, images) != NULL) {
		strcat(full_mvpath,(const char *) images);
		mkdir(full_mvpath, S_IRWXU); //creating directory
		printf("created %s directory\n", full_mvpath); // Add message which stats the directory, and says if it exists. 
		return images;
	}
	
        if (strstr(mime_to_sort, directory) != NULL) {
		return directory;
	}
	return unknown;
}

/*takes filename and the stripped mime type and moves to apropriate directory*/
int moving_file(char *dir_plus_act, char *movedir_mime, char *dir_to_make) 	
{	
	if (strcmp(dir_to_make, "directory") == 0) {
		printf("File is a directory, skipping\n");
		return 0;
	}
	if (rename(dir_plus_act, movedir_mime) == 0) {
		printf("success: file %s moved to %s\n", dir_plus_act, movedir_mime); 
		return 0;
	}
	else {
		printf("Did not move file %s to %s for unknown reasons (Probably because the file type has not been added.\n"\
			, dir_plus_act, movedir_mime);	
		printf("You could request this file to be added or edit the source youself ;), please email any modifications to vivi at mage.me.uk\n"); 
		return 0;
	}
}

/* run after organize is clicked */	
int organize(void)	
{	
        char *sort_directory; // Directory which contains all the files to be sorted. 
	char *move_to_dir;    // Directory to create new folders in and move files to. 
	
        char *dir_to_make;    // The mime of the file.
	char *dir_plus_act;   // Sort directory and file mime concatenated.
	
        char *movedir_mime;   // move to directory with mime direcory concatenated.
		
	const char *magic_full;

	strcpy(sort_directory, "/home/rezdev/gitting/cleaner/tests/data/sort/");	// This needs to take input from user.
	strcpy(move_to_dir, "/home/rezdev/gitting/cleaner/tests/data/sorted/");	// This also needs to take user input.	

	/*beginning directory run*/
	DIR *directory;
	struct dirent *listing;
	directory = opendir(sort_directory);
	if (directory != NULL) {
		while((listing = readdir(directory))) {
			sprintf(dir_plus_act, "%s%s", sort_directory, listing->d_name);
			magic_full = magic_file(magic_cookie, (const char *) dir_plus_act); 
			printf("1. %s = %s\n", magic_full, dir_plus_act);
			strcpy(dir_to_make, make_dir(magic_full, move_to_dir));	/*create directory*/
			sprintf(movedir_mime, "%s%s/%s", move_to_dir, dir_to_make, listing->d_name);
			printf("movedir_mime = %s\n", movedir_mime);			
			moving_file(dir_plus_act, movedir_mime, dir_to_make);	/*move files.*/
		}
	} else {
    printf("Failed to open directory %s", sort_directory);
  }

	printf("Organize end.\n");
	return 0;
}

int main(int argc, char *argv[])
{	
    // magic database needs to be initialized before use
    magic_database_init();	
    printf("first argument: %s\n", argv[1]);
    //char *filename = "bleh";
    get_metadata();
    
    ConfigFile cf("config.txt");
    
    std::string foo;
    std::string water;
    double four;
    
    foo = cf.Value("section_1","foo");
    water = cf.Value("section_2","water");
    //four = cf.Value("section_2","four");
    
    std::cout << foo   << std::endl;
    std::cout << water << std::endl;
    //std::cout << four  << std::endl;
    
    // Main organization function
    // organize();
    
    return 0;
}
