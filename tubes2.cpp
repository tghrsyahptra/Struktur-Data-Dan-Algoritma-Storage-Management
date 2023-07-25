#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <conio.h>
#include <fstream>
#include <cstdlib>
using namespace std;

// Deklarasi Struct Node
struct InventoryBarang
{
  string nama;
  string kode;
  string kategori;
  int stok;
  int harga;
  InventoryBarang *next; // Pointer untuk menghubungkan node selanjutnya dalam linked list
};

struct BarangKeluar
{
  string nama;
  string kode;
  string kategori;
  int stok;
  int harga;
  BarangKeluar *next; // Pointer untuk menghubungkan node selanjutnya dalam linked list (digunakan dalam queue)
};

BarangKeluar *front = NULL; // Pointer yang menunjuk ke depan (front) dari queue
BarangKeluar *back = NULL;  // Pointer yang menunjuk ke belakang (back) dari queue

vector<InventoryBarang> gudang; // Vector untuk menyimpan data barang dalam gudang

// Deklarasi Node
InventoryBarang *head, *tail, *baru, *bantu, *hapus;

// Inisialisasi Node
void init()
{
  head = NULL; // Inisialisasi head linked list menjadi NULL
  tail = NULL; // Inisialisasi tail linked list menjadi NULL
}

// Buat Node Baru
void buatNode(string nama, string kode, string kategori, int stok, int harga)
{
  baru = new InventoryBarang; // Membuat node baru dalam bentuk pointer baru
  baru->nama = nama;          // Mengisi data nama pada node baru
  baru->kode = kode;          // Mengisi data kode pada node baru
  baru->kategori = kategori;  // Mengisi data kategori pada node baru
  baru->stok = stok;          // Mengisi data stok pada node baru
  baru->harga = harga;        // Mengisi data harga pada node baru
  baru->next = NULL;          // Menginisialisasi pointer next pada node baru menjadi NULL
}

// Pengecekan apakah linked list kosong atau tidak
bool isEmpty()
{
  if (head == NULL) // Jika head NULL, berarti linked list kosong
    return true;
  else
    return false; // Jika head bukan NULL, berarti linked list tidak kosong
}

// Hitung Jumlah Node dalam Linked List
int hitungList()
{
  InventoryBarang *hitung;
  hitung = head;         // Inisialisasi pointer hitung ke head linked list
  int jumlah = 0;        // Inisialisasi jumlah node menjadi 0
  while (hitung != NULL) // Selama pointer hitung tidak NULL, artinya masih ada node dalam linked list
  {
    jumlah++;              // Tambahkan jumlah node
    hitung = hitung->next; // Geser pointer hitung ke node selanjutnya
  }
  return jumlah; // Kembalikan jumlah node dalam linked list
}

// Tambah Node pada Depan Linked List (Insert Barang)
void insertBarang(string nama, string kode, string kategori, int stok, int harga)
{
  // Buat Node baru dengan data yang diberikan
  buatNode(nama, kode, kategori, stok, harga);

  // Cek apakah linked list kosong
  if (isEmpty() == true)
  {
    head = tail = baru; // Jika kosong, head dan tail menunjuk ke node baru
    tail->next = NULL;  // Tail diarahkan ke NULL karena node baru adalah satu-satunya node dalam linked list
  }
  else
  {
    baru->next = head; // Jika tidak kosong, node baru akan menjadi head baru, maka node baru akan mengarahkan ke head yang sebelumnya
    head = baru;       // Head digeser ke node baru karena node baru adalah node terdepan dalam linked list
  }

  // Simpan node baru ke dalam vector gudang
  gudang.push_back(*baru);

  cout << "Data " << baru->nama << " berhasil diinput!" << endl; // Tampilkan pesan bahwa data berhasil ditambahkan
}

