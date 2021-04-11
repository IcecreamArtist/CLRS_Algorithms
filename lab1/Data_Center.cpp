#include<iostream>
#include<algorithm>
#include<unordered_map>

using namespace std;
const int Server_Number_MAX = 1e5 + 5;//�������������
const int Virtual_Machine_Number_MAX = 1e5 + 5;//������������
const int Days_MAX = 1e3 + 5;//�������
const int Server_Kinds = 105; //�������������ֵ
const int VM_Kinds = 1005;//������������ֵ

long long cost = 0;

class Server_Menu {
public:
    struct _Server { // �����ʱ��������
        int idex;
        int cpu_core;	//��������cpu��������һ��ģ�
        int memory;	//���������ڴ��С
        int purchase_cost;	//�������������
        int daily_energy_cost; 	//��������ÿ�պ��ܳɱ�
    } Server[Server_Kinds];

    // ��ѯ��ʱ����������
    int num; // �ô������������������
    unordered_map<string, int> idex;//����
    unordered_map<int, string> revidex; //
    int cpu_core[Server_Kinds];	//��������cpu����
    int memory[Server_Kinds];	//���������ڴ��С
    int purchase_cost[Server_Kinds];	//�������������
    int daily_energy_cost[Server_Kinds]; 	//��������ÿ�պ��ܳɱ�

    bool static Cmp(_Server a, _Server b) {
        double racial = 4.0;// ����������ͨ������ʽ�仯��
        double aa = a.daily_energy_cost * racial + a.purchase_cost;
        double bb = b.daily_energy_cost * racial + b.purchase_cost;
        return aa < bb; // ����
    }

    void Sort() {
        // �÷������ڽ�������ʱ���ã��������������
        sort(Server + 1, Server + 1 + num, Cmp);
    }
};
Server_Menu server_menu;   //�������˵�

class VM_Menu {
public:
    int num; // ���������
    unordered_map<string, int> idex;    //����
    int cpu_core[VM_Kinds];	//�������cpu����
    int memory[VM_Kinds];	//��������ڴ��С
    int deploy[VM_Kinds];	 	//������Ƿ�˫�ڵ㲿��,�ǵĻ�=1,��=0
    unordered_map<int,int> mp;// �������IDӳ�䵽ԭID
};
VM_Menu vm_menu;    //������˵�

class Virtual_Machine {
public:
    int type;	//�����������
    int server_id; // ����������������ķ�����������������ı�ţ����±꣩
    int pos = 3; // ���𵽸÷��������ø��ڵ��ϣ�0������1�����ң�Ĭ�ϣ�˫�ڵ�
    int id; // ����������ID
};

class Server {
public:
    int type;	//����������ı��
    // ��񡢳ɱ���menu�в���
    int lcpu_core, rcpu_core; // ���ռ���˵�cpu�������Լ��ұ�
    int lmemory, rmemory; // ���ռ���˵��ڴ��С���Լ��ұ�
};

Server servers[Server_Number_MAX]; // �Ѿ�����ķ������б�
//Server online_servers[Server_Number_MAX]; // �����ķ������б�
int online_server_num, server_num; // �����ķ�������Ŀ,�Ѿ�����ķ�������Ŀ

Virtual_Machine virtual_machine[Virtual_Machine_Number_MAX];//������б�


