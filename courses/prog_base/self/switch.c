int main()
{
    int h;
    int m;
    double price;
    int code;
    printf("Vvedit' dani u nastupnomu formati: godynu hvylyny code\n");
    scanf("%i %i %i", &h, &m, &code);
    if(code>9 && code<1000)
    {
        switch(code)
        {
            case 44:
                price = 0.77;
                break;
            case 62:
                price = 0.8;
                break;
            case 32:
                price = 0.95;
                break;
            case 697:
            case 692:
                price = 1.5;
                break;
            default:
                price = 1;
        }
    }
    else
    {
        printf("Nekorektniy kod");
        return 0;
    }
    
    price = price * (h*60 + m);
    printf("Cena dzvinka : %f", price);
        
        
        
}