// Hapus Node pada Tengah Linked List (Hapus Barang)
void hapusBarang(int posisi)
{
  if (isEmpty())
  {
    cout << "List masih kosong!" << endl;
    return;
  }

  if (posisi < 1 || posisi > hitungList())
  {
    cout << "Posisi di luar jangkauan" << endl;
    return;
  }

  if (posisi == 1)
  {
    hapus = head;                                                   // Simpan node yang akan dihapus dalam pointer hapus
    head = head->next;                                              // Geser head ke node selanjutnya
    hapus->next = nullptr;                                          // Menghapus koneksi node pertama dengan node selanjutnya
    cout << "Data " << hapus->nama << " berhasil dihapus!" << endl; // Tampilkan pesan bahwa data berhasil dihapus
    delete hapus;                                                   // Hapus node yang telah disimpan dalam pointer hapus

    if (isEmpty()) // Jika list kosong setelah menghapus node pertama
    {
      tail = nullptr; // Atur tail menjadi NULL
    }
  }
  else
  {
    InventoryBarang *bantu2 = nullptr; // Pointer bantu2 untuk menyimpan node sebelum node yang akan dihapus
    bantu = head;                      // Inisialisasi pointer bantu ke head linked list
    int nomor = 1;

    while (nomor < posisi) // Cari node yang akan dihapus berdasarkan posisinya
    {
      bantu2 = bantu;      // Simpan node sebelum node yang akan dihapus dalam pointer bantu2
      bantu = bantu->next; // Geser bantu ke node selanjutnya
      nomor++;
    }

    hapus = bantu;                                                  // Simpan node yang akan dihapus dalam pointer hapus
    bantu2->next = bantu->next;                                     // Hubungkan node sebelum node yang akan dihapus dengan node setelahnya
    hapus->next = nullptr;                                          // Menghapus koneksi node yang akan dihapus dengan node selanjutnya
    cout << "Data " << hapus->nama << " berhasil dihapus!" << endl; // Tampilkan pesan bahwa data berhasil dihapus
    delete hapus;                                                   // Hapus node yang telah disimpan dalam pointer hapus

    if (bantu2->next == nullptr) // Jika node yang dihapus adalah node terakhir
    {
      tail = bantu2; // Atur tail menjadi node sebelum node yang dihapus
    }
  }
}

// Ubah Data Barang
void ubahBarang(string nama, string kode, string kategori, int stok, int harga, int posisi)
{
  if (isEmpty() == 0)
  {
    if (posisi < 1 || posisi > hitungList())
    {
      cout << "Posisi di luar jangkauan" << endl;
    }
    else
    {
      bantu = head; // Inisialisasi pointer bantu ke head linked list
      int nomor = 1;

      while (nomor < posisi) // Cari node yang akan diubah berdasarkan posisinya
      {
        bantu = bantu->next; // Geser bantu ke node selanjutnya
        nomor++;
      }

      // Ubah data-data pada node yang ditemukan sesuai dengan data yang diberikan
      cout << "Data " << bantu->nama << " telah diganti dengan data";
      bantu->nama = nama;
      bantu->kode = kode;
      bantu->kategori = kategori;
      bantu->stok = stok;
      bantu->harga = harga;
      cout << bantu->nama << "!" << endl; // Tampilkan pesan bahwa data berhasil diubah
    }
  }
  else
  {
    cout << "List masih kosong!" << endl;
  }
}

// Hapus Semua Barang dalam Linked List
void clearList()
{
  bantu = head;         // Inisialisasi pointer bantu ke head linked list
  while (bantu != NULL) // Selama bantu tidak NULL (masih ada node dalam linked list)
  {
    hapus = bantu;       // Simpan node yang akan dihapus dalam pointer hapus
    bantu = bantu->next; // Geser bantu ke node selanjutnya
    delete hapus;        // Hapus node yang telah disimpan dalam pointer hapus
  }
  head = tail = NULL;                       // Set head dan tail linked list menjadi NULL (kosong)
  cout << "List berhasil dihapus!" << endl; // Tampilkan pesan bahwa seluruh data berhasil dihapus
}

