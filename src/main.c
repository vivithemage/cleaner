/*  Magicleaner: file organiser which uses magic numbers to sort files. 

    Copyright (C) 2010 Reza Snowdon <vivi at mage.me.uk>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <magic.h>
#include <gtk/gtk.h>

static magic_t magic_cookie;

/*initialising magic database for use*/
int magic_database_init(void) 
{
	magic_cookie = magic_open(MAGIC_MIME);
	if (magic_cookie == NULL) {
	        printf("unable to initialize magic library\n");
	        return 1;
	}
	printf("Loading default magic database\n");
	if (magic_load(magic_cookie, NULL) != 0) {
		printf("cannot load magic database - %s\n", magic_error(magic_cookie));
	        magic_close(magic_cookie);
		return 1;
	}
	return 0;
}

/*look at the mime, if the directory does not already exist, make it*/
char *make_dir(const char *mime_to_sort, char *move_to_dir)
{
	char full_mvpath[PATH_MAX];
	char *images = "image";
	char *directory = "directory";
	char *unknown ="unknown";	
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
		printf("File is a directory; skipping\n");
		return 0;
	}
	if (rename(dir_plus_act, movedir_mime) == 0) {
		printf("success: file %s moved to %s\n", dir_plus_act, movedir_mime); 
		return 0;
	}
	else {
		printf("Did not move file %s to %s for unknown reasons (Probably because the file type has not been added.\n", dir_plus_act, movedir_mime);	
		printf("You could request this file to be added or edit the source youself ;), please email any modifications to vivi at mage.me.uk\n"); 
		return 0;
	}
}

/*code run after organize is clicked*/	
int organize_clicked (void)	
{	
	char sort_directory[PATH_MAX]; // Directory which contains all the files to be sorted. 
	char dir_to_make[PATH_MAX];   // The mime of the file.
	char dir_plus_act[PATH_MAX];   // Sort directory and file nime concatenated.
	char move_to_dir[PATH_MAX];    // Directory to create new folders in and move files to. 
	char movedir_mime[PATH_MAX];   // move to directory with mime direcory concatenated.
		
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
 
	}
	printf("Organize end.\n");
	return 0;
}

/*have one of these for each button?*/
static void call_mime_check(GtkWidget *Widget, gpointer data)	{
	organize_clicked();
}

/*Gtk icon code*/
GdkPixbuf *create_pixbuf(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if (!pixbuf) {
   	fprintf(stderr, "%s\n", error->message);
   	g_error_free(error);
   }
   return pixbuf;
}

int main(int argc, char *argv[])
{	
	/* maybe place gtk related code in a seperate file? */
	GtkWidget *window;
	GtkWidget *table;

	/* Chosen widgets */	
	GtkWidget *file_chooser_directory;
	GtkWidget *organize_button; 
	
	gtk_init (&argc, &argv);
	
	magic_database_init();	
		
	/* setting window variables and related */	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW(window), 400, 200);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("Ban.jpg"));
	gtk_window_set_title(GTK_WINDOW(window), "magic-cleaner: File organizer");

	/* Create and put the table in the main window */
	table = gtk_table_new (14, 14, TRUE); 
	gtk_container_add (GTK_CONTAINER (window), table);

	/* Create organize button and point it to the sorter and allighn it to the table */
	organize_button = gtk_button_new_with_label ("Organize");	
	g_signal_connect (G_OBJECT (organize_button), "clicked", G_CALLBACK (call_mime_check), NULL);	
	gtk_table_attach_defaults (GTK_TABLE (table), organize_button, 1, 2, 0, 1);
	gtk_widget_show (organize_button);

	/* Create the file chooser widget, point the data to the new variable and allign
 	   to the table */
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileFilter *filter;	



	
	/* destruction */
	g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

	gtk_widget_show_all(window);	
	gtk_main ();
	return 0;
}
