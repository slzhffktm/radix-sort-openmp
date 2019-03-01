# IF3230 - *Radix Sort* dengan OpenMP

## Petunjuk Penggunaan Program

Jalankan Makefile.

```shell
make
```

Jalankan *command*:

```shell
# thread_count adalah jumlah thread
# size adalah ukuran senarai yang hendak diurutkan

# Linux
./radix_sort <thread_count> <size>

# Windows cmd
radix_sort <thread_count> <size>
```

## Pembagian Kerja

NIM | Pembagian Kerja
--- | ---------------
13516007 | program & laporan
13516121 | program & laporan

## Laporan Pengerjaan

### Solusi Paralel

Dalam penyelesaian *radix sort* dengan OpenMP, kami menggunakan paralelisasi pada bagian memasukkan elemen-elemen senarai pada *bucket*. *Bucket* awal diinisialisasi sebanyak 10 dikali jumlah *thread* yang digunakan. Isi dari *bucket* dimasukkan kembali ke senarai secara berurutan sesuai dari *rank thread*.

Paralelisasi pada program dilakukan dengan menaruh perintah:

```C++
#pragma omp parallel for schedule(static) num_threads(thread_count) reduction(+:sum0)
```

`parallel` digunakan karena menggunakan banyak *thread* sekaligus (sistem paralel).

`for` digunakan karena iterasi akan dibagi ke beberapa thread.

`schedule(static)` digunakan karena pembagian iterasi akan dibagi bergantung dengan *rank* *thread*. *Thread* 0 akan mendapatkan bagian pertama, *thread* 1 akan mendapatkan bagian kedua, dan seterusnya.

`num_threads(thread_count)` digunakan untuk mendefinisikan jumlah *thread* sebanyak `thread_count`.

`reduction(+:sum0)` digunakan agar operasi matematika (+) terhadap variabel `sum0` tetap berjalan dengan semestinya.

### Jumlah *Thread* yang Digunakan

Jumlah *thread* yang digunakan (paling optimal) adalah sebanyak maksimal jumlah *thread* yang dapat berjalan bersamaan.

### Pengukuran Kinerja

Dalam pengukuran kinerja, jumlah *thread* yang dipakai adalah 12.

N=5000 | Paralel | Serial
------ | ------- | ------
1      | 9122    | 9312
2      | 9669    | 9113
3      | 9181    | 10501

N=50000 | Paralel | Serial
------ | ------- | ------
1      | 36922    | 75262
2      | 38192    | 75412
3      | 40251   | 75016

N=100000 | Paralel | Serial
------ | ------- | ------
1      | 70902    | 148356
2      | 71349    | 146937
3      | 72741    | 148517

N=200000 | Paralel | Serial
------ | ------- | ------
1      | 115428    | 285689
2      | 120860    | 294011
3      | 120142    | 283001

N=400000 | Paralel | Serial
------ | ------- | ------
1      | 226829    | 581584
2      | 252717    | 517368
3      | 212272    | 498310

### Analisis Solusi dan Perbandingan Kinerja Serial dan Paralel

Berdasarkan hasil pengerjaan, dapat dilihat bahwa untuk *test case* dengan `size` yang cenderung kecil (~5000), performa kode dengan sistem paralel dan sistem serial tidak begitu jauh, bahkan sistem serial dapat memiliki waktu eksekusi yang lebih sedikit. Namun, dengan `size` yang semakin besar, dapat dilihat bahwa kinerja *radix sort* dengan sistem paralel memiliki performa semakin baik dibandingkan dengan *radix sort* sistem serial.

Solusi yang kami tawarkan sudah cukup optimal, namun solusi ini akan menjadi lebih baik lagi apabila diterapkan operasi  *bitwise* pada program.