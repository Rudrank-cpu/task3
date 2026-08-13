#include "songs.h"
#include <cstdlib>
#include <limits>

using namespace std;

// ---------- Basic "GUI" building blocks (ANSI escape codes) ----------
// These work in Windows Terminal, VS Code terminal, and Linux/Mac terminals.
// No external GUI library used -> keeps it "basic C++".

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"
#define MAGENTA "\033[35m"

// Clears the screen on both Windows and Linux/Mac
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Draws a horizontal line of a given width using a box character
void drawLine(int width)
{
    cout << CYAN;
    for (int i = 0; i < width; i++)
        cout << "-";
    cout << RESET << endl;
}

// Draws the application header/banner
void printHeader()
{
    clearScreen();
    drawLine(45);
    cout << BOLD << MAGENTA << "        MUSIC PLAYLIST MANAGER" << RESET << endl;
    drawLine(45);
}

// Pauses so the user can read the output before the screen clears again
void pauseScreen()
{
    cout << YELLOW << "\nPress Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Draws the main menu as a "panel"
void printMenu()
{
    cout << GREEN << "\n [1]  " << RESET << "Add Song at Front\n";
    cout << GREEN << " [2]  " << RESET << "Add Song at End\n";
    cout << GREEN << " [3]  " << RESET << "Display Playlist\n";
    cout << GREEN << " [4]  " << RESET << "Play / Search Specific Song\n";
    cout << GREEN << " [5]  " << RESET << "Remove Song\n";
    cout << GREEN << " [6]  " << RESET << "Randomize Playlist\n";
    cout << GREEN << " [7]  " << RESET << "Play Songs by Artist\n";
    cout << GREEN << " [8]  " << RESET << "Sort Playlist by Artist\n";
    cout << GREEN << " [9]  " << RESET << "Play Songs by Theme\n";
    cout << RED   << " [10] " << RESET << "Exit\n";
    drawLine(45);
}

// Validates that the user entered a real integer choice
int getValidChoice()
{
    int choice;

    while (true)
    {
        cout << YELLOW << "\nEnter Choice : " << RESET;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input! Please enter a number.\n" << RESET;
            continue;
        }

        return choice;
    }
}

int main()
{
    song_list l;
    int choice;
    string title, artist, theme;

    while (true)
    {
        printHeader();
        printMenu();
        choice = getValidChoice();

        switch (choice)
        {
        case 1:
        {
            printHeader();
            cout << BOLD << "Add Song at Front\n" << RESET;
            drawLine(45);
            song s1 = l.input();
            l.add_song_front(s1);
            cout << GREEN << "\nSong Added Successfully.\n" << RESET;
            pauseScreen();
            break;
        }

        case 2:
        {
            printHeader();
            cout << BOLD << "Add Song at End\n" << RESET;
            drawLine(45);
            song s1 = l.input();
            l.add_song_end(s1);
            cout << GREEN << "\nSong Added Successfully.\n" << RESET;
            pauseScreen();
            break;
        }

        case 3:
        {
            printHeader();
            cout << BOLD << "Playlist\n" << RESET;
            drawLine(45);
            l.display();
            pauseScreen();
            break;
        }

        case 4:
        {
            printHeader();
            cout << BOLD << "Play / Search Specific Song\n" << RESET;
            drawLine(45);
            l.search();
            pauseScreen();
            break;
        }

        case 5:
        {
            printHeader();
            cout << BOLD << "Remove Song\n" << RESET;
            drawLine(45);
            cin.ignore();
            cout << "Enter Song Title to Remove : ";
            getline(cin, title);
            l.removeSong(title);
            pauseScreen();
            break;
        }

        case 6:
        {
            printHeader();
            cout << BOLD << "Randomized Playlist\n" << RESET;
            drawLine(45);
            l.randomize();
            pauseScreen();
            break;
        }

        case 7:
        {
            printHeader();
            cout << BOLD << "Play Songs by Artist\n" << RESET;
            drawLine(45);
            cin.ignore();
            cout << "Enter Artist Name : ";
            getline(cin, artist);
            l.Artist(artist);
            pauseScreen();
            break;
        }

        case 8:
        {
            printHeader();
            cout << BOLD << "Sort Playlist by Artist\n" << RESET;
            drawLine(45);
            l.sort();
            cout << "\nSorted Playlist:\n";
            l.display();
            pauseScreen();
            break;
        }

        case 9:
        {
            printHeader();
            cout << BOLD << "Play Songs by Theme\n" << RESET;
            drawLine(45);
            cin.ignore();
            cout << "Enter Theme : ";
            getline(cin, theme);
            l.playTheme(theme);
            pauseScreen();
            break;
        }

        case 10:
        {
            printHeader();
            cout << GREEN << "\nThank you for using Music Playlist Manager!\n" << RESET;
            return 0;
        }

        default:
        {
            cout << RED << "\nInvalid Choice! Please try again.\n" << RESET;
            pauseScreen();
        }
        }
    }

    return 0;
}
