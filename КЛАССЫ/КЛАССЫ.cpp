#include " À¿——€.h"
#include <Windows.h>
//
void Otrezok::ChangeCharacteristic(double m, double _N)
{
    HINSTANCE load_function = LoadLibrary(L"‘”Õ ÷»».dll");
    typedef double (*characteristic) (double, double, double, double, double, double);
    characteristic Characteristic = (characteristic)GetProcAddress(load_function, "Characteristic");
    R = Characteristic(m, start->first, end->first, start->second, end->second, _N);
    FreeLibrary(load_function);
}
double Otrezok::GetCharacteristic()
{
    return R;
}
void Otrezok::SetEnd(pair<double, double>* _end, double _N)
{
    end = _end;
    M = abs((end->second - start->second) / pow(abs(end->first - start->first), (1 / _N)));
}
pair<double, double>* Otrezok::GetEnd()
{
    return end;
}
pair<double, double>* Otrezok::GetStart()
{
    return start;
}
Otrezok* Otrezok::GetNext()
{
    return Next;
}
void Otrezok::SetNext(Otrezok* _Next)
{
    Next = _Next;
}
double Otrezok::GetM()
{
    return M;
}
//
void Otrezki::Add(pair<double, double>* tmp, double _N)
{
    Otrezok* curr = Head;
    while (curr->GetEnd()->first < tmp->first)
    {
        curr = curr->GetNext();
    }
    if (curr->GetEnd()->first != tmp->first)
    {
        Otrezok* curr1 = new Otrezok(tmp, curr->GetEnd(), _N);
        curr->SetEnd(tmp, _N);
        curr1->SetNext(curr->GetNext());
        curr->SetNext(curr1);
        //
        if (curr->GetM() >= curr1->GetM())
        {
            Mmax = curr->GetM();
            if (Mmax != 0)
            {
                m = r * Mmax;
            }
            else
            {
                m = 1;
            }
        }
        else
        {
            Mmax = curr1->GetM();
            if (Mmax != 0)
            {
                m = r * Mmax;
            }
            else
            {
                m = 1;
            }
        }
        //
        curr = Head->GetNext();
        while (curr != Head)
        {
            curr->ChangeCharacteristic(m, _N);
            curr = curr->GetNext();
        }
        curr->ChangeCharacteristic(m, _N);
        //
        double Rmax = curr->GetCharacteristic();
        curr = curr->GetNext();
        while (curr != Head)
        {
            if (curr->GetCharacteristic() > Rmax)
            {
                Rmax = curr->GetCharacteristic();
                x_Rmax.first = curr->GetStart()->first;
                x_Rmax.second = curr->GetEnd()->first;
                y_Rmax.first = curr->GetStart()->second;
                y_Rmax.second = curr->GetEnd()->second;
            }
            curr = curr->GetNext();
        }
    }
}
double Otrezki::Getm()
{
    return m;
}
pair <double, double> Otrezki::GetX_Rmax()
{
    return x_Rmax;
}
pair <double, double> Otrezki::GetY_Rmax()
{
    return y_Rmax;
};
//
double CenterSquare::Get_x1()
{
    return x1x2.first;
}
double CenterSquare::Get_x2()
{
    return x1x2.second;
}
List CenterSquare::GetType()
{
    return Type;
}
CenterSquare* CenterSquare::GetStart()
{
    return Start;
}
CenterSquare* CenterSquare::GetEnd()
{
    return End;
}
CenterSquare* CenterSquare::GetNext()
{
    return Next;
}
CenterSquare* CenterSquare::GetPrevious()
{
    return Previous;
}
void CenterSquare::SetStart(CenterSquare* _Start)
{
    Start = _Start;
}
void CenterSquare::SetEnd(CenterSquare* _End)
{
    End = _End;
}
void CenterSquare::SetNext(CenterSquare* _Next)
{
    Next = _Next;
}
void CenterSquare::SetPrevious(CenterSquare* _Previous)
{
    Previous = _Previous;
}
//
CenterSquare* Hilbert_Curve_2D::GetHead()
{
    return Head;
}
CenterSquare* Hilbert_Curve_2D::GetEnd()
{
    return End;
}
