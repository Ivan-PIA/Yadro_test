#include <complex>
#include <random>
#include <vector>
#include <cmath>
using namespace std;


class Gaussian_noise{

    private:
        double real;
        double imag;

    public:
        vector<complex<double>> add_Gaussian_noise(vector<complex<double>> vec_qam, double dispersion){
            
            random_device rd;
            mt19937 gen(rd());
            normal_distribution<double> d(0.0, dispersion);

            for (int i = 0 ; i < vec_qam.size(); i++){
                
                imag = vec_qam[i].imag();
                real = vec_qam[i].real();

                imag += d(gen);
                real += d(gen);

                vec_qam[i] = complex<double>(real, imag);
                

            }
            return vec_qam;
            
        }

};