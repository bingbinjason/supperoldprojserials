
#include "core.h"
#include "CORE01.h"
#include "CORE02.h"
#include "CORE04.h"
#include "CORE07.h"
#include "CORE06.h"

//泡泡龙地图
char paodat[]={
//0
0,0,0,3,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//1
1,1,2,2,3,3,4,4  ,
 1,1,2,2,3,3,4   ,0,
3,3,4,4,1,1,2,2  ,
 3,4,4,1,1,2,2   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//2
0,2,2,2,1,1,1,0  ,
 2,0,0,0,0,0,1   ,0,
0,2,0,0,0,0,1,0  ,
 2,3,4,5,3,4,1   ,0,
0,4,5,3,4,5,3,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//3
0,2,2,2,1,1,1,0  ,
 2,0,0,0,0,0,1   ,0,
0,2,0,0,0,0,1,0  ,
 2,3,4,5,3,4,1   ,0,
0,4,5,3,4,5,3,0  ,
 0,3,4,5,3,4,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//4  //9代表火道具，烧掉周围六个
0,0,0,2,3,4,0,0  ,
 0,0,3,4,5,2,0   ,0,
0,0,0,5,9,3,0,0  ,
 0,4,3,2,0,0,0   ,0,
0,2,5,4,3,0,0,0  ,
 0,3,9,5,0,0,0   ,0,
0,0,0,4,3,2,0,0  ,
 0,0,2,5,4,3,0   ,0,
0,0,0,3,9,5,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//5
0,0,6,6,6,6,0,0  ,
 0,0,0,5,0,0,0   ,0,
0,0,0,5,4,0,0,0  ,
 0,0,0,4,0,0,0   ,0,
0,0,0,4,7,0,0,0  ,
 0,0,0,7,0,0,0   ,0,
0,0,0,7,3,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//6
0,0,6,0,0,6,0,0  ,
 0,0,6,5,6,0,0   ,0,
0,0,0,5,4,0,0,0  ,
 0,0,5,4,5,0,0   ,0,
0,0,0,4,7,0,0,0  ,
 0,0,3,7,3,0,0   ,0,
0,0,0,7,3,0,0,0  ,
 0,0,0,3,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//7  //19代表雷电，横扫
8,1,7,4,3,2,5,19  ,
 0,0,0,0,5,0,0   ,0,
0,0,0,5,5,0,0,0  ,
 0,0,5,0,0,0,0   ,0,
19,5,2,3,4,7,1,8  ,
 0,0,0,0,5,0,0   ,0,
0,0,0,5,5,0,0,0  ,
 0,0,5,0,0,0,0   ,0,
8,1,7,4,3,2,5,19  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//8
3,0,0,0,0,0,0,3  ,
 1,3,4,2,1,3,4   ,0,
2,0,0,0,0,0,0,2  ,
 4,2,1,3,4,2,1   ,0,
0,0,0,1,0,0,0,0  ,
 0,0,0,3,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//9		
0,6,6,0,0,7,7,0  ,
 5,0,0,0,0,0,2   ,0,
4,5,0,0,0,0,2,3  ,
 4,0,0,0,0,0,3   ,0,
5,4,0,0,0,0,3,2  ,
 5,0,0,0,0,0,2   ,0,
6,5,0,0,0,0,2,7  ,
 6,6,0,0,0,7,7   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//10
6,6,0,0,0,0,7,7  ,
 5,7,0,0,0,6,2   ,0,
4,5,0,0,0,0,2,3  ,
 4,0,0,0,0,0,3   ,0,
5,7,0,0,0,0,6,2  ,
 5,0,0,0,0,0,2   ,0,
6,5,0,0,0,0,2,7  ,
 6,7,0,0,0,6,7   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//11  //这里的29代表水, 横向3格往下2-4格部分变绿
0,0,0,3,29,3,0,0  ,
 1,7,4,0,7,4,1   ,0,
7,4,1,0,0,1,7,4  ,
 1,7,4,0,7,4,1   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//12
0,0,0,4,7,0,0,0  ,
 0,2,3,0,0,0,0   ,0,
1,6,0,7,4,0,0,0  ,
 0,0,0,0,3,2,0   ,0,
0,0,0,4,7,0,6,1  ,
 0,2,3,0,0,0,0   ,0,
1,6,0,7,4,0,0,0  ,
 0,0,0,0,3,2,0   ,0,
0,0,0,0,0,0,6,1  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//13
0,0,0,7,7,0,0,0  ,
 0,0,0,3,0,0,0   ,0,
0,0,0,5,0,0,0,0  ,
 0,0,0,6,0,0,0   ,0,
0,0,0,4,0,0,0,0  ,
 0,0,0,2,0,0,0   ,0,
0,0,0,7,0,0,0,0  ,
 0,0,0,3,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//14  //9为雷电道具,左边的往右扫
8,0,19,0,0,19,0,5  ,
 8,3,0,0,0,3,5   ,0,
7,5,2,0,0,2,8,7  ,
 3,4,0,0,0,4,3   ,0,
8,7,0,0,0,0,7,5  ,
 0,1,0,0,0,1,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//15 
2,0,0,0,0,0,0,3  ,
 2,4,0,0,0,1,3   ,0,
3,5,9,0,0,9,5,6  ,
 7,2,0,0,0,3,2   ,0,
0,4,5,0,0,5,1,0  ,
 0,3,2,0,3,6,0   ,0,
0,0,7,5,5,2,0,0  ,
 0,0,4,5,1,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//16  //这里9为火道具
4,4,0,0,0,0,7,7  ,
 7,0,0,0,0,0,4   ,0,
7,0,0,0,0,0,0,4  ,
 5,0,5,7,5,0,3   ,0,
7,4,7,3,5,4,7,4  ,
 4,9,7,0,4,9,7   ,0,
0,3,6,0,0,3,6,0  ,
 0,0,4,9,7,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//17
0,5,0,0,0,0,0,0  ,
 5,0,0,0,0,0,0   ,0,
0,4,3,2,6,1,7,0  ,
 0,0,0,0,0,0,5   ,0,
0,0,0,0,0,0,5,0  ,
 0,4,3,2,6,1,0   ,0,
0,5,0,0,0,0,0,0  ,
 5,0,0,0,0,0,0   ,0,
0,4,3,2,6,1,7,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//18
0,1,0,0,0,0,0,0  ,
 7,0,0,0,0,0,0   ,0,
4,3,2,6,1,7,4,3  ,
 0,0,0,0,0,0,2   ,0,
0,0,0,0,0,0,6,0  ,
 0,2,3,4,7,1,0   ,0,
0,6,0,0,0,0,0,0  ,
 1,0,0,0,0,0,0   ,0,
7,4,3,2,6,1,7,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//19
0,8,8,0,0,4,4,0  ,
 0,7,0,0,0,3,0   ,0,
0,3,0,0,0,3,0,0  ,
 0,3,0,0,0,8,0   ,0,
0,2,0,0,0,7,0,0  ,
 0,4,0,0,0,3,0   ,0,
0,2,0,0,0,3,0,0  ,
 0,3,0,0,0,2,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
//20
0,0,0,7,7,0,0,0  ,
 0,0,0,3,0,0,0   ,0,
0,0,0,4,2,0,0,0  ,
 0,0,0,1,0,0,0   ,0,
0,0,0,4,2,0,0,0  ,
 0,7,0,7,0,5,0   ,0,
5,8,5,8,5,8,5,8  ,
 5,0,2,0,6,0,3   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//21    9: fire
0,0,2,5,4,0,0,0  ,
 0,5,0,0,5,0,0   ,0,
0,0,2,9,4,2,5,0  ,
 0,5,4,2,0,0,2   ,0,
0,4,0,0,4,9,5,0  ,
 0,5,9,2,5,4,0   ,0,
0,0,2,5,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//22  9:fire
0,0,4,2,7,0,0,0  ,
 0,7,0,0,2,0,0   ,0,
0,0,4,9,7,5,4,0  ,
 0,7,5,4,0,0,5   ,0,
0,5,0,0,7,9,4,0  ,
 0,7,9,4,2,7,0   ,0,
0,0,4,2,0,0,4,0  ,
 0,0,0,4,9,7,0   ,0,
0,0,0,0,7,5,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//23  9:elec
0,0,5,0,0,19,0,0  ,
 0,2,0,0,8,0,0   ,0,
0,6,0,0,5,5,5,0  ,
 1,0,0,0,0,6,0   ,0,
5,5,5,5,0,2,0,0  ,
 0,0,7,0,0,0,0   ,0,
0,0,8,0,0,0,0,0  ,
 0,4,0,0,0,0,0   ,0,
0,5,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//24
0,0,0,0,5,0,0,0  ,
 6,2,4,7,0,0,0   ,0,
1,0,0,5,0,0,0,0  ,
 0,0,0,7,4,2,6   ,0,
1,0,0,0,5,0,0,1  ,
 6,2,4,7,0,0,0   ,0,
0,0,0,5,0,0,0,1  ,
 0,0,0,7,4,2,6   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//25 9:water  gray water
0,0,0,0,29,7,0,0  ,
 0,0,0,29,0,7,0   ,0,
0,0,0,0,29,7,0,0  ,
 0,0,0,0,2,8,1   ,0,
0,0,0,0,8,1,2,8  ,
 0,0,0,0,2,8,1   ,0,
0,0,0,0,8,1,2,8  ,
 0,0,0,0,2,8,1   ,0,
0,0,0,0,8,1,2,8  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  , 

//26
0,0,0,8,8,0,0,0  ,
 0,0,7,8,5,0,0   ,0,
0,0,4,7,5,1,0,0  ,
 0,2,4,0,1,6,0   ,0,
0,6,2,0,0,6,2,0  ,
 1,6,0,0,0,2,4   ,0,
5,1,0,0,0,0,4,7  ,
 5,0,0,0,0,0,7   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//27
0,0,0,0,6,4,1,0  ,
 0,0,4,6,4,1,4   ,0,
0,0,1,6,4,1,3,0  ,
 0,1,6,4,1,6,0   ,0,
0,4,6,4,1,4,0,0  ,
 4,6,4,1,4,0,0   ,0,
2,1,8,6,4,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//28
7,0,0,0,0,0,0,7  ,
 7,0,1,1,1,0,7   ,0,
0,7,2,0,0,2,7,0  ,
 0,4,0,0,0,4,0   ,0,
0,1,8,0,0,8,1,0  ,
 0,4,0,0,0,4,0   ,0,
0,0,2,0,0,2,0,0  ,
 0,0,1,1,1,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//29
0,4,0,1,0,6,0,1  ,
 4,0,6,0,8,0,1   ,0,
1,0,5,0,7,0,4,0  ,
 0,3,0,5,0,1,0   ,0,
0,2,0,8,0,2,0,0  ,
 8,0,4,0,3,0,0   ,0,
0,0,4,0,8,0,0,0  ,
 0,0,0,7,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//30  9:water blue
7,0,0,0,0,0,0,4  ,
 7,29,0,0,0,29,4   ,0,
3,5,0,0,0,0,5,3  ,
 4,2,0,0,0,2,7   ,0,
5,7,0,0,0,0,4,5  ,
 2,5,0,0,0,5,2   ,0,
7,4,0,0,0,0,7,4  ,
 2,0,0,0,0,0,2   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//31 9: elec
4,4,0,6,4,0,6,6  ,
 7,6,0,1,0,4,1   ,0,
5,4,0,5,19,0,6,5  ,
 7,0,0,7,0,0,6   ,0,
0,6,0,19,5,0,4,0  ,
 5,0,4,7,6,0,6   ,0,
5,0,0,4,19,0,0,5  ,
 4,0,0,0,0,0,6   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//32
0,0,0,0,5,0,0,0  ,
 0,0,0,0,4,0,0   ,0,
1,5,4,5,3,5,2,5  ,
 0,0,0,0,1,0,0   ,0,
0,0,0,2,5,0,0,0  ,
 0,0,5,0,4,0,0   ,0,
0,0,0,3,5,0,0,0  ,
 0,0,0,0,2,0,0   ,0,
0,0,0,1,5,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//33
4,2,3,4,7,8,1,1  ,
 1,0,5,0,3,0,5   ,0,
0,3,2,8,4,2,7,0  ,
 0,7,0,5,0,2,0   ,0,
0,4,4,4,1,2,4,0  ,
 5,0,3,0,2,0,3   ,0,
1,2,2,7,7,7,7,5  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//34  9: fire
0,7,7,7,4,4,4,0  ,
 1,4,2,3,4,7,8   ,0,
2,7,4,7,4,7,4,8  ,
 4,1,7,9,4,7,7   ,0,
2,7,6,4,7,3,4,4  ,
 1,4,0,0,0,7,5   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//35
0,0,0,7,2,0,0,0  ,
 0,0,7,5,5,0,0   ,0,
0,0,0,3,4,0,0,0  ,
 0,5,2,0,3,3,0   ,0,
0,4,5,5,7,5,6,0  ,
 0,7,3,0,4,2,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//36
0,0,0,0,5,0,0,0  ,
 0,0,0,5,0,0,0   ,0,
0,3,0,0,5,0,2,0  ,
 7,0,0,5,0,0,8   ,0,
0,2,0,0,5,0,5,0  ,
 0,8,0,5,0,7,0   ,0,
0,0,2,7,8,5,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//37  9:elec
4,0,0,2,2,0,0,1  ,
 4,0,0,3,0,0,1   ,0,
2,0,0,19,19,0,0,5  ,
 1,0,0,0,0,0,4   ,0,
5,4,2,1,4,5,1,2  ,
 1,5,0,0,0,2,4   ,0,
4,2,4,0,0,1,5,1  ,
 5,1,0,0,0,4,2   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//38
6,6,6,6,6,6,6,6  ,
 6,0,0,0,0,0,6   ,0,
6,0,0,3,8,7,3,3  ,
 6,0,0,0,8,4,1   ,0,
6,0,0,0,0,0,2,8  ,
 7,7,0,0,0,0,0   ,0,
2,4,1,3,0,0,0,0  ,
 8,3,8,2,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//39  9: fire
0,0,0,0,0,0,6,6  ,
 0,5,3,0,0,0,3   ,0,
0,6,0,2,0,0,5,4  ,
 4,0,0,7,2,3,7   ,0,
5,0,0,0,5,4,9,5  ,
 7,0,0,4,3,7,4   ,0,
0,2,0,6,0,0,5,2  ,
 0,3,5,0,0,0,6   ,0,
0,0,0,0,0,0,4,4  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//40
0,0,0,1,4,0,0,0  ,
 0,0,4,3,1,0,0   ,0,
0,0,3,1,4,3,0,0  ,
 0,1,4,3,1,4,0   ,0,
0,4,3,1,4,3,1,0  ,
 3,1,4,3,1,4,3   ,0,
1,4,3,1,4,3,1,4  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//41
1,1,1,1,1,1,1,1  ,
 2,0,0,0,0,0,0   ,0,
0,4,3,7,6,1,2,4  ,
 0,7,0,0,0,0,0   ,0,
0,0,6,1,2,4,3,7  ,
 0,0,2,0,0,0,0   ,0,
0,0,0,4,3,7,6,1  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//42  9: water gray
0,0,7,29,0,0,0,0  ,
 0,2,4,1,0,0,0   ,0,
0,4,1,2,4,0,0,0  ,
 1,2,4,1,2,0,0   ,0,
2,4,1,2,4,1,0,0  ,
 1,2,4,1,2,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//43
5,0,6,0,0,1,0,5  ,
 5,0,5,0,1,5,4   ,0,
0,2,0,4,7,0,4,0  ,
 3,6,0,0,0,2,0   ,0,
1,0,4,7,6,3,0,6  ,
 1,0,0,0,0,0,5   ,0,
0,5,2,1,6,7,4,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//44  9 : elec
7,0,0,7,5,7,0,7  ,
 7,0,5,1,7,0,7   ,0,
5,0,7,6,5,0,0,19  ,
 5,0,5,2,7,0,5   ,0,
19,0,7,4,5,0,0,5  ,
 7,0,5,3,7,0,0   ,0,
7,0,0,7,5,7,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,


//45
1,1,1,0,0,1,1,1  ,
 0,0,1,0,1,0,0   ,0,
0,0,3,4,4,3,0,0  ,
 0,4,0,7,0,4,0   ,0,
0,0,7,4,4,7,0,0  ,
 0,0,1,5,1,0,0   ,0,
0,2,3,0,0,3,2,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//46
0,0,0,7,7,0,0,0  ,
 0,0,7,0,0,0,0   ,0,
0,4,2,1,1,0,0,7  ,
 4,4,2,1,7,0,7   ,0,
4,3,4,1,1,7,7,0  ,
 4,4,2,1,7,0,7   ,0,
0,4,2,1,1,0,0,7  ,
 0,0,7,0,0,0,0   ,0,
0,0,0,7,7,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//47 9: water blue
0,0,5,1,2,7,0,0  ,
 0,0,0,0,29,0,0   ,0,
0,0,2,7,5,1,0,0  ,
 0,0,29,0,0,0,0   ,0,
0,0,5,1,2,7,0,0  ,
 0,0,0,0,29,0,0   ,0,
0,0,2,7,5,1,0,0  ,
 0,0,29,0,0,0,0   ,0,
0,0,5,1,2,7,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//48 9: water blue
0,7,5,1,2,7,0,0  ,
 0,0,0,0,29,0,0   ,0,
0,0,2,7,5,1,2,0  ,
 0,0,29,0,0,0,0   ,0,
0,7,5,1,2,7,0,0  ,
 0,0,0,0,29,0,0   ,0,
0,0,2,7,5,1,2,0  ,
 0,0,29,0,0,0,0   ,0,
0,7,5,1,2,7,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//49 
0,4,4,0,4,4,4,0  ,
 4,6,7,2,1,7,4   ,0,
5,4,4,4,0,4,4,5  ,
 3,5,3,5,3,5,3   ,0,
5,4,4,0,4,4,4,3  ,
 4,7,1,2,7,6,4   ,0,
3,4,4,4,0,4,4,3  ,
 5,5,3,3,3,5,5   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//50  9:fire
0,0,0,0,0,4,7,6  ,
 4,1,3,6,5,1,2   ,0,
0,6,7,2,4,3,9,0  ,
 9,4,5,6,7,1,0   ,0,
3,7,1,3,2,1,9,0  ,
 3,7,6,3,2,5,4   ,0,
0,6,6,0,0,5,4,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//51
2,2,2,0,0,4,7,6  ,
 5,1,3,6,5,1,2   ,0,
0,4,7,2,4,3,9,0  ,
 9,4,7,6,7,1,0   ,0,
0,7,5,3,2,1,9,0  ,
 7,5,1,3,2,5,4   ,0,
6,6,4,0,0,6,5,4  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//52
0,1,7,0,0,0,0,0  ,
 4,5,4,0,0,0,0   ,0,
0,7,1,0,0,0,0,0  ,
 0,0,7,4,0,0,0   ,0,
0,0,1,5,1,0,0,0  ,
 0,0,4,7,0,0,0   ,0,
0,0,0,0,4,1,0,0  ,
 0,0,0,7,1,7,0   ,0,
0,0,0,0,1,4,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//53
1,4,6,2,7,5,1,4  ,
 7,5,1,4,6,2,7   ,0,
1,4,6,2,7,5,1,4  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//54  9: water gray
0,0,0,2,2,7,7,0  ,
 4,5,6,8,4,5,1   ,0,
1,2,6,0,29,0,0,0  ,
 8,4,6,1,0,0,0   ,0,
5,1,2,7,8,0,0,0  ,
 7,8,4,5,0,0,0   ,0,
4,5,1,2,7,0,0,0  ,
 0,8,5,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//55
8,0,0,0,0,0,0,1  ,
 1,5,2,4,6,7,8   ,0,
8,0,0,0,0,0,0,1  ,
 1,5,2,4,6,7,8   ,0,
8,0,0,0,0,0,0,1  ,
 1,5,2,4,6,7,8   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//56 9: elec
5,0,0,0,0,0,0,5  ,
 5,0,2,5,5,0,5   ,0,
6,0,8,8,8,1,0,2  ,
 5,0,1,7,1,0,5   ,0,
2,0,8,8,5,2,0,4  ,
 5,8,5,19,8,5,8   ,0,
0,0,7,8,5,6,0,0  ,
 0,6,0,0,0,7,0   ,0,
0,0,7,0,0,6,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//57 9: fire
8,7,4,0,0,4,6,5  ,
 0,0,6,4,7,0,0   ,0,
6,9,7,5,8,6,9,7  ,
 6,7,0,0,0,6,7   ,0,
7,5,6,0,0,7,8,6  ,
 0,0,8,4,5,0,0   ,0,
7,9,6,7,6,7,9,6  ,
 7,6,0,0,0,7,6   ,0,
0,0,8,0,0,5,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//58
4,4,2,1,1,2,4,4  ,
 8,4,2,1,2,4,2   ,0,
1,5,4,2,2,4,8,5  ,
 8,2,4,2,4,5,8   ,0,
8,5,3,4,4,2,8,5  ,
 8,4,2,4,1,5,7   ,0,
2,5,8,1,2,8,8,7  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//59
1,1,0,0,0,0,2,2  ,
 2,5,0,0,0,3,1   ,0,
6,1,0,0,0,0,2,7  ,
 6,0,0,0,0,0,6   ,0,
2,8,0,0,0,0,2,1  ,
 1,2,3,6,2,1,2   ,0,
0,6,1,2,1,2,6,0  ,
 0,3,0,6,0,5,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//60 9: water blue
3,1,0,0,0,0,0,0  ,
 7,29,0,0,0,0,0   ,0,
1,5,7,0,0,0,0,0  ,
 4,1,29,0,0,0,0   ,0,
0,7,4,1,0,0,0,0  ,
 1,5,7,29,0,0,0   ,0,
7,4,1,5,7,0,0,0  ,
 5,7,4,1,5,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//61
0,6,6,0,0,6,6,0  ,
 1,0,2,0,2,0,1   ,0,
7,0,0,4,4,0,0,7  ,
 1,0,0,0,0,0,1   ,0,
0,6,0,0,0,0,6,0  ,
 0,2,0,0,0,2,0   ,0,
0,0,4,0,0,4,0,0  ,
 0,0,3,0,3,0,0   ,0,
0,0,0,7,7,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//62
0,0,0,1,7,0,0,0  ,
 0,0,3,8,4,0,0   ,0,
0,0,7,2,6,5,0,0  ,
 0,1,8,3,5,2,0   ,0,
0,0,4,6,4,1,0,0  ,
 0,0,5,8,3,0,0   ,0,
0,0,0,2,7,0,0,0  ,
 0,0,0,1,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//63  9:elec
1,1,0,0,0,0,3,3  ,
 0,5,1,19,3,5,0   ,0,
2,1,0,1,3,0,3,2  ,
 0,5,2,0,2,5,0   ,0,
1,2,0,0,0,0,2,3  ,
 0,5,1,19,3,5,0   ,0,
2,1,0,1,3,0,3,2  ,
 0,5,2,0,2,5,0   ,0,
1,1,0,0,0,0,3,3  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,

//64
6,6,0,3,3,0,1,1  ,
 7,0,0,4,0,0,8   ,0,
3,0,0,5,0,0,3,0  ,
 5,0,0,4,0,0,1   ,0,
5,0,0,3,0,0,5,0  ,
 5,0,0,8,0,0,6   ,0,
1,0,0,5,0,0,6,0  ,
 7,0,0,8,0,0,5   ,0,
0,0,0,0,0,0,0,0  ,
 0,0,0,0,0,0,0   ,0,
0,0,0,0,0,0,0,0  ,



};

