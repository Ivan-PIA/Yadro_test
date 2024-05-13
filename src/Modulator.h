#include <complex>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;



class QAMModulator {

    private:

        vector <complex<double>> vec_qam;
        double real;
        double imag;

    public:
        
        vector<complex<double>> QPSK(vector <int> bit){
            vec_qam.clear();
            if (bit.size() % 2 != 0 ){
                cout << "QPSK:\nError, check bit_mass length, need multiple of 2\n";

            }
            else{
                for(int i = 0; i < bit.size(); i +=2 ){
                    real = (1 - 2*bit[i] )/sqrt(2);
                    imag = (1 - 2*bit[i+1] )/sqrt(2);
                    complex <double> comp( real , imag);
                    vec_qam.push_back(comp);
                }
            }
            return vec_qam;
        }

        vector<complex<double>> QAM16(vector <int> bit){
            vec_qam.clear();

            if (bit.size() % 4 != 0 ){
                cout << "QAM16:\nError, check bit_mass length, need multiple of 4\n";
                
            }
            else{
                for(int i = 0; i < bit.size(); i+=4 ){

                    real = (1 - 2 * bit[i]) * (2 - (1 - 2 * bit[i+2])) / sqrt(10);
                    imag = (1 - 2 * bit[i+1]) * (2 - (1 - 2 * bit[i+3])) / sqrt(10);
                    complex <double> comp( real , imag);

                    vec_qam.push_back(comp);
                }
            }
            return vec_qam;
        }

        vector<complex<double>> QAM64(vector <int> bit){
            
            vec_qam.clear();
            
            if (bit.size() % 6 != 0 ){
                cout << "QAM64:\nError, check bit_mass length, need multiple of 6\n";

            }
            else{
                for(int i = 0; i < bit.size(); i+=6 ){

                    real = (1 - 2 * bit[i]) * (4 - (1 - 2 * bit[i+2]) * (2 - (1 - 2 * bit[i+4]))) / sqrt(42);
                    imag = (1 - 2 * bit[i+1]) * (4 - (1 - 2 * bit[i+3]) * (2 - (1 - 2 * bit[i+5]))) / sqrt(42);
                    complex <double> comp( real , imag);

                    vec_qam.push_back(comp);
                }
            }
            return vec_qam;
        }
    

};