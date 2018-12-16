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

BOD p0;

void swap(BOD *v1, BOD *v2)
{
    BOD temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

int orientation(BOD p, BOD q, BOD r)
{
    int val = (int)(q.y - p.y) * (r.x - q.x) - ( int)(q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

int compare(const void *vp1, const void *vp2)
{
    BOD *p1 = (BOD *)vp1;
    BOD *p2 = (BOD *)vp2;
    
    
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
    
    if(o == 2){
        return -1;
    }
    else{
        return 1;
    }
}

BOD * Convex_Hull(BOD *v,  int *count){
    int n = *count;
    int ymin = v[0].y;
    int min = 0;
    int i;
    int m;
    BOD *stack;
    
    for(i = 1; i < n; i++)
    {
        if((v[i].y < ymin) || ((v[i].y == ymin) && (v[i].x < v[min].x)))
        {
            ymin = v[i].y;
            min = i;
        }
    }
    
    swap(&v[0], &v[min]);
    p0 = v[0];
    if(n > 1)
        qsort(&v[1], n - 1, sizeof(BOD), compare);
    m = 1;
    for(i = 1; i < n; i++)
    {
        while((i < n - 1) && orientation(v[0], v[i], v[i + 1]) == 0)
            i++;
        v[m++] = v[i];
    }
    *count = n = m;
    if(n < 3)
        return v;
    stack = (BOD *)malloc(n * sizeof(BOD));
    stack[0] = v[0];
    stack[1] = v[1];
    stack[2] = v[2];
    m = 2;
    for(i = 3; i < n; i++)
    {
        while(orientation(stack[m-1], stack[m], v[i]) != 2)
            m--;
        stack[++m] = v[i];
    }
    *count = n = ++m;
    free(v);
    
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
