#include <iostream>
using namespace std;

class Material
{public:
    Material();
    ~Material();
    void print();

};

int main()
{
    cout << "--- 构造函数 ---" << endl;
    Material m;

    cout << "\n--- print函数 ---" << endl;
    m.print();

    cout << "\n--- 自动进行析构函数 ---" << endl;
    return 0;
}

Material::Material(){
    cout<<"111"<<endl;
}
Material::~Material(){
    cout<<"222"<<endl;
}
void Material::print(){
    cout<<"333"<<endl;
}