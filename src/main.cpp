#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>

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


int main(int argc, char* argv[]) {
    srand(time(NULL));

    vector <int> bit = gen_rand(12000);


    vector<complex<double>> qpsk, qam16, qam64;

    QAMModulator mod;

    qpsk = mod.QPSK(bit);
    qam16= mod.QAM16(bit);
    qam64 = mod.QAM64(bit);

    int file_true = atoi(argv[1]);

    // modulation
    if(file_true){
        ofstream file0("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\mod.txt", ios::binary);
        ofstream file01("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\mod16.txt", ios::binary);
        ofstream file02("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\mod64.txt", ios::binary);

        if (file0.is_open()){
            for( int i = 0; i < qpsk.size(); i++){
                file0 << qpsk[i] << " ";
            }
            for( int i = 0; i < qam16.size(); i++){
                file01 << qam16[i] << " ";
            }
            for( int i = 0; i < qam64.size(); i++){
                file02 << qam64[i] << " ";
            }
        }
        file0.close(); 
        file01.close(); 
        file02.close(); 
    }

    

    int N = 0;
    double dispersion = 0;

    vector <double> error_qam4, error_qam16, error_qam64;
    auto start = chrono::high_resolution_clock::now();
    
    while (N < 500){
        
        Gaussian_noise noise;

        vector<complex<double>> qam_noise_qpsk = noise.add_Gaussian_noise(qpsk, dispersion);
        vector<complex<double>> qam_noise_qam16 = noise.add_Gaussian_noise(qam16, dispersion);
        vector<complex<double>> qam_noise_qam64 = noise.add_Gaussian_noise(qam64, dispersion);

        if (dispersion == 0.04 && file_true){ 
            
            ofstream file11("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\demod.txt", ios::binary);
            ofstream file12("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\demod16.txt", ios::binary);
            ofstream file13("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\demod64.txt", ios::binary);
            
            if (file11.is_open() && file12.is_open() && file13.is_open()){
                for( int i = 0; i < qam_noise_qpsk.size(); i++){
                    file11 << qam_noise_qpsk[i] << " ";

                }
                for( int i = 0; i < qam_noise_qam16.size(); i++){
                    file12 << qam_noise_qam16[i] << " ";

                }
                for( int i = 0; i < qam_noise_qam64.size(); i++){
                    file13 << qam_noise_qam64[i] << " ";
                }

            }    
            file11.close(); 
            file12.close(); 
            file13.close();         
        }

        vector <int> dem_bit_4;
        vector <int> dem_bit_16;
        vector <int> dem_bit_64;

        Demodulator demod;

        

        dem_bit_4 = demod.Demodulation_QPSK(qam_noise_qpsk); //0 ms
        
        dem_bit_16 = demod.Demodulation_QAM16(qam_noise_qam16); // 12k bit - 60 ms
        
        
        dem_bit_64 = demod.Demodulation_QAM64(qam_noise_qam64); // 12k bit - 200ms

        error_qam4.push_back(error_bit(dem_bit_4,bit));
        error_qam16.push_back(error_bit(dem_bit_16,bit));
        error_qam64.push_back(error_bit(dem_bit_64,bit));

        dispersion += 0.01;
        N += 1;
        //cout << dispersion << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Время выполнения программы: " << duration.count() << " mс" << endl;

    

    //std::cout << "Время выполнения программы: " << duration.count() << " с" << std::endl;
    if(file_true){
        ofstream file1("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qpsk_er.txt", ios::binary);
        ofstream file2("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qam16_er.txt", ios::binary);
        ofstream file3("C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qam64_er.txt", ios::binary);
        
        if (file1.is_open() && file2.is_open() && file2.is_open()){
            for( int i = 0; i < error_qam4.size(); i++){
                file1 << error_qam4[i] << " ";

            }
            for( int i = 0; i < error_qam16.size(); i++){
                file2 << error_qam16[i] << " ";

            }
            for( int i = 0; i < error_qam64.size(); i++){
                file3 << error_qam64[i] << " ";
            }

        }
    
    file1.close(); 
    file2.close(); 
    file3.close(); 

    }
    //cout << dem_bit_4.size() << endl;
    //cout << dem_bit_16.size() << endl;
    //cout << dem_bit_64.size() << endl;
    return 0;
    
}
