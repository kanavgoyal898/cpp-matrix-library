#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Fraction {
    private:
        pair<int, int> frac;
        friend class Matrix;
    public:
    // Constructors
        Fraction() {
            frac.first = 0;
            frac.second = 1;
        }
        Fraction(int numerator, int denominator = 1) {
            try {
                if(denominator==0){
                    throw("Denominator cannot be 0"); 
                }
                frac.first = numerator;
                frac.second = denominator;
                simplestForm();
            } catch(const char* e) {
                cout << e;
                exit(1);
            }
            
        }
    // Setter Functions
        int setN(int num) {
            frac.first = num;
            simplestForm();
            return frac.first;
        }
        int setD(int den) {
            try {
                if(den == 0) {
                    throw("Denominator cannot be 0");
                    frac.second = den;
                    simplestForm();
                    return frac.second;
                }
            } catch(const char* e) {
                cout << e;
                exit(1);
            }
            return 0;
        }
        pair<int, int> setF(int n1, int n2) {
            try{
                if(n2==0) {
                    throw("Denominator cannot be 0");
                }
                frac.first = n1;
                frac.second = n2;
                simplestForm();
                return frac;
            } catch(const char* e){
                cout << e;
                exit(1);
            }
        }
    // Getter Functions
        int getN() {
            return frac.first;
        }
        int getD() {
            return frac.second;
        }
        pair<int, int> getF() {
            return frac;
        }
    // Utility Function
        int gcd(int a, int b) {
            if(b == 0) {
                return a;
            }
            return gcd(b, a%b);
        }
        int simplestForm() {
            int div = gcd(abs(frac.first), abs(frac.second));
            frac.first = frac.first/div;
            frac.second = frac.second/div;
            return div;
        }
    // Display Function
        int display() {
            cout << frac.first << "/" << frac.second << " ";
            return 0;
        }
    // Operations
        Fraction inverse() {
            Fraction f;
            f.frac.first = frac.second;
            f.frac.second = frac.first;
            f.simplestForm();
            return f;
        }
    // Whole Number Handling
        // type conversion (non-primitive to primitive)
        operator int() {
            return frac.second == 1 ? frac.first : frac.first/frac.second;
        }
    // Operator Overloading
        Fraction operator +(int);
        Fraction operator -(int);
        Fraction operator *(int);
        Fraction operator /(int);
        friend Fraction operator -(Fraction&);
        friend Fraction operator +(Fraction&, Fraction&);
        friend Fraction operator -(Fraction&, Fraction&);
        friend Fraction operator *(Fraction&, Fraction&);
        friend Fraction operator /(Fraction&, Fraction&);
        friend void operator >> (istream & cin, Fraction& f) {
            int num = 0;
            int den = 1;
            cin >> num;
            cin >> den;
            try {
                if(den==0){
                    throw("Denominator cannot be 0");
                }
                f.frac.first = num;
                f.frac.second = den;
                f.simplestForm();
            } catch(const char* e) {
                cout << e;
                exit(1);
            }
        }
        friend void operator << (ostream & cout, Fraction& f) {
            cout << f.frac.first << "/" << f.frac.second << " ";
        }
};

Fraction Fraction::operator +(int num) {
    Fraction f;
    f.frac.first = frac.first + frac.second*num;
    f.frac.second = frac.second;
    f.simplestForm();
    return f;
}
Fraction Fraction::operator -(int num) {
    Fraction f;
    f.frac.first = frac.first - frac.second*num;
    f.frac.second = frac.second;
    f.simplestForm();
    return f;
}
Fraction Fraction::operator *(int num) {
    Fraction f;
    f.frac.first = frac.first*num;
    f.frac.second = frac.second;
    f.simplestForm();
    return f;
}
Fraction Fraction::operator /(int num) {
    Fraction f;
    f.frac.first = frac.first;
    f.frac.second = frac.second*num;
    f.simplestForm();
    return f;
}
Fraction operator -(Fraction& f) {
    Fraction fAns;
    fAns.frac.first = -f.frac.first;
    fAns.frac.second = f.frac.second;
    return f;
}
Fraction operator +(Fraction& f1, Fraction& f2) {
    Fraction f3;
    f3.frac.first = (f1.frac.first * f2.frac.second) + (f2.frac.first * f1.frac.second);
    f3.frac.second = f1.frac.second * f2.frac.second;
    f3.simplestForm();
    return f3;
}
Fraction operator -(Fraction& f1, Fraction& f2) {
    Fraction f3;
    f3.frac.first = (f1.frac.first * f2.frac.second) - (f2.frac.first * f1.frac.second);
    f3.frac.second = f1.frac.second * f2.frac.second;
    f3.simplestForm();
    return f3;
}
Fraction operator *(Fraction& f1, Fraction& f2) {
    Fraction f3;
    f3.frac.first = f1.frac.first * f2.frac.first;
    f3.frac.second = f1.frac.second * f2.frac.second;
    f3.simplestForm();
    return f3;
}
Fraction operator /(Fraction& f1, Fraction& f2) {
    Fraction f3;
    f3.frac.first = f1.frac.first * f2.frac.second;
    f3.frac.second = f1.frac.second * f2.frac.first;
    f3.simplestForm();
    return f3;
}