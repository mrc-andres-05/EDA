#include <iostream>
using namespace std;

class Fraccion {
private:
    int num, dem;

public:
    Fraccion(int n = 0, int d = 1) {
    num = n;
    if (d == 0) dem = 1; 
    else dem = d;
    }

    Fraccion operator + (const Fraccion& nuevo) {
        int n = num * nuevo.dem + dem * nuevo.num;
        int d = dem * nuevo.dem;
        return Fraccion(n, d);
    }

    Fraccion operator - (const Fraccion& nuevo) {
        int n = num * nuevo.dem - dem * nuevo.num;
        int d = dem * nuevo.dem;
        return Fraccion(n, d);
    }
    
    Fraccion operator * (const Fraccion& nuevo) {
        int n = num * nuevo.num;
        int d = dem * nuevo.dem;
        return Fraccion(n, d);
    }
    
    Fraccion operator / (const Fraccion& nuevo) {
        int n = num * nuevo.dem;
        int d = dem * nuevo.num;
        return Fraccion(n, d);
    }
        
    void mostrar() {
    cout << num << "/" << dem << endl;
    }

};

int main()
{
    Fraccion f1(1,5);
    Fraccion f2(2,7);
    Fraccion f3 = f1 + f2;
    Fraccion f4 = f1 * f2;

    f3.mostrar();
    f4.mostrar();

    return 0;
}