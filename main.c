//
//  main.c
//  Refactoring
//
//  Created by Viktor Klíma on 16/12/18.
//  Copyright © 2018 Viktor Klíma. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct bod{
    int x;
    int y;
}BOD;

BOD * Convex_Hull(BOD *v,  int *count){
    int n = *count;
    int ymin = v[0].y;
    int min = 0;
    int i;
    int m;
    BOD *stack;
    
    return stack;
}

int main()
{
    int n;
    
    scanf("%d", &n);
    
    BOD v[n];
    
    for(int i = 0;i<n;i++){
        scanf("%d %d",v[i].x,&v[i].y);
    }
    
    return 0;
}
