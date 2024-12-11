/**
 * Project Untitled
 */


#ifndef _ULASAN_H
#define _ULASAN_H

class Ulasan {
public: 
    int id;
    int idPengguna;
    int idKendaraan;
    int rating;
    text komentar;
    datetime waktuPosting;
    
void tulisUlasan();
    
void lihatUlasan();
};

#endif //_ULASAN_H