// Pencarian Barang dengan Binary Search
void binarySearch(vector<InventoryBarang> &data, string target)
{
  int low = 0;
  int high = data.size() - 1;
  bool found = false;

  if (data[low].nama == target) // Cek apakah elemen pertama adalah target
  {
    found = true;
    cout << "Barang ditemukan: " << endl;
    cout << "Nama Barang: " << data[low].nama << endl;
    cout << "Kode Barang: " << data[low].kode << endl;
    cout << "Stok Barang: " << data[low].stok << endl;
    cout << "Harga Barang: " << data[low].harga << endl;
    cout << "Kategori Barang: " << data[low].kategori << endl;
  }
  else
  {
    while (low <= high) // Melakukan binary search
    {
      int mid = (low + high) / 2;   // Cari nilai tengah dari rentang data
      if (data[mid].nama == target) // Jika target ditemukan pada nilai tengah
      {
        found = true;
        cout << "Barang ditemukan: " << endl;
        cout << "Nama Barang: " << data[mid].nama << endl;
        cout << "Kode Barang: " << data[mid].kode << endl;
        cout << "Stok Barang: " << data[mid].stok << endl;
        cout << "Harga Barang: " << data[mid].harga << endl;
        cout << "Kategori Barang: " << data[mid].kategori << endl;
        break;
      }
      else if (data[mid].nama < target) // Jika target berada di sebelah kanan nilai tengah
      {
        low = mid + 1; // Batasi rentang pencarian ke sebelah kanan nilai tengah
      }
      else // Jika target berada di sebelah kiri nilai tengah
      {
        high = mid - 1; // Batasi rentang pencarian ke sebelah kiri nilai tengah
      }
    }
  }

  if (!found)
  {
    cout << "Barang tidak ditemukan." << endl; // Jika target tidak ditemukan
  }
}

// Pencarian Barang berdasarkan Kategori
void cariBarang()
{
  unordered_map<string, string> hashTable; // Membuat hashtable untuk menyimpan kategori dan nama barang
  string kategori;
  cout << "Masukkan Kategori Barang yang ingin dicari: ";
  getline(cin >> ws, kategori);

  bool found = false;
  for (const InventoryBarang &b : gudang)
  {
    hashTable[b.nama] = b.kategori; // Menyimpan data nama barang sebagai key dan kategori sebagai value dalam hashtable
  }

  cout << "Barang ditemukan: " << endl;
  for (const auto &item : hashTable)
  {
    if (item.second == kategori) // Jika kategori pada item sama dengan kategori yang dicari
    {
      found = true;
      cout << "Nama Barang: " << item.first << endl;            // Menampilkan nama barang
      cout << "Kode Barang: " << hashTable[item.first] << endl; // Menampilkan kategori barang yang sesuai
      cout << "Kategori Barang: " << item.second << endl;
      cout << "---------------------" << endl;
    }
  }

  if (!found)
  {
    cout << "Barang dengan kategori " << kategori << " tidak ditemukan." << endl; // Jika tidak ada barang dengan kategori yang dicari
  }
}

// Tampilkan Seluruh Data Barang dalam Linked List
void tampil()
{
  bantu = head;           // Inisialisasi pointer bantu ke head linked list
  if (isEmpty() == false) // Jika linked list tidak kosong
  {
    cout << "\nData Barang" << endl;
    cout << "==================================================\n";
    cout << left << setw(12) << "Nama" << setw(8) << "Kode" << setw(10) << "Stok" << setw(10) << "Harga" << setw(10) << "Kategori" << endl;
    cout << "==================================================\n";
    while (bantu != NULL) // Selama masih ada node dalam linked list
    {
      cout << left << setw(12) << bantu->nama << setw(8) << bantu->kode << setw(10) << bantu->stok << setw(10) << bantu->harga << setw(10) << bantu->kategori << endl;
      bantu = bantu->next; // Geser bantu ke node selanjutnya
    }
    cout << endl;
  }
  else
  {
    cout << "List masih kosong!" << endl; // Jika linked list kosong
  }
}

