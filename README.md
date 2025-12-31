# Algoritma Analizi ve Karmaşıklığı Proje Ödevi

Bu depo, Algoritma Analizi ve Karmaşıklığı dersi kapsamında verilen dönem projesi için hazırlanmıştır.  
Projede, ders slaytlarında yer alan temel algoritmalar C++ dili ile uygulanmış, zaman karmaşıklıkları analiz edilmiş ve farklı çözüm yaklaşımları karşılaştırılmıştır.

Program, menü tabanlı bir konsol arayüzü üzerinden çalışmakta olup her algoritma grubu bağımsız şekilde test edilebilmektedir.

---

## Geliştirme Ortamı ve Kullanılan Standartlar

| Özellik | Bilgi |
|------|------|
| Programlama Dili | C++ |
| Standart | C++11 ve üzeri |
| Zaman Ölçümü | chrono |
| Derleyici Uyumu | GCC / MSVC |

---

## Proje Dosya Yapısı

Proje çok dosyalı bir yapıda tasarlanmıştır. Her algoritma grubu ayrı bir kaynak dosyasında ele alınmıştır.

| Dosya | Açıklama |
|-----|---------|
| Main.cpp | Programın giriş noktası, menü sistemi |
| MaxSubsequenceProblem.cpp | Maximum Subsequence çözümleri |
| RecursiveAlgorithms.cpp | Rekürsif algoritmalar |
| SearchAlgorithms.cpp | Arama algoritmaları |
| SortAlgorithms.cpp | Sıralama algoritmaları |
| HeapStructures.cpp | Heap veri yapıları |
| GreedyAlgorithms.cpp | Greedy algoritmalar |
| DynamicProgramming.cpp | Dinamik programlama problemleri |
| ui.h | Konsol çıktısı yardımcıları |

---

## 1. Maximum Subsequence Problem

A[0..N-1] dizisi için maksimum ardışık alt dizi toplamı problemi dört farklı yaklaşımla çözülmüştür.

| Yaklaşım | Zaman Karmaşıklığı |
|-------|------------------|
| Brute Force | O(n³) |
| İyileştirilmiş Brute Force | O(n²) |
| Divide and Conquer | O(n log n) |
| Kadane Algoritması | O(n) |

Her yaklaşım için aynı giriş verisi kullanılmış ve çalışma süreleri mikro saniye cinsinden ölçülmüştür.

---

## 2. Rekürsif Algoritmalar

Bu bölümde temel rekürsif problemler ele alınmıştır.

| Problem | Açıklama |
|------|---------|
| 1 + 2 + … + N | Rekürsif toplam |
| Dizi Toplamı | Rekürsif dizi işlemi |
| aⁿ | Üstel hesaplama |
| Fibonacci | Rekürsif Fibonacci |
| Tower of Hanoi | Disk taşıma problemi |
| Digit Sum | Rekürsif basamak toplamı |

Her algoritma için rekürsif çağrı sayısı hesaplanmış ve çıktı olarak gösterilmiştir.

---

## 3. Arama Algoritmaları

Aşağıdaki arama algoritmaları uygulanmış ve karşılaştırma sayıları hesaplanmıştır.

| Algoritma |
|---------|
| İleri Yönlü Lineer Arama |
| Geri Yönlü Lineer Arama |
| İkili Arama |

İkili arama öncesinde dizinin sıralı olması garanti altına alınmıştır.

---

## 4. Sıralama Algoritmaları

Sıralama algoritmaları için çalışma süresi ölçümü zorunlu tutulmuştur.

| Algoritma |
|---------|
| Selection Sort |
| Bubble Sort |
| Insertion Sort |
| Merge Sort |
| Quick Sort |
| Heap Sort |
| Counting Sort |
| Radix Sort |
| External Sorting |

Tüm ölçümler `chrono` kütüphanesi kullanılarak yapılmıştır.

---

## 5. Heap Yapıları

Binary Heap veri yapısı hem min-heap hem max-heap olarak uygulanmıştır.

| Desteklenen İşlemler |
|---------------------|
| findMin |
| insertKey |
| deleteMin |
| buildMinHeap |
| buildMaxHeap |
| decreaseKey |
| increaseKey |
| deleteKey |
| Merge(H1, H2) |

Heap yapıları konsolda indeks ve değerleri içeren düzenli ASCII tablolarla gösterilmektedir.

---

## 6. Greedy Algoritmalar

Greedy yaklaşımıyla çözülen klasik problemler uygulanmıştır.

| Problem |
|-------|
| Aktivite Zamanlama |
| İş Zamanlama |
| Huffman Kodlama |

Her problem için seçilen adımlar ve sonuçlar açık şekilde gösterilmektedir.

---

## 7. Dinamik Programlama

Dinamik programlama bölümünde aşağıdaki problemler ele alınmıştır.

| Problem | Yaklaşım |
|-------|---------|
| Fibonacci | Bottom-Up |
| Minimum Maliyet Yol Problemi | Top-Down |
| 0-1 Sırt Çantası Problemi | Bottom-Up |

Her problem için dinamik programlama tablosu konsolda düzenli ve okunabilir biçimde gösterilmektedir.

---

## Programın Çalıştırılması

Program çalıştırıldığında kullanıcıyı menü tabanlı bir arayüz karşılar.  
Kullanıcı menü üzerinden ilgili algoritma grubunu seçerek testleri çalıştırabilir.

---

## Genel Değerlendirme

Bu proje, algoritmaların yalnızca doğru çalışmasını değil;  
zaman karmaşıklığı, bellek kullanımı ve farklı çözüm yaklaşımlarının etkilerini gözlemlemeyi amaçlamaktadır.

Kod okunabilirliği ve çıktı düzeni özellikle ön planda tutulmuştur.

---

Hazırlayan  
İrem Kalaycı  
Algoritma Analizi ve Karmaşıklığı Dersi Projesi
