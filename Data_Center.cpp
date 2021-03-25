#include<iostream>
#include<algorithm>
#include<unordered_map>

using namespace std;
const int Server_Number_MAX = 1e5 + 5;//服务器最大数量
const int Virtual_Machine_Number_MAX = 1e5 + 5;//虚拟机最大数量
const int Days_MAX = 1e3 + 5;//最大天数
const int Server_Kinds = 105; //服务器种类最大值
const int VM_Kinds = 1005;//虚拟机种类最大值

long long cost = 0;

class Server_Menu {
public:
    struct _Server { // 购买的时候遍历这个
        int idex;
        int cpu_core;	//服务器的cpu核数（是一半的）
        int memory;	//服务器的内存大小
        int purchase_cost;	//服务器购买费用
        int daily_energy_cost; 	//服务器的每日耗能成本
    } Server[Server_Kinds];

    // 查询的时候遍历下面的
    int num; // 该次输入服务器的种类数
    unordered_map<string, int> idex;//索引
    unordered_map<int, string> revidex; //
    int cpu_core[Server_Kinds];	//服务器的cpu核数
    int memory[Server_Kinds];	//服务器的内存大小
    int purchase_cost[Server_Kinds];	//服务器购买费用
    int daily_energy_cost[Server_Kinds]; 	//服务器的每日耗能成本

    bool static Cmp(_Server a, _Server b) {
        double racial = 4.0;// 比例（可以通过启发式变化）
        double aa = a.daily_energy_cost * racial + a.purchase_cost;
        double bb = b.daily_energy_cost * racial + b.purchase_cost;
        return aa < bb; // 排序
    }

    void Sort() {
        // 该方法仅在结束输入时调用，用于排序服务器
        sort(Server + 1, Server + 1 + num, Cmp);
    }
};
Server_Menu server_menu;   //服务器菜单

class VM_Menu {
public:
    int num; // 虚拟机数量
    unordered_map<string, int> idex;    //索引
    int cpu_core[VM_Kinds];	//虚拟机的cpu核数
    int memory[VM_Kinds];	//虚拟机的内存大小
    int deploy[VM_Kinds];	 	//虚拟机是否双节点部署,是的话=1,否=0
    unordered_map<int,int> mp;// 虚拟机新ID映射到原ID
};
VM_Menu vm_menu;    //虚拟机菜单

class Virtual_Machine {
public:
    int type;	//虚拟机种类编号
    int server_id; // 该虚拟机现在所处的服务器（这个是排序后的编号，即下标）
    int pos = 3; // 部署到该服务器的拿个节点上：0代表左；1代表右；默认：双节点
    int id; // 输入的虚拟机ID
};

class Server {
public:
    int type;	//服务器种类的编号
    // 规格、成本在menu中查找
    int lcpu_core, rcpu_core; // 左边占用了的cpu核数，以及右边
    int lmemory, rmemory; // 左边占用了的内存大小，以及右边
};

Server servers[Server_Number_MAX]; // 已经购买的服务器列表
//Server online_servers[Server_Number_MAX]; // 开启的服务器列表
int online_server_num, server_num; // 开启的服务器数目,已经购买的服务器数目

Virtual_Machine virtual_machine[Virtual_Machine_Number_MAX];//虚拟机列表