int news=0,dels=0,fals=0;

enum EFTTYP{EFT_NONE,EFT_XUMU,EFT_WEIMU,EFT_WIN,EFT_LOST,EFT_LOADING,EFT_PAUSE,
	EFT_READYGO,EFT_SCRO,EFT_CLEARPAO,EFT_DOWNPAO,EFT_COMEPRE,EFT_GDELEC,EFT_ELEC,
	EFT_GDFIRE,EFT_GDWATER,EFT_COMEGD,EFT_BGDPOINT,EFT_BGDBALL,EFT_BGDELEC,EFT_CONCLD,};
enum GAMESTA{GST_XUMU,GST_WEIMU,GST_MENU,GST_GAMING,GST_HARD,GST_PAUSE,GST_READY,
	GST_GAMEEND,GST_GAMFINAL,GST_CONCLUT,GST_CSLXUMU,GST_CSLWEIMU};
enum GAMETYP{GTP_STORY=0,GTP_CHLG=1,};
enum TIMETYP{TIM_NOINPUT=0,TIM_DOWNMAP=1,TIM_GAMETICK=2,TIM_MAKEGD=3,TIM_POINT=4,};
enum PLAYERSTA{PST_UNREADY,PST_READY,PST_GAMING,PST_ENDED,PST_LOSE,PST_STATEEND,PST_PAUSE,PST_LUNCHING,};


#define GAMEMAPW 8
#define GAMEMAPH 12
#define GAMEMAXP 2 //最大玩家数

#define PLY0LUNCHXY Point2(82,210)
#define PLY0ORGXY Point2(100.0f,22.0f)
#define PLY0ORGWH Point2(160.0f,226.0f)
#define PLY0PAOWH Point2(10.0f,8.660f)
#define PLY0PAOR 9.0f

#define PLY1LUNCHXY Point2(52,155)
#define PLY1ORGXY Point2(60.0f,48.0f)
#define PLY1ORGWH Point2(96.0f,170.0f)
#define PLY1PAOWH Point2(6.0f,6.0f)
#define PLY1PAOR 6.0f

#define PLY2LUNCHXY Point2(52,155)
#define PLY2ORGXY Point2(214.0f,48.0f)
#define PLY2ORGWH Point2(96.0f,170.0f)
#define PLY2PAOWH Point2(6.0f,6.0f)
#define PLY2PAOR 6.0f



struct Eftstr
{
  EFTTYP Eftp;
  ptc _pa;
  ptc _pb[10];
  Point2 *ps_,ps,ps0,ps1;
  Point3 pos,pos0;
  char num,num0,num1,num2;
  float nm,nm0,nm1;
  unsigned int dtime,lagtime;
  bool flg,flg0,enable;
  Eftstr()
  {
    init();
  }
  void init()
  {
    Eftp=EFT_NONE;
    num=num0=num1=0;
    nm=nm0=0;
    dtime=lagtime=0;
    enable=true;
    flg=false;
    flg0=false;
  }
};
enum{BVISIT=50,VISITBOUND=60,VISITFLG=70,BOUNDARY=200,};
class _MAPSTR
{
public:
	void init()
	{
		memset(paotj,0,12);
		memset(paoflg,0,GAMEMAPW*GAMEMAPH);
		memset(paobuf,0,GAMEMAPW*GAMEMAPH);
		blong=1;canbgood=1;goodtp=0;
		goodps=0;
	};
	void clear()
	{
		init();
	};
	void clearflg()
	{
		memset(paoflg,0,GAMEMAPW*GAMEMAPH);
	};
	void release()
	{
		
	};
	bool get(int x,int y,char *clr)
	{
		if(x<0||x>=GAMEMAPW||y<0||y>=GAMEMAPH)return false;
		*clr=paobuf[y*GAMEMAPW+x];
		return true;
	};
	bool set(int x,int y,char clr)
	{
		if(x<0||x>=GAMEMAPW||y<0||y>=GAMEMAPH)return false;
		paobuf[y*GAMEMAPW+x]=clr;
		return true;
	};
	char get(int xy){return paobuf[xy];};
	void set(int xy,char clr){paobuf[xy]=clr;};
	Point2 getaroundp(int x,int y,char s)
	{
		char bl=bLong(y)?1:0;
		switch(s)
		{
		case 0:	y-=1;x-=bl;	break;
		case 1:	y-=1;x+=!bl;break;
		case 2:	x+=1;		break;
		case 3: y+=1;x+=!bl;break;
		case 4: y+=1;x-=bl;	break;
		case 5: x-=1;		break;
		}
		return Point2(x,y);
	}
	char getaround(int x,int y,char s)
	{
		Point2 p=getaroundp(x,y,s);
		return paobuf[(int)p.y*GAMEMAPW+(int)p.x];
	}
	
	_MAPSTR(){init();};
	~_MAPSTR(){release();};
public:
	char paobuf[GAMEMAPW*GAMEMAPH];
	char paoflg[GAMEMAPW*GAMEMAPH];
	char paotj[12];
	char blong,canbgood,goodtp;
	int goodps;
public:
	int addgood(char tp)
	{
		if(!canbgood||goodtp!=0)return -1;
		int i;
		goodtp=tp;
		for(int j=0;j<100;j++)
		{
			i=rand()%(GAMEMAPW*GAMEMAPH);
			if(paobuf[i]>0&&paobuf[i]<9)
			{
				goodtp=tp;
				goodps=i;
				canbgood=0;
				break;
			}
		}
		return i;
	}
	void readyforgood()
	{
		canbgood=1;
		goodtp=0;
	}
	void clrpao(int i)
	{
		char *c=&paobuf[i];
		if((*c)>0 && (*c)<9)
		{
			paotj[*c]-=1;
			paotj[11]-=1;
		}
		*c=0;
		if(goodps==i)
		{
			canbgood=1;
			goodtp=0;
		}
	};
	void chgpao(int i,char clr)
	{
		char t=paobuf[i];
		paobuf[i]=clr;
		if(t<9&&t>0) paotj[t]-=1;
		else paotj[11]+=1;//若改变的是道具，总数要加
		paotj[clr]+=1;
	};
	void addpao(int i,char clr)
	{
		paobuf[i]=clr;
		paotj[clr]+=1;
		paotj[11]+=1;
	};
	bool clearpao(int x,int y,char clr,int *clrs,int dep=0);
	bool checkbdown(int x,int y,char flg,char *fgs,char *s);
	void checkbdown1();
	bool bcleard()
	{
		if(paotj[11]!=0)
				return false;
		return true;
	};
	bool bLong(int y)
	{
		return ABS(blong-y%2);
	};
	
