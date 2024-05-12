import numpy as np
import matplotlib.pyplot as plt


def plot_QAM(a, title = "QAM"):

    plt.figure(figsize=(6,6))
    plt.title(title)
    plt.grid(5)
    plt.axhline(y=0,color = 'red')
    plt.axvline(x=0,color = 'red')

    colors = range(len(a))
    plt.scatter(a.real, a.imag, s=10, c=colors, cmap="prism", alpha=1)
    plt.xlabel("real")
    plt.ylabel("imag")
    plt.show()



def file_qam(path_file):
    with open(path_file, 'r') as file:
        data = file.read()

    
    complex_numbers_str = data.replace('(', '').replace(')', '').split()

    complex_numbers = []
    for complex_number_str in complex_numbers_str:
        real_part, imag_part = map(float, complex_number_str.split(','))
        complex_number = complex(real_part, imag_part)
        complex_numbers.append(complex_number)

    fft = np.ravel(complex_numbers)

    return fft


def file_error_qpsk(path_file):
    with open(path_file, 'r') as file:
        values = file.read().split()
        
        
        float_array = [float(value) for value in values]

        
    return np.array(float_array)


path_qam ="C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qam64.txt"

path_qpsk = "C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qpsk_er.txt"
path_qam16 = "C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qam16_er.txt"
path_qam64 = "C:\\Users\\Ivan\\Desktop\\lerning\\YADRO\\Yadro_test\\text_file\\qam64_er.txt"

fft = file_qam(path_qam)

if(1):
    qpsk = file_error_qpsk(path_qpsk)
    qam16 = file_error_qpsk(path_qam16)
    qam64 = file_error_qpsk(path_qam64)
    dispersion = np.arange(0,5,0.01)
    plt.figure(1)
    plt.title("Зависимость вероятности ошибки на бит от дисперсии шума")
    plt.plot(dispersion,qpsk)
    plt.plot(dispersion, qam16)
    plt.plot(dispersion,qam64)
    plt.xlabel("дисперсия шума")
    plt.ylabel("вероятность ошибки на бит")
    plt.legend(["QPSK", "QAM16", "QAM64"], loc = 4)
    plt.show()

plot_QAM(fft)

