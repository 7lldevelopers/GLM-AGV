#include <iostream>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Jop.cpp"
#include "position.h"
#include "mechin.h"
#ifndef AGV_AGV
#define AGV_AGV
class AGV
{
private:
     int id;
     int velocity;
     int direction;
     bool status;
     Jop jop_cur;
     Position currentPosition;

     //得到当前机器的位置信息
      std::vector<Machin> machin_list;
public:
     //速度
     int get_velocity(){
          return velocity;
     }
     //方向
     int get_direction(){
          return direction;
     }
     int get_id(){
          return id;
     }
     Jop get_jop(){
          return jop_cur;
     }
     void set_jop_cur(Jop Jop){
          jop_cur=Jop;
     }
     void set_machine_list(std::vector<Machin> machin_list){
          machin_list=machin_list;
     }
     // id 速度 方向 位置。当前工件的状态  AGC初始的状态。
     AGV(int id, int v, int d, Position p) : id(id), velocity(v), direction(d), currentPosition(p), status(false) {}
     //     Position getNextPosition() {
     //        double deltaX = velocity * cos(direction) * 1;
     //        double deltaY = velocity * sin(direction) * 1;
     //        currentPosition.x += deltaX;
     //         currentPosition.y += deltaY;
     //       return currentPosition;
     //    };
     void change_fs(int f, int s)
     {
          this->velocity = s;  // 速度
          this->direction = f; // 方向
     }
     void change_map(std::vector<std::vector<char>> &map)
     {
          if (
               velocity==1) // 判断当前速度是否为1
          {
               switch (direction) // 1上 2下 3左 4右
               {
               case 1:
                    if (map[currentPosition.x - 1][currentPosition.y] != '#'&&map[currentPosition.x - 1][currentPosition.y] != 'm')
                    {
                         map[currentPosition.x - 1][currentPosition.y] =  id ; 
                         map[currentPosition.x][currentPosition.y] = '*';
                         // 改变位置
                         currentPosition.x--;
                    }
                    //添加判断是否是当前 选择到机器。后续 添加停留的时间。
                    if (map[currentPosition.x - 1][currentPosition.y] == 'm')
                    {
                          map[currentPosition.x - 1][currentPosition.y] =  '&';
                           map[currentPosition.x][currentPosition.y] = '*';
                         currentPosition.x--;
                        // status=true;
                    }
                    
                    break;
               case 2:
                    if (map[currentPosition.x + 1][currentPosition.y] != '#'&&map[currentPosition.x + 1][currentPosition.y] != 'm')
                    {
                         map[currentPosition.x + 1][currentPosition.y] = id ; 
                         map[currentPosition.x][currentPosition.y] = '*';
                         currentPosition.x++;
                    }
                    if (map[currentPosition.x + 1][currentPosition.y] == 'm')
                    {
                          map[currentPosition.x + 1][currentPosition.y] =  '&';
                           map[currentPosition.x][currentPosition.y] = '*';
                         currentPosition.x++;
                        // status=true;
                    }
                    break;
               case 3:
                    if (map[currentPosition.x][currentPosition.y - 1] != '#'&&map[currentPosition.x ][currentPosition.y- 1] != 'm')
                    {
                         map[currentPosition.x][currentPosition.y - 1] = id ; 
                         map[currentPosition.x][currentPosition.y] = '*';
                         currentPosition.y--;
                    }
                    if (map[currentPosition.x ][currentPosition.y-1] == 'm')
                    {
                          map[currentPosition.x ][currentPosition.y-1] =  '&';
                           map[currentPosition.x][currentPosition.y] = '*';
                         currentPosition.y--;
                       //  status=true;
                    }
                    break;
               case 4:
                    if (map[currentPosition.x][currentPosition.y + 1] != '#'&&map[currentPosition.x ][currentPosition.y+1] != 'm')
                    {
                         map[currentPosition.x][currentPosition.y + 1] = id + '1'; 
                         map[currentPosition.x][currentPosition.y] = '*';
                         currentPosition.y++;
                    }
                    if (map[currentPosition.x ][currentPosition.y+1] == 'm')
                    {
                          map[currentPosition.x ][currentPosition.y+1] =  '&';
                         map[currentPosition.x][currentPosition.y] = '*';
                         currentPosition.y++;
                      //   status=true;
                    }
                    break;
               }
               
               
          }else{  //表示速度=0 停留在当前位置 
          //判断当前位置是否在机器位置

 
                    
                    //这里实现 当前位置停留的时间。修改时间
                    //1.查找当前机器的状态 得到没有加工的机器。设置当前机器的加工时间 -1
                    // if (jop_cur.retuenMachineMeb()!=-1)
                    // {
                         



                    // }
                    

                    //2.判断一下当前工件是否完成 完成换下一个 工件


                    //3.返回信息。等待进一步的修改
          }
     }
     void set_jop(Jop Jop1)
     {
          jop_cur = Jop1;
     }
     void setPosition(int x, int y)
     {
          this->currentPosition.x = x;
          this->currentPosition.y = y;
     }
     const int &getx()
     {
          return this->currentPosition.x;
     }
     const int &gety()
     {
          return this->currentPosition.y;
     }
     void run(std::vector<std::vector<char>> &map)
     {
          int x;
          int y;
          int c=jop_cur.retuenMachineMeb();
          if (c!=-1)
          {
               if ( velocity==1 )
          {
               change_map(map);
          }else{
               
               for (size_t i = 0; i < machin_list.size(); i++)
               {
                    if (jop_cur.get_machinejop().machineName==machin_list[i].get_name())
                    {
                        x=machin_list[i].get_Position().x;
                        y=machin_list[i].get_Position().y;
                    }
               }
               if (x==currentPosition.x&&y==currentPosition.y)   
               {
                    if (jop_cur.get_machinejop().time!=0)
                    {
                        jop_cur.asd_1();
                    }else{
                         jop_cur.asd_sta();       
                    }
                    
               }
               
          }
          }else{
               // std::cout<<"AGV"+id<<std::endl;
          }
          
          
          
          
     }
     //    ~AGV();
};
#endif