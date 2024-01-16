#include<iostream>
#include<queue>
using namespace std;

struct node 
{
    string position;  //노드의 문자열 데이터
    node* left;  //왼쪽 노드를 가리키는 포인터
    node* right;  //오른쪽 노드를 가리키는 포인터
};

struct new_tree //tree의 전체적인 계층을 나타내는 구조체 선언
{
    node* root; //구조체의 멤버변수로 트리의 루트 노드를 가리키는 포인터
 
    static new_tree create_tree_structure (const string& pos)     
    {
        new_tree tree; 
        tree.root = new node{ pos, NULL ,NULL };  

        return tree;
    }

    static node* find(node* root, const string& value)
    {
        if (root == NULL)
            return NULL;

        if (root->position == value)
            return root;

        auto firstFound = new_tree::find(root->left, value);

        if (firstFound != NULL) 
            return firstFound;
            
        return find(root->right, value); 
    }

    bool addSubordinate(const string& manager, const string& subordinate)
    {
        auto managerNode = find(root, manager);
        // 1.root: 루트노드-> 전체 트리에 접근 
        // 2.tree에서 특정 값을 찾는다
        // 3.특정 노드의 포인터 managerNode에 할당

        if (!managerNode)
        {
            cout << manager << "을 찾을 수 없습니다:" << endl;
            return false;
        }
        if (managerNode->left && managerNode->right) 
        {
            cout << manager << "아래에 " << subordinate << "을 추가할 수 없습니다" << endl;
            return false;
        }
        if (!managerNode->left) 
        {
            managerNode->left = new node{ subordinate, NULL , NULL };
        }
        else
        {
            managerNode->right = new node{ subordinate, NULL, NULL };
        }
        cout << manager << "아래에 " << subordinate << "을 추가했습니다" << endl;

        return true;
    }
};

int main()
{
    auto tree = new_tree::create_tree_structure("CEO");
   
    tree.addSubordinate("CEO", "부사장");
    tree.addSubordinate("부사장", "it부장");
    tree.addSubordinate("부사장", "마케팅부장");
    tree.addSubordinate("it부장", "보안팀장");
    tree.addSubordinate("it부장", "앱개발팀장");
    tree.addSubordinate("마케팅부장", "물류팀장");
    tree.addSubordinate("마케팅부장", "홍보팀장");
    tree.addSubordinate("부사장", "재무부장");

    return 0;
}