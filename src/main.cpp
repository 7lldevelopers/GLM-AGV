#include <iostream>
#include <math.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "agv.h"
#include "openai.hpp"
#include "mechin.h"
// 运动求解器
// 每次计算1s的下一个车间所有状态信息
// Callback function to write response data to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
//读取map信息 输出AGV 和 路径 和  机器的信息。
std::vector<std::vector<char>> readMap(const std::string& filename, std::vector<std::string>& mapData, std::map<char, std::pair<int, int>>& agvPositions) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        // return  0;
    }
    std::string line;
    int row = 0;
    std::vector<std::vector<char>> asd;
    while (std::getline(inputFile, line)) {
        mapData.push_back(line);
        std::vector<char> a;
        for (int col = 0; col < line.size(); ++col) {
            char symbol = line[col];
            a.push_back(symbol);
            if (symbol >= '1' && symbol <= '9') {
                agvPositions[symbol] = std::make_pair(row, col);
            }
        }
        asd.push_back(a);
        row++;
    }
    inputFile.close();
    return asd;
}
//显示实时信息
void print_map( std::vector<std::vector<char>> map_char){
    for (const auto&a : map_char)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            std::cout<<a[i];
        }
        std::cout<<std::endl;  
    }
}
//跟新json数据AGV& agv
nlohmann::json creat( std::vector<Machin>& machin_list,std::vector<AGV>& agv_list){
    nlohmann::json  data;
    for (int i=0;i<machin_list.size();i++)
    {
        std::string a= machin_list[i].get_name();
        //char* charptr=new char[a.size() + 1];
        char chartry[a.size() + 1];
        std::strcpy(chartry, a.c_str());
        //std::cout<<"======================="<<std::endl;
        data[chartry]= {{"位置", std::to_string(machin_list[i].get_Position().x) + "," + std::to_string(machin_list[i].get_Position().y)}, {"状态", machin_list[i].get_status()}};
    }
    for (int i = 0; i < agv_list.size(); i++)
    {
        std::string a= "AGV"+std::to_string(agv_list[i].get_id());
        char chartry[a.size() + 1];
        std::strcpy(chartry, a.c_str());
        data[chartry]={
        {{"位置",  std::to_string(agv_list[i].getx()) + "," + std::to_string(agv_list[i].gety())}, {"速度", agv_list[i].get_velocity()}, {"方向", agv_list[i].get_direction()}},
        {{"工件",""}, {"工序",agv_list[i].get_jop().get_machinejop().jopName}, {"机器", agv_list[i].get_jop().get_machinejop().machineName}},
        {{"状态", agv_list[i].get_jop().get_machinejop().status}, {"剩余时间", agv_list[i].get_jop().get_machinejop().time}}
    };
    }
    // data["M05"] = {{"位置", std::to_string(1) + "," + std::to_string(2)}, {"状态", 1}};
    // data["M06"] = {{"位置", "5,14"}, {"状态", 0}};
    // data["M07"] = {{"位置", "8,14"}, {"状态", 0}};
    // data["M08"] = {{"位置", "10,13"}, {"状态", 0}};
    // data["AGV13"] = {
    //     {{"位置", "9,3"}, {"速度", 1}, {"方向", 4}},
    //     {{"工件", "001"}, {"工序", "A1"}, {"机器", "M01"}},
    //     {{"状态", 1}, {"剩余时间", 24}}
    // };
    // data["AGV24"] = {
    //     {{"位置", "6,10"}, {"速度", 1}, {"方向", 4}},
    //     {{"工件", "001"}, {"工序", "A1"}, {"机器", "M01"}},
    //     {{"状态", 0}, {"剩余时间", 24}}
    // };
    // data["AGV35"] = {
    //     {{"位置", "9,10"}, {"速度", 1}, {"方向", 4}},
    //     {{"工件", "001"}, {"工序", "A1"}, {"机器", "M01"}},
    //     {{"状态", 0}, {"剩余时间", 24}}
    // };
    //读取位置string  转换成int  int
    // std::string agv1Position = data["AGV1"][0]["位置"];
    // int agv1PosX, agv1PosY;
    // sscanf(agv1Position.c_str(), "%d,%d", &agv1PosX, &agv1PosY);
    return data;
}
//读取json
void print_js(nlohmann::json& asd){
    nlohmann::json data1 = R"(
    {
       "AGV1": [{"方向":"4", "速度":"0"}],
       "AGV2": [{"方向":"1", "速度":"1"}],
       "AGV3": [{"方向":"1", "速度":"1"}]
    }
    )"_json;
    // 读取 AGV1 的方向和速度
    std::string agv1Direction = data1["AGV1"][0]["方向"];
    int num = std::stoi(agv1Direction);  // 将字符串转换为整数
    std::string agv1Speed = data1["AGV1"][0]["速度"];
    std::string agv2Direction = data1["AGV2"][0]["方向"];
    std::string agv2Speed = data1["AGV2"][0]["速度"];
    std::string agv3Direction = data1["AGV3"][0]["方向"];
    std::string agv3Speed = data1["AGV3"][0]["速度"];
    // 输出读取的值
    std::cout << "AGV1：方向=" << num << " 速度=" << agv1Speed << std::endl;
    std::cout << "AGV2：方向=" << agv2Direction << " 速度=" << agv2Speed << std::endl;
    std::cout << "AGV3：方向=" << agv3Direction << " 速度=" << agv3Speed << std::endl;
    std::cout << "=================" << asd["AGV1"][0]["位置"] << " ================" << agv3Speed << std::endl;
}

