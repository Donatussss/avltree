// authored by Donatussss
// https://github.com/Donatussss/avltree
#include <iostream>
using namespace std;

class Node{
public:
    int value;
    Node * left;
    Node * right;
    static int counter;

    Node(int val){
        (*this).value = val;
        (*this).left = NULL;
        (*this).right = NULL;
    }

    void preOrder(){

        Node * root = this;
        Node * present = (*root).left;

        cout<<(*root).value<<" ";

        if(present != NULL){

            (*present).preOrder();

        }


        present = (*root).right;

        if(present != NULL){

            (*present).preOrder();

        }

    }

    int getBalance(){
        int left_height = 0;
        int right_height = 0;

        if ((*this).left != NULL){
            left_height = (*((*this).left)).heightoftree() + 1;
        }
        if ((*this).right != NULL){
            right_height = (*((*this).right)).heightoftree() + 1;
        }
        return left_height - right_height;
    }

    void insert2(int insertnum){
        Node * shift = this;

        if(insertnum < (*shift).value){

            if((*shift).left == NULL){
                (*shift).left = new Node(insertnum);
                return;
            }
            else{
                (*((*shift).left)).insert2(insertnum);
            }
        }

        if(insertnum >= (*shift).value){

            if((*shift).right == NULL){
                (*shift).right = new Node(insertnum);
                return;
            }
            else{
                (*((*shift).right)).insert2(insertnum);
            }
        }

    }

    Node * insert(int insertnum){
        Node * shift = this;
        Node * validation_tree = NULL;
        Node * returned_tree = NULL;

        if(insertnum < (*shift).value){

            if((*shift).left == NULL){
                (*shift).left = new Node(insertnum);
                return shift;
            }
            else{
                validation_tree = (*shift).left;
                returned_tree = (*((*shift).left)).insert(insertnum);
            }
        }

        if(insertnum >= (*shift).value){

            if((*shift).right == NULL){
                (*shift).right = new Node(insertnum);
                return shift;
            }
            else{
                validation_tree = (*shift).right;
                returned_tree = (*((*shift).right)).insert(insertnum);
            }
        }
        //cout<<(*shift).value<<endl;

        // need to check if balance factor is within bounds of avl tree
        // this can only happen when insert num is grandchild and not any of the childs
        // note RL and LR case are preferred over RR and LL case
        //(*shift).preOrder();
        //cout<<endl;

        int balance_factor = (*shift).getBalance();
        bool perform_balance = (balance_factor > 1) || (balance_factor < -1);


        if (perform_balance){

            Node * child1_right = (*shift).right;
            Node * child1_left = (*shift).left;

            bool right_right_case = false;
            bool left_left_case = false;
            bool right_left_case = false;
            bool left_right_case = false;

            if (child1_right != NULL){
                right_right_case = (balance_factor < -1) && (insertnum > (*child1_right).value);
                right_left_case = (balance_factor < -1) && (insertnum < (*child1_right).value);
            }
            else if (child1_left != NULL){
                left_left_case = (balance_factor > 1) && (insertnum < (*child1_left).value);
                left_right_case = (balance_factor > 1) && (insertnum > (*child1_left).value);
            }

            if (right_right_case){
                // perform left rotation
                left_rotation(shift, child1_right);
                return child1_right;
                //(*shift).right = child2_right;
            }

            if (left_left_case){
                // perform right rotation
                right_rotation(shift, child1_left);
                return child1_left;
                //(*shift).left = child2_left;
            }

            if (right_left_case){
                // perform right rotation then left rotation
                right_rotation(child1_right, (*child1_right).left);
                left_rotation(shift, (*child1_right).left);
                Node * temp = (*child1_right).left;
                (*child1_right).left = NULL;
                return temp;
            }

            if (left_right_case){
                // perform left rotation then right rotation
                left_rotation(child1_left, (*child1_left).right);
                right_rotation(shift, (*child1_left).right);
                Node * temp = (*child1_left).right;
                (*child1_left).right = NULL;
                return temp;
            }
        }

        if (returned_tree != NULL && validation_tree != returned_tree){

            if ((*validation_tree).value == (*((*shift).left)).value){
                (*shift).left = returned_tree;
            }
            else if ((*validation_tree).value == (*((*shift).right)).value){
                (*shift).right = returned_tree;
            }

            return shift;
        }
        return shift;
    }

    void left_rotation(Node * shift, Node * child1_right){
        // right_right_case
        // perform left rotation
        //(*shift).right = child2_right;
        (*shift).right = (*child1_right).left;
        (*child1_right).left = shift;
    }

    void right_rotation(Node * shift, Node * child1_left){
        // left_left_case
        // perform right rotation
        //(*shift).left = child2_left;
        (*shift).left = (*child1_left).right;
        (*child1_left).right = shift;
    }

    int heightoftree(){
        // do for left
        // do for right
        // take maximum value
        int templeft = 0;
        int templeftrecur = 0;
        int tempright = 0;
        int temprightrecur = 0;

        Node * shift = this;

        // do for left
        if ((*shift).left != NULL){
            templeft++;
            templeftrecur = (*((*shift).left)).heightoftree();
        }

        templeft += templeftrecur;

        // do for right
        if ((*shift).right != NULL){
            tempright++;
            temprightrecur = (*((*shift).right)).heightoftree();
        }

        tempright += temprightrecur;

        /*cout<<"Node "<<(*shift).value;
        cout<<" Left "<<templeft<<" ";
        cout<<"Right"<<tempright<<endl;*/

        return tempright>templeft ? tempright:templeft;

    }

};

int main()
{
    Node *myTree = new Node(7); // NB: we begin with myTree having one element

    // insert some elements
    myTree = myTree->insert(4);
    myTree = myTree->insert(2);
    myTree = myTree->insert(6);
    myTree = myTree->insert(1);
    //myTree->preOrder();
    myTree = myTree->insert(3);
    myTree = myTree->insert(5);
    myTree = myTree->insert(8);
    myTree = myTree->insert(10);
    myTree = myTree->insert(9);
    myTree = myTree->insert(11);
    myTree = myTree->insert(12);
    //cout<<myTree->getBalance()<<endl;
    /*
        DRAW THE TREE THAT RESULTS FROM THE INSERTIONS ABOVE IN ORDER TO VISUALIZE THE EXAMPLES GIVEN BELOW.
        REMEMBER IT IS A BST, SO FOLLOW THE BST RULES WHILE INSERTING.
    */

    //cout<<"Height of tree is: "<<(*myTree).heightoftree()<<endl;
    //cout<<"Balance factor is: "<<(*myTree).getBalance();

    myTree->preOrder(); // output should be: 8 4 2 1 3 6 5 7 10 9 11 12
}
