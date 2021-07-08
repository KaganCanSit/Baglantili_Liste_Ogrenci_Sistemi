#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;

struct ders {
	char derskodu[10];
	char dersadi[50];
	ders* sonraki;
};
struct ogrenci {
	char ogrno[15];
	char ad[30];
	char soyad[30];
	ders* dersdugumu;
	ogrenci* sonraki;
};

//Struct Yardımı İle Kullanılacak Fonksiyon Ve İşaretçiler İçin Yapı Kurulması
struct Liste
{
	ogrenci* bas = NULL;
	ogrenci* dugum_olustur(char*, char*, char*, char*, char*);
	void ekle(char*, char*, char*, char*, char*);
	void DosyaOku(string dosyadi);
	void ListeKur();
	void Listele();
	void DosyayaYaz();
	void DersSil();
	void OgrenciSil();
	void Ara();
	void NumarayaGoreAra();
	void SoyadaGoreAra();
	void KesisimBul();
};

Liste* list = new Liste();

//Fonksiyonların Bildirimleri
void MenuListe();
void Cikis();

//Ana Fonksiyon
int main(void)
{
	MenuListe();

	return 0;
}

//Giriş Ekranı Seçim ve İşlem Menüsü
void MenuListe()
{
	//Liste* list = new Liste();
	list->ListeKur();
yeniden:
	cout << "Arama Yapmak Icin: A" << endl;
	cout << "Ders Silmek Icin: D" << endl;
	cout << "Kesisim Bulmak Icin: K" << endl;
	cout << "Listeye Ekran Yazdirmak Icin: L" << endl;
	cout << "Ogrenci Silmek Icin: O" << endl;
	cout << "Dosyaya Yaz: Y" << endl;
	cout << "Cikis Icin: C" << endl;

	char secim;
	cout << "Yapmak Istediginiz Islemi Seciniz: " << endl;
	cin >> secim;
	switch (secim)
	{
	case 'A': case 'a':
		system("cls");
		list->Ara();
		cout << endl << "Isleminiz Tamamlandi. Yeniden Ana Menuye Donuyorsunuz.\n" << endl;
		goto yeniden;
		break;
	case 'D': case 'd':
		system("cls");
		list->DersSil();
		cout << endl << "Isleminiz Tamamlandi. Yeniden Ana Menuye Donuyorsunuz.\n" << endl;
		goto yeniden;
		break;
	case 'K': case 'k':
		system("cls");
		list->KesisimBul();
		cout << endl << "Isleminiz Tamamlandi. Yeniden Ana Menuye Donuyorsunuz.\n" << endl;
		goto yeniden;
		break;
	case 'L': case 'l':
		system("cls");
		cout << "\nLISTENIN GUNCEL DURUMU\n" << endl;
		list->Listele();
		cout << endl << "Isleminiz Tamamlandi. Yeniden Ana Menuye Donuyorsunuz.\n" << endl;
		goto yeniden;
		break;
	case 'O': case 'o':
		system("cls");
		list->OgrenciSil();
		cout << endl << "Isleminiz Tamamlandi. Yeniden Ana Menuye Donuyorsunuz.\n" << endl;
		goto yeniden;
		break;
	case 'Y': case 'y':
		system("cls");
		list->DosyayaYaz();
		cout << endl << "Isleminiz Tamamlandi. Yeniden Ana Menuye Donuyorsunuz.\n" << endl;
		goto yeniden;
		break;
	case 'C': case'c':
		system("cls");
		Cikis();
		break;
	default:
		cout << " \nYanlis Deger Girdiniz. ";
		Cikis();
	}
}

//Programdan Çıkış Fonksiyonu
void Cikis()
{
	cout << "Cikis Yapiliyor.";
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		Sleep(1000);
		cout << ".";
		Sleep(1000);
	}
	system("cls");
	exit(1);
}

