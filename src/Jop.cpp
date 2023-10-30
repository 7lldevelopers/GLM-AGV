#include <iostream>
#include <math.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
struct MachineJop{
    std::string jopName;
    std::string machineName;
    int time;
    bool status;
    
};

class Jop
{
private:
    int id;
    //工序名  时间  状态
    int job_time;
    //当前工序的时间 和是否完成的状态
    std::map<int,std::pair<int,bool>> process;
    //例子  “M01”-“时间”-“状态”
    std::map<std::string, std::map<int, int>> machine_status;
    std::vector<MachineJop> machine_schedule;
    //当前工件的机器 引用 当前的前Verctor,MachineJop& renwu; 
     MachineJop renwu;
    static std::map<int,std::vector<MachineJop>> Jop_list;
public:
   // Jop(int id):id(id){}
    /// @brief 
    /// @return 返回当前任务 执行的任务 
    MachineJop &get_machinejop(){
        return renwu;
    }
    void asd_1(){
        renwu.time--;
    }
    void asd_sta(){
        renwu.status=true;  
        machine_schedule[retuenMachineMeb()].status=true;
    }

    /// @brief 当前的状态和顺序结果 
    /// @param 7ll
    /// @param time 
    /// @param sts 
    void setMachineSchedule(std::string jopname,std::string name,int time,bool sts){
        machine_schedule.push_back({jopname,name,time,sts});
    }
    int retuenMachineMeb(){
        for (int i = 0; i < machine_schedule.size(); i++)
        {
            if (machine_schedule[i].status==false)
            {
                //设置当前工件需要加工的任务
                renwu=machine_schedule[i];
                return i;
            }
            
        }               
        return -1;
    }

    std::map<int,std::pair<int,bool>>& get_process(){
        return this->process; 
    }
    void set_machine_status(std::string mechine,int time,int status1){
        machine_status[mechine][time]=status1;
    }
    void set_job(int a,int time,bool status){
        process[a]=std::make_pair(time, status);
    }
    //返回当前 是否 有没有还要加工的工件
    int status_uuid(){
        //遍历返回当前的
        for (const auto& pro :machine_status)
        {

        }
        return 1;
    }
    bool status (){
        for (const auto& pro : process)
        {
            if(pro.second.second==false){
                return true;
            }
        }
        return false;
    }
    //返回需要加工的标号当前机器的标号   时间 状态
    std::pair<int,bool> get_mechin (){
        for (const auto& pro : process)
        {
            if(pro.second.second==false){
                return std::make_pair(pro.second.first, pro.second.second);
            }
        }               
    }
    void set_mechin(){
        for (const auto& pro : process)
        {
            if(pro.second.second==false){
                pro.second.second;
                break;
            }
        } 
    }
    //run执行结果 将当前时间 -1
    void jianqu_1( ){

    }

    char get_mechine(char a){
        return this->process.at(a).first;
    }

};
//    存储数据集合
//    std::map<std::string, std::vector<double>> machine_status;
//    // 向 map 中插入键值对  
//    machine_status["Machine1"] = std::vector<double>{1628758000, "Online"};  
//    machine_status["Machine2"] = std::vector<double>{1628758300, "Offline"};  
//    machine_status["Machine3"] = std::vector<double>{1628758600, "Idle"};
//    // 使用 map 的 find 方法查找键为 "Machine2" 的键值对  
//    auto it = machine_status.find("Machine2");  
//    if (it!= machine_status.end()) {  
//        std::cout << "找到了键为 'Machine2' 的键值对：" << it->second[0] << ", " << it->second[1] << std::endl;  
//    } else {  
//        std::cout << "未找到键为 'Machine2' 的键值对" << std::endl;  
//    }
//    // 修改键为 "Machine2" 的键值对的状态  
//    machine_status["Machine2"] = std::vector<double>{1628758900, "维修中"};
//    // 输出修改后的 map 内容  
//    std::cout << "修改后的 machine_status：" << std::endl;  
//    for (const auto& entry : machine_status) {  
//        std::cout << entry.first << ": " << entry.second[0] << ", " << entry.second[1] << std::endl;  
//    }
//    return 0;  