/**
 * Project Untitled
 */


#ifndef _USER_H
#define _USER_H

class User {
public: 
    
void Register();
    
void Login();
    
void lihatDataPemesanan();
    
void updateDataKonsumen();
    
void prosesPembayaran();
    
void lihatDaftarKendaraan();
private: 
    void id: int;
    void name: string;
    void email: string;
    void phone: string;
    void password: string;
};

#endif //_USER_H