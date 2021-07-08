# Bağlantılı Liste Öğrenci Sistemi

## 1. Ödev İsterleri
Bu ödevde birden fazla derse ait öğrenci listesini saklayacak çoklu bir bağlantılı liste yapısı kurmanız beklenmektedir. Programınız girdi dosyalarından bilgileri okuyarak, verileri aşağıda verilen yapıda tutmalıdır:

struct ogrenci{   </br>
  char ogrno[15]; </br>
  char ad[30] ;   </br>
  char soyad[30]; </br>
  ders *dersdugumu; </br>
  ogrenci *sonraki; </br>
};  </br>
struct ders{  </br>
  char derskodu[10];  </br>
  char dersadi[50]; </br>
  ders *sonraki;  </br>
}; </br>

3 adet girdi dosyası (mat101.txt, fiz101.txt, eng101.txt) verilmiştir. Her dosyanın başında dersin kodu ve adı yer almaktadır. Program 3 dosyanın birleşimini, 
ogrenci düğümlerinden oluşan çoklu listede tutmalıdır. Bir öğrenciye ilişkin ogrenci düğümü listede bir kez yer almalıdır. 
Ayrıca, her ogrenci düğümü, öğrencinin aldığı derslere ilişkin, ders düğümlerine bir işaretçi tutmalıdır.
Programda şu fonksiyonlar yer almalıdır;
* listeKur(): Girdi dosyalarının okunarak, çoklu bağlantılı liste yapısının oluşturulduğu fonksiyondur. Bağlantılı liste öğrenci numarası sırasına göre artan şekilde oluşturulmalıdır.
* dersSil(): Öğrenci numarasını ve silinmek istenen dersi kullanıcıdan alarak, öğrencinin ilgili dersteki kaydını siler.
* ogrenciSil(): Öğrenci numarasını kullanıcıdan alarak, öğrenciyi ve derslerini silme işlemini gerçekleştirir.
* listele(): Listenin son hali ekrana yazdırılır.
* ara():Kullanıcıya iki seçenek sunulur: -Numaraya göre arama, -Soyadına göre arama. Seçeneğe göre istenen arama işlemi gerçekleştirilir.
* kesisimBul(): Kullanıcıdan kesişiminin bulunması istenen iki ders kodu alınır. Bu iki dersi birlikte alan öğrenciler ekrana yazdırılır.
* dosyayaYaz(): Çıktı dosyasının oluşturulduğu fonksiyondur. Oluşturulan bağlantılı liste yapısı çıktı dosyasına yazdırılır. Örnek çıktı dosyası görüntüsü aşağıda verilmektedir.

## 2. Oluşturulan Programın Kabaca Alt Mantığı
İlk olarak bizden istenen bağlantılı liste yapısını tanımlamız gerekiyor. Bunun kısaca açıklaması şu şekilde kullanacağımız yapı bir çoklu liste yapısı. 
Öğrenci düğümleri öğrencilerin bilgilerini ayrıca kendilerinden bir sonraki öğrencinin adres bilgisini işaret edecektir. Ayrıca her öğrenci almış olduğu dersler için bir ders düğümü tutacaktır.
Bu ders düğümleri içerisinde ise dersin bilgisi ve öğrencinin almış olduğu bir sonraki ders düğümünün adresi bulunacaktır.

![Bağlantılı Liste Yapısı](https://user-images.githubusercontent.com/59123356/124971114-7bcd3f00-e031-11eb-9c2f-f0761dce81e3.JPG)

Bu yapı içerisinde bir adet baş işaretçisi öğrenci bağıntı listesinin başında bulunacak. Ekleme ve tarama işlemlerinde tuttuğu adres ile işlem yapmamızı sağlayacaktır. Aynı durum “Ders Düğüm Baş” içinde geçerlidir.

Düğümler içerisinde bulunan öğrenci bilgileri ve ders bilgileri struct yapısı yardımıyla soyutlanarak bir değişken tanımı oluşturuyoruz. Bu sayede her seferinde tek tek tanımlamaktansa struct tanımları içerisinde direk öğrenci değişkenini çağırarak tüm bilgileri işleyebiliyoruz.

Ardından kurmuş olduğumuz yapıya göre elimizdeki üç adet dosyayı okuyarak bağlantılı liste yapısını düğümlere atayarak yapıyı oluşturuyoruz. Kurmuş olduğumuz yapı içerisinde ayrıca fonksiyonel olarak listeye tarayarak ara, kesişimbul ve derssil donksiyonlarını oluşturuyoruz. Bu fonksiyonlar düğüm yapılarına uygun şekilde kurarak verimli bir biçimde gerçekliyoruz. Dosyayayaz fonksiyonu ile de bir txt dosyası içerisine listemizin yeni ve bütün halini yazdırıyoruz.