class deploy_journal {
public:
    // 记录当天的部署记录
    string record;
    bool deploy(int VM_id) {
        // 部署成功返回1， 部署失败返回0
        // 服务器型号和服务器id
        if (vm_menu.deploy[virtual_machine[VM_id].type] == 1) { //双节点部署
            for (int i = 1; i <= server_num; ++i) {
                if (server_menu.cpu_core[servers[i].type]/2 - servers[i].lcpu_core >= vm_menu.cpu_core[virtual_machine[VM_id].type] /2
                    && server_menu.cpu_core[servers[i].type] / 2 - servers[i].rcpu_core  >= vm_menu.cpu_core[virtual_machine[VM_id].type] / 2
                    && server_menu.memory[servers[i].type] / 2 -  servers[i].lmemory >= vm_menu.memory[virtual_machine[VM_id].type] / 2
                    && server_menu.memory[servers[i].type] / 2 - servers[i].rmemory >= vm_menu.memory[virtual_machine[VM_id].type] / 2) {
                    servers[i].lcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type] / 2;
                    servers[i].rcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type] / 2;
                    servers[i].lmemory += vm_menu.memory[virtual_machine[VM_id].type] / 2;
                    servers[i].rmemory += vm_menu.memory[virtual_machine[VM_id].type] / 2;
                    virtual_machine[VM_id].server_id = i;
                    record += "(" + to_string(i) + ")" + '\n';
                    return true;
                }
            }
        }
        else {  //单节点部署    哪个服务器上的节点能放就放
            for (int i = 1; i <= server_num; ++i) {
                if (server_menu.cpu_core[servers[i].type]/2  - servers[i].lcpu_core >= vm_menu.cpu_core[virtual_machine[VM_id].type]
                    && server_menu.memory[servers[i].type] / 2 - servers[i].lmemory >= vm_menu.memory[virtual_machine[VM_id].type]) {
                    virtual_machine[VM_id].pos = 0;
                    virtual_machine[VM_id].server_id = i;
                    servers[i].lcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type];
                    servers[i].lmemory += vm_menu.memory[virtual_machine[VM_id].type];
                    record += "(" + to_string(i) + ", A)" + '\n';//A是左节点
                    return true;
                }
                else if (server_menu.cpu_core[servers[i].type] / 2 - servers[i].rcpu_core >= vm_menu.cpu_core[virtual_machine[VM_id].type]
                         && server_menu.memory[servers[i].type] / 2 - servers[i].rmemory >= vm_menu.memory[virtual_machine[VM_id].type]) {
                    virtual_machine[VM_id].pos = 1;
                    virtual_machine[VM_id].server_id = i;
                    servers[i].rcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type];
                    servers[i].rmemory += vm_menu.memory[virtual_machine[VM_id].type];
                    record += "(" + to_string(i) + ", B)" + '\n';//B是右节点
                    return true;
                }
            }
        }
        return false;
    }

    void deploy2(int VM_id, int server_id) {
        // 部署到指定服务器上,id为虚拟机id,id2为服务器id
        virtual_machine[VM_id].server_id = server_id;
        if (vm_menu.deploy[virtual_machine[VM_id].type] == 1) { // 双接口
            servers[server_id].lcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type] / 2;
            servers[server_id].rcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type] / 2;
            servers[server_id].lmemory += vm_menu.memory[virtual_machine[VM_id].type] / 2;
            servers[server_id].rmemory += vm_menu.memory[virtual_machine[VM_id].type] / 2;
            record += "(" + to_string(server_id) + ")" + '\n';
        }
        else {
            // 单接口,默认部署在左节点上
            virtual_machine[VM_id].pos = 0;
            servers[server_id].lcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type] ;
            servers[server_id].lmemory += vm_menu.memory[virtual_machine[VM_id].type] ;
            record += "(" + to_string(server_id) + ", A)" + '\n';
        }
    }

    void delet(int VM_id) {
        // 传入虚拟机id
        if(virtual_machine[VM_id].pos == 3) {
            servers[virtual_machine[VM_id].server_id].lmemory -= vm_menu.memory[virtual_machine[VM_id].type]/2;
            servers[virtual_machine[VM_id].server_id].rmemory -= vm_menu.memory[virtual_machine[VM_id].type]/2;
            servers[virtual_machine[VM_id].server_id].lcpu_core -= vm_menu.cpu_core[virtual_machine[VM_id].type]/2;
            servers[virtual_machine[VM_id].server_id].rcpu_core -= vm_menu.cpu_core[virtual_machine[VM_id].type]/2;
        } else if (virtual_machine[VM_id].pos == 0) {
            servers[virtual_machine[VM_id].server_id].lmemory -= vm_menu.memory[virtual_machine[VM_id].type];
            servers[virtual_machine[VM_id].server_id].lcpu_core -= vm_menu.cpu_core[virtual_machine[VM_id].type];
        } else {
            servers[virtual_machine[VM_id].server_id].rmemory -= vm_menu.memory[virtual_machine[VM_id].type];
            servers[virtual_machine[VM_id].server_id].rcpu_core -= vm_menu.cpu_core[virtual_machine[VM_id].type];
        }
    }
}; // 一天的部署日志
deploy_journal deployment[Days_MAX]; // 所有天的部署日志

class transfer_journal {
public:
    int w[Days_MAX];//第i天迁移的虚拟机的数量

}; //迁移日志
transfer_journal transfer[Days_MAX]; // 所有天的迁移日志