//Listelerin İsimlerinin Tek Tek Parametre Olarak Gönderilerek Dosyalardan Verilerin Okunup Liste Kurulması
void Liste::ListeKur()
{
	DosyaOku("fiz101.txt");
	DosyaOku("mat101.txt");
	DosyaOku("eng101.txt");
}
void Liste::DosyaOku(string dosyaismi)
{
	ifstream dosyaOku(dosyaismi, ios::in);
	if (!dosyaOku)
	{
		cerr << "Dosya Acilamadi." << endl;
		exit(1);
	}
	char ogrNo[20], ad[30], soyad[30], dersKodu[20], dersAd[20];

	dosyaOku >> dersKodu >> dersAd;
	while (dosyaOku >> ogrNo >> ad >> soyad)
	{
		Liste::ekle(ogrNo, ad, soyad, dersKodu, dersAd);
	}
}

//Parametre Alarak Bağıntılı Liste İçin Yeni Düğüm Oluşturulması
ogrenci* Liste::dugum_olustur(char* ogrno, char* ad, char* soyad, char* derskodu, char* dersadi)
{
	ogrenci* yenidugum = new ogrenci();
	ders* yeniders = new ders();
	yenidugum->dersdugumu = yeniders;

	strcpy_s(yenidugum->ogrno, ogrno);
	strcpy_s(yenidugum->ad, ad);
	strcpy_s(yenidugum->soyad, soyad);
	strcpy_s(yeniders->derskodu, derskodu);
	strcpy_s(yeniders->dersadi, dersadi);

	yenidugum->sonraki = NULL;
	yeniders->sonraki = NULL;

	return yenidugum;
}

//Okunan Parametrelere Göre Başa, Araya Ekleme veya Aynı Öğrenci Numarasına Sahip Öğrencilerin Sadece Ders Düğümüne Eklenmesini Sağlama
void Liste::ekle(char* ogrno, char* ad, char* soyad, char* derskodu, char* dersadi)
{
	ogrenci* tara, * arka, * yenikisi;
	ders* yeniders;
	arka = NULL;
	tara = bas;
	if (bas == NULL)
	{
		bas = dugum_olustur(ogrno, ad, soyad, derskodu, dersadi);
		return;
	}
	if (tara && (strcmp(ogrno, tara->ogrno) < 0))
	{
		yenikisi = dugum_olustur(ogrno, ad, soyad, derskodu, dersadi);
		yenikisi->sonraki = bas;
		bas = yenikisi;
		return;
	}
	while (tara && (strcmp(ogrno, tara->ogrno) > 0))
	{
		arka = tara;
		tara = tara->sonraki;
	}
	if (tara && strcmp(ogrno, tara->ogrno) == 0)	//Bu öğrenci numarası daha önce eklenmiş ise **
	{
		yeniders = new ders;	//Sadece tel noyu ekle
		yeniders->sonraki = tara->dersdugumu;
		tara->dersdugumu = yeniders;
		strcpy_s(yeniders->derskodu, derskodu);
		strcpy_s(yeniders->dersadi, dersadi);

	}
	else
	{
		yenikisi = dugum_olustur(ogrno, ad, soyad, derskodu, dersadi);
		if (tara)
		{
			yenikisi->sonraki = tara;
			arka->sonraki = yenikisi;
			return;
		}
		else
		{
			arka->sonraki = yenikisi;
		}
	}
}

//Mevcut Bağıntı Listesinin Ekrana Yazdırılma Fonksiyonu
void Liste::Listele()
{
	ogrenci* bilgi;
	ders* baglanti;
	bilgi = bas;
	while (bilgi)
	{
		baglanti = bilgi->dersdugumu;
		cout << " " << bilgi->ogrno << " " << bilgi->ad << " " << bilgi->soyad;
		while (baglanti)
		{
			cout << " " << baglanti->derskodu << " " << baglanti->dersadi;
			baglanti = baglanti->sonraki;
		}
		cout << endl;
		bilgi = bilgi->sonraki;
	}
}

//Mevcut Listenin ".txt" Dosyasına Çevrilerek Çıktı Olarak Yadırılması
void Liste::DosyayaYaz()
{

	struct Dosya_Kayit
	{
		char ogrNo[20], ad[30], soyad[30], dersKodu[20], dersAd[20];
	};

	ogrenci* bilgi;
	ders* baglanti;
	bilgi = bas;

	ofstream dosyayaYaz("tumliste.txt");
	while (bilgi)
	{
		baglanti = bilgi->dersdugumu;
		dosyayaYaz << bilgi->ogrno << " " << bilgi->ad << " " << bilgi->soyad;
		while (baglanti)
		{
			dosyayaYaz << " " << baglanti->derskodu << " " << baglanti->dersadi;
			baglanti = baglanti->sonraki;
		}
		dosyayaYaz << endl;
		bilgi = bilgi->sonraki;
	}
	dosyayaYaz.close();
}

