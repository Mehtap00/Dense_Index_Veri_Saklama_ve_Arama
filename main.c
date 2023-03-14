#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

    struct kayit{
    int ogrNo;
    int dersKodu;
    int puan;
    };

    struct index{
    int no;
    int adres;
    };

    struct kayit ogrenci[100];
    struct kayit k1;
    struct kayit k2;
    struct index sira[100];

    int secim,i=0,j,k,yer,d_no,d_adres,kayitliOgrNo;
    int ilk,son,orta,ortanca,indis;
    int kontrol,kontrol_2,bul,yeniPuan,sayac;

    FILE *indeks_d;
    FILE *ikili_d;


void veriDosyasiOlustur()
{
    ikili_d=fopen("veri.bin","rb");

    if(ikili_d==NULL)
    {
    ikili_d=fopen("veri.bin","wb");
    if(ikili_d==NULL){
    printf("\nDosya olusturulamadi.\n");
    exit(1);
    }}

    fclose(ikili_d);
}


void indexDosyasiOlustur()
{
    indeks_d=fopen("indeks.txt","r+");

    if(indeks_d==NULL)
    {
    indeks_d=fopen("indeks.txt","w+");

    if(indeks_d==NULL){
    printf("\nDosya olusturulamadi.\n");
    exit(1);
    }

    else{
    fclose(indeks_d);
    i=0;

    ikili_d=fopen("veri.bin","rb");

    while(!feof(ikili_d)){
    fread(&ogrenci[i],sizeof(struct kayit),1,ikili_d);

    if(ftell(ikili_d)==0){
    i=0;
    break;}

    if(i==0){
    sira[0].adres=0;
    yer=ftell(ikili_d);
    sira[1].adres=yer;}

    else
    {
    yer=ftell(ikili_d);
    sira[i+1].adres=yer;
    }

    sira[i].no=ogrenci[i].ogrNo;

    if(i>0){
    j=i;
    d_no=sira[j].no;
    d_adres=sira[j].adres;
    k=j-1;

    while(k>=0 && sira[k].no>d_no){
    sira[k+1].no=sira[k].no;
    sira[k+1].adres=sira[k].adres;
    k--;}

    sira[k+1].no=d_no;
    sira[k+1].adres=d_adres;}

    i++;
    }
    fclose(ikili_d);

    indeks_d=fopen("indeks.txt","w");
    if(indeks_d==NULL)
    printf("Dosya acilamadi.");

    for(j=0;j<i;j++){
    fprintf(indeks_d,"%d\t%d\n",sira[j].no,sira[j].adres);}
    fclose(indeks_d);

    if(kontrol_2==4){
    printf("\nIndeks dosyasi olusturuldu ve silinen indeks dosyasindaki structlar yeni olusturulan indeks dosyasina tekrardan yazdirildi.\n");
    printf("Menu ekranina donmek icin herhangi bir tusa basiniz...");
    getch();
    printf("\n\n");}
    }}

    else
    {
    if(kontrol_2==4){
    printf("\nIndeks dosyasi program ilk acildiginda otomatik olarak olusturuldu.\n");
    printf("Menu ekranina donmek icin herhangi bir tusa basiniz...");
    getch();
    printf("\n\n");
    goto cikis2;}

    while(!feof(indeks_d)){
    fscanf(indeks_d,"%d\t%d\n",&sira[i].no,&sira[i].adres);

    if(ftell(indeks_d)==0){
    i=0;
    break;}
    i++;}

    cikis2:
    fclose(indeks_d);
    }
}


void kayitEkle()
{
    ikili_d=fopen("veri.bin","a");

    if(i==0)
    sira[i].adres=0;

    else
    {
    fseek(ikili_d,0,SEEK_END);
    yer=ftell(ikili_d);
    sira[i].adres=yer;
    }

    fwrite(&ogrenci[i],sizeof(struct kayit),1,ikili_d);
    fclose(ikili_d);

    sira[i].no=ogrenci[i].ogrNo;

    if(i>0){
    j=i;
    d_no=sira[j].no;
    d_adres=sira[j].adres;
    k=j-1;

    while(k>=0 && sira[k].no>d_no){
    sira[k+1].no=sira[k].no;
    sira[k+1].adres=sira[k].adres;
    k--;}

    sira[k+1].no=d_no;
    sira[k+1].adres=d_adres;}


    indeks_d=fopen("indeks.txt","w");
    if(indeks_d==NULL)
    printf("Dosya acilamadi.");

    for(j=0;j<=i;j++){
    fprintf(indeks_d,"%d\t%d\n",sira[j].no,sira[j].adres);}
    fclose(indeks_d);

    i++;
    printf("\nKayit ekleme islemi basarili.Menu ekranina donmek icin herhangi bir tusa basiniz...");
    getch();
    printf("\n\n");
}


