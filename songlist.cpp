#include "songs.h"


using namespace std;


// Constructor
song_list::song_list()
{
    start = end = NULL;
}


// Add Song at End
void song_list::add_song_end(song s1)
{
    song *ns = new song;


    if (!ns)
        return;


    ns->title = s1.title;
    ns->artist = s1.artist;
    ns->theme = s1.theme;
    ns->duration = s1.duration;
    ns->next = NULL;


    if (start == NULL)
    {
        start = end = ns;
        return;
    }


    end->next = ns;
    end = ns;
}


// Add Song at Front
void song_list::add_song_front(song s1)
{
    song *ns = new song;


    if (!ns)
        return;


    ns->title = s1.title;
    ns->artist = s1.artist;
    ns->theme = s1.theme;
    ns->duration = s1.duration;


    if (start == NULL)
    {
        ns->next = NULL;
        start = end = ns;
    }
    else
    {
        ns->next = start;
        start = ns;
    }
}


// Input Song
song song_list::input()
{
    song s1;


    cin.ignore();


    cout << "Enter Song Title : ";
    getline(cin, s1.title);


    cout << "Enter Artist Name : ";
    getline(cin, s1.artist);


    cout << "Enter Theme : ";
    getline(cin, s1.theme);


    cout << "Enter Duration (minutes) : ";
    cin >> s1.duration;


    s1.next = NULL;


    return s1;
}


// Display Playlist
void song_list::display()
{
    song *ptr = start;


    if (ptr == NULL)
    {
        cout << "Playlist is empty.\n";
        return;
    }


    while (ptr)
    {
        cout << "Title    : " << ptr->title << endl;
        cout << "Artist   : " << ptr->artist << endl;
        cout << "Theme    : " << ptr->theme << endl;
        cout << "Duration : " << ptr->duration << " min\n";
        cout << "-----------------------------\n";


        ptr = ptr->next;
    }
}


// Play/Search Specific Song
void song_list::search()
{
    if (start == NULL)
    {
        cout << "Playlist is Empty.\n";
        return;
    }


    string search;


    cin.ignore();


    cout << "Enter Song Title : ";
    getline(cin, search);


    song *ptr = start;


    while (ptr)
    {
        if (ptr->title == search)
        {
            cout << "\nNow Playing\n";
            cout << "Title    : " << ptr->title << endl;
            cout << "Artist   : " << ptr->artist << endl;
            cout << "Theme    : " << ptr->theme << endl;
            cout << "Duration : " << ptr->duration << " min\n";
            return;
        }


        ptr = ptr->next;
    }


    cout << "Song NOT FOUND!\n";
}


// Artist Search
bool song_list::artistSearch(string s)
{
    song *ptr = start;


    while (ptr)
    {
        if (ptr->artist == s)
            return true;


        ptr = ptr->next;
    }


    return false;
}


// Play Songs by Artist
void song_list::Artist(string s)
{
    if (start == NULL)
    {
        cout << "Playlist Empty.\n";
        return;
    }


    if (!artistSearch(s))
    {
        cout << "Artist not found.\n";
        return;
    }


    song *ptr = start;


    cout << "\nSongs by " << s << endl;


    while (ptr)
    {
        if (ptr->artist == s)
        {
            cout << "Playing : "
                 << ptr->title
                 << " (" << ptr->duration << " min)\n";
        }


        ptr = ptr->next;
    }
}


// Play Songs by Theme
void song_list::playTheme(string theme)
{
    song *ptr = start;


    bool found = false;


    while (ptr)
    {
        if (ptr->theme == theme)
        {
            cout << "Playing : "
                 << ptr->title
                 << " - "
                 << ptr->artist
                 << endl;


            found = true;
        }


        ptr = ptr->next;
    }


    if (!found)
        cout << "No Songs Found.\n";
}


// Remove Song
void song_list::removeSong(string title)
{
    if (start == NULL)
    {
        cout << "Playlist Empty.\n";
        return;
    }


    song *temp = start;
    song *prev = NULL;


    while (temp != NULL && temp->title != title)
    {
        prev = temp;
        temp = temp->next;
    }


    if (temp == NULL)
    {
        cout << "Song Not Found.\n";
        return;
    }


    if (temp == start)
    {
        start = start->next;


        if (start == NULL)
            end = NULL;
    }
    else
    {
        prev->next = temp->next;


        if (temp == end)
            end = prev;
    }


    delete temp;


    cout << "Song Removed Successfully.\n";
}


