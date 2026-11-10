#include<iostream>
#include<vector>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
private:
vector<int> table;

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

public:
HashTable() {
    table.resize(TABLE_SIZE, -1);// menginisialisasi tabel hash dengan ukuran TABLE_SIZE
}

void insert(int key) {
    int index = hashFunction(key);// menghitung index
    
while (table[index] != -1) { // jika index sudah terisi, lakukan probing linear
        index = (index + 1) % TABLE_SIZE; // pindah ke index berikutnya
    }
    table[index] = key; // simpan key di index yang kosong
}

void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << " " << table[i] << endl;
        
    }
}

};

int main() {
    HashTable ht;

    ht.insert(23);
    ht.insert(43);
    ht.insert(13);
    ht.insert(35);

    ht.display();

    return 0;
}