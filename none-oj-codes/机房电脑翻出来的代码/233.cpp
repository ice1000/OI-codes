#include <stdio.h>
#include <stdlib.h>
#include <queue>
#define  SIZE 200
#define  BIG 999999

using namespace std;

char map[SIZE][SIZE];

typedef struct {
    int x;
    int y;
    int step;
    int haveChakra;
} point;

point getFirst(int length, int width, int chakra){
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            if(map[i][j] == '+'){
                point poi;
                poi.x = i;
                poi.y = j;
                poi.step = 0;
                poi.haveChakra = chakra;
                return poi;
            }
        }
    }
}

int main(int argc,char* argv[]){
    int length = 0;
    int width = 0;
    int chakra = 0;
    int ans = BIG;
    scanf("%d %d %d", &length, &width, &chakra);
    for(int i = 0; i < length; i++){
        scanf("%s",map[i]);
    }
    
    queue<point> directory;
    while(!directory.empty()){
        directory.pop();
    }
    
    point poi = getFirst(length, width, chakra);
    directory.push(poi);
    
    while(!directory.empty()){
    // 广搜开始，取+删
        poi = directory.front();
        directory.pop();
        point newPoi;
        int x,y,s,c;
        newPoi.x = poi.x;
        newPoi.y = poi.y;
        newPoi.step = poi.step+1;
        newPoi.haveChakra = poi.haveChakra;
        if(x > 0){
            newPoi.x--;
            switch(map[newPoi.x][newPoi.y]){
                case '*':
                    directory.push(newPoi);
                    break;
                case '#':
                    if(newPoi.haveChakra > 0){
                        newPoi.haveChakra--;
                        directory.push(newPoi);
                    }
                    break;
                case '@':
                    if(ans > newPoi.step){
                        ans = newPoi.step;
                    }
                    break;
                default:
                    break;
            }
            newPoi.x++;
        }
        if(x < length-1){
            newPoi.x++;
            switch(map[newPoi.x][newPoi.y]){
                case '*':
                    directory.push(newPoi);
                    break;
                case '#':
                    if(newPoi.haveChakra > 0){
                        newPoi.haveChakra--;
                        directory.push(newPoi);
                    }
                    break;
                case '@':
                    if(ans > newPoi.step){
                        ans = newPoi.step;
                    }
                    break;
                default:
                    break;
            }
            newPoi.x--;
        }
        if(y < width-1){
            newPoi.y++;
            switch(map[newPoi.x][newPoi.y]){
                case '*':
                    directory.push(newPoi);
                    break;
                case '#':
                    if(newPoi.haveChakra > 0){
                        newPoi.haveChakra--;
                        directory.push(newPoi);
                    }
                    break;
                case '@':
                    if(ans > newPoi.step){
                        ans = newPoi.step;
                    }
                    break;
                default:
                    break;
            }
            newPoi.y--;
        }
        if(y > 0){
            newPoi.y--;
            switch(map[newPoi.x][newPoi.y]){
                case '*':
                    directory.push(newPoi);
                    break;
                case '#':
                    if(newPoi.haveChakra > 0){
                        newPoi.haveChakra--;
                        directory.push(newPoi);
                    }
                    break;
                case '@':
                    if(ans > newPoi.step){
                        ans = newPoi.step;
                    }
                    break;
                default:
                    break;
            }
            newPoi.y++;
        }
    }
    
    printf("%d\n", ans == BIG ? -1 : ans);
    return 0;
}
