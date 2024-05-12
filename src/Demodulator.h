#include <complex>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;


class Demodulator{
    
    private:
        vector <int> dem_bit;
        double real;
        double imag;
        /*
        map<vector <int>, complex<double>> mapping_qam16(){
            
            for (int i = 0; i < 2; i++){
                for (int j = 0; j < 2; j++){
                    for (int k = 0; k < 2; k++){
                        for (int l = 0; l < 2; l++){
                            real = (1 - 2 * i) * (2 - (1 - 2 * k)) / sqrt(10);
                            imag = (1 - 2 * j) * (2 - (1 - 2 * l)) / sqrt(10);
                            vector <int> bit_map = {i,j,k,l}; 
                            mapping_qam[bit_map] = complex <double> (real, imag);
                            
                            for(int num : bit_map){
                                cout << num << " ";
                            }
                            cout << mapping_qam[bit_map] << endl;
                            
                        }
                    }
                }
            }

            return mapping_qam;
        }


        map<vector <int>, complex<double>> mapping_qam64(){
           
            for (int i = 0; i < 2; i++){
                for (int j = 0; j < 2; j++){
                    for (int k = 0; k < 2; k++){
                        for (int l = 0; l < 2; l++){
                            for (int e = 0; e < 2; e++){
                                for (int h = 0; h < 2; h++){
                                    real = (1 - 2 * i) * (4 - (1 - 2 * k) * (2 - (1 - 2 * e))) / sqrt(42);
                                    imag = (1 - 2 * j) * (4 - (1 - 2 * l) * (2 - (1 - 2 * h))) / sqrt(42);
                                    vector <int> bit = {i,j,k,l,e,h}; 
                                    mapping_qam[bit] = complex <double> (real, imag);
                                    
                                }
                            }

                        }
                    }
                }
            }

            return mapping_qam;
        }
        */

    public:

        void print(auto bit_map){
            for(int num : bit_map){
                cout << num << " ";
            }
        }
        vector <int> Demodulation_QPSK(vector <complex<double>> qpsk){
            dem_bit.clear();
            for (int i = 0; i < qpsk.size(); i++){
                if (qpsk[i].real() > 0.0 && qpsk[i].imag() > 0.0){
                    dem_bit.push_back(0);
                    dem_bit.push_back(0);
                }
                if (qpsk[i].real() < 0.0 && qpsk[i].imag() > 0.0){
                    dem_bit.push_back(1);
                    dem_bit.push_back(0);
                }
                if (qpsk[i].real() > 0.0 && qpsk[i].imag() < 0.0){
                    dem_bit.push_back(0);
                    dem_bit.push_back(1);
                }
                if (qpsk[i].real() < 0.0 && qpsk[i].imag() < 0.0){
                    dem_bit.push_back(1);
                    dem_bit.push_back(1);
                }
            }

            return dem_bit;
        }

        
        vector <int> Demodulation_QAM16(vector <complex<double>> qam_symbol){
            dem_bit.clear();

            double modul;
            vector <int> decode_bit_symbol;
            map<vector <int>, complex<double>> mapping_qam;

            for (int sym = 0; sym < qam_symbol.size(); sym++){
                double min = 999999.0;
                for (int i = 0; i < 2; i++){
                    for (int j = 0; j < 2; j++){
                        for (int k = 0; k < 2; k++){
                            for (int l = 0; l < 2; l++){

                                real = (1 - 2 * i) * (2 - (1 - 2 * k)) / sqrt(10);
                                imag = (1 - 2 * j) * (2 - (1 - 2 * l)) / sqrt(10);

                                vector <int> bit_map = {i,j,k,l}; 
                                mapping_qam[bit_map] = complex <double> (real, imag);

                                modul = abs(mapping_qam[bit_map] - qam_symbol[sym]) ;

                                
                                if (modul < min ){
                                    min = modul;
                                    //cout << min << " ";
                                    decode_bit_symbol = bit_map;
                                }
                            }
                        }
                    }
                }
                //print(decode_bit_symbol);
                //cout << decode_bit_symbol.size() << " ";
                dem_bit.insert(dem_bit.end(), decode_bit_symbol.begin(), decode_bit_symbol.end());


            }

            return dem_bit;

      
        }

        vector <int> Demodulation_QAM64(vector <complex<double>> qam_symbol){
            dem_bit.clear();
            double modul , min;
            vector <int> decode_bit_symbol;
            map<vector <int>, complex<double>> mapping_qam;

            for (int sym = 0; sym < qam_symbol.size(); sym++){
                min = 999999.0;
                for (int i = 0; i < 2; i++){
                    for (int j = 0; j < 2; j++){
                        for (int k = 0; k < 2; k++){
                            for (int l = 0; l < 2; l++){
                                for (int e = 0; e < 2; e++){
                                    for (int h = 0; h < 2; h++){
                                        real = (1 - 2 * i) * (4 - (1 - 2 * k) * (2 - (1 - 2 * e))) / sqrt(42);
                                        imag = (1 - 2 * j) * (4 - (1 - 2 * l) * (2 - (1 - 2 * h))) / sqrt(42);

                                        vector <int> bit_map = {i,j,k,l,e,h}; 
                                        mapping_qam[bit_map] = complex <double> (real, imag);

                                        modul = abs(mapping_qam[bit_map] - qam_symbol[sym]) ;

                                        if (modul < min ){
                                            min = modul;
                                            decode_bit_symbol = bit_map;
                                        }
                                    
                                    }
                                }
                            }
                        }
                    }
                }
                //print(decode_bit_symbol);
                //cout << decode_bit_symbol.size() << " ";
                dem_bit.insert(dem_bit.end(), decode_bit_symbol.begin(), decode_bit_symbol.end());


            }

            return dem_bit;

        }
        


};

