#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
private:
    vector<pair<int, string>> table;
    vector<int> status; // 0 = kosong, 1 = terisi, 2 = dihapus

    int hash1(int key) {
        return key % TABLE_SIZE;
    }

    int hash2(int key) {
        return 7 - (key % 7);
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE, {-1, ""});
        status.resize(TABLE_SIZE, 0);
    }

    void insert(int key, string value) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;
        int deletedIndex = -1;

        while (true) {
            if (status[index] == 1 && table[index].first == key) {
                table[index].second = value;
                cout << "[INSERT] Key " << key << " diperbarui menjadi " << value << endl;
                return;
            }

            if (status[index] == 2 && deletedIndex == -1) {
                deletedIndex = index;
            }


            if (status[index] == 0) {
                int targetIndex = (deletedIndex != -1) ? deletedIndex : index;
                table[targetIndex] = make_pair(key, value);
                status[targetIndex] = 1;
                cout << "[INSERT] Berhasil menambahkan NIM: " << key << " (" << value << ")" << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        if (deletedIndex != -1) {
            table[deletedIndex] = make_pair(key, value);
            status[deletedIndex] = 1;
            cout << "[INSERT] Berhasil menambahkan NIM: " << key << " (" << value << ")" << endl;
        } else {
            cout << "[INSERT GAGAL] Tabel Hash Penuh!" << endl;
        }
    }

    void search(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        while (status[index] != 0) {
            if (status[index] == 1 && table[index].first == key) {
                cout << "[SEARCH] Data Ditemukan -> NIM: " << key << ", Nama: " << table[index].second << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        cout << "[SEARCH] Data NIM " << key << " tidak ditemukan." << endl;
    }

    void remove(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        while (status[index] != 0) {
            if (status[index] == 1 && table[index].first == key) {
                status[index] = 2; 
                cout << "[REMOVE] Data NIM " << key << " berhasil dihapus." << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        cout << "[REMOVE] Data NIM " << key << " tidak ditemukan." << endl;
    }

    void display() {
        cout << "\n============ ISI HASH TABLE =============" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index [" << i << "] : ";
            if (status[i] == 1) {
                cout << table[i].first << " - " << table[i].second;
            } else if (status[i] == 2) {
                cout << "[DELETED]";
            } else {
                cout << "[EMPTY]";
            }
            cout << endl;
        }
        cout << "============================================\n" << endl;
    }
};

int main() {
    HashTable ht;

    cout << "=== MENGISI DATA MAHASISWA ===" << endl;
    ht.insert(101, "Andi");
    ht.insert(202, "Budi");
    ht.insert(111, "Citra"); 
    ht.insert(305, "Dewi");

    
    ht.display(); 
 
    cout << "=== PENCARIAN DATA ===" << endl;
    ht.search(111);
    ht.search(999); // cari data yang tidak ada
    cout << endl;

    cout << "=== PENGHAPUSAN DATA ===" << endl;
    ht.remove(202);
    cout << endl;

    ht.display();

return 0;
}