	void loadmap(char mapn);
	char calcnextpao();
	void downpao();//挑战模式
};
class _gamedata
{
public:
	char gamemode,gameplayers,gameeasyhard;
	char paobufw,paobufh;
	Point2 GameWinpos,GameWinwh;
	GAMESTA gamesta;
public:
	void init()
	{
		GameWinpos=Point2(3,15);
		GameWinwh=Point2(314,232);
		paobufw=GAMEMAPW;
		paobufh=GAMEMAPH;
		gameplayers=1;
		gamemode=0;
		gameeasyhard=0;
		gamesta=GST_CSLXUMU;
	};
	void release()
	{
	};
	void clear()
	{
		gameplayers=1;
		gamemode=0;
		gamesta=GST_CSLXUMU;
	};
	void setstate(GAMESTA st){gamesta=st;};
	GAMESTA getstate(){return gamesta;};
};
class GameEffect;
class _player
{
public:
	char name[8];
	char pass[8];
	char m_rpos,m_vpos;
	char id;
	char money;
	char score;
	char statescr;
	char timeused;
	char level;
	char curpaoclr;
	char nextpaoclr;
	char lunchclr;
	char tpls;//提示线段数
	char pointangl;
	char curtheigh;//当前墙高度
	char goods[8];//玩家的道具栏,8个
	float paorad;//泡大小
	bool showtipl;
	bool bbreakpt;
	PLAYERSTA psta;//玩家状态
	_Time *m_timer[5];//自己的计时器
	Point2 paosz;
	Point2 ttl[15];//提示线
	Point2 paopos,paoinc,mappos,wakpos;//泡位置，泡速度,地图偏移，晃动
	Point2 gwinpos,gwinwh,lunchpos;//自己的游戏窗口 ,发射位置
	Point2 awatapos,goodps;//awata窗口,道具窗口
	_MAPSTR mapbf;//地图数据
	_gamedata *gdt;
	GameEffect *eft;
	CManager_Time *tim;
public:
	_player()
	{
		eft=NULL;tim=NULL;
	};
	void init()
	{
		psta=PST_UNREADY;
		memset(pass,0,8);
		memset(name,0,8);
		memset(goods,0,8);
		memset(m_timer,0,sizeof(_Time *)*5);
		money=0;
		id=0;
		m_rpos=0;
		m_vpos=0;
		score=0;
		statescr=0;
		timeused=0;
		paorad=9.0f;
		pointangl=0;
		level=1;
		tpls=10;
		curtheigh=0;
		curpaoclr=0;
		lunchclr=0;
		showtipl=true;
		bbreakpt=false;
		paosz=PLY0PAOWH;//cos(60*Pi)*20,sin(60*Pi)*10);
		gwinpos=PLY0ORGXY;
		gwinwh=PLY0ORGWH;
		lunchpos=PLY0LUNCHXY;
		awatapos=Point2(0,0);
		goodps=Point2(0,0);
		ttl[0]=Point2(0,0);
		mappos=Point2(0,0);
		wakpos=Point2(0,0);
		mapbf.init();
	};
	void stateclear()
	{
		mapbf.clear();
		setstate(PST_STATEEND);
		statescr=0;
//		timeused=0;
		curtheigh=0;
		mappos=Point2(0,0);
		bbreakpt=false;
		for(int i=0;i<5;i++)
		{
			if(m_timer[i]!=NULL)
			{
				m_timer[i]->Reset();
				m_timer[i]->SetTimeStart(false);
			}
		}
	};
	void release()
	{
		mapbf.release();
	};
public:
	Point2 getrealpos(float x,float y)////取得数据结构位置
	{
		Point2 xy1;
		xy1=gwinpos+mappos+wakpos;
		x=x-xy1.x;y=y-xy1.y;
		y=(int)(y/(paosz.y*2));
		if(mapbf.bLong(y)==false)x-=paosz.x;
		x=(int)(x/(paosz.x*2));
		xy1=Point2(x,y);
		//	if(gamemode==1)	y=((int)y+(GAMEMAPH-(int)curtheigh%GAMEMAPH))%GAMEMAPH;
		return xy1;
	};
	Point2 getvirtpos(int x,int y)//数据结构坐标到屏幕坐标
	{
		Point2 xy1,txy;
		//	if(gamemode==1)	y=(y+(int)curtheigh%GAMEMAPH)%GAMEMAPH;
		xy1=gwinpos+mappos+wakpos+Point2(paosz.x,paosz.y);
		txy.x=x*paosz.x*2;txy.y=y*paosz.y*2;
		if(mapbf.bLong(y)==false)txy.x+=paosz.x;
		xy1=xy1+txy;
		return xy1;
	};
	Point2 getvirtpos(int xy)
	{
		int x=xy%GAMEMAPW,y=xy/GAMEMAPW;
		return Point2(x,y);
	};
	bool getgamereslt()
	{
//		if(gdt->gamemode==GTP_STORY)
//		{
			return mapbf.bcleard();
//		}
//		else
//		{
				
//		}
		
	};
	bool checktuchline()
	{
		int i,j=(GAMEMAPH-curtheigh-1)*GAMEMAPW;
		if(gdt->gamemode==GTP_STORY)
		{
			for(i=j;i<j+GAMEMAPW;i++)
			{
				if(mapbf.get(i)!=0)
				{
					return true;
				}
			}
		}
		else
		{
			j=(GAMEMAPH-1)*GAMEMAPW;
			for(i=j;i<j+GAMEMAPW;i++)
			{
				if(mapbf.get(i)!=0)
				{
					return true;
				}
			}
		}
		return false;
	};
	void doclearpao(int x,int y,char clr);	
	void runlunch();
	void lunchpao();
	void usegdpoint(char ps);
	int gettipline(Point2 o,float alp,Point2 *tl,char* siz);
	void resetwall()
	{
		mappos=Point2(0,0);
		curtheigh=0;
	};
	void downwall();
	void wakemap();//晃动地图
	void drawtipline(Point2 o, float alp,Point2 *tl,char siz,char cr);
	void drawpoint(float angl,char c);
	void drawgameinfo();
	void drawfrtgrdinloop();
	void drawbkgrdinloop();
	void drawtime(int t);//提示时间
	void drawreadygo();//下一关的动画
	void drawpao(float x,float y,char clr);
	void drawpao1(int x,int y,char clr)
	{
		Point2 cc=getvirtpos(x,y);
		Circle(cc.x,cc.y,3,clr);
	};
	void drawwall();
	void drawmap();
	void nextlevel(char s=1);
	void startplay();	
	void drivepoint(char dir)
	{
		pointangl+=dir;
		if(pointangl<-82)pointangl=-82;
		else if(pointangl>82)pointangl=82;
		tpls=10;gettipline(Point2(gwinpos.x+lunchpos.x+cos((pointangl-90)*Pi)*30,gwinpos.y+lunchpos.y+sin((pointangl-90)*Pi)*30),pointangl,ttl,&tpls);
	};
	void toggltipl(char sh=3)
	{
		if(sh==3)
		  showtipl=!showtipl;
		else showtipl=sh;
	};
	void setstate(PLAYERSTA st){psta=st;};
	PLAYERSTA getstate(){return psta;};
	void refleshinputtick()
	{
		if(m_timer[TIM_NOINPUT]->IsTimeOver()!=true)
		{	m_timer[TIM_NOINPUT]->Reset();
		m_timer[TIM_NOINPUT]->SetTimeStart();
		}
	};
};


class GameEffect
{
public:
  _player *pdt;
  _gamedata *gdt;
  
  NODE<Eftstr *> Eftlst;
public:
  void Effectloop();
  void Effectdestroy();
  void startwinani();
  void startloseani(char pl);
  void startgameweimuani();
  void startloadingani();

  bool loopwinani(Eftstr *eft);
  bool looploseani(Eftstr *eft);
  bool loopgameweimuani(Eftstr *eft);
  bool looploadingani(Eftstr *eft);

  void startconcldsta(char pl=0);
  bool loopconcldsta(Eftstr *eft);

  void startgamexumuani();
  void startclearpaoani(Point2 s,char clr,char pl=0);
  void startdownpaoani(Point2 s,char i,char clr,char pl=0,char typ=0);
  void startcomeprepaoani();
  void startreadygoani(Point2 s,char lev,char pl=0);
  //固定道具--水，火，电
  void startelecgoodani(Point2 s,int i,char pl=0);
  void startelecani(Point2 s,float l, float siz, float hi,float lagtm,float timelong,char pl=0);
  void startwatergoodani(Point2 s,int i,char pl=0);
  void startfiregoodani(Point2 s,int i,char pl=0);
  bool loopelecgoodani(Eftstr *eft);
  bool loopelecani(Eftstr *eft);
  bool loopwatergoodani(Eftstr *eft);
  bool loopfiregoodani(Eftstr *eft);


  //大道具--雷，断针，原子弹
  void startbgdelec(char pl=0);
  void startbgdpoint(char pl=0);
  void startbgdball(char pl=0);
  bool loopbgdelec(Eftstr *eft);
  bool loopbgdpoint(Eftstr *eft);
  bool loopbgdball(Eftstr *eft);

  void startscroani(Point2 s,char sc,char clr,char pl=0);
//  void startgooduseani();
  void startgoodmoveani(Point2 s,char typ,char clr,Point2 s1=Point2(0,0),char pl=0,char pl1=0);

  bool loopscroani(Eftstr *eft);
//  bool loopgooduseani(Eftstr *eft);
  bool loopgoodmoveani(Eftstr *eft);
  bool loopreadygoani(Eftstr *eft);

