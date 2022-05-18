#include "OrgChart.hpp"
#include "doctest.h"
#include <iostream>

using namespace ariel;
using std::cout, std::endl;

TEST_CASE ("OrgChart base cases") {
            SUBCASE("Add a root") {
        OrgChart org;
                CHECK_NOTHROW(org.add_root("CEO"));
        org.add_sub("CEO", "CPO").add_sub("CEO", "CTO");
                CHECK_NOTHROW(org.add_root("Big CEO"));
        /**
         * Assumption:
         * Since we don't really know about how to fix the tree in case of deletion, it's safe to assume that add a root
         * which already exist will be invalid action.
         * Although if the input is the same root, then nothing should happened at all so its valid.
         */
                CHECK_THROWS(org.add_root("CTO"));
                CHECK_NOTHROW(org.add_root("BIG_CEO"));
    }

            SUBCASE("Add a Sub") {
        OrgChart org;
        org.add_root("CEO");
        /**
         * The cases will check the only 4 base case:
         * 1. Not exist, Not exist
         * 2. Not exist, Exist
         * 3. Exist, Exist
         * 4. Exist, Not exist
         *
         * As well as 2 more cases based on case 3:
         * 5. Root, Root
         * 6. Node, Node
         * In those cases since we do not add anything to the tree then nothing invalid will happen, therefore we don't
         * need to throw an exception.
         * Note that I mean node in the tree and not an object.
         *
         * The last case will check if the change we did in case 4 and then try to do it again will
         * raise an exception
         */
                CHECK_THROWS(org.add_sub("HELLO", "WORLD"));
                CHECK_THROWS(org.add_sub("HELLO", "CEO"));
        org.add_sub("CEO", "HELLO");
        org.add_sub("HELLO", "WORLD");
                CHECK_THROWS(org.add_sub("CEO", "WORLD"));
                CHECK_NOTHROW(org.add_sub("CEO", "CP0"));
                CHECK_NOTHROW(org.add_sub("CEO", "CEO"));
                CHECK_NOTHROW(org.add_sub("CP0", "CP0"));
                CHECK_THROWS(org.add_sub("CEO", "CP0"));
    }

    /**
     * Cannot test how it work, only if it works or not
     */

            SUBCASE("Operator<<") {
                SUBCASE("Case 1") {
            OrgChart org;
                    CHECK_NOTHROW(cout << org << endl);
            org.add_root("CEO");
                    CHECK_NOTHROW(cout << org << endl);
            org.add_sub("CEO", "CPO").add_sub("CEO", "CTO").add_sub("CEO", "CDO").
                    add_sub("CPO", "AI").add_sub("CPO", "DB");
                    CHECK_NOTHROW(cout << org << endl);
        }
                SUBCASE("Case 2") {
            OrgChart org;
            org.add_root("BOSS");
            org.add_root("CEO");
                    CHECK_NOTHROW(cout << org << endl);
            org.add_sub("CEO", "CPO").add_sub("CEO", "CTO").add_sub("CEO", "CDO").
                    add_sub("CPO", "AI").add_sub("CPO", "DB");
            org.add_root("BIG BOSS");
                    CHECK_NOTHROW(cout << org << endl);
        }
    }

    SUBCASE("Foreach") {
        OrgChart org;
        org.add_root("CEO");
        org.add_sub("CEO", "CPO").add_sub("CEO", "CTO").add_sub("CEO", "CDO").
                add_sub("CPO", "AI").add_sub("CPO", "DB");
        CHECK_NOTHROW(for(auto it: org){
                    cout<<it<< " ";
        });

    }
}


TEST_CASE ("Pre Order Iterator") {
            SUBCASE("base cases") {
        OrgChart org;
        for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        org.add_root("1");
        for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        org.add_root("0");
        for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it) {
                    CHECK_NOTHROW(*it);
        }
        org.add_sub("0", "1").add_sub("0", "2").add_sub("1", "3").add_sub("1", "4").add_sub("2", "5");

        for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        string expected = "0 1 3 4 2 5 ";
        string actual;

        for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it) {
            actual += (*it) + " ";
        }
                CHECK(expected == actual);
    }

            SUBCASE("Modify the orgchart while iterating is invalid") {
        OrgChart org;
        org.add_root("CEO");
        org.add_sub("CEO", "CPO").add_sub("CEO", "CTO").add_sub("CEO", "CDO").
                add_sub("CPO", "AI").add_sub("CPO", "DB");
        int i = 0;
        for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it) {
            i++;
            if (i >= 3) {
                        CHECK_THROWS(org.add_root("BOSS"));
                        CHECK_NOTHROW(org.add_root("CEO"));//since nothing will change
                        CHECK_THROWS(org.add_sub("CEO", "QA"));
                        CHECK_NOTHROW(org.add_sub("CEO", "CEO"));//since nothing will change
                break;
            }
        }
    }
}

TEST_CASE ("Level Order Iterator") {
            SUBCASE("base cases") {
        OrgChart org;
        for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        org.add_root("1");
        for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        org.add_root("0");
        for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
                    CHECK_NOTHROW(*it);
        }
        org.add_sub("0", "1").add_sub("0", "2").add_sub("1", "3").
        add_sub("1", "4").add_sub("2", "5");

        for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        string expected = "0 1 2 3 4 5 ";
        string actual;

        for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
            actual += (*it) + " ";
        }
                CHECK(expected == actual);
    }

            SUBCASE("Modify the orgchart while iterating is invalid") {
        OrgChart org;
        org.add_root("CEO");
        org.add_sub("CEO", "CPO").add_sub("CEO", "CTO").add_sub("CEO", "CDO").
                add_sub("CPO", "AI").add_sub("CPO", "DB");
        int i = 0;
        for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it) {
            i++;
            if (i >= 3) {
                        CHECK_THROWS(org.add_root("BOSS"));
                        CHECK_NOTHROW(org.add_root("CEO"));//since nothing will change
                        CHECK_THROWS(org.add_sub("CEO", "QA"));
                        CHECK_NOTHROW(org.add_sub("CEO", "CEO"));//since nothing will change
                break;
            }
        }
    }
}


TEST_CASE ("Reversed Level Order Iterator") {
            SUBCASE("base cases") {
        OrgChart org;
        for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        org.add_root("1");
        for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        org.add_root("0");
        for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it) {
                    CHECK_NOTHROW(*it);
        }
        org.add_sub("0", "1").add_sub("0", "2").add_sub("1", "3").
                add_sub("1", "4").add_sub("2", "5");

        for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it) {
                    CHECK_NOTHROW(*it);
        }

        string expected = "5 4 3 2 1 0 ";
        string actual;

        for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it) {
            actual += (*it) + " ";
        }
                CHECK(expected == actual);
    }

            SUBCASE("Modify the orgchart while iterating is invalid") {
        OrgChart org;
        org.add_root("CEO");
        org.add_sub("CEO", "CPO").add_sub("CEO", "CTO").add_sub("CEO", "CDO").
                add_sub("CPO", "AI").add_sub("CPO", "DB");
        int i = 0;
        for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it) {
            i++;
            if (i >= 3) {
                        CHECK_THROWS(org.add_root("BOSS"));
                        CHECK_NOTHROW(org.add_root("CEO"));//since nothing will change
                        CHECK_THROWS(org.add_sub("CEO", "QA"));
                        CHECK_NOTHROW(org.add_sub("CEO", "CEO"));//since nothing will change
                break;
            }
        }
    }
}
