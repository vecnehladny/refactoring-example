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
