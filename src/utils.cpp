//General utils
// standard libs
#include <iostream>
#include <magic.h>

using namespace std;
static magic_t magic_cookie;

/* Initialising magic database for use */
int magic_database_init(void) 
{
	magic_cookie = magic_open(MAGIC_MIME);
	if (magic_cookie == NULL) {
	        cout << "Unable to initialize magic library\n";
	        return 1;
	}
	cout << "Loading default magic database\n";
	if (magic_load(magic_cookie, NULL) != 0) {
		cout << "Cannot load magic database - " << magic_error(magic_cookie) << endl;
	        magic_close(magic_cookie);
		return 1;
	}
	return 0;
}