int main(){
	std::cout<<"Hello "<<std::endl;
	Position iniposition{0,0};
	std::cout<<iniposition.x<<"   "<<iniposition.y<<std::endl;
	AGV agv(1,45,90,iniposition);
	//Position nextposition=agv.getNextPosition();
	//std::cout<<nextposition.x<<"   "<<nextposition.y<<std::endl;
    //初始化当前数据
    std::string filename = "map.txt"; 
    std::vector<std::string> mapData;
    std::vector<std::vector<char>> map_char;
    std::map<char, std::pair<int, int>> agvPositions;
    std::vector<Machin> machin_list;
    std::vector<AGV> agv_list;
    map_char=readMap(filename, mapData, agvPositions);
    for (const auto&a : map_char)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            std::cout<<a[i];
        }
        std::cout<<std::endl;  
    }
   // std::cout<<map_char[1][1]<<std::endl;
   //
        Machin a(false,{9,3},"M0"+std::to_string(1));
        machin_list.push_back(a);
        Machin B(false,{5,14},"M0"+std::to_string(2));
        machin_list.push_back(B);
        Machin C(false,{8,14},"M0"+std::to_string(3));
        machin_list.push_back(C);
        Machin D(false,{10,13},"M0"+std::to_string(4));
        machin_list.push_back(D);
        agv_list.push_back(AGV(1,0,1,{1,3}));
        agv_list.push_back(AGV(2,0,1,{2,2}));
        agv_list.push_back(AGV(3,0,1,{3,3}));
    // Print the map data and AGV positions
    for (const std::string& row : mapData) {
        std::cout << row << std::endl;
    }
    int i=0;
    //初始调度结果--输入
    Jop job1;
    for (size_t i = 0; i <1; i++)
    {
        job1.setMachineSchedule("A1","M01",24,false);
        int c1=job1.retuenMachineMeb();
        std::cout<<job1.get_machinejop().jopName<<" "<<job1.get_machinejop().machineName<<" "<<job1.get_machinejop().time<<std::endl;
        agv_list[0].set_jop(job1);
        // int c1=job1.retuenMachineMeb();
        std::cout<<agv_list[0].get_jop().get_machinejop().jopName+"-"<<agv_list[0].get_jop().get_machinejop().machineName<<agv_list[0].get_jop().get_machinejop().time<<std::endl;
    }
    Jop job2;
     for (size_t i = 0; i < 1; i++)
    {
        job2.setMachineSchedule("A2","M02",21,false);
        int c2=job2.retuenMachineMeb();
        std::cout<<job2.get_machinejop().jopName<<" "<<job2.get_machinejop().machineName<<" "<<job2.get_machinejop().time<<std::endl;
        agv_list[1].set_jop(job2);
        //int c2=job2.retuenMachineMeb();
        std::cout<<agv_list[1].get_jop().get_machinejop().jopName+"-"<<agv_list[1].get_jop().get_machinejop().machineName<<agv_list[1].get_jop().get_machinejop().time<<std::endl;

    }
    Jop job3;
     for (size_t i = 0; i < 1; i++)
    {
        job3.setMachineSchedule("A3","M03",22,false);
        int c3=job3.retuenMachineMeb();
        std::cout<<job3.get_machinejop().jopName<<" "<<job3.get_machinejop().machineName<<" "<<job3.get_machinejop().time<<std::endl;
         agv_list[2].set_jop(job3);
        // int c3=job3.retuenMachineMeb();
        std::cout<<agv_list[2].get_jop().get_machinejop().jopName+"-"<<agv_list[2].get_jop().get_machinejop().machineName<<agv_list[2].get_jop().get_machinejop().time<<std::endl;

    }
    
    // for (const auto& agv : agvPositions) {
    //     std::cout << "AGV " << agv.first << "当前位置"<<": (" << agv.second.first << ", " << agv.second.second << ")" <<"携带工件加工时间     "<<"携带工件状态   "<<"携带工件工序进度   "  <<std::endl;
    //     agv_list[i++].setPosition(agv.second.first,agv.second.second);
    // }
    agv_list[0].change_fs(4,1);
    agv_list[1].change_fs(4,1);
    agv_list[2].change_fs(4,1);

    for (size_t i = 0; i <5; i++)
    {
        agv_list[0].run(map_char);
                agv_list[1].run(map_char);

        agv_list[2].run(map_char);

        print_map(map_char);
    }
    // for (int i = 0; i < 3; i++)
    // {
    //     std::cout << "机器 " << i << "当前位置"<<": (" <<agv_list[i].getx() << ", " << agv_list[i].gety() << ")" <<"当前加工工件id     "<<"机器当前状态状态   " <<std::endl;
    // }
                                        
    //openai 
    nlohmann::json data=creat(machin_list,agv_list);
    std::cout << data.dump(4) << std::endl;
    // 输出 JSON 数据
    print_js(data);

    // for (size_t i = 0; i < 10; i++)
    // {
    //     /* code */
    // }
    
    // while (1)
    // {
    //     //输入当前状态的信息到json文件中
    //     //
    // }


    // openai::start();


    //使用json文件 实现交互 
   openai::start("*******", "optional_organization"); 
  // export OPENAI_API_KEY='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'、
//输出 api列表
   // Calling API method is easy with some chosen free function 
    // auto models = openai::model().list();
    // std::cout << models["data"][0] << std::endl;

    // // Or if you prefer you can take back the instance reference and use member function
    // auto& openai = openai::instance();
    // auto models_other_approach = openai.model.list();
    // std::cout << models_other_approach["data"][1] << std::endl;

    // // Helper member and free functions have the same signature
    // auto model = openai::model().retrieve("text-davinci-003");
    // std::cout << model << std::endl;

//api的对话列表
    // auto chat = openai::chat().create(R"(
    // {
    //     "model": "gpt-3.5-turbo",
    //     "messages":[{"role":"user", "content":"写一个笑话"}],
    //     "max_tokens": 7,
    //     "temperature": 0
    // }
    // )"_json);
    // std::cout << "Response is:\n" << chat.dump(2) << '\n'; 
    // //runagv
    
    return 0; 
}
