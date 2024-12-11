/**
 * Project Untitled
 */


#ifndef _LOKASI_H
#define _LOKASI_H

class Lokasi {
public: 
    int id;
    string nama;
    string alamat;
    string kota;
    string provinsi;
    string negara;
    float kordinatLatitude;
    float koordinatLongitude;
    string jenisLokasi;
    
void tambahLokasi();
    
void ubahLokasi();
    
void hapusLokasi();
    
void cekStokLokal();
};

#endif //_LOKASI_H