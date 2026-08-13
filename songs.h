#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>


using namespace std;
using namespace std;
struct song
{
    string title, artist,theme;
    int duration;
    song *next;
};




class song_list
{
    song *start;
    song *end;




    public:
        song_list();


        song input();
        void add_song_end(song s1);
        void add_song_front(song s1);
        void display();
        void search();
        void randomize();
        void sort();
        void Artist(string s);
        void playTheme(string theme);
        bool artistSearch(string s);
        void removeSong(string title);

        // ---- Web API helper methods ----
        // These are ADDITIVE only. Every original method above (input, display,
        // search, Artist, playTheme, removeSong, randomize, sort) is completely
        // untouched. The methods below exist purely because the console
        // versions read from cin / print to cout, which doesn't work over
        // HTTP -- these instead take plain parameters and RETURN data so the
        // web server can turn it into JSON. They reuse the exact same
        // linked-list traversal logic as the originals.
        vector<song> getAllSongs();
        bool addFront(string title, string artist, string theme, int duration);
        bool addEnd(string title, string artist, string theme, int duration);
        bool removeByTitle(string title);
        bool searchByTitle(string title, song &result);
        vector<song> getByArtist(string s);
        vector<song> getByTheme(string theme);
        vector<song> getRandomOrder();
    };

// ---- JSON helpers (used by the web server, not part of the backend logic) ----
string escapeJSON(string s);
string songToJSON(const song &s);
string songsToJSONArray(vector<song> songs);
















