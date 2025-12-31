# Algoritma Analizi ve Karmaşıklığı Proje Ödevi

Bu depo, Algoritma Analizi ve Karmaşıklığı dersi kapsamında verilen dönem projesi için hazırlanmıştır.  
Projede ders slaytlarında yer alan temel algoritmalar C++ dili kullanılarak uygulanmış, zaman karmaşıklıkları analiz edilmiş ve farklı yaklaşımlar karşılaştırılmıştır.

Kod yapısı tek bir algoritmaya odaklanmak yerine, tüm konuları modüler dosyalar halinde ele alacak şekilde tasarlanmıştır. Program çalıştırıldığında kullanıcıyı menü tabanlı bir arayüz karşılar ve her algoritma grubu ayrı ayrı test edilebilir.

---

## Kullanılan Teknolojiler ve Standartlar

Bu proje C++ dili ile geliştirilmiştir.  
C++11 ve üzeri standartlarla uyumludur.  
Zaman ölçümleri için `chrono` kütüphanesi kullanılmıştır.  
Tüm algoritmalar ders slaytlarındaki mantıklar temel alınarak yazılmıştır.

---

## Proje Dosya Yapısı

Proje çok dosyalı bir yapıdadır ve her algoritma grubu kendi kaynak dosyasında yer alır.

Main.cpp  
Programın giriş noktasıdır. Menü yapısını içerir ve ilgili demo fonksiyonlarını çağırır.

MaxSubsequenceProblem.cpp / maxsubseq.h  
Maximum Subsequence Problem için farklı zaman karmaşıklıklarına sahip çözümleri içerir.

RecursiveAlgorithms.cpp  
Rekürsif algoritmalar ve her algoritma için rekürsif çağrı sayılarının hesaplanmasını içerir.

SearchAlgorithms.cpp  
Lineer arama ve ikili arama algoritmalarını ve karşılaştırma sayılarını içerir.

SortAlgorithms.cpp  
Sıralama algoritmalarını ve çalışma süresi ölçümlerini içerir.

HeapStructures.cpp / heap.h  
Binary Heap veri yapısının min-heap ve max-heap uygulamalarını içerir.

GreedyAlgorithms.cpp / greedy.h  
Greedy yaklaşımıyla çözülen klasik problemleri içerir.

DynamicProgramming.cpp / dp.h  
Dinamik programlama problemlerini ve DP tablolarının gösterimini içerir.

ui.h  
Konsol çıktılarının daha düzenli ve okunabilir olması için kullanılan yardımcı fonksiyonları içerir.

---

## 1. Maximum Subsequence Problem

Bu problem A[0..N-1] dizisi için aşağıdaki dört farklı yaklaşımla çözülmüştür:

O(n³) brute force yaklaşımı  
O(n²) iyileştirilmiş brute force  
O(n log n) divide and conquer yaklaşımı  
O(n) Kadane algoritması  

Her yaklaşım için aynı giriş verisi kullanılmıştır.  
Çalışma süreleri mikro saniye cinsinden ölçülmüş ve karşılaştırılmıştır.  
Sonuçlar hem ekranda tablo halinde gösterilmiş hem de analiz için kullanılabilir durumdadır.

---

## 2. Rekürsif Algoritmalar

Bu bölümde aşağıdaki rekürsif problemler ele alınmıştır:

1’den N’e kadar sayıların toplamı  
Dizi elemanlarının toplamı  
aⁿ hesaplaması  
Fibonacci dizisi  
Tower of Hanoi  
Recursive Digit Sum  

Her algoritma için rekürsif çağrı sayısı hesaplanmış ve çıktı olarak gösterilmiştir.  
Bu sayede teorik karmaşıklık ile pratik davranış karşılaştırılabilmektedir.

---

## 3. Arama Algoritmaları

Bu bölümde temel arama algoritmaları uygulanmıştır.

İleri yönlü lineer arama  
Geri yönlü lineer arama  
İkili arama  

Her algoritma için yapılan karşılaştırma sayısı hesaplanmıştır.  
İkili arama öncesinde dizinin sıralı olması garanti altına alınmıştır.

---

## 4. Sıralama Algoritmaları

Aşağıdaki sıralama algoritmaları uygulanmış ve performansları ölçülmüştür:

Selection Sort  
Bubble Sort  
Insertion Sort  
Merge Sort  
Quick Sort (ilk pivot ve median of three)  
Heap Sort  
Counting Sort (satellite data)  
Radix Sort  
External Sorting  

Her algoritma için çalışma süresi `chrono` kullanılarak ölçülmüştür.  
n log n karmaşıklığındaki algoritmalar birden fazla tekrar edilerek minimum süre alınmıştır.

---

## 5. Heap Yapıları

Binary Heap veri yapısı hem min-heap hem max-heap olacak şekilde uygulanmıştır.

Desteklenen işlemler:

findMin  
insertKey  
deleteMin  
buildMinHeap  
buildMaxHeap  
decreaseKey  
increaseKey  
deleteKey  
Merge(H1, H2)  

Heap yapısı, indeks ve değerleri birlikte gösteren düzenli bir ASCII tablo formatında ekrana basılmaktadır.  
Bu sayede heap’in iç yapısı görsel olarak takip edilebilmektedir.

---

## 6. Greedy Algoritmalar

Bu bölümde greedy yaklaşımıyla çözülen klasik problemler yer almaktadır.

Aktivite zamanlama problemi  
İş zamanlama problemi  
Huffman kodlama (encode ve decode işlemleri)  

Her problem için seçilen adımlar ve sonuçlar açık şekilde ekrana yazdırılmaktadır.

---

## 7. Dinamik Programlama

Dinamik programlama bölümünde üç temel problem ele alınmıştır.

Bottom-Up Fibonacci çözümü  
Minimum Maliyet Yol Problemi (Top-Down)  
0-1 Sırt Çantası Problemi  

Her problem için dinamik programlama tablosu ekranda gösterilmektedir.  
Tablolar sade, hizalı ve göz yormayan bir ASCII formatında basılmaktadır.  
Amaç yalnızca sonucu göstermek değil, DP mantığını açıkça ortaya koymaktır.

---

## Programın Çalıştırılması

Proje bir C++ derleyicisi ile derlendikten sonra çalıştırıldığında kullanıcıyı menü tabanlı bir arayüz karşılar.  
Kullanıcı menüden istediği algoritma grubunu seçerek ilgili demoyu çalıştırabilir.

Her demo çalışması sonrasında sonuçlar ekranda düzenli bir formatta gösterilir.

---

## Genel Notlar

Bu proje yalnızca algoritmaların çalışmasını göstermek için değil,  
zaman karmaşıklığı, bellek kullanımı ve farklı yaklaşımların etkisini gözlemlemek amacıyla hazırlanmıştır.

Kod okunabilirliği ve çıktının anlaşılabilirliği özellikle ön planda tutulmuştur.

---

Hazırlayan  
İrem Kalaycı  
Algoritma Analizi ve Karmaşıklığı Dersi Projesi
