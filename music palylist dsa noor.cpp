#include <iostream>
#include <string>
using namespace std;

struct Node {
    string song;
    Node* next;  

    Node(const string& song) : song(song), next(nullptr) {}
};

class CircularPlaylist {
private:
    Node* head; 
    Node* tail;

public:
    CircularPlaylist() : head(nullptr), tail(nullptr) {}

    ~CircularPlaylist() {
        if (head == nullptr) return;

        Node* current = head;
        Node* nextNode;

        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
    }

    void addSong(const string& song) {
        Node* newNode = new Node(song);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            tail->next = head; 
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
        cout << "Added ‘" << song << "’ to the playlist." << endl;
    }

    void removeSong(const string& song) {
        if (head == nullptr) {
            cout << "Playlist is empty. No songs to remove." << endl;
            return;
        }

        Node* current = head;
        Node* previous = nullptr;

        do {
            if (current->song == song) {
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                } else if (current == head) {
                    head = head->next;
                    tail->next = head;
                } else if (current == tail) {
                    tail = previous;
                    tail->next = head;
                } else {
                    previous->next = current->next;
                }
                delete current;
                cout << "Removed ‘" << song << "’ from the playlist." << endl;
                return;
            }
            previous = current;
            current = current->next;
        } while (current != head);

        cout << "Song ‘" << song << "’ not found in the playlist." << endl;
    }

    void playNext() {
        if (head == nullptr) {
            cout << "Playlist is empty. No songs to play." << endl;
            return;
        }
        static Node* current = head;
        cout << "Now playing: " << current->song << "’" << endl;
        current = current->next;
    }

    void displayPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }
        cout << "Current Playlist:" << endl;
        Node* current = head;
        int index = 1;
        do {
            cout << index << ". " << current->song << endl;
            current = current->next;
            index++;
        } while (current != head);
    }
};

int main() {
    CircularPlaylist playlist;

    playlist.addSong("Song 1 – Atif Aslam");
    playlist.addSong("Song 2 – Ali Zafar");
    playlist.addSong("Song 3 – Arjit Singh");
    playlist.addSong("Song 4 – Tony Kakkar");
    playlist.addSong("Song 5 – Honey Singh");

    playlist.displayPlaylist();

    playlist.playNext();
    playlist.playNext(); 

    playlist.removeSong("Song 3 – Arjit Singh");

    playlist.addSong("Song 6 – Armaan Malik");

    playlist.displayPlaylist();
    playlist.playNext(); 
    playlist.playNext();
    playlist.playNext(); 
    playlist.playNext(); 

    return 0;
}
