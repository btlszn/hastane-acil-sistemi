# Hastane Yönetim Sistemi

Bu program, hastaların kaydını tutmak, ilaç eklemek, hastaları listelemek ve acil servisteki hastaları yönetmek için basit bir hastane yönetim sistemi simülatörüdür. Program, HL7 standardına uygun hasta bilgilerini tutar ve her hasta için reçete bilgileri sağlar.

## Özellikler

- **Hasta Ekleme:** Yeni bir hasta ekler ve hastanın bilgilerini (isim, yaş, cinsiyet, hastalık durumu, öncelik, vb.) kaydeder.
- **İlaç Ekleme:** Hastalara ilaç ekler, ilaç adı, dozaj ve birimi gibi bilgileri kaydeder.
- **Hasta Listesi:** Sistemdeki tüm hastaları ve reçetelerini listeleme imkanı sağlar.
- **Acil Servis İşlemi:** Acil servis öncelik sırasına göre hastaları işler ve en yüksek öncelikli hastayı seçer.

## Gereksinimler

- C derleyicisi (örneğin GCC)
- Standart C kütüphaneleri

## Kullanım

Program çalıştırıldığında aşağıdaki seçenekleri göreceksiniz:

1. **Hasta Ekle:** Yeni bir hasta kaydedebilirsiniz. Hasta bilgileri (isim, yaş, cinsiyet, hastalık durumu, öncelik) girilir.
2. **Hastaları Listele:** Sistemdeki tüm hastaların bilgilerini ve reçetelerini görüntüler.
3. **İlaç Ekle:** Bir hastaya ilaç ekler. İlaç adı, dozaj ve birimi girilir.
4. **Acil Servis Hastasını İşle:** En yüksek öncelikli hastayı acil servis için işler.
5. **Çıkış:** Programdan çıkmanıza olanak tanır.

Her seçenek, ekrana uygun talimatları verir ve kullanıcıdan gerekli bilgileri alır.

## Fonksiyonlar

- `generate_hl7_id(char *buffer, int id)` - Hasta ID'si oluşturur.
- `generate_prescription_id(char *buffer)` - Reçete numarası oluşturur.
- `add_patient()` - Yeni hasta ekler.
- `add_medication()` - Mevcut bir hastaya ilaç ekler.
- `list_patients()` - Sistemdeki tüm hastaları listeler.
- `process_emergency()` - Acil servisteki hastayı işler ve en yüksek öncelikli hastayı seçer.

## Limitler

- Maksimum 100 hasta kaydedilebilir.
- Her hasta için en fazla 5 ilaç eklenebilir.

