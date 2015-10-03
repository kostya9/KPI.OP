#include <math.h>

int exec(int op, int  a, int b)
{
    if (op < 0)
    {
        int temp = a;
        a = b;
        b = temp;
        op = abs(op);
    }
    switch (op)
    {
        case 0:
        {
            return -a;
        }
            break;
        case 1:
        {
            return a + b;
        }
        break;
        case 2:
        {
            return a - b;
        }
        break;
        case 3:
        {
            return a*b;
        }
        break;
        case 4:
        {
            return a / b;
        }
        break;
        case 5:
        {
            return abs(a);
        }
        break;
        case 6:
        {
            return pow(a, b);
        }
        break;
        case 7:
        case 13:
        case 77:
        {
            return a%b;
        }
        break;
        case 8:
        {
            if (a >= b)
                return a;
            else
                return b;
        }
        break;
        case 9:
        {
            if (a <= b)
                return a;
            else
                return b;
        }
        break;
        case 10:
        { 
            switch(abs(b)%8)
            {
                case 0:
                    return abs(a) * sizeof(char);
                case 1:
                    return abs(a) * sizeof(signed char);
                case 2:
                    return abs(a) * sizeof(short);
                case 3:
                    return abs(a) * sizeof(unsigned int);
                case 4:
                    return abs(a) * sizeof(long);
                case 5:
                    return abs(a) * sizeof(unsigned long long);
                case 6:
                    return abs(a) * sizeof(float);
                case 7:
                    return abs(a) * sizeof(double);      
            }
        
        }
        break;
        case 11:
        {
            if (b != 0)
                return round(3.14159265358979323846 *((a + b) % (1 + 8 + 2)) / b);
            else
                return 0;
        }
        break;
        default :
        {
            if (op < 100)
                return (op%abs(a + 1)) + (op%abs(b + 1));
            else
                return -1;
        }
        break;
    }

}
