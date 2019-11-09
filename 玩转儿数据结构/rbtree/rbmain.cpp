//
// Created by light on 19-10-18.
//

#include "rb_tree.h"


int main() {
    time_t startTime = clock();
    RBTree<int, string> *rbTree = new RBTree<int, string>();


//        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
//            int *res = (*rbTree).search(*iter);
//            if (res == NULL)
//                (*rbTree).insert(*iter, 1);
//            else
//                (*res)++;
//        }
//
//        // 我们查看unite一词的词频
//        if (rbTree->contain("unite"))
//            cout << "'unite' : " << *(rbTree->search("unite")) << endl;
//        else
//            cout << "No word 'unite' in " + filename << endl;

    rbTree->insert(100, "v100");
    rbTree->insert(50, "v50");
    rbTree->insert(150, "v150");
    rbTree->insert(20, "v20");
    rbTree->insert(85, "v85");
    rbTree->insert(10, "v10");
    rbTree->insert(15, "a15");
    rbTree->insert(75, "v75");
    rbTree->insert(95, "v95");
    rbTree->insert(65, "v65");
    rbTree->insert(76, "v76");
    rbTree->insert(60, "v60");
    rbTree->insert(66, "v66");
    rbTree->insert(61, "v61");

    rbTree->levelOrder();
    time_t endTime = clock();

    cout << "RBTree, time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
    cout << endl;


    delete rbTree;
}