class deploy_journal {
public:
    // ��¼����Ĳ����¼
    string record;
    bool deploy(int VM_id) {
        // ����ɹ�����1�� ����ʧ�ܷ���0
        // �������ͺźͷ�����id
        if (vm_menu.deploy[virtual_machine[VM_id].type] == 1) { //˫�ڵ㲿��
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
        else {  //���ڵ㲿��    �ĸ��������ϵĽڵ��ܷžͷ�
            for (int i = 1; i <= server_num; ++i) {
                if (server_menu.cpu_core[servers[i].type]/2  - servers[i].lcpu_core >= vm_menu.cpu_core[virtual_machine[VM_id].type]
                    && server_menu.memory[servers[i].type] / 2 - servers[i].lmemory >= vm_menu.memory[virtual_machine[VM_id].type]) {
                    virtual_machine[VM_id].pos = 0;
                    virtual_machine[VM_id].server_id = i;
                    servers[i].lcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type];
                    servers[i].lmemory += vm_menu.memory[virtual_machine[VM_id].type];
                    record += "(" + to_string(i) + ", A)" + '\n';//A����ڵ�
                    return true;
                }
                else if (server_menu.cpu_core[servers[i].type] / 2 - servers[i].rcpu_core >= vm_menu.cpu_core[virtual_machine[VM_id].type]
                         && server_menu.memory[servers[i].type] / 2 - servers[i].rmemory >= vm_menu.memory[virtual_machine[VM_id].type]) {
                    virtual_machine[VM_id].pos = 1;
                    virtual_machine[VM_id].server_id = i;
                    servers[i].rcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type];
                    servers[i].rmemory += vm_menu.memory[virtual_machine[VM_id].type];
                    record += "(" + to_string(i) + ", B)" + '\n';//B���ҽڵ�
                    return true;
                }
            }
        }
        return false;
    }

    void deploy2(int VM_id, int server_id) {
        // ����ָ����������,idΪ�����id,id2Ϊ������id
        virtual_machine[VM_id].server_id = server_id;
        if (vm_menu.deploy[virtual_machine[VM_id].type] == 1) { // ˫�ӿ�
            servers[server_id].lcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type] / 2;
            servers[server_id].rcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type] / 2;
            servers[server_id].lmemory += vm_menu.memory[virtual_machine[VM_id].type] / 2;
            servers[server_id].rmemory += vm_menu.memory[virtual_machine[VM_id].type] / 2;
            record += "(" + to_string(server_id) + ")" + '\n';
        }
        else {
            // ���ӿ�,Ĭ�ϲ�������ڵ���
            virtual_machine[VM_id].pos = 0;
            servers[server_id].lcpu_core += vm_menu.cpu_core[virtual_machine[VM_id].type] ;
            servers[server_id].lmemory += vm_menu.memory[virtual_machine[VM_id].type] ;
            record += "(" + to_string(server_id) + ", A)" + '\n';
        }
    }

    void delet(int VM_id) {
        // ���������id
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
}; // һ��Ĳ�����־
deploy_journal deployment[Days_MAX]; // ������Ĳ�����־

class transfer_journal {
public:
    int w[Days_MAX];//��i��Ǩ�Ƶ������������

}; //Ǩ����־
transfer_journal transfer[Days_MAX]; // �������Ǩ����־

class purchase_journal {
public:
    int num = 0;//��i�칺��ķ�����������
    pair<int, int> p[Server_Kinds];//���칺��ķ��������ͺź�����
    int purchase(int VM_id) {
        // ���������id������·�����id
        int i;
        if (vm_menu.deploy[virtual_machine[VM_id].type] == 1) {
            // ˫�ڵ㲿��
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
    };//������־
};
purchase_journal purchase[Days_MAX];//������Ĺ�����־


int main() {

    scanf("%d", &server_menu.num);  //��������������
    for (int i = 1; i <= server_menu.num; i++) {
        string s;	//����������
        cin >> s; s = s.substr(1);
        int cor, mem, c1, c2;	//�������ڴ桢������á�ά������
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


    scanf("%d", &vm_menu.num); //�������������
    for (int i = 1; i <= vm_menu.num; i++) {
        string s;	//���������
        cin >> s; s = s.substr(1);
        int cor, mem, del;	//�������ڴ桢�Ƿ�˫�ڵ㲿��
        scanf(" %d, %d, %d)",&cor, &mem, &del); // ˫�ڵ㲿��Ļ���1�����ڵ���0.
        vm_menu.idex[s] = i;
        vm_menu.cpu_core[i] = cor;
        vm_menu.memory[i] = mem;
        vm_menu.deploy[i] = del;
    }


    int T; scanf("%d", &T); //����
    int newid = 0;  //�������ID
    for (int i = 1; i <= T; i++) {  //��i��
        int R; scanf("%d", &R);//ÿ�����������
        for (int j = 1; j <= R; j++) {//��j������
            string s1; //add����del����
            string s2;//������ͺ�
            int id;//�����id
            cin >> s1;
            if (s1 == "(add,") {
                cin >> s2;//����һ������
                scanf("%d)", &id); // ��Ŵ�0��ʼ���������ǰ�˳��
                virtual_machine[++newid].id = id; // ��δ�õ�
                vm_menu.mp[id] = newid;
                virtual_machine[newid].type = vm_menu.idex[s2];
                if (!deployment[i].deploy(newid)) {
                    // �������ʧ��
                    int server_id = purchase[i].purchase(newid);
                    // ���򣬷��ط�����
                    deployment[i].deploy2(newid, server_id);
                    // ����
                }
            }
            else {//ɾ�������
                scanf("%d)", &id);
                deployment[i].delet(newid);
            }
        }
        // ������һ�쿪�������������ķ���
        for (int j = 1; j <= server_num; ++j)
            if(servers[j].lcpu_core||servers[j].rcpu_core||servers[j].lmemory||servers[j].rmemory)
                cost += server_menu.daily_energy_cost[servers[j].type];
    }

    //���
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