// Input Nama, Kode, dan Kategori Barang
string inputNama;
string inputKode;
string inputKategori;
int inputStok;
int inputHarga;
void inputList()
{
  cout << "Masukkan Nama Barang : ";
  getline(cin >> ws, inputNama);
  cout << "Masukkan Kode Barang : ";
  getline(cin >> ws, inputKode);
  cout << "Masukkan Stok Barang : ";
  cin >> inputStok;
  cout << "Masukkan Harga Barang : ";
  cin >> inputHarga;
  cout << "Masukkan Kategori Barang : ";
  getline(cin >> ws, inputKategori);
}

// Queue

// Cek apakah queue kosong
bool kosong()
{
  return front == NULL; // Jika front NULL, berarti queue kosong
}

// Pencarian Barang berdasarkan Kode dan Pengurangan Stok (digunakan dalam fungsi barangKeluar)
void searchByKode(vector<InventoryBarang> &data, string target, int qty)
{
  bool found = false;

  for (const InventoryBarang &item : data)
  {
    if (item.kode == target) // Jika kode barang pada data sama dengan kode barang yang dicari
    {
      found = true;
      bantu = head; // Inisialisasi pointer bantu ke head linked list

      while (bantu != nullptr) // Cari node yang sesuai dengan kode barang yang dicari
      {
        if (bantu->kode == target) // Jika kode barang pada node sama dengan kode barang yang dicari
        {
          bantu->stok -= qty; // Kurangi stok barang sesuai dengan jumlah barang yang keluar
          break;
        }
        bantu = bantu->next; // Geser bantu ke node selanjutnya
      }

      // Buat node baru untuk data barang yang keluar dan tambahkan ke dalam queue (BarangKeluar)
      BarangKeluar *newNode = new BarangKeluar;
      newNode->nama = item.nama;
      newNode->kode = item.kode;
      newNode->kategori = item.kategori;
      newNode->stok = qty;
      newNode->harga = item.harga;

      if (kosong()) // Jika queue kosong
      {
        front = newNode;
        back = newNode;
      }
      else // Jika queue tidak kosong
      {
        back->next = newNode;
        back = newNode;
      }

      cout << "Barang dengan kode " << target << " berhasil keluar" << endl; // Tampilkan pesan bahwa barang berhasil keluar
      break;
    }
  }

  if (!found)
  {
    cout << "Kode Barang tidak ditemukan." << endl; // Jika kode barang tidak ditemukan
  }
}

// Tampilkan Seluruh Data Barang yang Telah Keluar dari Gudang
void tampilBarangKeluar()
{
  if (kosong()) // Jika queue kosong
  {
    cout << "Barang Keluar Kosong" << endl; // Tampilkan pesan bahwa queue barang keluar kosong
  }
  else
  {
    BarangKeluar *temp = front; // Inisialisasi pointer temp ke front queue
    int index = 1;
    cout << "\n\nData Barang Keluar" << endl;
    cout << "==================================================\n";
    cout << left << setw(12) << "Nama" << setw(8) << "Kode" << setw(10) << "Stok" << setw(10) << "Harga" << setw(10) << "Kategori" << endl;
    cout << "==================================================\n";
    while (temp != NULL) // Selama masih ada node dalam queue barang keluar
    {
      cout << left << setw(12) << temp->nama << setw(8) << temp->kode << setw(10) << temp->stok << setw(10) << temp->harga << setw(10) << temp->kategori << endl;
      temp = temp->next; // Geser temp ke node selanjutnya
      index++;
    }
    cout << endl;
  }
}

