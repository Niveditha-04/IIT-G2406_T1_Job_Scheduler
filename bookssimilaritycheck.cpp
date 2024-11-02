#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <iomanip> // Include for std::setw

using namespace std;

#define MAX_FILES 60
#define MAX_UNIQUE_WORDS 1000
#define MAX_WORD_LENGTH 50

// Struct to store similarity scores between file pairs
struct Similarity {
    double score;
    int file1;
    int file2;
};

// Function declarations
void normalizeText(const char* input, char* normalized);
bool isStopWord(const char* word);
int computeWordFrequency(const char* fileName, char words[MAX_UNIQUE_WORDS][MAX_WORD_LENGTH], 
                         int* wordCounts, int* totalWords);
double calculateSimilarity(char words1[MAX_UNIQUE_WORDS][MAX_WORD_LENGTH], int counts1[], 
                           int totalWords1, int uniqueWords1, 
                           char words2[MAX_UNIQUE_WORDS][MAX_WORD_LENGTH], int counts2[], 
                           int totalWords2, int uniqueWords2);

// Normalizes the input text by converting it to uppercase and filtering out non-alphanumeric characters
void normalizeText(const char* input, char* normalized) {
    int j = 0;
    for (size_t i = 0; i < strlen(input); ++i) {
        if (isalnum(static_cast<unsigned char>(input[i]))) {
            normalized[j++] = toupper(static_cast<unsigned char>(input[i]));
        }
    }
    normalized[j] = '\0';  // Null-terminate the string
}

