//
//  main.c
//  Refactoring
//
//  Created by Viktor Klíma on 16/12/18.
//  Copyright © 2018 Viktor Klíma. All rights reserved.
//
//Program na vypočítanie Convexneho obalu (menimalny convexny set ktory obsahuje vsetky body).
//Hlavna myslienka programu sa zaklada na Grahamovom algoritme, kde sa vytvor najprv spodna polka obalu, a potom vrchna.
//
//Standardny vstup obsahuje zapis súradnic bodov v 2d priestore. Na prvom riadku je cele císlo N (do 1000)
//to je pocet bodov, a nasleduje N dvojic celych cisel: x-ova a y-ova suradnica i-teho bodu.
//
//Na standardný vystup vypise najmensiu dlzku obalu, ktora je potrebna na obalenie setu bodov zo vstupu, zaokruhlenu na tri desatinne miesta.
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//--------Definovanie Struktur

typedef struct bod{
    int x;
    int y;
}BOD;

//--------Definovanie Globalnych premennych

BOD p0;

//--------Definovanie Funkcii

void vymenBody(BOD *v1, BOD *v2) {
    
    BOD temp = *v1;
    *v1 = *v2;
    *v2 = temp;

}//vymena dvoch bodov

int orientaciaBodu(BOD p, BOD q, BOD r){
    
    int val = (int)(q.y - p.y) * (r.x - q.x) - (int)(q.x - p.x) * (r.y - q.y);
    
    if (val == 0){
        return 0;
    }
    
    if(val > 0){
        return 1;
    }
    
    else {
        return 2;
    }
    
}//Funkcia vracia orientaciu troch za sebou iduch bodov: 0 = na jednej priamke, >0 = rotacia dolava, <0 = rotacia doprava

int vektor(BOD p1, BOD p2){
    
    return (int)(p1.x - p2.x)*(p1.x - p2.x) + (int)(p1.y - p2.y)*(p1.y - p2.y);
    
}//vypocita vektor dvoch bodov

double vzdialenostBodov(int xs, int xms,int ys,int yms){
    
    return sqrt(pow(xs - xms,2) + pow(ys - yms,2));
    
}//vypocita vzdialenost dvoch bodov z ich suradnic

int porovnanieBodov(const void *vp1,const void *vp2){
    
    BOD *p1 = (BOD *)vp1;
    BOD *p2 = (BOD *)vp2;
    
    if (orientaciaBodu(p0, *p1, *p2) == 0){
        
        if(vektor(p0, *p2) >= vektor(p0, *p1)){
            return -1;
        }
        
        else{
            return 1;
        }
    }
    
    if(orientaciaBodu(p0, *p1, *p2) == 2){
        return -1;
    }
    
    else{
        return 1;
    }
}//porovna body podla ich orientacii

BOD * convexHull(BOD *v,  int *pocet){
    
    int ymin = v[0].y;
    int min = 0;
    int i;
    int m;
    BOD *stack;
    
    for(i = 1; i < *pocet; i++){
        if((v[i].y < ymin) || ((v[i].y == ymin) && (v[i].x < v[min].x))){
            ymin = v[i].y;
            min = i;
        }
    }
    
    vymenBody(&v[0], &v[min]);
    p0 = v[0];
    
    if(*pocet > 1){
        qsort(&v[1], *pocet - 1, sizeof(BOD), porovnanieBodov);
    }
    
    m = 1;
    
    for(i = 1; i < *pocet; i++){
        
        while((i < *pocet - 1) && orientaciaBodu(v[0], v[i], v[i + 1]) == 0)
            i++;
        v[m++] = v[i];
        
    }
    
    *pocet = m;
    
    if(*pocet < 3){
        return v;
    }
    
    stack = (BOD *)malloc(*pocet * sizeof(BOD));
    stack[0] = v[0];
    stack[1] = v[1];
    stack[2] = v[2];
    m = 2;
    
    for(i = 3; i < *pocet; i++){
        
        while(orientaciaBodu(stack[m-1], stack[m], v[i]) != 2)
            m--;
        stack[++m] = v[i];
        
    }
    
    *pocet = ++m;
    free(v);
    
    return stack;
}//hlavna funkcia, ktora usporiada body podla suradnic(podla x-ovej, ked sa x-ove suradnice rovnaju, tak podla y-ovej), dalej vyberie vhodne body obalu

double obvod(int pocetBodov, BOD *v) {
    
    double obvod = 0.0;
    int i;
    
    for (i = 0; i < pocetBodov; ++i) {
        
        obvod += vzdialenostBodov(v[i].x, v[(i+1)%pocetBodov].x,v[i].y,v[(i+1)%pocetBodov].y);
    
    }
    
    return obvod;
}//vypocita obvod z bodov, ktore vybrala funkcia convexHull

//--------Definovanie Mainu

int main()
{
    int pocet;
    
    scanf("%d", &pocet);
    
    BOD *v;
    
    v = (BOD *)malloc( pocet * sizeof(BOD));
    
    for(int i = 0;i<pocet;i++){
        scanf("%d %d",&v[i].x,&v[i].y);
    }
    
    v = convexHull(v, &pocet);
    
    printf("%.3lf\n",obvod(pocet, v));
    
    return 0;
}
