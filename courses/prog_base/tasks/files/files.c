void fprocess(const char * pread, const char * pwrite)
{
    int i;
    int x1, x2, y1, y2;
    char buff[100];
    FILE * fread = fopen(pread, "r");
    FILE * fwrite = fopen(pwrite, "w");
    for(i = 0; i < 18;i++)
        fgets(buff, 100, fread);
    sscanf(buff,"%i %i %i %i", &x1, &y1, &x2, &y2);
    fclose(fread);
    i = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    fprintf(fwrite, "%i", i);
    fclose(fwrite);
}
