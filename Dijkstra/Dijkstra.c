#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
typedef struct Ayrit{
        int maaliyet;
        char *yol; //ornek: 1-2
        char ziyartEdildMi; //1 true 0 false
}Ayrit;

int **graph; //grafi temsil eden komsuluk matrisi
int boyut;
Ayrit *ayritlar; //Grafin ayrit veri yapisi ile temsili

void hafizaAc();
char dosykmOku(char *dosyAdi);
void dijkstra();
char intToChar(int i);
void ayritYazdir();

int main()
{
      if(dosykmOku("matrix.amd")==-1)
      {
             printf("dosya okuma hatasi");
             return -1;
      }
      int bslngc;
      printf("Baslangic Dugumu Girin: \n");
      scanf("%d",&bslngc);
      dijkstra(bslngc);
      getch();
      return 0;
}

//komsuluk matrisi icin gerekli bellek alanin acilmasi
void hafizaAc()
{
	int i;
	graph=(int**)malloc(boyut*sizeof(int *));
	
	for(i=0; i<boyut ; i++ )
	graph[i]=(int *)malloc(boyut*sizeof(int));
}

//komsuluk matrisinin dosyadan okunmasi
char dosykmOku(char *dosyAdi)
{
     FILE *fp = fopen(dosyAdi,"r");
     if(fp==NULL)
         return -1;

     fscanf(fp,"%d",&boyut); 
     hafizaAc(boyut,boyut);
     
     int i,j;
     for(i=0;i<boyut;i++)
             for(j=0;j<boyut;j++)
                     fscanf(fp,"%d",&graph[i][j]);
                             
        return 0;
}

void dijkstra(int baslngDugm)
{
      ayritlar = (Ayrit*) malloc(boyut*sizeof(Ayrit));
      int i;

      //ayritlari hazirla tum maaliyetler sonsuz
      for(i=0;i<boyut;i++)
      {
            ayritlar[i].yol = " ";
            ayritlar[i].maaliyet = INT_MAX;
            ayritlar[i].ziyartEdildMi = '0';
      }
      ayritYazdir();      
      
      int dgm = baslngDugm; 
      //baslangic dugumu mmaliyeti ayarlama
      ayritlar[dgm].maaliyet = 0;

      int geldiDugm = dgm; //geldigim dugum
      int ziyaretEdilen=0; //ziyaret edilen toplam dugum
      
      while(ziyaretEdilen!=boyut)
      {
           ayritlar[geldiDugm].ziyartEdildMi = '1';
           ziyaretEdilen++;
           
           //dugumun ziyaret edilmemis komsularini dolas ve maaliyetini
           //geldigi yeri ve ziyaret edilip edilmedigini guncelle
           for(dgm=0;dgm<boyut;dgm++)
           {     	
            	if(ayritlar[dgm].ziyartEdildMi!='1'
                        &&graph[geldiDugm][dgm]!=0
      				    	&&graph[geldiDugm][dgm]<ayritlar[dgm].maaliyet)
                {
                	//yolu not edicek gecici degisken
                    char *temp = malloc(3*sizeof(char));
                    temp[0]= intToChar(geldiDugm);
                    temp[1]= '-';
                    temp[2]= intToChar(dgm);
                    
          	      	ayritlar[dgm].yol = temp;
            		ayritlar[dgm].maaliyet = ayritlar[geldiDugm].maaliyet+graph[geldiDugm][dgm];
            		
            		ayritYazdir();
      			}
            }
            
            //yeni dugum icin algoritma tekrar calisacak
            geldiDugm = enKuckBul();
            
            //en kucuk dugum bulamadiysa bitir
            if(geldiDugm==-1)
                break;

      }
      printf("Bitti!\n");
      ayritYazdir();
}
//ziyaret edilmemis en kucuk ayritin bulunmasi
int enKuckBul()
{
    int i,enki;
    int enk=INT_MAX;
    for(i=0;i<boyut;i++)
    {
        if(ayritlar[i].ziyartEdildMi=='0' 
            && ayritlar[i].maaliyet<enk)
        {
            enk=ayritlar[i].maaliyet;
            enki=i;
        }
     }
    // printf("%d",enki);
    if(enk==INT_MAX)
        return -1;
    else
        return enki;
}
//ayritlarin o anki durumunun yazdirilmasi
void ayritYazdir()
{
	int i;
	for(i=0;i<boyut;i++)
	{
        printf(" %c",intToChar(i));
             
        if(ayritlar[i].ziyartEdildMi=='1')
            printf("* ");
        else
            printf("  ");
              
        if(ayritlar[i].maaliyet == INT_MAX)   
            printf(" SNZ ");
        else
            printf(" %3d ",ayritlar[i].maaliyet);
                 
        printf(" %3s ",ayritlar[i].yol);
        printf("\n");
	}
	
    printf("........\n");
	getch();
}
//ayritlarin geldikleri yerin not edilebilmesi 
//icin gerekli tip donusumu
char intToChar(int i)
{
	return i+'0';
}