// Randomize Playlist
void song_list::randomize()
{
    if (start == NULL)
    {
        cout << "Playlist Empty.\n";
        return;
    }


    // Count number of songs
    int count = 0;
    song *ptr = start;


    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }


    // Array to keep track of visited songs
    bool *visited = new bool[count];


    for (int i = 0; i < count; i++)
        visited[i] = false;


    cout << "\nRandom Playlist\n";


    for (int i = 0; i < count; i++)
    {
        int r;


        do
        {
            r = rand() % count;
        }
        while (visited[r]);


        visited[r] = true;


        ptr = start;


        for (int j = 0; j < r; j++)
            ptr = ptr->next;


        cout << i + 1 << ". "
             << ptr->title
             << " - "
             << ptr->artist
             << endl;
    }


    delete[] visited;
}


// Sort by Artist
void song_list::sort()
{
    if (start == NULL || start->next == NULL)
    {
        cout << "Not enough songs to sort.\n";
        return;
    }


    song *i;
    song *j;


    for (i = start; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->artist > j->artist)
            {
                swap(i->title, j->title);
                swap(i->artist, j->artist);
                swap(i->theme, j->theme);
                swap(i->duration, j->duration);
            }
        }
    }


    cout << "\nPlaylist Sorted by Artist Successfully.\n";
}





// =====================================================================
// WEB API HELPER METHODS
// Added purely to support the HTTP/JSON layer (server.cpp).
// Nothing above this line has been modified from the original backend.
// =====================================================================

vector<song> song_list::getAllSongs()
{
    vector<song> result;
    song *ptr = start;

    while (ptr)
    {
        result.push_back(*ptr);
        ptr = ptr->next;
    }

    return result;
}

bool song_list::addFront(string title, string artist, string theme, int duration)
{
    song s1;
    s1.title = title;
    s1.artist = artist;
    s1.theme = theme;
    s1.duration = duration;
    s1.next = NULL;

    add_song_front(s1);   // reuse original backend logic
    return true;
}

bool song_list::addEnd(string title, string artist, string theme, int duration)
{
    song s1;
    s1.title = title;
    s1.artist = artist;
    s1.theme = theme;
    s1.duration = duration;
    s1.next = NULL;

    add_song_end(s1);   // reuse original backend logic
    return true;
}

bool song_list::removeByTitle(string title)
{
    if (start == NULL)
        return false;

    song *temp = start;
    song *prev = NULL;

    while (temp != NULL && temp->title != title)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return false;

    if (temp == start)
    {
        start = start->next;
        if (start == NULL)
            end = NULL;
    }
    else
    {
        prev->next = temp->next;
        if (temp == end)
            end = prev;
    }

    delete temp;
    return true;
}

bool song_list::searchByTitle(string title, song &result)
{
    song *ptr = start;

    while (ptr)
    {
        if (ptr->title == title)
        {
            result = *ptr;
            return true;
        }
        ptr = ptr->next;
    }

    return false;
}

vector<song> song_list::getByArtist(string s)
{
    vector<song> result;
    song *ptr = start;

    while (ptr)
    {
        if (ptr->artist == s)
            result.push_back(*ptr);
        ptr = ptr->next;
    }

    return result;
}

vector<song> song_list::getByTheme(string theme)
{
    vector<song> result;
    song *ptr = start;

    while (ptr)
    {
        if (ptr->theme == theme)
            result.push_back(*ptr);
        ptr = ptr->next;
    }

    return result;
}

vector<song> song_list::getRandomOrder()
{
    vector<song> result;

    if (start == NULL)
        return result;

    int count = 0;
    song *ptr = start;

    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }

    bool *visited = new bool[count];
    for (int i = 0; i < count; i++)
        visited[i] = false;

    for (int i = 0; i < count; i++)
    {
        int r;
        do
        {
            r = rand() % count;
        }
        while (visited[r]);

        visited[r] = true;

        ptr = start;
        for (int j = 0; j < r; j++)
            ptr = ptr->next;

        result.push_back(*ptr);
    }

    delete[] visited;
    return result;
}

// ---- JSON helpers ----

string escapeJSON(string s)
{
    string out;
    for (size_t i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if (c == '"' || c == '\\')
        {
            out += '\\';
            out += c;
        }
        else if (c == '\n')
        {
            out += "\\n";
        }
        else
        {
            out += c;
        }
    }
    return out;
}

string songToJSON(const song &s)
{
    string json = "{";
    json += "\"title\":\"" + escapeJSON(s.title) + "\",";
    json += "\"artist\":\"" + escapeJSON(s.artist) + "\",";
    json += "\"theme\":\"" + escapeJSON(s.theme) + "\",";
    json += "\"duration\":" + to_string(s.duration);
    json += "}";
    return json;
}

string songsToJSONArray(vector<song> songs)
{
    string json = "[";
    for (size_t i = 0; i < songs.size(); i++)
    {
        json += songToJSON(songs[i]);
        if (i + 1 < songs.size())
            json += ",";
    }
    json += "]";
    return json;
}
