#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <fstream>

using namespace std;

class Book {
public:
    string title, author, genre, description;
    float rating;

    Book(string t, string a, string g, string d, float r)
        : title(t), author(a), genre(g), description(d), rating(r) {}

    void displayInfo() const {
        cout << "Title: " << title << "\nAuthor: " << author
             << "\nGenre: " << genre << "\nDescription: " << description
             << "\nRating: " << rating << "/5" << endl;
        cout << "------------------------" << endl;
    }
};
void loadBooksFromFile(vector<Book>& books) {
    ifstream inFile("books.txt");
    if (!inFile) {
        cout << "No existing book file found. Starting fresh!" << endl;
        return;
    }
    books.clear();
    string title, author, genre, description;
    float rating;
    while (getline(inFile, title, '|') &&
           getline(inFile, author, '|') &&
           getline(inFile, genre, '|') &&
           getline(inFile, description, '|') &&
           (inFile >> rating)) {
        inFile.ignore();
        books.emplace_back(title, author, genre, description, rating);
    }
    inFile.close();
}

void saveBooksToFile(const vector<Book>& books) {
    ofstream outFile("books.txt");
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    for (const auto& book : books) {
        outFile << book.title << "|" << book.author << "|" << book.genre << "|"
                << book.description << "|" << book.rating << "\n";
    }
    outFile.close();
}