void kayitBul()
{
    if(kontrol!=8 && kontrol!=9){
    printf("\nKayit bilgilerini bulmak ve listelemek istediginiz ogrenci numarasi:");}

    scanf("%d",&kayitliOgrNo);

    ilk=0;
    son=i-1;

    if(i>=1){
    while(son>=ilk)
    {
        orta=(ilk+son)/2;
        if(sira[orta].no==kayitliOgrNo){
        indis=orta;
        break;}

        if(sira[orta].no<kayitliOgrNo)
        ilk=orta+1;

        if(sira[orta].no>kayitliOgrNo)
        son=orta-1;
    }}

    else
    indis=-1;

    if(indis==-1 || sira[indis].no!=kayitliOgrNo){
    printf("\nGirilen ogrenci numarasina ait kayit bulunmamaktadir.Menu ekranina donmek icin herhangi bir tusa basiniz...");
    goto cikis;
    }

    while(indis!=0 ){
    if(sira[indis-1].no==kayitliOgrNo)
    indis--;

    else
    break;}

    sayac=1;
    while(sira[indis].no==kayitliOgrNo)
    {
       ikili_d=fopen("veri.bin","rb");
       fseek(ikili_d,sira[indis].adres,SEEK_SET);
       fread(&k1,sizeof(struct kayit),1,ikili_d);
       fclose(ikili_d);

       printf("\n\nGirilen ogrenci numarasina ait %d. kayit\n",sayac);
       printf("Ogrenci numarasi:%d\n",k1.ogrNo);
       printf("Ders kodu:%d\n",k1.dersKodu);
       printf("Puan:%d\n",k1.puan);
       sayac++;

       if(kontrol!=8 && kontrol!=9)
       printf("\nBulmak istediginiz kayit bu ise 2'ye basiniz.\nBu degil ise ayni ogrenci numarasina ait baska kayit mevcut ise onu goruntulemek icin 3'e basiniz:");

       else
       printf("\nGuncellemek veya silmek istediginiz kayit bu ise 2'ye basiniz.\nBu degil ise ayni ogrenci numarasina ait baska kayit mevcut ise onu goruntulemek icin 3'e basiniz:");

       scanf("%d",&bul);

       if(bul==2)
       {
       if(kontrol==8){
       printf("\nYeni puan:");
       scanf("%d",&yeniPuan);

       k1.puan=yeniPuan;

       ikili_d=fopen("veri.bin","r+b");
       fseek(ikili_d,(sira[indis].adres)+8,SEEK_SET);
       fwrite(&k1.puan,(sizeof(struct kayit))/3,1,ikili_d);
       fclose(ikili_d);

       printf("\nPuan guncellendi.Menu ekranina donmek icin herhangi bir tusa basiniz...");}

       if(kontrol==9)
        {
            ikili_d=fopen("veri.bin","rb");
            if(ikili_d==NULL)
            {
                printf("Veri dosyasi acilamadi.");
            }
            int r;
            r=(sira[indis].adres)/12;
            fseek(ikili_d,0,SEEK_END);
            long int buyukluk=ftell(ikili_d);
            buyukluk=buyukluk/12;

            fseek(ikili_d,0,SEEK_SET);
            for(j=0;j<i;j++)
            fread(&ogrenci[j],sizeof(struct kayit),1,ikili_d);


                    for((r=(sira[indis].adres)/12); r<buyukluk-1; r++)
                    {
                        ogrenci[r]=ogrenci[r+1];
                    }

            fclose(ikili_d);
            ikili_d=fopen("veri.bin","wb");
            fseek(ikili_d,0,SEEK_SET);
            for(int z=0; z<buyukluk-1; z++)
            {
                fwrite(&ogrenci[z],sizeof(struct kayit),1,ikili_d);
            }

             fclose(ikili_d);

                   for( int y=0; y<buyukluk; y++)
            {
                if(sira[y].adres>sira[indis].adres)
                {
                    sira[y].adres=(sira[y].adres)-12;
                }
            }


                    for(int e=indis; e<buyukluk-1; e++)
                    {
                        sira[e]=sira[e+1];
                    }

            indeks_d=fopen("indeks.txt","w");
            if(indeks_d==NULL)
            {
                printf("Dosya acilamadi.");
            }
            for(int x=0; x<buyukluk-1; x++)
            {
                fprintf(indeks_d,"%d\t%d\n",sira[x].no,sira[x].adres);
            }
            fclose(indeks_d);


             i--;
             printf("\nIstenilen kayit silinmistir.Menu ekranina donmek icin herhangi bir tusa basiniz...");
       }

       if(kontrol!=8 && kontrol!=9)
       printf("\nAranilan kayit bulundu.Menu ekranina donmek icin herhangi bir tusa basiniz...");

       goto cikis;
       }

       if(bul==3)
       indis++;

       if(bul!=2 && bul!=3){
       printf("\nYanlis deger girdiniz.Sadece 2 ve 3 degeri icin islem yapilmaktadir. Menu ekranina donmek icin herhangi bir tusa basiniz...");
       goto cikis;}

    }
    printf("\nBu ogrenci numarasina ait baska kayit bulunmamaktadir.Menu ekranina donmek icin herhangi bir tusa basiniz...");
    cikis:
    getch();
    printf("\n\n");
}