class purchase_journal {
public:
    int num = 0;//第i天购买的服务器种类数
    pair<int, int> p[Server_Kinds];//该天购买的服务器的型号和数量
    int purchase(int VM_id) {
        // 输入虚拟机id，输出新服务器id
        int i;
        if (vm_menu.deploy[virtual_machine[VM_id].type] == 1) {
            // 双节点部署
            for (i = 1; i <= server_menu.num; i++) {
                if (vm_menu.cpu_core[virtual_machine[VM_id].type] <= server_menu.Server[i].cpu_core && vm_menu.memory[virtual_machine[VM_id].type] <= server_menu.Server[i].memory) {
                    int j;
                    for (j = 1; j <= num; j++) {
                        if (p[j].first == server_menu.Server[i].idex) {
                            p[j].second++;
                            cost += server_menu.purchase_cost[p[j].first];
                            servers[++server_num].type = server_menu.Server[i].idex;
                            return server_num;
                        }
                    }
                    if (j > num) {
                        p[++num] = make_pair(server_menu.Server[i].idex, 1);
                        cost += server_menu.purchase_cost[p[num].first];
                        servers[++server_num].type = server_menu.Server[i].idex;
                        return server_num;
                    }
                }
            }
        }
        else {
            for (i = 1; i <= server_menu.num; i++) {
                if (vm_menu.cpu_core[virtual_machine[VM_id].type] <= server_menu.Server[i].cpu_core / 2 && vm_menu.memory[virtual_machine[VM_id].type] <= server_menu.Server[i].memory / 2) {
                    int j;
                    for (j = 1; j <= num; j++) {
                        if (p[j].first == server_menu.Server[i].idex) {
                            p[j].second++;
                            cost += server_menu.purchase_cost[p[j].first];
                            servers[++server_num].type = server_menu.Server[i].idex;
                            return server_num;
                        }
                        if (j > num) {
                            p[++num] = make_pair(server_menu.Server[i].idex, 1);
                            cost += server_menu.purchase_cost[p[num].first];
                            servers[++server_num].type = server_menu.Server[i].idex;
                            return server_num;
                        }
                    }
                }
            }
        }

        return -1;
    };//购买日志
};
purchase_journal purchase[Days_MAX];//所有天的购买日志


int main() {

    scanf("%d", &server_menu.num);  //服务器类型数量
    for (int i = 1; i <= server_menu.num; i++) {
        string s;	//服务器名字
        cin >> s; s = s.substr(1);
        int cor, mem, c1, c2;	//核数、内存、购买费用、维护费用
        scanf(" %d, %d, %d, %d)", &cor, &mem, &c1, &c2);
        server_menu.idex[s] = i;
        server_menu.revidex[i] = s;
        server_menu.cpu_core[i] = cor;
        server_menu.memory[i] = mem;
        server_menu.purchase_cost[i] = c1;
        server_menu.daily_energy_cost[i] = c2;
        server_menu.Server[i].idex = i;
        server_menu.Server[i].cpu_core = cor;
        server_menu.Server[i].memory = mem;
        server_menu.Server[i].purchase_cost = c1;
        server_menu.Server[i].daily_energy_cost = c2;
    }
    server_menu.Sort();


    scanf("%d", &vm_menu.num); //虚拟机种类数量
    for (int i = 1; i <= vm_menu.num; i++) {
        string s;	//虚拟机名字
        cin >> s; s = s.substr(1);
        int cor, mem, del;	//核数、内存、是否双节点部署
        scanf(" %d, %d, %d)",&cor, &mem, &del); // 双节点部署的话是1，单节点是0.
        vm_menu.idex[s] = i;
        vm_menu.cpu_core[i] = cor;
        vm_menu.memory[i] = mem;
        vm_menu.deploy[i] = del;
    }


    int T; scanf("%d", &T); //天数
    int newid = 0;  //虚拟机新ID
    for (int i = 1; i <= T; i++) {  //第i天
        int R; scanf("%d", &R);//每天的申请数量
        for (int j = 1; j <= R; j++) {//第j个请求
            string s1; //add或者del操作
            string s2;//虚拟机型号
            int id;//虚拟机id
            cin >> s1;
            if (s1 == "(add,") {
                cin >> s2;//多了一个逗号
                scanf("%d)", &id); // 编号从0开始，但并不是按顺序
                virtual_machine[++newid].id = id; // 暂未用到
                vm_menu.mp[id] = newid;
                virtual_machine[newid].type = vm_menu.idex[s2];
                if (!deployment[i].deploy(newid)) {
                    // 如果部署失败
                    int server_id = purchase[i].purchase(newid);
                    // 购买，返回服务器
                    deployment[i].deploy2(newid, server_id);
                    // 部署
                }
            }
            else {//删除虚拟机
                scanf("%d)", &id);
                deployment[i].delet(newid);
            }
        }
        // 计算这一天开机服务器产生的费用
        for (int j = 1; j <= server_num; ++j)
            if(servers[j].lcpu_core||servers[j].rcpu_core||servers[j].lmemory||servers[j].rmemory)
                cost += server_menu.daily_energy_cost[servers[j].type];
    }

    //输出
    for(int i=1;i<=T;i++){
        int sum = 0;
        for(int j=1;j<=purchase[i].num;j++){
            sum += purchase[i].p[j].second;
        }
        printf("(purchase, %d)\n",sum);
        for(int j=1;j<=purchase[i].num;j++){
            cout << "(" << server_menu.revidex[purchase[i].p[j].first]  << purchase[i].p[j].second << "\n";
        }

        cout << "(migration, 0)" << '\n';

        cout << deployment[i].record;


    }
    printf("%lld\n", cost);
}