void addBook(vector<Book>& books) {
    string title, author, genre, description;
    float rating;

    cout << "Enter book title: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);

    cout << "Enter author name: ";
    getline(cin, author);

    cout << "Enter genre (Poetry, Drama, Novel, Thriller, Fiction, Romance, Natok): ";
    getline(cin, genre);

    cout << "Enter description: ";
    getline(cin, description);

    cout << "Enter rating (0 to 5): ";
    while (!(cin >> rating) || rating < 0 || rating > 5) {
        cout << "Invalid input! Enter a rating between 0 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    books.emplace_back(title, author, genre, description, rating);
    saveBooksToFile(books);
    cout << "Book added successfully and saved!" << endl;
}

void filterByGenre(const vector<Book>& books, const string& genre, float minRating) {
    vector<Book> filteredBooks;
    for (const auto& book : books) {
        if (book.genre == genre && book.rating >= minRating) {
            filteredBooks.push_back(book);
        }
    }
    sort(filteredBooks.begin(), filteredBooks.end(), [](const Book& a, const Book& b) {
        return a.rating > b.rating;
    });

    if (filteredBooks.empty()) cout << "No books found." << endl;
    else for (const auto& book : filteredBooks) book.displayInfo();
}

void filterByAuthor(const vector<Book>& books, const string& authorName) {
    bool found = false;
    for (const auto& book : books) {
        if (book.author == authorName) {
            book.displayInfo();
            found = true;
        }
    }
    if (!found) cout << "No books found for this author." << endl;
}

void deleteBook(vector<Book>& books) {
    string title;
    cout << "Enter the title of the book to delete: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);

    auto it = remove_if(books.begin(), books.end(), [&title](const Book& book) {
        return book.title == title;
    });

    if (it != books.end()) {
        books.erase(it, books.end());
        saveBooksToFile(books);
        cout << "Book deleted successfully!" << endl;
    } else {
        cout << "No book found with the given title." << endl;
    }
}

void updateBook(vector<Book>& books) {
    string title;
    cout << "Enter the title of the book to update: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);

    for (auto& book : books) {
        if (book.title == title) {
            cout << "Enter new title (press enter to keep unchanged): ";
            string newTitle;
            getline(cin, newTitle);
            if (!newTitle.empty()) book.title = newTitle;

            cout << "Enter new author (press enter to keep unchanged): ";
            string newAuthor;
            getline(cin, newAuthor);
            if (!newAuthor.empty()) book.author = newAuthor;

            cout << "Enter new genre (press enter to keep unchanged): ";
            string newGenre;
            getline(cin, newGenre);
            if (!newGenre.empty()) book.genre = newGenre;

            cout << "Enter new description (press enter to keep unchanged): ";
            string newDescription;
            getline(cin, newDescription);
            if (!newDescription.empty()) book.description = newDescription;

            cout << "Enter new rating (0 to 5, -1 to keep unchanged): ";
            float newRating;
            if (cin >> newRating && newRating >= 0 && newRating <= 5) {
                book.rating = newRating;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            saveBooksToFile(books);
            cout << "Book updated successfully!" << endl;
            return;
        }
    }
    cout << "No book found with the given title." << endl;
}

int main() {
    vector<Book> bookList={
        Book("Gitanjali", "Rabindranath Tagore", "Poetry", "Nobel-winning poetry collection", 4.9),
        Book("Sanchayita", "Rabindranath Tagore", "Poetry", "Collection of poems", 4.8),
        Book("Sonar Tori", "Jibananda Das", "Poetry", "Famous poetry collection", 4.7),
        Book("Raktakarabi", "Rabindranath Tagore", "Drama", "Symbolic Bengali drama", 4.6),
        Book("Kobor", "Munier Chowdhury", "Drama", "Popular Bengali play", 4.8),
        Book("Chhaya Nat", "Haradhan Bandyopadhyay", "Drama", "Well-known Bengali drama", 4.7),
        Book("Oedipus", "Sophocles", "Drama", "Greek tragedy in Bengali", 4.5),
        Book("Dwikhandita", "Taslima Nasrin", "Drama", "Famous stage play", 4.4),
        Book("Shikhandi Kotha", "Selim Al Deen", "Drama", "Controversial drama", 4.6),
        Book("Payer Awaj Pawa Jay", "Syed Shamsul Haque", "Drama", "War-time drama", 4.9),
        Book("Rupbhan", "Sarat Chandra Chattopadhyay", "Drama", "Popular drama", 4.7),
        Book("Mayur Singhason", "Abdullah Al Mamun", "Drama", "Bengali political drama", 4.8),
        Book("Titas Ekti Nadir Naam", "Adwaita Mallabarman", "Drama", "Based on real-life struggles", 4.6),
        Book("Pather Panchali", "Bibhutibhushan Bandyopadhyay", "Novel", "Masterpiece of Bengali literature", 4.9),
        Book("Maa", "Anisul Hoque", "Novel", "Novel about Bangladesh Liberation War", 4.9),
        Book("Aguner Poroshmoni", "Humayun Ahmed", "Novel", "Based on 1971 war", 4.8),
        Book("Debi", "Humayun Ahmed", "Novel", "First book of Misir Ali series", 4.7),
        Book("Lal Nil Dipabali", "Humayun Ahmed", "Novel", "Autobiographical novel", 4.8),
        Book("Opekkha", "Humayun Ahmed", "Novel", "Love story novel", 4.6),
        Book("Moddhyanyo", "Zahir Raihan", "Novel", "Political novel", 4.7),
        Book("Jibonanonder Kobita", "Jibananda Das", "Novel", "Literary criticism", 4.7),
        Book("Rajakar", "Harun Rashid", "Novel", "Historical novel", 4.5),
        Book("Shesher Kobita", "Rabindranath Tagore", "Novel", "A poetic novel", 4.6),
        Book("Misir Ali Omnibus", "Humayun Ahmed", "Thriller", "Psychological thriller series", 4.7),
        Book("Feluda Somogro", "Satyajit Ray", "Thriller", "Popular detective stories", 4.9),
        Book("Sharadindu Omnibus", "Sharadindu Bandyopadhyay", "Thriller", "Byomkesh Bakshi stories", 4.8),
        Book("Dracula", "Bram Stoker", "Thriller", "Classic horror thriller", 4.6),
        Book("The Girl with the Dragon Tattoo", "Stieg Larsson", "Thriller", "Modern crime thriller", 4.8),
        Book("Gone Girl", "Gillian Flynn", "Thriller", "Psychological thriller", 4.7),
        Book("Sherlock Holmes", "Arthur Conan Doyle", "Thriller", "Detective fiction", 4.9),
        Book("The Silence of the Lambs", "Thomas Harris", "Thriller", "Psychological horror thriller", 4.8),
        Book("Shutter Island", "Dennis Lehane", "Thriller", "Mind-bending thriller", 4.7),
        Book("The Da Vinci Code", "Dan Brown", "Thriller", "Mystery thriller", 4.6),
        Book("The Great Gatsby", "F. Scott Fitzgerald", "Fiction", "A story about the Jazz Age", 4.4),
        Book("1984", "George Orwell", "Fiction", "A novel about totalitarianism", 4.7),
        Book("Nana Ranger Dinguli", "Selim Al Deen", "Natok", "Bengali stage drama", 4.6),
        Book("Shakuntala", "Kalidasa", "Natok", "Sanskrit play adapted in Bengali", 4.8),
        Book("Pride and Prejudice", "Jane Austen", "Romance", "Classic romantic tale", 4.5),
        Book("Devdas", "Saratchandra Chattopadhyay", "Romance", "Classic Bengali romantic novel", 4.7),
        Book("Nana Ranger Dinguli", "Selim Al Deen", "Natok", "Bengali stage drama", 4.6),
        Book("Shakuntala", "Kalidasa", "Natok", "Sanskrit play adapted in Bengali", 4.8),
        Book("Kobor", "Munier Chowdhury", "Natok", "Famous Bangladeshi play", 4.7),
        Book("Chhaya Nat", "Haradhan Bandyopadhyay", "Natok", "Popular Bengali stage play", 4.5),
        Book("Dwikhandita", "Taslima Nasrin", "Natok", "Controversial drama", 4.4),
        Book("Mayur Singhason", "Abdullah Al Mamun", "Natok", "Bengali political drama", 4.6),
        Book("Titas Ekti Nadir Naam", "Adwaita Mallabarman", "Natok", "Based on real-life struggles", 4.6),
        Book("Payer Awaj Pawa Jay", "Syed Shamsul Haque", "Natok", "Liberation war-based drama", 4.9),
        Book("Shikhandi Kotha", "Selim Al Deen", "Natok", "Socially controversial drama", 4.5),
        Book("Oedipus", "Sophocles", "Natok", "Greek tragedy translated into Bengali", 4.6),
        Book("Pride and Prejudice", "Jane Austen", "Romance", "Classic romantic tale", 4.5),
        Book("Devdas", "Saratchandra Chattopadhyay", "Romance", "Classic Bengali romantic novel", 4.7),
        Book("Romeo and Juliet", "William Shakespeare", "Romance", "Famous tragic love story", 4.9),
        Book("Bishad Sindhu", "Mir Mosharraf Hossain", "Romance", "Historical love tragedy", 4.8),
        Book("Shesher Kobita", "Rabindranath Tagore", "Romance", "A poetic love novel", 4.7),
        Book("Jaya", "Anisul Hoque", "Romance", "Modern love story", 4.6),
        Book("Hajar Bochor Dhore", "Zahir Raihan", "Romance", "Bengali classic romantic novel", 4.7),
        Book("Opekkha", "Humayun Ahmed", "Romance", "Emotional love novel", 4.6),
        Book("Ami Topu", "Muhammed Zafar Iqbal", "Romance", "Youth love story", 4.5),
        Book("Premer Golpo", "Samaresh Majumdar", "Romance", "Bengali love fiction", 4.6),

    };
    int choice;

    for (;;) {
        cout << "\nWelcome to the Book Recommendation System!" << endl;
        cout << "1. Search by Genre\n2. Search by Author\n3. Add a New Book\n4. Delete a Book\n5. Update a Book\n6. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 6) {
            cout << "Thank you for using the system! Books saved to file." << endl;
            break;
        }

        switch (choice) {
            case 1: {
                string genre;
                float minRating;
                cout << "Enter genre: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, genre);
                cout << "Enter minimum rating (0-5): ";
                while (!(cin >> minRating) || minRating < 0 || minRating > 5) {
                    cout << "Invalid input! Enter a rating between 0 and 5: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                filterByGenre(bookList, genre, minRating);
                break;
            }
            case 2:
                {
                string author;
                cout << "Enter author name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, author);
                filterByAuthor(bookList, author);
                break;
            }
            case 3:
                addBook(bookList);
                break;
            case 4:
                deleteBook(bookList);
                break;
            case 5:
                updateBook(bookList);
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}
