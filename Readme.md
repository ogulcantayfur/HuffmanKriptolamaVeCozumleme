Oğulcan Tayfur G181210007 2A 
Hacer Durak G181210079 2A 

Makefile çalıştırıldığında "libfdr.a" kullanılarak programımızın kaynak kodu olan main.c dosyasını derliyor
ve kripto adlı çalıştırılabilir bir dosya elde ediyoruz. Clean komutu ile derleme sırasında oluşan dosyaları
siliyoruz(*.o, kripto, vb).Cleanall komutu ile derleme sırasında oluşan dosyaların yanı sıra .kilit, encripted,
decripted, giris_metin,vb dosyalar var ise hepsini siliyoruz.Run komutu ile clean,make ve çalıştır komutlarını gerçekleştiriyoruz.

Program Libfdr/include içerisinde .h ve Libfdr/lib içerisinde libfdr.a dosyalarına ihtiyaç duymaktadır.
