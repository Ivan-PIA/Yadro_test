#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#include "C:\Users\Ivan\Desktop\lerning\YADRO\Yadro_test\src\Modulator.h"
#include "C:\Users\Ivan\Desktop\lerning\YADRO\Yadro_test\src\Gaussian_noise.h"
#include "C:\Users\Ivan\Desktop\lerning\YADRO\Yadro_test\src\Demodulator.h"

using namespace std;

vector<int> gen_rand(int size){
    vector<int>mass;
    for (int i = 0; i < size; i++){
        mass.push_back(rand()%2);
    }
    return mass;
}


double error_bit( vector <int> bit_after, vector <int> bit_before){
    double err_bit = 0.0; 
    for (int i = 0; i < bit_before.size(); i++ ){
        if (bit_after[i] != bit_before[i]){
            err_bit+=1;
        }
    }
    
    return(err_bit/bit_before.size());
}


int main() {
    srand(time(NULL));

    vector <int> bit = gen_rand(1200);


    vector<complex<double>> qpsk;
    vector<complex<double>> qam16;
    vector<complex<double>> qam64;
    QAMModulator mod;

    qpsk = mod.QPSK(bit);
    qam16= mod.QAM16(bit);
    qam64 = mod.QAM64(bit);

    ofstream file0("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\mod.txt", ios::binary);

    
    if (file0.is_open()){
        for( int i = 0; i < qpsk.size(); i++){
            file0 << qpsk[i] << " ";
        }
    }
    
    int N = 0;
    double dispersion = 0;

    vector <double> error_qam4, error_qam16, error_qam64;
    if (1){
    while (N < 500){
        
        Gaussian_noise noise;

        vector<complex<double>> qam_noise_qpsk = noise.add_Gaussian_noise(qpsk, dispersion);
        vector<complex<double>> qam_noise_qam16 = noise.add_Gaussian_noise(qam16, dispersion);
        vector<complex<double>> qam_noise_qam64 = noise.add_Gaussian_noise(qam64, dispersion);
        

        vector <int> dem_bit_4;
        vector <int> dem_bit_16;
        vector <int> dem_bit_64;

        Demodulator demod;

        dem_bit_4 = demod.Demodulation_QPSK(qam_noise_qpsk);
        dem_bit_16 = demod.Demodulation_QAM16(qam_noise_qam16);
        dem_bit_64 = demod.Demodulation_QAM64(qam_noise_qam64);
        

        error_qam4.push_back(error_bit(dem_bit_4,bit));
        error_qam16.push_back(error_bit(dem_bit_16,bit));
        error_qam64.push_back(error_bit(dem_bit_64,bit));

        dispersion += 0.01;
        N += 1;
        cout << dispersion << endl;
    }
    
    ofstream file("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qpsk_er.txt", ios::binary);
    ofstream file2("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qam16_er.txt", ios::binary);
    ofstream file3("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qam64_er.txt", ios::binary);
    
    if (file.is_open()){
        for( int i = 0; i < error_qam4.size(); i++){
            file << error_qam4[i] << " ";
            file2 << error_qam16[i] << " ";
            file3 << error_qam64[i] << " ";
        }
    }

    }//if
    // for (int i = 0; i < qpsk.size(); i++){
    //   cout << qpsk[i] << " ";
    // }
    // cout << endl;
    //cout << dem_bit_4.size() << endl;
    //cout << dem_bit_16.size() << endl;
    //cout << dem_bit_64.size() << endl;
    return 0;
    
}