  bool loopgamexumuani(Eftstr *eft);
  bool loopclearpaoani(Eftstr *eft);

	  
  bool loopdownpaoani(Eftstr *eft);
  bool loopcomeprepaoani(Eftstr *eft);

  
};
void GameEffect::Effectdestroy()//Delete 有问题，未能全部删除,故用free,存在内存泄露
{
	for(int i=0;i<Eftlst.GetSize();i++)
	{
		Eftlst.SetAt(0);
		delete Eftlst.Getdata();
		Eftlst.Delete();//非物理删除;
		dels+=1;
	}
	Eftlst.Free();
}
void GameEffect::Effectloop()
{
	Eftstr *eftstr;
	bool bres=true;
	for(eftstr=Eftlst.GetFirst();eftstr!=NULL;eftstr=Eftlst.GetNext())
	{
		switch(eftstr->Eftp)
		{
		case EFT_WIN:{bres=loopwinani(eftstr);break;}
		case EFT_LOST:{bres=looploseani(eftstr);break;}
		case EFT_XUMU:{bres=loopgamexumuani(eftstr);break;}
		case EFT_WEIMU:{bres=loopgameweimuani(eftstr);break;}
		case EFT_LOADING:{bres=looploadingani(eftstr);break;}
		case EFT_READYGO:{bres=loopreadygoani(eftstr);break;}
		case EFT_CLEARPAO:{bres=loopclearpaoani(eftstr);break;}
		case EFT_DOWNPAO:{bres=loopdownpaoani(eftstr);break;}
		case EFT_SCRO:{bres=loopscroani(eftstr);break;}
		case EFT_CONCLD:{bres=loopconcldsta(eftstr);break;}
		case EFT_COMEPRE:{bres=loopcomeprepaoani(eftstr);break;}
		case EFT_COMEGD:{bres=loopgoodmoveani(eftstr);break;}
		case EFT_ELEC:{bres=loopelecani(eftstr);break;}
		case EFT_GDELEC:{bres=loopelecgoodani(eftstr);break;}
		case EFT_GDFIRE:{bres=loopfiregoodani(eftstr);break;}
		case EFT_GDWATER:{bres=loopwatergoodani(eftstr);break;}
		case EFT_BGDELEC:{bres=loopbgdelec(eftstr);break;}
		case EFT_BGDPOINT:{bres=loopbgdpoint(eftstr);break;}
		case EFT_BGDBALL:{bres=loopbgdball(eftstr);break;}
		case EFT_PAUSE:{;}
		}
		if(bres==false)
		{
			Eftlst.Delete();//非物理删除;
			delete eftstr;
			dels+=1;
		}
	}
}
void GameEffect::startwinani(){}
bool GameEffect::loopwinani(Eftstr *eft){return true;}
void GameEffect::startloseani(char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_LOST;
	estr->num0=pl;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
bool GameEffect::looploseani(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	int tot=(GAMEMAPW*(GAMEMAPH));
	int alp;//=tot-(dtime/5)% (tot+5);
//	if(alp<0||alp>GAMEMAPW*GAMEMAPH)return false;
	for(alp=tot;alp>=0;alp--)
	{
		if(pdt[eft->num0].mapbf.get(alp))
		{
//			pdt[eft->num0].mapbf.set(alp,5);
			pdt[eft->num0].mapbf.clrpao(alp);
			startdownpaoani(pdt[eft->num0].getvirtpos(alp%GAMEMAPW,alp/GAMEMAPW),alp,5,eft->num0,1);
		}
	}
	return false;
}
void GameEffect::startconcldsta(char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_CONCLD;
	estr->num0=pl;
	estr->dtime=gettimetick();
	estr->lagtime=2;
	Eftlst.Push(estr);
}
bool GameEffect::loopconcldsta(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime){if(((dtime/500) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}}
	
	Point2 pos=pdt[eft->num0].gwinpos+pdt[eft->num0].gwinwh*0.5+Point2(-35,-30);

	int alp=dtime/20;
	if(alp<90)
		print_string(pos.x-8,pos.y,9,"Round Clear");
	else if(alp>100 && alp<200)
	{
		print_num(pos.x,pos.y,pdt[eft->num0].timeused,9);
		print_string(pos.x+20,pos.y,9,"SEC");
		print_num(pos.x,pos.y+20,pdt[eft->num0].statescr,9);
		print_string(pos.x+20,pos.y+20,9,"SCORE");
	}
	else if(alp>200)
	{
		pdt[eft->num0].nextlevel();
		return false;
	}
	return true;
}
void GameEffect::startreadygoani(Point2 s,char lev,char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_READYGO;
	estr->num0=pl;
	estr->ps0=s;
	estr->ps1=Point2(0,0);
	estr->ps=Point2(0,0);
	estr->nm=0;
	estr->num=lev;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
bool GameEffect::loopreadygoani(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	Point2 s0,s1;static float wak=0;
	
	FillLine(eft->ps0.x-10,eft->ps0.y-25,  eft->ps0.x+75,eft->ps0.y+15, 0);
	print_string(eft->ps0.x,eft->ps0.y-20,1+3*7,"ROUND");
	print_num(eft->ps0.x+50,eft->ps0.y-20, eft->num,1+3*7);
	if( (dtime/10) < 50 )
	{
		eft->ps.x=(dtime/2);//angle
		eft->ps.y=180+(dtime/2);
		eft->ps1.x=50-(dtime/10);//rad
		eft->ps1.y=50-(dtime/10);
		s0=Point2(eft->ps0.x+cos(eft->ps.x*Pi)*eft->ps1.x, eft->ps0.y+sin(eft->ps.x*Pi)*eft->ps1.x);
		s1=Point2(eft->ps0.x+cos(eft->ps.y*Pi)*eft->ps1.y, eft->ps0.y+sin(eft->ps.y*Pi)*eft->ps1.y);
		s1=s1+Point2(44,0);
	}
	else 
	{
		eft->ps=Point2(0,180);
		eft->ps1=Point2(0,0);
		
		s0=eft->ps0+Point2(wak,0);
		s1=eft->ps0+Point2(wak+44,0);
		if(dtime>3000 && dtime<4000)
		{
			wak=sin((double)dtime)*2;
		}
		else if(dtime>4000)
		{
			eft->ps=Point2((dtime-4000)/2,180+(dtime-4000)/2);
			eft->ps1=Point2((dtime-4000)/10,(dtime-4000)/10);
			eft->nm=eft->ps1.x * 6.0f/70.0f;
			if(eft->ps1.x>70)
			{
				pdt[eft->num0].setstate(PST_GAMING);
				for(int i=0;i<4;i++)
				{
					if(pdt[eft->num0].m_timer[i]!=NULL)
						pdt[eft->num0].m_timer[i]->SetTimeStart();
				}
				
				return false;
			}
			
			s0=Point2(eft->ps0.x+cos(eft->ps.x*Pi)*eft->ps1.x, eft->ps0.y+sin(eft->ps.x*Pi)*eft->ps1.x);
			s1=Point2(eft->ps0.x+cos(eft->ps.y*Pi)*eft->ps1.y, eft->ps0.y+sin(eft->ps.y*Pi)*eft->ps1.y);
			s1=s1+Point2(44,0);
		}
	}
	print_string(s0.x,s0.y,1+3*7+(int)eft->nm,"Ready");
	print_string(s1.x,s1.y,1+3*7+(int)eft->nm,"Go!");

	return true;
}
void GameEffect::startscroani(Point2 s,char sc,char clr,char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_SCRO;
	estr->num0=pl;
	estr->num1=sc;
	estr->num=clr;
	estr->ps0=s;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
bool GameEffect::loopscroani(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	int alp=(dtime/100)%10;
	if(alp>=5)return false;
	eft->ps0.y-=0.4;
	print_num(eft->ps0.x,eft->ps0.y,(int)eft->num,1+(eft->num-1)*7+alp,0);

	return true;
}


void GameEffect::startwatergoodani(Point2 s,int i,char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_GDWATER;
	estr->num0=pl;
	estr->ps=Point2(i%GAMEMAPW,i/GAMEMAPW);
	estr->ps0=s;
	estr->nm=s.y;
	estr->nm0=s.y;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
void GameEffect::startfiregoodani(Point2 s,int i,char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_GDFIRE;
	estr->num0=pl;
	estr->ps=Point2(i%GAMEMAPW,i/GAMEMAPW);
	estr->ps0=s;
	estr->nm=9.0f;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
void GameEffect::startelecgoodani(Point2 s,int i,char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_GDELEC;
	estr->num0=pl;
	estr->ps=Point2(i%GAMEMAPW,i/GAMEMAPW);
	estr->ps0=s;
	float l;
	if(s.x> (pdt[pl].gwinpos.x+pdt[pl].gwinwh.x/2) )
		l=-(s.x-pdt[pl].gwinpos.x-2);
	else l=pdt[pl].gwinpos.x+pdt[pl].gwinwh.x-s.x-2;
	estr->nm=l;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
bool GameEffect::loopelecgoodani(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}

	int alp=(dtime/50)%80;
	if(alp>20)
	{
		for(int i=0;i<GAMEMAPW;i++)
		{
			if(eft->nm<0)
			{if(i>eft->ps.x)continue;}
			else{if(i<eft->ps.x)continue;}
			if(pdt[eft->num0].mapbf.get((int)eft->ps.y*GAMEMAPW+i))
			{
				pdt[eft->num0].mapbf.clrpao((int)eft->ps.y*GAMEMAPW+i);
				startclearpaoani(pdt[eft->num0].getvirtpos(i,eft->ps.y),4);
			}
		}
		pdt[eft->num0].doclearpao(0,0,99);//just checkbdown
		return false;
	}
	if(alp<=5)
	{
		if(alp>0 && alp<2)
			startelecani(eft->ps0,eft->nm,10,4   ,rand()%40,1000,eft->num0);
		else if(alp >2 && alp<4)
			startelecani(eft->ps0,eft->nm,20,10   ,rand()%40,500,eft->num0);
		else if(alp >4)
			startelecani(eft->ps0,eft->nm,15,15   ,rand()%40,200,eft->num0);
	}
	return true;
}
void GameEffect::startelecani(Point2 s,float l, float siz, float hi,float lagtm,float timelong,char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_ELEC;
	estr->num0=pl;
	estr->ps0=s;
	estr->nm1=timelong;
	estr->nm=siz;
	estr->ps_=new Point2[(float)siz];
	for(int i=0;i<siz;i++)
		estr->ps_[i]=s+Point2(i*l/siz,rand()%(int)hi-rand()%(int)hi);
	estr->dtime=gettimetick();
	estr->lagtime=lagtm;
	Eftlst.Push(estr);
}
bool GameEffect::loopelecani(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/10) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	int alp=(float)(dtime)* 6.0f/eft->nm1;
	for(int i=0;i<(int)eft->nm-1;i++)
	{
		Line_(eft->ps_[i].x,eft->ps_[i].y,  eft->ps_[i+1].x,eft->ps_[i+1].y,1+3*7+alp);
	}
	if(dtime>eft->nm1)
	{
		delete[] eft->ps_;
		return false;
	}
	return true;
}
bool GameEffect::loopwatergoodani(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	float sj,cl,alp,r=3,h=pdt[eft->num0].gwinpos.y+pdt[eft->num0].gwinwh.y-eft->ps0.y;
	alp=0;//(dtime/100)%(int)3;
	if(dtime>1000)
	{
		if(eft->flg==false)
		{
			int u,v,du=0,dv=0;
			if(pdt[eft->num0].mapbf.bLong(eft->ps.y)==false)du=1;
			for(v=eft->ps.y;v<GAMEMAPH;v++)
			{
				for(u=eft->ps.x-2;u<=eft->ps.x+2-dv%2;u++)
				{
					if(u<0||u>=GAMEMAPW)continue;
					if(pdt[eft->num0].mapbf.get(v*GAMEMAPW+u+du))
						pdt[eft->num0].mapbf.chgpao(v*GAMEMAPW+u+du,4);
				}
				dv+=1;
			}
			eft->flg=true;
		}
	}
	if(dtime<=2000)
	{
		if(eft->nm<(eft->ps0.y+h))
			eft->nm=eft->ps0.y+dtime/5;
	}
	else if(dtime>2000)
	{
		if(eft->nm0<eft->ps0.y+h)
			eft->nm0=eft->ps0.y+(dtime-2000)/5;
		else return false;
	}
	for(int j=0;j<h;j+=3)
	{
		if(dtime<=2000)
		{
			if((eft->ps0.y+j)>eft->nm)break;
		}
		else if(dtime>2000)
		{
			if((eft->ps0.y+j)<eft->nm0)continue;
		}
		sj=sin((double)-dtime/40+j/3)*r;
		cl=3.5f+sj*3.5f/r;
		Line_(eft->ps0.x-40-sj,eft->ps0.y+j+alp, eft->ps0.x+40+sj, eft->ps0.y+j+alp,1+3*7+(int)(cl));
	}
	return true;	
}
bool GameEffect::loopfiregoodani(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	int i;Point2 ts;
	eft->nm=dtime/20;
	Circle(eft->ps0.x,eft->ps0.y,eft->nm+9,1+0*7+eft->nm*6.0f/20.0f);
	Circle(eft->ps0.x,eft->ps0.y,eft->nm+14,1+0*7+eft->nm*6.0f/20.0f);
	Circle(eft->ps0.x,eft->ps0.y,eft->nm+19,1+0*7+eft->nm*6.0f/20.0f);
	if(eft->nm>3)
	{
		if(eft->flg==false)
		{
			pdt[eft->num0].mapbf.clrpao((int)eft->ps.y*GAMEMAPW+eft->ps.x);
			for(i=0;i<6;i++)
			{
				ts=pdt[eft->num0].mapbf.getaroundp(eft->ps.x,eft->ps.y,i);
				if(ts.x<0||ts.x>GAMEMAPW||ts.y<0||ts.y>GAMEMAPH)continue;
				if(pdt[eft->num0].mapbf.get((int)ts.y*GAMEMAPW+(int)ts.x))
				{
					startdownpaoani(pdt[eft->num0].getvirtpos(ts.x,ts.y),(int)ts.y*GAMEMAPW+(int)ts.x,1,eft->num0,1);
					pdt[eft->num0].mapbf.clrpao((int)ts.y*GAMEMAPW+ts.x);
				}
			}
			pdt[eft->num0].doclearpao(0,0,99);
			eft->flg=true;
		}
	}
	if(eft->nm>20)
		return false;
	return true;	
}
//void GameEffect::startgooduseani()
//{
//	
//}
//bool GameEffect::loopgooduseani(Eftstr *eft)
//{
//	return true;
//}

void GameEffect::startgoodmoveani(Point2 s,char typ,char clr,Point2 s1,char pl,char pl1)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_COMEGD;
	estr->ps0=s;
	estr->ps1=s1;
	Vector2 tv=s1-s;
	estr->ps=tv;
	estr->num1=clr;
	estr->num=typ;
	estr->num0=pl;
	estr->num2=pl1;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}

bool GameEffect::loopgoodmoveani(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}

	int alp=0;float r=0;Point2 inc,ss=Point2(0,0);

	if(eft->num==0)//shine
	{
		alp=(dtime)* 6.0f/200.0f;
		r=(dtime)* 4.0f/200.0f;
		if((dtime)>200)return false;
	}
	else if(eft->num==1)//move
	{
		inc=eft->ps/800.0f;
		ss=inc*(float)dtime;
		if((dtime)>800)
		{
			if(eft->num1>0 && eft->num1<6)
				pdt[eft->num0].goods[eft->num1-1]+=1;
			return false;
		}
	}
	else if(eft->num==2)//use
	{
		if(eft->flg==false)
		{
			if(eft->num1>=0 && eft->num1<6)
				if(pdt[eft->num0].goods[eft->num1]>0)
					pdt[eft->num0].goods[eft->num1]-=1;
			eft->flg=true;
		}
		eft->ps=pdt[eft->num2].gwinpos+pdt[eft->num2].gwinwh*0.5f-Point2(18,4)-eft->ps0;
		inc=eft->ps/800.0f;
		ss=inc*(float)dtime;
		if((dtime)>800)
		{
			r=(dtime-800) * 6.0f/100.0f;
			alp=r;
			if( r>6 )
			{
				switch(eft->num1)//
				{
				case 1:
					startbgdpoint(eft->num2);
					break;
				case 2:
					break;
				case 3:
					break;
				}
				return false;
			}
		}
	}
	ss=eft->ps0+ss;
	FillLine(ss.x-4-r,ss.y-4-r,  ss.x+4+r,ss.y+4+r, 1+eft->num1*7+alp);
	return true;
}


void GameEffect::startbgdelec(char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_BGDELEC;
	estr->num0=pl;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
void GameEffect::startbgdpoint(char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_BGDPOINT;
	estr->num0=pl;
	estr->_pa.stoped=false;
	Point2 s=pdt[pl].gwinpos+pdt[pl].lunchpos;
	estr->_pa.s0=Point3(s.x,s.y,0);
	estr->_pa.v0=Point3( -5,-30,0);
	estr->_pa.makegrav();
	estr->_pa.grd=pdt[pl].gwinpos.y+pdt[pl].gwinwh.y;
	estr->_pa.e=-0.5;
	estr->_pa.timstep=0.08;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
void GameEffect::startbgdball(char pl)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_BGDBALL;
	estr->num0=pl;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	Eftlst.Push(estr);
}
bool GameEffect::loopbgdelec(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	return true;
}
bool GameEffect::loopbgdpoint(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	if(dtime>2000)return false;
	if(eft->_pa.tuchgrds>3)return false;
	Point2 s;double alp;
	alp=dtime/2;
	eft->_pa.run();

	Point2 p[3];
	p[0]=Point2(0,-8);
	p[1]=Point2(-3,2);
	p[2]=Point2(3,2);

	p[0]=Rotate(p[0],alp);
	p[1]=Rotate(p[1],alp);
	p[2]=Rotate(p[2],alp);

	p[0]=p[0]+Point2(eft->_pa.s.x,eft->_pa.s.y);
	p[1]=p[1]+Point2(eft->_pa.s.x,eft->_pa.s.y);
	p[2]=p[2]+Point2(eft->_pa.s.x,eft->_pa.s.y);

	Line_(p[0].x,p[0].y,  p[1].x,p[1].y,9);
	Line_(p[0].x,p[0].y,  p[2].x,p[2].y,9);

	if(eft->flg==false)
	{
		pdt[eft->num0].bbreakpt=true;
		pdt[eft->num0].m_timer[TIM_POINT]->SetTimeStart();
		eft->flg=true;
	}
	return true;
}
bool GameEffect::loopbgdball(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	return true;
}

void GameEffect::startcomeprepaoani()
{
}


bool GameEffect::loopcomeprepaoani(Eftstr *eft)
{
	return false;
}
void GameEffect::startgameweimuani()
{
}
void GameEffect::startloadingani()
{
}
bool GameEffect::loopgameweimuani(Eftstr *eft)
{
	return false;
}
bool GameEffect::looploadingani(Eftstr *eft)
{
	return false;
}
void GameEffect::startgamexumuani()
{
  Eftstr *estr=new Eftstr;
  if(estr==NULL){fals+=1;return;};
  news+=1;
  estr->Eftp=EFT_XUMU;
  for(int i=0;i<7;i++)
  {
    estr->_pb[i].stoped=false;
    estr->_pb[i].s0=Point3(gdt->GameWinpos.x+120+i*9,0,0);
    estr->_pb[i].v0=Point3(0,-1*(rand()%10+5),0);
    estr->_pb[i].makegrav();
    estr->_pb[i].grd=gdt->GameWinpos.y+100;
    estr->_pb[i].e=-0.5;
  }
  estr->_pb[6].stoped=true;
  estr->dtime=gettimetick();
  estr->lagtime=2;
  Eftlst.Push(estr);

}
bool GameEffect::loopgamexumuani(Eftstr *eft)
{
  unsigned int dtime=gettimetick()-eft->dtime;
  if(eft->lagtime)
  { if(((dtime/1000) <eft->lagtime ))return true;
    else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
  }

  if((dtime/1000)%60 > 10 || gdt->gamesta!=GST_XUMU)
  {
	  startgamexumuani();
	  return false;
  }
  int i;

  Line_(gdt->GameWinpos.x+120,gdt->GameWinpos.y+110,gdt->GameWinpos.x+206,gdt->GameWinpos.y+110,5, false);

  for(i=0;i<7;i++)
    eft->_pb[i].run();
  print_char(eft->_pb[0].s.x, eft->_pb[0].s.y, 'P',2);
  print_char(eft->_pb[1].s.x, eft->_pb[1].s.y, 'a',2);
  print_char(eft->_pb[2].s.x, eft->_pb[2].s.y, 'o',2);
  print_char(eft->_pb[3].s.x, eft->_pb[3].s.y, 'P',2);
  print_char(eft->_pb[4].s.x, eft->_pb[4].s.y, 'a',2);
  print_char(eft->_pb[5].s.x, eft->_pb[5].s.y, 'o',2);
  if(eft->_pb[6].stoped==false||eft->flg==true)
    print_string(eft->_pb[6].s.x, eft->_pb[6].s.y, 2, "Long");

  if( (dtime/1000)%200>2 && eft->flg==false)
  {
    eft->flg=true;
    eft->_pb[6].stoped=false;
  }
  if( eft->flg==true && eft->_pb[6].s.y>=eft->_pb[6].grd && eft->flg0==false)
  {
    eft->flg0=true;
    for(i=0;i<6;i++)
    {
      eft->_pb[i].stoped=false;
      eft->_pb[i].v0=Point3(0,-1*(rand()%10+5),0);
    }
  }

  return true;
}


void GameEffect::startclearpaoani(Point2 s,char clr,char pl)
{
  Eftstr *estr=new Eftstr;
  if(estr==NULL){fals+=1;return;};
  news+=1;
  estr->Eftp=EFT_CLEARPAO;
  estr->num1=pl;
  estr->ps=s;
  estr->num=clr;
  estr->nm=pdt[pl].paorad;
  estr->dtime=gettimetick();
  Eftlst.Push(estr);
}
bool GameEffect::loopclearpaoani(Eftstr *eft)
{
  unsigned int dtime=gettimetick()-eft->dtime;
  float alp=dtime/10; char cr;
  eft->nm=pdt[eft->num1].paorad- alp * pdt[eft->num1].paorad/80.0f;
  if(eft->nm<0)return false;
  cr=(int)((eft->nm)*6.0/pdt[eft->num1].paorad);
  Circle(eft->ps.x,eft->ps.y,eft->nm,(eft->num)*7+1-cr);
  return true;
}
void GameEffect::startdownpaoani(Point2 s,char i,char clr,char pl,char typ)
{
  Eftstr *estr=new Eftstr;
  if(estr==NULL){fals+=1;return;};
  news+=1;
  estr->Eftp=EFT_DOWNPAO;
  estr->num1=pl;
  estr->_pa.stoped=false;
  estr->_pa.s0=Point3(s.x,s.y,0);//Point3(320,240,0);
  if(typ==0)
	  estr->_pa.v0=Point3( (float)(rand()%10)-(float)(rand()%10),0-(float)(rand()%10+10),0);
  else  estr->_pa.v0=Point3( 0,5+rand()%3,0);
  estr->_pa.makegrav();
  estr->_pa.grd=pdt[pl].gwinpos.y+238;
  estr->_pa.e=-0.5;
  estr->_pa.timstep=0.08;
  estr->dtime=gettimetick();
  estr->lagtime=( GAMEMAPH-(s.y-pdt[pl].gwinpos.y)*(float)GAMEMAPH/(float)200.0f  )/1.2f;
  estr->num=clr;
  estr->num0=i;
  Eftlst.Push(estr);
}
bool GameEffect::loopdownpaoani(Eftstr *eft)
{
  unsigned int dtime=gettimetick()-eft->dtime;
  if(eft->lagtime)
  {
	  Circle(eft->_pa.s0.x,eft->_pa.s0.y,pdt[eft->num1].paorad,1+7*(eft->num-1));
	  if(((dtime/100) <eft->lagtime ))return true;
	  else { 
		  eft->dtime=gettimetick();eft->lagtime=0;
//		  pdt[eft->num1].mapbf.clrpao(eft->num0);
	  return true;  }
  }

  if((dtime/1000)%60 > 10)
	  return false;
  eft->_pa.run();
  Circle(eft->_pa.s.x,eft->_pa.s.y,pdt[eft->num1].paorad,1+7*(eft->num-1));
  return true;
}




void _MAPSTR::downpao()
{
	int i,j;
	blong=!blong;
	for(j=GAMEMAPH-1;j>=1;j--)
	{
		for(i=0;i<GAMEMAPW;i++)
		{
			paobuf[j*GAMEMAPW+i]=paobuf[(j-1)*GAMEMAPW+i];
		}
	}
	memset(paobuf,0,GAMEMAPW*sizeof(char));
	for(i=0;i<GAMEMAPW-(!blong);i++)
	{
		int alp=rand()%3 * 3 + rand()%3+1;
		if(9==alp)alp=rand()%8+1;
		addpao(i, alp);
	}
}
void _MAPSTR::checkbdown1()
{
  int i,j;bool blg=false;
  bool bct=false;
  for(j=1;j<GAMEMAPH;j++)
  {
    bct=false;
    blg=bLong(j);
    for(i=0;i<GAMEMAPW-1+blg;i++)
    {
      if(paobuf[j*GAMEMAPW+i]==0) {	bct=false;continue; }
      if(bct==true){paoflg[j*GAMEMAPW+i]=1;	continue; }
      if(blg==true)
      {
		if( (i-1)>=0)
		  if( paobuf[(j-1)*GAMEMAPW+(i-1)]!=0 && (paoflg[(j-1)*GAMEMAPW+(i-1)]>=1 || j==1) )
		    paoflg[j*GAMEMAPW+i]=1;
		if(paobuf[(j-1)*GAMEMAPW+i]!=0 && (paoflg[(j-1)*GAMEMAPW+i]>=1 || j==1) )
		  paoflg[j*GAMEMAPW+i]=1;
	  }
      else
      {
		if(paobuf[(j-1)*GAMEMAPW+i]!=0 && (paoflg[(j-1)*GAMEMAPW+i]>=1 || j==1) )
		  paoflg[j*GAMEMAPW+i]=1;
		if(paobuf[(j-1)*GAMEMAPW+i+1]!=0 && (paoflg[(j-1)*GAMEMAPW+i+1]>=1 || j==1))
		  paoflg[j*GAMEMAPW+i]=1;
      }
      if(paoflg[j*GAMEMAPW+i]>=1)bct=true;
    }
    for(i=GAMEMAPW-3+blg;i>=0;i--)
    {
		if(paobuf[j*GAMEMAPW+i]==0)continue;
		else
		{
			if(paoflg[j*GAMEMAPW+i]==0)
				if(paoflg[j*GAMEMAPW+i+1]>=1)
					paoflg[j*GAMEMAPW+i]=1;
		}
    }
  }
  for(j=GAMEMAPH-2;j>0;j--)
  {
    bct=false;
    blg=bLong(j);
    for(i=0;i<GAMEMAPW-1+blg;i++)
    {
      if(paoflg[j*GAMEMAPW+i]>=1 || paobuf[j*GAMEMAPW+i]==0){bct=false;continue;}
      if(bct==true){paoflg[j*GAMEMAPW+i]=1;	continue;}
      if(blg==true)
      {
		if((i-1)>=0)
		{
		  if(paoflg[(j+1)*GAMEMAPW+(i-1)]>=1)
		  {  paoflg[j*GAMEMAPW+i]=1;bct=true; }
		}
		if(paoflg[(j+1)*GAMEMAPW+i]>=1)
		{  paoflg[j*GAMEMAPW+i]=1;bct=true;	}
      }
      else
      {
		if(paoflg[(j+1)*GAMEMAPW+i]>=1)
		{  paoflg[j*GAMEMAPW+i]=1;bct=true;	}
		if(paoflg[(j+1)*GAMEMAPW+i+1]>=1)
		{  paoflg[j*GAMEMAPW+i]=1;bct=true;	}
	  }
	}
	for(i=GAMEMAPW-3+blg;i>=0;i--)
	{
		if(paobuf[j*GAMEMAPW+i]==0)continue;
	    else
		{
			if(paoflg[j*GAMEMAPW+i]==0)
			  if(paoflg[j*GAMEMAPW+i+1]>=1)
				 paoflg[j*GAMEMAPW+i]=1;
	    }
	}
  }
}
char _MAPSTR::calcnextpao()
{
  char i;int s=0,p;
  p=rand()%paotj[11];
  for(i=1;i<9;i++)
  {
    s+=paotj[i];
    if(s>=p&&s!=0)
    {
      p=i;
      break;
    }
  }
  if(p<0||p>=9)p=rand()%8+1;
  return p;
}
bool _MAPSTR::clearpao(int x,int y,char clr,int *clrs,int dep)
{
	int tx,ty,txy,xy;char dx=0;
	xy=y*GAMEMAPW+x;
	paoflg[xy]=BVISIT;
	*clrs+=1;

	//左上
	tx=x;ty=y-1;
	if(bLong(ty)==false){tx-=1;dx=1;}
	txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH-dx)
	{
		if(paoflg[txy]!=BVISIT&&paoflg[txy]<VISITBOUND&&paobuf[txy]!=0)
		{
			if(clr==paobuf[txy])
				clearpao(tx,ty,clr,clrs,dep+1);
			else
			{if(paoflg[xy]<VISITBOUND)
			paoflg[xy]=VISITBOUND;
			else paoflg[xy]+=1;
			}
		}
	}
	//右上
	tx+=1;  txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH-dx)
	{
		if(paoflg[txy]!=BVISIT&&paoflg[txy]<VISITBOUND&&paobuf[txy]!=0)
		{
			if(clr==paobuf[txy])
				clearpao(tx,ty,clr,clrs,dep+1);
			else
			{if(paoflg[xy]<VISITBOUND)
			paoflg[xy]=VISITBOUND;
			else paoflg[xy]+=1;
			}
		}
	}
	
	//左
	tx=x-1;ty=y;if(bLong(ty)==false){dx=1;}
	txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH-dx)
	{
		if(paoflg[txy]!=BVISIT&&paoflg[txy]<VISITBOUND&&paobuf[txy]!=0)
		{
			if(clr==paobuf[txy])
				clearpao(tx,ty,clr,clrs,dep+1);
			else
			{if(paoflg[xy]<VISITBOUND)
			paoflg[xy]=VISITBOUND;
			else paoflg[xy]+=1;
			}
		}
	}
	//右
	tx+=2; txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH-dx)
	{
		if(paoflg[txy]!=BVISIT&&paoflg[txy]<VISITBOUND&&paobuf[txy]!=0)
		{
			if(clr==paobuf[txy])
				clearpao(tx,ty,clr,clrs,dep+1);
			else
			{if(paoflg[xy]<VISITBOUND)
			paoflg[xy]=VISITBOUND;
			else paoflg[xy]+=1;
			}
		}
	}
	//左下
	tx=x;ty=y+1;
	if(bLong(ty)==false){tx-=1;dx=1;}
	txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH-dx)
	{
		if(paoflg[txy]!=BVISIT&&paoflg[txy]<VISITBOUND&&paobuf[txy]!=0)
		{
			if(clr==paobuf[txy])
				clearpao(tx,ty,clr,clrs,dep+1);
			else
			{if(paoflg[xy]<VISITBOUND)
			paoflg[xy]=VISITBOUND;
			else paoflg[xy]+=1;
			}
		}
	}
	//右下
	tx+=1; txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH-dx)
	{
		if(paoflg[txy]!=BVISIT&&paoflg[txy]<VISITBOUND&&paobuf[txy]!=0)
		{
			if(clr==paobuf[txy])
				clearpao(tx,ty,clr,clrs,dep+1);
			else
			{if(paoflg[xy]<VISITBOUND)
			paoflg[xy]=VISITBOUND;
			else paoflg[xy]+=1;
			}
		}
	}
	if(dep==0)
	{
		if((*clrs)>=3)return true;
	}
	return false;
}
bool _MAPSTR::checkbdown(int x,int y,char flg ,char *fgs,char *s)
{
	int tx,ty,txy,xy;char k=0,ts=0;bool nbdown=false,tp=false;
	ts=*s;
	xy=y*GAMEMAPW+x;
	
	//左上
	tx=x;ty=y-1;
	if(bLong(ty)==false)tx-=1;
	txy=ty*GAMEMAPW+tx;
	
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH)
	{
		if(paobuf[txy]!=0&&paoflg[txy]<VISITFLG)
		{
			if(paobuf[xy]==0)
			{
				paoflg[txy]=VISITFLG+flg;
				tp=checkbdown(tx,ty,VISITFLG+flg,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
				if(nbdown==false)
				{
					fgs[ts+k]=VISITFLG+flg;k++;*s=k;
				}
			}
			else
			{
				paoflg[txy]=flg;
				tp=checkbdown(tx,ty,flg,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
			}
		}
		else if(paobuf[xy]!=0&&paobuf[txy]==0&&paoflg[txy]>=VISITBOUND)
			paoflg[txy]-=1;//=BVISIT;
	}
	//右上
	tx+=1;txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH)
	{
		if(paobuf[txy]!=0&&paoflg[txy]<VISITFLG)
		{
			if(paobuf[xy]==0)
			{
				paoflg[txy]=VISITFLG+flg+1;
				tp=checkbdown(tx,ty,VISITFLG+flg+1,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
				if(nbdown==false)
				{
					fgs[ts+k]=VISITFLG+flg+1;k++;*s=k;
				}
			}
			else
			{
				paoflg[txy]=flg;
				tp=checkbdown(tx,ty,flg,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
			}
		}
		else if(paobuf[xy]!=0&&paobuf[txy]==0&&paoflg[txy]>=VISITBOUND)
			paoflg[txy]-=1;//BVISIT;
	}
	//左
	tx=x-1;ty=y;
	txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH)
	{
		if(paobuf[txy]!=0&&paoflg[txy]<VISITFLG)
		{
			if(paobuf[xy]==0)
			{
				paoflg[txy]=VISITFLG+flg+2;
				tp=checkbdown(tx,ty,VISITFLG+flg+2,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
				if(nbdown==false)
				{
					fgs[ts+k]=VISITFLG+flg+2;k++;*s=k;
				}
			}
			else
			{
				paoflg[txy]=flg;
				tp=checkbdown(tx,ty,flg,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
			}
		}
		else if(paobuf[xy]!=0&&paobuf[txy]==0&&paoflg[txy]>=VISITBOUND)
			paoflg[txy]-=1;//BVISIT;
	}
	//右
	tx+=2; txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH)
	{
		if(paobuf[txy]!=0&&paoflg[txy]<VISITFLG)
		{
			if(paobuf[xy]==0)
			{
				paoflg[txy]=VISITFLG+flg+3;
				tp=checkbdown(tx,ty,VISITFLG+flg+3,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
				if(nbdown==false)
				{
					fgs[ts+k]=VISITFLG+flg+3;k++;*s=k;
				}
			}
			else
			{
				paoflg[txy]=flg;
				tp=checkbdown(tx,ty,flg,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
			}
		}
		else if(paobuf[xy]!=0&&paobuf[txy]==0&&paoflg[txy]>=VISITBOUND)
			paoflg[txy]-=1;//BVISIT;
	}
	//左下
	tx=x;ty=y+1;
	if(bLong(ty)==false)tx-=1;
	txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH)
	{
		if(paobuf[txy]!=0&&paoflg[txy]<VISITFLG)
		{
			if(paobuf[xy]==0)
			{
				paoflg[txy]=VISITFLG+flg+4;
				tp=checkbdown(tx,ty,VISITFLG+flg+4,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
				if(nbdown==false)
				{
					fgs[ts+k]=VISITFLG+flg+4;k++;*s=k;
				}
			}
			else
			{
				paoflg[txy]=flg;
				tp=checkbdown(tx,ty,flg,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
			}
		}
		else if(paobuf[xy]!=0&&paobuf[txy]==0&&paoflg[txy]>=VISITBOUND)
			paoflg[txy]-=1;//BVISIT;
	}
	//右下
	tx+=1; txy=ty*GAMEMAPW+tx;
	if(tx>=0&&tx<GAMEMAPW&&ty>=0&&ty<GAMEMAPH)
	{
		if(paobuf[txy]!=0&&paoflg[txy]<VISITFLG)
		{
			if(paobuf[xy]==0)
			{
				paoflg[txy]=VISITFLG+flg+5;
				tp=checkbdown(tx,ty,VISITFLG+flg+5,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
				if(nbdown==false)
				{
					fgs[ts+k]=VISITFLG+flg+5;k++;*s=k;
				}
			}
			else
			{
				paoflg[txy]=flg;
				tp=checkbdown(tx,ty,flg,fgs,s);
				if(ty==0||tp==true)
					nbdown=true;
			}
		}
		else if(paobuf[xy]!=0&&paobuf[txy]==0&&paoflg[txy]>=VISITBOUND)
			paoflg[txy]-=1;//BVISIT;
	}
	if(paobuf[xy]==0)
		*s=(*s)+ts;
	return nbdown;
}

void _MAPSTR::loadmap(char mapn)
{
	int i,adr;char k;
	memset(paotj,0,12);
	memset(paobuf,0,GAMEMAPW*GAMEMAPH*sizeof(char));
	goodtp=0;canbgood=1;
	blong=true;//假设每张地图都为true;
	adr=mapn*8*11;
	for(i=0;i<GAMEMAPW*11;i++)
	{
		k=paodat[adr+i];
		paobuf[i]=k;//paodat[adr+i];
		if(k!=0&&k<9)
		{
			paotj[k]+=1;
			paotj[11]+=1;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void _player::usegdpoint(char ps)
{
	//Point2 s,char typ,char clr,Point2 s1,char pl,char pl1
	if(gdt->gameplayers!=2)return;
	eft->startgoodmoveani(goodps+Point2(0,0),2,1,Point2(0,0),m_rpos,ps);
}

void _player::nextlevel(char s)
{
	pointangl=0;
	level+=s;
#ifndef _DEBUG_
	if(level>2)showtipl=false;
#endif
	mapbf.loadmap(level);
	curpaoclr=mapbf.calcnextpao();
	nextpaoclr=mapbf.calcnextpao();
	tpls=10;gettipline(Point2(gwinpos.x+lunchpos.x+cos((pointangl-90)*Pi)*30,gwinpos.y+lunchpos.y+sin((pointangl-90)*Pi)*30),pointangl,ttl,&tpls);
	eft->startreadygoani(gwinpos+gwinwh/2-Point2(30,0),level+1,m_rpos);
	resetwall();
}

void _player::startplay()
{
	////////////////game clear ////////
	setstate(PST_GAMING);
	mapbf.loadmap(level);
	curpaoclr=mapbf.calcnextpao();
	nextpaoclr=mapbf.calcnextpao();
	tpls=10;
	gettipline(Point2(gwinpos.x+lunchpos.x+cos((pointangl-90)*Pi)*30,gwinpos.y+lunchpos.y+sin((pointangl-90)*Pi)*30),pointangl,ttl,&tpls);
	m_timer[TIM_NOINPUT]=tim->AddTimer(20);
	m_timer[TIM_NOINPUT]->Setsycle();
	m_timer[TIM_DOWNMAP]=tim->AddTimer( 30-gdt->gameeasyhard*10);//
	m_timer[TIM_DOWNMAP]->Setsycle();
	m_timer[TIM_GAMETICK]=tim->AddTimer(60*6);
	m_timer[TIM_GAMETICK]->Setsycle();
	m_timer[TIM_MAKEGD]=tim->AddTimer(20);
//	m_timer[TIM_MAKEGD]->Setsycle();
	m_timer[TIM_POINT]=tim->AddTimer(20);
	m_timer[TIM_POINT]->Reset();
	m_timer[TIM_POINT]->SetTimeStart(false);
};
void _player::doclearpao(int x,int y,char clr)
{
	char s=0,k=0,t=0,flgk[10];int i,cls=0;bool bclr=false;
	Point2 ss;
	mapbf.clearflg();
	if(clr<9)
	{
		bclr=mapbf.clearpao(x,y,clr,&cls);//此时可以播放动画(加延时)
		if(bclr==true)
		{
			statescr+=cls;
			for(i=0;i<GAMEMAPW*GAMEMAPH;i++)
			{
				if(mapbf.paoflg[i]==0)continue;
				else if(mapbf.paoflg[i]==BVISIT|| mapbf.paoflg[i]>=VISITBOUND)
				{
					ss=getvirtpos(i%GAMEMAPW,i/GAMEMAPW);
					eft->startclearpaoani(ss,mapbf.get(i));
					if(i==mapbf.goodps && mapbf.goodtp!=0)
					{
						eft->startgoodmoveani(ss,1,mapbf.goodtp,goodps+Point2( mapbf.goodtp*8,0),m_rpos);
						mapbf.readyforgood();
					}
					mapbf.clrpao(i);
//					pclr=mapbf.paobuf[i];	
//					if(pclr>0&&pclr<=9)
//						if(mapbf.paotj[pclr]>0)
//							mapbf.paotj[pclr]-=1;
//						mapbf.paobuf[i]=0;
						
						eft->startscroani(ss,3,clr);
				}
			}
		}
		/*
		for(i=0;i<11*8;i++)
		{
		flg=paoflg[i];
		if(flg<VISITBOUND||flg>=VISITFLG)continue;
		checkbdown(i%8,i/8,k,flgk,&s);k+=6;
		i--;
		break;
		}
		
		  //    print_num(30,400,s,3);
		  //    for(i=0;i<s;i++)
		  //      print_num(30+i*30,420,flgk[i],3);
		  }
		*/
	}
	mapbf.clearflg();
    mapbf.checkbdown1();
	
	for(i=GAMEMAPW;i<GAMEMAPW*GAMEMAPH;i++)//清除可下落泡，并播放动画
	{
		//    for(j=0;j<s;j++)
		//    {
		//      if(flgk[j]==paoflg[i])
		if((mapbf.paoflg[i]==0) && (mapbf.paobuf[i]!=0 ))
		{
			//drawpao1((int)(i%8),(int)(i/8),3);
			ss=getvirtpos(i%GAMEMAPW,(int)(i/GAMEMAPW));
			eft->startdownpaoani(ss,i,mapbf.paobuf[i]);
			if(i==mapbf.goodps)mapbf.readyforgood();
			mapbf.clrpao(i);//消,动画
		}
		//    }
	}

	if(getgamereslt())
	{
		timeused=m_timer[TIM_GAMETICK]->GetTime();
		eft->startconcldsta(m_rpos);
		stateclear();
	}
}
void _player::downwall()
{
	if(curtheigh>GAMEMAPH-2)return;
	curtheigh+=1;
	mappos.y=curtheigh * paosz.y * 2 ;
	tpls=10;
	gettipline(Point2(gwinpos.x+lunchpos.x+cos((pointangl-90)*Pi)*30,gwinpos.y+lunchpos.y+sin((pointangl-90)*Pi)*30),pointangl,ttl,&tpls);
}
void _player::drawtipline(Point2 o, float alp,Point2 *tl,char siz,char cr)
{
	Point2 sta=o+Point2(cos((alp-90)*Pi)*30,sin((alp-90)*Pi)*30);
	Vector2 v=tl[0]-sta;v.Unit();
	Point2 tp;
	float l=GetLength(sta,tl[0]),st=(cr==1)?8:12;
	float j=0;
	int dt=(gettimetick()/20)%(int)st;
	if(tl[0].x!=0)
	{
		for(j=0;j<l-6;j+=st)
		{
			tp=sta+v*(j+dt);
			Circle(tp.x,tp.y, cr,2+(dt+(int)j)%9 *7);
		}
		for(int i=0;i<siz-1;i++)
		{
			v=tl[i+1]-tl[i];v.Unit();
			l=GetLength(tl[i],tl[i+1]);
			for(j=0;j<l-6;j+=st)
			{
				tp=tl[i]+v*(j+dt);
				Circle(tp.x,tp.y,cr,2+(dt+(int)j)%9*7);
			}
		}
	}
}

void _player::lunchpao()
{
  if(psta==PST_LUNCHING||psta==PST_STATEEND||psta==PST_LOSE)return;
  if(psta!=PST_GAMING)return;
  float angle=pointangl-90;
  psta=PST_LUNCHING;
  lunchclr=curpaoclr;
  curpaoclr=99;
  paopos=Point2(gwinpos.x+lunchpos.x,gwinpos.y+lunchpos.y);
  paoinc=Vector2(cos(angle*Pi)*2,sin(angle*Pi)*2);
}
void _player::runlunch()
{
  if(psta!=PST_LUNCHING)return;
  Point2 vs,rs,ts;int j,k;bool bcheckd=false;
  paopos=paopos+paoinc;
  

/*  
  rs=getrealpos(paopos.x,paopos.y);
  for(int i=0;i<6;i++)
  {
	  vs=mapbf.getaroundp(rs.x,rs.y,i);
	  if(vs.x<0||vs.x>=GAMEMAPW||vs.y<0||vs.y>=GAMEMAPH)continue;
	  if(!mapbf.get(vs.y*GAMEMAPW+vs.x))continue;
	  ts=getvirtpos(vs.x,vs.y);
	  vs=ts-paopos;
	  if( vs.Mod() < (2*paorad-2) )
		  bcheckd=true;		  
  }
  if(paopos.y<=(gwinpos.y+mappos.y+2+paorad/2)) bcheckd=true;
*/
  for(int i=GAMEMAPW*GAMEMAPH-1;i>=0;i--)
  {
    if(mapbf.get(i)==0)continue;
    vs=getvirtpos(i%GAMEMAPW,i/GAMEMAPW);
    if( (paopos.y-vs.y)>2*paorad*2 )break;
    vs=vs-paopos;
    if(vs.Mod()<2*paorad-2 || paopos.y<=(gwinpos.y+mappos.y+2+paorad/2))
	{	
		bcheckd=true; rs=getrealpos(paopos.x,paopos.y); break; 
	}
  }
  if(bcheckd)
  {
	  psta=PST_GAMING;
	  curpaoclr=nextpaoclr;
	  nextpaoclr=mapbf.calcnextpao();
  	  if(rs.x<0||rs.x>=GAMEMAPW||rs.y<0||rs.y>=GAMEMAPH) return;
	  if(!mapbf.bLong(rs.y))
		  if(rs.x==GAMEMAPW-1) rs.x-=1;
	  mapbf.addpao((int)rs.y*GAMEMAPW+(int)rs.x,lunchclr);
	  doclearpao(rs.x,rs.y,lunchclr); 
	  tpls=10;gettipline(Point2(gwinpos.x+lunchpos.x+cos((pointangl-90)*Pi)*30,gwinpos.y+lunchpos.y+sin((pointangl-90)*Pi)*30),pointangl,ttl,&tpls);
	  
	  for(j=0;j<6;j++)
	  {
		  vs=mapbf.getaroundp(rs.x,rs.y,j);
		  if(vs.x<0||vs.x>GAMEMAPW||vs.y<0||vs.y>GAMEMAPH)continue;
		  k=mapbf.get(vs.y*GAMEMAPW+vs.x);
		  if(k==9)//fire
		  {
			  eft->startfiregoodani(getvirtpos(vs.x,vs.y),vs.y*GAMEMAPW+vs.x,m_rpos);
			  break;
		  }
		  else if(k==19)//elec
		  {
			  eft->startelecgoodani(getvirtpos(vs.x,vs.y),vs.y*GAMEMAPW+vs.x,m_rpos);
			  break;
		  }
		  else if(k==29)//water
		  {
			  eft->startwatergoodani(getvirtpos(vs.x,vs.y),vs.y*GAMEMAPW+vs.x,m_rpos);
			  break;
		  }
	  }
	  if(checktuchline())
	  {
		  setstate(PST_LOSE);
		  eft->startloseani(m_rpos);
	  }
	  return;//break;
   }


  if(paopos.x<=(gwinpos.x+4+paorad/2)||paopos.x>=(gwinpos.x-(4+paorad/2))+gwinwh.x)paoinc.x=-paoinc.x;
 // if(paopos.y<=(gwinpos.y+mappos.y+2+paorad/2)||paopos.y>=(gwinpos.y-(2+paorad/2))+gwinwh.y)paoinc.y=-paoinc.y;
  Circle(paopos.x,paopos.y,paorad,1+(lunchclr-1)*7);
}
int _player::gettipline(Point2 o,float alp,Point2 *tl,char* siz)
{
	float R=paorad,W=gwinwh.x-2*(4+paorad/2),H=gwinwh.y-2*(4+paorad/2),lowest=0,tp,mr=0;Point2 col,pl[4];Vector2 le,l,ol;
	int slen=0,i,j,k,i1;Point2 v0,ov0,cp;char nl=99;bool checked=false,bfound=false;
	Point2 pos=gwinpos+Point2(4+paorad/2,4+paorad/2)+mappos;
	alp=alp-90;
	l=Vector2(cos(alp*Pi),sin(alp*Pi));
	l.Unit();ol=l;ov0=o;v0=o;
	pl[0]=pos+Point2(0,H-mappos.y);
	pl[1]=pos+Point2(0,0);
	pl[2]=pos+Point2(W,0);
	pl[3]=pos+Point2(W,H-mappos.y);
	//  for(i=0;i<4;i++)Circle(pl[i].x,pl[i].y,3,3);
	
	for(i=0;i<*siz;i++)
	{
		checked=false;
		bfound=false;
		ov0=v0;ol=l;
		for(j=0;j<3;j++)
		{
			if(nl==j )continue;
			v0=GetInsectIn2L(ov0,ol,pl[j],(Vector2)(pl[j+1]-pl[j]));//求交点
			if(v0.x==0&&v0.y==0){*siz=i;break;}
			if((int)v0.x<(int)pos.x||(int)v0.x>(int)(pos.x+W)||((int)v0.y-(int)pos.y)<0||(int)v0.y>(int)(pos.y+H))continue;
			else
			{
				l=GetVecInvers(ol,pl[j]-pl[j+1]);//求反射
#ifdef _DEBUG_
DrawVec2(v0,l,18);
#endif
				nl=j;
				bfound=true;
				break;
			}
		}
		float tt1=0,tt=9999.0;
		for(k=GAMEMAPW*GAMEMAPH-1;k>=0;k--)
		{
			if(mapbf.get(k)==0)continue;
			cp=getvirtpos(k%GAMEMAPW,k/GAMEMAPW);
			if(tp=GetLD(cp,ov0,v0) < (R+2) )
			{
				GetInsectLS(ov0,v0-ov0,cp,10.0,&tt1);
				if(tt1==0)continue;
				if(tt1<tt)
				{
					tt=tt1;
					mr=tp;
					col=cp;
					i1=k/GAMEMAPW;
					checked=true;
				}
			}
		}
		if(checked==true)
		{
			v0 = GetInsectLS(ov0,v0-ov0,col,10.0);//取线圆交点
			tl[i]=v0;
			*siz=i+1;
			return 0;
		}
		if(bfound==true)
		{
			tl[i]=v0;
			if((int)v0.y==(int)pl[2].y)
			{
				*siz=i+1;
				return 0;
			}
		}
		else
		{
			*siz=i;
			break;
		}
	}
	le=tl[0]-o;
	for(i=0;i<*siz-1;i++)
	{
		slen+=le.Mod();
		le=tl[i+1]-tl[i];
	}
	return slen;
}
void _player::drawgameinfo()
{
	//  FillLine(gwinpos.x,gwinpos.y,gwinpos.x+164,gwinpos.y+230,0);
	Line_(gwinpos.x+gwinwh.x,gwinpos.y,gwinpos.x+gwinwh.x,gwinpos.y+gwinwh.y,2,false);
	Line_(gwinpos.x-52,gwinpos.y,gwinpos.x-2,gwinpos.y+gwinwh.y,2,true);
	print_string(gwinpos.x+72,gwinpos.y+230,3," PaoPaoLong",0);
	print_string(gwinpos.x-50,gwinpos.y+5,3,"SCORE:",0);
	print_string(gwinpos.x-50,gwinpos.y+15,8,"000000",0);
	print_string(gwinpos.x-50,gwinpos.y+50,3,"LEVEL:",0);
	print_string(gwinpos.x-50,gwinpos.y+65,8,"000000",0);
}

void _player::drawbkgrdinloop()
{
	drawgameinfo();

	Circle(gwinpos.x+lunchpos.x,gwinpos.y+lunchpos.y,16,23);
	if(curpaoclr!=99)
		Circle(gwinpos.x+lunchpos.x,gwinpos.y+lunchpos.y,paorad,1+(curpaoclr-1)*7);
	Circle(gwinpos.x+lunchpos.x/2,gwinpos.y+lunchpos.y,paorad,1+(nextpaoclr-1)*7);
	Line_(gwinpos.x,gwinpos.y+lunchpos.y-10,gwinpos.x+gwinwh.x,gwinpos.y+lunchpos.y-10,23,false);
	drawpoint(pointangl,bbreakpt?99:9);

	//goods;
	int i;
	print_string(goodps.x-2,goodps.y-10,2,"Goods:");
	for(i=0;i<5;i++)
	{
		Line_(goodps.x+i*9,goodps.y, goodps.x+6+i*9,goodps.y+6, 9, true);
		if(goods[i]!=0)
			FillLine(goodps.x+i*9+1,goodps.y+1, goodps.x+6+i*9+1,goodps.y+6+1,(i+1)*7+1);
	}
	for(i=0;i<2;i++)
	{
		Line_(goodps.x+i*9,goodps.y+9, goodps.x+6+i*9,goodps.y+6+9, 9, true);
		if(goods[i]!=0)
			FillLine(goodps.x+i*9+1,goodps.y+1, goodps.x+6+i*9+1,goodps.y+6+1,(i+1)*7+1);
	}
	
	drawwall();

	drawmap();
	
	if(showtipl)
		drawtipline(gwinpos+lunchpos,pointangl,ttl,tpls, (gdt->gameplayers==1)? 2:1);
	
	runlunch();

	if(getstate()==PST_LOSE)return;
//#ifndef _DEBUG_	
	int tmp;
	if(!m_timer[TIM_POINT]->IsTimeOver())
		bbreakpt=true;
	else bbreakpt=false;

	if(getstate()==PST_GAMING||getstate()==PST_LUNCHING)
	{
		if(m_timer[TIM_MAKEGD]->IsTimeOver())
		{
			mapbf.addgood(rand()%5+1);
			m_timer[TIM_MAKEGD]->Reset();
			m_timer[TIM_MAKEGD]->SetMaxTime(rand()%20+1);
			m_timer[TIM_MAKEGD]->SetTimeStart();
		}
	}

	tmp=m_timer[TIM_NOINPUT]->GetTime();
	if(tmp>13 && tmp%2==0)
		drawtime((20-tmp)/2);	
	if(tmp==19)
	{
		lunchpao();
		m_timer[TIM_NOINPUT]->Reset();
	}
	tmp=m_timer[TIM_DOWNMAP]->GetTime();
	int tp=30 - gdt->gameeasyhard * 10;
	if(tmp>=(tp-3)&&tmp<(tp-1))
		wakemap();
	else 
	{
		wakpos=Point2(0,0);
		if(tmp>=(tp-1))
		{
			if(gdt->gamemode==GTP_CHLG)mapbf.downpao();
			else downwall();
			if(checktuchline())
			{
				eft->startloseani(m_rpos);
			}
			m_timer[TIM_DOWNMAP]->Reset();
		}
	}

//#endif
	
}
void _player::drawpoint(float angl,char c)
{
	Point2 xy,xy1,xy2,ol=Point2(gwinpos.x+lunchpos.x,gwinpos.y+lunchpos.y);
	float l=30;	angl=angl-90;
	if(c==99){l=12;c=9;}
	xy.x=cos((float)(angl)*Pi)*l;
	xy.y=sin((float)(angl)*Pi)*l;
	xy1.x=cos((float)(angl-30)*Pi)*6;
	xy1.y=sin((float)(angl-30)*Pi)*6;
	xy2.x=cos((float)(angl+30)*Pi)*6;
	xy2.y=sin((float)(angl+30)*Pi)*6;
	xy=xy+ol;xy1=xy1+ol;xy2=xy2+ol;
	Line_(ol.x,ol.y,xy1.x,xy1.y, c ,false);
	Line_(ol.x,ol.y,xy2.x,xy2.y, c ,false);
	Line_(xy.x,xy.y, xy1.x,xy1.y,c ,false);
	Line_(xy.x,xy.y, xy2.x,xy2.y,c ,false);
}
void _player::drawpao(float x,float y,char clr)
{
	if(clr>=9)
	{
		Circle(x,y,paorad+(sin((double)gettimetick()/50)*1.1),1+rand()%9*7);
		return;
	}
	Circle(x,y,paorad,1+(clr-1)*7);
}
void _player::drawwall()
{
	float rh;
	rh=paosz.y *2 * curtheigh;
	Line_(gwinpos.x+4,gwinpos.y-4, gwinpos.x+4, gwinpos.y+rh-4,9,false);
	Line_(gwinpos.x+gwinwh.x-4, gwinpos.y-4, gwinpos.x+gwinwh.x-4, gwinpos.y+rh-4,9,false);
	Line_(gwinpos.x+4+30,gwinpos.y-4, gwinpos.x+4+30, gwinpos.y+rh-4,9,false);
	Line_(gwinpos.x+gwinwh.x-4-30, gwinpos.y-4, gwinpos.x+gwinwh.x-4-30, gwinpos.y+rh-4,9,false);
	Line_(gwinpos.x+2,gwinpos.y+rh-4, gwinpos.x+gwinwh.x-2, gwinpos.y+rh-2,9,true);
}
void _player::drawtime(int t)
{
	float i,x,y,r=paorad;
	Point2 ps=gwinpos+Point2(paorad,lunchpos.y-20);
	print_num(ps.x-3,ps.y-3,t,23);
	for(i=0;i<360;i++)
	{
		x=cos(i*Pi)*(r+sin(i*t*2*Pi)*r/3)+ps.x;
		y=sin(i*Pi)*(r+sin(i*t*2*Pi)*r/3)+ps.y;
		pset(x,y,23);
	}
}
void _player::wakemap()
{
	wakpos=Point2( sin((double)gettimetick()/40)*2 ,0);
}
void _player::drawreadygo()
{
	int t;
	for(int i=1;i<4;i++)
	{
	   t=(gettimetick()/2000)%5;
       FillLine(gwinpos.x+20,gwinpos.y+i*40,gwinpos.x+143,gwinpos.y+i*40+30,1+6*7+t+1);
	}
}
void _player::drawmap()
{
    int i,j;char k;Point2 tp;
	for(j=0;j<GAMEMAPH;j++)
		for(i=0;i<GAMEMAPW- abs(mapbf.blong-(j+1)%2) ;i++)
		{
			tp=getvirtpos(i,j);
			mapbf.get(i,j,&k);
			if(k)drawpao(tp.x,tp.y,k);
		}
	if(mapbf.goodtp!=0)
	{
		tp=getvirtpos(mapbf.goodps%GAMEMAPW,mapbf.goodps/GAMEMAPW);
		FillLine(tp.x-3,tp.y-3, tp.x+3,tp.y+3,mapbf.goodtp*7+1);
	}


/*  //留着，以后知道，曾用过这个不合时宜东西
    int k=0;Point2 p,o=Point2(-3,3),q,r; 
	r=q=o;		
    for(j=0;j<GAMEMAPH;j++)
    {
		q=r;
		for(i=0;i<GAMEMAPW-j%2;i++)
		{
			p=Logic(q.x,q.y,20,20,false,true)+pos;
			q.x+=1;q.y-=1;
			if(gamemode==1)
				j= (((int)j+(GAMEMAPH-(int)curtheigh%GAMEMAPH))%GAMEMAPH) ;
			if(k=paobuf[j*GAMEMAPW+i])
				drawpao(p.x,p.y,k);
		}
		if(j%2)r.y+=1;
		else r.x+=1;
		q=r;
	}
*/
}
//////////////////////////////////////////////////////////////////////////////////////////
class PaoPaoLong
{
public:
  GameEffect Eft;
  CManager_Time MTime;
  _gamedata gdata;
  _player	player[GAMEMAXP];
  int mnuidx;
  char gamehard,continuemnu;
  
  PaoPaoLong()
  {
//	gameinit();
  };
public:
  void gameloop();
  void gameinputloop();
  void gameinit()
  {
	  initdevice();

	  char ct=1;
	  lineclr(255,0,0,  0,0,0,  ct+0*7, ct+1*7);
	  lineclr(255,255,0, 0,0,0,  ct+1*7, ct+2*7);
	  lineclr(80,80,255,  0,0,0,  ct+2*7, ct+3*7);
	  lineclr(0,255,0,  0,0,0,  ct+3*7, ct+4*7);
	  lineclr(255,255,255, 0,0,0, ct+4*7, ct+5*7);
	  lineclr(255,177,88, 0,0,0, ct+5*7, ct+6*7);
	  lineclr(255,0,255, 0,0,0,  ct+6*7, ct+7*7);
	  lineclr(88,177,255, 0,0,0, ct+7*7, ct+8*7);
	  lineclr(0,255,255, 0,0,0,  ct+8*7, ct+9*7);
	  //----------------------------------------------------
		
	  mnuidx=0;
	  continuemnu=0;
	  gamehard=0;

	  gdata.init();
	  for(ct=0;ct<GAMEMAXP;ct++)
	  {
		  player[ct].init();
		  player[ct].gdt=&gdata;
		  player[ct].eft=&Eft;
		  player[ct].tim=&MTime;
		  player[ct].m_rpos=ct;
	  }
	  Eft.gdt=&gdata;
	  Eft.pdt=player;
      Eft.startgamexumuani();
  };
  void gameclear()
  {
	  gdata.clear();
	  for(int ct=0;ct<GAMEMAXP;ct++)
	  {	 player[ct].stateclear();
	  player[ct].level=1;
	  }
	  Eft.Effectdestroy();
      Eft.startgamexumuani();
  };
  void gamedestroy()
  {
	  gdata.release();
	  for(int ct=0;ct<GAMEMAXP;ct++)
		  player[ct].release();
	  
  };
  //game logic
  void nextlevel();
  void gamepause();
  void gamexumu();
  void gameweimu();
  void gamewin();
  void gamelose();
  void gamestart();
  void gameend();

  void drawbkground();
  void drawfrtground();
  void drawcompanyinfo();

  void drawcontinumenu();
  void drawstartmenu();
  void drawpausemenu();
  void drawhard();
  void drawconclut();//得分总结画面
  void clear();
};
void PaoPaoLong::nextlevel()
{
	player[0].nextlevel();
}
void PaoPaoLong::gamestart()
{
	int i;
//	gameclear();
	gdata.setstate(GST_GAMING);
	switch(gdata.gameplayers)
	{
	case 1:
		{
			player[0].lunchpos=PLY0LUNCHXY;
			player[0].gwinpos=PLY0ORGXY;
			player[0].gwinwh=PLY0ORGWH;
			player[0].paosz=PLY0PAOWH;
			player[0].paorad=PLY0PAOR;
			player[0].goodps=PLY0ORGXY+Point2(-48,140);
		}
		break;
	case 2:
		{
			player[0].lunchpos=PLY1LUNCHXY;
			player[0].gwinpos=PLY1ORGXY;
			player[0].gwinwh=PLY1ORGWH;
			player[0].paosz=PLY1PAOWH;
			player[0].paorad=PLY1PAOR;
			player[0].goodps=PLY1ORGXY+Point2(-48,130);
			
			player[1].lunchpos=PLY2LUNCHXY;
			player[1].gwinpos=PLY2ORGXY;
			player[1].gwinwh=PLY2ORGWH;
			player[1].paosz=PLY2PAOWH;
			player[1].paorad=PLY2PAOR;
			player[1].goodps=PLY2ORGXY+Point2(-48,130);
			
		}
		break;
	}
	for(i=0;i<gdata.gameplayers;i++)
		player[i].startplay();
}
void PaoPaoLong::drawpausemenu()
{
	print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+110,2,"Paused",0);
}
void PaoPaoLong::drawhard()
{
	print_string(gdata.GameWinpos.x+130,gdata.GameWinpos.y+80,2,"Easy",0);
	print_string(gdata.GameWinpos.x+130,gdata.GameWinpos.y+80+40,2,"Normal",0);
	print_string(gdata.GameWinpos.x+130,gdata.GameWinpos.y+80+80,2,"Hard",0);

	print_string(gdata.GameWinpos.x+120,gdata.GameWinpos.y+80+mnuidx*40,2,"*",0);
	
//	print_string(gdata.GameWinpos.x+30,gdata.GameWinpos.y+250,4,"Internet",0);
//	print_string(gdata.GameWinpos.x+30,gdata.GameWinpos.y+250,4,"Local",0);
}
void PaoPaoLong::drawcontinumenu()
{
	print_string(gdata.GameWinpos.x+100,gdata.GameWinpos.y+100,2,"Continue? Y/N",0);
//	print_string(gdata.GameWinpos.x+30,gdata.GameWinpos.y+280,4,"Game Over",0);
}
void PaoPaoLong::drawstartmenu()
{
	print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+100,2,"---Game Start---",0);
	print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+120,3,"   Single",0);
	print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+130,3,"   Mutiple",0);
	print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+150,2,"---Game Mode---",0);
	print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+170,3,"   Stroy",0);
	print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+180,3,"   Challenge",0);
	if(gdata.gamemode==0)
		print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+170,2,"  *",0);
	else if(gdata.gamemode==1)
		print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+180,2,"  *",0);
	if(gdata.gameplayers==1)
		print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+120,2,"  *",0);
	else if(gdata.gameplayers==2)
		print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+130,2,"  *",0);
	switch(mnuidx)
	{
	case 0:{print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+120,9,"  *",0);break;}
	case 1:{print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+130,9,"  *",0);break;}
	case 2:{print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+170,9,"  *",0);break;}
	case 3:{print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+180,9,"  *",0);break;}
		
	}
}
void PaoPaoLong::drawconclut()
{
}

