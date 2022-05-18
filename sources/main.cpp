///**
// * Demo file for the exercise on iterators
// *
// * @author Tal Zichlinsky
// * @since 2022-02
// */
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <stdexcept>
//using namespace std;
//
//#include "OrgChart.hpp"
//using namespace ariel;
//
//int main() {
//    OrgChart org;
//    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
//        cout<<(*it)<<endl;
//    }
//
//    org.add_root("1");
//    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
//        cout<<(*it)<<endl;
//    }
//
//    org.add_root("0");
//    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
//        cout<<(*it)<<endl;
//    }
//    org.add_sub("0", "1").add_sub("0", "2").add_sub("1", "3").
//            add_sub("1", "4").add_sub("2", "5");
//
//    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
//        cout<<(*it)<<endl;
//    }
//
//    string expected = "0 1 2 3 4 5 ";
//    string actual;
//
//    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
//        actual += (*it) + " ";
//    }
//    cout<<boolalpha<< (expected == actual);
//}
