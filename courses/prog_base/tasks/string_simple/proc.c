/*Знайти номер рядка, у якому найбільше разів зустрічається додаткова підстрока.
У результуючу строку спочатку записати кількість рядків у які додаткова строка входить хоча б один раз,
пробіл, і першу зі строк у яку додаткова строка не входить жодного разу*/

char * process(char * resultStr, const char * textLines[],
    int linesNum, const char * extraStr)
{
    int mostNum = -1;
    int zeroNum = -1;
    int nMoreOne = 0;
    int i, curOutputSymb = 0;
    for(i=0; i<linesNum; i++)
    {
        int curMostNum = 0;
        const char * line = textLines[i];
        if(!strstr(line, extraStr) && zeroNum==-1)
            zeroNum = i;
        else
            nMoreOne++;
        while(strstr(line, extraStr))
        {
            curMostNum++;
            line = strstr(line, extraStr) + 1;
        }
        mostNum = mostNum>curMostNum ? mostNum : curMostNum;
    }
    if(mostNum>0 || zeroNum>0)
        sprintf(resultStr, "%i %s", nMoreOne, textLines[zeroNum]);
    else
        sprintf(resultStr, "0 NULL %s", extraStr);
    return resultStr;
}