// Fungsi untuk mengeluarkan barang dari gudang
void barangKeluar()
{
  string kode;
  int stok;
  cout << endl
       << endl;
  int j, qty;
  tampil();

  cout << "\n\n=========================== Barang Keluar ============================" << endl;
  cout << "----------------------------------------------------------------------\n";
  cout << "Jumlah Barang Keluar :";
  cin >> j;
  cout << " " << endl;

  for (int i = 0; i < j; i++)
  {
    cout << "Masukkan Kode Barang " << i + 1 << " : ";
    getline(cin >> ws, kode);
    cout << "Masukkan Jumlah Barang : ";
    cin >> qty;
    searchByKode(gudang, kode, qty); // Panggil fungsi searchByKode untuk mencari barang dan mengurangi stoknya

    cout << " " << endl;
  }
}

// Fungsi untuk membuat laporan data barang ke dalam file CSV
void laporanBarang()
{
  ofstream myFile;

  myFile.open("laporan.csv"); // Buka file "laporan.csv" untuk dituliskan

  bantu = head;           // Inisialisasi pointer bantu ke head linked list
  if (isEmpty() == false) // Jika linked list tidak kosong
  {
    myFile << "Nama,"
           << "Kode,"
           << "Stok,"
           << "Harga,"
           << "Kategori" << endl;
    while (bantu != NULL) // Selama masih ada node dalam linked list
    {
      // Tuliskan data barang ke dalam file CSV
      myFile << bantu->nama << "," << bantu->kode << "," << bantu->stok << "," << bantu->harga << "," << bantu->kategori << endl;
      bantu = bantu->next; // Geser bantu ke node selanjutnya
    }
    myFile << endl;

    cout << "Berhasil mengexport data barang"; // Tampilkan pesan bahwa data berhasil diekspor
  }
  else
  {
    myFile << "Barang masih kosong" << endl; // Jika linked list kosong, tuliskan pesan bahwa data masih kosong pada file CSV
  }
}

int main()
{
  int pilihan;
  int posisi;

  init();
  do
  {
    system("cls");
    cout << "======================================" << endl;
    cout << " PROGRAM INVENTORY BARANG" << endl;
    cout << "======================================" << endl;
    string menuOptions[] = {
        "1. Tambah Barang",
        "2. Hapus Barang",
        "3. Ubah Barang",
        "4. Cari Barang (Binary Search)",
        "5. Cari Barang (Menampilkan Berdasarkan Kategori)",
        "6. Tampil Barang",
        "7. Hapus Semua Barang",
        "8. Barang Keluar",
        "9. Tampil Barang Keluar",
        "10. Export Excel (Data Barang)",
        "11. Exit"};

    int numMenuOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    // Menampilkan daftar menu m9enggunakan perulangan for
    for (int i = 0; i < numMenuOptions; i++)
    {
      cout << menuOptions[i] << endl;
    }

    cout << " Pilihan : ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
      inputList();
      insertBarang(inputNama, inputKode, inputKategori, inputStok, inputHarga);
      break;
    case 2:
      cout << "Masukkan posisi data yang akan dihapus : ";
      cin >> posisi;
      hapusBarang(posisi);
      break;
    case 3:
      cout << "Masukkan posisi data yang akan diubah : ";
      cin >> posisi;
      inputList();
      ubahBarang(inputNama, inputKode, inputKategori, inputStok, inputHarga, posisi);
      break;
    case 4:
      cout << "Masukkan nama barang yang ingin dicari: ";
      getline(cin >> ws, inputNama);
      binarySearch(gudang, inputNama);
      break;
    case 5:
      cariBarang();
      break;
    case 6:
      tampil();
      break;
    case 7:
      clearList();
      break;
    case 8:
      barangKeluar();
      break;
    case 9:
      tampilBarangKeluar();
      break;
    case 10:
      laporanBarang();
      break;
    case 11:
      exit(0);
      break;
    default:
      cout << "Pilihan tidak valid!" << endl;
      break;
    }
    getch();
  } while (true);
  return 0;
}