static bool bxumu=true;
void PaoPaoLong::gamexumu()
{
	int tm=(gettimetick()/700)%2;
	print_string(gdata.GameWinpos.x+90,gdata.GameWinpos.y+200,tm*2,"Press Enter to skip",0);
	if(bxumu==true)
	{
		bxumu=false;
	}
}
void PaoPaoLong::gameweimu()
{
}

void PaoPaoLong::drawcompanyinfo()
{
	print_string(gdata.GameWinpos.x,gdata.GameWinpos.y-10,33,"BinfenSoft Studio(C)",0);
	//  print_string(0,460,33,"For more games pls visit my website: http://spaces.msn.com/members/binbinbin1983",0);
	
}

void PaoPaoLong::gameloop()
{
	drawbkground();//
	drawcompanyinfo();
	MTime.LoopTimeManager();

	int sta=gdata.getstate();
	switch(sta)
	{
	case GST_CSLXUMU:
		{
			gdata.setstate(GST_XUMU);
			break;
		}
	case GST_XUMU:
		{
			gamexumu();
			Eft.Effectloop();
			break;
		}
	case GST_READY:
		{
			if(gamehard==0)
				drawstartmenu();
			else drawhard();
			break;
		}
	case GST_GAMING:
		{
			int i;
			for(i=0;i<gdata.gameplayers;i++)
				player[i].drawbkgrdinloop();
			break;
		}
	case GST_PAUSE:
		{
			if(continuemnu==0)
				drawpausemenu();
			else drawcontinumenu();
			break;
		}
	case GST_GAMFINAL:
		{
			drawcontinumenu();
			break;
		}
	case GST_GAMEEND:
		{
			
			break;
		}
	case GST_CONCLUT:
		{
			drawconclut();
			break;
		}
	case GST_CSLWEIMU:break;
	default:break;
	}

#ifndef _DEBUG_
	if(sta!=GST_PAUSE)
#endif
		Eft.Effectloop();
}
//int agl1=0;

