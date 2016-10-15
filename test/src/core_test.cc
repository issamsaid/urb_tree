///
/// @copyright Copyright (c)2016-, Issam SAID <said.issam@gmail.com>
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
///
/// 1. Redistributions of source code must retain the above copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. Neither the name of the copyright holder nor the names of its contributors
///    may be used to endorse or promote products derived from this software
///    without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
/// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY AND FITNESS
/// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
/// HOLDER OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
/// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
/// LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
/// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// @file test/src/core_test.cc
/// @author Issam SAID
/// @brief Unit testing file for the urb_tree core routines.
/// 
#include <gtest/gtest.h>
#include <urb_tree/urb_tree.h>

namespace {

    int  urb_cmp(void *a, void *b) { return *(int*)a-*(int*)b; }

    void urb_dst(void *a) { free(a); }

    void urb_shw(void *a, void *b) { 
        fprintf(stdout, "[%d, %d]\n", *(int*)a, *(int*)b); 
    }

    class CoreTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
        }
        virtual void TearDown() { }
    };

    TEST_F(CoreTest, create_delete) {
        urb_t *urb = &urb_sentinel;
        int *key    = (int*) malloc(sizeof(int));
        int *value  = (int*) malloc(sizeof(int));
        *key   = 1;
        *value = 1;
        urb = urb_tree_create(key, value);
        ASSERT_TRUE(urb != NULL);
        ASSERT_EQ(urb_tree_delete(&urb, urb_dst, urb_dst), URB_SUCCESS);
    }

    TEST_F(CoreTest, put) {
        urb_t *urb = &urb_sentinel;
        urb_t *n, *l, *r;
        int tmp;
        int *key    = (int*) malloc(sizeof(int));
        int *value  = (int*) malloc(sizeof(int));
        *key   = 8;
        *value = 8;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        URB_TREE_CHECK_INVARIANTS(&urb);
        urb_tree_print(&urb, urb_shw);
        ASSERT_TRUE((n = urb_tree_find(&urb, key, urb_cmp)) != &urb_sentinel);
        ASSERT_EQ(urb, n);
        ASSERT_EQ(n->left, &urb_sentinel);
        ASSERT_EQ(n->right, &urb_sentinel);
        ASSERT_EQ(black, n->color);
        
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 5;
        *value = 5;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        URB_TREE_CHECK_INVARIANTS(&urb);
        urb_tree_print(&urb, urb_shw);
        tmp   = 5;
        ASSERT_TRUE((l = urb_tree_find(&urb, &tmp, urb_cmp)) != &urb_sentinel);
        ASSERT_TRUE( l != NULL);
        tmp   = 8;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, urb_cmp)) != &urb_sentinel);
        ASSERT_TRUE( n != NULL);
        ASSERT_EQ(black, n->color);
        ASSERT_EQ(red, l->color);
        ASSERT_EQ(n, urb);
        ASSERT_EQ(n->left, l);
        
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 13;
        *value = 13;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        URB_TREE_CHECK_INVARIANTS(&urb);
        urb_tree_print(&urb, urb_shw);

        tmp   = 8;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, urb_cmp)) != &urb_sentinel);
        ASSERT_TRUE( n != NULL);

        tmp   = 5;
        ASSERT_TRUE((l = urb_tree_find(&urb, &tmp, urb_cmp)) != &urb_sentinel);
        ASSERT_TRUE( l != NULL);
        
        tmp   = 13;
        ASSERT_TRUE((r = urb_tree_find(&urb, &tmp, urb_cmp)) != &urb_sentinel);
        ASSERT_TRUE( r != NULL);
        
        ASSERT_EQ(black, n->color);
        ASSERT_EQ(red, l->color);
        ASSERT_EQ(red, r->color);
        ASSERT_EQ(n, urb);
        ASSERT_EQ(n->left, l);
        ASSERT_EQ(n->right, r);
        ASSERT_EQ(urb_tree_delete(&urb, urb_dst, urb_dst), URB_SUCCESS);
    }

    TEST_F(CoreTest, pop) {
        urb_t *urb = &urb_sentinel;
        int tmp;
        int *key    = (int*) malloc(sizeof(int));
        int *value  = (int*) malloc(sizeof(int));
        *key   = 8;
        *value = 8;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 5;
        *value = 5;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 2;
        *value = 2;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 1;
        *value = 1;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 14;
        *value = 14;        
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 7;
        *value = 7;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 11;
        *value = 11;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        key    = (int*) malloc(sizeof(int));
        value  = (int*) malloc(sizeof(int));
        *key   = 12;
        *value = 12;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(key, value), urb_cmp), 
                  URB_SUCCESS);
        urb_tree_print(&urb, urb_shw);
        URB_TREE_CHECK_INVARIANTS(&urb);
        ASSERT_EQ(urb_tree_size(&urb), 8);
        
        tmp = 2;
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) != &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 7);
        tmp = 14;
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) != &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 6);
        tmp = 12;
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) != &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 5);
        tmp = 8;
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) != &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 4);
        tmp = 7;
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) != &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 3);
        tmp = 11;
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) != &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 2);
        tmp = 5;
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) != &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 1);
        tmp = 1;
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) != &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 0);
        ASSERT_TRUE(urb_tree_pop(&urb, &tmp, urb_cmp) == &urb_sentinel);         
        URB_TREE_CHECK_INVARIANTS(&urb); 
        ASSERT_EQ(urb_tree_size(&urb), 0);
        ASSERT_EQ(urb_tree_delete(&urb, urb_dst, urb_dst), URB_SUCCESS);
    }
    /*
    TEST_F(CoreTest, right_rotate_root) {
         urb urb;
         rbn *n, *l, *r;
         ASSERT_EQ(create_urb(&urb, urb_cmp, urb_dst), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  8,  8), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  5,  5), RB_SUCCESS);         
         ASSERT_EQ(urb_tree_put(&urb,  2,  2), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  1,  1), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 14, 14), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  7,  7), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 11, 11), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 12, 12), RB_SUCCESS);         
         chk_invariants_urb(&urb);
         right_rotate_urb(&urb, urb.root);
         walk_key_urb(&urb, urb_shw); printf("\n");
         
         ASSERT_TRUE((n = find_rbn(&urb, 2)) != NULL);
         ASSERT_EQ(urb.root, n);
         ASSERT_TRUE((l = find_rbn(&urb, 1)) != NULL);
         ASSERT_EQ(n->left, l);
         ASSERT_TRUE((r = find_rbn(&urb, 5)) != NULL);
         ASSERT_EQ(n->right, r);
         n = r;
         ASSERT_TRUE((r = find_rbn(&urb, 8)) != NULL);
         ASSERT_EQ(n->right, r);
         n = r;
         ASSERT_TRUE((r = find_rbn(&urb, 12)) != NULL);
         ASSERT_TRUE((l = find_rbn(&urb,  7)) != NULL);
         ASSERT_EQ(BLACK, r->color);
         ASSERT_EQ(BLACK, l->color);
         ASSERT_EQ(n->left, l);
         ASSERT_EQ(n->right, r);
         n = r;
         ASSERT_TRUE((r = find_rbn(&urb, 14)) != NULL);
         ASSERT_TRUE((l = find_rbn(&urb, 11)) != NULL);
         ASSERT_EQ(RED, l->color);
         ASSERT_EQ(RED, r->color);
         ASSERT_EQ(n->right, r);
         ASSERT_EQ(n->left, l);         
         ASSERT_EQ(delete_urb(&urb), RB_SUCCESS);
    }
   
    TEST_F(CoreTest, left_rotate_root) {
         urb urb;
         rbn *n, *l, *r;
         ASSERT_EQ(create_urb(&urb, urb_cmp, urb_dst), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  8,  8), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  5,  5), RB_SUCCESS);         
         ASSERT_EQ(urb_tree_put(&urb,  2,  2), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  1,  1), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 14, 14), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  7,  7), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 11, 11), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 12, 12), RB_SUCCESS);
         chk_invariants_urb(&urb);
         left_rotate_urb(&urb, urb.root);
         walk_key_urb(&urb, urb_shw); printf("\n");
         
         ASSERT_TRUE((n = find_rbn(&urb, 8)) != NULL);
         ASSERT_EQ(urb.root, n);
         ASSERT_TRUE((l = find_rbn(&urb, 5)) != NULL);
         ASSERT_EQ(n->left, l);
         ASSERT_TRUE((r = find_rbn(&urb, 12)) != NULL);
         ASSERT_EQ(n->right, r);
         n = l;
         ASSERT_TRUE((l = find_rbn(&urb, 2)) != NULL);
         ASSERT_EQ(n->left, l);
         ASSERT_TRUE((r = find_rbn(&urb, 7)) != NULL);
         ASSERT_EQ(n->right, r);
         n = l;
         ASSERT_TRUE((l = find_rbn(&urb, 1)) != NULL);
         ASSERT_EQ(n->left, l);
         
         ASSERT_TRUE((n = find_rbn(&urb, 12)) != NULL);
         ASSERT_TRUE((l = find_rbn(&urb, 11)) != NULL);
         ASSERT_TRUE((r = find_rbn(&urb, 14)) != NULL);
         ASSERT_EQ(n->right, r);
         ASSERT_EQ(n->left, l);
         ASSERT_EQ(delete_urb(&urb), RB_SUCCESS);
    }
    
    TEST_F(CoreTest, mix_rotate_root) {
         urb urb;
         rbn *n;
         ASSERT_EQ(create_urb(&urb, urb_cmp, urb_dst), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  8,  8), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  5,  5), RB_SUCCESS);         
         ASSERT_EQ(urb_tree_put(&urb,  2,  2), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  1,  1), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 14, 14), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  7,  7), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 11, 11), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 12, 12), RB_SUCCESS);
         chk_invariants_urb(&urb);
         walk_key_urb(&urb, urb_shw); printf("\n");
         left_rotate_urb(&urb, urb.root);
         walk_key_urb(&urb, urb_shw); printf("\n");
         ASSERT_TRUE((n = find_rbn(&urb, 8)) != NULL);
         right_rotate_urb(&urb, n);
         walk_key_urb(&urb, urb_shw); printf("\n");
         // ASSERT_TRUE((n = find_rbn(&urb, 14)) != NULL);
         // ASSERT_EQ(urb.root, n);
         // ASSERT_TRUE((l = find_rbn(&urb, 8)) != NULL);
         // ASSERT_EQ(n->left, l);
         // ASSERT_TRUE((r = find_rbn(&urb, 15)) != NULL);
         // ASSERT_EQ(n->right, r);
         // n = l;
         // ASSERT_TRUE((l = find_rbn(&urb, 5)) != NULL);
         // ASSERT_EQ(n->left, l);
         // ASSERT_TRUE((r = find_rbn(&urb, 11)) != NULL);
         // ASSERT_EQ(n->right, r);
         // n = l;
         // ASSERT_TRUE((l = find_rbn(&urb, 2)) != NULL);
         // ASSERT_EQ(n->left, l);
         // ASSERT_TRUE((r = find_rbn(&urb, 7)) != NULL);
         // ASSERT_EQ(n->right, r);
         // n = l;
         // ASSERT_TRUE((l = find_rbn(&urb, 1)) != NULL);
         // ASSERT_EQ(n->left, l);
         ASSERT_EQ(delete_urb(&urb), RB_SUCCESS);
    }
 
    TEST_F(CoreTest, ordered) {
         urb urb;
         int i, T = 6;
         ASSERT_EQ(create_urb(&urb, urb_cmp, urb_dst), RB_SUCCESS);
         for (i=1; i<=T; ++i)
             ASSERT_EQ(urb_tree_put(&urb, i, i), RB_SUCCESS);
         walk_key_urb(&urb, urb_shw); printf("\n");
         chk_invariants_urb(&urb);
         ASSERT_EQ(BLACK, find_rbn(&urb, 1)->color);
         ASSERT_EQ(BLACK, find_rbn(&urb, 2)->color);
         ASSERT_EQ(RED, find_rbn(&urb, 4)->color);
         ASSERT_EQ(BLACK, find_rbn(&urb, 3)->color);
         ASSERT_EQ(BLACK, find_rbn(&urb, 5)->color);
         ASSERT_EQ(RED, find_rbn(&urb, 6)->color);
         ASSERT_EQ(urb.root, find_rbn(&urb, 2));
         ASSERT_EQ(urb.root->left, find_rbn(&urb, 1));
         ASSERT_EQ(urb.root->right, find_rbn(&urb, 4));
         delete_urb(&urb);
    }

    TEST_F(CoreTest, min) {
         urb urb;
         rbn *n;
         int i, T = 6;
         ASSERT_EQ(create_urb(&urb, urb_cmp, urb_dst), RB_SUCCESS);
         for (i=1; i<=T; ++i)
             ASSERT_EQ(urb_tree_put(&urb, i, i), RB_SUCCESS);
         chk_invariants_urb(&urb);
         ASSERT_EQ(1, min_urb(&urb, urb.root)->key);
         ASSERT_TRUE((n = find_rbn(&urb, 4)) != NULL);
         ASSERT_EQ(3, min_urb(&urb, n)->key);
         delete_urb(&urb);
    }

    TEST_F(CoreTest, max) {
         urb urb;
         rbn *n;
         int i, T = 6;
         ASSERT_EQ(create_urb(&urb, urb_cmp, urb_dst), RB_SUCCESS);
         for (i=1; i<=T; ++i)
             ASSERT_EQ(urb_tree_put(&urb, i, i), RB_SUCCESS);
         chk_invariants_urb(&urb);
         ASSERT_EQ(T, max_urb(&urb, urb.root)->key);
         ASSERT_TRUE((n = find_rbn(&urb, 4)) != NULL);
         ASSERT_EQ(T, max_urb(&urb, n)->key);
         delete_urb(&urb);
    }

    TEST_F(CoreTest, succ) {
         urb urb;
         rbn *n;
         ASSERT_EQ(create_urb(&urb, urb_cmp, urb_dst), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  8,  8), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  5,  5), RB_SUCCESS);         
         ASSERT_EQ(urb_tree_put(&urb,  2,  2), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  1,  1), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 14, 14), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  7,  7), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 11, 11), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 12, 12), RB_SUCCESS);
         chk_invariants_urb(&urb);
         ASSERT_TRUE((n = find_rbn(&urb, 8)) != NULL);
         ASSERT_EQ(11, succ_rbn(&urb, n)->key);
         ASSERT_TRUE((n = find_rbn(&urb, 11)) != NULL);
         ASSERT_EQ(12, succ_rbn(&urb, n)->key);
         ASSERT_TRUE((n = find_rbn(&urb, 14)) != NULL);
         ASSERT_EQ(NULL, succ_rbn(&urb, n));
         ASSERT_TRUE((n = find_rbn(&urb, 5)) != NULL);
         ASSERT_EQ(7, succ_rbn(&urb, n)->key);
         delete_urb(&urb);
    }

    TEST_F(CoreTest, prev) {
         urb urb;
         rbn *n;
         ASSERT_EQ(create_urb(&urb, urb_cmp, urb_dst), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  8,  8), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  5,  5), RB_SUCCESS);         
         ASSERT_EQ(urb_tree_put(&urb,  2,  2), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  1,  1), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 14, 14), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb,  7,  7), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 11, 11), RB_SUCCESS);
         ASSERT_EQ(urb_tree_put(&urb, 12, 12), RB_SUCCESS);
         chk_invariants_urb(&urb);
         ASSERT_TRUE((n = find_rbn(&urb, 8)) != NULL);
         ASSERT_EQ(7, prev_rbn(&urb, n)->key);
         ASSERT_TRUE((n = find_rbn(&urb, 11)) != NULL);
         ASSERT_EQ(8, prev_rbn(&urb, n)->key);
         ASSERT_TRUE((n = find_rbn(&urb, 14)) != NULL);
         ASSERT_EQ(12, prev_rbn(&urb, n)->key);
         ASSERT_TRUE((n = find_rbn(&urb, 5)) != NULL);
         ASSERT_EQ(2, prev_rbn(&urb, n)->key);
         ASSERT_TRUE((n = find_rbn(&urb, 1)) != NULL);
         ASSERT_EQ(NULL, prev_rbn(&urb, n));
         delete_urb(&urb);
    }
    */

}  // namespace