// Checks if a word is a stop word
bool isStopWord(const char* word) {
    const char* stopWords[] = {"A", "AND", "AN", "OF", "IN", "THE"};
    for (int i = 0; i < 6; ++i) {
        if (strcmp(word, stopWords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Computes the word frequency from a given file
int computeWordFrequency(const char* fileName, char words[MAX_UNIQUE_WORDS][MAX_WORD_LENGTH], 
                         int* wordCounts, int* totalWords) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << fileName << endl;
        return -1;  // Error opening file
    }

    char word[MAX_WORD_LENGTH]; // Use char array for word
    char normalized[MAX_WORD_LENGTH];
    *totalWords = 0;
    int uniqueWordCount = 0;

    // Read words from file and normalize
    while (file >> word) {
        normalizeText(word, normalized);

        // Skip stopwords and empty words
        if (isStopWord(normalized) || normalized[0] == '\0') {
            continue;
        }

        // Check if the word already exists in the list
        bool found = false;
        for (int i = 0; i < uniqueWordCount; ++i) {
            if (strcmp(words[i], normalized) == 0) {
                wordCounts[i]++;
                found = true;
                break;
            }
        }

        // If the word is new, add it to the list
        if (!found && uniqueWordCount < MAX_UNIQUE_WORDS) {
            strcpy(words[uniqueWordCount], normalized);
            wordCounts[uniqueWordCount] = 1;
            uniqueWordCount++;
        }

        (*totalWords)++;
    }

    file.close();
    return uniqueWordCount;
}

// Calculates similarity between two sets of words
double calculateSimilarity(char words1[MAX_UNIQUE_WORDS][MAX_WORD_LENGTH], int counts1[], 
                           int totalWords1, int uniqueWords1, 
                           char words2[MAX_UNIQUE_WORDS][MAX_WORD_LENGTH], int counts2[], 
                           int totalWords2, int uniqueWords2) {
    double similarity = 0.0;

    // Compare words from the first file with the second file
    for (int i = 0; i < uniqueWords1; ++i) {
        for (int j = 0; j < uniqueWords2; ++j) {
            if (strcmp(words1[i], words2[j]) == 0) {
                double freq1 = (double)counts1[i] / totalWords1;
                double freq2 = (double)counts2[j] / totalWords2;
                similarity += freq1 + freq2;
                break;
            }
        }
    }

    return similarity;
}

int main() {
    // List of filenames (exactly 60 files)
    const char* fileNames[] = {
        "books/Cats by Moncrif.txt", "books/Foxes Book of Martyrs Part 1.txt", 
        "books/Foxes Book of Martyrs Part 2.txt", "books/Foxes Book of Martyrs Part 3.txt",
        "books/Foxes Book of Martyrs Part 4.txt", "books/Foxes Book of Martyrs Part 5.txt",
        "books/Foxes Book of Martyrs Part 6.txt", "books/Gerard's Herbal Vol. 3.txt", 
        "books/Gerards Herbal Vol. 1.txt", "books/Gerards Herbal Vol. 2.txt", 
        "books/Gerards Herbal Vol.4.txt", "books/Gil Blas.txt", "books/Gossip in a Library.txt",
        "books/Hudibras.txt", "books/King of the Beggars.txt", "books/Knocknagow.txt", 
        "books/Les Chats par Moncrif.txt", "books/Lives and Anecdotes of Misers.txt", 
        "books/Love and Madness - Herbert Croft.txt", "books/Memoirs of Laetitia Pilkington V 1.txt",
        "books/Memoirs of Laetitia Pilkington V 2.txt", "books/Memoirs of Laetitia Pilkington V 3.txt", 
        "books/Memoirs of Mrs Margaret Leeson - Peg Plunkett.txt", "books/Monro his Expedition.txt", 
        "books/Mrs Beetons Book of Household Management.txt", "books/Out of the Hurly-Burly.txt", 
        "books/Percys Reliques.txt", "books/Pompey The Little.txt", 
        "books/Radical Pamphlets from the English Civil War.txt", "books/Scepsis Scientifica.txt", 
        "books/The Anatomy of Melancholy Part 1.txt", "books/The Anatomy of Melancholy Part 2.txt", 
        "books/The Anatomy of Melancholy Part 3.txt", "books/The Complete Cony-catching.txt", 
        "books/The Consolation of Philosophy.txt", "books/The Covent Garden Calendar.txt", 
        "books/The Devil on Two Sticks.txt", "books/The Diary of a Lover of Literature.txt", 
        "books/The History Of Ireland - Geoffrey Keating.txt", "books/The History of the Human Heart.txt", 
        "books/The Ingoldsby Legends.txt", "books/The Life of Beau Nash.txt", 
        "books/The Life of John Buncle by Thomas Amory.txt", "books/The Life of King Richard III.txt", 
        "books/The Life of Pico della Mirandola.txt", "books/The Martyrdom of Man.txt", 
        "books/The Masterpiece of Aristotle.txt", "books/The Memoirs of Count Boruwlaski.txt", 
        "books/The Metamorphosis of Ajax.txt", "books/The Newgate Calendar - Supplement 3.txt", 
        "books/The Newgate Calendar Supplement 2.txt", "books/The Newgate Calendar Supplement.txt", 
        "books/The Newgate Calendar V 1.txt", "books/The Newgate Calendar V 2.txt", 
        "books/The Newgate Calendar V 3.txt", "books/The Newgate Calendar V 4.txt", 
        "books/The Newgate Calendar V 5.txt", "books/The Newgate Calendar V 6.txt", 
        "books/The Poems of Ossian.txt", "books/The Poetical Works of John Skelton.txt", 
        "books/The Protestant Reformation.txt", "books/The Real Story of John Carteret Pilkington.txt", 
        "books/The Rowley Poems.txt", "books/The SIlver Fox.txt",
    };

    int numFiles = MAX_FILES;

    // Store words and word counts for each file
    char words[MAX_FILES][MAX_UNIQUE_WORDS][MAX_WORD_LENGTH];    // 1000 unique words per file
    int wordCounts[MAX_FILES][MAX_UNIQUE_WORDS];    // Counts for each unique word
    int totalWords[MAX_FILES];          // Total word count for each file
    int uniqueWords[MAX_FILES];         // Unique word count for each file

    // Initialize arrays
    for (int i = 0; i < MAX_FILES; i++) {
        totalWords[i] = 0;
        uniqueWords[i] = 0;
        for (int j = 0; j < MAX_UNIQUE_WORDS; j++) {
            wordCounts[i][j] = 0;
        }
    }

    // Process each file and compute word frequencies
    for (int i = 0; i < numFiles; ++i) {
        cout << "Processing: " << fileNames[i] << endl;
        uniqueWords[i] = computeWordFrequency(fileNames[i], words[i], wordCounts[i], &totalWords[i]);
        if (uniqueWords[i] < 0) {
            return 1;  // Error in processing files
        }
    }

    // Create a similarity matrix
    double similarityMatrix[MAX_FILES][MAX_FILES] = {0}; // Initialize the matrix

    // Calculate similarities between file pairs
    for (int i = 0; i < numFiles; ++i) {
        for (int j = i; j < numFiles; ++j) {
            similarityMatrix[i][j] = calculateSimilarity(words[i], wordCounts[i], 
                                                          totalWords[i], uniqueWords[i], 
                                                          words[j], wordCounts[j], 
                                                          totalWords[j], uniqueWords[j]);
            similarityMatrix[j][i] = similarityMatrix[i][j];  // Symmetric
        }
    }

    // Display similarities in the specified format
    for (int i = 0; i < numFiles; ++i) {
        // Extract the filename without "books/"
        const char* fileNameWithoutPath = strrchr(fileNames[i], '/') + 1; // Get the last part after the '/'
        
        cout << fileNameWithoutPath << " : ["; // Start displaying similarity for the current book

        for (int j = 0; j < numFiles; ++j) {
            if (i != j) { // Avoid showing similarity to itself
                cout << " " << strrchr(fileNames[j], '/') + 1 << " : " << similarityMatrix[i][j] << ","; // Show other book names and their similarity values
            }
        }

        // Remove the last comma and close the brackets
        cout << "\b ]\n\n"; // Erase the last comma and close the bracket

        // Leave two lines of space
        cout << endl; 
    }

    return 0;
}
