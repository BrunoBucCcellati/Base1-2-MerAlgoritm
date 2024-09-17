#include <iostream>
#include <Windows.h>
#include "КЛАССЫ.h"
using namespace std;
//
pair <double, double> Base_N_Mer_Algoritm(double a, double b, double epsilon, double r, double N, double m)
{
    HINSTANCE load_function = LoadLibrary(L"ФУНКЦИИ.dll");
    //typedef double (*sh) (double);
    //sh ShekelFunc = (sh)GetProcAddress(load_function, "ShekelFunc");
    typedef double (*grsh) (double, double);
    grsh GrishaginFunc = (grsh)GetProcAddress(load_function, "GrishaginFunc");
    //
    pair<double, double>* start = new pair<double, double>;
    start->first = a;
    pair<double, double>* end = new pair<double, double>;
    end->first = b;
    //
    Hilbert_Curve_2D Curve_2D = Hilbert_Curve_2D(a, b, a, b, m);
    if (N == 2.0)
    {
        start->second = GrishaginFunc(Curve_2D.GetHead()->Get_x1(), Curve_2D.GetHead()->Get_x2());
        end->second = GrishaginFunc(Curve_2D.GetEnd()->Get_x1(), Curve_2D.GetEnd()->Get_x2());
    }
    else
    {
        //start->second = ShekelFunc(a);
        //end->second = ShekelFunc(b);
    }
    //
    Otrezok* otrezok = new Otrezok(start, end, N);
    //
    Otrezki* interval = new Otrezki(otrezok, r, N);
    //
    pair<double, double> pred_i_sled_shag;
    pred_i_sled_shag.first = a;
    pred_i_sled_shag.second = b;
    //
    pair <double, double> min_xy;
    while (pow(abs(pred_i_sled_shag.second - pred_i_sled_shag.first), (1.0 / N)) > epsilon)
    {
        min_xy.first = pred_i_sled_shag.second;
        if (min_xy.first == b)
        {
            min_xy.second = end->second;
        }
        else
        {
            short number = min_xy.first / (1.0 / pow(2.0, m * N));
            if (number <= pow(2.0, m * N) / 2.0)
            {
                CenterSquare* Curr = Curve_2D.GetHead();
                while (number != 0)
                {
                    number--;
                    Curr = Curr->GetNext();
                }
                min_xy.second = GrishaginFunc(Curr->Get_x1(), Curr->Get_x2());
            }
            else
            {
                CenterSquare* Curr = Curve_2D.GetEnd();
                while (pow(2.0, m * N) - number - 1 != 0)
                {
                    number++;
                    Curr = Curr->GetPrevious();
                }
                min_xy.second = GrishaginFunc(Curr->Get_x1(), Curr->Get_x2());
            }   
        }
        pred_i_sled_shag.first = pred_i_sled_shag.second;
        //
        typedef double (*shag) (double, double, double, double, double, double);
        shag Shag = (shag)GetProcAddress(load_function, "Shag");
        pred_i_sled_shag.second = Shag(interval->Getm(), interval->GetX_Rmax().first, interval->GetX_Rmax().second, interval->GetY_Rmax().first, interval->GetY_Rmax().second, N);
        //
        pair<double, double>* promejutochnaya_tochka = new pair<double, double>;
        promejutochnaya_tochka->first = pred_i_sled_shag.second;
        //promejutochnaya_tochka->second = ShekelFunc(pred_i_sled_shag.second);
        short number = (pred_i_sled_shag.second) / (1.0 / pow(2.0, m * N));
        if (number <= pow(2.0, m * N) / 2.0)
        {
            CenterSquare* Curr = Curve_2D.GetHead();
            while (number != 0)
            {
                number--;
                Curr = Curr->GetNext();
            }
            (promejutochnaya_tochka->second) = GrishaginFunc(Curr->Get_x1(), Curr->Get_x2());
        }
        else
        {
            CenterSquare* Curr = Curve_2D.GetEnd();
            while (pow(2.0, m * N) - number - 1 != 0)
            {
                number++;
                Curr = Curr->GetPrevious();
            }
            (promejutochnaya_tochka->second) = GrishaginFunc(Curr->Get_x1(), Curr->Get_x2());
        }
        interval->Add(promejutochnaya_tochka, N);
    }
    FreeLibrary(load_function);
    return min_xy;
}
//
int main()
{
    pair <double, double> Extr = Base_N_Mer_Algoritm(0.0, 1.0, 0.005, 4.1, 2.0, 6.0);
    cout << "Xmin = " << Extr.first << " " << "Ymin = " << Extr.second << endl;
}