bool tmpbool=true;
void PaoPaoLong::gameinputloop()
{
	switch(gdata.getstate())
	{
	case GST_XUMU:
		{
			if(getkey(VK_SPACE,true)||getkey(VK_RETURN,true)){gdata.setstate(GST_READY);}
			if(getkey(VK_ESCAPE,true))
				PostMessage(hWnd, WM_CLOSE, NULL, NULL);
			break;
		}
	case GST_READY:
		{
			if(!gamehard)
			{
				
				if(getkey(VK_DOWN,true)){mnuidx+=1;if(mnuidx>3)mnuidx=0;}
				if(getkey(VK_UP,true)){mnuidx-=1;if(mnuidx<0)mnuidx=3;}
				if(getkey(VK_RETURN,true))
				{
					if(mnuidx==2)gdata.gamemode=GTP_STORY;
					else if(mnuidx==3)gdata.gamemode=GTP_CHLG;
					else if(mnuidx==0){gdata.gameplayers=1;gamehard=1;}
					else if(mnuidx==1){gdata.gameplayers=2;gamehard=1;}
				}
			}
			else
			{
				if(getkey(VK_DOWN,true)){mnuidx+=1;if(mnuidx>2)mnuidx=0;}
				if(getkey(VK_UP,true)){mnuidx-=1;if(mnuidx<0)mnuidx=2;}
				if(getkey(VK_RETURN,true))
				{	gamehard=0;
					if(mnuidx==0)gdata.gameeasyhard=0;
					else if(mnuidx==1)gdata.gameeasyhard=1;
					else if(mnuidx==2)gdata.gameeasyhard=2;
					gamestart();
				}
			}
			break;
		}
	case GST_GAMING:
		{
#ifdef _DEBUG_
			if(getkey('G'))
			{
				int gt=rand()%6+1;
				int pp=player[0].mapbf.addgood(gt);
				if(pp>0)Eft.startgoodmoveani(player[0].getvirtpos(pp%GAMEMAPW,pp/GAMEMAPW),0,gt);
			}
#endif
			if(getkey('1',true)){player[1].usegdpoint(0);}
			if(getkey(VK_NUMPAD1,true)){player[0].usegdpoint(1);}
			if(getkey(VK_ESCAPE,true)){gdata.setstate(GST_PAUSE);continuemnu=1;}
			if(getkey(VK_LEFT)){player[0].drivepoint(-1);}
			if(getkey(VK_RIGHT)){player[0].drivepoint(1);}
			if(getkey('T')){player[0].toggltipl();}
			if(getkey(VK_RETURN,true))
			{
				gdata.setstate(GST_PAUSE);
				player[0].setstate(PST_PAUSE);
				player[1].setstate(PST_PAUSE);
			}
			if(getkey(VK_SPACE))
			{
				player[0].refleshinputtick();
				player[0].lunchpao();
			}
			if(gdata.gameplayers==2)
			{
				if(getkey('A')){player[1].drivepoint(-1);}
				if(getkey('D')){player[1].drivepoint(1);}
				if(getkey('Y')){player[1].toggltipl();}
				if(getkey('S'))
				{
					player[1].refleshinputtick();
					player[1].lunchpao();
				}
			}
#ifdef _DEBUG_
			static int kt=0;Point2 ss;
			if(getkey('V',true)){kt+=1;if(kt>8)kt=0;}
			if(getmouse(RMCLKED))
			{
				ss=player[0].getrealpos(mx,my);
				if(ss.x>=0&&ss.x<GAMEMAPW&&ss.y>=0&&ss.y<GAMEMAPH)
				{
					player[0].mapbf.chgpao((int)(ss.y*GAMEMAPW+ss.x),kt);
				}
			}
			if(getmouse(LMCLKED))
			{
				int cls=0;
				player[0].mapbf.clearflg();
				ss=player[0].getrealpos(mx,my);
				if(ss.x>=0&&ss.x<GAMEMAPW&&ss.y>=0&&ss.y<GAMEMAPH)
						player[0].mapbf.clearpao(ss.x,ss.y,kt,&cls);

			}
			if(getkey('M'))
			{
				int i,j;
				for(i=0;i<GAMEMAPW;i++)
					for(j=0;j<GAMEMAPH;j++)
					{
						ss=player[0].getvirtpos(i,j);
						print_num(ss.x-6,ss.y-2,player[0].mapbf.paoflg[j*GAMEMAPW+i],10);
					}
			}
			if(getkey('K',true))
			{
//				player[0].mapbf.downpao();
				char t=player[0].mapbf.paotj[0];
			}
#endif
			break;
		}
	case GST_PAUSE:
		{
			if(getkey(VK_RETURN,true)){gdata.setstate(GST_GAMING);}
			if(continuemnu==1)
			{
				if(getkey('Y',true)){continuemnu=0;gdata.setstate(GST_GAMING);}
				if(getkey('N',true)){continuemnu=0;gdata.setstate(GST_XUMU);gameclear();}
			}
#ifdef _DEBUG_
			if(getkey(VK_SPACE,true))
			{
				Eft.startreadygoani(Point2(150,100),5);
				Eft.startwatergoodani(Point2(150,100),0);
				Eft.startfiregoodani(Point2(150,100),0);
				Eft.startelecgoodani(Point2(10,100),0);
				Eft.startgoodmoveani(Point2(50,50),1,4, Point2(300,50));
				Eft.startbgdpoint(0);
				Eft.startconcldsta();
			}
#endif
			break;
		}
	case GST_CONCLUT:
		{
			if(getkey(VK_LEFT)){}
			if(getkey(VK_RIGHT)){}
			if(getkey(VK_RETURN)){}
			break;
		}
	default:break;
	}
#ifdef _DEBUG_
	if(getkey(VK_DOWN,true)){player[0].nextlevel(1);if(gdata.gameplayers==2)player[1].nextlevel(1);}
	if(getkey(VK_UP,true)){player[0].nextlevel(-1);if(gdata.gameplayers==2)player[1].nextlevel(1);}
#endif
	Circle(mx,my,lmclked?1:(rmclked?3:2),10);
}