//Ogrencinin Numarasını Karşılaştırarak Bulduktan Sonra Ders Düğümlerinin Bulunduğu Konuma Göre Baş-Orta-Son Ayırt Ederek İşlemini Gerçekleştiren Fonksiyon
void Liste::DersSil()
{
	char silogrno[20], sildersKod[20];
	cout << "Dersini Silmek Istediginiz Ogrencinin No'sunu Giriniz: " << endl;
	cin >> silogrno;
	cout << "Ogrencinin Hangi Dersini Silmek Istiyorsaniz Ders Kodunu Giriniz(MAT101 - ENG101 - FIZ101): " << endl;
	cin >> sildersKod;

	struct Degiskenler
	{
		char ogrNo[20], ad[30], soyad[30], dersKodu[20], dersAd[20];
	};

	ogrenci* bilgi;
	ders* baglanti;
	ders* gecici;
	gecici = NULL;
	bilgi = bas;

	while (bilgi)
	{
		baglanti = bilgi->dersdugumu;
		if (strcmp(bilgi->ogrno, silogrno) == 0)
		{
			while (baglanti)
			{
				if (strcmp(baglanti->derskodu, sildersKod) == 0)
				{
					if (gecici == NULL && baglanti->sonraki == NULL)
					{
						cout << "Ogrenci En Az Bir Derse Kayitli Olmalidir. Silinemez" << endl;
					}
					else if (baglanti->sonraki == NULL)
					{
						gecici->sonraki = NULL;
					}
					else
					{
						strcpy_s(baglanti->derskodu, baglanti->sonraki->derskodu);
						strcpy_s(baglanti->dersadi, baglanti->sonraki->dersadi);

						baglanti->sonraki = baglanti->sonraki->sonraki;
					}
				}
				gecici = baglanti;
				baglanti = baglanti->sonraki;
			}
		}
		bilgi = bilgi->sonraki;
	}
}

//Öğrencinin Bulunduğu Konuma Göre(Liste Başı - Sonu - Ortası) Silme İşlemini Gerçekleştiren Fonksiyon
void Liste::OgrenciSil()
{
	char silogrno[20];
	cout << "Silmek Istediginiz Ogrencinin No'sunu Giriniz: " << endl;
	cin >> silogrno;

	ogrenci* bilgi;
	ogrenci* gecici;
	gecici = NULL;
	bilgi = bas;
	while (bilgi)
	{
		if (strcmp(bilgi->ogrno, silogrno) == 0)
		{
			if (bilgi->sonraki == NULL)
			{
				gecici->sonraki = NULL;
			}
			else if (strcmp(silogrno, bas->ogrno) == 0)
			{
				bas = bas->sonraki;
			}
			else
			{
				gecici->sonraki = bilgi->sonraki;
			}
		}
		gecici = bilgi;
		bilgi = bilgi->sonraki;
	}
}

//Arama Yapamak İçin Numara Veya Soyad Ayrımının Use Case İle Yapılması. Bu Karara Göre Gerekli Fonksiyonlara Yönlendirilmesi
void Liste::Ara()
{
	char secim;
	cout << "Nasil Arama Yapmak Istersiniz?" << endl;
	cout << "Numaraya Gore Arama Yapmak Icin -> N, Soyadina Gore Arama Yapmak Icin -> S Giriniz." << endl;
	cin >> secim;
	switch (secim)
	{
	case 'N': case 'n':
		list->NumarayaGoreAra();
		break;
	case 'S': case 's':
		list->SoyadaGoreAra();
		break;
	default:
		cout << " \nYanlis Deger Girdiniz.";
		Cikis();
	}
}

