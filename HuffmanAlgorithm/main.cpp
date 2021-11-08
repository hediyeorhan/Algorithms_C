#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <ctime>
#include <fstream>

using namespace std;

// Agac olusturmak icin bir struct olusturalım
typedef struct Agac
{
    char ch;
    int frekans;
    Agac *sol, *sag;
}A;

// Agacın durumuna gore yeni olusacak degeri yerlestirecegimiz yeri belirlememizi saglayan struct.
typedef struct AgacOlustur
{
    bool operator()(A* sol, A* sag)
    {
        // degerlerin oncelik sirasina göre true, false degerleri doner ve agac buna gore sekillenir.
        return sol->frekans > sag->frekans;
    }
};

// Agactan bir dugum olusturmak icin bir fonksiyon tanimlayalim ve fonksiyondan bu dugum donsun.
A* DugumOlustur(char ch, int frekans, A* sol, A* sag)
{
    A* root = new A();

    root->ch = ch;
    root->frekans = frekans;
    root->sol = sol;
    root->sag = sag;

    return root;
}

// txt dosyasından okudugumuz metni sikistirmamizi saglıyor.
void encode(A* root, string str,unordered_map<char, string> &huffman) // unordered_map : c++ sozluk yapisi
{
    if (root == nullptr)
        return;

    // agacin solu ve sagi null degilken, huffman'nin  indisine stringimizi atiyoruz.
    if (!root->sol && !root->sag)
    {
        huffman[root->ch] = str;
    }

    encode(root->sol, str + "0", huffman);
    encode(root->sag, str + "1", huffman);
}
// Huffman Agacini olusturur ve verilen metnin kodunu cozer.
void HuffmanAgacOlustur(string text)
{

    // karakterleri ve sikliklarini tutan map yapisi
    unordered_map<char, int> frekans;
    for (char ch: text)
    {
        frekans[ch]++; // ayni karakterden birden fazla varsa sikligini/frekansini artiriyoruz.
    }

    // degerlerimizi tutmak icin bir kuyruk yapisi olusturuyoruz.
    priority_queue<A*, vector<A*>, AgacOlustur> huffmanqueue;


    // auto pair : otomatik tipini ayarliyor.
    // frekans icinde foreach ile dolaniyoruz.
    for (auto pair: frekans)
    {   // kuyruga push ile dugumolusturdan donen dugumumuzun degerlerini ekliyoruz.
        huffmanqueue.push(DugumOlustur(pair.first, pair.second, nullptr, nullptr));
    }

    // kuyrukta birden fazla düðüm olana kadar doner.
    while (huffmanqueue.size() != 1)
    {

        A *sol = huffmanqueue.top(); // Dugumdeki en ustteki elemani sol'a at.
        huffmanqueue.pop(); // Dugumdeki en ustteki elemani dugumden cikar.
        A *sag = huffmanqueue.top(); // Dugumdeki en ustteki elemani sag'a at.
        huffmanqueue.pop();  // Dugumdeki en ustteki elemani dugumden cikar.

        // toplam frekanslari bir degere atadiktan sonra bu deger ile yeni bir dugum olusturup
        // kuyruga ekleyelim.
        int toplam = sol->frekans + sag->frekans;
        huffmanqueue.push(DugumOlustur('\0', toplam, sol, sag)); // frekansa gore yeni dugum olusutuyoruz ve kuyruga ekliyoruz.
    }


    A* root = huffmanqueue.top();  // Dugumdeki en ustteki elemani root'a at.


    unordered_map<char, string> huffman;
    encode(root, "", huffman);

    cout << "HUFFMAN KOD KARSILIKLARI :\n" << '\n';
    for (auto pair: huffman) // Map icinde dolasarak ilk degerini (key) ve ikinci degerini (value) yazdiriyoruz.
    {
        cout << pair.first << " " << pair.second << '\n';
    }

    cout << "\nMETIN :\n" << text << '\n';

    // Dosya islemleri
    string str = "";
    for (char ch: text)
    {
        str += huffman[ch];
    }

    cout << "\nSIFRELI METIN :\n" << str << '\n';

    ofstream dosyaYaz("SikistirilmisMetin.txt");
    dosyaYaz << str;
    dosyaYaz.close();

    int index = -1;

}

// Huffman coding algorithm
int main()
{
    clock_t baslangic = clock(), bitis;

    ifstream dosyaOku("metin.txt");
    string satir = "";
    string metin = "";
    if (dosyaOku.is_open())
    {

        while(getline(dosyaOku, satir))
        {
            metin += satir;
        }

        dosyaOku.close();
    }

    HuffmanAgacOlustur(metin);
    bitis = clock();
    float calismasuresi = (float)(bitis - baslangic) / CLOCKS_PER_SEC;
    cout << "\n\n --> Calisma Suresi  : " << calismasuresi << endl;

    return 0;
}
