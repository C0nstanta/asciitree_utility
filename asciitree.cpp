#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <list>

using std::string;
using std::vector;


struct Node{
    string val;
    int lvl_num;
    vector<Node*> sub_tree;

    Node(): val(string()), lvl_num(0), sub_tree({}){}
    Node(string val, int lvl): val(val), lvl_num(lvl), sub_tree({}){}
};


string operator*(int mult_num, const string str){
    string tmp_str;

    while(mult_num--){
        tmp_str += str;
    }
    return tmp_str;
}


class Solution{
//    string* str;
    Node* node_;
    int lvl;
    int pos_start;
    int pos_end;

public:
    Solution(): node_(new Node()), lvl(0), pos_start(0), pos_end(0){}

    Node* new_node(const string& str){
        Node* tmp_node = new Node;
        tmp_node->lvl_num = ++lvl;
        tmp_node->val = str.substr(pos_start + 1, pos_end - pos_start - 1);
        pos_start = pos_end;
        return tmp_node;
    }

    void fill_node(const string& str, Node* node=nullptr){
        if (!node){ return; }
        node->lvl_num = ++lvl;
        node->val = str.substr(pos_start + 1, pos_end - pos_start - 1);
        pos_start = pos_end;
    }


    void parseTree(const string& str, Node* node=nullptr){
        if (pos_end >= str.length()){ return; }
        if (node == nullptr){ node = node_; }

        while(pos_start < str.length()) {
            if (str[pos_start] == ')' ){ // && pos_start == pos_end// ")" case
                ++pos_start;
                --lvl;
                return;
            }
            else if (str[pos_start] == '(' && (str[pos_end] == ' ' ||
                     str[pos_end] == ')')){ // "(word " case. new node
                if (!node->val.length()){
                    fill_node(str, node);
                    continue;
                }
                else {
                    auto vec_node = new_node(str);
                    node->sub_tree.push_back(vec_node);
                }
                parseTree(str, node->sub_tree.back());
            }
            else if(str[pos_start] == ' ' && str[pos_end] == '('){ // " (" case
                ++pos_start;
                ++pos_end;
                continue;
            }
            else if(str[pos_start] == ' '
                    && pos_start < pos_end
                    && str[pos_end] == ' '){ // " word " case
                auto vec_node = new_node(str);
                node->sub_tree.push_back(vec_node);
                --lvl;
            }
            else if(str[pos_start] == ' '
                    && pos_start < pos_end
                    && str[pos_end] == ')'){ // " word)" case

                if (!node->val.length()){ fill_node(str, node); }
                else {
                    auto vec_node = new_node(str);
                    node->sub_tree.push_back(vec_node);
                    --lvl;
                }
            }
            ++pos_end;
        }
    }


    void print_ascii_tree(Node* tmp_node=nullptr, string prefix_str = "+--"){
        if (!tmp_node){ tmp_node = node_; }
        while(true){
            if (tmp_node->val.length()){
                int lvl = tmp_node->lvl_num;
                string out_str = tmp_node->val;
                out_str = (lvl == 1)? out_str :
                          (lvl == 2)? prefix_str + out_str: string("|") + (lvl - 2) * string("   ") + prefix_str + out_str;
                std::cout << out_str << std::endl;
            }
            int i = 0;
            while(i < tmp_node->sub_tree.size()){
                print_ascii_tree(tmp_node->sub_tree[i++]);
            }
            break;
        }
    }
};



int main(int argc, const char * argv[]) {

    {
        string asciitree = "(asciitree (sometimes you) (just (want to draw)) trees (in (your terminal)))";
        Solution sol;
        sol.parseTree(asciitree);
        sol.print_ascii_tree();

        std::cout << "----------------------" << std::endl;
    }

    {
        string asciitree = "(asciitree)";
        Solution sol;
        sol.parseTree(asciitree);
        sol.print_ascii_tree();

        std::cout << "----------------------" << std::endl;
    }

    {
        string asciitree = "(asciitree (qwer qwer qwewr df) dfgh)";
        Solution sol;
        sol.parseTree(asciitree);
        sol.print_ascii_tree();

        std::cout << "----------------------" << std::endl;
    }


    return 0;
}
