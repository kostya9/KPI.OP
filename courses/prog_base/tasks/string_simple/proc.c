/*Çíàéòè íîìåð ðÿäêà, ó ÿêîìó íàéá³ëüøå ðàç³â çóñòð³÷àºòüñÿ äîäàòêîâà ï³äñòðîêà.
Ó ðåçóëüòóþ÷ó ñòðîêó ñïî÷àòêó çàïèñàòè ê³ëüê³ñòü ðÿäê³â ó ÿê³ äîäàòêîâà ñòðîêà âõîäèòü õî÷à á îäèí ðàç,
ïðîá³ë, ³ ïåðøó ç³ ñòðîê ó ÿêó äîäàòêîâà ñòðîêà íå âõîäèòü æîäíîãî ðàçó*/

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
        int hasOne = strstr(line, extraStr);
        if(!hasOne && nZero==-1)
            nZero = i;
        if(hasOne)
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
    if(nMost>0 && nZero>0)
        sprintf(resultStr, "%i %i %s", iMost, nMoreOne, textLines[nZero]);
    else
        sprintf(resultStr, "0 NULL %s", extraStr);
    return resultStr;
}
