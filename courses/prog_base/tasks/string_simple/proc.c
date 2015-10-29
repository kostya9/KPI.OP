/*Знайти номер рядка, у якому найбільше разів зустрічається додаткова підстрока.
У результуючу строку спочатку записати кількість рядків у які додаткова строка входить хоча б один раз,
пробіл, і першу зі строк у яку додаткова строка не входить жодного разу*/

char * process(char * resultStr, const char * textLines[],
    int linesNum, const char * extraStr)
{
    int nMost = -1;
    int iMost = -1;
    int nZero = -1;
    int nMoreOne = 0;
    int i, curOutputSymb = 0;
    for(i=0; i<linesNum; i++)
    {
        int nCurMost = 0;
        const char * line = textLines[i];
        if(!strstr(line, extraStr) && nZero==-1)
            nZero = i;
        else
            nMoreOne++;
        while(strstr(line, extraStr))
        {
            nCurMost++;
            line = strstr(line, extraStr) + 1;
        }
        if(nCurMost>nMost)
        {
            nMost = nCurMost;
            iMost = i;
        }
    }
    if(nMost>0 || nZero>0)
        sprintf(resultStr, "%i %i %s", iMost, nMoreOne, textLines[nZero]);
    else
        sprintf(resultStr, "0 NULL %s", extraStr);
    return resultStr;
}
