#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
    clock_t baslangic = clock(), bitis;
    vector <int> index;
    // str icinde harflerimizi boldugumuz durumlar var.(aa, ab, ba a, b gibi)
    // index icinde bunlarin aldigi sayisal karsiliklar var.
    vector <string>str;
    vector<int>encoding;

    ifstream dosyaOku("metin.txt");
    string satir = "";
    string s1 = "";
    if (dosyaOku.is_open())
    {

        while(getline(dosyaOku, satir))
        {
            s1 += satir;
        }

        dosyaOku.close();
    } // txt dosyamizdan textimizi okuyoruz.
    int i=0,ind=1,k;
    while(i<s1.length()) // textimiz icinde sonuna kadar geziniyoruz.
    {
        int durum=0;
        for(k=0; k<str.size(); k++)
        {
            string harfler;
            harfler+=s1.at(i);  // her harfi tek tek gezerek harfler stringine atiyoruz.
            if(str.at(k)==harfler)
            {
                durum=1;
            } // Eger ayni harfe vektorde tekrar rastladiysak durum degiskenini 1 yapiyoruz.
        }
        if(durum==0) // Durum degiskeni 0 iken textimizin indis degerini temp'e atiyoruz
        {
            string temp;
            temp+=s1.at(i);
            str.push_back(temp); // str vektorune temp'i ekliyoruz.
            index.push_back(ind); // indisi de ekleyip bir artiriyoruz.
            ind++;
        }
        i++;
    }
    // indis degeri verdigimiz harf ve hecelerimizin indislerini alfabeye gore siralamak icin stringimizi for ile geziyoruz indis
    // numaralandirmasini alfabeye gore yapiyoruz.
    for(i=0; i<str.size(); i++)
    {
        // Bubble Sort
        for(int j=0; j<str.size()-i-1; j++)
        {
            if(str.at(j)>str.at(j+1))
            {
                string temp=str.at(j);
                str.at(j)=str.at(j+1);
                str.at(j+1)=temp;
            }
        }
    }
    i=0;
    ind=str.size()+1;
    while(i<s1.length())
    {
        string temp;
        int durum=0,temp_index;
        for(k=0; k<index.size(); k++)
        {
            string harfler;
            harfler=s1.substr(i,str.at(k).length()); // Baslangic indeksi, Nereye kadar alacagi
            if(harfler==str.at(k))
            {
                durum=1;
                temp_index = k+1;
            }
        }
        // Eger string uzunlugumuz textimizin uzunlugundan kucukse indeksimizi encoding vektorune ekliyoruz.
        if(i+str.at(temp_index-1).length()<s1.length())
        {
            encoding.push_back(temp_index); // string harflere karsilik geldikleri sayisal degerleri ekliyoruz. metindeki harflerin sirasina gore
            temp+=str.at(temp_index-1);
            temp+=s1.at(i+str.at(temp_index-1).length());
            str.push_back(temp);
        }
        else if(i+str.at(temp_index-1).length()==s1.length()) //esitse sadece indeks ekliyoruz.
        {
            encoding.push_back(temp_index);
        }
        index.push_back(ind);
        ind++;
        i+=str.at(temp_index-1).length();
    }
    ofstream dosyaYaz("SikistirilmisMetin.txt");
    // str icinde harflerimizi boldugumuz durumlar var.(aa, ab, ba a, b gibi)
    // index icinde bunlarin aldigi sayisal karsiliklar var.
    cout<<"LZW KODLAMA KARSILIKLARI \n";
    for(i=0; i<str.size(); i++)
    {
        cout<<"\n "<<str.at(i)<<"\t "<<index.at(i);
    }

    // Sikistirdigimiz (indeksteki) degerler metindeki harflere gore siralanip encoding vektorunde tutuluyor.
    cout<<"\n\n -- SIKISTIRILMIS METIN : ";
    for(i=0; i<encoding.size(); i++)
    {
        dosyaYaz<<encoding.at(i); // harflerimizi ve sayýsal karþýlýklarý yazýyoruz.
        cout<<" "<<encoding.at(i);
    }
    cout<<"\n\n -- METIN : ";
    cout<<s1;
    dosyaYaz.close();
    bitis = clock();
    float calismasuresi = (float)(bitis - baslangic) / CLOCKS_PER_SEC;
    cout << "\n\n --> CALISMA SURESI  : " << calismasuresi << endl;
    return 0;
}