//Numaraya Göre Bağıntılı Listede Arama Yapan Ve Aranan Öğrencinin Bilgilerini Yazdıran Fonksiyon
void Liste::NumarayaGoreAra()
{
	char araogrno[20];
	cout << "Aradiginiz ogrencinin numarasini giriniz: " << endl;
	cin >> araogrno;

	ogrenci* bilgi;
	ders* baglanti;
	bilgi = bas;
	while (bilgi)
	{
		baglanti = bilgi->dersdugumu;
		if (strcmp(bilgi->ogrno, araogrno) == 0)
		{
			cout << "\n\nAradiginiz Ogrencinin Bilgileri: " << endl;
			cout << bilgi->ogrno << " " << bilgi->ad << " " << bilgi->soyad << endl;
			cout << "Ogrencinin Su An Aldigi Dersler: " << endl;
			while (baglanti)
			{
				cout << baglanti->derskodu << " " << baglanti->dersadi << " ";
				baglanti = baglanti->sonraki;
			}
			cout << endl;
			break;
		}
		bilgi = bilgi->sonraki;
	}
}
//Soyada Göre Bağıntılı Listede Arama Yapan Ve Aranan Öğrencinin Bilgilerini Yazdıran Fonksiyon
void Liste::SoyadaGoreAra()
{
	char araogrsoyad[30];
	cout << "Aradiginiz ogrencinin soyadini giriniz: " << endl;
	cout << "! Ingilizce Yazima Uygun ve Buyuk Harf Kullanarak Giriniz. Ornegin: KOSEOGLU" << endl;
	cin >> araogrsoyad;

	ogrenci* bilgi;
	ders* baglanti;
	bilgi = bas;
	while (bilgi)
	{
		baglanti = bilgi->dersdugumu;
		if (strcmp(bilgi->soyad, araogrsoyad) == 0)
		{
			cout << "\n\nAradiginiz Ogrencinin Bilgileri: " << endl;
			cout << bilgi->ogrno << " " << bilgi->ad << " " << bilgi->soyad << endl;
			cout << "Ogrencinin Su An Aldigi Dersler: " << endl;
			while (baglanti)
			{
				cout << baglanti->derskodu << " " << baglanti->dersadi << " ";
				baglanti = baglanti->sonraki;
			}
			cout << endl;
			break;
		}
		bilgi = bilgi->sonraki;
	}
}

/*
Fonksiyon Başında Bir Sayaç Tanımlıyoruz. Liste İçerisinde Bir Pointer İle Gezerken Geçiçi Bir Pointer İle Ders Düğümünün Başlangıç Kısmını Tutuyoruz.
İf Fonksiyonu İçerisinde Aradığımız Ders Bulunursa Sayacımızı Bir Arttırıyoruz. Sayacımız While Sonunda Eğer 2 ise Kesişim Olarak Dersleri Alan Bir Öğrenci Olduğunu Anlayıp Bilgilerini Yazıyoruz.
Aksi Halde Sayacımızı Sıfırlayıp Sonraki Öğrenciye Geçip Kontrol Etmeye Devam Ediyoruz.
*/
void Liste::KesisimBul()
{
	char kesisimders1[20], kesisimders2[20];
	cout << "Iki Dersi Ayni Anda  Alan Ogrencilerin Kesisimini Bulma" << endl;
	cout << "Ders Kodlarini (MAT101 - ENG101 - FIZ101) Yazimlarina Uygun Olarak Giriniz." << endl;
	cout << "Birinci Dersin Kodunu Giriniz:";
	cin >> kesisimders1;
	cout << "Ikinci Dersin Kodunu Giriniz:";
	cin >> kesisimders2;
	int kesisimsay = 0;

	ogrenci* bilgi;
	ders* baglanti;
	ders* gecici;
	bilgi = bas;
	while (bilgi)
	{
		baglanti = bilgi->dersdugumu;
		gecici = bilgi->dersdugumu;
		while (baglanti)
		{
			if (strcmp(baglanti->derskodu, kesisimders1) == 0 || strcmp(baglanti->derskodu, kesisimders2) == 0)
			{
				kesisimsay++;
			}
			baglanti = baglanti->sonraki;
		}
		if (kesisimsay == 2)
		{
			cout << bilgi->ogrno << " " << bilgi->ad << " " << bilgi->soyad;
			while (gecici)
			{
				cout << " " << gecici->derskodu << " " << gecici->dersadi;
				gecici = gecici->sonraki;
			}
			cout << endl;
		}
		else
		{
			kesisimsay = 0;
			bilgi = bilgi->sonraki;
		}
	}
}