void kayitSil()
{
    printf("Silinmek istenen kayidin ogrenci numarasini giriniz: ");
    kontrol=9;
    kayitBul();
    kontrol=5;
}



void kayitGuncelle()
{
    printf("\nPuan guncellemesi yapilacak ogrenci numarasi:");
    kontrol=8;
    kayitBul();
    kontrol=5;
}



void veriDosyasiniGoster()
{

    ikili_d=fopen("veri.bin", "rb");

    if(ikili_d == NULL)
    {
        printf("Dosya acilamadi");
        exit(1);
    }
    printf("\nVeri Dosyasi Icerikleri\n");

    while(1)
    {
        struct kayit k2;

        size_t okunan_sayi = fread(&k2, sizeof(struct kayit), 1, ikili_d);

        if(ftell(ikili_d)==0){
        printf("\nVeri dosyasinda kayit bulunmamaktadir.Uygulamayi kullanarak kayit ekleyebilirsiniz.\n");
        printf("Menu ekranina donmek icin herhangi bir tusa basiniz...");
        fclose(ikili_d);
        getch();
        printf("\n\n");
        exit(1);
        }


        if(okunan_sayi <1)
        {
            break;
        }
        printf(" %d, %d, %d\n",k2.ogrNo, k2.dersKodu, k2.puan);
    }

    fclose(ikili_d);
    printf("\nVeri dosyasi listelendi.Menu ekranina donmek icin herhangi bir tusa basiniz...");
    getch();
    printf("\n\n");

}


void indeksDosyasiniGoster()
{
    char c;

    indeks_d=fopen("indeks.txt","r");

    if(indeks_d==NULL){
    printf("\nBilgisayarinizda indeks dosyasi bulunmamaktadir.Uygulamayi kullanarak olusturabilirsiniz.\n");
    printf("Menu ekranina donmek icin herhangi bir tusa basiniz...");
    goto cikis3;}

    printf("\nIndex dosyasi icerigi:\n");
    while((c=fgetc(indeks_d))!=EOF)
    {
    if(ftell(indeks_d)==0){
    printf("\nIndex dosyasinda kayit bulunmamamaktadir.Menu ekranina donmek icin herhangi bir tusa basiniz...");
    fclose(indeks_d);
    goto cikis3;}

    printf("%c",c);
    }

    fclose(indeks_d);
    printf("\nIndex dosyasi listelendi.Menu ekranina donmek icin herhangi bir tusa basiniz...");

    cikis3:
    getch();
    printf("\n\n");


}

void indeksDosyasiniSil()
{
    int kontrol_3;
    char dosyaAdi[20];
    printf("Silinecek dosyanin adini giriniz: \n");
    fflush(stdin);
    gets(dosyaAdi);
    kontrol_3 = remove(dosyaAdi);
    if(kontrol_3==0){
        printf("\nDosya basarili bir sekilde silinmistir.Menu ekranina donmek icin herhangi bir tusa basiniz...");
        getch();
        printf("\n\n");}
     else{
        printf("\nDosya silinemedi! Menu ekranina donmek icin herhangi bir tusa basiniz...");
        getch();
        printf("\n\n");}

}



int main()
{
    veriDosyasiOlustur();
    indexDosyasiOlustur();

    kontrol=5;
    kontrol_2=3;
    secim=1;

    while(secim!=0){
    printf("\n0-Sistemden Cikis\n");
    printf("1-Kayit Ekle\n");
    printf("2-Kayit Bul\n");
    printf("3-Kayit Sil\n");
    printf("4-Kayit Guncelle\n");
    printf("5-Veri Dosyasini Goster\n");
    printf("6-Indeks Dosyasini Goster\n");
    printf("7-Indeks Dosyasini Sil\n");
    printf("8-Indeks Dosyasi Olustur\n");
    printf("\nYapmak istediginiz islemi giriniz:");
    scanf("%d",&secim);

    switch(secim){
    case 0:
    printf("\nSistemden cikisiniz yapilmistir...\n");
    break;

    case 1:
    printf("\nSisteme kaydetmek istediginiz ogrenci bilgilerini giriniz:\n");
    printf("Ogrenci numarasi:");
    scanf("%d",&ogrenci[i].ogrNo);
    printf("Ders kodu:");
    scanf("%d",&ogrenci[i].dersKodu);
    printf("Puan:");
    scanf("%d",&ogrenci[i].puan);

    kayitEkle();
    break;

    case 2:
    kayitBul();
    break;

    case 3:
    kayitSil();
    break;

    case 4:
    kayitGuncelle();
    break;

    case 5:
    veriDosyasiniGoster();
    break;

    case 6:
    indeksDosyasiniGoster();
    break;

    case 7:
    indeksDosyasiniSil();
    break;

    case 8:
    kontrol_2=4;
    indexDosyasiOlustur();
    kontrol_2=3;
    break;

    default:
    printf("\nYanlis deger girdiniz.Yeni bir secim yapmak uzere menu ekranina donmek icin herhangi bir tusa basiniz...");
    getch();
    printf("\n\n");
    break;

    }}


    return 0;

}