void PaoPaoLong::drawbkground()
{
	Line_(gdata.GameWinpos.x, gdata.GameWinpos.y,  gdata.GameWinpos.x+gdata.GameWinwh.x, gdata.GameWinpos.y+gdata.GameWinwh.y, 34,true);
	Line_(gdata.GameWinpos.x+1, gdata.GameWinpos.y+1,  gdata.GameWinpos.x+gdata.GameWinwh.x+1, gdata.GameWinpos.y+gdata.GameWinwh.y+1, 32,true);

	
}
void PaoPaoLong::drawfrtground()
{

}


inline bool _delay(float tfps)
{
	tfps=1000.0f/tfps;
	static int _tm=0;
	float d=(GetTickCount()-_tm);
	if(d>tfps)
	{
		_tm=GetTickCount();
		return true;
	}
	return false;
}

PaoPaoLong Pao;
static int _speed=0,_frames=0,_fps=0;
static int mmkeys=500,mmgams=500;
void DoFrame();
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow){
	MSG	msg;float dtime;

	if(!_m_buf.InitWindow(WIDTH, HEIGHT, "GEngin  -  PaoPaoLong", hInstance, &hWnd, WndProc, NULL)) return FALSE;
	if(!_m_buf.SetBufferMode(WIDTH, HEIGHT, BPP, FullScreen, &tcf)) return FALSE;

	Pao.gameinit();
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0)){
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(_fps<mmgams)
		{
			if(IsMinimized == FALSE && (ActiveApp && !FullScreen))
			{
				_speed=GetTickCount();
//				if(_delay(mmgams))
					DoFrame();
				dtime=(float)(GetTickCount()-_speed);
				if(dtime==0)dtime=0.01f;
				_fps=1000.0f/dtime;
			}
			else{	WaitMessage();	}
		}
		else
		{
			dtime=(float)(GetTickCount()-_speed);
			if(dtime==0)dtime=0.01f;
			_fps=1000.0f/dtime;
		}
	}

}
void DoFrame(){
	if(SwitchMode){
		_m_buf.SetBufferMode(WIDTH, HEIGHT, BPP, FullScreen, &tcf);
		_m_buf.SetWindowSize(WIDTH, HEIGHT);
		_m_buf.SetPalette(NULL);
		_m_buf.RealizePalette();
		SwitchMode = FALSE;
	}
	
	if(_m_buf.Lock(&_m_bd))
	{
		clearscr();


/*
		int i=0, j=0;
		FillLine(0,0,270,300,32);
		for(j=0;j<9;j++)
			for(i=1;i<8;i++)
				FillLine(i*30,j*30,i*30+31,j*30+30, i+j*7);
*/


		Pao.gameinputloop();
//		if(_delay(mmkeys))
			Pao.gameloop();


	//	ArcR(100,100,20,10,340,2);
/*
		Point2 ctt[3];
		ctt[0]=Point2(100,80);
		ctt[1]=Point2(130,120);
		ctt[2]=Point2(100,160);

		Circle(ctt[0].x,ctt[0].y,2,2);
		Circle(ctt[1].x,ctt[1].y,2,2);
		Circle(ctt[2].x,ctt[2].y,2,2);
		
        ArcP(ctt[0].x,ctt[0].y,ctt[1].x,ctt[1].y, ctt[2].x,ctt[2].y ,2);


		Point2 ttc=Point2(100,100);float xx,yy;int an,dd=(gettimetick()/100)%360;
		xx=cos(dd*Pi)*20+ttc.x;
		yy=sin(dd*Pi)*20+ttc.y;
		Line_(ttc.x,ttc.y,xx,yy, 3, false);
		an=GetAngel(Vector2(xx-ttc.x,yy-ttc.y),Vector2(-10,0));
		print_num(ttc.x,ttc.y, an, 4);
*/

//#ifdef _DEBUG_
		drawfps();
		print_num(0,0,mmgams,9);
		print_num(0,12,mmkeys,9);
		
//#endif
		_m_buf.Unlock();
	}
//#ifdef _DEBUG_
	fps=gettimetick();
//#endif
	_m_buf.UpdateFrontBuffer(FullScreen ? NULL : UFB_STRETCH);	//Call UpdateFrontBuffer while UNLOCKED.
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	switch(iMsg){
		case WM_ACTIVATEAPP :
			ActiveApp = wParam;
			break;
		case WM_ACTIVATE :
			IsMinimized = HIWORD(wParam);
			break;
		case WM_CREATE :
			return 0;
		case WM_LBUTTONDOWN:lmclked=true;break;
		case WM_LBUTTONUP:lmclked=false;break;
		case WM_RBUTTONDOWN:rmclked=true;break;
		case WM_RBUTTONUP:rmclked=false;break;
		case WM_MOUSEMOVE :
			mx=MouseX = LOWORD(lParam);
			my=MouseY = HIWORD(lParam);
			break;
		case WM_KEYDOWN :
			_m_wparam=wParam;
			switch(wParam){
			case '0':
				mmgams+=1;break;
			case '9':mmgams-=1;if(mmgams<0)mmgams=0;break;
				case VK_ESCAPE :
//					PostMessage(hwnd, WM_CLOSE, NULL, NULL);
					break;
				case VK_RETURN:
					{
#ifdef _DEBUG_
						if(Pao.gdata.getstate()!=GST_PAUSE)break;
						Point2 ss;int i;
				    	for(i=0;i<GAMEMAPW*GAMEMAPH;i++)
						if(Pao.player[0].mapbf.get(i)!=0)
						{
							ss=Pao.player[0].getvirtpos(i%GAMEMAPW,i/GAMEMAPW);
							Pao.Eft.startdownpaoani(ss,i,Pao.player[0].mapbf.get(i));
							//  Eft.startclearpaoani(ss,paobuf[i]);
							//    Eft.startgamexumuani();
							
						}
#endif
					}
					break;
				case VK_F8 :
					FullScreen = !FullScreen;
					SwitchMode = TRUE;
					break;
			}
			break;
		case WM_KEYUP:
			{
				_m_wparam=0;
			}

		case WM_PAINT :
			BeginPaint(hwnd, &ps);
			_m_buf.UpdateFrontBuffer(FullScreen ? NULL : UFB_STRETCH);
			EndPaint(hwnd, &ps);
			return 0;
		case WM_CLOSE :
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY :
			hWnd = NULL;
			_m_buf.Destroy();
			Pao.gamedestroy();		
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}









































































































































































